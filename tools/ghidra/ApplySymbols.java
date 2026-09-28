// Ghidra headless script: apply durable names (and optional types) from tools/ghidra/symbols.txt.
// Line formats (blank lines and lines starting with # are ignored, // starts a comment):
//   <hexaddr> <name> [:type]                   function rename (created if missing) or global label;
//                                              :type (e.g. :short, :ushort[8], :ImgRect[6]) also types the data
//   struct <Name> <field>:<type> ...           define a packed struct for later :type use (types may not contain spaces)
//   struct <Name> [size=0xN] <field>@0xOFF:<type> ...   same, fields at explicit offsets (gaps become undefined bytes)
//   this <Type> <name-regex> ...               (TypeThis.java) type param_1 of matching functions as <Type>*
//   arg <n> <Type> <name-regex> ...            (TypeThis.java) type param_<n> as <Type>*
//   ret <Type> <name-regex> ...                (TypeThis.java) set the return type to <Type>*
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import ghidra.util.data.DataTypeParser;
import java.nio.file.*;

public class ApplySymbols extends GhidraScript {
    DataTypeParser parser;

    java.util.Map<String, DataType> mine = new java.util.HashMap<>();

    DataType type(String s) throws Exception {
        // own structs first (a same-named type from an archive would make the parser ambiguous)
        java.util.regex.Matcher m = java.util.regex.Pattern.compile("(\\w+)((?:\\[\\d+\\])*)").matcher(s);
        if (m.matches() && mine.containsKey(m.group(1))) {
            DataType dt = mine.get(m.group(1));
            java.util.List<Integer> dims = new java.util.ArrayList<>();
            for (String d : m.group(2).split("[\\[\\]]+")) if (!d.isEmpty()) dims.add(Integer.parseInt(d));
            for (int i = dims.size() - 1; i >= 0; i--) dt = new ArrayDataType(dt, dims.get(i), dt.getLength());
            return dt;
        }
        return parser.parse(s.replace("unsigned_", "u"));
    }

    // an empty StructureDataType reports length 1
    static int len(StructureDataType st) { return st.isZeroLength() ? 0 : st.getLength(); }

    @Override
    public void run() throws Exception {
        DataTypeManager dtm = currentProgram.getDataTypeManager();
        parser = new DataTypeParser(dtm, dtm, null, DataTypeParser.AllowedDataTypes.ALL);
        Path p = Paths.get(getSourceFile().getParentFile().getAbsolutePath(), "symbols.txt");
        int n = 0, t = 0;
        for (String line : Files.readAllLines(p)) {
            line = line.replaceAll("//.*", "").trim();
            if (line.isEmpty() || line.startsWith("#") || line.matches("(this|arg|ret|rval|val|nargs|like) .*")) continue;
            String[] f = line.split("\\s+");
            try {
                if (f[0].equals("struct")) {
                    StructureDataType st = new StructureDataType(f[1], 0, dtm);
                    for (int i = 2; i < f.length; i++) {
                        if (f[i].startsWith("size=")) {
                            int sz = Integer.decode(f[i].substring(5));
                            if (len(st) < sz) st.growStructure(sz - len(st));
                            continue;
                        }
                        int c = f[i].indexOf(':'), at = f[i].indexOf('@');
                        DataType dt = type(f[i].substring(c + 1));
                        if (at < 0 || at > c) { st.add(dt, f[i].substring(0, c), null); continue; }
                        int off = Integer.decode(f[i].substring(at + 1, c));
                        int need = off + dt.getLength() - len(st);
                        if (need > 0) st.growStructure(need);
                        st.replaceAtOffset(off, dt, dt.getLength(), f[i].substring(0, at), null);
                    }
                    mine.put(f[1], dtm.addDataType(st, DataTypeConflictHandler.REPLACE_HANDLER));
                    continue;
                }
                Address a = toAddr(Long.parseLong(f[0].replace("0x", ""), 16));
                Function fn = getFunctionAt(a);
                if (fn == null && f[1].matches("[A-Z].*") && getInstructionAt(a) != null)
                    fn = createFunction(a, f[1]);   // code only reached through a pointer (vector ctor callbacks)
                if (fn != null) fn.setName(f[1], SourceType.USER_DEFINED);
                else createLabel(a, f[1], true, SourceType.USER_DEFINED);
                n++;
                if (f.length > 2 && f[2].startsWith(":")) {
                    DataType dt = type(f[2].substring(1));
                    clearListing(a, a.add(dt.getLength() - 1));
                    createData(a, dt);
                    t++;
                }
            } catch (Exception e) {
                println("ERROR symbols.txt: " + line + ": " + e);
            }
        }
        println("REPORT symbols applied: " + n + ", typed: " + t);
    }
}
