// Ghidra headless post-script: commit the decompiler's parameters and return type for every game function
// that has no user-set signature yet, so callers decompile against the same prototype the callee's own
// body shows (otherwise calls come out as RGB565_Pack() with the arguments dropped).
// Usage: -postScript CommitSigs.java <libStartHex>
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.SourceType;

public class CommitSigs extends GhidraScript {
    @Override
    public void run() throws Exception {
        long lib = Long.parseLong(getScriptArgs()[0], 16);
        DecompInterface ifc = new DecompInterface();
        ifc.openProgram(currentProgram);
        int n = 0;
        for (int pass = 0; pass < 2; pass++)   // second pass sees callees' committed signatures
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                if (f.getEntryPoint().getOffset() >= lib) break;
                if (f.getSignatureSource() == SourceType.USER_DEFINED) continue;
                DecompileResults r = ifc.decompileFunction(f, 60, monitor);
                HighFunction hf = r.getHighFunction();
                if (hf == null) continue;
                HighFunctionDBUtil.commitParamsToDatabase(hf, true, HighFunctionDBUtil.ReturnCommitOption.COMMIT, SourceType.ANALYSIS);
                if (pass == 1) n++;
            }
        println("REPORT signatures committed: " + n);
    }
}
