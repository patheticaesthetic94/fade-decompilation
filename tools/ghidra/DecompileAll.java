// Ghidra headless post-script: decompile every function.
// Usage: -postScript DecompileAll.java <outdir> [libStartHex]
// Functions below libStartHex go to <outdir>/game.c, the rest (import thunks, CRT, static MFC)
// to <outdir>/lib.c. Each function is prefixed with "// <addr> <name>".
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import java.io.*;

public class DecompileAll extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        String out = args.length > 0 ? args[0] : ".";
        long libStart = args.length > 1 ? Long.parseLong(args[1], 16) : Long.MAX_VALUE;
        DecompInterface ifc = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        opts.grabFromProgram(currentProgram); // program options incl. "respect read-only flags"
        ifc.setOptions(opts);
        ifc.openProgram(currentProgram);
        try (PrintWriter game = new PrintWriter(new File(out, "game.c"));
             PrintWriter lib = new PrintWriter(new File(out, "lib.c"))) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                PrintWriter w = f.getEntryPoint().getOffset() < libStart ? game : lib;
                DecompileResults r = ifc.decompileFunction(f, 120, monitor);
                w.println("// " + f.getEntryPoint() + " " + f.getName());
                w.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// FAILED: " + r.getErrorMessage());
            }
        }
    }
}
