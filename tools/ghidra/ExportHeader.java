// Ghidra headless post-script: emit a C++ header of the types and globals that decomp/game.c uses.
// Usage: -postScript ExportHeader.java <outdir>     (run after DecompileAll; reads <outdir>/game.c, writes <outdir>/fade_types.h)
// Memory types keep the original 32-bit layout: every pointer stored in memory becomes P32<T> (port/include/p32.h),
// structs are packed with explicit padding and size-asserted. Globals become macros over their original address,
// since the port maps the image's data sections at their original virtual addresses.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.regex.*;

public class ExportHeader extends GhidraScript {
    Map<String, DataType> byName = new HashMap<>();
    LinkedHashSet<DataType> emitted = new LinkedHashSet<>();
    Set<DataType> visiting = new HashSet<>();
    StringBuilder defs = new StringBuilder();
    TreeSet<String> fwd = new TreeSet<>();

    static String cname(String n) { return n.replaceAll("[^A-Za-z0-9_]", "_"); }

    // [base, suffix] declarator parts for a memory-resident type
    String[] decl(DataType dt) {
        if (dt instanceof TypeDef && !(((TypeDef) dt).getBaseDataType() instanceof Composite)
                && dt.getCategoryPath().isRoot() == false && dt.getName().matches("undefined\\d|uint|ushort|byte|ulong|sbyte|word|dword|uchar|longlong|ulonglong|wchar16|wchar32"))
            return new String[]{dt.getName(), ""};
        if (dt instanceof Pointer) {
            DataType t = ((Pointer) dt).getDataType();
            if (t == null || t instanceof FunctionDefinition || t instanceof DefaultDataType) return new String[]{"P32<void>", ""};
            String[] in = decl(t);
            if (!in[1].isEmpty()) return new String[]{"P32<void>", ""};
            return new String[]{"P32<" + in[0] + ">", ""};
        }
        if (dt instanceof Array) {
            Array a = (Array) dt;
            String[] in = decl(a.getDataType());
            return new String[]{in[0], "[" + a.getNumElements() + "]" + in[1]};
        }
        if (dt instanceof AbstractStringDataType || dt instanceof StringDataType || dt.getName().startsWith("string") || dt.getName().startsWith("unicode") || dt.getName().equals("TerminatedCString") || dt.getName().equals("TerminatedUnicode")) {
            boolean w = dt.getName().toLowerCase().contains("unicode") || dt.getName().contains("16");
            return new String[]{w ? "wchar16" : "char", "[]"};
        }
        if (dt instanceof Composite || dt instanceof ghidra.program.model.data.Enum || dt instanceof TypeDef) { need(dt); return new String[]{cname(dt.getName()), ""}; }
        if (dt instanceof FunctionDefinition) return new String[]{"uint8_t", "[4]"};
        if (dt instanceof DefaultDataType || dt instanceof Undefined) return new String[]{"undefined" + Math.max(1, dt.getLength()), ""};
        String n = dt.getName();
        if (n.equals("wchar_t")) n = "wchar16";
        return new String[]{cname(n), ""};
    }

    void need(DataType dt) {
        if (emitted.contains(dt) || visiting.contains(dt)) return;
        visiting.add(dt);
        StringBuilder sb = new StringBuilder();
        String n = cname(dt.getName());
        if (dt instanceof Structure || dt instanceof Union) {
            Composite c = (Composite) dt;
            boolean u = dt instanceof Union;
            fwd.add((u ? "union " : "struct ") + n + ";");
            sb.append(u ? "union " : "struct ").append(n).append(" {\n");
            int off = 0, pad = 0;
            for (DataTypeComponent m : c.getDefinedComponents()) {
                if (m.isBitFieldComponent()) continue;
                DataType t = m.getDataType();
                if (t instanceof DefaultDataType) continue;
                if (!u && m.getOffset() > off) { sb.append("  uint8_t field_0x").append(Integer.toHexString(off)).append("[").append(m.getOffset() - off).append("];\n"); }
                String[] d = decl(t);
                String fn = m.getFieldName() != null ? m.getFieldName() : m.getDefaultFieldName();
                if (d[1].equals("[]")) d[1] = "[" + t.getLength() / (d[0].equals("wchar16") ? 2 : 1) + "]";
                sb.append("  ").append(d[0]).append(" ").append(cname(fn)).append(d[1]).append(";\n");
                if (!u) off = m.getOffset() + m.getLength();
            }
            if (!u && dt.getLength() > off) sb.append("  uint8_t field_0x").append(Integer.toHexString(off)).append("[").append(dt.getLength() - off).append("];\n");
            sb.append("};\nstatic_assert(sizeof(").append(n).append(") == ").append(dt.getLength()).append(", \"").append(n).append("\");\n");
        } else if (dt instanceof ghidra.program.model.data.Enum) {
            ghidra.program.model.data.Enum e = (ghidra.program.model.data.Enum) dt;
            sb.append("typedef ").append(e.getLength() == 1 ? "uint8_t" : e.getLength() == 2 ? "uint16_t" : "uint32_t").append(" ").append(n).append(";\n");
            for (String v : e.getNames()) sb.append("#define ").append(cname(v)).append(" ").append(e.getValue(v)).append("\n");
        } else if (dt instanceof TypeDef) {
            String[] d = decl(((TypeDef) dt).getDataType());
            if (d[1].equals("[]")) d[1] = "[" + dt.getLength() + "]";
            sb.append("typedef ").append(d[0]).append(" ").append(n).append(d[1]).append(";\n");
        }
        visiting.remove(dt);
        emitted.add(dt);
        defs.append(sb);
    }

    @Override
    public void run() throws Exception {
        String out = getScriptArgs()[0];
        String src = new String(Files.readAllBytes(Paths.get(out, "game.c")));
        Set<String> words = new HashSet<>();
        Matcher mw = Pattern.compile("[A-Za-z_][A-Za-z0-9_]*").matcher(src);
        while (mw.find()) words.add(mw.group());

        DataTypeManager dtm = currentProgram.getDataTypeManager();
        Iterator<DataType> it = dtm.getAllDataTypes();
        while (it.hasNext()) {
            DataType dt = it.next();
            if (!(dt instanceof Composite || dt instanceof ghidra.program.model.data.Enum || dt instanceof TypeDef)) continue;
            if (words.contains(dt.getName()) && !byName.containsKey(dt.getName())) byName.put(dt.getName(), dt);
        }
        Set<String> builtin = Set.of("uint", "ushort", "byte", "ulong", "uchar", "wchar16", "undefined1", "undefined2", "undefined4", "undefined8", "sbyte", "dword", "word", "longlong", "ulonglong", "wchar32");
        for (DataType dt : byName.values()) if (!builtin.contains(dt.getName())) need(dt);

        // globals: every data symbol named in game.c
        StringBuilder g = new StringBuilder();
        SymbolTable st = currentProgram.getSymbolTable();
        Listing lst = currentProgram.getListing();
        TreeSet<String> names = new TreeSet<>(words);
        for (String w : names) {
            if (!w.matches("(g_|s_|u_|DAT_|PTR_).*")) continue;
            SymbolIterator si = st.getSymbols(w);
            Address a;
            if (si.hasNext()) {
                Symbol s = si.next();
                if (s.getSymbolType() == SymbolType.FUNCTION) continue;
                a = s.getAddress();
            } else {
                Matcher ma = Pattern.compile("_([0-9a-f]{8})$").matcher(w);   // decompiler-made name: s_text_00043c28
                if (!ma.find()) continue;
                a = toAddr(Long.parseLong(ma.group(1), 16));
            }
            if (!a.isMemoryAddress()) continue;
            Data d = lst.getDataAt(a);
            DataType dt = d != null ? d.getDataType() : null;
            String[] dd = dt == null || dt instanceof DefaultDataType ? new String[]{"undefined4", ""} : decl(dt);
            if (dd[1].equals("[]")) dd[1] = "[" + Math.max(1, d.getLength() / (dd[0].equals("wchar16") ? 2 : 1)) + "]";
            g.append("typedef ").append(dd[0]).append(" T_").append(w).append(dd[1]).append(";\n");
            g.append("#define ").append(w).append(" (*(T_").append(w).append(" *)(uintptr_t)0x").append(a.toString()).append(")\n");
        }
        try (PrintWriter pw = new PrintWriter(new File(out, "fade_types.h"))) {
            pw.println("// Generated by tools/ghidra/ExportHeader.java -- do not edit.\n#pragma once\n#pragma pack(push, 1)");
            for (String f : fwd) pw.println(f);
            pw.print(defs);
            pw.println("#pragma pack(pop)");
            pw.print(g);
        }
        println("REPORT ExportHeader: " + emitted.size() + " types");
    }
}
