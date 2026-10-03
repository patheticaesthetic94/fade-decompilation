package org.fadeport.fade;

import android.content.Context;
import android.net.Uri;
import android.webkit.WebResourceResponse;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.util.Collections;

/**
 * Serves the web player's page (APK assets/web/: index.html, site.css, player.js, walkthroughs) at a
 * private https origin; no network is used. The game itself is native (GameActivity), so the page's
 * WebAssembly engine and data packs are not shipped. index.html gains the Android shim
 * (assets/android/shim.js) ahead of player.js, and starts in the player's Fullscreen layout unless
 * the URL says fs=0 (the device view, carried between Home and the game).
 */
final class Assets {
    static final String HOST = "appassets.androidplatform.net";
    static final String ORIGIN = "https://" + HOST + "/";

    private Assets() {}

    static boolean isLocal(Uri uri) {
        return "https".equals(uri.getScheme()) && HOST.equals(uri.getHost());
    }

    static WebResourceResponse serve(Context context, Uri uri) {
        if (!isLocal(uri)) return null;
        String path = uri.getPath() == null ? "" : uri.getPath().replaceFirst("^/+", "");
        if (path.isEmpty()) path = "index.html";
        if (path.contains("..")) return notFound();
        String asset = path.startsWith("android/") ? path : "web/" + path;
        try {
            InputStream in = context.getAssets().open(asset);
            if (path.equals("index.html")) in = withShim(in, !"0".equals(uri.getQueryParameter("fs")));
            WebResourceResponse r = new WebResourceResponse(mime(path), null, in);
            r.setResponseHeaders(Collections.singletonMap("Cache-Control", "no-cache"));
            return r;
        } catch (IOException e) {
            return notFound();
        }
    }

    private static InputStream withShim(InputStream in, boolean fullscreen) throws IOException {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        byte[] buf = new byte[16384];
        for (int n; (n = in.read(buf)) > 0; ) out.write(buf, 0, n);
        in.close();
        String html = new String(out.toByteArray(), StandardCharsets.UTF_8)
                .replaceFirst("<head>", "<head>\n<script src=\"android/shim.js\"></script>")
                // Fullscreen layout from the first paint, before the shim's DOMContentLoaded handler.
                .replaceFirst("<body>", fullscreen ? "<body class=\"fs android\">" : "<body class=\"android\">");
        return new ByteArrayInputStream(html.getBytes(StandardCharsets.UTF_8));
    }

    private static WebResourceResponse notFound() {
        WebResourceResponse r = new WebResourceResponse("text/plain", "utf-8", new ByteArrayInputStream(new byte[0]));
        r.setStatusCodeAndReasonPhrase(404, "Not Found");
        return r;
    }

    private static String mime(String path) {
        String ext = path.substring(path.lastIndexOf('.') + 1).toLowerCase();
        switch (ext) {
            case "html": return "text/html";
            case "css": return "text/css";
            case "js": return "text/javascript";
            case "wasm": return "application/wasm";
            case "json": return "application/json";
            case "png": return "image/png";
            case "jpg": return "image/jpeg";
            case "svg": return "image/svg+xml";
            default: return "application/octet-stream";
        }
    }
}
