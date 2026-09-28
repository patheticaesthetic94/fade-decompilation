package org.fadeport.fade;

import android.os.Process;
import org.libsdl.app.SDLActivity;

/** The recovered game runtime supports one session per process. */
public final class FadeActivity extends SDLActivity {
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
