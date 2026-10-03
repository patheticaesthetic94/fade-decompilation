package org.fadeport.fade;

import android.content.Context;
import android.util.Base64;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Iterator;
import org.json.JSONException;
import org.json.JSONObject;

/**
 * The native game's saved files: SDL's pref path (= getFilesDir()), holding save/... and
 * registry.txt, exactly the files the web player keeps under /saves. Exchanged with the page as
 * {relative path: base64}.
 */
final class Saves {
    private Saves() {}

    static String read(Context context) {
        JSONObject files = new JSONObject();
        File dir = context.getFilesDir();
        try {
            add(files, dir, new File(dir, "registry.txt"));
            addTree(files, dir, new File(dir, "save"));
        } catch (JSONException e) {
            throw new IllegalStateException(e);
        }
        return files.toString();
    }

    /** Restore: replaces every saved file with the backup's. */
    static boolean replace(Context context, String json) {
        File dir = context.getFilesDir();
        try {
            JSONObject files = new JSONObject(json);
            deleteTree(new File(dir, "save"));
            new File(dir, "registry.txt").delete();
            for (Iterator<String> it = files.keys(); it.hasNext(); ) {
                String name = it.next();
                File target = new File(dir, name);
                if (!target.getCanonicalPath().startsWith(dir.getCanonicalPath() + File.separator)) return false;
                target.getParentFile().mkdirs();
                try (FileOutputStream out = new FileOutputStream(target)) {
                    out.write(Base64.decode(files.getString(name), Base64.NO_WRAP));
                }
            }
            return true;
        } catch (JSONException | IOException | IllegalArgumentException e) {
            return false;
        }
    }

    private static void addTree(JSONObject files, File root, File f) throws JSONException {
        File[] list = f.listFiles();
        if (list == null) return;
        for (File c : list) {
            if (c.isDirectory()) addTree(files, root, c);
            else add(files, root, c);
        }
    }

    private static void add(JSONObject files, File root, File f) throws JSONException {
        if (!f.isFile() || f.length() > (4 << 20)) return;
        try (InputStream in = new FileInputStream(f)) {
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            byte[] buf = new byte[8192];
            for (int n; (n = in.read(buf)) > 0; ) out.write(buf, 0, n);
            files.put(root.toURI().relativize(f.toURI()).getPath(), Base64.encodeToString(out.toByteArray(), Base64.NO_WRAP));
        } catch (IOException ignored) {
        }
    }

    private static void deleteTree(File f) {
        File[] list = f.listFiles();
        if (list != null) for (File c : list) deleteTree(c);
        f.delete();
    }
}
