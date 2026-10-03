package org.fadeport.fade;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.net.Uri;
import android.os.Message;
import android.util.Log;
import android.webkit.ConsoleMessage;
import android.webkit.ValueCallback;
import android.webkit.WebChromeClient;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Toast;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

/**
 * The web player's page in a WebView, as Home (HomeActivity) and over the native game (GameActivity):
 * local assets, new-tab links (walkthrough here, anything else in the browser), Restore's file
 * picker and Back up's "save as". The owning activity forwards onActivityResult.
 */
final class PlayerWeb {
    private static final int SAVE_BACKUP = 41, OPEN_BACKUP = 42;
    final WebView view;
    private final Activity activity;
    private ValueCallback<Uri[]> chooser;
    private String pendingBackup;

    @SuppressLint("SetJavaScriptEnabled")
    PlayerWeb(Activity activity, Object bridge) {
        this.activity = activity;
        // Chrome DevTools over adb in debuggable builds.
        WebView.setWebContentsDebuggingEnabled((activity.getApplicationInfo().flags & ApplicationInfo.FLAG_DEBUGGABLE) != 0);
        view = new WebView(activity);
        WebSettings s = view.getSettings();
        s.setJavaScriptEnabled(true);
        s.setDomStorageEnabled(true);
        s.setMediaPlaybackRequiresUserGesture(false);
        s.setAllowFileAccess(false);
        s.setAllowContentAccess(false);
        s.setSupportMultipleWindows(true);   // target=_blank links come to onCreateWindow
        s.setTextZoom(100);                  // the page sizes itself to the screen
        view.addJavascriptInterface(bridge, "FadeAndroid");
        view.setWebViewClient(new WebViewClient() {
            @Override
            public WebResourceResponse shouldInterceptRequest(WebView v, WebResourceRequest request) {
                return Assets.serve(activity, request.getUrl());
            }

            @Override
            public boolean shouldOverrideUrlLoading(WebView v, WebResourceRequest request) {
                if (Assets.isLocal(request.getUrl())) return false;
                HomeActivity.openExternal(activity, request.getUrl());
                return true;
            }
        });
        view.setWebChromeClient(new WebChromeClient() {
            @Override
            public boolean onConsoleMessage(ConsoleMessage m) {
                Log.println(m.messageLevel() == ConsoleMessage.MessageLevel.ERROR ? Log.ERROR : Log.INFO, "Fade",
                        m.message() + " (" + m.sourceId() + ":" + m.lineNumber() + ")");
                return true;
            }

            @Override
            public boolean onCreateWindow(WebView v, boolean dialog, boolean gesture, Message result) {
                // A new-tab link: catch its URL in a throwaway view, then open it here or in the browser.
                WebView probe = new WebView(activity);
                probe.setWebViewClient(new WebViewClient() {
                    @Override
                    public boolean shouldOverrideUrlLoading(WebView p, WebResourceRequest request) {
                        Uri uri = request.getUrl();
                        if (Assets.isLocal(uri)) GuideActivity.open(activity, uri);
                        else HomeActivity.openExternal(activity, uri);
                        p.destroy();
                        return true;
                    }
                });
                ((WebView.WebViewTransport) result.obj).setWebView(probe);
                result.sendToTarget();
                return true;
            }

            @Override
            public boolean onShowFileChooser(WebView v, ValueCallback<Uri[]> callback, FileChooserParams params) {
                // Restore on the Home menu: pick a fade-saves.json backup.
                if (chooser != null) chooser.onReceiveValue(null);
                chooser = callback;
                Intent pick = new Intent(Intent.ACTION_OPEN_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE).setType("*/*")
                        .putExtra(Intent.EXTRA_MIME_TYPES, new String[] {"application/json", "text/plain", "application/octet-stream"});
                try {
                    activity.startActivityForResult(pick, OPEN_BACKUP);
                } catch (ActivityNotFoundException e) {
                    chooser = null;
                    return false;
                }
                return true;
            }
        });
    }

    /** Back up: the page's download link, handed over by the shim. */
    void saveFile(String name, String text) {
        activity.runOnUiThread(() -> {
            pendingBackup = text;
            Intent create = new Intent(Intent.ACTION_CREATE_DOCUMENT).addCategory(Intent.CATEGORY_OPENABLE)
                    .setType("application/json").putExtra(Intent.EXTRA_TITLE, name);
            try {
                activity.startActivityForResult(create, SAVE_BACKUP);
            } catch (ActivityNotFoundException e) {
                pendingBackup = null;
            }
        });
    }

    boolean onActivityResult(int request, int result, Intent data) {
        Uri uri = result == Activity.RESULT_OK && data != null ? data.getData() : null;
        if (request == OPEN_BACKUP) {
            if (chooser != null) chooser.onReceiveValue(uri == null ? null : new Uri[] {uri});
            chooser = null;
            return true;
        }
        if (request != SAVE_BACKUP) return false;
        String text = pendingBackup;
        pendingBackup = null;
        if (uri == null || text == null) return true;
        try (OutputStream out = activity.getContentResolver().openOutputStream(uri, "wt")) {
            out.write(text.getBytes(StandardCharsets.UTF_8));
            Toast.makeText(activity, "Save backup written", Toast.LENGTH_SHORT).show();
        } catch (IOException | NullPointerException e) {
            Toast.makeText(activity, "The backup could not be written", Toast.LENGTH_LONG).show();
        }
        return true;
    }

    /** Asks the page's shim to handle Back; runs `otherwise` when it did not (Home: leave the app). */
    void back(Runnable otherwise) {
        view.evaluateJavascript("window.fadeAndroidBack ? fadeAndroidBack() : false", handled -> {
            if (!"true".equals(handled)) otherwise.run();
        });
    }
}
