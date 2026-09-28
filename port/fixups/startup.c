// Open the menu as soon as resources are ready, with its normal glow animation.
#include "../src/port.h"

// 00013700 LoadGameResources
// HD_WRAP LoadGameResources
void LoadGameResources(void)
{
    legacy_LoadGameResources();
    KillTimer(g_hwnd,g_animTimer);
    g_waitTapToStart=0;
    g_splashActive=0;
    g_fadeActive=0;
    g_glowActive=1;
    g_animFrame=0;
    // A failed timer already releases all animation buffers in the original.
    if(g_animTimer) {
        game_free(g_splash.pixels);
        g_splash.pixels=0;
        for(int i=0;i<6;i++) {
            game_free(g_fadeFx[i].pixels);
            g_fadeFx[i].pixels=0;
        }
        g_animTimer=SetTimer(g_hwnd,0x66,0x8c,AnimTimerProc);
    } else g_glowActive=0;
    Menu_SetActive(&g_menu,1);
    Picture_DrawDirect(&g_menu.img);
}
