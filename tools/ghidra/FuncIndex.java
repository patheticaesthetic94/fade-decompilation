// Ghidra headless script: one line per game function, for picking names without reading game.c.
// Usage: -postScript FuncIndex.java <outfile> [libStartHex]
// Line format: <addr> <name> <size> | callees: a,b,... | str: "..." "..."
// Strings are found via direct refs and via literal-pool words that point at a string.
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.util.*;

public class FuncIndex extends GhidraScript {
    String str(Address a) {
        Data d = getDataAt(a);
        if (d != null && d.hasStringValue()) return d.getDefaultValueRepresentation();
        try { // undefined: try reading a UTF-16 or ASCII string
            StringBuilder sb = new StringBuilder();
            boolean wide = getByte(a.add(1)) == 0;
            for (int i = 0; i < 80; i++) {
                int c = wide ? getShort(a.add(2 * i)) & 0xffff : getByte(a.add(i)) & 0xff;
                if (c == 0) break;
                if (c < 0x20 || c > 0x7e) return null;
                sb.append((char) c);
            }
            return sb.length() >= 3 ? (wide ? "u\"" : "\"") + sb + "\"" : null;
        } catch (Exception e) { return null; }
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        long libStart = args.length > 1 ? Long.parseLong(args[1], 16) : Long.MAX_VALUE;
        ReferenceManager rm = currentProgram.getReferenceManager();
        try (PrintWriter w = new PrintWriter(new File(args[0]))) {
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                if (f.getEntryPoint().getOffset() >= libStart) break;
                Set<String> callees = new LinkedHashSet<>();
                for (Function c : f.getCalledFunctions(monitor)) callees.add(c.getName());
                Set<String> strs = new LinkedHashSet<>();
                for (Address a : f.getBody().getAddresses(true)) {
                    for (Reference r : rm.getReferencesFrom(a)) {
                        if (!r.getReferenceType().isData()) continue;
                        Address t = r.getToAddress();
                        String s = str(t);
                        if (s == null) { // literal pool word -> pointer
                            try {
                                Address p = toAddr(getInt(t) & 0xffffffffL);
                                s = str(p);
                                Symbol sym = getSymbolAt(p);
                                if (s == null && sym != null && sym.getName().startsWith("IAT_"))
                                    callees.add(sym.getName().substring(4));
                            } catch (Exception e) { }
                        }
                        if (s != null) strs.add(s);
                    }
                }
                w.println(f.getEntryPoint() + " " + f.getName() + " " + f.getBody().getNumAddresses()
                    + " | " + String.join(",", callees) + " | " + String.join(" ", strs));
            }
        }
    }
}
