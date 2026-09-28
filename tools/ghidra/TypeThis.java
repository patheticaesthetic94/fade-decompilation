// Ghidra headless post-script: for each "this <Type> <name-regex> ..." line in symbols.txt, commit the decompiler's
// parameters of every matching game function and retype param_1 as <Type>* named "this".
// "arg <n> <Type> <name-regex> ..." types param_<n> (1-based) as <Type>* and keeps its name.
// "ret <Type> <name-regex> ..." sets the return type to <Type>*.
// "rval <Type> <name-regex> ..." sets the return type to <Type> itself (int, byte, ushort, ...).
// "val <n> <Type> <name-regex> ..." types param_<n> as <Type> itself (by value, e.g. a CString argument).
// "nargs <n> <name-regex> ..." drops parameters after the n-th (register spills the decompiler took for args).
// "like <srcFn> <name-regex> ..." copies srcFn's parameters and return type (wrappers that tail-call it).
// <Type> may be a C type such as char* (then "arg" gives char**). Lib functions match only by exact name.
// Usage: -postScript TypeThis.java [libStartHex]
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.HighFunctionDBUtil;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
import java.util.*;

public class TypeThis extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        long libStart = args.length > 0 ? Long.parseLong(args[0], 16) : Long.MAX_VALUE;
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        Map<Function, Map<Integer, DataType>> todo = new LinkedHashMap<>();
        Map<Function, Integer> nargs = new HashMap<>();
        Map<Function, String> like = new LinkedHashMap<>();
        Set<Function> thisFns = new HashSet<>();
        ghidra.util.data.DataTypeParser parser = new ghidra.util.data.DataTypeParser(dtm, dtm, null,
            ghidra.util.data.DataTypeParser.AllowedDataTypes.ALL);
        Path p = Paths.get(getSourceFile().getParentFile().getAbsolutePath(), "symbols.txt");
        for (String line : Files.readAllLines(p)) {
            line = line.replaceAll("//.*", "").trim();
            if (!line.matches("(this|arg|ret|rval|val|nargs|like) .*")) continue;
            if (line.startsWith("like ")) {
                String[] g = line.split("\\s+");
                for (int i = 2; i < g.length; i++) for (Function fn : matching(g[i], libStart)) like.put(fn, g[1]);
                continue;
            }
            if (line.startsWith("nargs ")) {
                String[] g = line.split("\\s+");
                for (int i = 2; i < g.length; i++)
                    for (Function fn : matching(g[i], libStart)) { nargs.put(fn, Integer.parseInt(g[1])); todo.computeIfAbsent(fn, k -> new TreeMap<>()); }
                continue;
            }
            boolean byVal = line.startsWith("val ") || line.startsWith("rval ");
            if (line.startsWith("rval ")) line = "arg 0" + line.substring(4);
            else if (byVal) line = "arg" + line.substring(3);
            if (line.startsWith("ret ")) line = "arg 0" + line.substring(3);
            boolean isThis = line.startsWith("this ");
            if (isThis) line = "arg 1" + line.substring(4);
            String[] f0 = line.split("\\s+");
            int idx = Integer.parseInt(f0[1]) - 1;
            String[] f = Arrays.copyOfRange(f0, 1, f0.length);
            DataType base;
            if (f[1].contains("*")) base = parser.parse(f[1]);
            else {
                List<DataType> found = new ArrayList<>();
                dtm.findDataTypes(f[1], found);
                base = found.isEmpty() ? parser.parse(f[1]) : found.get(0);
            }
            DataType ptr = byVal ? base : dtm.getPointer(base);
            for (int i = 2; i < f.length; i++)
                for (Function fn : matching(f[i], libStart)) {
                    todo.computeIfAbsent(fn, k -> new TreeMap<>()).put(idx, ptr);
                    if (isThis) thisFns.add(fn);
                }
        }
        DecompInterface ifc = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        opts.grabFromProgram(currentProgram);
        ifc.setOptions(opts);
        ifc.openProgram(currentProgram);
        int n = 0;
        for (Map.Entry<Function, Map<Integer, DataType>> e : todo.entrySet()) {
            Function fn = e.getKey();
            try {
                if (fn.getSignatureSource() == SourceType.DEFAULT || fn.getParameterCount() == 0) {
                    DecompileResults r = ifc.decompileFunction(fn, 60, monitor);
                    if (!r.decompileCompleted()) continue;
                    HighFunctionDBUtil.commitParamsToDatabase(r.getHighFunction(), true,
                        HighFunctionDBUtil.ReturnCommitOption.COMMIT, SourceType.USER_DEFINED);
                }
                Integer keep = nargs.get(fn);
                if (keep != null) while (fn.getParameterCount() > keep) fn.removeParameter(fn.getParameterCount() - 1);
                for (Map.Entry<Integer, DataType> a : e.getValue().entrySet()) {
                    if (a.getKey() < 0) { fn.setReturnType(a.getValue(), SourceType.USER_DEFINED); n++; continue; }
                    // params the decompiler missed (only passed through to a callee) are appended
                    while (fn.getParameterCount() <= a.getKey())
                        fn.insertParameter(fn.getParameterCount(), new ParameterImpl(null, Undefined4DataType.dataType, currentProgram), SourceType.USER_DEFINED);
                    Parameter pa = fn.getParameter(a.getKey());
                    pa.setDataType(a.getValue(), SourceType.USER_DEFINED);
                    if (a.getKey() == 0 && thisFns.contains(fn)) pa.setName("this", SourceType.USER_DEFINED);
                    n++;
                }
            } catch (Exception ex) {
                println("ERROR this: " + fn.getName() + ": " + ex);
            }
        }
        for (Map.Entry<Function, String> e : like.entrySet()) {
            Function fn = e.getKey();
            List<Function> src = matching(e.getValue(), Long.MAX_VALUE);
            if (src.isEmpty()) continue;
            List<Variable> ps = new ArrayList<>();
            for (Parameter q : src.get(0).getParameters())
                ps.add(new ParameterImpl(q.getName(), q.getDataType(), currentProgram));
            try {
                fn.updateFunction(null, new ReturnParameterImpl(src.get(0).getReturnType(), currentProgram), ps,
                    Function.FunctionUpdateType.DYNAMIC_STORAGE_ALL_PARAMS, true, SourceType.USER_DEFINED);
                n++;
            } catch (Exception ex) { println("ERROR like: " + fn.getName() + ": " + ex); }
        }
        println("REPORT this typed: " + n);
    }

    // lib (CRT/MFC) functions only by exact name
    List<Function> matching(String pat, long libStart) {
        java.util.regex.Pattern re = java.util.regex.Pattern.compile(pat);
        List<Function> out = new ArrayList<>();
        for (Function fn : currentProgram.getFunctionManager().getFunctions(true)) {
            if (fn.getEntryPoint().getOffset() >= libStart && !pat.matches("\\w+")) break;
            if (re.matcher(fn.getName()).matches()) out.add(fn);
        }
        if (out.isEmpty()) println("ERROR this: no function matches " + pat);
        return out;
    }
}
