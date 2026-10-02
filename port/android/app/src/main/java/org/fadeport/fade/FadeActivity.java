package org.fadeport.fade;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Process;
import android.system.ErrnoException;
import android.system.Os;
import org.libsdl.app.SDLActivity;

/** The recovered game runtime supports one session per process. */
public final class FadeActivity extends SDLActivity {
    /** Set once the native game has been started in this process (see LauncherActivity). */
    static boolean started;

    @Override
    protected void onCreate(Bundle state) {
        started = true;
        // The launcher's choice, read by the native runtime (SDL_getenv) before it loads any media.
        // Kept in preferences so a process Android recreates from Recents resumes the same edition.
        SharedPreferences prefs = getSharedPreferences("launcher", MODE_PRIVATE);
        try {
            Os.setenv("FADE_EDITION", prefs.getString("edition", "classic"), true);
            Os.setenv("FADE_LCD", prefs.getBoolean("lcd", false) ? "1" : "0", true);
        } catch (ErrnoException e) {
            throw new IllegalStateException(e);
        }
        super.onCreate(state);
    }

    @Override
    protected void onDestroy() {
        // SDL stops and joins the native game thread before releasing its glue.
        super.onDestroy();
        // Returning from SDL_main leaves the fixed-address PE image, low heap,
        // stack and native static state alive. A new activity must get a fresh
        // process rather than run the game's startup over those old mappings.
        Process.killProcess(Process.myPid());
    }
}
