// Ghidra headless post-script (after analysis): type ARM literal-pool words in game code that point
// into the image as pointers. .text is read-only, so the decompiler then folds `*DAT_pool` into
// the target global (g_game, s_..., FUN_...) instead of showing an opaque DAT_ load.
// Words inside [offLo, offHi) (the g_gameState object) are field offsets added to a GameState*, not
// addresses: those are typed as plain uint constants so struct field access can resolve.
// Usage: -postScript TypePools.java [libStartHex [offLoHex offHiHex]]
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.MutabilitySettingsDefinition;
import ghidra.program.model.data.PointerDataType;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.symbol.*;

public class TypePools extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        long libStart = args.length > 0 ? Long.parseLong(args[0], 16) : Long.MAX_VALUE;
        long offLo = args.length > 2 ? Long.parseLong(args[1], 16) : 0, offHi = args.length > 2 ? Long.parseLong(args[2], 16) : 0;
        int no = 0;
        Memory mem = currentProgram.getMemory();
        ReferenceManager rm = currentProgram.getReferenceManager();
        Listing listing = currentProgram.getListing();
        int n = 0, ns = 0;
        for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
            if (f.getEntryPoint().getOffset() >= libStart) break;
            for (Address a : f.getBody().getAddresses(true)) {
                for (Reference r : rm.getReferencesFrom(a)) {
                    Address t = r.getToAddress();
                    if (!r.getReferenceType().isRead() || t.getOffset() % 4 != 0) continue;
                    if (mem.getBlock(t) == null || !mem.getBlock(t).isExecute()) continue; // pools live in .text
                    if (listing.getInstructionContaining(t) != null) continue;
                    Data d = listing.getDataAt(t);
                    if (d != null && d.isDefined() && !d.isPointer() && !d.getDataType().getName().startsWith("undefined")) continue;
                    Address v;
                    try { v = toAddr(mem.getInt(t) & 0xffffffffL); } catch (Exception e) { continue; }
                    if (mem.getBlock(v) == null) continue;
                    if (v.getOffset() > offLo && v.getOffset() < offHi) {
                        try {
                            listing.clearCodeUnits(t, t.add(3), false);
                            for (Reference pr : rm.getReferencesFrom(t)) rm.delete(pr);
                            Data od = listing.createData(t, new ghidra.program.model.data.UnsignedIntegerDataType());
                            MutabilitySettingsDefinition.DEF.setChoice(od, MutabilitySettingsDefinition.CONSTANT);
                            no++;
                        } catch (Exception e) { }
                        continue;
                    }
                    try {
                        if (d == null || !d.isPointer()) {
                            listing.clearCodeUnits(t, t.add(3), false);
                            d = listing.createData(t, new PointerDataType());
                        }
                        MutabilitySettingsDefinition.DEF.setChoice(d, MutabilitySettingsDefinition.CONSTANT);
                        n++;
                        if (typeString(mem, listing, v)) ns++;
                    } catch (Exception e) { }
                }
            }
        }
        println("REPORT pool pointers typed: " + n + ", short strings: " + ns + ", offsets: " + no);
    }

    // Short string literals in writable .data ("ON", "\\n", ".IFJ") are missed by auto-analysis:
    // type a word-aligned printable NUL-terminated run as a string so the decompiler shows its contents.
    boolean typeString(Memory mem, Listing listing, Address v) throws Exception {
        if (v.getOffset() % 4 != 0 || mem.getBlock(v).isExecute()) return false;
        Data d = listing.getDataAt(v);
        if (d != null && d.isDefined()) return false;
        int len = 0;
        for (;; len++) {
            int b = mem.getByte(v.add(len)) & 0xff;
            if (b == 0) break;
            if ((b < 0x20 || b > 0x7e) && b != '\n' && b != '\t') return false;
            if (len > 64) return false;
        }
        if (len == 0) return false;
        listing.clearCodeUnits(v, v.add(len), false);
        listing.createData(v, new ghidra.program.model.data.StringDataType(), len + 1);
        return true;
    }
}
