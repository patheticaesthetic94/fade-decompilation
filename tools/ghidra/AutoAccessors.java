// Ghidra headless post-script: name trivial unnamed game functions (<= 32 bytes) after what they do,
// from their decompiled C. Manual names (symbols.txt) are never touched.
//   get<bits>_<off>_<addr>  return *(T*)(this+off)       set<bits>_<off>_<addr>  *(T*)(this+off) = arg
//   fld_<off>_<addr>        return this+off              elem<size>_<off>_<addr> return this+off+i*size
//   nop_<addr>              empty body
// Usage: -postScript AutoAccessors.java [libStartHex]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import java.util.regex.*;

public class AutoAccessors extends GhidraScript {
    static String bits(String t) {
        if (t == null) return "32";
        if (t.contains("1") || t.contains("byte") || t.contains("char") || t.equals("bool")) return "8";
        if (t.contains("2") || t.contains("short")) return "16";
        return "32";
    }
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        long libStart = args.length > 0 ? Long.parseLong(args[0], 16) : Long.MAX_VALUE;
        DecompInterface ifc = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        opts.grabFromProgram(currentProgram);
        ifc.setOptions(opts);
        ifc.openProgram(currentProgram);
        String T = "\\(?(?:\\(\\s*)?([a-z_0-9 ]+?)\\s*\\*\\)\\s*";
        Pattern get = Pattern.compile("^return \\*(?:" + T + ")?\\(?param_1(?: \\+ (0x[0-9a-f]+|\\d+))?\\)?;$");
        Pattern set = Pattern.compile("^\\*(?:" + T + ")?\\(?param_1(?: \\+ (0x[0-9a-f]+|\\d+))?\\)? = \\(?[a-z0-9_ ]*\\)?param_2;(?: return;)?$");
        Pattern fld = Pattern.compile("^return (?:\\([a-z0-9_ ]+\\*\\))?param_1 \\+ (0x[0-9a-f]+|\\d+);$");
        Pattern elem = Pattern.compile("^return \\(param_2 & 0xff\\) \\* (0x[0-9a-f]+|\\d+) \\+ param_1(?: \\+ (0x[0-9a-f]+|\\d+))?;$");
        int n = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            long ep = f.getEntryPoint().getOffset();
            if (ep >= libStart) break;
            if (!f.getName().startsWith("FUN_") || f.getBody().getNumAddresses() > 32) continue;
            DecompileResults r = ifc.decompileFunction(f, 30, monitor);
            if (!r.decompileCompleted()) continue;
            String c = r.getDecompiledFunction().getC();
            String body = c.substring(c.indexOf('{') + 1, c.lastIndexOf('}'))
                .replaceAll("(?m)^\\s*(?!return\\b)[A-Za-z_0-9]+ \\*?[a-zA-Z_0-9]+;\\s*$", "").replaceAll("\\s+", " ").trim();
            String a = String.format("%05x", ep);
            String name = null;
            Matcher m;
            if (body.isEmpty() || body.equals("return;")) name = "nop_" + a;
            else if ((m = get.matcher(body)).matches()) name = "get" + bits(m.group(1)) + "_" + off(m.group(2)) + "_" + a;
            else if ((m = set.matcher(body)).matches()) name = "set" + bits(m.group(1)) + "_" + off(m.group(2)) + "_" + a;
            else if ((m = fld.matcher(body)).matches()) name = "fld_" + off(m.group(1)) + "_" + a;
            else if ((m = elem.matcher(body)).matches()) name = "elem" + off(m.group(1)) + "_" + off(m.group(2)) + "_" + a;
            if (name != null) { f.setName(name, SourceType.ANALYSIS); n++; }
        }
        println("REPORT accessors named: " + n);
    }
    static String off(String s) {
        if (s == null) return "0";
        return Long.toHexString(s.startsWith("0x") ? Long.parseLong(s.substring(2), 16) : Long.parseLong(s));
    }
}
