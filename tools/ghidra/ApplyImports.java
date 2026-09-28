// Ghidra headless pre-script for Fade.exe (ARM WinCE PE).
// 1. Renames Ordinal_N imports using defs/<dll>.def (mingw-w64 libce .def files).
// 2. Labels every IAT slot with its import name and types it as a pointer. Fade's IAT lives
//    in .data and Ghidra leaves it untyped, so without this calls show up as (*(code*)*DAT_x)().
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.PointerDataType;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.*;
import java.io.File;
import java.nio.file.*;
import java.util.*;
import java.util.regex.*;

public class ApplyImports extends GhidraScript {
    Map<String, Map<Integer, String>> defs = new HashMap<>();

    String ordinalName(String dll, int ord) throws Exception {
        String key = dll.toLowerCase().replace(".dll", "");
        if (!defs.containsKey(key)) {
            Map<Integer, String> m = new HashMap<>();
            Path p = Paths.get(getSourceFile().getParentFile().getAbsolutePath(), "defs", key + ".def");
            if (Files.exists(p)) {
                Pattern re = Pattern.compile("^\\s*([A-Za-z_?@][^\\s@=]*)\\S*\\s*@(\\d+)");
                for (String line : Files.readAllLines(p)) {
                    Matcher mm = re.matcher(line);
                    if (mm.find()) m.putIfAbsent(Integer.parseInt(mm.group(2)), mm.group(1));
                }
            }
            defs.put(key, m);
        }
        return defs.get(key).get(ord);
    }

    @Override
    public void run() throws Exception {
        SymbolTable st = currentProgram.getSymbolTable();
        ReferenceManager rm = currentProgram.getReferenceManager();
        for (Symbol s : st.getExternalSymbols()) {
            String dll = s.getParentNamespace().getName();
            String name = s.getName();
            if (name.startsWith("Ordinal_")) {
                String n = ordinalName(dll, Integer.parseInt(name.substring(8)));
                if (n == null) { println("unresolved: " + dll + "::" + name); continue; }
                s.setName(n, SourceType.IMPORTED);
                name = n;
            }
        }
        // IAT slots carry external references (slot -> external location).
        ReferenceIterator it = rm.getExternalReferences();
        List<Reference> refs = new ArrayList<>();
        while (it.hasNext()) refs.add(it.next());
        for (Reference r : refs) {
            Address slot = r.getFromAddress();
            String name = ((ExternalReference) r).getExternalLocation().getLabel();
            if (name.startsWith("?")) name = name.substring(1, name.indexOf("@@"));
            try {
                clearListing(slot, slot.add(3));
                createData(slot, PointerDataType.dataType);
                rm.addExternalReference(slot, ((ExternalReference) r).getLibraryName(),
                    ((ExternalReference) r).getExternalLocation().getLabel(),
                    null, SourceType.IMPORTED, 0, RefType.DATA);
            } catch (Exception e) { println("type fail " + slot + " " + e); }
            createLabel(slot, "IAT_" + name, true, SourceType.IMPORTED);
            // ARM code reaches the slot through literal-pool words in .text; type them as pointers
            // so the decompiler prints *PTR_IAT_<name> instead of *DAT_x.
            byte[] pat = new byte[4];
            long v = slot.getOffset();
            for (int i = 0; i < 4; i++) pat[i] = (byte) (v >> (8 * i));
            MemoryBlock text = currentProgram.getMemory().getBlock(".text");
            Address hit = text.getStart();
            while ((hit = currentProgram.getMemory().findBytes(hit, text.getEnd(), pat, null, true, monitor)) != null) {
                if (hit.getOffset() % 4 == 0) {
                    try { clearListing(hit, hit.add(3)); createData(hit, PointerDataType.dataType); }
                    catch (Exception e) { println("pool fail " + hit + " " + e); }
                }
                hit = hit.add(1);
            }
        }
    }
}
