package org.fadeport.fade;

import android.content.Intent;
import android.graphics.Color;
import android.graphics.Rect;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Process;
import android.system.ErrnoException;
import android.system.Os;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.webkit.JavascriptInterface;
import android.webkit.WebView;
import android.widget.RelativeLayout;
import org.libsdl.app.SDLActivity;

/**
 * The native game (SDL surface) inside the web player's page. The page is a transparent WebView
 * over the surface: android/shim.js cuts a hole where the player's screen is and reports that
 * rectangle, and the surface is laid out exactly under it. Touches inside it go to the game unless
 * a Walkthrough, Help, balloon or loading screen covers it; the device and dock buttons send keys.
 * Runs in its own process (:game): the recovered runtime supports one session per process, so Home
 * ends the process and a new game starts a fresh one.
 */
public final class GameActivity extends SDLActivity {
    static final String EXTRA_EDITION = "edition", EXTRA_LANG = "lang";
    private PlayerWeb web;
    private final Rect screen = new Rect();
    private volatile boolean blocking = true;   // the page covers the screen (loading, Walkthrough, Help, balloon)
    private volatile boolean started;
    private boolean touchToGame, leaving;

    static native void nativeSetLcd(int on);

    @Override
    protected void onCreate(Bundle state) {
        // This process has its own WebView data; Home's is in the main process.
        if (Build.VERSION.SDK_INT >= 28) {
            try {
                WebView.setDataDirectorySuffix("game");
            } catch (IllegalStateException ignored) {
            }
        }
        Intent in = getIntent();
        String edition = in.getStringExtra(EXTRA_EDITION), lang = in.getStringExtra(EXTRA_LANG);
        String lcd = in.getStringExtra(HomeActivity.EXTRA_LCD), fs = in.getStringExtra(HomeActivity.EXTRA_FS);
        if (edition == null) edition = "classic";
        if (lang == null) lang = "en";
        try {
            // Read by the native runtime (SDL_getenv) before it loads any media.
            Os.setenv("FADE_EDITION", edition, true);
            Os.setenv("FADE_LCD", "1".equals(lcd) ? "1" : "0", true);
            Os.setenv("FADE_LANG", lang, true);
        } catch (ErrnoException e) {
            throw new IllegalStateException(e);
        }
        super.onCreate(state);
        if (mLayout == null) return;   // SDL could not load its libraries and is showing an error
        getWindow().setBackgroundDrawable(new ColorDrawable(Color.BLACK));
        web = new PlayerWeb(this, new Bridge());
        web.view.setBackgroundColor(Color.TRANSPARENT);
        mLayout.addView(web.view, new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.MATCH_PARENT));
        web.view.loadUrl(Uri.parse(Assets.ORIGIN).buildUpon().appendQueryParameter("native", edition)
                .appendQueryParameter("lang", lang).appendQueryParameter("lcd", "1".equals(lcd) ? "1" : "0")
                .appendQueryParameter("fs", "0".equals(fs) ? "0" : "1").build().toString());
    }

    /** Called by the native runtime (game thread) once it has created its window and drawn. */
    @SuppressWarnings("unused")
    public void onGameStarted() {
        started = true;
        runOnUiThread(() -> { if (web != null) web.view.evaluateJavascript("window.fadeNativeReady && fadeNativeReady()", null); });
    }

    @Override
    public void onWindowFocusChanged(boolean focus) {
        super.onWindowFocusChanged(focus);
        if (focus) HomeActivity.immersive(this);
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        int action = ev.getActionMasked();
        if (action == MotionEvent.ACTION_DOWN)
            touchToGame = !blocking && mSurface != null && screen.contains((int) ev.getX(), (int) ev.getY());
        if (!touchToGame) return super.dispatchTouchEvent(ev);
        MotionEvent local = MotionEvent.obtain(ev);
        local.offsetLocation(-screen.left, -screen.top);
        mSurface.dispatchTouchEvent(local);
        local.recycle();
        if (action == MotionEvent.ACTION_UP || action == MotionEvent.ACTION_CANCEL) touchToGame = false;
        return true;
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event) {
        int code = event.getKeyCode();
        if (code == KeyEvent.KEYCODE_BACK) {
            // As on the web: close a balloon or screen, else ask before returning Home.
            if (event.getAction() == KeyEvent.ACTION_UP && web != null) web.back(() -> {});
            return true;
        }
        if (isGameKey(code) && web != null) {
            if (blocking) return web.view.dispatchKeyEvent(event);   // the page scrolls or closes its screen
            if (event.getAction() == KeyEvent.ACTION_DOWN && event.getRepeatCount() == 0) onNativeKeyDown(code);
            else if (event.getAction() == KeyEvent.ACTION_UP) onNativeKeyUp(code);
            return true;
        }
        return super.dispatchKeyEvent(event);
    }

    private static boolean isGameKey(int code) {
        switch (code) {
            case KeyEvent.KEYCODE_DPAD_UP: case KeyEvent.KEYCODE_DPAD_DOWN: case KeyEvent.KEYCODE_DPAD_LEFT:
            case KeyEvent.KEYCODE_DPAD_RIGHT: case KeyEvent.KEYCODE_DPAD_CENTER: case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_Z: case KeyEvent.KEYCODE_X: case KeyEvent.KEYCODE_C:
                return true;
            default:
                return false;
        }
    }

    /** The page's key names (player.js sendKey) as Android key codes, which SDL maps for the game. */
    private static int keyCode(String key) {
        switch (key) {
            case "ArrowUp": return KeyEvent.KEYCODE_DPAD_UP;
            case "ArrowDown": return KeyEvent.KEYCODE_DPAD_DOWN;
            case "ArrowLeft": return KeyEvent.KEYCODE_DPAD_LEFT;
            case "ArrowRight": return KeyEvent.KEYCODE_DPAD_RIGHT;
            case "Enter": return KeyEvent.KEYCODE_ENTER;
            case "Escape": return KeyEvent.KEYCODE_ESCAPE;
            case "z": return KeyEvent.KEYCODE_Z;
            case "x": return KeyEvent.KEYCODE_X;
            case "c": return KeyEvent.KEYCODE_C;
            default: return 0;
        }
    }

    private void goHome(boolean lcd, boolean fullscreen) {
        leaving = true;
        startActivity(new Intent(this, HomeActivity.class).addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK)
                .putExtra(HomeActivity.EXTRA_LCD, lcd ? "1" : "0").putExtra(HomeActivity.EXTRA_FS, fullscreen ? "1" : "0"));
        overridePendingTransition(0, 0);
        // The fixed-address PE image, low heap and native state cannot be reused: end the process.
        Process.killProcess(Process.myPid());
    }

    @Override
    protected void onPause() {
        if (web != null) web.view.onPause();
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (web != null) web.view.onResume();
    }

    @Override
    protected void onActivityResult(int request, int result, Intent data) {
        if (web == null || !web.onActivityResult(request, result, data)) super.onActivityResult(request, result, data);
    }

    @Override
    protected void onDestroy() {
        // SDL stops and joins the native game thread before releasing its glue.
        super.onDestroy();
        // The game's own Quit returns to the edition menu, as the web player's "Back to editions" does.
        if (!leaving && isFinishing() && !isChangingConfigurations())
            startActivity(new Intent(this, HomeActivity.class).addFlags(Intent.FLAG_ACTIVITY_NEW_TASK));
        Process.killProcess(Process.myPid());
    }

    /** Called from android/shim.js. */
    private final class Bridge {
        @JavascriptInterface
        public boolean isStarted() {
            return started;
        }

        /** The player's screen in CSS pixels, and whether the page covers it. */
        @JavascriptInterface
        public void setScreen(double x, double y, double w, double h, double ratio, boolean covered) {
            Rect r = new Rect((int) Math.round(x * ratio), (int) Math.round(y * ratio),
                    (int) Math.round((x + w) * ratio), (int) Math.round((y + h) * ratio));
            runOnUiThread(() -> {
                blocking = covered;
                if (r.equals(screen) || r.width() < 2 || r.height() < 2 || mSurface == null) return;
                screen.set(r);
                RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(r.width(), r.height());
                lp.leftMargin = r.left;
                lp.topMargin = r.top;
                mSurface.setLayoutParams(lp);
            });
        }

        @JavascriptInterface
        public void key(boolean down, String key) {
            int code = keyCode(key);
            if (code == 0) return;
            if (down) onNativeKeyDown(code);
            else onNativeKeyUp(code);
        }

        @JavascriptInterface
        public void setLcd(boolean on) {
            nativeSetLcd(on ? 1 : 0);
        }

        @JavascriptInterface
        public void home(boolean lcd, boolean fullscreen) {
            runOnUiThread(() -> goHome(lcd, fullscreen));
        }

        @JavascriptInterface
        public void saveFile(String name, String text) {
            web.saveFile(name, text);
        }
    }
}
