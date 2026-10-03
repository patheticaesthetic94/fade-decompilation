package org.fadeport.fade;

import android.app.Activity;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowInsets;
import android.view.WindowInsetsController;
import android.view.WindowManager;
import android.webkit.JavascriptInterface;

/**
 * The web player's Pocket PC Home (Classic / Remastered, language, screen filter, saves, Walkthrough,
 * Help) full screen. Choosing an edition starts the native game in its own process (GameActivity);
 * its Home button comes back here.
 */
public final class HomeActivity extends Activity {
    static final String EXTRA_LCD = "lcd", EXTRA_FS = "fs";
    private PlayerWeb web;

    @Override
    protected void onCreate(Bundle state) {
        super.onCreate(state);
        web = new PlayerWeb(this, new Bridge());
        web.view.setBackgroundColor(0xff000000);
        setContentView(web.view);
        immersive(this);   // after setContentView: the insets controller needs the decor view
        // Returning from a game keeps its screen filter and fullscreen/device choice.
        Uri.Builder url = Uri.parse(Assets.ORIGIN).buildUpon();
        Intent in = getIntent();
        if (in.hasExtra(EXTRA_LCD)) url.appendQueryParameter("lcd", in.getStringExtra(EXTRA_LCD));
        if (in.hasExtra(EXTRA_FS)) url.appendQueryParameter("fs", in.getStringExtra(EXTRA_FS));
        if (state != null) web.view.restoreState(state);
        else web.view.loadUrl(url.build().toString());
    }

    static void immersive(Activity activity) {
        Window window = activity.getWindow();
        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        if (Build.VERSION.SDK_INT >= 28)
            window.getAttributes().layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        if (Build.VERSION.SDK_INT >= 30) {
            window.setDecorFitsSystemWindows(false);
            WindowInsetsController c = window.getInsetsController();
            if (c != null) {
                c.hide(WindowInsets.Type.systemBars());
                c.setSystemBarsBehavior(WindowInsetsController.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE);
            }
        } else {
            window.getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                    | View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                    | View.SYSTEM_UI_FLAG_LAYOUT_STABLE | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                    | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION);
        }
    }

    static void openExternal(Activity from, Uri uri) {
        try {
            from.startActivity(new Intent(Intent.ACTION_VIEW, uri));
        } catch (ActivityNotFoundException ignored) {
        }
    }

    @Override
    public void onWindowFocusChanged(boolean focus) {
        super.onWindowFocusChanged(focus);
        if (focus) immersive(this);
    }

    @Override
    public void onBackPressed() {
        web.back(this::finish);
    }

    @Override
    protected void onSaveInstanceState(Bundle out) {
        super.onSaveInstanceState(out);
        web.view.saveState(out);
    }

    @Override
    protected void onPause() {
        web.view.onPause();
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        web.view.onResume();
    }

    @Override
    protected void onDestroy() {
        web.view.destroy();
        super.onDestroy();
    }

    @Override
    protected void onActivityResult(int request, int result, Intent data) {
        if (!web.onActivityResult(request, result, data)) super.onActivityResult(request, result, data);
    }

    /** Called from android/shim.js. */
    private final class Bridge {
        @JavascriptInterface
        public void play(String edition, String lang, boolean lcd, boolean fullscreen) {
            runOnUiThread(() -> {
                startActivity(new Intent(HomeActivity.this, GameActivity.class)
                        .putExtra(GameActivity.EXTRA_EDITION, "remastered".equals(edition) ? "remastered" : "classic")
                        .putExtra(GameActivity.EXTRA_LANG, "fr".equals(lang) ? "fr" : "en")
                        .putExtra(EXTRA_LCD, lcd ? "1" : "0")
                        .putExtra(EXTRA_FS, fullscreen ? "1" : "0"));
                overridePendingTransition(0, 0);
                finish();
            });
        }

        @JavascriptInterface
        public String readSaves() {
            return Saves.read(HomeActivity.this);
        }

        @JavascriptInterface
        public boolean replaceSaves(String json) {
            return Saves.replace(HomeActivity.this, json);
        }

        @JavascriptInterface
        public void saveFile(String name, String text) {
            web.saveFile(name, text);
        }
    }
}
