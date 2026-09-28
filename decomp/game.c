// 00011010 GetScreen

undefined * GetScreen(void)

{
  return (undefined *)&g_screen;
}


// 00011044 StaticInit_1eedc

void StaticInit_1eedc(void)

{
  Menu_Ctor(&g_menu);
  return;
}


// 00011078 StaticInit_23b3c

void StaticInit_23b3c(void)

{
  Game_Ctor(&g_game);
  return;
}


// 000110ac Fonts_StaticInit

void Fonts_StaticInit(void)

{
  FontGlyphs_Ctor(&g_fontTextWhite);
  FontGlyphs_Ctor(&g_fontTextBlack);
  FontGlyphs_Ctor(&g_fontTextYellow);
  FontGlyphs_Ctor(&g_fontTextBlue);
  FontGlyphs_Ctor(&g_fontPopupWhite);
  FontGlyphs_Ctor(&g_fontPopupOrange);
  return;
}


// 00011108 Fonts_StaticDestroy

void Fonts_StaticDestroy(void)

{
  FontGlyphs_Dtor(&g_fontPopupOrange);
  FontGlyphs_Dtor(&g_fontPopupWhite);
  FontGlyphs_Dtor(&g_fontTextBlue);
  FontGlyphs_Dtor(&g_fontTextYellow);
  FontGlyphs_Dtor(&g_fontTextBlack);
  FontGlyphs_Dtor(&g_fontTextWhite);
  return;
}


// 00011168 StaticInit_21004

void StaticInit_21004(void)

{
  GameState_Ctor((GameState *)&g_gameState);
  return;
}


// 0001118c FatalOutOfMemory

int FatalOutOfMemory(void)

{
  CString local_8;
  
  local_8.str = g_afxEmptyString;
  CString_AssignA(&local_8,s_Error___More_memory_space_is_nee_00043464);
  MessageBoxW((HWND)0x0,local_8.str,u_Fade_00043458,0x10);
  GXCloseInput();
  GXCloseDisplay();
  crt_exit(1);
  CString_Dtor(&local_8);
  return 0;
}


// 00011210 WinMain

WPARAM WinMain(HINSTANCE param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint _Seed;
  int iVar1;
  BOOL BVar2;
  MSG MStack_28;
  
  _Seed = time(0);
  srand(_Seed);
  set_new_handler(FatalOutOfMemory);
  g_initFlag = 1;
  iVar1 = InitInstance(param_1,param_4);
  if (iVar1 == 0) {
    MStack_28.wParam = 0;
  }
  else {
    LoadGameResources();
    while (BVar2 = GetMessageW(&MStack_28,(HWND)0x0,0,0), BVar2 != 0) {
      TranslateMessage(&MStack_28);
      DispatchMessageW(&MStack_28);
    }
  }
  return MStack_28.wParam;
}


// 000112a0 RegisterFadeWindowClass

ATOM RegisterFadeWindowClass(HINSTANCE param_1,LPCWSTR param_2)

{
  ATOM AVar1;
  WNDCLASSW local_34;
  
  local_34.style = 3;
  local_34.cbClsExtra = 0;
  local_34.lpfnWndProc = WndProc;
  local_34.cbWndExtra = 0;
  local_34.hIcon = (HICON)0x0;
  local_34.hCursor = (HCURSOR)0x0;
  local_34.hInstance = param_1;
  local_34.hbrBackground = GetStockObject(4);
  local_34.lpszMenuName = (LPCWSTR)0x0;
  local_34.lpszClassName = param_2;
  AVar1 = RegisterClassW(&local_34);
  return AVar1;
}


// 000112fc InitInstance

int InitInstance(HINSTANCE param_1,int param_2)

{
  bool bVar1;
  HWND pHVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  GXDisplayProperties *pGVar6;
  GXKeyList *pGVar7;
  undefined1 *puVar8;
  WCHAR aWStack_a8 [8];
  WCHAR aWStack_98 [8];
  undefined1 auStack_88 [24];
  undefined1 auStack_70 [96];
  
  memcpy(aWStack_98,u_FADE_0004348c,10);
  memcpy(aWStack_a8,u_Fade_00043458,10);
  pHVar2 = FindWindowW(aWStack_a8,aWStack_98);
  if (pHVar2 == (HWND)0x0) {
    RegisterFadeWindowClass(param_1,aWStack_a8);
    iVar3 = GetSystemMetrics(1);
    iVar4 = GetSystemMetrics(0);
    pHVar2 = CreateWindowExW(0,aWStack_a8,aWStack_98,0x10000000,0,0,iVar4,iVar3,(HWND)0x0,(HMENU)0x0
                             ,param_1,(LPVOID)0x0);
    if (pHVar2 != (HWND)0x0) {
      ShowWindow(pHVar2,param_2);
      UpdateWindow(pHVar2);
      g_hwnd = pHVar2;
      iVar3 = GXOpenDisplay(pHVar2,1);
      if (iVar3 != 0) {
        GXOpenInput();
        puVar5 = (undefined1 *)GXGetDisplayProperties();
        iVar3 = 0x18;
        puVar8 = auStack_88;
        do {
          iVar4 = iVar3 + -1;
          *puVar8 = *puVar5;
          bVar1 = 0 < iVar3;
          puVar5 = puVar5 + 1;
          iVar3 = iVar4;
          puVar8 = puVar8 + 1;
        } while (iVar4 != 0 && bVar1);
        pGVar6 = &g_gxProps;
        iVar3 = 0x18;
        puVar5 = auStack_88;
        do {
          iVar4 = iVar3 + -1;
          *(undefined1 *)&pGVar6->cxWidth = *puVar5;
          bVar1 = 0 < iVar3;
          pGVar6 = (GXDisplayProperties *)((int)&pGVar6->cxWidth + 1);
          iVar3 = iVar4;
          puVar5 = puVar5 + 1;
        } while (iVar4 != 0 && bVar1);
        puVar5 = (undefined1 *)GXGetDefaultKeys((int)auStack_70);
        iVar3 = 0x60;
        puVar8 = auStack_70;
        do {
          iVar4 = iVar3 + -1;
          *puVar8 = *puVar5;
          bVar1 = 0 < iVar3;
          puVar5 = puVar5 + 1;
          iVar3 = iVar4;
          puVar8 = puVar8 + 1;
        } while (iVar4 != 0 && bVar1);
        pGVar7 = &g_keys;
        iVar3 = 0x60;
        puVar5 = auStack_70;
        do {
          iVar4 = iVar3 + -1;
          *(undefined1 *)&pGVar7->vkUp = *puVar5;
          bVar1 = 0 < iVar3;
          pGVar7 = (GXKeyList *)((int)&pGVar7->vkUp + 1);
          iVar3 = iVar4;
          puVar5 = puVar5 + 1;
        } while (iVar4 != 0 && bVar1);
        return 1;
      }
    }
  }
  else {
    SetForegroundWindow((HWND)((uint)pHVar2 | 1));
  }
  return 0;
}


// 000114cc Screen_Init

void Screen_Init(Screen *this,int param_2,int param_3)

{
  ushort *puVar1;
  ushort **ppuVar2;
  int iVar3;
  
  this->h = param_3;
  ppuVar2 = this->layer;
  this->w = param_2;
  iVar3 = 5;
  this->size = param_2 * param_3;
  do {
    puVar1 = (ushort *)operator_new(this->size << 1);
    iVar3 = iVar3 + -1;
    *ppuVar2 = puVar1;
    ppuVar2 = ppuVar2 + 1;
  } while (iVar3 != 0);
  return;
}


// 00011510 DrawSplashRows

void DrawSplashRows(int param_1)

{
  Screen_DrawDirectRows
            (&g_screen,g_splash.x,g_splash.y,g_splash.w,0x140,param_1,(int)g_splash.pixels);
  return;
}


// 00011554 Screen_SetPitch

void Screen_SetPitch(Screen *this,int param_2,int param_3)

{
  this->xPitch = param_2 >> 1;
  this->yPitch = param_3 >> 1;
  return;
}


// 00011568 Screen_SetPixelFormat

void Screen_SetPixelFormat(Screen *this,uint param_2)

{
  uint uVar1;
  
  if ((param_2 & 0x40) != 0) {
    this->pixFmt = 0x40;
    uVar1 = (uint)(char)g_gamma;
    g_colorKey = RGB888_To555(uVar1,uVar1,uVar1);
  }
  if ((param_2 & 0x80) != 0) {
    this->pixFmt = 0x80;
    uVar1 = (uint)(char)g_gamma;
    g_colorKey = RGB888_To565(uVar1,uVar1,uVar1);
  }
  if ((param_2 & 0x200) != 0) {
    this->pixFmt = 0x200;
    uVar1 = (uint)(char)g_gamma;
    g_colorKey = RGB888_To444(uVar1,uVar1,uVar1);
  }
  return;
}


// 000115f4 Screen_GetPixFmt

int Screen_GetPixFmt(Screen *this)

{
  return this->pixFmt;
}


// 000115fc Screen_CopyKeyed

void Screen_CopyKeyed(Screen *this,short *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = 0;
  if (this->size != 0) {
    iVar2 = param_3 - (int)param_2;
    do {
      uVar1 = uVar1 + 1;
      if (*param_2 != g_colorKey) {
        *(short *)(iVar2 + (int)param_2) = *param_2;
      }
      param_2 = param_2 + 1;
    } while (uVar1 < (uint)this->size);
  }
  return;
}


// 00011688 WndProc

LRESULT WndProc(HWND param_1,UINT param_2,WPARAM param_3,uint param_4)

{
  short sVar1;
  char cVar2;
  HWND pHVar3;
  LRESULT LVar4;
  int iVar5;
  ushort uVar6;
  tagPAINTSTRUCT tStack_50;
  
  if (param_2 < 0x10) {
    if (param_2 == 0xf) {
      BeginPaint(param_1,&tStack_50);
      pHVar3 = GetForegroundWindow();
      if (pHVar3 == param_1) {
        EndPaint(param_1,&tStack_50);
      }
    }
    else if (param_2 != 1) {
      if (param_2 == 2) {
        GXCloseInput();
        GXCloseDisplay();
        PostQuitMessage(0);
      }
      else if (param_2 != 6) {
        if (param_2 == 7) {
          GXResume();
          GameState_OnActivate((GameState *)&g_gameState);
        }
        else {
          if (param_2 != 8) goto LAB_000117b4;
          GameState_OnDeactivate((GameState *)&g_gameState);
          GXSuspend();
        }
      }
    }
  }
  else {
    sVar1 = (short)param_3;
    if (param_2 == 0x100) {
      if (sVar1 == g_keys.vkUp) {
        if (g_cheat1Keys[g_cheat1Idx] == g_keys.vkUp) {
          iVar5 = (g_cheat1Idx + 1) * 0x1000000;
          g_cheat1Idx = (char)((uint)iVar5 >> 0x18);
          if (iVar5 >> 0x18 == 8) {
            PlayEnding('\x02');
          }
        }
        else {
          g_cheat1Idx = '\0';
        }
        if (g_cheat2Keys[g_cheat2Idx] == g_keys.vkUp) {
          iVar5 = (g_cheat2Idx + 1) * 0x1000000;
          g_cheat2Idx = (char)((uint)iVar5 >> 0x18);
          if (iVar5 >> 0x18 == 8) {
            ShowSplashThisIsNot();
          }
        }
        else {
          g_cheat2Idx = '\0';
        }
        if (g_inGame != '\0') {
          Game_OnKeyUp(&g_game);
        }
      }
      else if (sVar1 == g_keys.vkDown) {
        if (g_cheat1Keys[g_cheat1Idx] == g_keys.vkDown) {
          iVar5 = (g_cheat1Idx + 1) * 0x1000000;
          g_cheat1Idx = (char)((uint)iVar5 >> 0x18);
          if (iVar5 >> 0x18 == 8) {
            PlayEnding('\x02');
          }
        }
        else {
          g_cheat1Idx = '\0';
        }
        if (g_cheat2Keys[g_cheat2Idx] == g_keys.vkDown) {
          iVar5 = (g_cheat2Idx + 1) * 0x1000000;
          g_cheat2Idx = (char)((uint)iVar5 >> 0x18);
          if (iVar5 >> 0x18 == 8) {
            ShowSplashThisIsNot();
          }
        }
        else {
          g_cheat2Idx = '\0';
        }
        if (g_inGame != '\0') {
          Game_OnKeyDown(&g_game);
        }
      }
      else {
        if (sVar1 == g_keys.vkLeft) {
          uVar6 = g_keys.vkLeft;
          if ((g_cheat1Keys[g_cheat1Idx] == g_keys.vkLeft) &&
             (iVar5 = (g_cheat1Idx + 1) * 0x1000000, g_cheat1Idx = (char)((uint)iVar5 >> 0x18),
             iVar5 >> 0x18 == 8)) {
            PlayEnding('\x02');
            uVar6 = g_keys.vkLeft;
          }
        }
        else {
          if (sVar1 != g_keys.vkRight) {
            return 0;
          }
          uVar6 = g_keys.vkRight;
          if ((g_cheat1Keys[g_cheat1Idx] == g_keys.vkRight) &&
             (iVar5 = (g_cheat1Idx + 1) * 0x1000000, g_cheat1Idx = (char)((uint)iVar5 >> 0x18),
             iVar5 >> 0x18 == 8)) {
            PlayEnding('\x02');
            uVar6 = g_keys.vkRight;
          }
        }
        if (g_cheat2Keys[g_cheat2Idx] == uVar6) {
          iVar5 = (g_cheat2Idx + 1) * 0x1000000;
          g_cheat2Idx = (char)((uint)iVar5 >> 0x18);
          if (iVar5 >> 0x18 == 8) {
            ShowSplashThisIsNot();
          }
        }
        else {
          g_cheat2Idx = '\0';
        }
      }
    }
    else if (param_2 != 0x113) {
      if (param_2 == 0x201) {
        if (g_inGame != '\0') {
          iVar5 = Game_HitTest(&g_game,param_4 & 0xffff,param_4 >> 0x10);
          Game_OnTap((Game *)param_1,iVar5);
        }
        cVar2 = Menu_IsActive(&g_menu);
        if (cVar2 == '\x01') {
          Menu_OnTapDown(&g_menu,(ushort)param_4,param_4 >> 0x10);
        }
        if (g_waitTapToStart != 0) {
          g_waitTapToStart = 0;
          Menu_SetActive(&g_menu,1);
          g_splashActive = 0;
          g_glowActive = 1;
          KillTimer(g_hwnd,g_animTimer);
          g_animTimer = SetTimer(g_hwnd,0x66,0x8c,AnimTimerProc);
          free(g_splash.pixels);
          iVar5 = 0;
          do {
            free(g_fadeFx[iVar5].pixels);
            iVar5 = (iVar5 + 1) * 0x1000000 >> 0x18;
          } while (iVar5 < 6);
          Picture_DrawDirect(&g_menu.img);
        }
      }
      else if (param_2 == 0x202) {
        cVar2 = Menu_IsActive(&g_menu);
        if (cVar2 == '\x01') {
          iVar5 = Menu_HitTest(&g_menu,param_4 & 0xffff,param_4 >> 0x10);
          Menu_OnSelect((Menu *)param_1,iVar5);
        }
      }
      else {
        if (param_2 != 0x400) {
LAB_000117b4:
          LVar4 = DefWindowProcW(param_1,param_2,param_3,param_4);
          return LVar4;
        }
        if (sVar1 == 1) {
          Game_OnUserMsg1(&g_game);
        }
        else if (sVar1 == 2) {
          g_inGame = '\0';
          g_gameFinished = 1;
          Menu_SetState(&g_menu,2);
          PlayEnding('\x01');
          Reg_SaveTilipTip();
        }
        else if (sVar1 == 3) {
          Game_OnUserMsg3(&g_game,(int)(char)param_4);
        }
      }
    }
  }
  return 0;
}


// 00011c58 AnimTimerProc

void AnimTimerProc(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  if ((g_splashActive != 0) && (g_initFlag == '\0')) {
    DrawSplashRows(g_splashRow);
    iVar3 = g_splashRow + 1;
    uVar4 = g_splashRow + 0x141;
    g_splashRow = iVar3;
    if ((uint)g_splash.h < uVar4) {
      g_splashActive = 0;
      g_fadeActive = 1;
      KillTimer(g_hwnd,g_animTimer);
      g_animTimer = SetTimer(g_hwnd,0x66,0x8c,AnimTimerProc);
    }
  }
  if (g_fadeActive == 0) {
    iVar3 = (int)g_animFrame;
  }
  else {
    iVar3 = (int)g_animFrame;
    Screen_DrawDirect(&g_screen,g_fadeFx[iVar3].x,g_fadeFx[iVar3].y,g_fadeFx[iVar3].w,
                      g_fadeFx[iVar3].h,g_fadeFx[iVar3].pixels);
    iVar2 = ((int)g_glowDir + (int)g_animFrame) * 0x1000000;
    iVar3 = iVar2 >> 0x18;
    g_animFrame = (char)((uint)iVar2 >> 0x18);
    if (iVar3 == 6) {
      g_fadeActive = 0;
      iVar3 = 0;
      g_glowActive = 1;
      g_animFrame = '\0';
    }
  }
  if (g_glowActive != 0) {
    cVar1 = (char)iVar3;
    Screen_DrawDirect(&g_screen,g_glowFx[cVar1].x,g_glowFx[cVar1].y,g_glowFx[cVar1].w,
                      g_glowFx[cVar1].h,g_glowFx[cVar1].pixels);
    iVar3 = ((int)g_glowDir + (int)g_animFrame) * 0x1000000;
    g_animFrame = (char)((uint)iVar3 >> 0x18);
    if (iVar3 >> 0x18 == 6) {
      g_glowDir = -1;
      g_animFrame = '\x05';
    }
    if (g_animFrame == -1) {
      g_glowDir = '\x01';
      g_animFrame = '\x01';
    }
  }
  return;
}


// 00011e40 Screen_Compose

void Screen_Compose(Screen *this)

{
  memcpy(this->layer[0],this->layer[3],this->size << 1);
  Screen_CopyKeyed(this,(short *)this->layer[2],(int)this->layer[0]);
  Screen_CopyKeyed(this,(short *)this->layer[1],(int)this->layer[0]);
  return;
}


// 00011e80 Screen_ComposeRows

void Screen_ComposeRows(Screen *this,int param_2)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  
  memcpy(this->layer[0],this->layer[3],this->size << 1);
  puVar2 = this->layer[1];
  iVar1 = this->w * param_2;
  if (iVar1 != 0) {
    iVar3 = (int)this->layer[0] - (int)puVar2;
    do {
      iVar1 = iVar1 + -1;
      if (*puVar2 != g_colorKey) {
        *(ushort *)(iVar3 + (int)puVar2) = *puVar2;
      }
      puVar2 = puVar2 + 1;
    } while (iVar1 != 0);
  }
  return;
}


// 00011eb8 Screen_Present

void Screen_Present(Screen *this)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort *puVar5;
  uint uVar6;
  
  puVar2 = GXBeginDraw();
  Screen_Compose(this);
  uVar6 = 0;
  puVar5 = this->layer[0];
  if (this->h != 0) {
    do {
      uVar4 = 0;
      puVar3 = puVar2;
      if (this->w != 0) {
        do {
          uVar1 = *puVar5;
          uVar4 = uVar4 + 1;
          puVar5 = puVar5 + 1;
          *puVar3 = uVar1;
          puVar3 = puVar3 + this->xPitch;
        } while (uVar4 < (uint)this->w);
      }
      uVar6 = uVar6 + 1;
      puVar2 = puVar2 + this->yPitch;
    } while (uVar6 < (uint)this->h);
  }
  GXEndDraw();
  return;
}


// 00011f5c Screen_PresentRows

void Screen_PresentRows(Screen *this,int param_2)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort *puVar5;
  
  puVar2 = GXBeginDraw();
  Screen_ComposeRows(this,param_2);
  puVar5 = this->layer[0];
  for (; param_2 != 0; param_2 = param_2 + -1) {
    uVar4 = 0;
    puVar3 = puVar2;
    if (this->w != 0) {
      do {
        uVar1 = *puVar5;
        uVar4 = uVar4 + 1;
        puVar5 = puVar5 + 1;
        *puVar3 = uVar1;
        puVar3 = puVar3 + this->xPitch;
      } while (uVar4 < (uint)this->w);
    }
    puVar2 = puVar2 + this->yPitch;
  }
  GXEndDraw();
  return;
}


// 00011ff8 Screen_PresentLayer

void Screen_PresentLayer(Screen *this,char param_2)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort *puVar5;
  uint uVar6;
  
  puVar2 = GXBeginDraw();
  puVar5 = this->layer[param_2];
  uVar6 = 0;
  if (this->h != 0) {
    do {
      uVar4 = 0;
      puVar3 = puVar2;
      if (this->w != 0) {
        do {
          uVar1 = *puVar5;
          uVar4 = uVar4 + 1;
          puVar5 = puVar5 + 1;
          *puVar3 = uVar1;
          puVar3 = puVar3 + this->xPitch;
        } while (uVar4 < (uint)this->w);
      }
      uVar6 = uVar6 + 1;
      puVar2 = puVar2 + this->yPitch;
    } while (uVar6 < (uint)this->h);
  }
  GXEndDraw();
  return;
}


// 000120a0 Screen_PresentRect

void Screen_PresentRect(Screen *this,int param_2,int param_3,int param_4,int param_5,char param_6)

{
  int iVar1;
  ushort *puVar2;
  ushort *puVar3;
  void *pvVar4;
  ushort *puVar5;
  ushort *puVar6;
  
  pvVar4 = GXBeginDraw();
  puVar6 = this->layer[param_6] + this->w * param_3 + param_2;
  puVar5 = (ushort *)((int)pvVar4 + (this->xPitch * param_2 + this->yPitch * param_3) * 2);
  for (; iVar1 = param_4, puVar2 = puVar5, puVar3 = puVar6, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *puVar3;
      puVar2 = puVar2 + this->xPitch;
      puVar3 = puVar3 + 1;
    }
    puVar5 = puVar5 + this->yPitch;
    puVar6 = puVar6 + this->w;
  }
  GXEndDraw();
  return;
}


// 00012174 Screen_FillLayer

void Screen_FillLayer(Screen *this,ushort param_2,char param_3)

{
  ushort *puVar1;
  uint uVar2;
  
  puVar1 = this->layer[param_3];
  uVar2 = 0;
  if (this->size != 0) {
    do {
      *puVar1 = param_2;
      uVar2 = uVar2 + 1;
      puVar1 = puVar1 + 1;
    } while (uVar2 < (uint)this->size);
  }
  return;
}


// 000121b4 Screen_FillAll

void Screen_FillAll(Screen *this,ushort param_2)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    Screen_FillLayer(this,param_2,(char)iVar1);
    iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
  } while (iVar1 < 5);
  return;
}


// 000121f0 Screen_BlitToLayer

void Screen_BlitToLayer(Screen *this,int param_2,int param_3,int param_4,int param_5,ushort *param_6
                       ,char param_7)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  
  iVar4 = this->w;
  puVar3 = this->layer[param_7] + iVar4 * param_3 + param_2;
  for (; iVar2 = param_4, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *param_6;
      param_6 = param_6 + 1;
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
    }
    puVar3 = puVar3 + (iVar4 - param_4 & 0xffff);
  }
  return;
}


// 00012274 Screen_BlitToLayerStride

void Screen_BlitToLayerStride
               (Screen *this,int param_2,int param_3,uint param_4,int param_5,uint param_6,
               ushort *param_7,char param_8)

{
  ushort uVar1;
  uint uVar2;
  ushort *puVar3;
  int iVar4;
  uint uVar5;
  uint unaff_r7;
  
  uVar5 = param_4;
  if (param_6 < param_4) {
    unaff_r7 = param_4 - param_6 & 0xffff;
    uVar5 = param_6;
  }
  iVar4 = this->w;
  if (param_4 <= param_6) {
    unaff_r7 = 0;
  }
  puVar3 = this->layer[param_8] + iVar4 * param_3 + param_2;
  for (; uVar2 = uVar5, param_5 != 0; param_5 = param_5 + -1) {
    for (; uVar2 != 0; uVar2 = uVar2 - 1) {
      uVar1 = *param_7;
      param_7 = param_7 + 1;
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
    }
    puVar3 = puVar3 + (iVar4 - uVar5 & 0xffff);
    param_7 = param_7 + (unaff_r7 & 0xffff);
  }
  return;
}


// 00012318 Screen_BlitDownscaled

void Screen_BlitDownscaled
               (Screen *this,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
               ushort *param_6,char param_7,char param_8)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  ushort *puVar7;
  
  uVar6 = (uint)param_8;
  iVar3 = __rt_udiv(uVar6,param_4);
  uVar4 = this->w;
  puVar7 = this->layer[param_7] + uVar4 * param_3 + param_2;
  for (iVar5 = __rt_udiv(uVar6,param_5); iVar2 = iVar3, iVar5 != 0; iVar5 = iVar5 + -1) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *param_6;
      param_6 = param_6 + uVar6;
      *puVar7 = uVar1;
      puVar7 = puVar7 + 1;
    }
    puVar7 = puVar7 + (uVar4 - iVar3 & 0xffff);
    param_6 = param_6 + (((uVar6 & 0xffff) - 1) * (uVar4 & 0xffff) & 0xffff);
  }
  return;
}


// 00012400 Menu_OnSelect

void Menu_OnSelect(Menu *this,int param_2)

{
  ushort uVar1;
  uint uVar2;
  CString CVar3;
  CString CVar4;
  CString CVar5;
  CString CVar6;
  CString CVar7;
  CString CVar8;
  CString CVar9;
  CString CVar10;
  CString CVar11;
  CString CVar12;
  CString CVar13;
  CString CVar14;
  CString CStack_64;
  CString CStack_60;
  CString CStack_5c;
  CString CStack_58;
  CString CStack_54;
  CString CStack_50;
  CString CStack_4c;
  CString CStack_48;
  CString CStack_44;
  CString CStack_40;
  CString local_3c;
  CString local_38;
  CString local_34;
  CString local_30;
  CString local_2c;
  CString local_28;
  CString local_24;
  CString local_20;
  CString local_1c;
  CString local_18;
  CString local_14;
  CString local_10;
  
  if (param_2 == 1) {
    Menu_SetActive(&g_menu,0);
    g_inGame = 1;
    KillTimer(g_hwnd,g_animTimer);
    Menu_SetState(&g_menu,1);
    CString_CtorA(&CStack_40,s_menu_CONTINUE_SELECT4_jpg_00043500);
    CString_Plus(&local_24,&g_installDir,&CStack_40);
    CString_CtorA(&CStack_44,s_menu_CONTINUE_SELECT3_jpg_000434e4);
    CString_Plus(&local_20,&g_installDir,&CStack_44);
    CString_CtorA(&CStack_48,s_menu_CONTINUE_SELECT2_jpg_000434c8);
    CString_Plus(&local_1c,&g_installDir,&CStack_48);
    CString_CtorA(&CStack_4c,s_menu_CONTINUE_SELECT1_jpg_000434ac);
    CString_Plus(&local_18,&g_installDir,&CStack_4c);
    CString_CtorW(&local_14,(wchar_t *)&g_emptyW);
    CString_CtorA(&CStack_50,s_menu_Continue_jpg_00043498);
    CString_Plus(&local_10,&g_installDir,&CStack_50);
    CVar14.str._1_1_ = local_24.str._1_1_;
    CVar14.str._0_1_ = local_24.str._0_1_;
    CVar14.str._2_1_ = local_24.str._2_1_;
    CVar14.str._3_1_ = local_24.str._3_1_;
    CVar12.str._1_1_ = local_20.str._1_1_;
    CVar12.str._0_1_ = local_20.str._0_1_;
    CVar12.str._2_1_ = local_20.str._2_1_;
    CVar12.str._3_1_ = local_20.str._3_1_;
    CVar10.str._1_1_ = local_1c.str._1_1_;
    CVar10.str._0_1_ = local_1c.str._0_1_;
    CVar10.str._2_1_ = local_1c.str._2_1_;
    CVar10.str._3_1_ = local_1c.str._3_1_;
    CVar8.str._1_1_ = local_18.str._1_1_;
    CVar8.str._0_1_ = local_18.str._0_1_;
    CVar8.str._2_1_ = local_18.str._2_1_;
    CVar8.str._3_1_ = local_18.str._3_1_;
    CVar6.str._1_1_ = local_14.str._1_1_;
    CVar6.str._0_1_ = local_14.str._0_1_;
    CVar6.str._2_1_ = local_14.str._2_1_;
    CVar6.str._3_1_ = local_14.str._3_1_;
    CVar4.str._1_1_ = local_10.str._1_1_;
    CVar4.str._0_1_ = local_10.str._0_1_;
    CVar4.str._2_1_ = local_10.str._2_1_;
    CVar4.str._3_1_ = local_10.str._3_1_;
    Menu_AddButton(&g_menu,0,0,0x43,0xae,CVar4,CVar6,CVar8,CVar10,CVar12,CVar14,'\x01',2);
    CString_Dtor(&CStack_50);
    CString_Dtor(&CStack_4c);
    CString_Dtor(&CStack_48);
    CString_Dtor(&CStack_44);
    CString_Dtor(&CStack_40);
    GameState_NewGame((GameState *)&g_gameState);
    Menu_SetButtonState(&g_menu,4,1);
    GameState_SetCurScene((GameState *)&g_gameState,1);
LAB_000129f4:
    uVar1 = GameState_GetCurScene((GameState *)&g_gameState);
    Game_LoadScene(&g_game,(uint)uVar1);
    Game_Redraw(&g_game);
    Game_SceneIntro(&g_game);
  }
  else {
    if (param_2 == 2) {
      Menu_SetActive(&g_menu,0);
      g_inGame = 1;
      KillTimer(g_hwnd,g_animTimer);
      Screen_Present(&g_screen);
      return;
    }
    if (param_2 == 3) {
      LoadSaveSlot((int)&g_menu);
      uVar2 = SaveLoadMenu(&g_menu,'\x01');
      if (((char)uVar2 != '\0') &&
         (uVar2 = ReadSaveFile((GameState *)&g_gameState,uVar2,&g_screen), (uVar2 & 0xff) != 0)) {
        Menu_SetActive(&g_menu,0);
        g_inGame = 1;
        KillTimer(g_hwnd,g_animTimer);
        uVar2 = Menu_HasButton(&g_menu,1);
        if ((uVar2 & 0xff) != 0) {
          Menu_SetState(&g_menu,1);
          CString_CtorA(&CStack_54,s_menu_CONTINUE_SELECT4_jpg_00043500);
          CString_Plus(&local_3c,&g_installDir,&CStack_54);
          CString_CtorA(&CStack_58,s_menu_CONTINUE_SELECT3_jpg_000434e4);
          CString_Plus(&local_38,&g_installDir,&CStack_58);
          CString_CtorA(&CStack_5c,s_menu_CONTINUE_SELECT2_jpg_000434c8);
          CString_Plus(&local_34,&g_installDir,&CStack_5c);
          CString_CtorA(&CStack_60,s_menu_CONTINUE_SELECT1_jpg_000434ac);
          CString_Plus(&local_30,&g_installDir,&CStack_60);
          CString_CtorW(&local_2c,(wchar_t *)&g_emptyW);
          CString_CtorA(&CStack_64,s_menu_Continue_jpg_00043498);
          CString_Plus(&local_28,&g_installDir,&CStack_64);
          CVar13.str._1_1_ = local_3c.str._1_1_;
          CVar13.str._0_1_ = local_3c.str._0_1_;
          CVar13.str._2_1_ = local_3c.str._2_1_;
          CVar13.str._3_1_ = local_3c.str._3_1_;
          CVar11.str._1_1_ = local_38.str._1_1_;
          CVar11.str._0_1_ = local_38.str._0_1_;
          CVar11.str._2_1_ = local_38.str._2_1_;
          CVar11.str._3_1_ = local_38.str._3_1_;
          CVar9.str._1_1_ = local_34.str._1_1_;
          CVar9.str._0_1_ = local_34.str._0_1_;
          CVar9.str._2_1_ = local_34.str._2_1_;
          CVar9.str._3_1_ = local_34.str._3_1_;
          CVar7.str._1_1_ = local_30.str._1_1_;
          CVar7.str._0_1_ = local_30.str._0_1_;
          CVar7.str._2_1_ = local_30.str._2_1_;
          CVar7.str._3_1_ = local_30.str._3_1_;
          CVar5.str._1_1_ = local_2c.str._1_1_;
          CVar5.str._0_1_ = local_2c.str._0_1_;
          CVar5.str._2_1_ = local_2c.str._2_1_;
          CVar5.str._3_1_ = local_2c.str._3_1_;
          CVar3.str._1_1_ = local_28.str._1_1_;
          CVar3.str._0_1_ = local_28.str._0_1_;
          CVar3.str._2_1_ = local_28.str._2_1_;
          CVar3.str._3_1_ = local_28.str._3_1_;
          Menu_AddButton(&g_menu,0,0,0x43,0xae,CVar3,CVar5,CVar7,CVar9,CVar11,CVar13,'\x01',2);
          CString_Dtor(&CStack_64);
          CString_Dtor(&CStack_60);
          CString_Dtor(&CStack_5c);
          CString_Dtor(&CStack_58);
          CString_Dtor(&CStack_54);
          Menu_SetButtonState(&g_menu,4,1);
        }
        FlushInputMessages();
        sndPlaySoundW((LPCWSTR)0x0,0);
        goto LAB_000129f4;
      }
    }
    else {
      if (param_2 != 4) {
        if (param_2 == 5) {
          sndPlaySoundW((LPCWSTR)0x0,0);
          SendMessageW((HWND)this,0x10,0,0);
          return;
        }
        if (param_2 != 6) {
          return;
        }
        KillTimer(g_hwnd,g_animTimer);
        ShowCredits(&g_menu);
        g_animTimer = SetTimer(g_hwnd,0x66,0x5a,AnimTimerProc);
        return;
      }
      LoadSaveSlot((int)&g_menu);
      uVar2 = SaveLoadMenu(&g_menu,'\0');
      if ((char)uVar2 != '\0') {
        WriteSaveFile((GameState *)&g_gameState,uVar2,&g_screen);
      }
    }
    Picture_DrawDirect(&g_menu.img);
  }
  return;
}


// 00012a24 Screen_DrawDirect

void Screen_DrawDirect(Screen *this,int param_2,int param_3,int param_4,int param_5,ushort *param_6)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  void *pvVar4;
  ushort *puVar5;
  
  pvVar4 = GXBeginDraw();
  puVar5 = (ushort *)((int)pvVar4 + (this->xPitch * param_2 + this->yPitch * param_3) * 2);
  for (; iVar2 = param_4, puVar3 = puVar5, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *param_6;
      param_6 = param_6 + 1;
      *puVar3 = uVar1;
      puVar3 = puVar3 + this->xPitch;
    }
    puVar5 = puVar5 + this->yPitch;
  }
  GXEndDraw();
  return;
}


// 00012ad4 Screen_DrawDirectStride

void Screen_DrawDirectStride
               (Screen *this,int param_2,int param_3,uint param_4,int param_5,uint param_6,
               ushort *param_7)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  void *pvVar4;
  ushort *puVar5;
  uint unaff_r9;
  
  pvVar4 = GXBeginDraw();
  if (param_6 < param_4) {
    unaff_r9 = param_4 - param_6 & 0xffff;
  }
  if (param_4 <= param_6) {
    unaff_r9 = 0;
  }
  if (param_4 <= param_6) {
    param_6 = param_4;
  }
  puVar5 = (ushort *)((int)pvVar4 + (this->xPitch * param_2 + this->yPitch * param_3) * 2);
  for (; puVar2 = puVar5, uVar3 = param_6, param_5 != 0; param_5 = param_5 + -1) {
    for (; uVar3 != 0; uVar3 = uVar3 - 1) {
      uVar1 = *param_7;
      param_7 = param_7 + 1;
      *puVar2 = uVar1;
      puVar2 = puVar2 + this->xPitch;
    }
    puVar5 = puVar5 + this->yPitch;
    param_7 = param_7 + (unaff_r9 & 0xffff);
  }
  GXEndDraw();
  return;
}


// 00012ba4 Screen_DrawDirectRows

void Screen_DrawDirectRows
               (Screen *this,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
               )

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *puVar3;
  void *pvVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  
  pvVar4 = GXBeginDraw();
  puVar5 = (undefined2 *)(param_7 + param_4 * param_6 * 2);
  puVar6 = (undefined2 *)((int)pvVar4 + (this->xPitch * param_2 + this->yPitch * param_3) * 2);
  for (; iVar2 = param_4, puVar3 = puVar6, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *puVar5;
      puVar5 = puVar5 + 1;
      *puVar3 = uVar1;
      puVar3 = puVar3 + this->xPitch;
    }
    puVar6 = puVar6 + this->yPitch;
  }
  GXEndDraw();
  return;
}


// 00012c64 Screen_BlitRowsToLayer

void Screen_BlitRowsToLayer
               (Screen *this,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
               ,char param_8)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  ushort *puVar5;
  
  iVar4 = this->w;
  puVar5 = (ushort *)(param_7 + param_4 * param_6 * 2);
  puVar3 = this->layer[param_8] + iVar4 * param_3 + param_2;
  for (; iVar2 = param_4, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *puVar5;
      puVar5 = puVar5 + 1;
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
    }
    puVar3 = puVar3 + (iVar4 - param_4 & 0xffff);
  }
  return;
}


// 00012cf8 Screen_BlitMaskedToLayer

void Screen_BlitMaskedToLayer
               (Screen *this,int param_2,int param_3,int param_4,int param_5,short *param_6,
               short *param_7,char param_8)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  
  iVar3 = this->w;
  puVar2 = this->layer[param_8] + iVar3 * param_3 + param_2;
  for (; iVar1 = param_4, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      if (*param_7 != g_colorKey) {
        if (*param_6 == g_colorKey) {
          *puVar2 = g_colorKey + 1;
        }
        else {
          *puVar2 = *param_6;
        }
      }
      param_7 = param_7 + 1;
      puVar2 = puVar2 + 1;
      param_6 = param_6 + 1;
    }
    puVar2 = puVar2 + (iVar3 - param_4 & 0xffff);
  }
  return;
}


// 00012da4 Screen_ReadLayer

void Screen_ReadLayer(Screen *this,int param_2,int param_3,int param_4,int param_5,ushort *param_6,
                     char param_7)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  
  iVar4 = this->w;
  puVar3 = this->layer[param_7] + iVar4 * param_3 + param_2;
  for (; iVar2 = param_4, param_5 != 0; param_5 = param_5 + -1) {
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      uVar1 = *puVar3;
      puVar3 = puVar3 + 1;
      *param_6 = uVar1;
      param_6 = param_6 + 1;
    }
    puVar3 = puVar3 + (iVar4 - param_4 & 0xffff);
  }
  return;
}


// 00012e28 Font_IsMarkerPixel

undefined4
Font_IsMarkerPixel(Screen *param_1,int param_2,int param_3,int param_4,undefined4 param_5,
                  int param_6)

{
  int iVar1;
  ushort *puVar2;
  bool bVar3;
  byte local_8;
  byte local_7;
  byte local_6 [2];
  
  iVar1 = param_1->pixFmt;
  puVar2 = (ushort *)(param_6 + (param_3 * param_4 + param_2) * 2);
  if (iVar1 == 0x40) {
    RGB555_Split((uint)*puVar2,&local_8,&local_7,local_6);
    if ((char)g_gamma == 0) {
LAB_00012f48:
      if (local_8 != 0x1f) {
        return 0;
      }
      bVar3 = local_7 == 0;
    }
    else {
      if (local_8 != 0x1f) {
        return 0;
      }
      bVar3 = (uint)local_7 == (int)(char)g_gamma >> 3;
    }
  }
  else {
    if (iVar1 != 0x80) {
      if (iVar1 != 0x200) {
        return 1;
      }
      RGB444_Split((uint)*puVar2,&local_8,&local_7,local_6);
      if ((char)g_gamma == 0) {
        if (local_8 != 0xf) {
          return 0;
        }
        bVar3 = local_7 == 0;
      }
      else {
        if (local_8 != 0xf) {
          return 0;
        }
        bVar3 = (uint)local_7 == (int)(char)g_gamma >> 4;
      }
      if (!bVar3) {
        return 0;
      }
      bVar3 = local_6[0] == 0xf;
      goto LAB_00012f64;
    }
    RGB565_Split((uint)*puVar2,&local_8,&local_7,local_6);
    if ((char)g_gamma == 0) goto LAB_00012f48;
    if (local_8 != 0x1f) {
      return 0;
    }
    bVar3 = (uint)local_7 == (int)(char)g_gamma >> 2;
  }
  if (!bVar3) {
    return 0;
  }
  bVar3 = local_6[0] == 0x1f;
LAB_00012f64:
  if (!bVar3) {
    return 0;
  }
  return 1;
}


// 00012f7c Game_OnTap

void Game_OnTap(Game *this,int param_2)

{
  if (param_2 == 1) {
    Menu_SetActive(&g_menu,1);
    g_inGame = 0;
    Picture_DrawDirect(&g_menu.img);
    g_animTimer = SetTimer(g_hwnd,0x66,0x8c,AnimTimerProc);
  }
  else if (param_2 == 2) {
    Game_OpenInventory(&g_game);
  }
  else if (param_2 == 3) {
    OpenBook((undefined4 *)&g_game);
  }
  else if (param_2 == 4) {
    Game_ExitMenu(&g_game);
  }
  else if (param_2 == 5) {
    Game_OnKeyUp(&g_game);
  }
  else if (param_2 == 6) {
    Game_OnKeyDown(&g_game);
  }
  return;
}


// 00013048 Screen_BlitKeyedToLayer

void Screen_BlitKeyedToLayer
               (Screen *this,int param_2,int param_3,int param_4,int param_5,short *param_6,
               char param_7)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  int iVar4;
  
  iVar4 = this->w;
  puVar3 = this->layer[param_7] + iVar4 * param_3 + param_2;
  for (; iVar2 = param_4, param_5 != 0; param_5 = param_5 + -1) {
    while (iVar2 != 0) {
      uVar1 = *param_6;
      param_6 = param_6 + 1;
      if (uVar1 != g_colorKey) {
        *puVar3 = uVar1;
      }
      puVar3 = puVar3 + 1;
      iVar2 = iVar2 + -1;
    }
    puVar3 = puVar3 + (iVar4 - param_4 & 0xffff);
  }
  return;
}


// 000130d8 DrawLoadingProgress

void DrawLoadingProgress(char param_1)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined8 uVar8;
  CString local_28;
  CString CStack_24;
  
  local_28.str = g_afxEmptyString;
  uVar8 = __itod((int)param_1);
  __muld((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),0xe76c8b44,0x400aa9fb);
  cVar1 = __dtoi();
  if (cVar1 < 0x65) {
    CString_AssignA(&local_28,s_Loading____00043520);
    CString_AssignA(&local_28,&g_emptyA);
    cVar2 = __rt_sdiv(10,(int)cVar1);
    CString_AppendChar(&local_28,(short)(char)(cVar2 + '0'));
    CString_AppendChar(&local_28,(short)(char)(cVar1 + cVar2 * -10 + '0'));
    CString_CtorA(&CStack_24,s_space);
    CString_Append(&local_28,&CStack_24);
    CString_Dtor(&CStack_24);
  }
  else {
    cVar1 = 'd';
    CString_AssignA(&local_28,s_Loading____100_00043530);
    CString_AssignA(&local_28,s_100_0004352c);
  }
  iVar5 = g_progressBar.w;
  uVar4 = __rt_udiv(100,cVar1 * g_progressBar.w);
  uVar6 = 0xf0U - iVar5 >> 1;
  uVar7 = 0x140U - g_progressBar.h >> 1;
  Screen_BlitToLayer(&g_screen,uVar6,uVar7,iVar5,g_progressBar.h,g_progressBar.pixels,'\x01');
  Screen_DrawDirectStride
            (&g_screen,uVar6,uVar7,g_progressFill.w,g_progressFill.h,uVar4,g_progressFill.pixels);
  Screen_BlitToLayerStride
            (&g_screen,uVar6,uVar7,g_progressFill.w,g_progressFill.h,uVar4,g_progressFill.pixels,
             '\x01');
  uVar6 = 0xcd;
  uVar7 = (0x140U - g_progressBar.h >> 1) + 0x59;
  iVar5 = 0;
  while( true ) {
    iVar5 = (int)(char)iVar5;
    if (*(int *)(local_28.str + -4) <= iVar5) break;
    Glyph_DrawDirect(g_fontTextWhite.glyphs + (ushort)local_28.str[iVar5],uVar6,uVar7);
    Glyph_BlitToLayer(g_fontTextWhite.glyphs + (ushort)local_28.str[iVar5],'\x01',uVar6,uVar7);
    bVar3 = Glyph_GetW(g_fontTextWhite.glyphs + (ushort)local_28.str[iVar5]);
    uVar6 = bVar3 + uVar6;
    iVar5 = (iVar5 + 1) * 0x1000000 >> 0x18;
  }
  CString_Dtor(&local_28);
  return;
}


// 000133b0 Screen_DrawKeyedDirect

void Screen_DrawKeyedDirect
               (Screen *this,uint param_2,uint param_3,int param_4,int param_5,short *param_6)

{
  ushort uVar1;
  void *pvVar2;
  ushort *puVar3;
  int iVar4;
  int iVar5;
  ushort *puVar6;
  
  pvVar2 = GXBeginDraw();
  puVar6 = (ushort *)((int)pvVar2 + (this->xPitch * param_2 + this->yPitch * param_3) * 2);
  if (param_3 < param_3 + param_5) {
    iVar5 = (param_3 + param_5) - param_3;
    do {
      if (param_2 < param_2 + param_4) {
        iVar4 = (param_2 + param_4) - param_2;
        puVar3 = puVar6;
        do {
          uVar1 = *param_6;
          iVar4 = iVar4 + -1;
          param_6 = param_6 + 1;
          if (uVar1 != g_colorKey) {
            *puVar3 = uVar1;
          }
          puVar3 = puVar3 + this->xPitch;
        } while (iVar4 != 0);
      }
      iVar5 = iVar5 + -1;
      puVar6 = puVar6 + this->yPitch;
    } while (iVar5 != 0);
  }
  GXEndDraw();
  return;
}


// 00013478 FadeIn565

void FadeIn565(int param_1,uint param_2,uint param_3,int param_4,int param_5,char param_6)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  byte local_34;
  byte local_33;
  byte local_32 [2];
  uint local_30;
  
  iVar2 = *(int *)(param_1 + 4);
  uVar4 = param_3 + param_5;
  uVar7 = param_2 + param_4;
  local_30 = uVar4;
  if (iVar2 == 0x40) {
    iVar2 = 6;
    do {
      if (param_3 < uVar4) {
        uVar6 = param_3;
        do {
          puVar3 = (ushort *)
                   (*(int *)(param_1 + param_6 * 4 + 0x1c) +
                   (*(int *)(param_1 + 8) * uVar6 + param_2) * 2);
          if (param_2 < uVar7) {
            iVar5 = uVar7 - param_2;
            do {
              RGB555_Split((uint)*puVar3,&local_34,&local_33,local_32);
              local_34 = local_34 >> 1;
              local_33 = local_33 >> 1;
              local_32[0] = local_32[0] >> 1;
              uVar1 = RGB555_Pack((uint)local_34,(uint)local_33,(uint)local_32[0]);
              iVar5 = iVar5 + -1;
              *puVar3 = uVar1;
              puVar3 = puVar3 + 1;
              uVar4 = local_30;
            } while (iVar5 != 0);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar4);
      }
      Sleep(0x1e);
      Screen_PresentRows((Screen *)param_1,uVar4);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else if (iVar2 == 0x80) {
    iVar2 = 6;
    do {
      if (param_3 < uVar4) {
        uVar6 = param_3;
        do {
          puVar3 = (ushort *)
                   (*(int *)(param_1 + param_6 * 4 + 0x1c) +
                   (*(int *)(param_1 + 8) * uVar6 + param_2) * 2);
          if (param_2 < uVar7) {
            iVar5 = uVar7 - param_2;
            do {
              RGB565_Split((uint)*puVar3,&local_34,&local_33,local_32);
              local_34 = local_34 >> 1;
              local_33 = local_33 >> 1;
              local_32[0] = local_32[0] >> 1;
              uVar1 = RGB565_Pack((uint)local_34,(uint)local_33,(uint)local_32[0]);
              iVar5 = iVar5 + -1;
              *puVar3 = uVar1;
              puVar3 = puVar3 + 1;
              uVar4 = local_30;
            } while (iVar5 != 0);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar4);
      }
      Sleep(0x1e);
      Screen_PresentRows((Screen *)param_1,uVar4);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else if (iVar2 == 0x200) {
    iVar2 = 3;
    do {
      if (param_3 < uVar4) {
        uVar6 = param_3;
        do {
          puVar3 = (ushort *)
                   (*(int *)(param_1 + param_6 * 4 + 0x1c) +
                   (*(int *)(param_1 + 8) * uVar6 + param_2) * 2);
          if (param_2 < uVar7) {
            iVar5 = uVar7 - param_2;
            do {
              RGB444_Split((uint)*puVar3,&local_34,&local_33,local_32);
              local_34 = local_34 >> 1;
              local_33 = local_33 >> 1;
              local_32[0] = local_32[0] >> 1;
              uVar1 = RGB444_Pack((uint)local_34,(uint)local_33,(uint)local_32[0]);
              iVar5 = iVar5 + -1;
              *puVar3 = uVar1;
              puVar3 = puVar3 + 1;
              uVar4 = local_30;
            } while (iVar5 != 0);
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar4);
      }
      Sleep(0x1e);
      Screen_PresentRows((Screen *)param_1,uVar4);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}


// 00013700 LoadGameResources

void LoadGameResources(void)

{
  int iVar1;
  int iVar2;
  LPDWORD lpcbData;
  LPDWORD lpType;
  wchar_t *lpData;
  LSTATUS LVar3;
  CString *pCVar4;
  CString CVar5;
  CString CVar6;
  CString CVar7;
  CString CVar8;
  CString CVar9;
  CString CVar10;
  CString CVar11;
  CString CVar12;
  CString CVar13;
  CString CVar14;
  CString CVar15;
  CString CVar16;
  CString CVar17;
  CString CVar18;
  CString CVar19;
  CString CVar20;
  CString CVar21;
  CString CVar22;
  CString CVar23;
  CString CVar24;
  CString CVar25;
  CString CVar26;
  CString CVar27;
  CString CVar28;
  CString CVar29;
  HKEY local_58;
  CString CStack_54;
  CString CStack_50;
  CString CStack_4c;
  CString CStack_48;
  CString local_44;
  CString local_40;
  CString local_3c;
  CString local_38;
  CString local_34;
  CString local_30;
  CString local_2c;
  CString local_28;
  
  iVar2 = Reg_LoadGamma();
  g_gamma._0_1_ = (undefined1)iVar2;
  Screen_SetPixelFormat(&g_screen,g_gxProps.ffFormat);
  g_pixelFormat = Screen_GetPixFmt(&g_screen);
  Screen_SetPitch(&g_screen,g_gxProps.cbxPitch,g_gxProps.cbyPitch);
  Screen_Init(&g_screen,g_gxProps.cxWidth,g_gxProps.cyHeight);
  Screen_FillAll(&g_screen,g_colorKey);
  Screen_PresentLayer(&g_screen,'\x01');
  g_gameFinished = 0;
  g_fadeActive = 0;
  g_glowActive = 0;
  g_splashActive = 1;
  g_animFrame = '\0';
  g_splashRow = 0;
  g_animTimer = SetTimer(g_hwnd,0x66,0x5a,AnimTimerProc);
  if (g_animTimer == 0) {
    iVar2 = 0;
    do {
      free(g_fadeFx[iVar2].pixels);
      free(g_glowFx[iVar2].pixels);
      iVar2 = (iVar2 + 1) * 0x10000 >> 0x10;
    } while (iVar2 < 6);
    free(g_splash.pixels);
    Menu_SetActive(&g_menu,1);
    Picture_DrawDirect(&g_menu.img);
    g_splashActive = 0;
  }
  g_cheat1Keys[0] = g_keys.vkDown;
  g_cheat1Keys[1] = g_keys.vkDown;
  g_cheat1Keys[2] = g_keys.vkUp;
  g_cheat1Keys[3] = g_keys.vkLeft;
  g_cheat1Keys[4] = g_keys.vkUp;
  g_cheat1Keys[5] = g_keys.vkRight;
  g_cheat1Keys[6] = g_keys.vkDown;
  g_cheat1Keys[7] = g_keys.vkUp;
  g_cheat1Idx = 0;
  g_cheat2Keys[0] = g_keys.vkLeft;
  g_cheat2Keys[1] = g_keys.vkUp;
  g_cheat2Keys[2] = g_keys.vkLeft;
  g_cheat2Keys[3] = g_keys.vkRight;
  g_cheat2Keys[4] = g_keys.vkDown;
  g_cheat2Keys[5] = g_keys.vkDown;
  g_cheat2Keys[6] = g_keys.vkUp;
  g_cheat2Keys[7] = g_keys.vkRight;
  g_cheat2Idx = 0;
  lpcbData = (LPDWORD)operator_new(4);
  *lpcbData = 200;
  lpType = (LPDWORD)operator_new(4);
  lpData = (wchar_t *)operator_new(*lpcbData);
  RegOpenKeyExW((HKEY)0x80000002,u_SOFTWARE_Fade_00043ab8,0,0,&local_58);
  RegQueryValueExW(local_58,u_Install_Dir_00043aa0,(LPDWORD)0x0,lpType,(LPBYTE)lpData,lpcbData);
  LVar3 = RegCloseKey(local_58);
  if (LVar3 == 0) {
    CString_AssignW(&g_installDir,lpData);
    CString_CtorA(&CStack_54,s___00043a9c);
    pCVar4 = CString_Plus(&local_40,&g_installDir,&CStack_54);
    CString_Assign(&g_installDir,pCVar4);
    CString_Dtor(&local_40);
    CString_Dtor(&CStack_54);
  }
  else {
    CString_AssignA(&g_installDir,s_Program_Files_fade__00043a88);
  }
  free(lpcbData);
  free(lpType);
  CString_CtorA(&CStack_54,s_UI_progress_bar_jpg_00043a74);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  LoadImage(local_40,&g_progressBar.h,&g_progressBar.w,&g_progressBar.pixels,1);
  CString_Dtor(&CStack_54);
  CString_CtorA(&CStack_54,s_UI_progress_bar_gradient_jpg_00043a54);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  LoadImage(local_40,&g_progressFill.h,&g_progressFill.w,&g_progressFill.pixels,1);
  CString_Dtor(&CStack_54);
  Screen_PresentLayer(&g_screen,'\0');
  Screen_DrawDirect(&g_screen,0xf0U - g_progressBar.w >> 1,0x140U - g_progressBar.h >> 1,
                    g_progressBar.w,g_progressBar.h,g_progressBar.pixels);
  CString_CtorA(&CStack_54,s_fonts_FONT_TEXTE_Blanche_bmp_00043a34);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  Font_Load(&g_fontTextWhite,local_40,&g_screen,0);
  CString_Dtor(&CStack_54);
  DrawLoadingProgress('\x01');
  CString_CtorA(&CStack_54,s_fonts_FONT_TEXTE_Noir_bmp_00043a18);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  Font_Load(&g_fontTextBlack,local_40,&g_screen,0);
  CString_Dtor(&CStack_54);
  DrawLoadingProgress('\x02');
  CString_CtorA(&CStack_54,s_fonts_FONT_TEXTE_Jaune_bmp_000439fc);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  Font_Load(&g_fontTextYellow,local_40,&g_screen,0);
  CString_Dtor(&CStack_54);
  DrawLoadingProgress('\x03');
  CString_CtorA(&CStack_54,s_fonts_FONT_TEXTE_Bleu_bmp_000439e0);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  Font_Load(&g_fontTextBlue,local_40,&g_screen,0);
  CString_Dtor(&CStack_54);
  DrawLoadingProgress('\x04');
  CString_CtorA(&CStack_54,s_fonts_FONT_POPUPS_Blanche_bmp_000439c0);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  Font_Load(&g_fontPopupWhite,local_40,&g_screen,1);
  CString_Dtor(&CStack_54);
  DrawLoadingProgress('\x05');
  CString_CtorA(&CStack_54,s_fonts_FONT_POPUPS_Orange_bmp_000439a0);
  CString_Plus(&local_40,&g_installDir,&CStack_54);
  Font_Load(&g_fontPopupOrange,local_40,&g_screen,1);
  CString_Dtor(&CStack_54);
  DrawLoadingProgress('\x06');
  CString_CtorA(&CStack_50,s_menu_Menu_saveload_jpg_00043988);
  CString_Plus(&local_40,&g_installDir,&CStack_50);
  CString_CtorA(&CStack_54,s_menu_MENU_BACKGROUND_jpg_0004396c);
  CString_Plus(&local_44,&g_installDir,&CStack_54);
  ShowPopUpAller(&g_menu,0,0,local_44.str,local_40,&g_fontTextBlack,&g_fontPopupOrange,
                 &g_fontPopupWhite,&g_screen);
  CString_Dtor(&CStack_54);
  CString_Dtor(&CStack_50);
  DrawLoadingProgress('\a');
  CString_CtorA(&local_44,s_menu_NEW_GAME_SELECT4_jpg_00043950);
  CString_Plus(&local_40,&g_installDir,&local_44);
  CString_CtorA(&CStack_48,s_menu_NEW_GAME_SELECT3_jpg_00043934);
  CString_Plus(&local_3c,&g_installDir,&CStack_48);
  CString_CtorA(&CStack_4c,s_menu_NEW_GAME_SELECT2_jpg_00043918);
  CString_Plus(&local_38,&g_installDir,&CStack_4c);
  CString_CtorA(&CStack_54,s_menu_NEW_GAME_SELECT1_jpg_000438fc);
  CString_Plus(&local_34,&g_installDir,&CStack_54);
  CString_CtorW(&local_30,(wchar_t *)&g_emptyW);
  CString_CtorA(&CStack_50,s_menu_New_Game_jpg_000438e8);
  CString_Plus(&local_2c,&g_installDir,&CStack_50);
  CVar23.str._1_1_ = local_3c.str._1_1_;
  CVar23.str._0_1_ = local_3c.str._0_1_;
  CVar23.str._2_1_ = local_3c.str._2_1_;
  CVar23.str._3_1_ = local_3c.str._3_1_;
  CVar18.str._1_1_ = local_38.str._1_1_;
  CVar18.str._0_1_ = local_38.str._0_1_;
  CVar18.str._2_1_ = local_38.str._2_1_;
  CVar18.str._3_1_ = local_38.str._3_1_;
  CVar13.str._1_1_ = local_34.str._1_1_;
  CVar13.str._0_1_ = local_34.str._0_1_;
  CVar13.str._2_1_ = local_34.str._2_1_;
  CVar13.str._3_1_ = local_34.str._3_1_;
  CVar8.str._1_1_ = local_30.str._1_1_;
  CVar8.str._0_1_ = local_30.str._0_1_;
  CVar8.str._2_1_ = local_30.str._2_1_;
  CVar8.str._3_1_ = local_30.str._3_1_;
  CVar5.str._1_1_ = local_2c.str._1_1_;
  CVar5.str._0_1_ = local_2c.str._0_1_;
  CVar5.str._2_1_ = local_2c.str._2_1_;
  CVar5.str._3_1_ = local_2c.str._3_1_;
  Menu_AddButton(&g_menu,0,0,0x3e,0xb6,CVar5,CVar8,CVar13,CVar18,CVar23,local_40,'\x01',1);
  CString_Dtor(&CStack_50);
  CString_Dtor(&CStack_54);
  CString_Dtor(&CStack_4c);
  CString_Dtor(&CStack_48);
  CString_Dtor(&local_44);
  CString_CtorA(&CStack_54,s_menu_LOAD_GAME_SELECT4_jpg_000438cc);
  CString_Plus(&local_2c,&g_installDir,&CStack_54);
  CString_CtorA(&CStack_50,s_menu_LOAD_GAME_SELECT3_jpg_000438b0);
  CString_Plus(&local_30,&g_installDir,&CStack_50);
  CString_CtorA(&CStack_4c,s_menu_LOAD_GAME_SELECT2_jpg_00043894);
  CString_Plus(&local_34,&g_installDir,&CStack_4c);
  CString_CtorA(&CStack_48,s_menu_LOAD_GAME_SELECT1_jpg_00043878);
  CString_Plus(&local_38,&g_installDir,&CStack_48);
  CString_CtorW(&local_3c,(wchar_t *)&g_emptyW);
  CString_CtorA(&local_44,s_menu_Load_Game_jpg_00043864);
  CString_Plus(&local_40,&g_installDir,&local_44);
  CVar28.str._1_1_ = local_2c.str._1_1_;
  CVar28.str._0_1_ = local_2c.str._0_1_;
  CVar28.str._2_1_ = local_2c.str._2_1_;
  CVar28.str._3_1_ = local_2c.str._3_1_;
  CVar24.str._1_1_ = local_30.str._1_1_;
  CVar24.str._0_1_ = local_30.str._0_1_;
  CVar24.str._2_1_ = local_30.str._2_1_;
  CVar24.str._3_1_ = local_30.str._3_1_;
  CVar19.str._1_1_ = local_34.str._1_1_;
  CVar19.str._0_1_ = local_34.str._0_1_;
  CVar19.str._2_1_ = local_34.str._2_1_;
  CVar19.str._3_1_ = local_34.str._3_1_;
  CVar14.str._1_1_ = local_38.str._1_1_;
  CVar14.str._0_1_ = local_38.str._0_1_;
  CVar14.str._2_1_ = local_38.str._2_1_;
  CVar14.str._3_1_ = local_38.str._3_1_;
  CVar9.str._1_1_ = local_3c.str._1_1_;
  CVar9.str._0_1_ = local_3c.str._0_1_;
  CVar9.str._2_1_ = local_3c.str._2_1_;
  CVar9.str._3_1_ = local_3c.str._3_1_;
  Menu_AddButton(&g_menu,0,0x28,0x39,0xbc,local_40,CVar9,CVar14,CVar19,CVar24,CVar28,'\x01',3);
  CString_Dtor(&local_44);
  CString_Dtor(&CStack_48);
  CString_Dtor(&CStack_4c);
  CString_Dtor(&CStack_50);
  CString_Dtor(&CStack_54);
  CString_CtorA(&local_40,s_menu_SAVE_GAME_SELECT4_jpg_00043848);
  CString_Plus(&local_2c,&g_installDir,&local_40);
  CString_CtorA(&CStack_54,s_menu_SAVE_GAME_SELECT3_jpg_0004382c);
  CString_Plus(&local_30,&g_installDir,&CStack_54);
  CString_CtorA(&CStack_50,s_menu_SAVE_GAME_SELECT2_jpg_00043810);
  CString_Plus(&local_34,&g_installDir,&CStack_50);
  CString_CtorA(&CStack_4c,s_menu_SAVE_GAME_SELECT1_jpg_000437f4);
  CString_Plus(&local_38,&g_installDir,&CStack_4c);
  CString_CtorA(&CStack_48,s_menu_save_game_OFF_jpg_000437dc);
  CString_Plus(&local_3c,&g_installDir,&CStack_48);
  CString_CtorA(&local_44,s_menu_save_game_jpg_000437c8);
  CString_Plus(&local_28,&g_installDir,&local_44);
  CVar29.str._1_1_ = local_2c.str._1_1_;
  CVar29.str._0_1_ = local_2c.str._0_1_;
  CVar29.str._2_1_ = local_2c.str._2_1_;
  CVar29.str._3_1_ = local_2c.str._3_1_;
  CVar25.str._1_1_ = local_30.str._1_1_;
  CVar25.str._0_1_ = local_30.str._0_1_;
  CVar25.str._2_1_ = local_30.str._2_1_;
  CVar25.str._3_1_ = local_30.str._3_1_;
  CVar20.str._1_1_ = local_34.str._1_1_;
  CVar20.str._0_1_ = local_34.str._0_1_;
  CVar20.str._2_1_ = local_34.str._2_1_;
  CVar20.str._3_1_ = local_34.str._3_1_;
  CVar15.str._1_1_ = local_38.str._1_1_;
  CVar15.str._0_1_ = local_38.str._0_1_;
  CVar15.str._2_1_ = local_38.str._2_1_;
  CVar15.str._3_1_ = local_38.str._3_1_;
  CVar10.str._1_1_ = local_3c.str._1_1_;
  CVar10.str._0_1_ = local_3c.str._0_1_;
  CVar10.str._2_1_ = local_3c.str._2_1_;
  CVar10.str._3_1_ = local_3c.str._3_1_;
  Menu_AddButton(&g_menu,0,0x4a,0x39,0xb9,local_28,CVar10,CVar15,CVar20,CVar25,CVar29,'\x04',4);
  CString_Dtor(&local_44);
  CString_Dtor(&CStack_48);
  CString_Dtor(&CStack_4c);
  CString_Dtor(&CStack_50);
  CString_Dtor(&CStack_54);
  CString_Dtor(&local_40);
  CString_CtorA(&CStack_50,s_menu_Credit_SELECT4_jpg_000437b0);
  CString_Plus(&local_28,&g_installDir,&CStack_50);
  CString_CtorA(&CStack_4c,s_menu_Credit_SELECT3_jpg_00043798);
  CString_Plus(&local_2c,&g_installDir,&CStack_4c);
  CString_CtorA(&CStack_48,s_menu_Credit_SELECT2_jpg_00043780);
  CString_Plus(&local_30,&g_installDir,&CStack_48);
  CString_CtorA(&local_44,s_menu_Credit_SELECT1_jpg_00043768);
  CString_Plus(&local_34,&g_installDir,&local_44);
  CString_CtorW(&local_38,(wchar_t *)&g_emptyW);
  CString_CtorA(&local_40,s_menu_Credit_jpg_00043758);
  CString_Plus(&local_3c,&g_installDir,&local_40);
  CVar26.str._1_1_ = local_2c.str._1_1_;
  CVar26.str._0_1_ = local_2c.str._0_1_;
  CVar26.str._2_1_ = local_2c.str._2_1_;
  CVar26.str._3_1_ = local_2c.str._3_1_;
  CVar21.str._1_1_ = local_30.str._1_1_;
  CVar21.str._0_1_ = local_30.str._0_1_;
  CVar21.str._2_1_ = local_30.str._2_1_;
  CVar21.str._3_1_ = local_30.str._3_1_;
  CVar16.str._1_1_ = local_34.str._1_1_;
  CVar16.str._0_1_ = local_34.str._0_1_;
  CVar16.str._2_1_ = local_34.str._2_1_;
  CVar16.str._3_1_ = local_34.str._3_1_;
  CVar11.str._1_1_ = local_38.str._1_1_;
  CVar11.str._0_1_ = local_38.str._0_1_;
  CVar11.str._2_1_ = local_38.str._2_1_;
  CVar11.str._3_1_ = local_38.str._3_1_;
  CVar6.str._1_1_ = local_3c.str._1_1_;
  CVar6.str._0_1_ = local_3c.str._0_1_;
  CVar6.str._2_1_ = local_3c.str._2_1_;
  CVar6.str._3_1_ = local_3c.str._3_1_;
  Menu_AddButton(&g_menu,0,0x6e,0x49,0xaa,CVar6,CVar11,CVar16,CVar21,CVar26,local_28,'\x01',6);
  CString_Dtor(&local_40);
  CString_Dtor(&local_44);
  CString_Dtor(&CStack_48);
  CString_Dtor(&CStack_4c);
  CString_Dtor(&CStack_50);
  CString_CtorA(&CStack_50,s_menu_QUIT_SELECT4_jpg_00043740);
  CString_Plus(&local_28,&g_installDir,&CStack_50);
  CString_CtorA(&CStack_4c,s_menu_QUIT_SELECT3_jpg_00043728);
  CString_Plus(&local_2c,&g_installDir,&CStack_4c);
  CString_CtorA(&CStack_48,s_menu_QUIT_SELECT2_jpg_00043710);
  CString_Plus(&local_30,&g_installDir,&CStack_48);
  CString_CtorA(&local_44,s_menu_QUIT_SELECT1_jpg_000436f8);
  CString_Plus(&local_34,&g_installDir,&local_44);
  CString_CtorW(&local_38,(wchar_t *)&g_emptyW);
  CString_CtorA(&local_40,s_menu_quit_jpg_000436e8);
  CString_Plus(&local_3c,&g_installDir,&local_40);
  CVar27.str._1_1_ = local_2c.str._1_1_;
  CVar27.str._0_1_ = local_2c.str._0_1_;
  CVar27.str._2_1_ = local_2c.str._2_1_;
  CVar27.str._3_1_ = local_2c.str._3_1_;
  CVar22.str._1_1_ = local_30.str._1_1_;
  CVar22.str._0_1_ = local_30.str._0_1_;
  CVar22.str._2_1_ = local_30.str._2_1_;
  CVar22.str._3_1_ = local_30.str._3_1_;
  CVar17.str._1_1_ = local_34.str._1_1_;
  CVar17.str._0_1_ = local_34.str._0_1_;
  CVar17.str._2_1_ = local_34.str._2_1_;
  CVar17.str._3_1_ = local_34.str._3_1_;
  CVar12.str._1_1_ = local_38.str._1_1_;
  CVar12.str._0_1_ = local_38.str._0_1_;
  CVar12.str._2_1_ = local_38.str._2_1_;
  CVar12.str._3_1_ = local_38.str._3_1_;
  CVar7.str._1_1_ = local_3c.str._1_1_;
  CVar7.str._0_1_ = local_3c.str._0_1_;
  CVar7.str._2_1_ = local_3c.str._2_1_;
  CVar7.str._3_1_ = local_3c.str._3_1_;
  Menu_AddButton(&g_menu,0,0x94,0x5e,0x95,CVar7,CVar12,CVar17,CVar22,CVar27,local_28,'\x01',5);
  CString_Dtor(&local_40);
  CString_Dtor(&local_44);
  CString_Dtor(&CStack_48);
  CString_Dtor(&CStack_4c);
  CString_Dtor(&CStack_50);
  Menu_SetActive(&g_menu,0);
  g_waitTapToStart = 1;
  g_inGame = 0;
  DrawLoadingProgress('\b');
  LoadUIImages(&g_game,&g_screen,&g_fontTextWhite,&g_fontTextYellow,&g_fontTextBlue,
               &g_fontPopupWhite,&g_fontPopupOrange,&g_gameState);
  DrawLoadingProgress('\t');
  CString_CtorA(&local_40,s_menu_Effect_FADE1_jpg_000436d0);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_fadeFx[0].h,&g_fadeFx[0].w,&g_fadeFx[0].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\n');
  CString_CtorA(&local_40,s_menu_Effect_FADE1_jpg_000436d0);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_fadeFx[1].h,&g_fadeFx[1].w,&g_fadeFx[1].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\v');
  CString_CtorA(&local_40,s_menu_Effect_FADE2_jpg_000436b8);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_fadeFx[2].h,&g_fadeFx[2].w,&g_fadeFx[2].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\f');
  CString_CtorA(&local_40,s_menu_Effect_FADE3_jpg_000436a0);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_fadeFx[3].h,&g_fadeFx[3].w,&g_fadeFx[3].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\r');
  CString_CtorA(&local_40,s_menu_Effect_FADE4_jpg_00043688);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_fadeFx[4].h,&g_fadeFx[4].w,&g_fadeFx[4].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x0e');
  CString_CtorA(&local_40,s_menu_Effect_FADE4_jpg_00043688);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_fadeFx[5].h,&g_fadeFx[5].w,&g_fadeFx[5].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x0f');
  CString_CtorA(&local_40,s_menu_Effect_GLOW1_jpg_00043670);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_glowFx[0].h,&g_glowFx[0].w,&g_glowFx[0].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x10');
  CString_CtorA(&local_40,s_menu_Effect_GLOW2_jpg_00043658);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_glowFx[1].h,&g_glowFx[1].w,&g_glowFx[1].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x11');
  CString_CtorA(&local_40,s_menu_Effect_GLOW3_jpg_00043640);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_glowFx[2].h,&g_glowFx[2].w,&g_glowFx[2].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x12');
  CString_CtorA(&local_40,s_menu_Effect_GLOW4_jpg_00043628);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_glowFx[3].h,&g_glowFx[3].w,&g_glowFx[3].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x13');
  CString_CtorA(&local_40,s_menu_Effect_GLOW5_jpg_00043610);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_glowFx[4].h,&g_glowFx[4].w,&g_glowFx[4].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x14');
  CString_CtorA(&local_40,s_menu_Effect_GLOW6_jpg_000435f8);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_glowFx[5].h,&g_glowFx[5].w,&g_glowFx[5].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x15');
  iVar2 = 0;
  do {
    g_logos[iVar2].x = 0;
    g_logos[iVar2].y = 0;
    iVar2 = (iVar2 + 1) * 0x10000 >> 0x10;
  } while (iVar2 < 8);
  CString_CtorA(&local_40,s_Images_logo1_jpg_000435e4);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[0].h,&g_logos[0].w,&g_logos[0].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x16');
  CString_CtorA(&local_40,s_Images_logo2_jpg_000435d0);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[1].h,&g_logos[1].w,&g_logos[1].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x17');
  CString_CtorA(&local_40,s_Images_logo3_jpg_000435bc);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[2].h,&g_logos[2].w,&g_logos[2].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x18');
  CString_CtorA(&local_40,s_Images_logo4_jpg_000435a8);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[3].h,&g_logos[3].w,&g_logos[3].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x19');
  CString_CtorA(&local_40,s_Images_logo5_jpg_00043594);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[4].h,&g_logos[4].w,&g_logos[4].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x1a');
  CString_CtorA(&local_40,s_Images_logo6_jpg_00043580);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[5].h,&g_logos[5].w,&g_logos[5].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x1b');
  CString_CtorA(&local_40,s_Images_logo7_jpg_0004356c);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[4].h,&g_logos[4].w,&g_logos[4].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x1c');
  CString_CtorA(&local_40,s_Images_logo8_jpg_00043558);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_logos[5].h,&g_logos[5].w,&g_logos[5].pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x1d');
  iVar2 = 0;
  do {
    g_fadeFx[iVar2].x = 0;
    g_fadeFx[iVar2].y = 0xe3;
    g_glowFx[iVar2].x = 0;
    iVar1 = (iVar2 + 1) * 0x10000 >> 0x10;
    g_glowFx[iVar2].y = 0xe3;
    iVar2 = iVar1;
  } while (iVar1 < 6);
  CString_CtorA(&local_40,s_menu_scroll_jpg_00043548);
  CString_Plus(&local_28,&g_installDir,&local_40);
  LoadImage(local_28,&g_splash.h,&g_splash.w,&g_splash.pixels,1);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x1e');
  CString_CtorA(&local_40,s_SAVE_00043540);
  pCVar4 = CString_Plus(&local_28,&g_installDir,&local_40);
  CreateDirectoryW(pCVar4->str,(LPSECURITY_ATTRIBUTES)0x0);
  CString_Dtor(&local_28);
  CString_Dtor(&local_40);
  DrawLoadingProgress('\x1f');
  Screen_BlitRowsToLayer
            (&g_screen,g_splash.x,g_splash.y,g_splash.w,0x140,0,(int)g_splash.pixels,'\x04');
  Screen_FadeToWhite(&g_screen,0,0,0xf0,0x140,'\x01');
  Screen_FadeFromWhite(&g_screen,0,0,0xf0,0x140,'\x04','\x01');
  g_splashRow = g_splashRow + 1;
  FlushInputMessages();
  Game_DrawBackground(&g_game);
  free(g_progressFill.pixels);
  free(g_progressBar.pixels);
  g_glowActive = 0;
  g_fadeActive = 0;
  g_splashActive = 1;
  g_animFrame = '\0';
  g_splashRow = 0;
  g_animTimer = SetTimer(g_hwnd,0x66,0x5a,AnimTimerProc);
  if (g_animTimer == 0) {
    iVar2 = 0;
    do {
      free(g_fadeFx[iVar2].pixels);
      free(g_glowFx[iVar2].pixels);
      iVar2 = (iVar2 + 1) * 0x10000 >> 0x10;
    } while (iVar2 < 6);
    free(g_splash.pixels);
    Menu_SetActive(&g_menu,1);
    Picture_DrawDirect(&g_menu.img);
    g_splashActive = 0;
  }
  g_initFlag = 0;
  return;
}


// 00015090 Screen_FadeFromBlack

void Screen_FadeFromBlack
               (Screen *this,uint param_2,uint param_3,int param_4,int param_5,char param_6,
               char param_7)

{
  ushort uVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  ushort *puVar9;
  uint uVar10;
  byte local_43;
  byte local_42;
  byte local_41;
  uint local_40;
  ushort **local_3c;
  ushort **local_38;
  uint local_34;
  uint local_30;
  
  Screen_FillLayer(this,g_colorKey,param_7);
  iVar2 = this->pixFmt;
  uVar4 = param_2 + param_4;
  uVar5 = param_3 + param_5;
  bVar3 = 0;
  local_34 = uVar5;
  local_30 = uVar4;
  if (iVar2 == 0x40) {
    local_40 = 6;
    do {
      bVar3 = (char)(1 << (local_40 - 1 & 0xff)) + bVar3;
      uVar7 = local_40;
      if (param_3 < uVar5) {
        local_3c = this->layer + param_6 + -7;
        local_38 = this->layer + param_7 + -7;
        uVar10 = param_3;
        do {
          iVar2 = (this->w * uVar10 + param_2) * 2;
          puVar8 = (ushort *)((int)local_3c[7] + iVar2);
          puVar9 = (ushort *)((int)local_38[7] + iVar2);
          if (param_2 < uVar4) {
            uVar6 = (uVar7 & 0xff) - 1;
            iVar2 = uVar4 - param_2;
            do {
              RGB555_Split((uint)*puVar8,&local_43,&local_42,&local_41);
              uVar1 = RGB555_Pack((uint)(byte)((bVar3 & local_43) >> (uVar6 & 0xff)),
                                  (uint)(byte)((bVar3 & local_42) >> (uVar6 & 0xff)),
                                  (uint)(byte)((bVar3 & local_41) >> (uVar6 & 0xff)));
              iVar2 = iVar2 + -1;
              *puVar9 = uVar1;
              puVar8 = puVar8 + 1;
              puVar9 = puVar9 + 1;
              uVar4 = local_30;
              uVar5 = local_34;
              uVar7 = local_40;
            } while (iVar2 != 0);
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < uVar5);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar5);
      local_40 = uVar7 - 1;
    } while (local_40 != 0);
  }
  else if (iVar2 == 0x80) {
    local_40 = 6;
    do {
      bVar3 = (char)(1 << (local_40 - 1 & 0xff)) + bVar3;
      uVar7 = local_40;
      if (param_3 < uVar5) {
        local_3c = this->layer + param_6 + -7;
        local_38 = this->layer + param_7 + -7;
        uVar10 = param_3;
        do {
          iVar2 = (this->w * uVar10 + param_2) * 2;
          puVar8 = (ushort *)((int)local_3c[7] + iVar2);
          puVar9 = (ushort *)((int)local_38[7] + iVar2);
          if (param_2 < uVar4) {
            uVar6 = (uVar7 & 0xff) - 1;
            iVar2 = uVar4 - param_2;
            do {
              RGB565_Split((uint)*puVar8,&local_43,&local_42,&local_41);
              uVar1 = RGB565_Pack((uint)(byte)((bVar3 & local_43) >> (uVar6 & 0xff)),
                                  (uint)(byte)((bVar3 & local_42) >> (uVar6 & 0xff)),
                                  (uint)(byte)((bVar3 & local_41) >> (uVar6 & 0xff)));
              iVar2 = iVar2 + -1;
              *puVar9 = uVar1;
              puVar8 = puVar8 + 1;
              puVar9 = puVar9 + 1;
              uVar4 = local_30;
              uVar5 = local_34;
              uVar7 = local_40;
            } while (iVar2 != 0);
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < uVar5);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar5);
      local_40 = uVar7 - 1;
    } while (local_40 != 0);
  }
  else if (iVar2 == 0x200) {
    local_40 = 6;
    do {
      bVar3 = (char)(1 << (local_40 - 1 & 0xff)) + bVar3;
      uVar7 = local_40;
      if (param_3 < uVar5) {
        local_3c = this->layer + param_6 + -7;
        local_38 = this->layer + param_7 + -7;
        uVar10 = param_3;
        do {
          iVar2 = (this->w * uVar10 + param_2) * 2;
          puVar8 = (ushort *)((int)local_3c[7] + iVar2);
          puVar9 = (ushort *)((int)local_38[7] + iVar2);
          if (param_2 < uVar4) {
            uVar6 = (uVar7 & 0xff) - 1;
            iVar2 = uVar4 - param_2;
            do {
              RGB444_Split((uint)*puVar8,&local_43,&local_42,&local_41);
              uVar1 = RGB444_Pack((uint)(byte)((bVar3 & local_43) >> (uVar6 & 0xff)),
                                  (uint)(byte)((bVar3 & local_42) >> (uVar6 & 0xff)),
                                  (uint)(byte)((bVar3 & local_41) >> (uVar6 & 0xff)));
              iVar2 = iVar2 + -1;
              *puVar9 = uVar1;
              puVar8 = puVar8 + 1;
              puVar9 = puVar9 + 1;
              uVar4 = local_30;
              uVar5 = local_34;
              uVar7 = local_40;
            } while (iVar2 != 0);
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < uVar5);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar5);
      local_40 = uVar7 - 1;
    } while (local_40 != 0);
  }
  return;
}


// 000154bc Screen_FadeToWhite

void Screen_FadeToWhite(Screen *this,uint param_2,uint param_3,int param_4,int param_5,char param_6)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  byte local_34;
  byte local_33;
  byte local_32 [2];
  uint local_30;
  
  iVar2 = this->pixFmt;
  uVar8 = param_3 + param_5;
  uVar11 = param_2 + param_4;
  local_30 = uVar8;
  if (iVar2 == 0x40) {
    iVar2 = 0x20;
    do {
      if (param_3 < uVar8) {
        uVar10 = param_3;
        do {
          puVar7 = this->layer[param_6] + this->w * uVar10 + param_2;
          if (param_2 < uVar11) {
            iVar9 = uVar11 - param_2;
            do {
              RGB555_Split((uint)*puVar7,&local_34,local_32,&local_33);
              uVar3 = local_34 + 1;
              local_34 = (byte)uVar3;
              uVar8 = local_32[0] + 1;
              local_32[0] = (byte)uVar8;
              uVar4 = local_33 + 1;
              uVar5 = uVar3 & 0xff;
              local_33 = (byte)uVar4;
              if (0x1f < uVar5) {
                uVar3 = 0x1f;
              }
              uVar6 = uVar4 & 0xff;
              if (0x1f < uVar5) {
                local_34 = (byte)uVar3;
              }
              if (0x1f < uVar6) {
                uVar4 = 0x1f;
              }
              if (0x1f < uVar6) {
                local_33 = (byte)uVar4;
              }
              if (0x1f < (uVar8 & 0xff)) {
                uVar8 = 0x1f;
                local_32[0] = 0x1f;
              }
              uVar1 = RGB555_Pack(uVar3,uVar8,uVar4);
              iVar9 = iVar9 + -1;
              *puVar7 = uVar1;
              puVar7 = puVar7 + 1;
              uVar8 = local_30;
            } while (iVar9 != 0);
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < uVar8);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar8);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else if (iVar2 == 0x80) {
    iVar2 = 0x20;
    do {
      if (param_3 < uVar8) {
        uVar10 = param_3;
        do {
          puVar7 = this->layer[param_6] + this->w * uVar10 + param_2;
          if (param_2 < uVar11) {
            iVar9 = uVar11 - param_2;
            do {
              RGB565_Split((uint)*puVar7,&local_34,local_32,&local_33);
              uVar3 = local_34 + 1;
              local_34 = (byte)uVar3;
              uVar8 = local_32[0] + 2;
              local_32[0] = (byte)uVar8;
              uVar4 = local_33 + 1;
              uVar5 = uVar3 & 0xff;
              local_33 = (byte)uVar4;
              if (0x1f < uVar5) {
                uVar3 = 0x1f;
              }
              uVar6 = uVar4 & 0xff;
              if (0x1f < uVar5) {
                local_34 = (byte)uVar3;
              }
              if (0x1f < uVar6) {
                uVar4 = 0x1f;
              }
              if (0x1f < uVar6) {
                local_33 = (byte)uVar4;
              }
              if (0x3f < (uVar8 & 0xff)) {
                uVar8 = 0x3f;
                local_32[0] = 0x3f;
              }
              uVar1 = RGB565_Pack(uVar3,uVar8,uVar4);
              iVar9 = iVar9 + -1;
              *puVar7 = uVar1;
              puVar7 = puVar7 + 1;
              uVar8 = local_30;
            } while (iVar9 != 0);
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < uVar8);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar8);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else if (iVar2 == 0x200) {
    iVar2 = 0x10;
    do {
      if (param_3 < uVar8) {
        uVar10 = param_3;
        do {
          puVar7 = this->layer[param_6] + this->w * uVar10 + param_2;
          if (param_2 < uVar11) {
            iVar9 = uVar11 - param_2;
            do {
              RGB444_Split((uint)*puVar7,&local_34,local_32,&local_33);
              uVar3 = local_34 + 1;
              local_34 = (byte)uVar3;
              uVar8 = local_32[0] + 1;
              local_32[0] = (byte)uVar8;
              uVar4 = local_33 + 1;
              uVar5 = uVar3 & 0xff;
              local_33 = (byte)uVar4;
              if (0xf < uVar5) {
                uVar3 = 0xf;
              }
              uVar6 = uVar4 & 0xff;
              if (0xf < uVar5) {
                local_34 = (byte)uVar3;
              }
              if (0xf < uVar6) {
                uVar4 = 0xf;
              }
              if (0xf < uVar6) {
                local_33 = (byte)uVar4;
              }
              if (0xf < (uVar8 & 0xff)) {
                uVar8 = 0xf;
                local_32[0] = 0xf;
              }
              uVar1 = RGB444_Pack(uVar3,uVar8,uVar4);
              iVar9 = iVar9 + -1;
              *puVar7 = uVar1;
              puVar7 = puVar7 + 1;
              uVar8 = local_30;
            } while (iVar9 != 0);
          }
          uVar10 = uVar10 + 1;
        } while (uVar10 < uVar8);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar8);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}


// 000157d4 Screen_FadeFromWhite

void Screen_FadeFromWhite
               (Screen *this,uint param_2,uint param_3,int param_4,int param_5,char param_6,
               char param_7)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  ushort *puVar9;
  uint uVar10;
  ushort *puVar11;
  uint uVar12;
  bool bVar13;
  bool bVar14;
  byte local_40;
  byte local_3f;
  byte local_3e;
  byte local_3d;
  byte local_3c;
  byte local_3b [3];
  uint local_38;
  uint local_34;
  
  Screen_FillLayer(this,0xffff,param_7);
  iVar2 = this->pixFmt;
  uVar10 = param_3 + param_5;
  local_34 = param_2 + param_4;
  local_38 = uVar10;
  if (iVar2 == 0x40) {
    iVar2 = 0x20;
    do {
      if (param_3 < uVar10) {
        uVar12 = param_3;
        do {
          iVar7 = this->w * uVar12 + param_2;
          puVar11 = this->layer[param_6] + iVar7;
          puVar9 = this->layer[param_7] + iVar7;
          if (param_2 < local_34) {
            iVar7 = local_34 - param_2;
            do {
              RGB555_Split((uint)*puVar11,&local_3d,local_3b,&local_3c);
              RGB555_Split((uint)*puVar9,&local_3f,&local_40,&local_3e);
              uVar3 = (uint)local_3f;
              uVar10 = (uint)local_3e;
              uVar4 = uVar3;
              if (local_3d < uVar3) {
                uVar4 = uVar3 + 0xff & 0xff;
              }
              uVar8 = (uint)local_3c;
              if (local_3d < uVar3) {
                local_3f = (byte)uVar4;
              }
              uVar3 = uVar8;
              if (uVar8 < uVar10) {
                uVar3 = uVar10 + 0xff;
              }
              uVar5 = (uint)local_40;
              if (uVar8 < uVar10) {
                uVar10 = uVar3 & 0xff;
                local_3e = (byte)uVar3;
              }
              if (local_3b[0] < uVar5) {
                uVar3 = uVar5 + 0xff;
                uVar5 = uVar3 & 0xff;
                local_40 = (byte)uVar3;
              }
              uVar1 = RGB555_Pack(uVar4,uVar5,uVar10);
              iVar7 = iVar7 + -1;
              *puVar9 = uVar1;
              puVar11 = puVar11 + 1;
              puVar9 = puVar9 + 1;
            } while (iVar7 != 0);
          }
          uVar12 = uVar12 + 1;
          uVar10 = local_38;
        } while (uVar12 < local_38);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar10);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else if (iVar2 == 0x80) {
    iVar2 = 0x20;
    do {
      if (param_3 < uVar10) {
        uVar12 = param_3;
        do {
          iVar7 = this->w * uVar12 + param_2;
          puVar11 = this->layer[param_6] + iVar7;
          puVar9 = this->layer[param_7] + iVar7;
          if (param_2 < local_34) {
            iVar7 = local_34 - param_2;
            do {
              RGB565_Split((uint)*puVar11,&local_3d,local_3b,&local_3c);
              RGB565_Split((uint)*puVar9,&local_3f,&local_40,&local_3e);
              uVar3 = (uint)local_3f;
              uVar10 = (uint)local_3e;
              uVar8 = (uint)local_3b[0];
              uVar4 = uVar3;
              if (local_3d < uVar3) {
                uVar4 = uVar3 + 0xff & 0xff;
              }
              uVar5 = (uint)local_3c;
              if (local_3d < uVar3) {
                local_3f = (byte)uVar4;
              }
              uVar3 = uVar5;
              if (uVar5 < uVar10) {
                uVar3 = uVar10 + 0xff;
              }
              uVar6 = (uint)local_40;
              if (uVar5 < uVar10) {
                uVar10 = uVar3 & 0xff;
                local_3e = (byte)uVar3;
              }
              bVar14 = uVar8 <= uVar6;
              bVar13 = uVar6 == uVar8;
              if (bVar14 && !bVar13) {
                uVar3 = uVar6 + 0xff;
                uVar6 = uVar3 & 0xff;
                local_40 = (byte)uVar3;
                bVar14 = uVar8 <= uVar6;
                bVar13 = uVar6 == uVar8;
              }
              if (bVar14 && !bVar13) {
                uVar3 = uVar6 + 0xff;
                uVar6 = uVar3 & 0xff;
                local_40 = (byte)uVar3;
              }
              uVar1 = RGB565_Pack(uVar4,uVar6,uVar10);
              iVar7 = iVar7 + -1;
              *puVar9 = uVar1;
              puVar11 = puVar11 + 1;
              puVar9 = puVar9 + 1;
            } while (iVar7 != 0);
          }
          uVar12 = uVar12 + 1;
          uVar10 = local_38;
        } while (uVar12 < local_38);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar10);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  else if (iVar2 == 0x200) {
    iVar2 = 0x10;
    do {
      if (param_3 < uVar10) {
        uVar12 = param_3;
        do {
          iVar7 = this->w * uVar12 + param_2;
          puVar11 = this->layer[param_6] + iVar7;
          puVar9 = this->layer[param_7] + iVar7;
          if (param_2 < local_34) {
            iVar7 = local_34 - param_2;
            do {
              RGB444_Split((uint)*puVar11,&local_3d,local_3b,&local_3c);
              RGB444_Split((uint)*puVar9,&local_3f,&local_40,&local_3e);
              uVar3 = (uint)local_3f;
              uVar10 = (uint)local_3e;
              uVar4 = uVar3;
              if (local_3d < uVar3) {
                uVar4 = uVar3 + 0xff & 0xff;
              }
              uVar8 = (uint)local_3c;
              if (local_3d < uVar3) {
                local_3f = (byte)uVar4;
              }
              uVar3 = uVar8;
              if (uVar8 < uVar10) {
                uVar3 = uVar10 + 0xff;
              }
              uVar5 = (uint)local_40;
              if (uVar8 < uVar10) {
                uVar10 = uVar3 & 0xff;
                local_3e = (byte)uVar3;
              }
              if (local_3b[0] < uVar5) {
                uVar3 = uVar5 + 0xff;
                uVar5 = uVar3 & 0xff;
                local_40 = (byte)uVar3;
              }
              uVar1 = RGB444_Pack(uVar4,uVar5,uVar10);
              iVar7 = iVar7 + -1;
              *puVar9 = uVar1;
              puVar11 = puVar11 + 1;
              puVar9 = puVar9 + 1;
            } while (iVar7 != 0);
          }
          uVar12 = uVar12 + 1;
          uVar10 = local_38;
        } while (uVar12 < local_38);
      }
      Sleep(0x1e);
      Screen_PresentRows(this,uVar10);
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}


// 00015bc0 Screen_DrawShadow

void Screen_DrawShadow(Screen *this,int param_2,int param_3,int param_4,int param_5,char param_6,
                      char param_7)

{
  int iVar1;
  
  iVar1 = this->pixFmt;
  if (iVar1 == 0x40) {
    Screen_DrawShadow_Fmt40(this,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  else if (iVar1 == 0x80) {
    Screen_DrawShadow_565(this,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  else if (iVar1 == 0x200) {
    Screen_DrawShadow_444(this,param_2,param_3,param_4,param_5,param_6,param_7);
  }
  return;
}


// 00015c4c Screen_DrawShadow_444

void Screen_DrawShadow_444
               (Screen *this,int param_2,int param_3,int param_4,int param_5,char param_6,
               char param_7)

{
  ushort **ppuVar1;
  ushort **ppuVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint extraout_r3;
  int iVar11;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint extraout_r3_02;
  uint uVar12;
  uint uVar13;
  ushort *puVar14;
  ushort *puVar15;
  byte local_48;
  byte local_47;
  byte local_46 [2];
  ushort **local_44;
  ushort **local_40;
  int local_3c;
  int local_38;
  
  uVar13 = 0;
  local_44 = this->layer + param_7 + -7;
  local_40 = this->layer + param_6 + -7;
  do {
    iVar4 = this->w * (uVar13 + param_3 + param_5) + (param_2 - uVar13) + 5;
    puVar15 = (ushort *)((int)local_40[7] + iVar4 * 2);
    puVar14 = (ushort *)((int)local_44[7] + iVar4 * 2);
    iVar4 = param_4 + (uVar13 + 0x7ffffffd) * 2;
    if (iVar4 != 0) {
      uVar12 = 7 - uVar13 & 0xff;
      do {
        uVar3 = *puVar15;
        puVar15 = puVar15 + 1;
        RGB444_Split((uint)uVar3,&local_48,local_46,&local_47);
        uVar8 = (uint)local_47;
        if (uVar12 < local_48) {
          uVar5 = local_48 - uVar12;
          uVar10 = uVar12;
        }
        else {
          uVar5 = 0;
          uVar10 = extraout_r3;
        }
        local_48 = (byte)uVar5;
        if (uVar12 < uVar8) {
          uVar10 = uVar8;
        }
        if (uVar12 < uVar8) {
          uVar10 = uVar10 - uVar12;
        }
        else {
          uVar10 = 0;
        }
        local_47 = (byte)uVar10;
        if (uVar12 < local_46[0]) {
          uVar8 = local_46[0] - uVar12;
        }
        else {
          uVar8 = 0;
        }
        local_46[0] = (byte)uVar8;
        uVar3 = RGB444_Pack(uVar5,uVar8,uVar10);
        iVar4 = iVar4 + -1;
        *puVar14 = uVar3;
        puVar14 = puVar14 + 1;
      } while (iVar4 != 0);
    }
    iVar9 = (param_3 - uVar13) + 5;
    iVar4 = param_5 + (uVar13 + 0x7ffffffe) * 2;
    if (iVar4 != 0) {
      uVar12 = 6 - uVar13 & 0xff;
      do {
        iVar11 = (int)local_44[7];
        iVar6 = this->w * iVar9 + uVar13 + param_2 + param_4;
        RGB444_Split((uint)*(ushort *)((int)local_40[7] + iVar6 * 2),&local_48,local_46,&local_47);
        uVar8 = (uint)local_47;
        if (uVar12 < local_48) {
          uVar5 = local_48 - uVar12;
          uVar10 = uVar12;
        }
        else {
          uVar5 = 0;
          uVar10 = extraout_r3_00;
        }
        local_48 = (byte)uVar5;
        if (uVar12 < uVar8) {
          uVar10 = uVar8;
        }
        if (uVar12 < uVar8) {
          uVar10 = uVar10 - uVar12;
        }
        else {
          uVar10 = 0;
        }
        local_47 = (byte)uVar10;
        if (uVar12 < local_46[0]) {
          uVar8 = local_46[0] - uVar12;
        }
        else {
          uVar8 = 0;
        }
        local_46[0] = (byte)uVar8;
        uVar3 = RGB444_Pack(uVar5,uVar8,uVar10);
        iVar4 = iVar4 + -1;
        *(ushort *)(iVar11 + iVar6 * 2) = uVar3;
        iVar9 = iVar9 + 1;
      } while (iVar4 != 0);
    }
    uVar13 = uVar13 + 1 & 0xff;
  } while (uVar13 < 4);
  uVar13 = 1;
  local_38 = param_2 + param_4;
  do {
    uVar12 = 0;
    if (uVar13 != 0) {
      uVar8 = 6 - uVar13 & 0xff;
      do {
        iVar4 = this->w * ((param_3 - uVar13) + 4) + uVar12 + local_38;
        iVar9 = (int)local_44[7];
        RGB444_Split((uint)*(ushort *)((int)local_40[7] + iVar4 * 2),&local_48,local_46,&local_47);
        uVar10 = (uint)local_47;
        if (uVar8 < local_48) {
          uVar7 = local_48 - uVar8;
          uVar5 = uVar8;
        }
        else {
          uVar7 = 0;
          uVar5 = extraout_r3_01;
        }
        local_48 = (byte)uVar7;
        if (uVar8 < uVar10) {
          uVar5 = uVar10;
        }
        if (uVar8 < uVar10) {
          uVar5 = uVar5 - uVar8;
        }
        else {
          uVar5 = 0;
        }
        local_47 = (byte)uVar5;
        if (uVar8 < local_46[0]) {
          uVar10 = local_46[0] - uVar8;
        }
        else {
          uVar10 = 0;
        }
        local_46[0] = (byte)uVar10;
        uVar3 = RGB444_Pack(uVar7,uVar10,uVar5);
        uVar12 = uVar12 + 1;
        *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
      } while (uVar12 < uVar13);
    }
    uVar13 = uVar13 + 1 & 0xff;
  } while (uVar13 < 4);
  local_3c = param_3 + param_5;
  uVar13 = 1;
  do {
    if (uVar13 != 0) {
      uVar8 = 6 - uVar13 & 0xff;
      iVar4 = local_3c;
      uVar12 = uVar13;
      do {
        iVar6 = (int)local_44[7];
        iVar9 = this->w * iVar4 + (param_2 - uVar13) + 4;
        RGB444_Split((uint)*(ushort *)((int)local_40[7] + iVar9 * 2),&local_48,local_46,&local_47);
        uVar10 = (uint)local_47;
        if (uVar8 < local_48) {
          uVar7 = local_48 - uVar8;
          uVar5 = uVar8;
        }
        else {
          uVar7 = 0;
          uVar5 = extraout_r3_02;
        }
        local_48 = (byte)uVar7;
        if (uVar8 < uVar10) {
          uVar5 = uVar10;
        }
        if (uVar8 < uVar10) {
          uVar5 = uVar5 - uVar8;
        }
        else {
          uVar5 = 0;
        }
        local_47 = (byte)uVar5;
        if (uVar8 < local_46[0]) {
          uVar10 = local_46[0] - uVar8;
        }
        else {
          uVar10 = 0;
        }
        local_46[0] = (byte)uVar10;
        uVar3 = RGB444_Pack(uVar7,uVar10,uVar5);
        uVar12 = uVar12 - 1;
        *(ushort *)(iVar6 + iVar9 * 2) = uVar3;
        iVar4 = iVar4 + 1;
      } while (uVar12 != 0);
    }
    ppuVar2 = local_40;
    ppuVar1 = local_44;
    uVar13 = uVar13 + 1 & 0xff;
  } while (uVar13 < 4);
  uVar13 = 0;
  do {
    iVar4 = ((uVar13 + local_3c) * this->w - uVar13) + param_2 + 4;
    iVar9 = (int)ppuVar1[7];
    RGB444_Split((uint)*(ushort *)((int)ppuVar2[7] + iVar4 * 2),&local_48,local_46,&local_47);
    uVar8 = (uint)local_48;
    uVar10 = 5 - uVar13 & 0xff;
    uVar12 = uVar8;
    if (uVar10 < uVar8) {
      uVar12 = uVar8 - uVar10;
    }
    uVar5 = (uint)local_47;
    if (uVar8 <= uVar10) {
      uVar12 = 0;
    }
    local_48 = (byte)uVar12;
    uVar8 = uVar5;
    if (uVar10 < uVar5) {
      uVar8 = uVar5 - uVar10;
    }
    if (uVar5 <= uVar10) {
      uVar8 = 0;
    }
    local_47 = (byte)uVar8;
    if (uVar10 < local_46[0]) {
      uVar10 = local_46[0] - uVar10;
    }
    else {
      uVar10 = 0;
    }
    local_46[0] = (byte)uVar10;
    uVar3 = RGB444_Pack(uVar12,uVar10,uVar8);
    iVar6 = local_38;
    *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
    uVar13 = uVar13 + 1 & 0xff;
  } while (uVar13 < 3);
  uVar13 = 0;
  do {
    iVar4 = ((param_3 + 4) - uVar13) * this->w + uVar13 + iVar6;
    iVar9 = (int)ppuVar1[7];
    RGB444_Split((uint)*(ushort *)((int)ppuVar2[7] + iVar4 * 2),&local_48,local_46,&local_47);
    uVar8 = (uint)local_48;
    uVar10 = 5 - uVar13 & 0xff;
    uVar12 = uVar8;
    if (uVar10 < uVar8) {
      uVar12 = uVar8 - uVar10;
    }
    uVar5 = (uint)local_47;
    if (uVar8 <= uVar10) {
      uVar12 = 0;
    }
    local_48 = (byte)uVar12;
    uVar8 = uVar5;
    if (uVar10 < uVar5) {
      uVar8 = uVar5 - uVar10;
    }
    if (uVar5 <= uVar10) {
      uVar8 = 0;
    }
    local_47 = (byte)uVar8;
    if (uVar10 < local_46[0]) {
      uVar10 = local_46[0] - uVar10;
    }
    else {
      uVar10 = 0;
    }
    local_46[0] = (byte)uVar10;
    uVar3 = RGB444_Pack(uVar12,uVar10,uVar8);
    *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
    uVar13 = uVar13 + 1 & 0xff;
  } while (uVar13 < 3);
  uVar13 = 0;
  do {
    iVar4 = (uVar13 + local_3c) * this->w + uVar13 + iVar6 + -1;
    iVar9 = (int)ppuVar1[7];
    RGB444_Split((uint)*(ushort *)((int)ppuVar2[7] + iVar4 * 2),&local_48,local_46,&local_47);
    uVar8 = (uint)local_48;
    uVar10 = 5 - uVar13 & 0xff;
    uVar12 = uVar8;
    if (uVar10 < uVar8) {
      uVar12 = uVar8 - uVar10;
    }
    uVar5 = (uint)local_47;
    if (uVar8 <= uVar10) {
      uVar12 = 0;
    }
    local_48 = (byte)uVar12;
    uVar8 = uVar5;
    if (uVar10 < uVar5) {
      uVar8 = uVar5 - uVar10;
    }
    if (uVar5 <= uVar10) {
      uVar8 = 0;
    }
    local_47 = (byte)uVar8;
    if (uVar10 < local_46[0]) {
      uVar10 = local_46[0] - uVar10;
    }
    else {
      uVar10 = 0;
    }
    local_46[0] = (byte)uVar10;
    uVar3 = RGB444_Pack(uVar12,uVar10,uVar8);
    *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
    uVar13 = uVar13 + 1 & 0xff;
  } while (uVar13 < 3);
  return;
}


// 000162ac Screen_DrawShadow_Fmt40

void Screen_DrawShadow_Fmt40
               (Screen *this,int param_2,int param_3,int param_4,int param_5,char param_6,
               char param_7)

{
  ushort **ppuVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint extraout_r3;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint extraout_r3_02;
  uint uVar10;
  ushort *puVar11;
  uint uVar12;
  ushort *puVar13;
  byte local_4c;
  byte local_4b;
  byte local_4a [2];
  ushort **local_48;
  ushort **local_44;
  int local_40;
  int local_3c;
  
  uVar10 = 0;
  local_44 = this->layer + param_7 + -7;
  local_48 = this->layer + param_6 + -7;
  do {
    iVar3 = this->w * (uVar10 + param_3 + param_5) + (param_2 - uVar10) + 5;
    puVar13 = (ushort *)((int)local_48[7] + iVar3 * 2);
    puVar11 = (ushort *)((int)local_44[7] + iVar3 * 2);
    iVar3 = param_4 + (uVar10 + 0x7ffffffd) * 2;
    if (iVar3 != 0) {
      uVar12 = uVar10 * -2 + 0xe & 0xff;
      do {
        uVar2 = *puVar13;
        puVar13 = puVar13 + 1;
        RGB565_Split((uint)uVar2,local_4a,&local_4b,&local_4c);
        RGB444_Split((uint)uVar2,local_4a,&local_4b,&local_4c);
        uVar7 = (uint)local_4c;
        if (uVar12 < local_4a[0]) {
          uVar4 = local_4a[0] - uVar12;
          uVar9 = uVar12;
        }
        else {
          uVar4 = 0;
          uVar9 = extraout_r3;
        }
        local_4a[0] = (byte)uVar4;
        if (uVar12 < uVar7) {
          uVar9 = uVar7;
        }
        if (uVar12 < uVar7) {
          uVar9 = uVar9 - uVar12;
        }
        else {
          uVar9 = 0;
        }
        local_4c = (byte)uVar9;
        if (uVar12 * 2 < (uint)local_4b) {
          uVar7 = (uint)local_4b + uVar12 * -2 & 0xff;
        }
        else {
          uVar7 = 0;
        }
        local_4b = (byte)uVar7;
        uVar2 = RGB565_Pack(uVar4,uVar7,uVar9);
        *puVar11 = uVar2;
        uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
        iVar3 = iVar3 + -1;
        puVar11[1] = uVar2;
        puVar11 = puVar11 + 2;
      } while (iVar3 != 0);
    }
    iVar8 = (param_3 - uVar10) + 5;
    iVar3 = param_5 + (uVar10 + 0x7ffffffe) * 2;
    if (iVar3 != 0) {
      uVar12 = uVar10 * -2 + 0xc & 0xff;
      do {
        iVar5 = this->w * iVar8 + uVar10 + param_2 + param_4;
        puVar11 = (ushort *)((int)local_44[7] + iVar5 * 2);
        uVar7 = (uint)*(ushort *)((int)local_48[7] + iVar5 * 2);
        RGB565_Split(uVar7,local_4a,&local_4b,&local_4c);
        RGB444_Split(uVar7,local_4a,&local_4b,&local_4c);
        uVar7 = (uint)local_4c;
        if (uVar12 < local_4a[0]) {
          uVar4 = local_4a[0] - uVar12;
          uVar9 = uVar12;
        }
        else {
          uVar4 = 0;
          uVar9 = extraout_r3_00;
        }
        local_4a[0] = (byte)uVar4;
        if (uVar12 < uVar7) {
          uVar9 = uVar7;
        }
        if (uVar12 < uVar7) {
          uVar9 = uVar9 - uVar12;
        }
        else {
          uVar9 = 0;
        }
        local_4c = (byte)uVar9;
        if (uVar12 * 2 < (uint)local_4b) {
          uVar7 = (uint)local_4b + uVar12 * -2 & 0xff;
        }
        else {
          uVar7 = 0;
        }
        local_4b = (byte)uVar7;
        uVar2 = RGB565_Pack(uVar4,uVar7,uVar9);
        *puVar11 = uVar2;
        uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
        iVar3 = iVar3 + -1;
        *puVar11 = uVar2;
        iVar8 = iVar8 + 1;
      } while (iVar3 != 0);
    }
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 4);
  uVar10 = 1;
  local_3c = param_2 + param_4;
  do {
    uVar12 = 0;
    if (uVar10 != 0) {
      uVar7 = uVar10 * -2 + 0xc & 0xff;
      do {
        iVar3 = this->w * ((param_3 - uVar10) + 4) + uVar12 + param_2 + param_4;
        puVar11 = (ushort *)((int)local_44[7] + iVar3 * 2);
        uVar9 = (uint)*(ushort *)((int)local_48[7] + iVar3 * 2);
        RGB565_Split(uVar9,local_4a,&local_4b,&local_4c);
        RGB444_Split(uVar9,local_4a,&local_4b,&local_4c);
        uVar9 = (uint)local_4c;
        if (uVar7 < local_4a[0]) {
          uVar6 = local_4a[0] - uVar7;
          uVar4 = uVar7;
        }
        else {
          uVar6 = 0;
          uVar4 = extraout_r3_01;
        }
        local_4a[0] = (byte)uVar6;
        if (uVar7 < uVar9) {
          uVar4 = uVar9;
        }
        if (uVar7 < uVar9) {
          uVar4 = uVar4 - uVar7;
        }
        else {
          uVar4 = 0;
        }
        local_4c = (byte)uVar4;
        if (uVar7 * 2 < (uint)local_4b) {
          uVar9 = (uint)local_4b + uVar7 * -2 & 0xff;
        }
        else {
          uVar9 = 0;
        }
        local_4b = (byte)uVar9;
        uVar2 = RGB565_Pack(uVar6,uVar9,uVar4);
        *puVar11 = uVar2;
        uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
        uVar12 = uVar12 + 1;
        *puVar11 = uVar2;
      } while (uVar12 < uVar10);
    }
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 4);
  uVar10 = 1;
  local_40 = param_3 + param_5;
  do {
    if (uVar10 != 0) {
      uVar7 = uVar10 * -2 + 0xc & 0xff;
      iVar3 = local_40;
      uVar12 = uVar10;
      do {
        iVar8 = this->w * iVar3 + (param_2 - uVar10) + 4;
        puVar11 = (ushort *)((int)local_44[7] + iVar8 * 2);
        uVar9 = (uint)*(ushort *)((int)local_48[7] + iVar8 * 2);
        RGB565_Split(uVar9,local_4a,&local_4b,&local_4c);
        RGB444_Split(uVar9,local_4a,&local_4b,&local_4c);
        uVar9 = (uint)local_4c;
        if (uVar7 < local_4a[0]) {
          uVar6 = local_4a[0] - uVar7;
          uVar4 = uVar7;
        }
        else {
          uVar6 = 0;
          uVar4 = extraout_r3_02;
        }
        local_4a[0] = (byte)uVar6;
        if (uVar7 < uVar9) {
          uVar4 = uVar9;
        }
        if (uVar7 < uVar9) {
          uVar4 = uVar4 - uVar7;
        }
        else {
          uVar4 = 0;
        }
        local_4c = (byte)uVar4;
        if (uVar7 * 2 < (uint)local_4b) {
          uVar9 = (uint)local_4b + uVar7 * -2 & 0xff;
        }
        else {
          uVar9 = 0;
        }
        local_4b = (byte)uVar9;
        uVar2 = RGB565_Pack(uVar6,uVar9,uVar4);
        *puVar11 = uVar2;
        uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
        uVar12 = uVar12 - 1;
        *puVar11 = uVar2;
        iVar3 = iVar3 + 1;
      } while (uVar12 != 0);
    }
    ppuVar1 = local_44;
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 4);
  uVar10 = 0;
  do {
    iVar3 = ((uVar10 + local_40) * this->w - uVar10) + param_2 + 4;
    puVar11 = (ushort *)((int)ppuVar1[7] + iVar3 * 2);
    uVar12 = (uint)*(ushort *)((int)local_48[7] + iVar3 * 2);
    RGB565_Split(uVar12,local_4a,&local_4b,&local_4c);
    RGB444_Split(uVar12,local_4a,&local_4b,&local_4c);
    uVar7 = (uint)local_4a[0];
    uVar9 = uVar10 * -2 + 10 & 0xff;
    uVar12 = uVar7;
    if (uVar9 < uVar7) {
      uVar12 = uVar7 - uVar9;
    }
    uVar4 = (uint)local_4c;
    if (uVar7 <= uVar9) {
      uVar12 = 0;
    }
    local_4a[0] = (byte)uVar12;
    uVar7 = uVar4;
    if (uVar9 < uVar4) {
      uVar7 = uVar4 - uVar9;
    }
    if (uVar4 <= uVar9) {
      uVar7 = 0;
    }
    local_4c = (byte)uVar7;
    if (uVar9 * 2 < (uint)local_4b) {
      uVar9 = (uint)local_4b + uVar9 * -2 & 0xff;
    }
    else {
      uVar9 = 0;
    }
    local_4b = (byte)uVar9;
    uVar2 = RGB565_Pack(uVar12,uVar9,uVar7);
    *puVar11 = uVar2;
    uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
    iVar3 = local_3c;
    *puVar11 = uVar2;
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 3);
  uVar10 = 0;
  do {
    iVar8 = ((param_3 + 4) - uVar10) * this->w + uVar10 + iVar3;
    puVar11 = (ushort *)((int)ppuVar1[7] + iVar8 * 2);
    uVar12 = (uint)*(ushort *)((int)local_48[7] + iVar8 * 2);
    RGB565_Split(uVar12,local_4a,&local_4b,&local_4c);
    RGB444_Split(uVar12,local_4a,&local_4b,&local_4c);
    uVar7 = (uint)local_4a[0];
    uVar9 = uVar10 * -2 + 10 & 0xff;
    uVar12 = uVar7;
    if (uVar9 < uVar7) {
      uVar12 = uVar7 - uVar9;
    }
    uVar4 = (uint)local_4c;
    if (uVar7 <= uVar9) {
      uVar12 = 0;
    }
    local_4a[0] = (byte)uVar12;
    uVar7 = uVar4;
    if (uVar9 < uVar4) {
      uVar7 = uVar4 - uVar9;
    }
    if (uVar4 <= uVar9) {
      uVar7 = 0;
    }
    local_4c = (byte)uVar7;
    if (uVar9 * 2 < (uint)local_4b) {
      uVar9 = (uint)local_4b + uVar9 * -2 & 0xff;
    }
    else {
      uVar9 = 0;
    }
    local_4b = (byte)uVar9;
    uVar2 = RGB565_Pack(uVar12,uVar9,uVar7);
    *puVar11 = uVar2;
    uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
    *puVar11 = uVar2;
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 3);
  uVar10 = 0;
  do {
    iVar8 = (uVar10 + local_40) * this->w + uVar10 + iVar3 + -1;
    puVar11 = (ushort *)((int)ppuVar1[7] + iVar8 * 2);
    uVar12 = (uint)*(ushort *)((int)local_48[7] + iVar8 * 2);
    RGB565_Split(uVar12,local_4a,&local_4b,&local_4c);
    RGB444_Split(uVar12,local_4a,&local_4b,&local_4c);
    uVar7 = (uint)local_4a[0];
    uVar9 = uVar10 * -2 + 10 & 0xff;
    uVar12 = uVar7;
    if (uVar9 < uVar7) {
      uVar12 = uVar7 - uVar9;
    }
    uVar4 = (uint)local_4c;
    if (uVar7 <= uVar9) {
      uVar12 = 0;
    }
    local_4a[0] = (byte)uVar12;
    uVar7 = uVar4;
    if (uVar9 < uVar4) {
      uVar7 = uVar4 - uVar9;
    }
    if (uVar4 <= uVar9) {
      uVar7 = 0;
    }
    local_4c = (byte)uVar7;
    if (uVar9 * 2 < (uint)local_4b) {
      uVar9 = (uint)local_4b + uVar9 * -2 & 0xff;
    }
    else {
      uVar9 = 0;
    }
    local_4b = (byte)uVar9;
    uVar2 = RGB565_Pack(uVar12,uVar9,uVar7);
    *puVar11 = uVar2;
    uVar2 = RGB444_Pack((uint)local_4a[0],(uint)local_4b,(uint)local_4c);
    *puVar11 = uVar2;
    uVar10 = uVar10 + 1 & 0xff;
  } while (uVar10 < 3);
  return;
}


// 00016a84 PlayEnding

void PlayEnding(char param_1)

{
  bool bVar1;
  CString *pCVar2;
  div_t *pdVar3;
  wchar_t *pwVar4;
  HANDLE pvVar5;
  int iVar6;
  short sStack_86;
  short asStack_84 [2];
  CString local_80;
  CString CStack_7c;
  CString CStack_78;
  CString CStack_74;
  CString CStack_70;
  CString CStack_6c;
  CString CStack_68;
  CString CStack_64;
  CString local_60;
  CString local_5c;
  CString CStack_58;
  CString local_54;
  div_t dStack_50;
  int local_48;
  char local_44;
  undefined1 local_43;
  undefined1 local_42;
  undefined1 local_41;
  div_t dStack_40;
  ushort *local_38 [3];
  int local_2c;
  int local_28;
  
  local_80.str = g_afxEmptyString;
  bVar1 = false;
  g_cheat1Idx = 0;
  CString_CtorA(&CStack_7c,s__images_End_00043ae8);
  pCVar2 = CString_Plus(&local_60,&g_installDir,&CStack_7c);
  CString_Assign(&local_80,pCVar2);
  CString_Dtor(&local_60);
  CString_Dtor(&CStack_7c);
  iVar6 = (int)param_1;
  pdVar3 = div(&dStack_50,iVar6,10);
  local_48 = pdVar3->quot;
  local_44 = (char)pdVar3->rem;
  local_43 = *(undefined1 *)((int)&pdVar3->rem + 1);
  local_42 = *(undefined1 *)((int)&pdVar3->rem + 2);
  local_41 = *(undefined1 *)((int)&pdVar3->rem + 3);
  if (local_48 != 0) {
    CString_PlusChar(&CStack_78,&local_80,(short)(char)((char)(int3)pdVar3->quot + '0'));
    CString_Assign(&local_80,&CStack_78);
    CString_Dtor(&CStack_78);
  }
  CString_PlusChar(&CStack_74,&local_80,(short)(char)(local_44 + '0'));
  CString_Assign(&local_80,&CStack_74);
  CString_Dtor(&CStack_74);
  CString_CtorA(&CStack_7c,s__IFJ_00043ae0);
  CString_Append(&local_80,&CStack_7c);
  CString_Dtor(&CStack_7c);
  Screen_FillAll(&g_screen,g_colorKey);
  FadeIn565((int)&g_screen,0,0,0xf0,0x140,'\x01');
  CString_CopyCtor(&local_60,&local_80);
  LoadImage(local_60,&local_28,&local_2c,local_38,1);
  Screen_BlitToLayer(&g_screen,0,0,local_2c,local_28,local_38[0],'\x04');
  Screen_FadeFromBlack(&g_screen,0,0,0xf0,0x140,'\x04','\x01');
  free(local_38[0]);
  if (iVar6 == 1) {
    Sleep(0x9c4);
  }
  iVar6 = (iVar6 + 1) * 0x1000000 >> 0x18;
  CString_CtorA(&CStack_7c,s_images_End_00043ad4);
  pCVar2 = CString_Plus(&local_60,&g_installDir,&CStack_7c);
  CString_Assign(&local_80,pCVar2);
  CString_Dtor(&local_60);
  CString_Dtor(&CStack_7c);
  pdVar3 = div(&dStack_50,iVar6,10);
  local_48 = pdVar3->quot;
  local_44 = (char)pdVar3->rem;
  local_43 = *(undefined1 *)((int)&pdVar3->rem + 1);
  local_42 = *(undefined1 *)((int)&pdVar3->rem + 2);
  local_41 = *(undefined1 *)((int)&pdVar3->rem + 3);
  if (local_48 != 0) {
    CString_PlusChar(&CStack_70,&local_80,(short)(char)((char)(int3)pdVar3->quot + '0'));
    CString_Assign(&local_80,&CStack_70);
    CString_Dtor(&CStack_70);
  }
  CString_PlusChar(&CStack_6c,&local_80,(short)(char)(local_44 + '0'));
  CString_Assign(&local_80,&CStack_6c);
  CString_Dtor(&CStack_6c);
  CString_CtorA(&CStack_7c,s__IFJ_00043ae0);
  CString_Append(&local_80,&CStack_7c);
  CString_Dtor(&CStack_7c);
  Sleep(0x9c4);
  pwVar4 = CString_GetBuffer(&local_80,*(int *)(local_80.str + -4));
  CString_CtorW(&local_60,pwVar4);
  pCVar2 = MangleAssetPath(&CStack_7c,local_60);
  pvVar5 = CreateFileW(pCVar2->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_7c);
  if (pvVar5 == (HANDLE)0xffffffff) {
    bVar1 = true;
  }
  else {
    CloseHandle(pvVar5);
  }
  while (!bVar1) {
    FadeIn565((int)&g_screen,0,0,0xf0,0x140,'\x01');
    CString_CopyCtor(&local_5c,&local_80);
    LoadImage(local_5c,&local_28,&local_2c,local_38,1);
    Screen_BlitToLayer(&g_screen,0,0,local_2c,local_28,local_38[0],'\x04');
    Screen_FadeFromBlack(&g_screen,0,0,0xf0,0x140,'\x04','\x01');
    free(local_38[0]);
    iVar6 = (iVar6 + 1) * 0x1000000 >> 0x18;
    CString_CtorA(&CStack_7c,s_images_End_00043ad4);
    pCVar2 = CString_Plus(&CStack_58,&g_installDir,&CStack_7c);
    CString_Assign(&local_80,pCVar2);
    CString_Dtor(&CStack_58);
    CString_Dtor(&CStack_7c);
    pdVar3 = div(&dStack_40,iVar6,10);
    local_48 = pdVar3->quot;
    local_44 = (char)pdVar3->rem;
    local_43 = *(undefined1 *)((int)&pdVar3->rem + 1);
    local_42 = *(undefined1 *)((int)&pdVar3->rem + 2);
    local_41 = *(undefined1 *)((int)&pdVar3->rem + 3);
    if (local_48 != 0) {
      CString_PlusChar(&CStack_68,&local_80,(short)(char)((char)(int3)pdVar3->quot + '0'));
      CString_Assign(&local_80,&CStack_68);
      CString_Dtor(&CStack_68);
    }
    CString_PlusChar(&CStack_64,&local_80,(short)(char)(local_44 + '0'));
    CString_Assign(&local_80,&CStack_64);
    CString_Dtor(&CStack_64);
    CString_CtorA(&local_60,s__IFJ_00043ae0);
    CString_Append(&local_80,&local_60);
    CString_Dtor(&local_60);
    pwVar4 = CString_GetBuffer(&local_80,*(int *)(local_80.str + -4));
    CString_CtorW(&local_54,pwVar4);
    pCVar2 = MangleAssetPath((CString *)&dStack_50,local_54);
    pvVar5 = CreateFileW(pCVar2->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    CString_Dtor((CString *)&dStack_50);
    if (pvVar5 == (HANDLE)0xffffffff) {
      bVar1 = true;
    }
    else {
      CloseHandle(pvVar5);
    }
    FlushInputMessages();
    Sleep(0x9c4);
    if (iVar6 == 0x1d) {
      WaitForPenUp(asStack_84,&sStack_86);
    }
  }
  FlushInputMessages();
  WaitForPenUp(asStack_84,&sStack_86);
  Menu_SetActive(&g_menu,1);
  g_inGame = 0;
  Picture_DrawDirect(&g_menu.img);
  Screen_FillLayer(&g_screen,g_colorKey,'\x04');
  Game_DrawBackground(&g_game);
  Game_DrawScene(&g_game);
  CString_Dtor(&local_80);
  return;
}


// 00017158 Screen_DrawShadow_565

void Screen_DrawShadow_565
               (Screen *this,int param_2,int param_3,int param_4,int param_5,char param_6,
               char param_7)

{
  ushort **ppuVar1;
  ushort **ppuVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint extraout_r3;
  int iVar11;
  uint extraout_r3_00;
  uint extraout_r3_01;
  uint extraout_r3_02;
  uint uVar12;
  uint uVar13;
  ushort *puVar14;
  ushort *puVar15;
  byte local_48;
  byte local_47;
  byte local_46 [2];
  ushort **local_44;
  ushort **local_40;
  int local_3c;
  int local_38;
  
  local_44 = this->layer + param_7 + -7;
  uVar12 = 0;
  local_40 = this->layer + param_6 + -7;
  do {
    iVar4 = this->w * (uVar12 + param_3 + param_5) + (param_2 - uVar12) + 5;
    puVar15 = (ushort *)((int)local_40[7] + iVar4 * 2);
    puVar14 = (ushort *)((int)local_44[7] + iVar4 * 2);
    iVar4 = param_4 + (uVar12 + 0x7ffffffd) * 2;
    if (iVar4 != 0) {
      uVar13 = uVar12 * -2 + 0xe & 0xff;
      do {
        uVar3 = *puVar15;
        puVar15 = puVar15 + 1;
        RGB565_Split((uint)uVar3,&local_48,local_46,&local_47);
        uVar8 = (uint)local_47;
        if (uVar13 < local_48) {
          uVar5 = local_48 - uVar13;
          uVar10 = uVar13;
        }
        else {
          uVar5 = 0;
          uVar10 = extraout_r3;
        }
        local_48 = (byte)uVar5;
        if (uVar13 < uVar8) {
          uVar10 = uVar8;
        }
        if (uVar13 < uVar8) {
          uVar10 = uVar10 - uVar13;
        }
        else {
          uVar10 = 0;
        }
        local_47 = (byte)uVar10;
        if (uVar13 * 2 < (uint)local_46[0]) {
          uVar8 = (uint)local_46[0] + uVar13 * -2 & 0xff;
        }
        else {
          uVar8 = 0;
        }
        local_46[0] = (byte)uVar8;
        uVar3 = RGB565_Pack(uVar5,uVar8,uVar10);
        iVar4 = iVar4 + -1;
        *puVar14 = uVar3;
        puVar14 = puVar14 + 1;
      } while (iVar4 != 0);
    }
    iVar9 = (param_3 - uVar12) + 5;
    iVar4 = param_5 + (uVar12 + 0x7ffffffe) * 2;
    if (iVar4 != 0) {
      uVar13 = uVar12 * -2 + 0xc & 0xff;
      do {
        iVar11 = (int)local_44[7];
        iVar6 = this->w * iVar9 + uVar12 + param_2 + param_4;
        RGB565_Split((uint)*(ushort *)((int)local_40[7] + iVar6 * 2),&local_48,local_46,&local_47);
        uVar8 = (uint)local_47;
        if (uVar13 < local_48) {
          uVar5 = local_48 - uVar13;
          uVar10 = uVar13;
        }
        else {
          uVar5 = 0;
          uVar10 = extraout_r3_00;
        }
        local_48 = (byte)uVar5;
        if (uVar13 < uVar8) {
          uVar10 = uVar8;
        }
        if (uVar13 < uVar8) {
          uVar10 = uVar10 - uVar13;
        }
        else {
          uVar10 = 0;
        }
        local_47 = (byte)uVar10;
        if (uVar13 * 2 < (uint)local_46[0]) {
          uVar8 = (uint)local_46[0] + uVar13 * -2 & 0xff;
        }
        else {
          uVar8 = 0;
        }
        local_46[0] = (byte)uVar8;
        uVar3 = RGB565_Pack(uVar5,uVar8,uVar10);
        iVar4 = iVar4 + -1;
        *(ushort *)(iVar11 + iVar6 * 2) = uVar3;
        iVar9 = iVar9 + 1;
      } while (iVar4 != 0);
    }
    uVar12 = uVar12 + 1 & 0xff;
  } while (uVar12 < 4);
  uVar12 = 1;
  local_38 = param_2 + param_4;
  do {
    uVar13 = 0;
    if (uVar12 != 0) {
      uVar8 = uVar12 * -2 + 0xc & 0xff;
      do {
        iVar4 = this->w * ((param_3 - uVar12) + 4) + uVar13 + local_38;
        iVar9 = (int)local_44[7];
        RGB565_Split((uint)*(ushort *)((int)local_40[7] + iVar4 * 2),&local_48,local_46,&local_47);
        uVar10 = (uint)local_47;
        if (uVar8 < local_48) {
          uVar7 = local_48 - uVar8;
          uVar5 = uVar8;
        }
        else {
          uVar7 = 0;
          uVar5 = extraout_r3_01;
        }
        local_48 = (byte)uVar7;
        if (uVar8 < uVar10) {
          uVar5 = uVar10;
        }
        if (uVar8 < uVar10) {
          uVar5 = uVar5 - uVar8;
        }
        else {
          uVar5 = 0;
        }
        local_47 = (byte)uVar5;
        if (uVar8 * 2 < (uint)local_46[0]) {
          uVar10 = (uint)local_46[0] + uVar8 * -2 & 0xff;
        }
        else {
          uVar10 = 0;
        }
        local_46[0] = (byte)uVar10;
        uVar3 = RGB565_Pack(uVar7,uVar10,uVar5);
        uVar13 = uVar13 + 1;
        *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
      } while (uVar13 < uVar12);
    }
    uVar12 = uVar12 + 1 & 0xff;
  } while (uVar12 < 4);
  uVar12 = 1;
  local_3c = param_3 + param_5;
  do {
    if (uVar12 != 0) {
      uVar8 = uVar12 * -2 + 0xc & 0xff;
      iVar4 = local_3c;
      uVar13 = uVar12;
      do {
        iVar6 = (int)local_44[7];
        iVar9 = this->w * iVar4 + (param_2 - uVar12) + 4;
        RGB565_Split((uint)*(ushort *)((int)local_40[7] + iVar9 * 2),&local_48,local_46,&local_47);
        uVar10 = (uint)local_47;
        if (uVar8 < local_48) {
          uVar7 = local_48 - uVar8;
          uVar5 = uVar8;
        }
        else {
          uVar7 = 0;
          uVar5 = extraout_r3_02;
        }
        local_48 = (byte)uVar7;
        if (uVar8 < uVar10) {
          uVar5 = uVar10;
        }
        if (uVar8 < uVar10) {
          uVar5 = uVar5 - uVar8;
        }
        else {
          uVar5 = 0;
        }
        local_47 = (byte)uVar5;
        if (uVar8 * 2 < (uint)local_46[0]) {
          uVar10 = (uint)local_46[0] + uVar8 * -2 & 0xff;
        }
        else {
          uVar10 = 0;
        }
        local_46[0] = (byte)uVar10;
        uVar3 = RGB565_Pack(uVar7,uVar10,uVar5);
        uVar13 = uVar13 - 1;
        *(ushort *)(iVar6 + iVar9 * 2) = uVar3;
        iVar4 = iVar4 + 1;
      } while (uVar13 != 0);
    }
    ppuVar2 = local_40;
    ppuVar1 = local_44;
    uVar12 = uVar12 + 1 & 0xff;
  } while (uVar12 < 4);
  uVar12 = 0;
  do {
    iVar4 = ((uVar12 + local_3c) * this->w - uVar12) + param_2 + 4;
    iVar9 = (int)ppuVar1[7];
    RGB565_Split((uint)*(ushort *)((int)ppuVar2[7] + iVar4 * 2),&local_48,local_46,&local_47);
    uVar8 = (uint)local_48;
    uVar10 = uVar12 * -2 + 10 & 0xff;
    uVar13 = uVar8;
    if (uVar10 < uVar8) {
      uVar13 = uVar8 - uVar10;
    }
    uVar5 = (uint)local_47;
    if (uVar8 <= uVar10) {
      uVar13 = 0;
    }
    local_48 = (byte)uVar13;
    uVar8 = uVar5;
    if (uVar10 < uVar5) {
      uVar8 = uVar5 - uVar10;
    }
    if (uVar5 <= uVar10) {
      uVar8 = 0;
    }
    local_47 = (byte)uVar8;
    if (uVar10 * 2 < (uint)local_46[0]) {
      uVar10 = (uint)local_46[0] + uVar10 * -2 & 0xff;
    }
    else {
      uVar10 = 0;
    }
    local_46[0] = (byte)uVar10;
    uVar3 = RGB565_Pack(uVar13,uVar10,uVar8);
    iVar6 = local_38;
    *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
    uVar12 = uVar12 + 1 & 0xff;
  } while (uVar12 < 3);
  uVar12 = 0;
  do {
    iVar4 = ((param_3 + 4) - uVar12) * this->w + uVar12 + iVar6;
    iVar9 = (int)ppuVar1[7];
    RGB565_Split((uint)*(ushort *)((int)ppuVar2[7] + iVar4 * 2),&local_48,local_46,&local_47);
    uVar8 = (uint)local_48;
    uVar10 = uVar12 * -2 + 10 & 0xff;
    uVar13 = uVar8;
    if (uVar10 < uVar8) {
      uVar13 = uVar8 - uVar10;
    }
    uVar5 = (uint)local_47;
    if (uVar8 <= uVar10) {
      uVar13 = 0;
    }
    local_48 = (byte)uVar13;
    uVar8 = uVar5;
    if (uVar10 < uVar5) {
      uVar8 = uVar5 - uVar10;
    }
    if (uVar5 <= uVar10) {
      uVar8 = 0;
    }
    local_47 = (byte)uVar8;
    if (uVar10 * 2 < (uint)local_46[0]) {
      uVar10 = (uint)local_46[0] + uVar10 * -2 & 0xff;
    }
    else {
      uVar10 = 0;
    }
    local_46[0] = (byte)uVar10;
    uVar3 = RGB565_Pack(uVar13,uVar10,uVar8);
    *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
    uVar12 = uVar12 + 1 & 0xff;
  } while (uVar12 < 3);
  uVar12 = 0;
  do {
    iVar4 = (uVar12 + local_3c) * this->w + uVar12 + iVar6 + -1;
    iVar9 = (int)ppuVar1[7];
    RGB565_Split((uint)*(ushort *)((int)ppuVar2[7] + iVar4 * 2),&local_48,local_46,&local_47);
    uVar8 = (uint)local_48;
    uVar10 = uVar12 * -2 + 10 & 0xff;
    uVar13 = uVar8;
    if (uVar10 < uVar8) {
      uVar13 = uVar8 - uVar10;
    }
    uVar5 = (uint)local_47;
    if (uVar8 <= uVar10) {
      uVar13 = 0;
    }
    local_48 = (byte)uVar13;
    uVar8 = uVar5;
    if (uVar10 < uVar5) {
      uVar8 = uVar5 - uVar10;
    }
    if (uVar5 <= uVar10) {
      uVar8 = 0;
    }
    local_47 = (byte)uVar8;
    if (uVar10 * 2 < (uint)local_46[0]) {
      uVar10 = (uint)local_46[0] + uVar10 * -2 & 0xff;
    }
    else {
      uVar10 = 0;
    }
    local_46[0] = (byte)uVar10;
    uVar3 = RGB565_Pack(uVar13,uVar10,uVar8);
    *(ushort *)(iVar9 + iVar4 * 2) = uVar3;
    uVar12 = uVar12 + 1 & 0xff;
  } while (uVar12 < 3);
  return;
}


// 000177e0 Reg_SaveTilipTip

void Reg_SaveTilipTip(void)

{
  void *_Memory;
  BYTE *lpData;
  HKEY local_10;
  
  _Memory = (void *)operator_new(4);
  lpData = (BYTE *)operator_new(4);
  *lpData = 'M';
  RegOpenKeyExW((HKEY)0x80000002,u_SOFTWARE_Fade_00043ab8,0,0,&local_10);
  RegSetValueExW(local_10,u_TilipTip_00043af4,0,4,lpData,4);
  RegCloseKey(local_10);
  free(_Memory);
  free(lpData);
  return;
}


// 00017870 Reg_LoadTilipTip

bool Reg_LoadTilipTip(void)

{
  LPDWORD lpcbData;
  LPDWORD lpType;
  LPBYTE lpData;
  LSTATUS LVar1;
  bool bVar2;
  HKEY local_14;
  
  lpcbData = (LPDWORD)operator_new(4);
  *lpcbData = 100;
  lpType = (LPDWORD)operator_new(4);
  lpData = (LPBYTE)operator_new(*lpcbData);
  RegOpenKeyExW((HKEY)0x80000002,u_SOFTWARE_Fade_00043ab8,0,0,&local_14);
  RegQueryValueExW(local_14,u_TilipTip_00043af4,(LPDWORD)0x0,lpType,lpData,lpcbData);
  LVar1 = RegCloseKey(local_14);
  if (LVar1 == 0) {
    bVar2 = *lpData == 'M';
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}


// 0001791c Reg_LoadGamma

int Reg_LoadGamma(void)

{
  LPDWORD lpcbData;
  LPDWORD lpType;
  LPBYTE lpData;
  LSTATUS LVar1;
  int iVar2;
  HKEY local_14;
  
  lpcbData = (LPDWORD)operator_new(4);
  *lpcbData = 4;
  lpType = (LPDWORD)operator_new(4);
  lpData = (LPBYTE)operator_new(*lpcbData);
  RegOpenKeyExW((HKEY)0x80000002,u_SOFTWARE_Fade_00043ab8,0,0,&local_14);
  LVar1 = RegQueryValueExW(local_14,u_Gamma_00043b08,(LPDWORD)0x0,lpType,lpData,lpcbData);
  RegCloseKey(local_14);
  if (LVar1 == 0) {
    iVar2 = (int)(char)*lpData;
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}


// 000179b4 RGB565_Split

void RGB565_Split(uint param_1,byte *param_2,byte *param_3,byte *param_4)

{
  *param_2 = (byte)((param_1 & 0xffff) >> 0xb);
  *param_3 = (byte)((param_1 & 0xffff) >> 5) & 0x3f;
  *param_4 = (byte)param_1 & 0x1f;
  return;
}


// 000179f0 ShowSplashThisIsNot

void ShowSplashThisIsNot(void)

{
  bool bVar1;
  char cVar2;
  short sStack_34;
  short sStack_32;
  CString CStack_30;
  CString local_2c [2];
  ushort *local_24 [3];
  int local_18;
  int local_14;
  
  g_cheat2Idx = 0;
  bVar1 = Reg_LoadTilipTip();
  if (bVar1) {
    cVar2 = Menu_IsActive(&g_menu);
    if (cVar2 != '\0') {
      KillTimer(g_hwnd,g_animTimer);
    }
    CString_CtorA(&CStack_30,s_images_thisisnot_jpg_00043b14);
    CString_Plus(local_2c,&g_installDir,&CStack_30);
    LoadImage(local_2c[0],&local_14,&local_18,local_24,1);
    CString_Dtor(&CStack_30);
    Screen_DrawDirect(&g_screen,0,0,local_18,local_14,local_24[0]);
    WaitForPenUp(&sStack_32,&sStack_34);
    free(local_24[0]);
  }
  cVar2 = Menu_IsActive(&g_menu);
  if (cVar2 == '\0') {
    if (g_inGame != '\0') {
      Game_Redraw(&g_game);
    }
  }
  else {
    Picture_DrawDirect(&g_menu.img);
    g_animTimer = SetTimer(g_hwnd,0x66,0x5a,AnimTimerProc);
  }
  return;
}


// 00017b24 RGB555_Split

void RGB555_Split(uint param_1,byte *param_2,byte *param_3,byte *param_4)

{
  *param_2 = (byte)((param_1 & 0xffff) >> 10);
  *param_3 = (byte)((param_1 & 0xffff) >> 5) & 0x1f;
  *param_4 = (byte)param_1 & 0x1f;
  return;
}


// 00017b60 RGB444_Split

void RGB444_Split(uint param_1,byte *param_2,byte *param_3,byte *param_4)

{
  *param_2 = (byte)(param_1 >> 8);
  *param_3 = (byte)((param_1 & 0xffff) >> 4) & 0xf;
  *param_4 = (byte)param_1 & 0xf;
  return;
}


// 00017b9c RGB565_Pack

ushort RGB565_Pack(uint param_1,uint param_2,uint param_3)

{
  return (ushort)param_3 & 0x1f | (ushort)((param_2 & 0x3f | (param_1 & 0x1f) << 6) << 5);
}


// 00017bc8 RGB555_Pack

ushort RGB555_Pack(uint param_1,uint param_2,uint param_3)

{
  return (ushort)param_3 & 0x1f | (ushort)((param_2 & 0x1f | (param_1 & 0x1f) << 5) << 5);
}


// 00017bf4 RGB444_Pack

ushort RGB444_Pack(uint param_1,uint param_2,uint param_3)

{
  return (ushort)param_3 & 0xf | (ushort)((param_2 & 0xf | (param_1 & 0xf) << 4) << 4);
}


// 00017c20 RGB888_To565

ushort RGB888_To565(uint param_1,uint param_2,uint param_3)

{
  ushort uVar1;
  
  uVar1 = RGB565_Pack((param_1 & 0xff) >> 3,(param_2 & 0xff) >> 2,(param_3 & 0xff) >> 3);
  return uVar1;
}


// 00017c3c RGB888_To555

ushort RGB888_To555(uint param_1,uint param_2,uint param_3)

{
  ushort uVar1;
  
  uVar1 = RGB555_Pack((param_1 & 0xff) >> 3,(param_2 & 0xff) >> 3,(param_3 & 0xff) >> 3);
  return uVar1;
}


// 00017c58 RGB888_To444

ushort RGB888_To444(uint param_1,uint param_2,uint param_3)

{
  ushort uVar1;
  
  uVar1 = RGB444_Pack((param_1 & 0xff) >> 4,(param_2 & 0xff) >> 4,(param_3 & 0xff) >> 4);
  return uVar1;
}


// 00017c74 MangleAssetPath

CString * MangleAssetPath(CString *param_1,CString param_2)

{
  wchar_t wVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  CString local_34;
  CString local_30;
  CString local_2c;
  CString local_28;
  CString local_c [3];
  
  local_34.str = g_afxEmptyString;
  iVar6 = (int)(char)param_2.str[-4];
  local_c[0].str = param_2.str;
  if (iVar6 < 3) {
    CString_CtorA(param_1,&g_emptyA);
    goto LAB_00017ec4;
  }
  CString_AssignChar(&local_34,param_2.str[iVar6 + -3]);
  CString_AppendChar(&local_34,local_c[0].str[iVar6 + -2]);
  CString_AppendChar(&local_34,local_c[0].str[iVar6 + -1]);
  CString_MakeUpper(&local_34);
  CString_CtorA(&local_30,s_BMP_00043b40);
  iVar4 = wcscmp(local_34.str,local_30.str);
  CString_Dtor(&local_30);
  if (iVar4 == 0) {
    pcVar5 = s_IFB_00043b3c;
LAB_00017da4:
    CString_AssignA(&local_34,pcVar5);
  }
  else {
    CString_CtorA(&local_2c,s_JPG_00043b38);
    iVar4 = wcscmp(local_34.str,local_2c.str);
    CString_Dtor(&local_2c);
    if (iVar4 == 0) {
      pcVar5 = s_IFJ_00043b34;
      goto LAB_00017da4;
    }
    CString_CtorA(&local_28,s_WAV_00043b30);
    iVar4 = wcscmp(local_34.str,local_28.str);
    CString_Dtor(&local_28);
    if (iVar4 == 0) {
      pcVar5 = s_IFV_00043b2c;
      goto LAB_00017da4;
    }
  }
  CString_SetAt(local_c,iVar6 + -3,*local_34.str);
  CString_SetAt(local_c,iVar6 + -2,local_34.str[1]);
  CString_SetAt(local_c,iVar6 + -1,local_34.str[2]);
  CString_MakeUpper(local_c);
  iVar6 = (char)local_c[0].str[-4] + -1;
  while (local_c[0].str[(char)iVar6] != L'.') {
    iVar6 = ((char)iVar6 + -1) * 0x1000000 >> 0x18;
  }
  iVar6 = iVar6 + -1;
  while( true ) {
    iVar6 = (int)(char)iVar6;
    if ((local_c[0].str + iVar6)[-1] == L'\\') break;
    wVar1 = local_c[0].str[iVar6];
    uVar2 = wVar1 & 0xff;
    if ((uVar2 < 0x41) || (0x5a < uVar2)) {
      uVar3 = uVar2;
      if (wVar1 == L'É') {
        uVar3 = 0x31;
      }
    }
    else {
      uVar3 = uVar2 + 4;
      if (0x5a < (uVar2 + 4 & 0xff)) {
        uVar3 = uVar2 - 0x16;
      }
    }
    CString_SetAt(local_c,iVar6,uVar3 & 0xff);
    iVar6 = (iVar6 + -1) * 0x1000000 >> 0x18;
  }
  CString_CopyCtor(param_1,local_c);
LAB_00017ec4:
  CString_Dtor(&local_34);
  CString_Dtor(local_c);
  return param_1;
}


// 00017ee0 LoadImageFile

int LoadImageFile(wchar_t *param_1,void *param_2)

{
  CString *pCVar1;
  wchar_t *lpFileName;
  HANDLE hFile;
  int iVar2;
  CString local_1048;
  CString local_1044;
  CString local_1040;
  CString CStack_103c;
  DWORD DStack_1038;
  CString local_1034;
  CString local_1030 [2];
  byte local_1028 [16];
  undefined1 local_1018;
  undefined1 auStack_1017 [4095];
  
  memset(auStack_1017,0,0xfff);
  local_1048.str = g_afxEmptyString;
  local_1030[0].str = g_afxEmptyString;
  CString_AssignW(&local_1048,param_1);
  CString_CopyCtor(&local_1044,&local_1048);
  pCVar1 = MangleAssetPath(&CStack_103c,local_1044);
  CString_Assign(&local_1048,pCVar1);
  CString_Dtor(&CStack_103c);
  lpFileName = CString_GetBuffer(&local_1048,*(int *)(local_1048.str + -4));
  hFile = CreateFileW(lpFileName,0xc0000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    local_1040.str = g_afxEmptyString;
    CString_Assign(&local_1040,&local_1048);
    CString_CtorA(&local_1034,&g_emptyA);
    iVar2 = wcscmp(local_1040.str,local_1034.str);
    CString_Dtor(&local_1034);
    if (iVar2 != 0) {
      CString_CtorA(&local_1044,s_Error___00043b50);
      pCVar1 = CString_Plus(&CStack_103c,&local_1044,&local_1040);
      CString_Assign(&local_1040,pCVar1);
      CString_Dtor(&CStack_103c);
      CString_Dtor(&local_1044);
      CString_CtorA(&local_1044,s_Not_found__00043b44);
      CString_Append(&local_1040,&local_1044);
      CString_Dtor(&local_1044);
      MessageBoxW((HWND)0x0,local_1040.str,u_Fade_00043458,0x10);
      GXCloseInput();
      GXCloseDisplay();
      crt_exit(1);
    }
    CString_Dtor(&local_1040);
    iVar2 = 0;
  }
  else {
    ReadFile(hFile,local_1028,10,&DStack_1038,(LPOVERLAPPED)0x0);
    iVar2 = 0;
    do {
      local_1028[iVar2] = local_1028[iVar2] ^ 0x4d;
      iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18;
    } while (iVar2 < 10);
    SetFilePointer(hFile,0,(PLONG)0x0,0);
    WriteFile(hFile,local_1028,10,&DStack_1038,(LPOVERLAPPED)0x0);
    SetFilePointer(hFile,0,(PLONG)0x0,0);
    g_imgDecompInfo.dwSize = 0x3c;
    g_imgDecompInfo.pbBuffer = &local_1018;
    g_imgDecompInfo.dwBufferMax = 0x1000;
    g_imgDecompInfo.dwBufferCurrent = 0;
    g_imgDecompInfo.ppImageRender = (void *)0x0;
    g_imgDecompInfo.iBitDepth = 0x18;
    g_imgDecompInfo.iScale = 100;
    g_imgDecompInfo.iMaxWidth = 400;
    g_imgDecompInfo.iMaxHeight = 600;
    g_imgDecompInfo.pfnGetData = ReadFileSafe;
    g_imgDecompInfo.pfnImageProgress = (void *)0x0;
    g_imgDecompInfo.crTransparentOverride = 0xffffffff;
    g_imgDecompInfo.phBM = param_2;
    g_imgDecompInfo.lParam = (int)hFile;
    DecompressImageIndirect();
    iVar2 = 0;
    do {
      local_1028[iVar2] = local_1028[iVar2] ^ 0x4d;
      iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18;
    } while (iVar2 < 10);
    SetFilePointer(hFile,0,(PLONG)0x0,0);
    WriteFile(hFile,local_1028,10,&DStack_1038,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    iVar2 = 1;
  }
  CString_Dtor(local_1030);
  CString_Dtor(&local_1048);
  return iVar2;
}


// 0001821c LoadImage

int LoadImage(CString param_1,int *param_2,int *param_3,ushort **param_4,byte param_5)

{
  wchar_t *pwVar1;
  uint uVar2;
  ushort *puVar3;
  CString *pCVar4;
  int iVar5;
  CString local_54;
  HANDLE local_50;
  CString local_4c;
  CString CStack_48;
  CString aCStack_44 [2];
  undefined1 auStack_3c [4];
  int local_38;
  int local_34;
  byte *local_28;
  CString local_10;
  int *piStack_c;
  int *piStack_8;
  ushort **ppuStack_4;
  
  local_10.str = param_1.str;
  piStack_c = param_2;
  piStack_8 = param_3;
  ppuStack_4 = param_4;
  pwVar1 = CString_GetBuffer(&local_10,*(int *)(param_1.str + -4));
  uVar2 = LoadImageFile(pwVar1,&local_50);
  if ((uVar2 & 0xff) == 0) {
    local_54.str = g_afxEmptyString;
    CString_Assign(&local_54,&local_10);
    CString_CtorA(&local_4c,&g_emptyA);
    iVar5 = wcscmp(local_54.str,local_4c.str);
    CString_Dtor(&local_4c);
    if (iVar5 != 0) {
      CString_CtorA(&CStack_48,s_Error___00043b50);
      pCVar4 = CString_Plus(aCStack_44,&CStack_48,&local_54);
      CString_Assign(&local_54,pCVar4);
      CString_Dtor(aCStack_44);
      CString_Dtor(&CStack_48);
      CString_CtorA(&CStack_48,s_Not_found__00043b44);
      CString_Append(&local_54,&CStack_48);
      CString_Dtor(&CStack_48);
      MessageBoxW((HWND)0x0,local_54.str,u_Fade_00043458,0x10);
      GXCloseInput();
      GXCloseDisplay();
      crt_exit(1);
    }
    CString_Dtor(&local_54);
    iVar5 = 0;
  }
  else {
    GetObjectW(local_50,0x18,auStack_3c);
    *param_2 = local_34;
    *param_3 = local_38;
    puVar3 = (ushort *)operator_new(*param_2 * local_38 * 2);
    *param_4 = puVar3;
    for (uVar2 = local_38 * 3; (uVar2 & 0xfffffffc) < uVar2; uVar2 = uVar2 + 1) {
    }
    if (g_pixelFormat == 0x40) {
      Bitmap_ConvertTo555((char)uVar2,local_28,(int)puVar3,*param_2,*param_3);
    }
    else if (g_pixelFormat == 0x80) {
      Bitmap_ConvertTo565((char)uVar2,local_28,(int)puVar3,*param_2,*param_3);
    }
    else if (g_pixelFormat == 0x200) {
      Bitmap_ConvertTo444(uVar2,local_28,(int)puVar3,*param_2,*param_3,param_5);
    }
    DeleteObject(local_50);
    iVar5 = 1;
  }
  CString_Dtor(&local_10);
  return iVar5;
}


// 00018460 ReadFileSafe

DWORD ReadFileSafe(LPVOID param_1,DWORD param_2,HANDLE param_3)

{
  DWORD local_8;
  
  if (param_3 == (HANDLE)0xffffffff) {
    local_8 = 0;
  }
  else {
    ReadFile(param_3,param_1,param_2,&local_8,(LPOVERLAPPED)0x0);
  }
  return local_8;
}


// 000184a8 Bitmap_ConvertTo565

void Bitmap_ConvertTo565(char param_1,byte *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  byte bVar2;
  ushort uVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  ushort *puVar11;
  int iVar12;
  int iVar13;
  
  iVar13 = param_3 + param_4 * param_5 * 2;
  for (; param_4 != 0; param_4 = param_4 + -1) {
    if (param_5 != 0) {
      puVar11 = (ushort *)(iVar13 + param_5 * -2);
      iVar12 = param_5;
      do {
        iVar9 = (int)(char)g_gamma;
        pbVar4 = param_2 + 1;
        pbVar5 = param_2 + 2;
        bVar2 = *param_2;
        param_2 = param_2 + 3;
        uVar10 = (uint)*pbVar5;
        iVar1 = (int)(char)g_gamma;
        uVar7 = (uint)bVar2 + iVar1;
        uVar8 = uVar7;
        if ((int)uVar7 < 0xff) {
          uVar8 = (uint)bVar2;
        }
        iVar6 = uVar10 + iVar1;
        if ((int)uVar7 < 0xff) {
          uVar8 = uVar8 + iVar9;
        }
        else {
          uVar8 = 0xff;
        }
        if (iVar6 < 0xff) {
          uVar10 = uVar10 + iVar9;
        }
        if (0xfe < iVar6) {
          uVar10 = 0xff;
        }
        if ((int)((uint)*pbVar4 + iVar1) < 0xff) {
          uVar7 = (uint)*pbVar4 + iVar9;
        }
        else {
          uVar7 = 0xff;
        }
        uVar3 = RGB888_To565(uVar10,uVar7,uVar8);
        iVar12 = iVar12 + -1;
        *puVar11 = uVar3;
        puVar11 = puVar11 + 1;
      } while (iVar12 != 0);
    }
    iVar13 = iVar13 + param_5 * -2;
    param_2 = param_2 + (byte)(param_1 + (char)param_5 * -3);
  }
  return;
}


// 000185ac Bitmap_ConvertTo555

void Bitmap_ConvertTo555(char param_1,byte *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  byte bVar2;
  ushort uVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  ushort *puVar11;
  int iVar12;
  int iVar13;
  
  iVar13 = param_3 + param_4 * param_5 * 2;
  for (; param_4 != 0; param_4 = param_4 + -1) {
    if (param_5 != 0) {
      puVar11 = (ushort *)(iVar13 + param_5 * -2);
      iVar12 = param_5;
      do {
        iVar9 = (int)(char)g_gamma;
        pbVar4 = param_2 + 1;
        pbVar5 = param_2 + 2;
        bVar2 = *param_2;
        param_2 = param_2 + 3;
        uVar10 = (uint)*pbVar5;
        iVar1 = (int)(char)g_gamma;
        uVar7 = (uint)bVar2 + iVar1;
        uVar8 = uVar7;
        if ((int)uVar7 < 0xff) {
          uVar8 = (uint)bVar2;
        }
        iVar6 = uVar10 + iVar1;
        if ((int)uVar7 < 0xff) {
          uVar8 = uVar8 + iVar9;
        }
        else {
          uVar8 = 0xff;
        }
        if (iVar6 < 0xff) {
          uVar10 = uVar10 + iVar9;
        }
        if (0xfe < iVar6) {
          uVar10 = 0xff;
        }
        if ((int)((uint)*pbVar4 + iVar1) < 0xff) {
          uVar7 = (uint)*pbVar4 + iVar9;
        }
        else {
          uVar7 = 0xff;
        }
        uVar3 = RGB888_To555(uVar10,uVar7,uVar8);
        iVar12 = iVar12 + -1;
        *puVar11 = uVar3;
        puVar11 = puVar11 + 1;
      } while (iVar12 != 0);
    }
    iVar13 = iVar13 + param_5 * -2;
    param_2 = param_2 + (byte)(param_1 + (char)param_5 * -3);
  }
  return;
}


// 000186b0 Bitmap_ConvertTo444

void Bitmap_ConvertTo444(int param_1,byte *param_2,int param_3,uint param_4,uint param_5,
                        char param_6)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint unaff_r6;
  uint unaff_r7;
  byte *pbVar11;
  byte *pbVar12;
  uint local_40;
  ushort *local_3c;
  int local_38;
  uint local_34;
  
  local_38 = param_3 + param_4 * param_5 * 2;
  local_34 = 0;
  if (param_4 != 0) {
    do {
      local_40 = param_5;
      if (param_5 != 0) {
        local_3c = (ushort *)(local_38 + param_5 * -2);
        pbVar4 = param_2;
        pbVar11 = param_2 + param_1;
        do {
          param_2 = pbVar4 + 3;
          pbVar12 = pbVar11 + 3;
          iVar7 = (int)(char)g_gamma;
          iVar1 = (int)(char)g_gamma;
          iVar5 = (uint)*pbVar4 + iVar1;
          if (iVar5 < 0xff) {
            unaff_r7 = (uint)*pbVar4 + iVar7;
          }
          iVar6 = (uint)pbVar4[2] + iVar1;
          if (0xfe < iVar5) {
            unaff_r7 = 0xff;
          }
          if (iVar6 < 0xff) {
            unaff_r6 = (uint)pbVar4[2] + iVar7;
          }
          if (0xfe < iVar6) {
            unaff_r6 = 0xff;
          }
          if ((int)((uint)pbVar4[1] + iVar1) < 0xff) {
            uVar9 = (uint)pbVar4[1] + iVar7;
          }
          else {
            uVar9 = 0xff;
          }
          uVar2 = RGB888_To444(unaff_r6,uVar9,unaff_r7);
          *local_3c = uVar2;
          if (param_6 != '\0') {
            uVar8 = unaff_r6 & 0xf;
            uVar9 = uVar9 & 0xf;
            uVar10 = unaff_r7 & 0xf;
            if (1 < local_40) {
              unaff_r7 = (uint)*param_2;
              uVar3 = (uVar10 >> 1) + unaff_r7;
              if (uVar3 < 0x100) {
                *param_2 = (byte)uVar3;
              }
              else {
                *param_2 = 0xff;
              }
              uVar3 = (uVar9 >> 1) + (uint)pbVar4[4];
              if (uVar3 < 0x100) {
                pbVar4[4] = (byte)uVar3;
              }
              else {
                pbVar4[4] = 0xff;
              }
              uVar3 = (uVar8 >> 1) + (uint)pbVar4[5];
              if (uVar3 < 0x100) {
                pbVar4[5] = (byte)uVar3;
              }
              else {
                pbVar4[5] = 0xff;
              }
            }
            if (local_34 != param_4 - 1) {
              if (1 < local_40) {
                unaff_r7 = (uint)*pbVar12;
                uVar3 = (uVar10 >> 2) + unaff_r7;
                if (uVar3 < 0x100) {
                  *pbVar12 = (byte)uVar3;
                }
                else {
                  *pbVar12 = 0xff;
                }
                uVar3 = (uVar9 >> 2) + (uint)pbVar11[4];
                if (uVar3 < 0x100) {
                  pbVar11[4] = (byte)uVar3;
                }
                else {
                  pbVar11[4] = 0xff;
                }
                uVar3 = (uVar8 >> 2) + (uint)pbVar11[5];
                if (uVar3 < 0x100) {
                  pbVar11[5] = (byte)uVar3;
                }
                else {
                  pbVar11[5] = 0xff;
                }
              }
              pbVar4 = param_2 + param_1 + -3;
              uVar10 = (uVar10 >> 2) + (uint)*pbVar4;
              if (0xff < uVar10) {
                *pbVar4 = 0xff;
              }
              if (uVar10 < 0x100) {
                *pbVar4 = (byte)uVar10;
              }
              uVar9 = (uVar9 >> 2) + (uint)param_2[param_1 + -2];
              if (uVar9 < 0x100) {
                param_2[param_1 + -2] = (byte)uVar9;
              }
              else {
                param_2[param_1 + -2] = 0xff;
              }
              uVar9 = (uVar8 >> 2) + (uint)param_2[param_1 + -1];
              if (uVar9 < 0x100) {
                param_2[param_1 + -1] = (byte)uVar9;
              }
              else {
                param_2[param_1 + -1] = 0xff;
              }
            }
          }
          uVar9 = local_40 - 1;
          local_3c = local_3c + 1;
          pbVar4 = param_2;
          unaff_r6 = local_40;
          pbVar11 = pbVar12;
          local_40 = uVar9;
        } while (uVar9 != 0);
      }
      param_2 = param_2 + (byte)((char)param_1 + (char)param_5 * -3);
      local_38 = local_38 + param_5 * -2;
      local_34 = local_34 + 1;
    } while (local_34 < param_4);
  }
  return;
}


// 0001898c StaticInit_RegisterAtexit

void StaticInit_RegisterAtexit(void)

{
  InstallDir_StaticInit();
  atexit(&LAB_000189c4);
  return;
}


// 0001899c InstallDir_StaticInit

void InstallDir_StaticInit(void)

{
  g_installDir.str = g_afxEmptyString;
  return;
}


// 000189d0 ReadDataIndex

uint ReadDataIndex(uint param_1)

{
  CString *pCVar1;
  HANDLE hFile;
  CString CStack_20;
  CString CStack_1c;
  uint local_18;
  DWORD DStack_14;
  
  CString_CtorA(&CStack_20,s_data_index_fad_00043b5c);
  pCVar1 = CString_Plus(&CStack_1c,&g_installDir,&CStack_20);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_1c);
  CString_Dtor(&CStack_20);
  if (hFile == (HANDLE)0xffffffff) {
    local_18 = 0;
  }
  else {
    SetFilePointer(hFile,(param_1 & 0xffff) << 2,(PLONG)0x0,0);
    ReadFile(hFile,&local_18,4,&DStack_14,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return local_18;
}


// 00018a9c nop_18a9c

void nop_18a9c(void)

{
  return;
}


// 00018aa0 nop_18aa0

void nop_18aa0(void)

{
  return;
}


// 00018aa4 Line_Init

void Line_Init(Line *this,int param_2,int param_3,int param_4,int param_5)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  
  if (param_2 == param_4) {
    this->vertical = 1;
    fVar1 = (float)__utos(param_2);
    this->m = fVar1;
  }
  else {
    this->vertical = 0;
    uVar2 = __utos(param_3);
    uVar3 = __utos(param_2);
    uVar4 = __utos(param_5);
    uVar4 = __subs(uVar4,uVar2);
    uVar5 = __utos(param_4);
    uVar5 = __subs(uVar5,uVar3);
    fVar1 = (float)__divs(uVar4,uVar5);
    this->m = fVar1;
    uVar3 = __muls(fVar1,uVar3);
    fVar1 = (float)__subs(uVar2,uVar3);
  }
  this->b = fVar1;
  iVar6 = __eqs(this->m,0);
  this->horizontal = iVar6 != 0;
  return;
}


// 00018bf8 Line_IsBelow

bool Line_IsBelow(Line *this,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  
  if (this->vertical == 0) {
    uVar1 = __utos();
    uVar2 = __utos(param_2);
    uVar2 = __muls(uVar2,this->m);
    uVar2 = __adds(uVar2,this->b);
    iVar3 = __ges(uVar1,uVar2);
    bVar4 = iVar3 != 0;
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}


// 00018ca4 Line_IsAbove

bool Line_IsAbove(Line *this,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  bool bVar4;
  
  if (this->vertical == 0) {
    uVar1 = __utos();
    uVar2 = __utos(param_2);
    uVar2 = __muls(uVar2,this->m);
    uVar2 = __adds(uVar2,this->b);
    iVar3 = __les(uVar1,uVar2);
    bVar4 = iVar3 != 0;
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}


// 00018d50 Line_IsLeftOf

bool Line_IsLeftOf(Line *this,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  if (this->horizontal == 0) {
    if (this->vertical == 0) {
      uVar1 = __utos();
      uVar3 = __utos(param_3);
      uVar3 = __subs(uVar3,this->b);
      uVar3 = __divs(uVar3,this->m);
      iVar2 = __les(uVar1,uVar3);
    }
    else {
      uVar1 = __utos();
      iVar2 = __les(uVar1,this->m);
    }
    bVar4 = iVar2 != 0;
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}


// 00018e28 Line_IsRightOf

bool Line_IsRightOf(Line *this,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  
  if (this->horizontal == 0) {
    if (this->vertical == 0) {
      uVar1 = __utos();
      uVar3 = __utos(param_3);
      uVar3 = __subs(uVar3,this->b);
      uVar3 = __divs(uVar3,this->m);
      iVar2 = __ges(uVar1,uVar3);
    }
    else {
      uVar1 = __utos();
      iVar2 = __ges(uVar1,this->m);
    }
    bVar4 = iVar2 != 0;
  }
  else {
    bVar4 = false;
  }
  return bVar4;
}


// 00018f00 RecF8_Ctor

void RecF8_Ctor(RecF8 *this)

{
  Rec14 *pRVar1;
  int iVar2;
  
  iVar2 = 8;
  (this->name).str = g_afxEmptyString;
  (this->spritePath).str = g_afxEmptyString;
  pRVar1 = this->actions;
  do {
    iVar2 = iVar2 + -1;
    (pRVar1->label).str = g_afxEmptyString;
    (pRVar1->text).str = g_afxEmptyString;
    pRVar1 = pRVar1 + 1;
  } while (iVar2 != 0);
  return;
}


// 00018f48 VecCtorIterator

void VecCtorIterator(int param_1,int param_2,int param_3,undefined *param_4)

{
  if (-1 < param_3 + -1) {
    do {
      (*(code *)param_4)(param_1);
      param_3 = param_3 + -1;
      param_1 = param_1 + param_2;
    } while (param_3 != 0);
  }
  return;
}


// 00018f84 VecDtorIterator

void VecDtorIterator(int param_1,int param_2,int param_3,undefined *param_4)

{
  int iVar1;
  
  iVar1 = param_2 * param_3 + param_1;
  if (-1 < param_3 + -1) {
    do {
      iVar1 = iVar1 - param_2;
      (*(code *)param_4)(iVar1);
      param_3 = param_3 + -1;
    } while (param_3 != 0);
  }
  return;
}


// 00018fc8 RecF8_Dtor

void RecF8_Dtor(RecF8 *this)

{
  RecF8 *pRVar1;
  int iVar2;
  
  iVar2 = 8;
  pRVar1 = this + 1;
  do {
    CString_Dtor(&pRVar1[-1].actions[7].text);
    CString_Dtor((CString *)(pRVar1[-1].actions + 7));
    iVar2 = iVar2 + -1;
    pRVar1 = (RecF8 *)(pRVar1[-1].actions + 7);
  } while (iVar2 != 0);
  CString_Dtor(&this->spritePath);
  CString_Dtor(&this->name);
  return;
}


// 0001900c RecF8_FreePixels

void RecF8_FreePixels(RecF8 *this)

{
  if (this->noSprite == 0) {
    free((this->img).pixels);
  }
  return;
}


// 00019024 RecF8_GetPos

Point * RecF8_GetPos(RecF8 *this,Point *param_2)

{
  *(char *)&param_2->x = (char)this->x;
  *(undefined1 *)((int)&param_2->x + 1) = *(undefined1 *)((int)&this->x + 1);
  *(undefined1 *)((int)&param_2->x + 2) = *(undefined1 *)((int)&this->x + 2);
  *(undefined1 *)((int)&param_2->x + 3) = *(undefined1 *)((int)&this->x + 3);
  *(char *)&param_2->y = (char)this->y;
  *(undefined1 *)((int)&param_2->y + 1) = *(undefined1 *)((int)&this->y + 1);
  *(undefined1 *)((int)&param_2->y + 2) = *(undefined1 *)((int)&this->y + 2);
  *(undefined1 *)((int)&param_2->y + 3) = *(undefined1 *)((int)&this->y + 3);
  return param_2;
}


// 00019070 RecF8_HitTest

bool RecF8_HitTest(RecF8 *this,int param_2,int param_3)

{
  bool bVar1;
  bool bVar2;
  Line LStack_20;
  
  nop_18a9c();
  Line_Init(&LStack_20,this->poly[0],this->poly[1],this->poly[2],this->poly[3]);
  bVar1 = Line_IsBelow(&LStack_20,param_2,param_3);
  bVar2 = false;
  if (bVar1) {
    Line_Init(&LStack_20,this->poly[2],this->poly[3],this->poly[4],this->poly[5]);
    bVar1 = Line_IsLeftOf(&LStack_20,param_2,param_3);
    bVar2 = false;
    if (bVar1) {
      Line_Init(&LStack_20,this->poly[4],this->poly[5],this->poly[6],this->poly[7]);
      bVar1 = Line_IsAbove(&LStack_20,param_2,param_3);
      bVar2 = false;
      if (bVar1) {
        Line_Init(&LStack_20,this->poly[6],this->poly[7],this->poly[0],this->poly[1]);
        bVar2 = Line_IsRightOf(&LStack_20,param_2,param_3);
      }
    }
  }
  nop_18aa0();
  return bVar2;
}


// 000191e8 RecF8_GetImg

ImgRect * RecF8_GetImg(RecF8 *this,ImgRect *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  ImgRect *pIVar4;
  ImgRect *pIVar5;
  
  iVar2 = 0x14;
  pIVar4 = param_2;
  pIVar5 = &this->img;
  do {
    iVar3 = iVar2 + -1;
    *(undefined1 *)&pIVar4->pixels = *(undefined1 *)&pIVar5->pixels;
    bVar1 = 0 < iVar2;
    iVar2 = iVar3;
    pIVar4 = (ImgRect *)((int)&pIVar4->pixels + 1);
    pIVar5 = (ImgRect *)((int)&pIVar5->pixels + 1);
  } while (iVar3 != 0 && bVar1);
  return param_2;
}


// 00019210 RecF8_GetName

CString * RecF8_GetName(RecF8 *this,CString *param_2)

{
  CString_CopyCtor(param_2,&this->name);
  return param_2;
}


// 0001922c RecF8_GetNoSprite

byte RecF8_GetNoSprite(RecF8 *this)

{
  return this->noSprite;
}


// 00019234 RecF8_IsVisible

byte RecF8_IsVisible(RecF8 *this)

{
  return this->visible;
}


// 0001923c RecF8_Get6

byte RecF8_Get6(RecF8 *this)

{
  return this->f6;
}


// 00019244 RecF8_GetNumActions

byte RecF8_GetNumActions(RecF8 *this)

{
  return this->nActions;
}


// 0001924c RecF8_GetSub14

int RecF8_GetSub14(RecF8 *this,int param_2,uint param_3)

{
  Rec14_Copy((Rec14 *)param_2,this->actions + (param_3 & 0xff));
  return param_2;
}


// 00019278 Rec14_Copy

int Rec14_Copy(Rec14 *this,Rec14 *param_2)

{
  CString_CopyCtor(&this->label,&param_2->label);
  this->enabled = param_2->enabled;
  CString_CopyCtor(&this->text,&param_2->text);
  this->kind = param_2->kind;
  this->arg = param_2->arg;
  this->b11 = param_2->b11;
  this->b12 = param_2->b12;
  return (int)this;
}


// 000192c4 Zoom_Ctor

int Zoom_Ctor(Zoom *this)

{
  RecF8 *this_00;
  int iVar1;
  
  this_00 = this->recs;
  iVar1 = 0x19;
  (this->path).str = g_afxEmptyString;
  do {
    RecF8_Ctor(this_00);
    iVar1 = iVar1 + -1;
    this_00 = this_00 + 1;
  } while (iVar1 != 0);
  return (int)this;
}


// 00019304 Zoom_Dtor

void Zoom_Dtor(Zoom *this)

{
  Zoom *this_00;
  int iVar1;
  
  this_00 = this + 1;
  iVar1 = 0x19;
  do {
    this_00 = (Zoom *)(this_00[-1].recs + 0x18);
    RecF8_Dtor((RecF8 *)this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  CString_Dtor(&this->path);
  return;
}


// 00019340 Img_Free

void Img_Free(Zoom *this)

{
  if (this->loaded != 0) {
    free((this->img).pixels);
    this->loaded = 0;
  }
  return;
}


// 00019368 Img_Load

void Img_Load(Zoom *this)

{
  wchar_t *pwVar1;
  int iVar2;
  CString local_10;
  
  if (this->loaded == 0) {
    (this->img).x = 0;
    (this->img).y = 0;
    pwVar1 = CString_GetBuffer(&this->path,*(int *)((this->path).str + -4));
    CString_CtorW(&local_10,pwVar1);
    iVar2 = LoadImage(local_10,&(this->img).h,&(this->img).w,&(this->img).pixels,1);
    this->loaded = (byte)iVar2;
  }
  return;
}


// 000193d4 Img_Free2

void Img_Free2(Zoom *this)

{
  if (this->loaded != 0) {
    free((this->img).pixels);
    this->loaded = 0;
  }
  return;
}


// 000193fc Zoom_GetImg

ImgRect * Zoom_GetImg(Zoom *this,ImgRect *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  ImgRect *pIVar4;
  ImgRect *pIVar5;
  
  iVar2 = 0x14;
  pIVar4 = param_2;
  pIVar5 = &this->img;
  do {
    iVar3 = iVar2 + -1;
    *(undefined1 *)&pIVar4->pixels = *(undefined1 *)&pIVar5->pixels;
    bVar1 = 0 < iVar2;
    iVar2 = iVar3;
    pIVar4 = (ImgRect *)((int)&pIVar4->pixels + 1);
    pIVar5 = (ImgRect *)((int)&pIVar5->pixels + 1);
  } while (iVar3 != 0 && bVar1);
  return param_2;
}


// 00019424 Zoom_GetSlot

byte Zoom_GetSlot(Zoom *this)

{
  return this->slot;
}


// 0001942c Zoom_SetSlot

void Zoom_SetSlot(Zoom *this,byte param_2)

{
  this->slot = param_2;
  return;
}


// 00019434 Zoom_GetCount

byte Zoom_GetCount(Zoom *this)

{
  return this->count;
}


// 0001943c Zoom_GetRec

RecF8 * Zoom_GetRec(Zoom *this,uint param_2)

{
  return this->recs + (param_2 & 0xff);
}


// 00019454 Rec15c_Ctor

Rec15c * Rec15c_Ctor(Rec15c *this)

{
  Rec44 *pRVar1;
  int iVar2;
  
  pRVar1 = this->choices;
  iVar2 = 5;
  (this->title).str = g_afxEmptyString;
  do {
    (pRVar1->text).str = g_afxEmptyString;
    VecCtorIterator((int)pRVar1->replies,0xc,5,Rec0c_Ctor);
    iVar2 = iVar2 + -1;
    pRVar1 = pRVar1 + 1;
  } while (iVar2 != 0);
  return this;
}


// 000194ac Rec0c_Ctor

void Rec0c_Ctor(Rec0c *this)

{
  (this->text).str = g_afxEmptyString;
  return;
}


// 000194c0 Rec15c_Dtor

void Rec15c_Dtor(Rec15c *this)

{
  Rec15c *this_00;
  int iVar1;
  
  this_00 = this + 1;
  iVar1 = 5;
  do {
    this_00 = (Rec15c *)(this_00[-1].choices + 4);
    Rec44_Dtor((Rec44 *)this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  CString_Dtor(&this->title);
  return;
}


// 000194f4 Rec44_Dtor

void Rec44_Dtor(Rec44 *this)

{
  Rec0c *pRVar1;
  int iVar2;
  
  iVar2 = 5;
  pRVar1 = (Rec0c *)&this->active;
  do {
    CString_Dtor(&pRVar1[-1].text);
    iVar2 = iVar2 + -1;
    pRVar1 = pRVar1 + -1;
  } while (iVar2 != 0);
  CString_Dtor(&this->text);
  return;
}


// 00019528 Rec15c_ResetStates

void Rec15c_ResetStates(Rec15c *this)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = 0;
  do {
    uVar1 = 0;
    do {
      uVar2 = uVar1 + 1 & 0xff;
      this->choices[uVar3].replies[uVar1].val = 1;
      uVar1 = uVar2;
    } while (uVar2 < 5);
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 5);
  return;
}


// 0001957c Rec15c_GetName

CString * Rec15c_GetName(Rec15c *this,CString *param_2)

{
  CString_CopyCtor(param_2,&this->title);
  return param_2;
}


// 00019598 Rec15c_GetScript

byte Rec15c_GetScript(Rec15c *this)

{
  return this->script;
}


// 000195a0 Rec15c_GetRec44

int Rec15c_GetRec44(Rec15c *this,int param_2,uint param_3)

{
  Rec44_Copy((Rec44 *)param_2,this->choices + (param_3 & 0xff));
  return param_2;
}


// 000195cc Rec44_Copy

int Rec44_Copy(Rec44 *this,Rec44 *param_2)

{
  Rec0c *this_00;
  Rec0c *pRVar1;
  int iVar2;
  
  CString_CopyCtor(&this->text,&param_2->text);
  this_00 = this->replies;
  pRVar1 = (Rec0c *)(((int)this_00 - (int)this) + (int)param_2);
  iVar2 = 5;
  do {
    Rec0c_Copy(this_00,pRVar1);
    iVar2 = iVar2 + -1;
    this_00 = this_00 + 1;
    pRVar1 = pRVar1 + 1;
  } while (iVar2 != 0);
  this->active = param_2->active;
  return (int)this;
}


// 0001961c Rec0c_Copy

Rec0c * Rec0c_Copy(Rec0c *this,Rec0c *param_2)

{
  this->val = param_2->val;
  this->b4 = param_2->b4;
  this->b5 = param_2->b5;
  CString_CopyCtor(&this->text,&param_2->text);
  return this;
}


// 00019650 Rec44_AnyActive

bool Rec44_AnyActive(Rec44 *this,uint param_2)

{
  uint uVar1;
  bool bVar2;
  
  bVar2 = false;
  uVar1 = 0;
  do {
    if ((byte)this[(param_2 & 0xff) + 1].replies[0].val <= uVar1) {
      return bVar2;
    }
    bVar2 = this[param_2 & 0xff].replies[uVar1].text.str != (wchar_t *)0x1;
    uVar1 = uVar1 + 1 & 0xff;
  } while (!bVar2);
  return bVar2;
}


// 000196b8 Rec15c_AllDone

int Rec15c_AllDone(Rec15c *this)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 1;
  if (this->count != 0) {
    uVar2 = 0;
    do {
      bVar1 = Rec44_AnyActive((Rec44 *)this,uVar2);
      uVar2 = uVar2 + 1 & 0xff;
      if (bVar1) {
        iVar3 = 0;
      }
    } while (uVar2 < this->count);
  }
  return iVar3;
}


// 00019708 Rec15c_GetCount

byte Rec15c_GetCount(Rec15c *this)

{
  return this->count;
}


// 00019710 Rec15c_Advance

void Rec15c_Advance(Rec15c *this,uint param_2,uint param_3)

{
  if (this->choices[param_2 & 0xff].replies[param_3 & 0xff].val == 2) {
    this->choices[param_2 & 0xff].replies[param_3 & 0xff].val = 1;
  }
  return;
}


// 00019758 ScriptOpList_Ctor

int ScriptOpList_Ctor(ScriptOpList *this)

{
  ScriptOpList *pSVar1;
  int iVar2;
  
  iVar2 = 0x19;
  pSVar1 = this;
  do {
    VecCtorIterator((int)pSVar1->ops[0].str,4,3,CString_CtorEmpty);
    iVar2 = iVar2 + -1;
    pSVar1 = (ScriptOpList *)(pSVar1->ops + 1);
  } while (iVar2 != 0);
  return (int)this;
}


// 00019798 CString_CtorEmpty

void CString_CtorEmpty(undefined4 *param_1)

{
  *param_1 = g_afxEmptyString;
  return;
}


// 000197ac ScriptOpList_Dtor

void ScriptOpList_Dtor(ScriptOpList *this)

{
  ScriptOp *pSVar1;
  int iVar2;
  
  iVar2 = 0x19;
  pSVar1 = (ScriptOp *)&this->count;
  do {
    VecDtorIterator((int)pSVar1[-1].str,4,3,CString_Dtor);
    iVar2 = iVar2 + -1;
    pSVar1 = pSVar1 + -1;
  } while (iVar2 != 0);
  return;
}


// 000197ec ScriptOpList_GetCount

byte ScriptOpList_GetCount(ScriptOpList *this)

{
  return (byte)this->count;
}


// 000197fc ScriptOpList_Get

undefined4 * ScriptOpList_Get(ScriptOpList *this,undefined4 *param_2,uint param_3)

{
  ScriptOp_Copy((ScriptOp *)param_2,this->ops + (param_3 & 0xff));
  return param_2;
}


// 00019824 ScriptOp_Copy

ScriptOp * ScriptOp_Copy(ScriptOp *this,ScriptOp *param_2)

{
  CString *this_00;
  CString *pCVar1;
  int iVar2;
  
  this_00 = this->str;
  this->op = param_2->op;
  iVar2 = 3;
  this->b4 = param_2->b4;
  this->arg = param_2->arg;
  this->arg2 = param_2->arg2;
  this->ba = param_2->ba;
  this->bb = param_2->bb;
  this->bc = param_2->bc;
  this->bd = param_2->bd;
  this->i10 = param_2->i10;
  this->b14 = param_2->b14;
  this->list[0] = param_2->list[0];
  this->list[1] = param_2->list[1];
  this->list[2] = param_2->list[2];
  this->list[3] = param_2->list[3];
  this->list[4] = param_2->list[4];
  this->list[5] = param_2->list[5];
  this->list[6] = param_2->list[6];
  this->list[7] = param_2->list[7];
  pCVar1 = (CString *)(((int)this_00 - (int)this) + (int)param_2);
  do {
    CString_CopyCtor(this_00,pCVar1);
    iVar2 = iVar2 + -1;
    this_00 = this_00 + 1;
    pCVar1 = pCVar1 + 1;
  } while (iVar2 != 0);
  return this;
}


// 000198f4 Scene_Ctor

Scene * Scene_Ctor(Scene *this)

{
  CString *pCVar1;
  int iVar2;
  Rec15c *this_00;
  RecF8 *this_01;
  Zoom *this_02;
  ScriptOpList *this_03;
  
  iVar2 = 3;
  *(wchar_t **)this = g_afxEmptyString;
  pCVar1 = this->strs;
  do {
    iVar2 = iVar2 + -1;
    pCVar1->str = g_afxEmptyString;
    pCVar1 = pCVar1 + 1;
  } while (iVar2 != 0);
  this_00 = this->topics;
  iVar2 = 0xf;
  do {
    Rec15c_Ctor(this_00);
    iVar2 = iVar2 + -1;
    this_00 = this_00 + 1;
  } while (iVar2 != 0);
  this_01 = this->objs;
  iVar2 = 0x1e;
  do {
    RecF8_Ctor(this_01);
    iVar2 = iVar2 + -1;
    this_01 = this_01 + 1;
  } while (iVar2 != 0);
  this_02 = this->zooms;
  iVar2 = 10;
  do {
    Zoom_Ctor(this_02);
    iVar2 = iVar2 + -1;
    this_02 = this_02 + 1;
  } while (iVar2 != 0);
  this_03 = this->scripts;
  iVar2 = 0x1e;
  do {
    ScriptOpList_Ctor(this_03);
    iVar2 = iVar2 + -1;
    this_03 = this_03 + 1;
  } while (iVar2 != 0);
  return this;
}


// 000199d4 Scene_Dtor

void Scene_Dtor(Scene *this)

{
  ScriptOpList *this_00;
  Zoom *this_01;
  RecF8 *this_02;
  Rec15c *this_03;
  CString *this_04;
  int iVar1;
  
  this_00 = (ScriptOpList *)&this->nScripts;
  iVar1 = 0x1e;
  do {
    this_00 = this_00 + -1;
    ScriptOpList_Dtor(this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this_01 = (Zoom *)&this->nExits;
  iVar1 = 10;
  do {
    this_01 = this_01 + -1;
    Zoom_Dtor(this_01);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this_02 = (RecF8 *)&this->nObjs;
  iVar1 = 0x1e;
  do {
    this_02 = this_02 + -1;
    RecF8_Dtor(this_02);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this_03 = (Rec15c *)&this->f1494;
  iVar1 = 0xf;
  do {
    this_03 = this_03 + -1;
    Rec15c_Dtor(this_03);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  this_04 = (CString *)&this->curStr;
  iVar1 = 3;
  do {
    this_04 = this_04 + -1;
    CString_Dtor(this_04);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  CString_Dtor((CString *)this);
  return;
}


// 00019ab0 Scene_GetNumScripts

byte Scene_GetNumScripts(Scene *this)

{
  return (byte)this->nScripts;
}


// 00019ac0 Scene_Get1259a

byte Scene_Get1259a(Scene *this)

{
  return this->f12596[4];
}


// 00019ad0 Scene_Get12599

byte Scene_Get12599(Scene *this)

{
  return this->f12596[3];
}


// 00019ae0 Scene_GetF1259c

byte Scene_GetF1259c(Scene *this)

{
  return this->f12596[6];
}


// 00019af0 Scene_Get1259b

byte Scene_Get1259b(Scene *this)

{
  return this->f12596[5];
}


// 00019b00 Scene_GetExit

Link * Scene_GetExit(Scene *this,Link *param_2,uint param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)((undefined *)0x1256e + (int)(this->strs + ((param_3 & 0xff) - 8)));
  param_2->id = (ushort)uVar2;
  uVar1 = (undefined2)((uint)uVar2 >> 0x10);
  param_2->script = (char)uVar1;
  param_2->f3 = (char)((ushort)uVar1 >> 8);
  return param_2;
}


// 00019b34 Scene_GetNumObjs

byte Scene_GetNumObjs(Scene *this)

{
  return this->nObjs;
}


// 00019b44 Scene_GetObj

RecF8 * Scene_GetObj(Scene *this,uint param_2)

{
  return this->objs + (param_2 & 0xff);
}


// 00019b64 Scene_FreeResources

void Scene_FreeResources(Scene *this)

{
  uint uVar1;
  
  free((this->bg).pixels);
  if (this->kind == 2) {
    if (this->nObjs != 0) {
      uVar1 = 0;
      do {
        RecF8_FreePixels(this->objs + uVar1);
        uVar1 = uVar1 + 1 & 0xff;
      } while (uVar1 < this->nObjs);
    }
    if (this->nExits != 0) {
      uVar1 = 0;
      do {
        Img_Free(this->zooms + uVar1);
        uVar1 = uVar1 + 1 & 0xff;
      } while (uVar1 < this->nExits);
    }
  }
  return;
}


// 00019c28 Scene_GetBgImg

ImgRect * Scene_GetBgImg(Scene *this,ImgRect *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  ImgRect *pIVar4;
  ImgRect *pIVar5;
  
  iVar2 = 0x14;
  pIVar4 = param_2;
  pIVar5 = &this->bg;
  do {
    iVar3 = iVar2 + -1;
    *(undefined1 *)&pIVar4->pixels = *(undefined1 *)&pIVar5->pixels;
    bVar1 = 0 < iVar2;
    iVar2 = iVar3;
    pIVar4 = (ImgRect *)((int)&pIVar4->pixels + 1);
    pIVar5 = (ImgRect *)((int)&pIVar5->pixels + 1);
  } while (iVar3 != 0 && bVar1);
  return param_2;
}


// 00019c50 Scene_GetCurString

CString * Scene_GetCurString(Scene *this,CString *param_2)

{
  CString_CopyCtor(param_2,this->strs + this->curStr);
  return param_2;
}


// 00019c74 Scene_GetF12598

byte Scene_GetF12598(Scene *this)

{
  return this->f12596[2];
}


// 00019c84 Scene_SetKind

void Scene_SetKind(Scene *this,int param_2)

{
  this->kind = param_2;
  return;
}


// 00019c8c Scene_GetKind

int Scene_GetKind(Scene *this)

{
  return this->kind;
}


// 00019c94 Scene_SetCurStr

void Scene_SetCurStr(Scene *this,byte param_2)

{
  this->curStr = param_2;
  return;
}


// 00019c9c Scene_GetTopic

Rec15c * Scene_GetTopic(Scene *this,uint param_2)

{
  return this->topics + (param_2 & 0xff);
}


// 00019cb4 Scene_GetScripts

ScriptOpList * Scene_GetScripts(Scene *this)

{
  return this->scripts;
}


// 00019cc4 Scene_GetZoom

int Scene_GetZoom(Scene *this,uint param_2)

{
  return (int)(this->zooms + (param_2 & 0xff));
}


// 00019ce8 Scene_GetNumExits

byte Scene_GetNumExits(Scene *this)

{
  return this->nExits;
}


// 00019cf8 ReadDataRecord

CString * ReadDataRecord(CString *param_1,uint param_2)

{
  CString *pCVar1;
  HANDLE hFile;
  uint lDistanceToMove;
  uint uVar2;
  byte *lpBuffer;
  byte *pbVar3;
  DWORD nNumberOfBytesToRead;
  byte *local_30;
  CString local_2c;
  CString CStack_28;
  CString CStack_24;
  DWORD DStack_20;
  
  local_2c.str = g_afxEmptyString;
  CString_CtorA(&CStack_28,s_data_data_fad_00043b6c);
  pCVar1 = CString_Plus(&CStack_24,&g_installDir,&CStack_28);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_24);
  CString_Dtor(&CStack_28);
  if (hFile == (HANDLE)0xffffffff) {
    CString_CtorA(param_1,&g_emptyA);
  }
  else {
    lDistanceToMove = ReadDataIndex(param_2);
    uVar2 = ReadDataIndex(param_2 + 1);
    nNumberOfBytesToRead = uVar2 - lDistanceToMove;
    lpBuffer = (byte *)operator_new(nNumberOfBytesToRead);
    SetFilePointer(hFile,lDistanceToMove,(PLONG)0x0,0);
    ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,&DStack_20,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    pbVar3 = lpBuffer;
    for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
      *pbVar3 = *pbVar3 ^ 0x77;
      pbVar3 = pbVar3 + 1;
    }
    local_30 = lpBuffer;
    pCVar1 = Fad_ReadString(&CStack_24,(char **)&local_30);
    CString_Assign(&local_2c,pCVar1);
    CString_Dtor(&CStack_24);
    free(lpBuffer);
    CString_CopyCtor(param_1,&local_2c);
  }
  CString_Dtor(&local_2c);
  return param_1;
}


// 00019e6c LoadSceneFromData

void LoadSceneFromData(uint param_1,Scene *param_2)

{
  CString *pCVar1;
  HANDLE hFile;
  uint lDistanceToMove;
  uint uVar2;
  byte *lpBuffer;
  wchar_t *pwVar3;
  DWORD nNumberOfBytesToRead;
  byte *local_30;
  CString local_2c;
  CString CStack_28;
  CString local_24;
  DWORD DStack_20;
  
  local_2c.str = g_afxEmptyString;
  CString_CtorA(&CStack_28,s_data_data_fad_00043b6c);
  pCVar1 = CString_Plus(&local_24,&g_installDir,&CStack_28);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&local_24);
  CString_Dtor(&CStack_28);
  if (hFile != (HANDLE)0xffffffff) {
    lDistanceToMove = ReadDataIndex(param_1);
    uVar2 = ReadDataIndex(param_1 + 1);
    nNumberOfBytesToRead = uVar2 - lDistanceToMove;
    lpBuffer = (byte *)operator_new(nNumberOfBytesToRead);
    SetFilePointer(hFile,lDistanceToMove,(PLONG)0x0,0);
    ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,&DStack_20,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    local_30 = lpBuffer;
    for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
      *local_30 = *local_30 ^ 0x77;
      local_30 = local_30 + 1;
    }
    local_30 = (byte *)Fad_SkipField((char *)lpBuffer);
    local_30 = (byte *)Fad_SkipField((char *)local_30);
    CString_CtorA(&CStack_28,s_images__00043b7c);
    pCVar1 = CString_Plus(&local_24,&g_installDir,&CStack_28);
    CString_Assign(&local_2c,pCVar1);
    CString_Dtor(&local_24);
    CString_Dtor(&CStack_28);
    pCVar1 = Fad_ReadString(&local_24,(char **)&local_30);
    CString_Append(&local_2c,pCVar1);
    CString_Dtor(&local_24);
    pwVar3 = CString_GetBuffer(&local_2c,*(int *)(local_2c.str + -4));
    CString_CtorW(&local_24,pwVar3);
    LoadImage(local_24,&(param_2->bg).x,(int *)&param_2->bg,(ushort **)param_2,1);
    free(lpBuffer);
  }
  CString_Dtor(&local_2c);
  return;
}


// 0001a044 ReadDataRecord2

uint ReadDataRecord2(uint param_1)

{
  bool bVar1;
  CString *pCVar2;
  HANDLE hFile;
  uint uVar3;
  uint uVar4;
  byte *lpBuffer;
  DWORD nNumberOfBytesToRead;
  byte *local_28;
  CString CStack_24;
  CString CStack_20;
  DWORD DStack_1c;
  
  CString_CtorA(&CStack_24,s_data_data_fad_00043b6c);
  pCVar2 = CString_Plus(&CStack_20,&g_installDir,&CStack_24);
  hFile = CreateFileW(pCVar2->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_20);
  CString_Dtor(&CStack_24);
  if (hFile == (HANDLE)0xffffffff) {
    uVar3 = 0;
  }
  else {
    uVar3 = ReadDataIndex(param_1);
    uVar4 = ReadDataIndex(param_1 + 1);
    nNumberOfBytesToRead = uVar4 - uVar3;
    lpBuffer = (byte *)operator_new(nNumberOfBytesToRead);
    SetFilePointer(hFile,uVar3,(PLONG)0x0,0);
    ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,&DStack_1c,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    local_28 = lpBuffer;
    for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
      *local_28 = *local_28 ^ 0x77;
      local_28 = local_28 + 1;
    }
    local_28 = (byte *)Fad_SkipField((char *)lpBuffer);
    local_28 = (byte *)Fad_SkipField((char *)local_28);
    local_28 = (byte *)Fad_SkipField((char *)local_28);
    local_28 = (byte *)Fad_SkipField((char *)local_28);
    bVar1 = Fad_ReadBool((char **)&local_28);
    uVar3 = (uint)bVar1;
    free(lpBuffer);
  }
  return uVar3;
}


// 0001a190 ReadDataIndexCount

ushort ReadDataIndexCount(void)

{
  CString *pCVar1;
  HANDLE hFile;
  CString CStack_1c;
  CString CStack_18;
  ushort local_14 [2];
  DWORD DStack_10;
  
  CString_CtorA(&CStack_1c,s_data_index_fad_00043b5c);
  pCVar1 = CString_Plus(&CStack_18,&g_installDir,&CStack_1c);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_18);
  CString_Dtor(&CStack_1c);
  if (hFile == (HANDLE)0xffffffff) {
    local_14[0] = 0;
  }
  else {
    ReadFile(hFile,local_14,4,&DStack_10,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return local_14[0];
}


// 0001a23c LoadSceneScript

void LoadSceneScript(int param_1,uint param_2,undefined4 param_3)

{
  CString *pCVar1;
  HANDLE hFile;
  uint lDistanceToMove;
  uint uVar2;
  byte *lpBuffer;
  byte *pbVar3;
  DWORD nNumberOfBytesToRead;
  CString CStack_2c;
  CString CStack_28;
  DWORD DStack_24;
  
  CString_CtorA(&CStack_2c,s_data_data_fad_00043b6c);
  pCVar1 = CString_Plus(&CStack_28,&g_installDir,&CStack_2c);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_28);
  CString_Dtor(&CStack_2c);
  if (hFile != (HANDLE)0xffffffff) {
    lDistanceToMove = ReadDataIndex(param_2);
    uVar2 = ReadDataIndex(param_2 + 1);
    nNumberOfBytesToRead = uVar2 - lDistanceToMove;
    lpBuffer = (byte *)operator_new(nNumberOfBytesToRead);
    SetFilePointer(hFile,lDistanceToMove,(PLONG)0x0,0);
    ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,&DStack_24,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    pbVar3 = lpBuffer;
    for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
      *pbVar3 = *pbVar3 ^ 0x77;
      pbVar3 = pbVar3 + 1;
    }
    ExecSceneScript((Scene *)param_1,lpBuffer,(char)param_3);
    free(lpBuffer);
  }
  return;
}


// 0001a35c Fad_ReadString

CString * Fad_ReadString(CString *param_1,char **param_2)

{
  byte bVar1;
  byte *pbVar2;
  CString local_14;
  
  local_14.str = g_afxEmptyString;
  pbVar2 = (byte *)*param_2;
  CString_AssignA(&local_14,&g_emptyA);
  do {
    bVar1 = *pbVar2;
    pbVar2 = pbVar2 + 1;
  } while (bVar1 != 0x23);
  for (; *pbVar2 != 0x23; pbVar2 = pbVar2 + 1) {
    CString_AppendChar(&local_14,(ushort)*pbVar2);
  }
  *param_2 = (char *)(pbVar2 + 1);
  CString_CopyCtor(param_1,&local_14);
  CString_Dtor(&local_14);
  return param_1;
}


// 0001a3e8 Fad_ReadCharAfterUnderscore

char Fad_ReadCharAfterUnderscore(char **param_1)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = *param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '_');
  *param_1 = pcVar2;
  return *pcVar2;
}


// 0001a408 Fad_ReadU16AfterUnderscore

int Fad_ReadU16AfterUnderscore(char **param_1)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar3 = (byte *)*param_1;
  do {
    pbVar4 = pbVar3;
    pbVar3 = pbVar4 + 1;
  } while (*pbVar4 != 0x5f);
  bVar1 = pbVar4[1];
  bVar2 = pbVar4[2];
  *param_1 = (char *)(pbVar4 + 3);
  return (int)(((uint)bVar2 + (uint)bVar1 * 0x100) * 0x10000) >> 0x10;
}


// 0001a440 Fad_ReadInt

int Fad_ReadInt(char **param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  
  pbVar3 = (byte *)*param_1;
  iVar2 = 0;
  do {
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0x23);
  for (; *pbVar3 != 0x23; pbVar3 = pbVar3 + 1) {
    iVar2 = iVar2 * 10 + (uint)*pbVar3 + -0x30;
  }
  *param_1 = (char *)(pbVar3 + 1);
  return iVar2;
}


// 0001a494 Fad_ReadIntComma

int Fad_ReadIntComma(char **param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  pbVar3 = (byte *)*param_1;
  iVar2 = 0;
  do {
    bVar1 = *pbVar3;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0x23);
  for (; (uVar4 = (uint)*pbVar3, uVar4 != 0x23 && (uVar4 != 0x2c)); pbVar3 = pbVar3 + 1) {
    iVar2 = iVar2 * 10 + uVar4 + -0x30;
  }
  if (*pbVar3 == 0x2c) {
    pbVar3 = pbVar3 + 1;
  }
  *param_1 = (char *)pbVar3;
  return iVar2;
}


// 0001a4f8 Fad_ReadIntNext

int Fad_ReadIntNext(char **param_1)

{
  bool bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  iVar2 = 0;
  bVar1 = true;
  for (pbVar3 = (byte *)*param_1; (uVar4 = (uint)*pbVar3, uVar4 != 0x23 && (uVar4 != 0x2c));
      pbVar3 = pbVar3 + 1) {
    iVar2 = iVar2 * 10 + uVar4 + -0x30;
    bVar1 = false;
  }
  if (bVar1) {
    iVar2 = -1;
  }
  *param_1 = (char *)(pbVar3 + 1);
  return iVar2;
}


// 0001a554 Fad_ReadIntFlag

int Fad_ReadIntFlag(char **param_1,bool *param_2)

{
  bool bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  iVar2 = 0;
  bVar1 = true;
  for (pbVar3 = (byte *)*param_1; (uVar4 = (uint)*pbVar3, uVar4 != 0x23 && (uVar4 != 0x2c));
      pbVar3 = pbVar3 + 1) {
    iVar2 = iVar2 * 10 + uVar4 + -0x30;
    bVar1 = false;
  }
  if (bVar1) {
    iVar2 = -1;
  }
  *param_2 = *pbVar3 == 0x23;
  *param_1 = (char *)(pbVar3 + 1);
  return iVar2;
}


// 0001a5c4 Fad_ReadBool

bool Fad_ReadBool(char **param_1)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  
  pcVar2 = *param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '#');
  cVar1 = *pcVar2;
  bVar3 = cVar1 == '1';
  while (cVar1 != '#') {
    pcVar2 = pcVar2 + 1;
    cVar1 = *pcVar2;
  }
  *param_1 = pcVar2 + 1;
  return bVar3;
}


// 0001a614 Fad_SkipField

char * Fad_SkipField(char *param_1)

{
  char cVar1;
  
  do {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '#');
  do {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '#');
  return param_1;
}


// 0001a638 ParseSceneScript

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 * ParseSceneScript(ScriptOpList *param_1,char **param_2)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  CString *pCVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  char *local_4a8;
  char local_4a4;
  bool local_4a3 [3];
  CString local_4a0;
  CString local_49c;
  CString local_498;
  CString CStack_494;
  CString CStack_490;
  CString CStack_48c;
  CString CStack_488;
  CString CStack_484;
  ScriptOpList local_480;
  
  ScriptOpList_Ctor(&local_480);
  local_4a8 = *param_2;
  uVar7 = 0;
  local_4a4 = '\0';
  local_4a0.str = g_afxEmptyString;
  do {
    uVar3 = Fad_ReadU16AfterUnderscore(&local_4a8);
    uVar6 = uVar3 & 0xff;
    switch((uVar3 & 0xffff) >> 8) {
    case 0x41:
      if (uVar6 != 100) {
        if (uVar6 == 0x66) {
          local_480.ops[uVar7].op = 0;
          uVar3 = 0;
          do {
            pCVar4 = Fad_ReadString(&CStack_494,&local_4a8);
            CString_Assign(local_480.ops[uVar7].str + uVar3,pCVar4);
            CString_Dtor(&CStack_494);
            uVar3 = uVar3 + 1 & 0xff;
          } while (uVar3 < 3);
        }
        else {
          if (uVar6 != 0x6c) {
            if (uVar6 != 0x74) break;
            iVar5 = 0x20;
            goto LAB_0001a96c;
          }
          local_480.ops[uVar7].op = 0xb;
LAB_0001a9c0:
          iVar5 = Fad_ReadInt(&local_4a8);
          local_480.ops[uVar7].arg = (ushort)iVar5;
        }
        goto LAB_0001ac18;
      }
      iVar5 = 0x1f;
LAB_0001a96c:
      local_480.ops[uVar7].op = iVar5;
      iVar5 = Fad_ReadInt(&local_4a8);
      local_480.ops[uVar7].arg = (ushort)iVar5;
      iVar5 = Fad_ReadInt(&local_4a8);
      local_480.ops[uVar7].bc = (byte)iVar5;
      goto LAB_0001aee4;
    case 0x42:
      break;
    case 0x43:
      if (uVar6 == 0x61) {
        iVar5 = 0xe;
LAB_0001aab8:
        local_480.ops[uVar7].op = iVar5;
        iVar5 = Fad_ReadInt(&local_4a8);
        local_480.ops[uVar7].arg = (ushort)iVar5;
        goto LAB_0001aed0;
      }
      if (uVar6 == 0x69) {
        iVar5 = 0x22;
        goto LAB_0001aefc;
      }
      if (uVar6 == 0x6c) {
        iVar5 = 0x21;
        goto LAB_0001a8cc;
      }
      break;
    case 0x44:
      if (uVar6 == 0x65) {
        iVar5 = 6;
      }
      else {
        if (uVar6 != 0x69) {
          if (uVar6 == 0x6c) {
            local_480.ops[uVar7].op = 0x1e;
            goto LAB_0001a9c0;
          }
          if (uVar6 == 0x73) {
            iVar5 = 0x17;
            goto LAB_0001aab8;
          }
          break;
        }
        iVar5 = 0xf;
      }
      local_480.ops[uVar7].op = iVar5;
      iVar5 = Fad_ReadIntComma(&local_4a8);
      local_480.ops[uVar7].arg = (ushort)iVar5;
      iVar5 = Fad_ReadIntNext(&local_4a8);
      local_480.ops[uVar7].b4 = (byte)iVar5;
      goto LAB_0001aee4;
    case 0x45:
      if (uVar6 == 0x66) {
        local_480.ops[uVar7].op = 0xc;
        iVar5 = Fad_ReadInt(&local_4a8);
        local_480.ops[uVar7].ba = (byte)iVar5;
        uVar7 = uVar7 + 1 & 0xff;
      }
      if (uVar6 == 0x61) {
        iVar5 = 0xd;
        goto LAB_0001aefc;
      }
      break;
    case 0x46:
      if (uVar6 != 0x41) {
        if (uVar6 == 0x62) {
          iVar5 = 0x25;
        }
        else if (uVar6 == 99) {
          iVar5 = 0x24;
        }
        else if (uVar6 == 0x6a) {
          iVar5 = 0x23;
        }
        else {
          if (uVar6 == 0x73) {
            iVar5 = 0x18;
            goto LAB_0001aab8;
          }
          if (uVar6 != 0x7a) break;
          iVar5 = 0x1d;
        }
        goto LAB_0001aefc;
      }
      local_4a4 = '\x01';
      break;
    case 0x47:
      break;
    case 0x48:
      break;
    case 0x49:
      if (uVar6 == 0x66) {
        local_480.ops[uVar7].op = 0x16;
        uVar3 = Fad_ReadIntComma(&local_4a8);
        local_480.ops[uVar7].list[0] = (byte)uVar3;
        local_4a3[0] = (uVar3 & 0xff) == 0xffffffff;
        uVar3 = 1;
        if (!local_4a3[0]) {
          do {
            iVar5 = Fad_ReadIntFlag(&local_4a8,local_4a3);
            local_480.ops[uVar7].list[uVar3] = (byte)iVar5;
            uVar3 = uVar3 + 1 & 0xff;
          } while (local_4a3[0] == false);
        }
        for (; uVar3 < 8; uVar3 = uVar3 + 1 & 0xff) {
          local_480.ops[uVar7].list[uVar3] = 0xff;
        }
        iVar5 = Fad_ReadInt(&local_4a8);
        local_480.ops[uVar7].bc = (byte)iVar5;
        iVar5 = Fad_ReadInt(&local_4a8);
        local_480.ops[uVar7].bd = (byte)iVar5;
LAB_0001b01c:
        uVar7 = uVar7 + 1;
        goto LAB_0001b020;
      }
      if (uVar6 == 0x6c) {
        local_480.ops[uVar7].op = 3;
        pCVar4 = Fad_ReadString(&CStack_490,&local_4a8);
        CString_Assign(local_480.ops[uVar7].str,pCVar4);
        CString_Dtor(&CStack_490);
        goto LAB_0001aee4;
      }
      break;
    case 0x4a:
      break;
    case 0x4b:
      break;
    case 0x4c:
      if (uVar6 == 100) {
        iVar5 = 0x10;
      }
      else {
        if (uVar6 != 0x74) {
          if (uVar6 == 0x7a) {
            local_480.ops[uVar7].op = 0x15;
            iVar5 = Fad_ReadInt(&local_4a8);
            local_480.ops[uVar7].bb = (byte)iVar5;
            goto LAB_0001ac18;
          }
          break;
        }
        iVar5 = 0x1c;
      }
LAB_0001aefc:
      local_480.ops[uVar7].op = iVar5;
      uVar7 = uVar7 + 1;
      goto LAB_0001b020;
    case 0x4d:
      break;
    case 0x4e:
      break;
    case 0x4f:
      break;
    case 0x50:
      if (uVar6 == 0x61) {
        local_480.ops[uVar7].op = 1;
        uVar3 = 0;
        do {
          pCVar4 = Fad_ReadString(&CStack_48c,&local_4a8);
          CString_Assign(local_480.ops[uVar7].str + uVar3,pCVar4);
          CString_Dtor(&CStack_48c);
          uVar3 = uVar3 + 1 & 0xff;
        } while (uVar3 < 3);
      }
      else {
        if (uVar6 == 0x69) {
          iVar5 = 0x13;
LAB_0001a8cc:
          local_480.ops[uVar7].op = iVar5;
          goto LAB_0001aea8;
        }
        if (uVar6 != 0x72) {
          if (uVar6 == 0x73) {
            local_480.ops[uVar7].op = 9;
            iVar5 = Fad_ReadIntComma(&local_4a8);
            local_480.ops[uVar7].arg = (ushort)iVar5;
          }
          else {
            if (uVar6 != 0x7a) break;
            local_480.ops[uVar7].op = 8;
            iVar5 = Fad_ReadIntComma(&local_4a8);
            local_480.ops[uVar7].arg = (ushort)iVar5;
            iVar5 = Fad_ReadIntNext(&local_4a8);
            local_480.ops[uVar7].bb = (byte)iVar5;
          }
          iVar5 = Fad_ReadIntNext(&local_4a8);
          bVar1 = (byte)iVar5;
          goto LAB_0001aeb0;
        }
        local_480.ops[uVar7].op = 7;
        iVar5 = Fad_ReadInt(&local_4a8);
        local_480.ops[uVar7].ba = (byte)iVar5;
      }
LAB_0001ac18:
      uVar7 = uVar7 + 1;
      goto LAB_0001b020;
    case 0x51:
      break;
    case 0x52:
      if (uVar6 == 0x65) {
        local_480.ops[uVar7].op = 0x1a;
        iVar5 = Fad_ReadIntComma(&local_4a8);
        local_480.ops[uVar7].arg = (ushort)iVar5;
        iVar5 = Fad_ReadIntNext(&local_4a8);
        local_480.ops[uVar7].bb = (byte)iVar5;
        iVar5 = Fad_ReadIntNext(&local_4a8);
        local_480.ops[uVar7].ba = (byte)iVar5;
        iVar5 = Fad_ReadIntNext(&local_4a8);
        local_480.ops[uVar7].bc = (byte)iVar5;
        pCVar4 = Fad_ReadString(&CStack_488,&local_4a8);
        CString_Assign(&local_4a0,pCVar4);
        CString_Dtor(&CStack_488);
        CString_CtorA(&local_498,s_ON_00043ba0);
        iVar5 = wcscmp(local_4a0.str,local_498.str);
        CString_Dtor(&local_498);
        if (iVar5 == 0) {
          local_480.ops[uVar7].i10 = 0;
        }
        else {
          CString_CtorA(&local_49c,s_OFF_00043b9c);
          iVar5 = wcscmp(local_4a0.str,local_49c.str);
          CString_Dtor(&local_49c);
          if (iVar5 == 0) {
            local_480.ops[uVar7].i10 = 1;
          }
          else {
            local_480.ops[uVar7].i10 = 2;
          }
        }
        goto LAB_0001b01c;
      }
      break;
    case 0x53:
      if (uVar6 == 99) {
        local_480.ops[uVar7].op = 4;
        iVar5 = Fad_ReadIntComma(&local_4a8);
        local_480.ops[uVar7].arg = (ushort)iVar5;
        iVar5 = Fad_ReadIntNext(&local_4a8);
        local_480.ops[uVar7].arg2 = (ushort)iVar5;
        goto LAB_0001aed0;
      }
      if (uVar6 == 100) {
        iVar5 = 0x12;
        goto LAB_0001aefc;
      }
      if (uVar6 == 0x6f) {
        local_480.ops[uVar7].op = 10;
        pCVar4 = Fad_ReadString(&CStack_484,&local_4a8);
        CString_Assign(&local_4a0,pCVar4);
        CString_Dtor(&CStack_484);
        iVar5 = Fad_ReadInt(&local_4a8);
        local_480.ops[uVar7].b4 = (byte)iVar5;
        CString_Assign(local_480.ops[uVar7].str,&local_4a0);
        goto LAB_0001ac18;
      }
      break;
    case 0x54:
      if (uVar6 == 0x6c) {
        local_480.ops[uVar7].op = 2;
LAB_0001aea8:
        iVar5 = Fad_ReadIntComma(&local_4a8);
        bVar1 = (byte)iVar5;
LAB_0001aeb0:
        local_480.ops[uVar7].ba = bVar1;
        iVar5 = Fad_ReadIntNext(&local_4a8);
        local_480.ops[uVar7].bc = (byte)iVar5;
        goto LAB_0001aed0;
      }
      break;
    case 0x55:
      break;
    case 0x56:
      if (uVar6 == 0x69) {
        local_480.ops[uVar7].op = 0x11;
        iVar5 = Fad_ReadIntComma(&local_4a8);
        local_480.ops[uVar7].arg = (ushort)iVar5;
LAB_0001ac8c:
        iVar5 = Fad_ReadIntNext(&local_4a8);
        bVar1 = (byte)iVar5;
      }
      else {
        if (uVar6 != 0x6f) {
          if (uVar6 != 0x7a) break;
          local_480.ops[uVar7].op = 0x14;
          iVar5 = Fad_ReadIntComma(&local_4a8);
          local_480.ops[uVar7].arg = (ushort)iVar5;
          iVar5 = Fad_ReadIntNext(&local_4a8);
          local_480.ops[uVar7].bb = (byte)iVar5;
          goto LAB_0001ac8c;
        }
        local_480.ops[uVar7].op = 0x1b;
        iVar5 = Fad_ReadInt(&local_4a8);
        bVar1 = (byte)iVar5;
      }
      local_480.ops[uVar7].ba = bVar1;
LAB_0001aed0:
      bVar2 = Fad_ReadBool(&local_4a8);
      local_480.ops[uVar7].b14 = bVar2;
LAB_0001aee4:
      uVar7 = uVar7 + 1;
LAB_0001b020:
      uVar7 = uVar7 & 0xff;
      break;
    case 0x57:
      if (uVar6 == 0x61) {
        iVar5 = 0x19;
        goto LAB_0001aefc;
      }
      break;
    case 0x58:
      break;
    case 0x59:
      break;
    case 0x5a:
      if (uVar6 == 0x6f) {
        local_480.ops[uVar7].op = 5;
        iVar5 = Fad_ReadIntComma(&local_4a8);
        local_480.ops[uVar7].arg = (ushort)iVar5;
        iVar5 = Fad_ReadIntNext(&local_4a8);
        local_480.ops[uVar7].bb = (byte)iVar5;
        goto LAB_0001aed0;
      }
    }
    if (local_4a4 != '\0') {
      local_480.count._0_1_ = (undefined1)uVar7;
      *param_2 = local_4a8;
      ScriptOpList_Copy(param_1,&local_480);
      CString_Dtor(&local_4a0);
      ScriptOpList_Dtor(&local_480);
      return (undefined4 *)param_1;
    }
  } while( true );
}


// 0001b07c ScriptOpList_Copy

undefined4 * ScriptOpList_Copy(ScriptOpList *this,ScriptOpList *param_2)

{
  ScriptOpList *this_00;
  int iVar1;
  
  iVar1 = 0x19;
  this_00 = this;
  do {
    ScriptOp_Copy(this_00->ops,(ScriptOp *)(((int)param_2 - (int)this) + (int)this_00));
    iVar1 = iVar1 + -1;
    this_00 = (ScriptOpList *)(this_00->ops + 1);
  } while (iVar1 != 0);
  *(char *)&this->count = (char)param_2->count;
  return (undefined4 *)this;
}


// 0001b0c8 LoadSprite

void LoadSprite(RecF8 *this,char **param_2,char param_3)

{
  bool bVar1;
  char cVar2;
  bool bVar3;
  CString *pCVar4;
  int iVar5;
  wchar_t *pwVar6;
  uint uVar7;
  char *local_28;
  CString CStack_24;
  CString local_20;
  
  local_28 = *param_2;
  pCVar4 = Fad_ReadString(&CStack_24,&local_28);
  CString_Assign(&this->name,pCVar4);
  CString_Dtor(&CStack_24);
  iVar5 = Fad_ReadInt(&local_28);
  this->f4 = (byte)iVar5;
  iVar5 = Fad_ReadIntComma(&local_28);
  this->poly[0] = (int)(short)iVar5;
  iVar5 = Fad_ReadIntNext(&local_28);
  this->poly[1] = (int)(short)iVar5;
  uVar7 = 1;
  do {
    iVar5 = Fad_ReadIntNext(&local_28);
    this->poly[uVar7 * 2] = (int)(short)iVar5;
    iVar5 = Fad_ReadIntNext(&local_28);
    this->poly[uVar7 * 2 + 1] = (int)(short)iVar5;
    uVar7 = uVar7 + 1 & 0xff;
  } while (uVar7 < 4);
  iVar5 = Fad_ReadInt(&local_28);
  this->f6 = (byte)iVar5;
  bVar1 = Fad_ReadBool(&local_28);
  this->visible = 1;
  this->noSprite = bVar1;
  if (!bVar1) {
    iVar5 = Fad_ReadIntComma(&local_28);
    this->x = (int)(short)iVar5;
    iVar5 = Fad_ReadIntNext(&local_28);
    this->y = (int)(short)iVar5;
    bVar1 = Fad_ReadBool(&local_28);
    this->visible = bVar1;
    if (param_3 != '\0') {
      CString_CtorA(&CStack_24,s_sprites__00043ba4);
      pCVar4 = CString_Plus(&local_20,&g_installDir,&CStack_24);
      CString_Assign(&this->spritePath,pCVar4);
      CString_Dtor(&local_20);
      CString_Dtor(&CStack_24);
      pCVar4 = Fad_ReadString(&local_20,&local_28);
      CString_Append(&this->spritePath,pCVar4);
      CString_Dtor(&local_20);
      (this->img).x = this->x;
      (this->img).y = this->y;
      pwVar6 = CString_GetBuffer(&this->spritePath,*(int *)((this->spritePath).str + -4));
      CString_CtorW(&local_20,pwVar6);
      LoadImage(local_20,&(this->img).h,&(this->img).w,&(this->img).pixels,1);
    }
  }
  bVar1 = false;
  this->nActions = 0;
  do {
    cVar2 = Fad_ReadCharAfterUnderscore(&local_28);
    if (cVar2 == 'F') {
      bVar1 = true;
    }
    else if (cVar2 == 'P') {
      pCVar4 = Fad_ReadString(&local_20,&local_28);
      CString_Assign(&this->actions[this->nActions].label,pCVar4);
      CString_Dtor(&local_20);
      cVar2 = Fad_ReadCharAfterUnderscore(&local_28);
      if (cVar2 == 'A') {
        this->actions[this->nActions].kind = 2;
        bVar3 = Fad_ReadBool(&local_28);
        this->actions[this->nActions].enabled = bVar3;
        iVar5 = Fad_ReadInt(&local_28);
        this->actions[this->nActions].arg = (byte)iVar5;
      }
      else if (cVar2 == 'D') {
        this->actions[this->nActions].kind = 0;
        bVar3 = Fad_ReadBool(&local_28);
        this->actions[this->nActions].enabled = bVar3;
        pCVar4 = Fad_ReadString(&CStack_24,&local_28);
        CString_Assign(&this->actions[this->nActions].text,pCVar4);
        CString_Dtor(&CStack_24);
      }
      else if (cVar2 == 'Z') {
        this->actions[this->nActions].kind = 1;
        bVar3 = Fad_ReadBool(&local_28);
        this->actions[this->nActions].enabled = bVar3;
        iVar5 = Fad_ReadInt(&local_28);
        this->actions[this->nActions].b12 = (byte)iVar5;
      }
      this->nActions = this->nActions + 1;
    }
  } while (!bVar1);
  *param_2 = local_28;
  return;
}


// 0001b414 LoadZoom

void LoadZoom(Zoom *this,char **param_2)

{
  bool bVar1;
  char cVar2;
  CString *pCVar3;
  char *local_1c;
  CString CStack_18;
  CString CStack_14;
  
  local_1c = *param_2;
  CString_CtorA(&CStack_18,s_zoom__00043bb0);
  pCVar3 = CString_Plus(&CStack_14,&g_installDir,&CStack_18);
  CString_Assign(&this->path,pCVar3);
  CString_Dtor(&CStack_14);
  CString_Dtor(&CStack_18);
  pCVar3 = Fad_ReadString(&CStack_14,&local_1c);
  CString_Append(&this->path,pCVar3);
  CString_Dtor(&CStack_14);
  this->loaded = 0;
  bVar1 = false;
  this->count = 0;
  do {
    cVar2 = Fad_ReadCharAfterUnderscore(&local_1c);
    if (cVar2 == 'F') {
      bVar1 = true;
    }
    else if (cVar2 == 'O') {
      LoadSprite(this->recs + this->count,&local_1c,'\x01');
      this->count = this->count + 1;
    }
  } while (!bVar1);
  *param_2 = local_1c;
  return;
}


// 0001b508 Rec15c_Parse

void Rec15c_Parse(Rec15c *this,char **param_2)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  CString *pCVar5;
  int iVar6;
  int iVar7;
  char *local_44;
  CString local_40;
  CString local_3c;
  CString local_38;
  CString local_34;
  CString CStack_30;
  CString CStack_2c;
  CString CStack_28;
  
  local_40.str = g_afxEmptyString;
  Rec15c_ResetStates(this);
  local_44 = *param_2;
  bVar2 = false;
  pCVar5 = Fad_ReadString(&CStack_30,&local_44);
  CString_Assign(&this->title,pCVar5);
  CString_Dtor(&CStack_30);
  CString_CtorA(&local_3c,&g_emptyA);
  iVar6 = wcscmp((this->title).str,local_3c.str);
  CString_Dtor(&local_3c);
  if (iVar6 == 0) {
    CString_AssignA(&this->title,s_space);
  }
  this->count = 0;
  this->script = 0xff;
  this->choices[0].active = 0;
  do {
    cVar3 = Fad_ReadCharAfterUnderscore(&local_44);
    if (cVar3 == 'F') {
      bVar2 = true;
    }
    else if (cVar3 == 'P') {
      pCVar5 = Fad_ReadString(&CStack_30,&local_44);
      CString_Assign(&this->choices[this->count].text,pCVar5);
      CString_Dtor(&CStack_30);
      bVar1 = false;
      do {
        cVar3 = Fad_ReadCharAfterUnderscore(&local_44);
        if (cVar3 == 'A') {
          iVar6 = Fad_ReadInt(&local_44);
          this->choices[this->count].replies[this->choices[this->count].active - 1].b5 = (byte)iVar6
          ;
        }
        else if (cVar3 == 'F') {
          bVar1 = true;
        }
        else if (cVar3 == 'R') {
          pCVar5 = Fad_ReadString(&CStack_2c,&local_44);
          CString_Assign(&this->choices[this->count].replies[this->choices[this->count].active].text
                         ,pCVar5);
          CString_Dtor(&CStack_2c);
          pCVar5 = Fad_ReadString(&CStack_28,&local_44);
          CString_Assign(&local_40,pCVar5);
          CString_Dtor(&CStack_28);
          CString_CtorA(&local_38,s_ON_00043ba0);
          iVar6 = wcscmp(local_40.str,local_38.str);
          CString_Dtor(&local_38);
          if (iVar6 == 0) {
            this->choices[this->count].replies[this->choices[this->count].active].val = 0;
          }
          else {
            CString_CtorA(&local_34,s_OFF_00043b9c);
            iVar6 = wcscmp(local_40.str,local_34.str);
            CString_Dtor(&local_34);
            iVar7 = 1;
            if (iVar6 != 0) {
              iVar7 = 2;
            }
            this->choices[this->count].replies[this->choices[this->count].active].val = iVar7;
          }
          iVar6 = Fad_ReadInt(&local_44);
          this->choices[this->count].replies[this->choices[this->count].active].b4 = (byte)iVar6;
          this->choices[this->count].replies[this->choices[this->count].active].b5 = 0xff;
          this->choices[this->count].active = this->choices[this->count].active + 1;
        }
      } while (!bVar1);
      bVar4 = this->count + 1;
      this->count = bVar4;
      this->choices[bVar4].active = 0;
    }
    else if (cVar3 == 'S') {
      iVar6 = Fad_ReadInt(&local_44);
      this->script = (byte)iVar6;
    }
  } while (!bVar2);
  *param_2 = local_44;
  CString_Dtor(&local_40);
  return;
}


// 0001b848 Fad_ReadPairs10

void Fad_ReadPairs10(char **param_1,Link *param_2)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  byte *pbVar4;
  ushort uVar5;
  char *pcVar6;
  byte bVar7;
  ushort uVar8;
  
  pcVar6 = *param_1;
  uVar3 = 0;
  do {
    param_2[uVar3].id = 0;
    param_2[uVar3].script = 0xff;
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 10);
  uVar3 = 0;
  for (; *pcVar6 != '#'; pcVar6 = pcVar6 + 1) {
  }
  pbVar4 = (byte *)(pcVar6 + 1);
  bVar2 = false;
  do {
    uVar8 = 0;
    for (; ((uVar5 = (ushort)*pbVar4, uVar5 != 0x2c && (uVar5 != 0x23)) && (uVar5 != 0x3a));
        pbVar4 = pbVar4 + 1) {
      uVar8 = (uVar8 * 10 + uVar5) - 0x30;
    }
    if (*pbVar4 == 0x3a) {
      bVar7 = 0;
      while( true ) {
        pbVar4 = pbVar4 + 1;
        bVar1 = *pbVar4;
        if (((bVar1 == 0x2c) || (bVar1 == 0x23)) || (bVar1 == 0x3a)) break;
        bVar7 = (bVar7 * '\n' + bVar1) - 0x30;
      }
    }
    else {
      bVar7 = 0xff;
    }
    bVar1 = *pbVar4;
    pbVar4 = pbVar4 + 1;
    param_2[uVar3].id = uVar8;
    if (bVar1 == 0x23) {
      bVar2 = true;
    }
    param_2[uVar3].script = bVar7;
    uVar3 = uVar3 + 1 & 0xff;
  } while (!bVar2);
  *param_1 = (char *)pbVar4;
  return;
}


// 0001b954 ExecSceneScript

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void ExecSceneScript(Scene *this,char *param_2,char param_3)

{
  bool bVar1;
  char cVar2;
  CString *pCVar3;
  int iVar4;
  wchar_t *pwVar5;
  ScriptOpList *pSVar6;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  char *local_494;
  CString local_490;
  CString local_48c;
  CString CStack_488;
  CString local_484;
  CString local_480;
  ScriptOpList SStack_47c;
  
  local_490.str = g_afxEmptyString;
  local_494 = param_2;
  pCVar3 = Fad_ReadString(&CStack_488,&local_494);
  CString_Assign((CString *)this,pCVar3);
  CString_Dtor(&CStack_488);
  pCVar3 = Fad_ReadString(&CStack_488,&local_494);
  CString_Assign(&local_490,pCVar3);
  CString_Dtor(&CStack_488);
  CString_CtorA(&local_480,s_P_00043bbc);
  iVar4 = wcscmp(local_490.str,local_480.str);
  CString_Dtor(&local_480);
  if (iVar4 == 0) {
    this->kind = 0;
  }
  else {
    CString_CtorA(&local_484,s_D_00043bb8);
    iVar4 = wcscmp(local_490.str,local_484.str);
    CString_Dtor(&local_484);
    iVar7 = 1;
    if (iVar4 != 0) {
      iVar7 = 2;
    }
    this->kind = iVar7;
  }
  CString_CtorA(&CStack_488,s_images__00043b7c);
  pCVar3 = CString_Plus(&local_48c,&g_installDir,&CStack_488);
  CString_Assign(&local_490,pCVar3);
  CString_Dtor(&local_48c);
  CString_Dtor(&CStack_488);
  pCVar3 = Fad_ReadString(&local_48c,&local_494);
  CString_Append(&local_490,pCVar3);
  CString_Dtor(&local_48c);
  if (param_3 != '\0') {
    pwVar5 = CString_GetBuffer(&local_490,*(int *)(local_490.str + -4));
    CString_CtorW(&local_48c,pwVar5);
    LoadImage(local_48c,&(this->bg).h,&(this->bg).w,&(this->bg).pixels,1);
  }
  (this->bg).x = 0;
  (this->bg).y = 0;
  Fad_ReadPairs10(&local_494,this->exits);
  bVar1 = Fad_ReadBool(&local_494);
  this->f12596[1] = bVar1;
  bVar1 = Fad_ReadBool(&local_494);
  *(bool *)&this->nScripts = bVar1;
  Fad_ReadBool(&local_494);
  iVar4 = Fad_ReadInt(&local_494);
  this->f12596[2] = (byte)iVar4;
  iVar4 = Fad_ReadInt(&local_494);
  this->f12596[4] = (byte)iVar4;
  bVar1 = Fad_ReadBool(&local_494);
  this->f12596[3] = bVar1;
  iVar4 = Fad_ReadInt(&local_494);
  this->f12596[6] = (byte)iVar4;
  bVar1 = Fad_ReadBool(&local_494);
  uVar8 = 0;
  this->curStr = 0;
  this->f12596[5] = bVar1;
  do {
    pCVar3 = Fad_ReadString(&local_48c,&local_494);
    CString_Assign(this->strs + uVar8,pCVar3);
    CString_Dtor(&local_48c);
    uVar8 = uVar8 + 1 & 0xff;
  } while (uVar8 < 3);
  pbVar10 = &this->nObjs;
  *pbVar10 = 0;
  pbVar9 = &this->nExits;
  *pbVar9 = 0;
  bVar1 = false;
  pbVar11 = this->f12596;
  *pbVar11 = 0;
  pbVar12 = &this->f1494;
  *pbVar12 = 0;
  do {
    cVar2 = Fad_ReadCharAfterUnderscore(&local_494);
    if (cVar2 == 'A') {
      pSVar6 = (ScriptOpList *)ParseSceneScript(&SStack_47c,&local_494);
      ScriptOpList_Assign(this->scripts + *pbVar11,pSVar6);
      ScriptOpList_Dtor(&SStack_47c);
      *pbVar11 = *pbVar11 + 1;
    }
    else if (cVar2 == 'D') {
      Rec15c_Parse(this->topics + *pbVar12,&local_494);
      *pbVar12 = *pbVar12 + 1;
    }
    else if (cVar2 == 'F') {
      bVar1 = true;
    }
    else if (cVar2 == 'O') {
      LoadSprite(this->objs + *pbVar10,&local_494,param_3);
      *pbVar10 = *pbVar10 + 1;
    }
    else if (cVar2 == 'Z') {
      Zoom_SetSlot(this->zooms + *pbVar9,*pbVar9);
      LoadZoom(this->zooms + *pbVar9,&local_494);
      *pbVar9 = *pbVar9 + 1;
    }
  } while (!bVar1);
  CString_Dtor(&local_490);
  return;
}


// 0001bd78 ScriptOpList_Assign

int ScriptOpList_Assign(ScriptOpList *this,ScriptOpList *param_2)

{
  ScriptOpList *this_00;
  int iVar1;
  
  iVar1 = 0x19;
  this_00 = this;
  do {
    ScriptOp_Assign(this_00->ops,(ScriptOp *)(((int)param_2 - (int)this) + (int)this_00));
    iVar1 = iVar1 + -1;
    this_00 = (ScriptOpList *)(this_00->ops + 1);
  } while (iVar1 != 0);
  *(char *)&this->count = (char)param_2->count;
  return (int)this;
}


// 0001bdc4 ScriptOp_Assign

ScriptOp * ScriptOp_Assign(ScriptOp *this,ScriptOp *param_2)

{
  byte *pbVar1;
  CString *this_00;
  int iVar2;
  
  this->op = param_2->op;
  pbVar1 = this->list;
  this->b4 = param_2->b4;
  this->arg = param_2->arg;
  this->arg2 = param_2->arg2;
  this->ba = param_2->ba;
  this->bb = param_2->bb;
  this->bc = param_2->bc;
  this->bd = param_2->bd;
  this->i10 = param_2->i10;
  this->b14 = param_2->b14;
  do {
    *pbVar1 = pbVar1[(int)param_2 - (int)this];
    pbVar1 = pbVar1 + 1;
  } while (pbVar1 + (-0x15 - (int)this) < (byte *)0x8);
  this_00 = this->str;
  iVar2 = 3;
  do {
    CString_Assign(this_00,(CString *)((int)this_00 + ((int)param_2 - (int)this)));
    iVar2 = iVar2 + -1;
    this_00 = this_00 + 1;
  } while (iVar2 != 0);
  return this;
}


// 0001be70 WaitForPenDown

void WaitForPenDown(short *param_1,short *param_2)

{
  tagMSG tStack_30;
  
  tStack_30.message = 0;
  PeekMessageW(&tStack_30,(HWND)0x0,0,0,1);
  while (tStack_30.message != 0x201) {
    PeekMessageW(&tStack_30,(HWND)0x0,0,0,1);
  }
  *param_1 = (short)tStack_30.lParam;
  *param_2 = (short)((uint)tStack_30.lParam >> 0x10);
  return;
}


// 0001bef4 WaitForPenUp

void WaitForPenUp(short *param_1,short *param_2)

{
  tagMSG tStack_30;
  
  tStack_30.message = 0;
  PeekMessageW(&tStack_30,(HWND)0x0,0,0,1);
  while (tStack_30.message != 0x202) {
    PeekMessageW(&tStack_30,(HWND)0x0,0,0,1);
  }
  *param_1 = (short)tStack_30.lParam;
  *param_2 = (short)((uint)tStack_30.lParam >> 0x10);
  return;
}


// 0001bf78 FlushInputMessages

void FlushInputMessages(void)

{
  BOOL BVar1;
  tagMSG tStack_24;
  
  do {
    BVar1 = PeekMessageW(&tStack_24,(HWND)0x0,0x100,0x108,1);
  } while (BVar1 != 0);
  do {
    BVar1 = PeekMessageW(&tStack_24,(HWND)0x0,0x200,0x209,1);
  } while (BVar1 != 0);
  return;
}


// 0001bfd0 RandomRange

char RandomRange(char param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = __itos((int)param_1);
  do {
    rand();
    uVar3 = __itos();
    uVar3 = __muls(uVar3,uVar2);
    __muls(uVar3,0x38000100);
    cVar1 = __stoi();
  } while ((int)cVar1 == (int)param_1);
  return cVar1;
}


// 0001c064 TextList_Ctor

int TextList_Ctor(TextList *this)

{
  StrList_Init(&this->lines,10);
  return (int)this;
}


// 0001c080 StrList_Init

void StrList_Init(StrList *this,int param_2)

{
  this->blockSize = param_2;
  *(undefined1 *)&this->vtbl = 0;
  *(undefined1 *)((int)&this->vtbl + 1) = 0;
  this->count = 0;
  this->free = (StrNode *)0x0;
  *(undefined1 *)((int)&this->vtbl + 2) = 4;
  this->tail = (StrNode *)0x0;
  this->head = (StrNode *)0x0;
  *(undefined1 *)((int)&this->vtbl + 3) = 0;
  this->blocks = (void *)0x0;
  return;
}


// 0001c0c4 StrList_Serialize

void StrList_Serialize(StrList *this,CArchive *param_2)

{
  uint uVar1;
  StrNode *pSVar2;
  StrItem local_20;
  
  if ((param_2->mode & 1) == 0) {
    CArchive_WriteCount(param_2,this->count);
    for (pSVar2 = this->head; pSVar2 != (StrNode *)0x0; pSVar2 = pSVar2->next) {
      StrList_SerializeElements(param_2,&pSVar2->item,1);
    }
  }
  else {
    uVar1 = CArchive_ReadCount(param_2);
    local_20.text.str = g_afxEmptyString;
    for (; g_afxEmptyString = local_20.text.str, uVar1 != 0; uVar1 = uVar1 - 1) {
      StrList_SerializeElements(param_2,&local_20,1);
      StrList_AddTail(this,&local_20);
      CString_Dtor(&local_20.text);
      local_20.text.str = g_afxEmptyString;
    }
  }
  return;
}


// 0001c168 StrList_AddTail

int StrList_AddTail(StrList *this,StrItem *param_2)

{
  StrNode *pSVar1;
  
  pSVar1 = StrList_NewNode(this,this->tail,0);
  CString_Assign(&(pSVar1->item).text,&param_2->text);
  (pSVar1->item).val = param_2->val;
  (pSVar1->item).flag = param_2->flag;
  if (this->tail == (StrNode *)0x0) {
    this->head = pSVar1;
  }
  else {
    this->tail->next = pSVar1;
  }
  this->tail = pSVar1;
  return (int)pSVar1;
}


// 0001c1c0 StrList_DeletingDtor

StrList * StrList_DeletingDtor(StrList *this,uint param_2)

{
  *(undefined1 *)&this->vtbl = 0;
  *(undefined1 *)((int)&this->vtbl + 1) = 0;
  *(undefined1 *)((int)&this->vtbl + 2) = 4;
  *(undefined1 *)((int)&this->vtbl + 3) = 0;
  StrList_RemoveAll(this);
  if ((param_2 & 1) != 0) {
    free(this);
  }
  return this;
}


// 0001c20c StrList_RemoveAll

void StrList_RemoveAll(StrList *this)

{
  StrNode *pSVar1;
  
  for (pSVar1 = this->head; pSVar1 != (StrNode *)0x0; pSVar1 = pSVar1->next) {
    StrList_DestructElements((StrList *)&pSVar1->item,1);
  }
  this->count = 0;
  this->free = (StrNode *)0x0;
  this->tail = (StrNode *)0x0;
  this->head = (StrNode *)0x0;
  CPlex_FreeDataChain(this->blocks);
  this->blocks = (void *)0x0;
  return;
}


// 0001c258 StrList_NewNode

StrNode * StrList_NewNode(StrList *this,StrNode *param_2,StrNode *param_3)

{
  int iVar1;
  int iVar2;
  StrNode *pSVar3;
  
  if (this->free == (StrNode *)0x0) {
    iVar1 = CPlex_Create(&this->blocks,this->blockSize,0x14);
    iVar2 = this->blockSize;
    pSVar3 = (StrNode *)(iVar2 * 0x14 + iVar1 + -0x10);
    if (-1 < iVar2 + -1) {
      do {
        iVar2 = iVar2 + -1;
        pSVar3->next = this->free;
        this->free = pSVar3;
        pSVar3 = pSVar3 + -1;
      } while (iVar2 != 0);
    }
  }
  pSVar3 = this->free;
  this->free = pSVar3->next;
  pSVar3->prev = param_2;
  pSVar3->next = param_3;
  this->count = this->count + 1;
  StrList_ConstructElements((StrList *)&pSVar3->item,1);
  return pSVar3;
}


// 0001c2fc StrList_DestructElements

void StrList_DestructElements(StrList *this,int param_2)

{
  for (; param_2 != 0; param_2 = param_2 + -1) {
    CString_Dtor((CString *)this);
    this = (StrList *)&this->count;
  }
  return;
}


// 0001c32c StrList_SerializeElements

void StrList_SerializeElements(CArchive *this,void *param_2,int param_3)

{
  if ((this->mode & 1) == 0) {
    CArchive_Write(this,param_2,param_3 * 0xc);
  }
  else {
    CArchive_Read(this,param_2,param_3 * 0xc);
  }
  return;
}


// 0001c358 StrList_ConstructElements

void StrList_ConstructElements(StrList *this,int param_2)

{
  memset(this,0,param_2 * 0xc);
  for (; param_2 != 0; param_2 = param_2 + -1) {
    if (this != (StrList *)0x0) {
      this->vtbl = g_afxEmptyString;
    }
    this = (StrList *)&this->count;
  }
  return;
}


// 0001c3a4 TextList_Reset

void TextList_Reset(TextList *this)

{
  *(undefined1 *)&(this->lines).vtbl = 0;
  *(undefined1 *)((int)&(this->lines).vtbl + 1) = 0;
  *(undefined1 *)((int)&(this->lines).vtbl + 2) = 4;
  *(undefined1 *)((int)&(this->lines).vtbl + 3) = 0;
  StrList_RemoveAll(&this->lines);
  return;
}


// 0001c3d0 TextList_Init

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void TextList_Init(TextList *this,FontGlyphs *param_2,int param_3,int param_4,int param_5,
                  int param_6,CString param_7,Screen *param_8)

{
  bool bVar1;
  byte bVar2;
  FontGlyphs *pFVar3;
  byte *pbVar4;
  undefined4 uVar5;
  ushort *puVar6;
  Screen *pSVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  CString local_28;
  
  this->x = param_3;
  this->top_y = param_4;
  this->font = param_2;
  this->right = param_5;
  this->bottom = param_6;
  CString_CopyCtor(&local_28,&param_7);
  LoadImage(local_28,&this->h,&this->w,&this->img,1);
  pFVar3 = this->font;
  this->screen = param_8;
  this->top = 0;
  uVar5._0_1_ = pFVar3->glyphs[0].w;
  uVar5._1_1_ = pFVar3->glyphs[0].h;
  uVar5._2_2_ = *(undefined2 *)&pFVar3->glyphs[0].field_0x2;
  puVar6 = pFVar3->glyphs[0].pixels;
  pSVar7 = pFVar3->glyphs[0].screen;
  pbVar4 = &pFVar3->glyphs[0].keyed;
  iVar8 = 0xfe4;
  pbVar10 = &stack0xffffeff4;
  do {
    iVar9 = iVar8 + -1;
    *pbVar10 = *pbVar4;
    bVar1 = 0 < iVar8;
    pbVar4 = pbVar4 + 1;
    iVar8 = iVar9;
    pbVar10 = pbVar10 + 1;
  } while (iVar9 != 0 && bVar1);
  bVar2 = TextList_CalcLinesPerPage(this,uVar5,puVar6,pSVar7);
  this->page = bVar2;
  CString_Dtor(&param_7);
  return;
}


// 0001c4c4 TextList_SetRect

void TextList_SetRect(TextList *this,int param_2,int param_3,int param_4,int param_5,
                     FontGlyphs *param_6)

{
  this->right = param_4;
  this->x = param_2;
  this->bottom = param_5;
  this->top_y = param_3;
  this->font = param_6;
  return;
}


// 0001c4e4 TextList_SetFont

void TextList_SetFont(TextList *this,FontGlyphs *param_2)

{
  bool bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined4 uVar4;
  ushort *puVar5;
  Screen *pSVar6;
  int iVar7;
  int iVar8;
  byte *pbVar9;
  byte abStack_ff4 [4068];
  
  this->font = param_2;
  this->top = 0;
  uVar4._0_1_ = param_2->glyphs[0].w;
  uVar4._1_1_ = param_2->glyphs[0].h;
  uVar4._2_2_ = *(undefined2 *)&param_2->glyphs[0].field_0x2;
  puVar5 = param_2->glyphs[0].pixels;
  pSVar6 = param_2->glyphs[0].screen;
  pbVar3 = &param_2->glyphs[0].keyed;
  iVar7 = 0xfe4;
  pbVar9 = abStack_ff4;
  do {
    iVar8 = iVar7 + -1;
    *pbVar9 = *pbVar3;
    bVar1 = 0 < iVar7;
    pbVar3 = pbVar3 + 1;
    iVar7 = iVar8;
    pbVar9 = pbVar9 + 1;
  } while (iVar8 != 0 && bVar1);
  bVar2 = TextList_CalcLinesPerPage(this,uVar4,puVar5,pSVar6);
  this->page = bVar2;
  return;
}


// 0001c550 TextList_Clear

void TextList_Clear(TextList *this)

{
  StrList_RemoveAll(&this->lines);
  this->count = 0;
  this->top = 0;
  return;
}


// 0001c570 TextList_SetText

void TextList_SetText(TextList *this,CString param_2)

{
  int iVar1;
  CString local_20;
  CString local_c [3];
  
  local_c[0].str = param_2.str;
  TextList_Clear(this);
  iVar1 = *(int *)(local_c[0].str + -4);
  if (iVar1 < 1) {
    TextList_Clear(this);
  }
  else {
    CString_CopyCtor(&local_20,local_c);
    TextList_WrapText(this,local_20,this->font,'\0');
    this->count = (byte)(this->lines).count;
  }
  this->hasText = 0 < iVar1;
  CString_Dtor(local_c);
  return;
}


// 0001c5e8 TextList_AppendText

void TextList_AppendText(TextList *this,CString param_2,int param_3,char param_4)

{
  int iVar1;
  CString local_28;
  CString local_c;
  int iStack_8;
  int iStack_4;
  
  iStack_4 = (int)param_4;
  iVar1 = *(int *)(param_2.str + -4);
  local_c.str = param_2.str;
  iStack_8 = param_3;
  if (0 < iVar1) {
    CString_CopyCtor(&local_28,&local_c);
    TextList_WrapText(this,local_28,(FontGlyphs *)param_3,param_4);
    this->count = (byte)(this->lines).count;
  }
  this->hasText = 0 < iVar1;
  CString_Dtor(&local_c);
  return;
}


// 0001c65c TextList_SetLineTag

void TextList_SetLineTag(TextList *this,char param_2,int param_3)

{
  StrNode *pSVar1;
  int iVar2;
  
  iVar2 = (int)param_2;
  if (iVar2 < (int)(uint)this->count) {
    if ((iVar2 < (this->lines).count) && (-1 < iVar2)) {
      pSVar1 = (this->lines).head;
      for (; iVar2 != 0; iVar2 = iVar2 + -1) {
        pSVar1 = pSVar1->next;
      }
    }
    else {
      pSVar1 = (StrNode *)0x0;
    }
    (pSVar1->item).val = param_3;
  }
  return;
}


// 0001c6b0 TextList_CalcLinesPerPage

undefined1
TextList_CalcLinesPerPage(TextList *this,undefined4 param_2,ushort *param_3,Screen *param_4)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uStack_c;
  ushort *puStack_8;
  Screen *pSStack_4;
  
  uStack_c = param_2;
  puStack_8 = param_3;
  pSStack_4 = param_4;
  uVar2 = Font_MaxGlyphWidth((int)&uStack_c);
  uVar1 = __rt_sdiv(uVar2 & 0xff,this->bottom - this->top_y & 0xff);
  FontGlyphs_Dtor((FontGlyphs *)&uStack_c);
  return uVar1;
}


// 0001c704 TextList_SetDialogMenu

void TextList_SetDialogMenu
               (TextList *this,int param_2,FontGlyphs *param_3,FontGlyphs *param_4,
               FontGlyphs *param_5,char param_6)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  CString *pCVar4;
  CString CVar5;
  FontGlyphs *pFVar6;
  uint uVar7;
  CString local_6c;
  CString local_68;
  CString local_64 [2];
  Rec44 RStack_5c;
  
  bVar3 = this->top;
  local_6c.str = g_afxEmptyString;
  TextList_Clear(this);
  this->top = bVar3;
  pCVar4 = Rec15c_GetName((Rec15c *)param_2,&local_68);
  CString_Assign(&local_6c,pCVar4);
  CString_Dtor(&local_68);
  CString_CtorA(&local_68,s__00043bc0);
  CString_Append(&local_6c,&local_68);
  CString_Dtor(&local_68);
  CString_CopyCtor(local_64,&local_6c);
  TextList_AppendText(this,local_64[0],(int)param_3,'\0');
  cVar1 = Rec15c_GetCount((Rec15c *)param_2);
  if (cVar1 != '\0') {
    uVar7 = 0;
    do {
      bVar2 = Rec44_AnyActive((Rec44 *)param_2,uVar7);
      if (bVar2) {
        pCVar4 = (CString *)Rec15c_GetRec44((Rec15c *)param_2,(int)&RStack_5c,uVar7);
        CString_Assign(&local_6c,pCVar4);
        Rec44_Dtor(&RStack_5c);
        if ((int)param_6 == uVar7) {
          CString_CopyCtor(&local_68,&local_6c);
          CVar5.str = local_68.str;
          pFVar6 = param_5;
        }
        else {
          CString_CopyCtor(local_64,&local_6c);
          CVar5.str = local_64[0].str;
          pFVar6 = param_4;
        }
        TextList_AppendText(this,CVar5,(int)pFVar6,'\x02');
      }
      uVar7 = uVar7 + 1 & 0xff;
      bVar3 = Rec15c_GetCount((Rec15c *)param_2);
    } while (uVar7 < bVar3);
  }
  CString_Dtor(&local_6c);
  return;
}


// 0001c864 TextList_SetDialogTitle

void TextList_SetDialogTitle(TextList *this,Rec15c *param_2,FontGlyphs *param_3)

{
  CString *pCVar1;
  CString local_1c;
  CString CStack_18;
  CString local_14;
  
  local_1c.str = g_afxEmptyString;
  TextList_Clear(this);
  pCVar1 = Rec15c_GetName(param_2,&CStack_18);
  CString_Assign(&local_1c,pCVar1);
  CString_Dtor(&CStack_18);
  CString_CtorA(&CStack_18,s__00043bc0);
  CString_Append(&local_1c,&CStack_18);
  CString_Dtor(&CStack_18);
  CString_CopyCtor(&local_14,&local_1c);
  TextList_AppendText(this,local_14,(int)param_3,'\0');
  CString_Dtor(&local_1c);
  return;
}


// 0001c904 TextList_SetDialogMenu2

void TextList_SetDialogMenu2
               (TextList *this,int param_2,FontGlyphs *param_3,FontGlyphs *param_4,
               FontGlyphs *param_5,char param_6)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  CString *pCVar4;
  CString CVar5;
  FontGlyphs *pFVar6;
  uint uVar7;
  CString local_6c;
  CString local_68;
  CString local_64 [2];
  Rec44 RStack_5c;
  
  bVar3 = this->top;
  local_6c.str = g_afxEmptyString;
  TextList_Clear(this);
  this->top = bVar3;
  pCVar4 = Rec15c_GetName((Rec15c *)param_2,&local_68);
  CString_Assign(&local_6c,pCVar4);
  CString_Dtor(&local_68);
  CString_CtorA(&local_68,s__00043bc0);
  CString_Append(&local_6c,&local_68);
  CString_Dtor(&local_68);
  CString_CopyCtor(local_64,&local_6c);
  TextList_AppendText(this,local_64[0],(int)param_3,'\0');
  cVar1 = Rec15c_GetCount((Rec15c *)param_2);
  if (cVar1 != '\0') {
    uVar7 = 0;
    do {
      bVar2 = Rec44_AnyActive((Rec44 *)param_2,uVar7);
      if (bVar2) {
        pCVar4 = (CString *)Rec15c_GetRec44((Rec15c *)param_2,(int)&RStack_5c,uVar7);
        CString_Assign(&local_6c,pCVar4);
        Rec44_Dtor(&RStack_5c);
        if ((int)param_6 == uVar7) {
          CString_CopyCtor(&local_68,&local_6c);
          CVar5.str = local_68.str;
          pFVar6 = param_5;
        }
        else {
          CString_CopyCtor(local_64,&local_6c);
          CVar5.str = local_64[0].str;
          pFVar6 = param_4;
        }
        TextList_AppendText(this,CVar5,(int)pFVar6,'\x02');
      }
      uVar7 = uVar7 + 1 & 0xff;
      bVar3 = Rec15c_GetCount((Rec15c *)param_2);
    } while (uVar7 < bVar3);
  }
  CString_Dtor(&local_6c);
  return;
}


// 0001ca64 TextList_SetDialogReply

void TextList_SetDialogReply(TextList *this,wchar_t *param_2,int param_3,undefined4 param_4)

{
  char in_stack_00000038;
  int in_stack_00000040;
  CString local_24;
  CString local_20;
  CString CStack_c;
  int iStack_8;
  undefined4 uStack_4;
  
  local_24.str = g_afxEmptyString;
  CStack_c.str = param_2;
  iStack_8 = param_3;
  uStack_4 = param_4;
  TextList_Clear(this);
  CString_AssignA(&local_24,&g_emptyA);
  CString_Assign(&local_24,(CString *)(&stack0x00000000 + in_stack_00000038 * 0xc));
  CString_CopyCtor(&local_20,&local_24);
  TextList_AppendText(this,local_20,in_stack_00000040,'\0');
  CString_Dtor(&local_24);
  Rec44_Dtor((Rec44 *)&CStack_c);
  return;
}


// 0001caf8 TextList_GetLineCount

byte TextList_GetLineCount(TextList *this)

{
  return (byte)(this->lines).count;
}


// 0001cb00 TextList_PageUp

bool TextList_PageUp(TextList *this)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = this->top;
  bVar2 = this->page;
  if (bVar2 <= bVar1) {
    this->top = bVar1 - bVar2;
  }
  else {
    this->top = 0;
  }
  return bVar2 <= bVar1;
}


// 0001cb30 TextList_PageDown

bool TextList_PageDown(TextList *this)

{
  bool bVar1;
  
  bVar1 = (int)(uint)this->top < (int)((uint)this->count - (uint)this->page);
  if (bVar1) {
    this->top = this->top + this->page;
  }
  return bVar1;
}


// 0001cb58 TextList_LineUp

bool TextList_LineUp(TextList *this)

{
  byte bVar1;
  
  bVar1 = this->top;
  if (bVar1 != 0) {
    this->top = bVar1 - 1;
  }
  return bVar1 != 0;
}


// 0001cb74 TextList_LineDown

bool TextList_LineDown(TextList *this)

{
  bool bVar1;
  
  bVar1 = (int)(uint)this->top < (int)((uint)this->count - (uint)this->page);
  if (bVar1) {
    this->top = this->top + 1;
  }
  return bVar1;
}


// 0001cb9c TextList_AtEnd

bool TextList_AtEnd(TextList *this)

{
  return (uint)this->count <= (uint)this->top + (uint)this->page;
}


// 0001cbc0 Text_DrawLine

void Text_DrawLine(TextList *this,CString param_2,FontGlyphs *param_3,undefined4 param_4,int param_5
                  ,char param_6)

{
  wchar_t wVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  CString local_c;
  FontGlyphs *local_8;
  undefined4 uStack_4;
  
  iVar4 = this->x;
  local_c.str = param_2.str;
  local_8 = param_3;
  uStack_4 = param_4;
  for (iVar3 = 0; iVar3 = (int)(char)iVar3, iVar3 < *(int *)(local_c.str + -4);
      iVar3 = (iVar3 + 1) * 0x1000000 >> 0x18) {
    wVar1 = local_c.str[iVar3];
    Glyph_BlitToLayer(local_8->glyphs + (byte)wVar1,param_6,iVar4,param_5);
    bVar2 = Glyph_GetW(local_8->glyphs + (byte)wVar1);
    iVar4 = (uint)bVar2 + iVar4;
  }
  CString_Dtor(&local_c);
  return;
}


// 0001cc40 Text_TypeLine

int Text_TypeLine(TextList *this,CString param_2,FontGlyphs *param_3,undefined4 param_4,uint param_5
                 ,char param_6,char param_7)

{
  wchar_t wVar1;
  byte bVar2;
  int iVar3;
  BOOL BVar4;
  uint uVar5;
  int iVar6;
  tagMSG tStack_44;
  CString local_c;
  FontGlyphs *local_8;
  undefined4 uStack_4;
  
  uVar5 = this->x;
  iVar6 = 1;
  local_c.str = param_2.str;
  local_8 = param_3;
  uStack_4 = param_4;
  for (iVar3 = 0; iVar3 = (int)(char)iVar3, iVar3 < *(int *)(local_c.str + -4);
      iVar3 = (iVar3 + 1) * 0x1000000 >> 0x18) {
    wVar1 = local_c.str[iVar3];
    Glyph_Draw(local_8->glyphs + (byte)wVar1,param_6,uVar5,param_5);
    bVar2 = Glyph_GetW(local_8->glyphs + (byte)wVar1);
    uVar5 = bVar2 + uVar5;
    if (iVar6 != 0) {
      Sleep(0x1e);
      BVar4 = PeekMessageW(&tStack_44,(HWND)0x0,0,0,1);
      if (((BVar4 != 0) && (param_7 != '\0')) &&
         ((tStack_44.message == 0x100 || (iVar6 = 1, tStack_44.message == 0x202)))) {
        iVar6 = 0;
      }
    }
  }
  CString_Dtor(&local_c);
  return iVar6;
}


// 0001cd3c TextList_DrawDirect

void TextList_DrawDirect(TextList *this)

{
  Screen_DrawDirect(this->screen,this->x,this->top_y,this->w,this->h,this->img);
  return;
}


// 0001cd70 TextList_BlitToLayer

void TextList_BlitToLayer(TextList *this,char param_2)

{
  Screen_BlitToLayer(this->screen,this->x,this->top_y,this->w,this->h,this->img,param_2);
  return;
}


// 0001cda8 TextList_Draw

void TextList_Draw(TextList *this,char param_2)

{
  uint uVar1;
  StrNode *pSVar2;
  uint uVar3;
  int iVar4;
  CString local_38;
  FontGlyphs *local_34;
  byte local_30;
  CString local_28;
  FontGlyphs *local_24;
  undefined4 local_20;
  
  local_38.str = g_afxEmptyString;
  iVar4 = this->top_y;
  uVar3 = (uint)this->top;
  if (this->hasText != 0) {
    TextList_BlitToLayer(this,param_2);
    if ((int)uVar3 < (this->lines).count) {
      pSVar2 = (this->lines).head;
      for (uVar1 = uVar3; uVar1 != 0; uVar1 = uVar1 - 1) {
        pSVar2 = pSVar2->next;
      }
    }
    else {
      pSVar2 = (StrNode *)0x0;
    }
    CString_Assign(&local_38,&(pSVar2->item).text);
    local_34 = (FontGlyphs *)(pSVar2->item).val;
    local_30 = (pSVar2->item).flag;
    while ((uVar3 = uVar3 + 1, uVar3 - this->top <= (uint)this->page && (uVar3 <= this->count))) {
      CString_CopyCtor(&local_28,&local_38);
      local_24 = local_34;
      local_20 = CONCAT31(local_20._1_3_,local_30);
      Text_DrawLine(this,local_28,local_34,local_20,iVar4,param_2);
      if (uVar3 < this->count) {
        if (((int)uVar3 < (this->lines).count) && (-1 < (int)uVar3)) {
          pSVar2 = (this->lines).head;
          for (uVar1 = uVar3; uVar1 != 0; uVar1 = uVar1 - 1) {
            pSVar2 = pSVar2->next;
          }
        }
        else {
          pSVar2 = (StrNode *)0x0;
        }
        CString_Assign(&local_38,&(pSVar2->item).text);
        local_34 = (FontGlyphs *)(pSVar2->item).val;
        local_30 = (pSVar2->item).flag;
      }
      uVar1 = Font_MaxGlyphWidth((int)this->font);
      iVar4 = (uVar1 & 0xff) + iVar4;
    }
  }
  CString_Dtor(&local_38);
  return;
}


// 0001cf38 TextList_DrawTyped

void TextList_DrawTyped(TextList *this,char param_2,char param_3)

{
  uint uVar1;
  StrNode *pSVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  CString local_50;
  FontGlyphs *local_4c;
  byte local_48;
  CString local_40;
  FontGlyphs *local_3c;
  undefined4 local_38;
  CString local_30;
  FontGlyphs *local_2c;
  undefined4 local_28;
  
  local_50.str = g_afxEmptyString;
  uVar4 = this->top_y;
  uVar5 = 1;
  uVar3 = (uint)this->top;
  if (this->hasText != 0) {
    TextList_BlitToLayer(this,param_2);
    TextList_DrawDirect(this);
    if ((int)uVar3 < (this->lines).count) {
      pSVar2 = (this->lines).head;
      for (uVar1 = uVar3; uVar1 != 0; uVar1 = uVar1 - 1) {
        pSVar2 = pSVar2->next;
      }
    }
    else {
      pSVar2 = (StrNode *)0x0;
    }
    CString_Assign(&local_50,&(pSVar2->item).text);
    local_4c = (FontGlyphs *)(pSVar2->item).val;
    local_48 = (pSVar2->item).flag;
    while ((uVar3 = uVar3 + 1, uVar3 - this->top <= (uint)this->page && (uVar3 <= this->count))) {
      if ((uVar5 & 0xff) == 0) {
        CString_CopyCtor(&local_30,&local_50);
        local_2c = local_4c;
        local_28 = CONCAT31(local_28._1_3_,local_48);
        Text_DrawLine(this,local_30,local_4c,local_28,uVar4,param_2);
      }
      else {
        CString_CopyCtor(&local_40,&local_50);
        local_3c = local_4c;
        local_38 = CONCAT31(local_38._1_3_,local_48);
        uVar5 = Text_TypeLine(this,local_40,local_4c,local_38,uVar4,param_2,param_3);
      }
      if (uVar3 < this->count) {
        if (((int)uVar3 < (this->lines).count) && (-1 < (int)uVar3)) {
          pSVar2 = (this->lines).head;
          for (uVar1 = uVar3; uVar1 != 0; uVar1 = uVar1 - 1) {
            pSVar2 = pSVar2->next;
          }
        }
        else {
          pSVar2 = (StrNode *)0x0;
        }
        CString_Assign(&local_50,&(pSVar2->item).text);
        local_4c = (FontGlyphs *)(pSVar2->item).val;
        local_48 = (pSVar2->item).flag;
      }
      uVar1 = Font_MaxGlyphWidth((int)this->font);
      uVar4 = (uVar1 & 0xff) + uVar4;
    }
  }
  CString_Dtor(&local_50);
  return;
}


// 0001d124 TextList_HitTest

int TextList_HitTest(TextList *this,uint param_2,uint param_3)

{
  int iVar1;
  
  if ((((param_3 <= (uint)this->top_y) || ((uint)this->bottom <= param_3)) ||
      (param_2 <= (uint)this->x)) || (iVar1 = 1, (uint)this->right <= param_2)) {
    iVar1 = 0;
  }
  return iVar1;
}


// 0001d164 TextList_LineAt

int TextList_LineAt(TextList *this,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = Font_MaxGlyphWidth((int)this->font);
  uVar1 = __rt_udiv(uVar1 & 0xff,param_3 - this->top_y);
  return (uVar1 & 0xff) + (uint)this->top;
}


// 0001d1a8 Text_NextWord

CString * Text_NextWord(TextList *param_1,CString *param_2,int param_3,CString param_4,
                       undefined1 *param_5)

{
  wchar_t wVar1;
  undefined1 uVar2;
  CString CStack_24;
  CString local_4;
  
  local_4.str = param_4.str;
  CString_CtorA(&CStack_24,&g_emptyA);
  for (; param_3 < *(int *)(local_4.str + -4); param_3 = param_3 + 1) {
    wVar1 = local_4.str[param_3];
    if ((wVar1 == L' ') || (wVar1 == L'\n')) break;
    CString_AppendChar(&CStack_24,wVar1);
  }
  if ((*(int *)(local_4.str + -4) <= param_3) || (uVar2 = 1, local_4.str[param_3] != L'\n')) {
    uVar2 = 0;
  }
  *param_5 = uVar2;
  CString_CopyCtor(param_2,&CStack_24);
  CString_Dtor(&CStack_24);
  CString_Dtor(&local_4);
  return param_2;
}


// 0001d260 TextList_WrapText

void TextList_WrapText(TextList *this,CString param_2,FontGlyphs *param_3,char param_4)

{
  int iVar1;
  byte bVar2;
  CString *pCVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char local_68 [4];
  CString local_64;
  CString local_60;
  CString CStack_5c;
  CString CStack_58;
  CString CStack_54;
  CString CStack_50;
  CString local_4c;
  CString CStack_48;
  CString local_44;
  StrItem local_40;
  CString local_c;
  FontGlyphs *pFStack_8;
  int iStack_4;
  
  iStack_4 = (int)param_4;
  local_64.str = g_afxEmptyString;
  uVar7 = this->x;
  iVar6 = 0;
  local_60.str = local_64.str;
  local_40.text.str = local_64.str;
  local_c.str = param_2.str;
  pFStack_8 = param_3;
  CString_AssignA(&local_64,&g_emptyA);
  iVar1 = (int)param_4;
  if (0 < iVar1) {
    iVar4 = 0;
    do {
      CString_CtorA(&CStack_5c,s_space);
      CString_Append(&local_64,&CStack_5c);
      CString_Dtor(&CStack_5c);
      bVar2 = Glyph_GetW(param_3->glyphs + 0x20);
      uVar7 = bVar2 + uVar7;
      iVar4 = (iVar4 + 1) * 0x1000000 >> 0x18;
    } while (iVar4 < iVar1);
  }
  CString_Assign(&local_40.text,&local_64);
  uVar5 = uVar7;
  local_40.val = (int)param_3;
  while (iVar6 < *(int *)(local_c.str + -4)) {
    CString_CopyCtor(&local_4c,&local_c);
    pCVar3 = Text_NextWord(this,&CStack_48,iVar6,local_4c,local_68);
    CString_Assign(&local_60,pCVar3);
    CString_Dtor(&CStack_48);
    CString_CopyCtor(&local_44,&local_60);
    bVar2 = Font_TextWidth(this->font,local_44);
    uVar5 = bVar2 + uVar5;
    if (uVar5 < (uint)this->right) {
      CString_Append(&local_40.text,&local_60);
    }
    else {
      StrList_AddTail(&this->lines,&local_40);
      CString_Assign(&local_40.text,&local_64);
      uVar5 = bVar2 + uVar7;
      if (iVar1 != 0) {
        CString_CtorA(&CStack_5c,s_space);
        CString_Append(&local_40.text,&CStack_5c);
        CString_Dtor(&CStack_5c);
        bVar2 = Glyph_GetW(param_3->glyphs + 0x20);
        uVar5 = bVar2 + uVar5;
      }
      CString_Append(&local_40.text,&local_60);
      local_40.val = (int)param_3;
    }
    if (local_68[0] != '\0') {
      StrList_AddTail(&this->lines,&local_40);
      iVar6 = iVar6 + 1;
      CString_Assign(&local_40.text,&local_64);
      uVar5 = uVar7;
      local_40.val = (int)param_3;
      if (iVar1 != 0) {
        CString_CtorA(&CStack_58,s_space);
        CString_Append(&local_40.text,&CStack_58);
        CString_Dtor(&CStack_58);
        bVar2 = Glyph_GetW(param_3->glyphs + 0x20);
        uVar5 = bVar2 + uVar7;
      }
    }
    if ((*(int *)(local_60.str + -4) + iVar6 < *(int *)(local_c.str + -4)) &&
       (local_c.str[*(int *)(local_60.str + -4) + iVar6] == L' ')) {
      bVar2 = Glyph_GetW(this->font->glyphs + 0x20);
      if (bVar2 + uVar5 < (uint)this->right) {
        CString_CtorA(&CStack_54,s_space);
        CString_Append(&local_40.text,&CStack_54);
        CString_Dtor(&CStack_54);
        bVar2 = Glyph_GetW(this->font->glyphs + 0x20);
        uVar5 = bVar2 + uVar5;
      }
      else {
        StrList_AddTail(&this->lines,&local_40);
        CString_Assign(&local_40.text,&local_64);
        uVar5 = uVar7;
        local_40.val = (int)param_3;
        if (iVar1 != 0) {
          CString_CtorA(&CStack_50,s_space);
          CString_Append(&local_40.text,&CStack_50);
          CString_Dtor(&CStack_50);
          bVar2 = Glyph_GetW(param_3->glyphs + 0x20);
          uVar5 = bVar2 + uVar7;
        }
      }
      iVar6 = iVar6 + 1;
    }
    iVar6 = *(int *)(local_60.str + -4) + iVar6;
    if (iVar6 == *(int *)(local_c.str + -4)) {
      StrList_AddTail(&this->lines,&local_40);
    }
  }
  CString_Dtor(&local_64);
  CString_Dtor(&local_60);
  CString_Dtor(&local_40.text);
  CString_Dtor(&local_c);
  return;
}


// 0001d5a8 FontGlyphs_Ctor

int FontGlyphs_Ctor(FontGlyphs *this)

{
  int iVar1;
  
  iVar1 = 0xff;
  do {
    nop_1e4c4();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return (int)this;
}


// 0001d5d8 FontGlyphs_Dtor

void FontGlyphs_Dtor(FontGlyphs *this)

{
  int iVar1;
  
  iVar1 = 0xff;
  do {
    nop_1e4c8();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 0001d600 Font_MaxGlyphWidth

uint Font_MaxGlyphWidth(int param_1)

{
  byte bVar1;
  uint uVar2;
  Glyph *this;
  uint uVar3;
  
  uVar3 = 0;
  uVar2 = 0;
  do {
    this = (Glyph *)(param_1 + uVar2 * 0x10);
    bVar1 = Glyph_GetH(this);
    if (uVar3 < bVar1) {
      bVar1 = Glyph_GetH(this);
      uVar3 = (uint)bVar1;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0xff);
  return uVar3;
}


// 0001d650 Font_ScanRowToMarker

uint Font_ScanRowToMarker
               (int param_1,uint param_2,undefined4 param_3,uint param_4,int param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  uVar1 = param_4;
  while ((uVar1 < param_2 &&
         (uVar1 = Font_IsMarkerPixel((Screen *)param_6,uVar1,param_5,param_2,param_3,param_1),
         (uVar1 & 0xff) == 0))) {
    uVar2 = uVar2 + 1 & 0xff;
    uVar1 = uVar2 + param_4;
  }
  return uVar2;
}


// 0001d6c0 Font_ScanColToMarker

uint Font_ScanColToMarker(int param_1,int param_2,uint param_3,int param_4,uint param_5,int param_6)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  uVar1 = param_5;
  while ((uVar1 < param_3 &&
         (uVar1 = Font_IsMarkerPixel((Screen *)param_6,param_4,uVar1,param_2,param_3,param_1),
         (uVar1 & 0xff) == 0))) {
    uVar2 = uVar2 + 1 & 0xff;
    uVar1 = uVar2 + param_5;
  }
  return uVar2;
}


// 0001d734 Font_ExtractGlyph

void Font_ExtractGlyph(int param_1,undefined4 *param_2,byte *param_3,undefined1 *param_4,
                      uint param_5,uint param_6,int param_7,uint *param_8,uint *param_9)

{
  undefined2 uVar1;
  bool bVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  undefined2 *puVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  byte local_3a;
  byte local_39;
  
  uVar10 = *param_8;
  uVar12 = *param_9;
  uVar13 = (uint)local_3a;
  bVar2 = false;
  bVar3 = false;
  do {
    if (bVar2) {
      return;
    }
    if (uVar10 < param_5) {
      do {
        uVar4 = Font_IsMarkerPixel((Screen *)param_7,uVar10,uVar12,param_5,param_6,param_1);
        if ((uVar4 & 0xff) == 0) break;
        uVar10 = uVar10 + 1;
      } while (uVar10 < param_5);
      if (param_5 <= uVar10) goto LAB_0001d7dc;
      bVar2 = true;
    }
    else {
LAB_0001d7dc:
      bVar3 = true;
    }
    if (!bVar3) {
      uVar4 = Font_ScanRowToMarker(param_1,param_5,param_6,uVar10,uVar12,param_7);
      local_39 = (byte)uVar4;
      uVar5 = Font_ScanColToMarker(param_1,param_5,param_6,uVar10,uVar12,param_7);
      uVar4 = uVar4 & 0xff;
      uVar11 = uVar5 & 0xff;
      puVar6 = (undefined2 *)operator_new(uVar4 * uVar11 * 2);
      puVar7 = (undefined2 *)(param_1 + (uVar12 * param_5 + uVar10) * 2);
      puVar8 = puVar6;
      uVar13 = uVar5;
      for (; uVar11 != 0; uVar11 = uVar11 - 1) {
        uVar9 = uVar4;
        if (uVar4 != 0) {
          do {
            uVar1 = *puVar7;
            uVar9 = uVar9 - 1;
            puVar7 = puVar7 + 1;
            *puVar8 = uVar1;
            puVar8 = puVar8 + 1;
          } while (uVar9 != 0);
          uVar13 = uVar5 & 0xff;
        }
        puVar7 = puVar7 + (param_5 - uVar4);
      }
      *param_2 = puVar6;
      *param_3 = local_39;
      *param_4 = (char)uVar13;
      *param_8 = uVar4 + uVar10;
    }
    if (((bVar3) || (param_5 <= local_39 + uVar10)) &&
       (uVar4 = (uVar13 & 0xff) + uVar12, uVar4 <= param_6)) {
      uVar10 = 0;
      while ((uVar4 < param_6 &&
             (uVar12 = Font_IsMarkerPixel((Screen *)param_7,0,uVar4,param_5,param_6,param_1),
             (uVar12 & 0xff) != 0))) {
        uVar4 = uVar4 + 1;
      }
      *param_9 = uVar4;
      uVar12 = uVar4;
    }
    if (bVar3) {
      return;
    }
  } while( true );
}


// 0001d958 Font_Load

void Font_Load(FontGlyphs *this,CString param_2,Screen *param_3,byte param_4)

{
  uint uVar1;
  byte local_54;
  byte local_53 [3];
  undefined4 local_50;
  uint local_4c;
  ushort *local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  CString local_38;
  CString CStack_34;
  CString CStack_c;
  Screen *pSStack_8;
  uint uStack_4;
  
  uStack_4 = (uint)param_4;
  CStack_c.str = param_2.str;
  pSStack_8 = param_3;
  CString_CopyCtor(&CStack_34,&CStack_c);
  CString_CopyCtor(&local_38,&CStack_c);
  LoadImage(local_38,(int *)&local_40,(int *)&local_3c,&local_48,0);
  uVar1 = 0;
  do {
    Glyph_SetH(this->glyphs + uVar1,0);
    Glyph_SetW(this->glyphs + uVar1,0);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0xff);
  local_4c = 0;
  uVar1 = 0x41;
  local_44 = 0;
  do {
    Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                      &local_4c,&local_44);
    Glyph_SetTarget(this->glyphs + uVar1,param_3,param_4);
    Glyph_Init(this->glyphs + uVar1,local_50,local_53[0],local_54);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0x5b);
  local_4c = 0;
  uVar1 = 0x61;
  do {
    Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                      &local_4c,&local_44);
    Glyph_SetTarget(this->glyphs + uVar1,param_3,param_4);
    Glyph_Init(this->glyphs + uVar1,local_50,local_53[0],local_54);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0x7b);
  local_4c = 0;
  uVar1 = 0x31;
  do {
    Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                      &local_4c,&local_44);
    Glyph_SetTarget(this->glyphs + uVar1,param_3,param_4);
    Glyph_Init(this->glyphs + uVar1,local_50,local_53[0],local_54);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0x3a);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x30,param_3,param_4);
  Glyph_Init(this->glyphs + 0x30,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xe7,param_3,param_4);
  Glyph_Init(this->glyphs + 0xe7,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xe2,param_3,param_4);
  Glyph_Init(this->glyphs + 0xe2,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xe0,param_3,param_4);
  Glyph_Init(this->glyphs + 0xe0,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xe9,param_3,param_4);
  Glyph_Init(this->glyphs + 0xe9,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xea,param_3,param_4);
  Glyph_Init(this->glyphs + 0xea,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xe8,param_3,param_4);
  Glyph_Init(this->glyphs + 0xe8,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xf4,param_3,param_4);
  Glyph_Init(this->glyphs + 0xf4,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xf9,param_3,param_4);
  Glyph_Init(this->glyphs + 0xf9,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0xfb,param_3,param_4);
  Glyph_Init(this->glyphs + 0xfb,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x20,param_3,param_4);
  Glyph_Init(this->glyphs + 0x20,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x21,param_3,param_4);
  Glyph_Init(this->glyphs + 0x21,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x22,param_3,param_4);
  Glyph_Init(this->glyphs + 0x22,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x2d,param_3,param_4);
  Glyph_Init(this->glyphs + 0x2d,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x27,param_3,param_4);
  Glyph_Init(this->glyphs + 0x27,local_50,local_53[0],local_54);
  Glyph_SetTarget(this->glyphs + 0x92,param_3,param_4);
  Glyph_Init(this->glyphs + 0x92,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x3f,param_3,param_4);
  Glyph_Init(this->glyphs + 0x3f,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x3b,param_3,param_4);
  Glyph_Init(this->glyphs + 0x3b,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x2c,param_3,param_4);
  Glyph_Init(this->glyphs + 0x2c,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x2e,param_3,param_4);
  Glyph_Init(this->glyphs + 0x2e,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x3a,param_3,param_4);
  Glyph_Init(this->glyphs + 0x3a,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x28,param_3,param_4);
  Glyph_Init(this->glyphs + 0x28,local_50,local_53[0],local_54);
  Font_ExtractGlyph((int)local_48,&local_50,local_53,&local_54,local_3c,local_40,(int)param_3,
                    &local_4c,&local_44);
  Glyph_SetTarget(this->glyphs + 0x29,param_3,param_4);
  Glyph_Init(this->glyphs + 0x29,local_50,local_53[0],local_54);
  free(local_48);
  CString_Dtor(&CStack_34);
  CString_Dtor(&CStack_c);
  return;
}


// 0001e3cc Font_TextWidth

char Font_TextWidth(FontGlyphs *param_1,CString param_2)

{
  char cVar1;
  int iVar2;
  char cVar3;
  CString local_c [3];
  
  cVar3 = '\0';
  local_c[0].str = param_2.str;
  for (iVar2 = 0; iVar2 = (int)(char)iVar2, iVar2 < *(int *)(local_c[0].str + -4);
      iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18) {
    cVar1 = Glyph_GetW(param_1->glyphs + (ushort)local_c[0].str[iVar2]);
    cVar3 = cVar1 + cVar3;
  }
  CString_Dtor(local_c);
  return cVar3;
}


// 0001e440 Text_CountLines

byte Text_CountLines(FontGlyphs *param_1,int param_2,int param_3,CString param_4)

{
  byte bVar1;
  CString local_74 [2];
  TextList TStack_6c;
  CString CStack_4;
  
  CStack_4.str = param_4.str;
  TextList_Ctor(&TStack_6c);
  TextList_SetRect(&TStack_6c,param_2,0,param_3,200,param_1);
  CString_CopyCtor(local_74,&CStack_4);
  TextList_SetText(&TStack_6c,local_74[0]);
  bVar1 = TextList_GetLineCount(&TStack_6c);
  TextList_Reset(&TStack_6c);
  CString_Dtor(&CStack_4);
  return bVar1;
}


// 0001e4c4 nop_1e4c4

void nop_1e4c4(void)

{
  return;
}


// 0001e4c8 nop_1e4c8

void nop_1e4c8(void)

{
  return;
}


// 0001e4cc Glyph_SetTarget

void Glyph_SetTarget(Glyph *this,Screen *param_2,byte param_3)

{
  this->screen = param_2;
  this->keyed = param_3;
  return;
}


// 0001e4d8 Glyph_GetW

byte Glyph_GetW(Glyph *this)

{
  return this->w;
}


// 0001e4e0 Glyph_GetH

byte Glyph_GetH(Glyph *this)

{
  return this->h;
}


// 0001e4e8 Glyph_IsKeyed

byte Glyph_IsKeyed(Glyph *this)

{
  return this->keyed;
}


// 0001e4f0 Glyph_SetW

void Glyph_SetW(Glyph *this,byte param_2)

{
  this->w = param_2;
  return;
}


// 0001e4f8 Glyph_SetH

void Glyph_SetH(Glyph *this,byte param_2)

{
  this->h = param_2;
  return;
}


// 0001e508 Glyph_Init

void Glyph_Init(Glyph *this,ushort *param_2,byte param_3,byte param_4)

{
  Glyph_SetW(this,param_3);
  Glyph_SetH(this,param_4);
  this->pixels = param_2;
  this->loaded = 1;
  return;
}


// 0001e53c Glyph_BlitToLayer

void Glyph_BlitToLayer(Glyph *this,char param_2,int param_3,int param_4)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  if (this->loaded != 0) {
    cVar1 = Glyph_IsKeyed(this);
    if (cVar1 == '\0') {
      bVar2 = Glyph_GetH(this);
      bVar3 = Glyph_GetW(this);
      Screen_BlitToLayer(this->screen,param_3,param_4,(uint)bVar3,(uint)bVar2,this->pixels,param_2);
    }
    else {
      bVar2 = Glyph_GetH(this);
      bVar3 = Glyph_GetW(this);
      Screen_BlitKeyedToLayer
                (this->screen,param_3,param_4,(uint)bVar3,(uint)bVar2,(short *)this->pixels,param_2)
      ;
    }
  }
  return;
}


// 0001e5ec Glyph_DrawDirect

void Glyph_DrawDirect(Glyph *this,uint param_2,uint param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  if (this->loaded != 0) {
    cVar1 = Glyph_IsKeyed(this);
    if (cVar1 == '\0') {
      bVar2 = Glyph_GetH(this);
      bVar3 = Glyph_GetW(this);
      Screen_DrawDirect(this->screen,param_2,param_3,(uint)bVar3,(uint)bVar2,this->pixels);
    }
    else {
      bVar2 = Glyph_GetH(this);
      bVar3 = Glyph_GetW(this);
      Screen_DrawKeyedDirect
                (this->screen,param_2,param_3,(uint)bVar3,(uint)bVar2,(short *)this->pixels);
    }
  }
  return;
}


// 0001e690 Glyph_Draw

void Glyph_Draw(Glyph *this,char param_2,uint param_3,uint param_4)

{
  Glyph_BlitToLayer(this,param_2,param_3,param_4);
  Glyph_DrawDirect(this,param_3,param_4);
  return;
}


// 0001e6b8 PopupMenu_Ctor

void PopupMenu_Ctor(PopupMenu *this)

{
  CString *pCVar1;
  int iVar2;
  
  pCVar1 = this->items;
  iVar2 = 0xf;
  do {
    iVar2 = iVar2 + -1;
    pCVar1->str = g_afxEmptyString;
    pCVar1 = pCVar1 + 1;
  } while (iVar2 != 0);
  return;
}


// 0001e6e8 PopupMenu_Dtor

void PopupMenu_Dtor(PopupMenu *this)

{
  CString *this_00;
  int iVar1;
  
  free(this->saved);
  this_00 = (CString *)&this->count;
  iVar1 = 0xf;
  do {
    this_00 = this_00 + -1;
    CString_Dtor(this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 0001e71c PopupMenu_ClampPos

void PopupMenu_ClampPos(PopupMenu *this)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar2 = (uint)this->posX;
  if ((uint)this->left < (uint)this->posY) {
    this->left = (uint)this->posY;
  }
  if ((uint)this->top < (uint)this->f14) {
    this->top = (uint)this->f14;
  }
  uVar3 = this->left + this->itemW + 3;
  uVar4 = uVar3;
  if (uVar2 < uVar3) {
    uVar4 = uVar2 - this->itemW;
  }
  if (uVar2 < uVar3) {
    this->left = uVar4;
  }
  iVar1 = (uint)this->count * (this->itemH + 3);
  if ((uint)this->f10 < (uint)(this->top + iVar1)) {
    this->top = ((uint)this->f10 - iVar1) + -3;
  }
  return;
}


// 0001e78c PopupMenu_Init

void PopupMenu_Init(PopupMenu *this,Screen *param_2,FontGlyphs *param_3,FontGlyphs *param_4,
                   CString param_5,byte param_6,ushort param_7,ushort param_8,ushort param_9,
                   ushort param_10)

{
  CString local_20;
  
  this->screen = param_2;
  this->font2 = param_4;
  this->font = param_3;
  CString_CopyCtor(&local_20,&param_5);
  LoadImage(local_20,&this->itemH,&this->itemW,&this->saved,1);
  this->fc = param_6;
  this->posX = param_8;
  this->f10 = param_10;
  this->posY = param_7;
  this->f14 = param_9;
  CString_Dtor(&param_5);
  return;
}


// 0001e80c PopupMenu_DrawItem

void PopupMenu_DrawItem(PopupMenu *this,uint param_2,int param_3)

{
  uint uVar1;
  CString CVar2;
  CString local_18;
  
  uVar1 = param_2 & 0xff;
  Screen_BlitToLayer(this->screen,this->itemRects[uVar1].x,this->itemRects[uVar1].y,this->itemW,
                     this->itemH,this->saved,this->fc);
  CString_CopyCtor(&local_18,this->items + uVar1);
  CVar2.str._1_1_ = local_18.str._1_1_;
  CVar2.str._0_1_ = local_18.str._0_1_;
  CVar2.str._2_1_ = local_18.str._2_1_;
  CVar2.str._3_1_ = local_18.str._3_1_;
  PopupMenu_DrawText(this,this->itemRects[uVar1].x + 2,this->itemRects[uVar1].y,param_3,CVar2);
  return;
}


// 0001e8b4 PopupMenu_HighlightItem

void PopupMenu_HighlightItem(PopupMenu *this,byte param_2)

{
  Screen_DrawShadow(this->screen,this->itemRects[param_2].x,this->itemRects[param_2].y,this->itemW,
                    this->itemH,'\0',this->fc);
  return;
}


// 0001e900 PopupMenu_ClearItems

void PopupMenu_ClearItems(PopupMenu *this)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    CString_AssignA(this->items + uVar1,&g_emptyA);
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0xf);
  return;
}


// 0001e934 PopupMenu_LayoutItems

void PopupMenu_LayoutItems(PopupMenu *this)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    this->itemRects[uVar1].x = this->left;
    this->itemRects[uVar1].y = (this->itemH + 3) * uVar1 + this->top;
    this->itemRects[uVar1].w = this->itemW;
    this->itemRects[uVar1].h = this->itemH;
    this->itemRects[uVar1].hilite = 0;
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0xf);
  return;
}


// 0001e9a0 PopupMenu_DrawText

void PopupMenu_DrawText(PopupMenu *this,int param_2,int param_3,int param_4,CString param_5)

{
  byte bVar1;
  uint uVar2;
  
  for (uVar2 = 0; (int)uVar2 < *(int *)(param_5.str + -4); uVar2 = uVar2 + 1 & 0xff) {
    Glyph_BlitToLayer((Glyph *)(param_4 + (uint)(ushort)param_5.str[uVar2] * 0x10),this->fc,param_2,
                      param_3);
    bVar1 = Glyph_GetW((Glyph *)(param_4 + (uint)(ushort)param_5.str[uVar2] * 0x10));
    param_2 = (uint)bVar1 + param_2;
  }
  CString_Dtor(&param_5);
  return;
}


// 0001ea24 PopupMenu_CountItems

uint PopupMenu_CountItems(PopupMenu *this)

{
  int iVar1;
  uint uVar2;
  CString local_18;
  
  uVar2 = 0;
  do {
    CString_CtorA(&local_18,&g_emptyA);
    iVar1 = wcscmp(this->items[uVar2].str,local_18.str);
    CString_Dtor(&local_18);
    if (iVar1 == 0) {
      return uVar2;
    }
    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 0xf);
  return 0xf;
}


// 0001ea9c PopupMenu_OnTapDown

void PopupMenu_OnTapDown(PopupMenu *this,uint param_2,uint param_3)

{
  bool bVar1;
  byte bVar2;
  ItemRect *pIVar3;
  PopupMenu *pPVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  byte local_2c [4];
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  
  bVar2 = this->count;
  uVar5 = 0;
  if (bVar2 != 0) {
    pPVar4 = this;
    do {
      pIVar3 = pPVar4->itemRects;
      iVar6 = 0x14;
      pbVar8 = local_2c;
      do {
        iVar7 = iVar6 + -1;
        *pbVar8 = pIVar3->hilite;
        bVar1 = 0 < iVar6;
        pIVar3 = (ItemRect *)&pIVar3->field_0x1;
        iVar6 = iVar7;
        pbVar8 = pbVar8 + 1;
      } while (iVar7 != 0 && bVar1);
      if ((((local_28 <= (param_2 & 0xffff)) && ((param_2 & 0xffff) < local_20 + local_28)) &&
          (local_24 <= (param_3 & 0xffff))) && ((param_3 & 0xffff) < local_1c + local_24 + 2)) {
        if (local_2c[0] != 0) {
          return;
        }
        this->itemRects[uVar5].hilite = 1;
        PopupMenu_DrawItem(this,uVar5 & 0xff,(int)this->font);
        Screen_PresentRect(this->screen,this->itemRects[uVar5].x,this->itemRects[uVar5].y,
                           this->itemRects[uVar5].w,this->itemRects[uVar5].h,this->fc);
        return;
      }
      uVar5 = uVar5 + 1;
      pPVar4 = (PopupMenu *)&pPVar4->f14;
    } while ((int)uVar5 < (int)(uint)bVar2);
  }
  return;
}


// 0001eb98 PopupMenu_OnTapUp

uint PopupMenu_OnTapUp(PopupMenu *this,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  ItemRect *pIVar5;
  uint uVar6;
  byte local_2c [4];
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  
  uVar6 = 0;
  if (this->count != 0) {
    do {
      iVar4 = 0x14;
      pbVar3 = local_2c;
      pIVar5 = this->itemRects + uVar6;
      do {
        iVar2 = iVar4 + -1;
        *pbVar3 = pIVar5->hilite;
        bVar1 = 0 < iVar4;
        iVar4 = iVar2;
        pbVar3 = pbVar3 + 1;
        pIVar5 = (ItemRect *)&pIVar5->field_0x1;
      } while (iVar2 != 0 && bVar1);
      if (local_2c[0] == 1) {
        iVar4 = this->itemRects[uVar6].y;
        this->itemRects[uVar6].hilite = 0;
        Screen_PresentRect(this->screen,this->itemRects[uVar6].x,iVar4,this->itemRects[uVar6].w,
                           this->itemRects[uVar6].h,this->fc);
        if ((((local_28 <= (param_2 & 0xffff)) && ((param_2 & 0xffff) < local_20 + local_28)) &&
            (local_24 <= (param_3 & 0xffff))) && ((param_3 & 0xffff) < local_1c + local_24 + 2)) {
          return uVar6;
        }
      }
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < this->count);
  }
  return 0xffffffff;
}


// 0001ec9c PopupMenu_Run

uint PopupMenu_Run(PopupMenu *this,int param_2,int param_3,int param_4)

{
  ushort *_Memory;
  uint uVar1;
  int iVar2;
  int iVar3;
  tagMSG tStack_38;
  
  this->left = param_2;
  this->top = param_3;
  PopupMenu_ClearItems(this);
  uVar1 = 0;
  do {
    CString_Assign(this->items + uVar1,(CString *)(param_4 + uVar1 * 4));
    uVar1 = uVar1 + 1 & 0xff;
  } while (uVar1 < 0xf);
  uVar1 = PopupMenu_CountItems(this);
  this->count = (byte)uVar1;
  if ((uVar1 & 0xff) == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    PopupMenu_ClampPos(this);
    PopupMenu_LayoutItems(this);
    iVar3 = (uint)this->count * (this->itemH + 4);
    iVar2 = this->itemW + 4;
    _Memory = (ushort *)operator_new(iVar3 * iVar2 * 2);
    Screen_ReadLayer(this->screen,this->left,this->top,iVar2,iVar3,_Memory,'\0');
    if (this->count != 0) {
      uVar1 = 0;
      do {
        PopupMenu_HighlightItem(this,(byte)uVar1);
        PopupMenu_DrawItem(this,uVar1,(int)this->font2);
        uVar1 = uVar1 + 1 & 0xff;
      } while (uVar1 < this->count);
    }
    Screen_PresentRect(this->screen,this->left,this->top,iVar2,iVar3,this->fc);
    PeekMessageW(&tStack_38,(HWND)0x0,0,0,1);
    while (tStack_38.message != 0x201) {
      PeekMessageW(&tStack_38,(HWND)0x0,0,0,1);
    }
    PopupMenu_OnTapDown(this,tStack_38.lParam & 0xffff,(uint)tStack_38.lParam >> 0x10);
    PeekMessageW(&tStack_38,(HWND)0x0,0,0,1);
    while (tStack_38.message != 0x202) {
      PeekMessageW(&tStack_38,(HWND)0x0,0,0,1);
    }
    uVar1 = PopupMenu_OnTapUp(this,tStack_38.lParam & 0xffff,(uint)tStack_38.lParam >> 0x10);
    Screen_BlitToLayer(this->screen,this->left,this->top,iVar2,iVar3,_Memory,this->fc);
    Screen_PresentRect(this->screen,this->left,this->top,iVar2,iVar3,this->fc);
    free(_Memory);
  }
  return uVar1;
}


// 0001eedc Menu_Ctor

int Menu_Ctor(Menu *this)

{
  PopupMenu_Ctor(&this->popup);
  RecList_Init(&this->buttons,10);
  return (int)this;
}


// 0001ef00 RecList_Init

void RecList_Init(RecList *this,int param_2)

{
  this->blockSize = param_2;
  *(undefined1 *)&this->vtbl = 0x10;
  *(undefined1 *)((int)&this->vtbl + 1) = 0;
  this->count = 0;
  this->free = (RecNode *)0x0;
  *(undefined1 *)((int)&this->vtbl + 2) = 4;
  this->tail = (RecNode *)0x0;
  this->head = (RecNode *)0x0;
  *(undefined1 *)((int)&this->vtbl + 3) = 0;
  this->blocks = (void *)0x0;
  return;
}


// 0001ef44 RecList_Serialize

void RecList_Serialize(RecList *this,CArchive *param_2)

{
  uint uVar1;
  RecNode *pRVar2;
  MenuButton MStack_44;
  
  if ((param_2->mode & 1) == 0) {
    CArchive_WriteCount(param_2,this->count);
    for (pRVar2 = this->head; pRVar2 != (RecNode *)0x0; pRVar2 = pRVar2->next) {
      RecList_SerializeElements(param_2,&pRVar2->item,1);
    }
  }
  else {
    for (uVar1 = CArchive_ReadCount(param_2); uVar1 != 0; uVar1 = uVar1 - 1) {
      RecList_SerializeElements(param_2,&MStack_44,1);
      RecList_AddTail(this,&MStack_44);
    }
  }
  return;
}


// 0001efd0 RecList_DeletingDtor

RecList * RecList_DeletingDtor(RecList *this,uint param_2)

{
  *(undefined1 *)&this->vtbl = 0x10;
  *(undefined1 *)((int)&this->vtbl + 1) = 0;
  *(undefined1 *)((int)&this->vtbl + 2) = 4;
  *(undefined1 *)((int)&this->vtbl + 3) = 0;
  RecList_RemoveAll(this);
  if ((param_2 & 1) != 0) {
    free(this);
  }
  return this;
}


// 0001f01c RecList_AddTail

void RecList_AddTail(RecList *this,MenuButton *param_2)

{
  bool bVar1;
  RecNode *pRVar2;
  int iVar3;
  int iVar4;
  MenuButton *pMVar5;
  
  pRVar2 = RecList_NewNode(this,this->tail,0);
  iVar3 = 0x34;
  pMVar5 = &pRVar2->item;
  do {
    iVar4 = iVar3 + -1;
    *(undefined1 *)pMVar5->imgs = *(undefined1 *)param_2->imgs;
    bVar1 = 0 < iVar3;
    iVar3 = iVar4;
    pMVar5 = (MenuButton *)((int)pMVar5->imgs + 1);
    param_2 = (MenuButton *)((int)param_2->imgs + 1);
  } while (iVar4 != 0 && bVar1);
  if (this->tail == (RecNode *)0x0) {
    this->head = pRVar2;
  }
  else {
    this->tail->next = pRVar2;
  }
  this->tail = pRVar2;
  return;
}


// 0001f064 RecList_RemoveAll

void RecList_RemoveAll(RecList *this)

{
  RecNode *pRVar1;
  
  for (pRVar1 = this->head; pRVar1 != (RecNode *)0x0; pRVar1 = pRVar1->next) {
  }
  this->count = 0;
  this->free = (RecNode *)0x0;
  this->tail = (RecNode *)0x0;
  this->head = (RecNode *)0x0;
  CPlex_FreeDataChain(this->blocks);
  this->blocks = (void *)0x0;
  return;
}


// 0001f0a4 RecList_NewNode

RecNode * RecList_NewNode(RecList *this,RecNode *param_2,RecNode *param_3)

{
  int iVar1;
  int iVar2;
  RecNode *pRVar3;
  
  if (this->free == (RecNode *)0x0) {
    iVar1 = CPlex_Create(&this->blocks,this->blockSize,0x3c);
    iVar2 = this->blockSize;
    pRVar3 = (RecNode *)(iVar2 * 0x3c + iVar1 + -0x38);
    if (-1 < iVar2 + -1) {
      do {
        iVar2 = iVar2 + -1;
        pRVar3->next = this->free;
        this->free = pRVar3;
        pRVar3 = pRVar3 + -1;
      } while (iVar2 != 0);
    }
  }
  pRVar3 = this->free;
  this->free = pRVar3->next;
  pRVar3->prev = param_2;
  pRVar3->next = param_3;
  this->count = this->count + 1;
  RecList_ConstructElements((RecList *)&pRVar3->item,1);
  return pRVar3;
}


// 0001f148 RecList_SerializeElements

void RecList_SerializeElements(CArchive *this,void *param_2,int param_3)

{
  if ((this->mode & 1) == 0) {
    CArchive_Write(this,param_2,param_3 * 0x34);
  }
  else {
    CArchive_Read(this,param_2,param_3 * 0x34);
  }
  return;
}


// 0001f174 RecList_ConstructElements

void RecList_ConstructElements(RecList *this,int param_2)

{
  memset(this,0,param_2 * 0x34);
  return;
}


// 0001f184 ShowPopUpAller

void ShowPopUpAller(Menu *this,ushort param_2,ushort param_3,wchar_t *param_4,CString param_5,
                   Glyph *param_6,undefined4 param_7,undefined4 param_8,Screen *param_9)

{
  uint uVar1;
  CString CVar2;
  CString local_2c;
  CString local_28;
  CString CStack_4;
  
  this->x = param_2;
  this->screen = param_9;
  this->active = 1;
  this->y = param_3;
  this->font = param_6;
  CStack_4.str = param_4;
  CString_CopyCtor(&local_2c,&CStack_4);
  uVar1 = LoadImage(local_2c,&this->h,&this->w,&this->img,1);
  if ((uVar1 & 0xff) == 0) {
    this->hasImg = 0;
  }
  else {
    this->hasImg = 1;
  }
  CString_CopyCtor(&local_2c,&param_5);
  LoadImage(local_2c,&this->img2H,&this->img2W,&this->img2,1);
  if (this->hasImg != 0) {
    Screen_BlitToLayer(this->screen,(uint)this->x,(uint)this->y,this->w,this->h,this->img,'\0');
  }
  CString_CtorA(&local_2c,s_ui_PopUpAller_jpg_00043bc4);
  CString_Plus(&local_28,&g_installDir,&local_2c);
  CVar2.str._1_1_ = local_28.str._1_1_;
  CVar2.str._0_1_ = local_28.str._0_1_;
  CVar2.str._2_1_ = local_28.str._2_1_;
  CVar2.str._3_1_ = local_28.str._3_1_;
  PopupMenu_Init(&this->popup,this->screen,param_7,param_8,CVar2,0,5,0xeb,5,0xe6);
  CString_Dtor(&local_2c);
  CString_Dtor(&CStack_4);
  CString_Dtor(&param_5);
  return;
}


// 0001f2e8 Menu_Dtor

void Menu_Dtor(Menu *this)

{
  *(undefined1 *)&(this->buttons).vtbl = 0x10;
  *(undefined1 *)((int)&(this->buttons).vtbl + 1) = 0;
  *(undefined1 *)((int)&(this->buttons).vtbl + 2) = 4;
  *(undefined1 *)((int)&(this->buttons).vtbl + 3) = 0;
  RecList_RemoveAll(&this->buttons);
  PopupMenu_Dtor(&this->popup);
  return;
}


// 0001f34c Menu_SetActive

void Menu_SetActive(Menu *this,byte param_2)

{
  this->active = param_2;
  return;
}


// 0001f354 Menu_IsActive

byte Menu_IsActive(Menu *this)

{
  return this->active;
}


// 0001f35c Menu_AddButton

void Menu_AddButton(Menu *this,ushort param_2,ushort param_3,ushort param_4,ushort param_5,
                   CString param_6,CString param_7,CString param_8,CString param_9,CString param_10,
                   CString param_11,char param_12,int param_13)

{
  uint uVar1;
  CString local_68;
  CString local_64;
  CString local_60;
  CString local_5c;
  MenuButton MStack_58;
  
  MStack_58.state = param_12;
  MStack_58.h = param_5;
  MStack_58.savedState = param_12;
  MStack_58.hasImg0 = 1;
  MStack_58.hasImg5 = 1;
  MStack_58.hasImg1 = 1;
  MStack_58.id = param_13;
  MStack_58.x = param_2;
  MStack_58.y = param_3;
  MStack_58.w = param_4;
  CString_CopyCtor(&local_68,&param_6);
  uVar1 = LoadImage(local_68,&MStack_58.imgW,&MStack_58.imgH,MStack_58.imgs,1);
  if ((uVar1 & 0xff) == 0) {
    MStack_58.hasImg0 = 0;
  }
  CString_CopyCtor(&local_68,&param_7);
  uVar1 = LoadImage(local_68,&MStack_58.imgW,&MStack_58.imgH,MStack_58.imgs + 1,1);
  if ((uVar1 & 0xff) == 0) {
    MStack_58.hasImg1 = 0;
  }
  CString_CopyCtor(&local_68,&param_8);
  LoadImage(local_68,&MStack_58.imgW,&MStack_58.imgH,MStack_58.imgs + 2,1);
  CString_CopyCtor(&local_64,&param_9);
  LoadImage(local_64,&MStack_58.imgW,&MStack_58.imgH,MStack_58.imgs + 3,1);
  CString_CopyCtor(&local_60,&param_10);
  LoadImage(local_60,&MStack_58.imgW,&MStack_58.imgH,MStack_58.imgs + 4,1);
  CString_CopyCtor(&local_5c,&param_11);
  uVar1 = LoadImage(local_5c,&MStack_58.imgW,&MStack_58.imgH,MStack_58.imgs + 5,1);
  if ((uVar1 & 0xff) == 0) {
    MStack_58.hasImg5 = 0;
  }
  RecList_AddHead(&this->buttons,&MStack_58);
  CString_Dtor(&param_6);
  CString_Dtor(&param_7);
  CString_Dtor(&param_8);
  CString_Dtor(&param_9);
  CString_Dtor(&param_10);
  CString_Dtor(&param_11);
  return;
}


// 0001f4e0 RecList_AddHead

void RecList_AddHead(RecList *this,MenuButton *param_2)

{
  bool bVar1;
  RecNode *pRVar2;
  int iVar3;
  int iVar4;
  MenuButton *pMVar5;
  
  pRVar2 = RecList_NewNode(this,0,this->head);
  iVar3 = 0x34;
  pMVar5 = &pRVar2->item;
  do {
    iVar4 = iVar3 + -1;
    *(undefined1 *)pMVar5->imgs = *(undefined1 *)param_2->imgs;
    bVar1 = 0 < iVar3;
    iVar3 = iVar4;
    pMVar5 = (MenuButton *)((int)pMVar5->imgs + 1);
    param_2 = (MenuButton *)((int)param_2->imgs + 1);
  } while (iVar4 != 0 && bVar1);
  if (this->head == (RecNode *)0x0) {
    this->tail = pRVar2;
  }
  else {
    this->head->prev = pRVar2;
  }
  this->head = pRVar2;
  return;
}


// 0001f528 Menu_SetState

void Menu_SetState(Menu *this,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  void **ppvVar4;
  RecNode *pRVar5;
  MenuButton *pMVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  void *local_4c;
  void *local_48;
  undefined4 local_44 [8];
  char local_24;
  char local_23;
  char local_22;
  int local_1c;
  
  iVar9 = (this->buttons).count;
  iVar7 = 0;
  while( true ) {
    iVar2 = (int)(char)iVar7;
    if (iVar9 <= iVar2) {
      return;
    }
    if ((iVar2 < (this->buttons).count) && (-1 < iVar2)) {
      pRVar5 = (this->buttons).head;
      for (iVar3 = iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
        pRVar5 = pRVar5->next;
      }
    }
    else {
      pRVar5 = (RecNode *)0x0;
    }
    ppvVar4 = &local_4c;
    pMVar6 = &pRVar5->item;
    iVar3 = 0x34;
    do {
      iVar8 = iVar3 + -1;
      *(undefined1 *)ppvVar4 = *(undefined1 *)pMVar6->imgs;
      bVar1 = 0 < iVar3;
      ppvVar4 = (void **)((int)ppvVar4 + 1);
      pMVar6 = (MenuButton *)((int)pMVar6->imgs + 1);
      iVar3 = iVar8;
    } while (iVar8 != 0 && bVar1);
    if (local_1c == param_2) break;
    iVar7 = (iVar2 + 1) * 0x1000000 >> 0x18;
  }
  if (local_24 != '\0') {
    free(local_4c);
  }
  if (local_22 != '\0') {
    iVar9 = 0;
    do {
      free((void *)local_44[iVar9]);
      iVar9 = (iVar9 + 1) * 0x1000000 >> 0x18;
    } while (iVar9 < 4);
  }
  if (local_23 != '\0') {
    free(local_48);
  }
  iVar7 = (int)(char)iVar7;
  if ((iVar7 < (this->buttons).count) && (-1 < iVar7)) {
    pRVar5 = (this->buttons).head;
    for (; iVar7 != 0; iVar7 = iVar7 + -1) {
      pRVar5 = pRVar5->next;
    }
  }
  else {
    pRVar5 = (RecNode *)0x0;
  }
  RecList_RemoveAt(&this->buttons,pRVar5);
  return;
}


// 0001f660 RecList_RemoveAt

void RecList_RemoveAt(RecList *this,RecNode *param_2)

{
  int iVar1;
  
  if (param_2 == this->head) {
    this->head = param_2->next;
  }
  else {
    param_2->prev->next = param_2->next;
  }
  if (param_2 == this->tail) {
    this->tail = param_2->prev;
  }
  else {
    param_2->next->prev = param_2->prev;
  }
  param_2->next = this->free;
  this->free = param_2;
  iVar1 = this->count + -1;
  this->count = iVar1;
  if (iVar1 == 0) {
    RecList_RemoveAll(this);
  }
  return;
}


// 0001f69c Menu_HasButton

int Menu_HasButton(Menu *this,int param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  MenuButton *pMVar4;
  RecNode *pRVar5;
  int iVar6;
  int iVar7;
  undefined1 *puVar8;
  undefined1 auStack_50 [48];
  int local_20;
  
  iVar6 = (this->buttons).count;
  iVar2 = 0;
  while( true ) {
    iVar2 = (int)(char)iVar2;
    if (iVar6 <= iVar2) {
      return 0;
    }
    if ((iVar2 < (this->buttons).count) && (-1 < iVar2)) {
      pRVar5 = (this->buttons).head;
      for (iVar3 = iVar2; iVar3 != 0; iVar3 = iVar3 + -1) {
        pRVar5 = pRVar5->next;
      }
    }
    else {
      pRVar5 = (RecNode *)0x0;
    }
    pMVar4 = &pRVar5->item;
    iVar3 = 0x34;
    puVar8 = auStack_50;
    do {
      iVar7 = iVar3 + -1;
      *puVar8 = *(undefined1 *)pMVar4->imgs;
      bVar1 = 0 < iVar3;
      pMVar4 = (MenuButton *)((int)pMVar4->imgs + 1);
      iVar3 = iVar7;
      puVar8 = puVar8 + 1;
    } while (iVar7 != 0 && bVar1);
    if (local_20 == param_2) break;
    iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18;
  }
  return 1;
}


// 0001f740 Menu_SetButtonState

void Menu_SetButtonState(Menu *this,int param_2,byte param_3)

{
  bool bVar1;
  undefined1 *puVar2;
  int iVar3;
  MenuButton *pMVar4;
  int iVar5;
  RecNode *pRVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_54 [43];
  byte local_29;
  undefined1 local_28;
  int local_24;
  
  iVar7 = (this->buttons).count;
  iVar3 = 0;
  while( true ) {
    if (iVar7 <= iVar3) {
      return;
    }
    if ((iVar3 < (this->buttons).count) && (-1 < iVar3)) {
      pRVar6 = (this->buttons).head;
      for (iVar5 = iVar3; iVar5 != 0; iVar5 = iVar5 + -1) {
        pRVar6 = pRVar6->next;
      }
    }
    else {
      pRVar6 = (RecNode *)0x0;
    }
    iVar5 = 0x34;
    puVar2 = auStack_54;
    pMVar4 = &pRVar6->item;
    do {
      iVar8 = iVar5 + -1;
      *puVar2 = *(undefined1 *)pMVar4->imgs;
      local_28 = local_29;
      bVar1 = 0 < iVar5;
      iVar5 = iVar8;
      puVar2 = puVar2 + 1;
      pMVar4 = (MenuButton *)((int)pMVar4->imgs + 1);
    } while (iVar8 != 0 && bVar1);
    if (local_24 == param_2) break;
    iVar3 = iVar3 + 1;
  }
  local_29 = param_3;
  if ((iVar3 < (this->buttons).count) && (-1 < iVar3)) {
    pRVar6 = (this->buttons).head;
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      pRVar6 = pRVar6->next;
    }
  }
  else {
    pRVar6 = (RecNode *)0x0;
  }
  iVar3 = 0x34;
  puVar2 = auStack_54;
  pMVar4 = &pRVar6->item;
  do {
    iVar7 = iVar3 + -1;
    *(undefined1 *)pMVar4->imgs = *puVar2;
    bVar1 = 0 < iVar3;
    iVar3 = iVar7;
    puVar2 = puVar2 + 1;
    pMVar4 = (MenuButton *)((int)pMVar4->imgs + 1);
  } while (iVar7 != 0 && bVar1);
  return;
}


// 0001f828 Picture_DrawDirect

void Picture_DrawDirect(undefined4 *param_1)

{
  Screen_DrawDirect((Screen *)param_1[0x78],(uint)*(ushort *)(param_1 + 1),
                    (uint)*(ushort *)((int)param_1 + 6),param_1[2],param_1[3],(ushort *)*param_1);
  Menu_DrawButtons((Menu *)param_1);
  return;
}


// 0001f868 Menu_DrawButtons

void Menu_DrawButtons(Menu *this)

{
  bool bVar1;
  int iVar2;
  RecNode *pRVar3;
  int iVar4;
  ushort **ppuVar5;
  MenuButton *pMVar6;
  int iVar7;
  int iVar8;
  ushort *local_48;
  ushort *local_44;
  ushort local_30;
  ushort local_2e;
  int local_28;
  int local_24;
  char local_1d;
  
  iVar8 = (int)(char)(this->buttons).count;
  if (0 < iVar8) {
    iVar7 = 0;
    do {
      if ((iVar7 < (this->buttons).count) && (-1 < iVar7)) {
        pRVar3 = (this->buttons).head;
        for (iVar2 = iVar7; iVar2 != 0; iVar2 = iVar2 + -1) {
          pRVar3 = pRVar3->next;
        }
      }
      else {
        pRVar3 = (RecNode *)0x0;
      }
      iVar2 = 0x34;
      ppuVar5 = &local_48;
      pMVar6 = &pRVar3->item;
      do {
        iVar4 = iVar2 + -1;
        *(undefined1 *)ppuVar5 = *(undefined1 *)pMVar6->imgs;
        bVar1 = 0 < iVar2;
        iVar2 = iVar4;
        ppuVar5 = (ushort **)((int)ppuVar5 + 1);
        pMVar6 = (MenuButton *)((int)pMVar6->imgs + 1);
      } while (iVar4 != 0 && bVar1);
      if (local_1d == '\x01') {
        Screen_DrawDirect(this->screen,(uint)local_30,(uint)local_2e,local_28,local_24,local_48);
      }
      else if (local_1d == '\x04') {
        Screen_DrawDirect(this->screen,(uint)local_30,(uint)local_2e,local_28,local_24,local_44);
      }
      iVar7 = (iVar7 + 1) * 0x1000000 >> 0x18;
    } while (iVar7 < iVar8);
  }
  return;
}


// 0001f95c PlayPowerOnSound

void PlayPowerOnSound(Menu *this,char param_2,char param_3)

{
  bool bVar1;
  int iVar2;
  CString *pCVar3;
  RecNode *pRVar4;
  int iVar5;
  undefined1 *puVar6;
  MenuButton *pMVar7;
  uint uVar8;
  CString CStack_58;
  CString local_54;
  CString aCStack_50 [2];
  undefined1 auStack_48 [8];
  undefined4 local_40 [4];
  ushort local_30;
  ushort local_2e;
  int local_28;
  int local_24;
  
  iVar2 = (int)param_2;
  if ((iVar2 < (this->buttons).count) && (-1 < iVar2)) {
    pRVar4 = (this->buttons).head;
    for (; iVar2 != 0; iVar2 = iVar2 + -1) {
      pRVar4 = pRVar4->next;
    }
  }
  else {
    pRVar4 = (RecNode *)0x0;
  }
  iVar2 = 0x34;
  puVar6 = auStack_48;
  pMVar7 = &pRVar4->item;
  do {
    iVar5 = iVar2 + -1;
    *puVar6 = *(undefined1 *)pMVar7->imgs;
    bVar1 = 0 < iVar2;
    iVar2 = iVar5;
    puVar6 = puVar6 + 1;
    pMVar7 = (MenuButton *)((int)pMVar7->imgs + 1);
  } while (iVar5 != 0 && bVar1);
  CString_CtorA(&CStack_58,s_sounds_PowerOn_wav_00043bd8);
  CString_Plus(&local_54,&g_installDir,&CStack_58);
  pCVar3 = MangleAssetPath(aCStack_50,local_54);
  sndPlaySoundW(pCVar3->str,3);
  CString_Dtor(aCStack_50);
  CString_Dtor(&CStack_58);
  if (param_3 == '\x01') {
    iVar2 = 0;
    do {
      Screen_DrawDirect(this->screen,(uint)local_30,(uint)local_2e,local_28,local_24,
                        (ushort *)local_40[iVar2]);
      Sleep(0x32);
      iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18;
    } while (iVar2 < 4);
  }
  else {
    uVar8 = 3;
    do {
      Screen_DrawDirect(this->screen,(uint)local_30,(uint)local_2e,local_28,local_24,
                        (ushort *)local_40[uVar8]);
      Sleep(0x32);
      uVar8 = (int)((uVar8 - 1) * 0x1000000) >> 0x18;
    } while (uVar8 < 0x80000000);
  }
  return;
}


// 0001fadc LoadSaveSlot

void LoadSaveSlot(int param_1)

{
  CString *pCVar1;
  HANDLE hFile;
  CString CVar2;
  CString CVar3;
  int iVar4;
  char local_70;
  char local_6f;
  char local_6e;
  char local_6d;
  ushort local_6c [2];
  DWORD DStack_68;
  CString local_64;
  CString local_60;
  CString local_5c;
  CString CStack_58;
  CString CStack_54;
  CString CStack_50;
  CString CStack_4c;
  undefined1 local_48 [4];
  CString CStack_44;
  CString local_40;
  CString local_3c;
  CString local_38;
  CString local_34;
  ushort *local_30;
  ushort *local_24;
  int local_20;
  
  local_64.str = g_afxEmptyString;
  local_60.str = local_64.str;
  local_5c.str = local_64.str;
  Screen_BlitToLayer(*(Screen **)(param_1 + 0x1e0),(uint)*(ushort *)(param_1 + 4),
                     (uint)*(ushort *)(param_1 + 6),*(int *)(param_1 + 8),*(int *)(param_1 + 0xc),
                     *(ushort **)(param_1 + 0x14),'\0');
  iVar4 = 0;
  do {
    CString_CtorA(&CStack_58,s_save_save_00043c04);
    pCVar1 = CString_Plus(&CStack_50,&g_installDir,&CStack_58);
    CString_Assign(&local_5c,pCVar1);
    CString_Dtor(&CStack_50);
    CString_Dtor(&CStack_58);
    CString_AppendChar(&local_5c,(short)(char)((uint)((iVar4 + 0x31) * 0x1000000) >> 0x18));
    CString_CtorA(&CStack_54,s__fad_00043bfc);
    CString_Append(&local_5c,&CStack_54);
    CString_Dtor(&CStack_54);
    hFile = CreateFileW(local_5c.str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    if (hFile == (HANDLE)0xffffffff) {
      CString_AssignA(&local_60,s_EMPTY_00043bf4);
      CString_AssignA(&local_64,s_SLOT_00043bec);
      CString_CopyCtor(&local_38,&local_64);
      CString_CopyCtor(&local_34,&local_60);
      CVar2.str = local_34.str;
      CVar3.str = local_38.str;
    }
    else {
      ReadFile(hFile,local_6c,2,&DStack_68,(LPOVERLAPPED)0x0);
      ReadFile(hFile,&local_6e,1,&DStack_68,(LPOVERLAPPED)0x0);
      ReadFile(hFile,&local_6d,1,&DStack_68,(LPOVERLAPPED)0x0);
      ReadFile(hFile,local_48,4,&DStack_68,(LPOVERLAPPED)0x0);
      ReadFile(hFile,&local_6f,1,&DStack_68,(LPOVERLAPPED)0x0);
      ReadFile(hFile,&local_70,1,&DStack_68,(LPOVERLAPPED)0x0);
      CloseHandle(hFile);
      LoadSceneFromData((uint)local_6c[0],(Scene *)&local_30);
      Screen_BlitDownscaled
                (*(Screen **)(param_1 + 0x1e0),8,iVar4 * 0x44 + 7,local_24,local_20,local_30,'\0',
                 '\x03');
      free(local_30);
      pCVar1 = ReadDataRecord(&CStack_4c,(uint)local_6c[0]);
      CString_Assign(&local_60,pCVar1);
      CString_Dtor(&CStack_4c);
      pCVar1 = FormatSaveDate(&CStack_44,local_6d,local_6e,local_48[0],local_6f,local_70);
      CString_Assign(&local_64,pCVar1);
      CString_Dtor(&CStack_44);
      CString_CopyCtor(&local_40,&local_64);
      CString_CopyCtor(&local_3c,&local_60);
      CVar2.str = local_3c.str;
      CVar3.str = local_40.str;
    }
    SaveMenu_DrawSlotText((Menu *)param_1,(char)iVar4,CVar2.str,CVar3.str);
    iVar4 = (iVar4 + 1) * 0x1000000 >> 0x18;
  } while (iVar4 < 3);
  Screen_PresentLayer(*(Screen **)(param_1 + 0x1e0),'\0');
  CString_Dtor(&local_64);
  CString_Dtor(&local_60);
  CString_Dtor(&local_5c);
  return;
}


// 0001fdd8 SaveMenu_DrawSlotText

void SaveMenu_DrawSlotText(Menu *this,char param_2,wchar_t *param_3,wchar_t *param_4)

{
  int iVar1;
  CString local_28;
  CString local_24;
  CString CStack_8;
  CString CStack_4;
  
  CStack_8.str = param_3;
  CStack_4.str = param_4;
  CString_CopyCtor(&local_28,&CStack_8);
  iVar1 = ((int)param_2 & 0xffffU) * 0x44;
  Menu_DrawText(this,100,iVar1 + 10,(int)local_28.str);
  CString_CopyCtor(&local_24,&CStack_4);
  Menu_DrawText(this,100,iVar1 + 0x20,(int)local_24.str);
  CString_Dtor(&CStack_8);
  CString_Dtor(&CStack_4);
  return;
}


// 0001fe60 Menu_DrawText

void Menu_DrawText(Menu *this,uint param_2,uint param_3,int param_4)

{
  byte bVar1;
  uint uVar2;
  CString local_4;
  
  local_4.str = (wchar_t *)param_4;
  for (uVar2 = 0; (int)uVar2 < *(int *)(local_4.str + -4); uVar2 = uVar2 + 1 & 0xff) {
    Glyph_BlitToLayer(this->font + (ushort)local_4.str[uVar2],'\0',param_2 & 0xffff,param_3 & 0xffff
                     );
    bVar1 = Glyph_GetW(this->font + (ushort)local_4.str[uVar2]);
    param_2 = bVar1 + param_2;
  }
  CString_Dtor(&local_4);
  return;
}


// 0001fef8 SaveLoadMenu

uint SaveLoadMenu(Menu *this,char param_2)

{
  char cVar1;
  bool bVar2;
  CString *pCVar3;
  HANDLE hObject;
  wchar_t *lpFileName;
  int iVar4;
  char *pcVar5;
  CString *this_00;
  uint uVar6;
  ushort local_d4;
  ushort local_d2;
  CString local_d0;
  CString CStack_cc;
  CString CStack_c8;
  CString CStack_c4;
  CString CStack_c0;
  CString CStack_bc;
  CString CStack_b8;
  CString CStack_b4;
  CString CStack_b0;
  CString CStack_ac;
  CString CStack_a8;
  CString CStack_a4;
  CString local_a0;
  CString local_9c;
  CString CStack_98;
  CString local_94;
  CString local_90;
  CString local_8c;
  CString CStack_88;
  CString local_84;
  CString local_80;
  CString CStack_7c;
  CString CStack_78;
  CString CStack_74;
  CString local_70;
  CString CStack_6c;
  CString CStack_68;
  CString aCStack_64 [2];
  CString local_5c [15];
  
  this_00 = (CString *)&stack0xffffffe0;
  pCVar3 = local_5c;
  iVar4 = 0xf;
  do {
    iVar4 = iVar4 + -1;
    pCVar3->str = g_afxEmptyString;
    pCVar3 = pCVar3 + 1;
  } while (iVar4 != 0);
  local_d0.str = g_afxEmptyString;
  bVar2 = false;
  uVar6 = (uint)(char)local_d4;
  do {
    WaitForPenDown((short *)&local_d2,(short *)&local_d4);
    if (((local_d4 < 0xe6) && (8 < local_d2)) && (local_d2 < 0xd0)) {
      iVar4 = 0;
      do {
        if ((iVar4 * 0x44 + 7 < (int)(uint)local_d4) && ((int)(uint)local_d4 < iVar4 * 0x44 + 0x43))
        {
          CString_CtorA(&CStack_bc,s_save_save_00043c04);
          pCVar3 = CString_Plus(&CStack_7c,&g_installDir,&CStack_bc);
          CString_Assign(&local_d0,pCVar3);
          CString_Dtor(&CStack_7c);
          CString_Dtor(&CStack_bc);
          CString_AppendChar(&local_d0,(short)(char)((uint)((iVar4 + 0x31) * 0x1000000) >> 0x18));
          CString_CtorA(&CStack_c4,s__fad_00043bfc);
          CString_Append(&local_d0,&CStack_c4);
          CString_Dtor(&CStack_c4);
          hObject = CreateFileW(local_d0.str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,
                                (HANDLE)0x0);
          if ((hObject == (HANDLE)0xffffffff) && (param_2 == '\x01')) {
            CString_AssignA(local_5c,s_Back_to_Menu_00043c44);
            CString_AssignA(local_5c + 1,&g_emptyA);
            CString_CtorA(&CStack_b4,s_sounds_bruit_plastic_wav_00043c28);
            CString_Plus(&local_9c,&g_installDir,&CStack_b4);
            pCVar3 = MangleAssetPath(&CStack_a4,local_9c);
            sndPlaySoundW(pCVar3->str,3);
            CString_Dtor(&CStack_a4);
            CString_Dtor(&CStack_b4);
            uVar6 = PopupMenu_Run(&this->popup,(uint)local_d2,(uint)local_d4,(int)local_5c);
            if ((char)uVar6 == '\0') {
              bVar2 = true;
              CString_CtorA(&CStack_cc,s_sounds_bruit_plastic_wav_00043c28);
              CString_Plus(&local_94,&g_installDir,&CStack_cc);
              pCVar3 = MangleAssetPath(&CStack_6c,local_94);
              sndPlaySoundW(pCVar3->str,3);
              CString_Dtor(&CStack_6c);
              CString_Dtor(&CStack_cc);
            }
          }
          else {
            CloseHandle(hObject);
            if (param_2 == '\0') {
              pcVar5 = s_Save_00043c20;
            }
            else {
              pcVar5 = s_Load_00043c18;
            }
            CString_AssignA(local_5c,pcVar5);
            CString_AssignA(local_5c + 1,s_Delete_00043c10);
            CString_AssignA(local_5c + 2,s_Back_to_Menu_00043c44);
            CString_AssignA(local_5c + 3,&g_emptyA);
            CString_CtorA(&CStack_ac,s_sounds_bruit_plastic_wav_00043c28);
            CString_Plus(&local_8c,&g_installDir,&CStack_ac);
            pCVar3 = MangleAssetPath(&CStack_74,local_8c);
            sndPlaySoundW(pCVar3->str,3);
            CString_Dtor(&CStack_74);
            CString_Dtor(&CStack_ac);
            uVar6 = PopupMenu_Run(&this->popup,(uint)local_d2,(uint)local_d4,(int)local_5c);
            cVar1 = (char)uVar6;
            if (cVar1 == '\0') {
              CString_CtorA(&CStack_b8,s_sounds_bruit_plastic_wav_00043c28);
              CString_Plus(&local_90,&g_installDir,&CStack_b8);
              pCVar3 = MangleAssetPath(&CStack_88,local_90);
              sndPlaySoundW(pCVar3->str,3);
              CString_Dtor(&CStack_88);
              CString_Dtor(&CStack_b8);
              uVar6 = iVar4 + 1;
LAB_00020308:
              bVar2 = true;
            }
            else if (cVar1 == '\x01') {
              CString_CtorA(&CStack_c0,s_sounds_bruit_plastic_wav_00043c28);
              CString_Plus(&local_a0,&g_installDir,&CStack_c0);
              pCVar3 = MangleAssetPath(&CStack_98,local_a0);
              sndPlaySoundW(pCVar3->str,3);
              CString_Dtor(&CStack_98);
              CString_Dtor(&CStack_c0);
              lpFileName = CString_GetBuffer(&local_d0,*(int *)(local_d0.str + -4));
              DeleteFileW(lpFileName);
              LoadSaveSlot((int)this);
            }
            else if (cVar1 == '\x02') {
              CString_CtorA(&CStack_c8,s_sounds_bruit_plastic_wav_00043c28);
              CString_Plus(&local_84,&g_installDir,&CStack_c8);
              pCVar3 = MangleAssetPath(aCStack_64,local_84);
              sndPlaySoundW(pCVar3->str,3);
              CString_Dtor(aCStack_64);
              CString_Dtor(&CStack_c8);
              uVar6 = 0;
              goto LAB_00020308;
            }
          }
        }
        iVar4 = (iVar4 + 1) * 0x1000000 >> 0x18;
      } while (iVar4 < 3);
    }
    else {
      CString_AssignA(local_5c,s_Back_to_Menu_00043c44);
      CString_AssignA(local_5c + 1,&g_emptyA);
      CString_CtorA(&CStack_b0,s_sounds_bruit_plastic_wav_00043c28);
      CString_Plus(&local_80,&g_installDir,&CStack_b0);
      pCVar3 = MangleAssetPath(&CStack_78,local_80);
      sndPlaySoundW(pCVar3->str,3);
      CString_Dtor(&CStack_78);
      CString_Dtor(&CStack_b0);
      uVar6 = PopupMenu_Run(&this->popup,(uint)local_d2,(uint)local_d4,(int)local_5c);
      if ((char)uVar6 == '\0') {
        CString_CtorA(&CStack_a8,s_sounds_bruit_plastic_wav_00043c28);
        CString_Plus(&local_70,&g_installDir,&CStack_a8);
        pCVar3 = MangleAssetPath(&CStack_68,local_70);
        sndPlaySoundW(pCVar3->str,3);
        CString_Dtor(&CStack_68);
        CString_Dtor(&CStack_a8);
        bVar2 = true;
      }
    }
    if (bVar2) {
      if ((char)uVar6 == '\0') {
        Picture_DrawDirect(&this->img);
      }
      CString_Dtor(&local_d0);
      iVar4 = 0xf;
      do {
        this_00 = this_00 + -1;
        CString_Dtor(this_00);
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
      return uVar6;
    }
  } while( true );
}


// 00020444 Menu_OnTapDown

void Menu_OnTapDown(Menu *this,ushort param_2,uint param_3)

{
  bool bVar1;
  undefined1 *puVar2;
  int iVar3;
  MenuButton *pMVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  RecNode *pRVar9;
  undefined1 auStack_50 [26];
  ushort local_36;
  ushort local_34;
  ushort local_32;
  int local_2c;
  char local_25;
  char local_24;
  
  iVar6 = (this->buttons).count;
  iVar5 = 0;
  if (0 < iVar6) {
    iVar7 = (this->buttons).count;
    do {
      if ((iVar5 < iVar7) && (-1 < iVar5)) {
        pRVar9 = (this->buttons).head;
        for (iVar3 = iVar5; iVar3 != 0; iVar3 = iVar3 + -1) {
          pRVar9 = pRVar9->next;
        }
      }
      else {
        pRVar9 = (RecNode *)0x0;
      }
      pMVar4 = &pRVar9->item;
      iVar3 = 0x34;
      puVar2 = auStack_50;
      do {
        iVar8 = iVar3 + -1;
        *puVar2 = *(undefined1 *)pMVar4->imgs;
        bVar1 = 0 < iVar3;
        pMVar4 = (MenuButton *)((int)pMVar4->imgs + 1);
        iVar3 = iVar8;
        puVar2 = puVar2 + 1;
      } while (iVar8 != 0 && bVar1);
      if ((local_34 <= param_2) && (param_2 < local_32)) {
        if (((uint)local_36 <= (param_3 & 0xffff)) &&
           ((param_3 & 0xffff) < (uint)local_36 + local_2c)) {
          if (local_25 == '\x04') {
            return;
          }
          local_24 = local_25;
          local_25 = 2;
          if ((iVar5 < (this->buttons).count) && (-1 < iVar5)) {
            pRVar9 = (this->buttons).head;
            for (iVar6 = iVar5; iVar6 != 0; iVar6 = iVar6 + -1) {
              pRVar9 = pRVar9->next;
            }
          }
          else {
            pRVar9 = (RecNode *)0x0;
          }
          iVar6 = 0x34;
          puVar2 = auStack_50;
          pMVar4 = &pRVar9->item;
          do {
            iVar7 = iVar6 + -1;
            *(undefined1 *)pMVar4->imgs = *puVar2;
            bVar1 = 0 < iVar6;
            iVar6 = iVar7;
            puVar2 = puVar2 + 1;
            pMVar4 = (MenuButton *)((int)pMVar4->imgs + 1);
          } while (iVar7 != 0 && bVar1);
          PlayPowerOnSound(this,(char)iVar5,'\x01');
          return;
        }
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar6);
  }
  return;
}


// 0002059c Menu_HitTest

int Menu_HitTest(Menu *this,uint param_2,uint param_3)

{
  bool bVar1;
  int iVar2;
  RecNode *pRVar3;
  int iVar4;
  undefined1 *puVar5;
  MenuButton *pMVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_50 [24];
  ushort local_38;
  ushort local_36;
  int local_30;
  int local_2c;
  char local_25;
  char local_24;
  int local_20;
  
  iVar8 = (this->buttons).count;
  iVar7 = 0;
  if (0 < iVar8) {
    do {
      if ((iVar7 < (this->buttons).count) && (-1 < iVar7)) {
        pRVar3 = (this->buttons).head;
        for (iVar2 = iVar7; iVar2 != 0; iVar2 = iVar2 + -1) {
          pRVar3 = pRVar3->next;
        }
      }
      else {
        pRVar3 = (RecNode *)0x0;
      }
      iVar2 = 0x34;
      puVar5 = auStack_50;
      pMVar6 = &pRVar3->item;
      do {
        iVar4 = iVar2 + -1;
        *puVar5 = *(undefined1 *)pMVar6->imgs;
        bVar1 = 0 < iVar2;
        iVar2 = iVar4;
        puVar5 = puVar5 + 1;
        pMVar6 = (MenuButton *)((int)pMVar6->imgs + 1);
      } while (iVar4 != 0 && bVar1);
      if (local_25 == '\x02') {
        local_24 = local_25;
        local_25 = '\x01';
        if ((iVar7 < (this->buttons).count) && (-1 < iVar7)) {
          pRVar3 = (this->buttons).head;
          for (iVar2 = iVar7; iVar2 != 0; iVar2 = iVar2 + -1) {
            pRVar3 = pRVar3->next;
          }
        }
        else {
          pRVar3 = (RecNode *)0x0;
        }
        iVar2 = 0x34;
        puVar5 = auStack_50;
        pMVar6 = &pRVar3->item;
        do {
          iVar4 = iVar2 + -1;
          *(undefined1 *)pMVar6->imgs = *puVar5;
          bVar1 = 0 < iVar2;
          iVar2 = iVar4;
          puVar5 = puVar5 + 1;
          pMVar6 = (MenuButton *)((int)pMVar6->imgs + 1);
        } while (iVar4 != 0 && bVar1);
        PlayPowerOnSound(this,(char)iVar7,-1);
        if (((uint)local_38 <= (param_2 & 0xffff)) &&
           ((param_2 & 0xffff) < (uint)local_38 + local_30)) {
          if (((uint)local_36 <= (param_3 & 0xffff)) &&
             ((param_3 & 0xffff) < (uint)local_36 + local_2c)) {
            return local_20;
          }
        }
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 < iVar8);
  }
  return 0;
}


// 00020708 FormatSaveDate

CString * FormatSaveDate(CString *param_1,char param_2,char param_3,char param_4,char param_5,
                        char param_6)

{
  div_t *pdVar1;
  CString *pCVar2;
  CString local_44;
  CString CStack_40;
  CString CStack_3c;
  CString CStack_38;
  CString CStack_34;
  CString CStack_30;
  CString CStack_2c;
  CString CStack_28;
  div_t dStack_24;
  char local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  char local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  
  local_44.str = g_afxEmptyString;
  CString_AssignA(&local_44,&g_emptyA);
  pdVar1 = div(&dStack_24,(int)param_2,10);
  local_1c = (char)pdVar1->quot;
  local_1b = *(undefined1 *)((int)&pdVar1->quot + 1);
  local_1a = *(undefined1 *)((int)&pdVar1->quot + 2);
  local_19 = *(undefined1 *)((int)&pdVar1->quot + 3);
  local_18 = (char)pdVar1->rem;
  local_17 = *(undefined1 *)((int)&pdVar1->rem + 1);
  local_16 = *(undefined1 *)((int)&pdVar1->rem + 2);
  local_15 = *(undefined1 *)((int)&pdVar1->rem + 3);
  CString_PlusChar(&CStack_40,&local_44,(short)(char)(local_1c + '0'));
  CString_Assign(&local_44,&CStack_40);
  CString_Dtor(&CStack_40);
  CString_PlusChar(&CStack_3c,&local_44,(short)(char)(local_18 + '0'));
  CString_Assign(&local_44,&CStack_3c);
  CString_Dtor(&CStack_3c);
  CString_CtorA(&CStack_38,s_space);
  pCVar2 = CString_Plus((CString *)&dStack_24,&local_44,&CStack_38);
  CString_Assign(&local_44,pCVar2);
  CString_Dtor((CString *)&dStack_24);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,g_monthNames[param_3]);
  pCVar2 = CString_Plus((CString *)&dStack_24,&local_44,&CStack_38);
  CString_Assign(&local_44,pCVar2);
  CString_Dtor((CString *)&dStack_24);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_space);
  pCVar2 = CString_Plus((CString *)&dStack_24,&local_44,&CStack_38);
  CString_Assign(&local_44,pCVar2);
  CString_Dtor((CString *)&dStack_24);
  CString_Dtor(&CStack_38);
  pdVar1 = div(&dStack_24,(param_4 * 0x18 + (int)param_5) * 0x1000000 >> 0x18,10);
  local_1c = (char)pdVar1->quot;
  local_1b = *(undefined1 *)((int)&pdVar1->quot + 1);
  local_1a = *(undefined1 *)((int)&pdVar1->quot + 2);
  local_19 = *(undefined1 *)((int)&pdVar1->quot + 3);
  local_18 = (char)pdVar1->rem;
  local_17 = *(undefined1 *)((int)&pdVar1->rem + 1);
  local_16 = *(undefined1 *)((int)&pdVar1->rem + 2);
  local_15 = *(undefined1 *)((int)&pdVar1->rem + 3);
  CString_PlusChar(&CStack_34,&local_44,(short)(char)(local_1c + '0'));
  CString_Assign(&local_44,&CStack_34);
  CString_Dtor(&CStack_34);
  CString_PlusChar(&CStack_30,&local_44,(short)(char)(local_18 + '0'));
  CString_Assign(&local_44,&CStack_30);
  CString_Dtor(&CStack_30);
  CString_CtorA(&CStack_38,s___00043c54);
  pCVar2 = CString_Plus((CString *)&dStack_24,&local_44,&CStack_38);
  CString_Assign(&local_44,pCVar2);
  CString_Dtor((CString *)&dStack_24);
  CString_Dtor(&CStack_38);
  pdVar1 = div(&dStack_24,(int)param_6,10);
  local_1c = (char)pdVar1->quot;
  local_1b = *(undefined1 *)((int)&pdVar1->quot + 1);
  local_1a = *(undefined1 *)((int)&pdVar1->quot + 2);
  local_19 = *(undefined1 *)((int)&pdVar1->quot + 3);
  local_18 = (char)pdVar1->rem;
  local_17 = *(undefined1 *)((int)&pdVar1->rem + 1);
  local_16 = *(undefined1 *)((int)&pdVar1->rem + 2);
  local_15 = *(undefined1 *)((int)&pdVar1->rem + 3);
  CString_PlusChar(&CStack_2c,&local_44,(short)(char)(local_1c + '0'));
  CString_Assign(&local_44,&CStack_2c);
  CString_Dtor(&CStack_2c);
  CString_PlusChar(&CStack_28,&local_44,(short)(char)(local_18 + '0'));
  CString_Assign(&local_44,&CStack_28);
  CString_Dtor(&CStack_28);
  CString_CopyCtor(param_1,&local_44);
  CString_Dtor(&local_44);
  return param_1;
}


// 00020ac8 ShowCredits

void ShowCredits(Menu *this)

{
  short sStack_34;
  short sStack_32;
  CString CStack_30;
  CString local_2c [2];
  ushort *local_24 [3];
  int local_18;
  int local_14;
  
  CString_CtorA(&CStack_30,s__Menu_Credits1_ifj_00043c6c);
  CString_Plus(local_2c,&g_installDir,&CStack_30);
  LoadImage(local_2c[0],&local_14,&local_18,local_24,1);
  CString_Dtor(&CStack_30);
  Screen_DrawDirect(this->screen,0,0,local_18,local_14,local_24[0]);
  WaitForPenUp(&sStack_32,&sStack_34);
  free(local_24[0]);
  CString_CtorA(&CStack_30,s__Menu_Credits2_ifj_00043c58);
  CString_Plus(local_2c,&g_installDir,&CStack_30);
  LoadImage(local_2c[0],&local_14,&local_18,local_24,1);
  CString_Dtor(&CStack_30);
  Screen_DrawDirect(this->screen,0,0,local_18,local_14,local_24[0]);
  WaitForPenUp(&sStack_32,&sStack_34);
  free(local_24[0]);
  Picture_DrawDirect(&this->img);
  return;
}


// 00020be4 Rec9_IsVisible

byte Rec9_IsVisible(Rec9 *this)

{
  return this->flags[0];
}


// 00020bec Rec9_SetVisible

void Rec9_SetVisible(Rec9 *this,byte param_2)

{
  this->flags[0] = param_2;
  return;
}


// 00020bf4 Rec9_GetFlag

byte Rec9_GetFlag(Rec9 *this,uint param_2)

{
  return this->flags[(param_2 & 0xff) + 1];
}


// 00020c04 Rec9_SetFlag

void Rec9_SetFlag(Rec9 *this,uint param_2,byte param_3)

{
  this->flags[(param_2 & 0xff) + 1] = param_3;
  return;
}


// 00020c14 RecE1_GetObjState

Rec9 * RecE1_GetObjState(RecE1 *this,uint param_2)

{
  return this->objStates + (param_2 & 0xff);
}


// 00020c28 Rec9ec_Ctor

void Rec9ec_Ctor(Rec9ec *this)

{
  (this->name).str = g_afxEmptyString;
  this->flags[1] = 1;
  return;
}


// 00020c44 Rec9ec_Dtor

void Rec9ec_Dtor(Rec9ec *this)

{
  CString_Dtor(&this->name);
  return;
}


// 00020c4c Rec9ec_GetObjState

Rec9 * Rec9ec_GetObjState(Rec9ec *this,uint param_2)

{
  return this->objStates + (param_2 & 0xff);
}


// 00020c64 Rec9ec_GetRecE1

RecE1 * Rec9ec_GetRecE1(Rec9ec *this,uint param_2)

{
  return this->recsE1 + (param_2 & 0xff);
}


// 00020c7c Rec9ec_Get1

byte Rec9ec_Get1(Rec9ec *this)

{
  return this->flags[0];
}


// 00020c84 Rec9ec_Set1

void Rec9ec_Set1(Rec9ec *this,byte param_2)

{
  this->flags[0] = param_2;
  return;
}


// 00020c8c Rec9ec_Get0

byte Rec9ec_Get0(Rec9ec *this)

{
  return this->f0;
}


// 00020c94 Rec9ec_Set0

void Rec9ec_Set0(Rec9ec *this,byte param_2)

{
  this->f0 = param_2;
  return;
}


// 00020c9c Rec9ec_Get2

byte Rec9ec_Get2(Rec9ec *this)

{
  return this->flags[1];
}


// 00020ca4 Rec9ec_Set2

void Rec9ec_Set2(Rec9ec *this,byte param_2)

{
  this->flags[1] = param_2;
  return;
}


// 00020cac Rec9ec_Get3

int Rec9ec_Get3(Rec9ec *this)

{
  return (int)(char)this->flags[2];
}


// 00020cb4 Rec9ec_Set3

void Rec9ec_Set3(Rec9ec *this,byte param_2)

{
  this->flags[2] = param_2;
  return;
}


// 00020cbc Rec9ec_GetDialogTopic

int Rec9ec_GetDialogTopic(Rec9ec *this)

{
  return (int)(char)this->flags[3];
}


// 00020cc4 Rec9ec_Set4

void Rec9ec_Set4(Rec9ec *this,byte param_2)

{
  this->flags[3] = param_2;
  return;
}


// 00020ccc Rec9ec_Set5

void Rec9ec_Set5(Rec9ec *this,byte param_2)

{
  this->flags[4] = param_2;
  return;
}


// 00020cd4 Rec9ec_Get5

byte Rec9ec_Get5(Rec9ec *this)

{
  return this->flags[4];
}


// 00020cdc Rec9ec_Set7

void Rec9ec_Set7(Rec9ec *this,byte param_2)

{
  this->flags[6] = param_2;
  return;
}


// 00020ce4 Rec9ec_Get7

int Rec9ec_Get7(Rec9ec *this)

{
  return (int)(char)this->flags[6];
}


// 00020cec Rec9ec_Set6

void Rec9ec_Set6(Rec9ec *this,byte param_2)

{
  this->flags[5] = param_2;
  return;
}


// 00020cf4 Rec9ec_Get6

byte Rec9ec_Get6(Rec9ec *this)

{
  return this->flags[5];
}


// 00020cfc Rec9ec_Set8

void Rec9ec_Set8(Rec9ec *this,byte param_2)

{
  this->flags[7] = param_2;
  return;
}


// 00020d04 Rec9ec_Get8

int Rec9ec_Get8(Rec9ec *this)

{
  return (int)(char)this->flags[7];
}


// 00020d0c Rec9ec_SetName

void Rec9ec_SetName(Rec9ec *this,CString param_2)

{
  CString aCStack_c [3];
  
  aCStack_c[0].str = param_2.str;
  CString_Assign(&this->name,aCStack_c);
  CString_Dtor(aCStack_c);
  return;
}


// 00020d30 Rec9ec_GetName

CString * Rec9ec_GetName(Rec9ec *this,CString *param_2)

{
  CString_CopyCtor(param_2,&this->name);
  return param_2;
}


// 00020d4c Rec9ec_Save

void Rec9ec_Save(Rec9ec *this,HANDLE param_2)

{
  DWORD DStack_14;
  
  WriteFile(param_2,this,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 1,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 2,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 3,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->f10,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->f11,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->objStates,0x10e,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->recsE1,0x8ca,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 4,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 5,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 6,1,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,this->flags + 7,1,&DStack_14,(LPOVERLAPPED)0x0);
  return;
}


// 00020ea8 Rec9ec_Load

void Rec9ec_Load(Rec9ec *this,HANDLE param_2)

{
  DWORD DStack_14;
  
  ReadFile(param_2,this,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 1,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 2,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 3,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,&this->f10,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,&this->f11,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->objStates,0x10e,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->recsE1,0x8ca,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 4,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 5,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 6,1,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,this->flags + 7,1,&DStack_14,(LPOVERLAPPED)0x0);
  return;
}


// 00021004 GameState_Ctor

int GameState_Ctor(GameState *this)

{
  GameState *this_00;
  int iVar1;
  
  iVar1 = 0x1c2;
  this_00 = this;
  do {
    Rec9ec_Ctor(this_00->scenes);
    iVar1 = iVar1 + -1;
    this_00 = (GameState *)(this_00->scenes + 1);
  } while (iVar1 != 0);
  Inventory_Ctor(&this->inventory);
  Book_Ctor(&this->book);
  return (int)this;
}


// 00021060 GameState_Dtor

void GameState_Dtor(GameState *this)

{
  Rec9ec *this_00;
  int iVar1;
  
  Book_Dtor(&this->book);
  this_00 = (Rec9ec *)&this->inventory;
  Inventory_Dtor((Inventory *)this_00);
  iVar1 = 0x1c2;
  do {
    this_00 = this_00 + -1;
    Rec9ec_Dtor(this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 000210b8 GameState_NewGame

void GameState_NewGame(GameState *this)

{
  ushort uVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  Rec9ec *this_00;
  uint uVar5;
  CString local_1c;
  
  Book_LoadText(&this->book);
  puVar2 = (uint *)CTime_GetCurrentTime(&local_1c);
  puVar3 = &this->lastTime;
  *puVar3 = *puVar2;
  local_1c.str = (wchar_t *)*puVar3;
  puVar2 = (uint *)CTime_Sub((int *)puVar3,(int *)&local_1c,(int)local_1c.str);
  this->playTime = *puVar2;
  uVar1 = ReadDataIndexCount();
  if (0 < (short)uVar1) {
    uVar5 = 1;
    do {
      ReadDataRecord(&local_1c,uVar5);
      this_00 = this->scenes + uVar5;
      Rec9ec_SetName(this_00,local_1c);
      Rec9ec_Set1(this_00,0);
      Rec9ec_Set3(this_00,0);
      Rec9ec_Set2(this_00,1);
      uVar4 = ReadDataRecord2(uVar5);
      Rec9ec_Set0(this_00,(char)uVar4);
      uVar5 = (int)((uVar5 + 1) * 0x10000) >> 0x10;
    } while ((int)uVar5 <= (int)(short)uVar1);
  }
  return;
}


// 000211bc CTime_Sub

int * CTime_Sub(int *param_1,int *param_2,int param_3)

{
  *param_2 = *param_1 - param_3;
  return param_2;
}


// 000211d0 GameState_InitScene

void GameState_InitScene(GameState *this,uint param_2)

{
  if ((g_scratchSceneGuard & 1) == 0) {
    g_scratchSceneGuard = g_scratchSceneGuard | 1;
    Scene_Ctor(&g_scratchScene);
    atexit(&LAB_0002123c);
  }
  LoadSceneScript((int)&g_scratchScene,param_2,0);
  Rec9ec_InitFromScene(this->scenes,param_2,(int)&g_scratchScene);
  return;
}


// 00021248 Rec9ec_InitFromScene

void Rec9ec_InitFromScene(Rec9ec *this,uint param_2,int param_3)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  int iVar5;
  RecF8 *pRVar6;
  Rec9 *pRVar7;
  RecE1 *this_00;
  Zoom *pZVar8;
  uint uVar9;
  uint uVar10;
  Rec9ec *this_01;
  uint uVar11;
  CString aCStack_50 [2];
  CString aCStack_48 [4];
  CString aCStack_38 [2];
  CString aCStack_30 [3];
  
  this_01 = this + (param_2 & 0xffff);
  Rec9ec_Set2(this_01,0);
  uVar1 = Scene_Get1259b((Scene *)param_3);
  Rec9ec_Set5(this_01,uVar1);
  uVar1 = Scene_Get12599((Scene *)param_3);
  Rec9ec_Set6(this_01,uVar1);
  uVar1 = Scene_GetF1259c((Scene *)param_3);
  Rec9ec_Set7(this_01,uVar1);
  uVar1 = Scene_Get1259a((Scene *)param_3);
  Rec9ec_Set8(this_01,uVar1);
  iVar5 = Scene_GetKind((Scene *)param_3);
  if (iVar5 == 2) {
    cVar2 = Scene_GetNumObjs((Scene *)param_3);
    uVar9 = 0;
    if (0 < cVar2) {
      do {
        pRVar6 = Scene_GetObj((Scene *)param_3,uVar9);
        uVar1 = RecF8_IsVisible(pRVar6);
        pRVar7 = Rec9ec_GetObjState(this_01,uVar9);
        Rec9_SetVisible(pRVar7,uVar1);
        pRVar6 = Scene_GetObj((Scene *)param_3,uVar9);
        cVar3 = RecF8_GetNumActions(pRVar6);
        if (0 < cVar3) {
          uVar10 = 0;
          do {
            pRVar6 = Scene_GetObj((Scene *)param_3,uVar9);
            iVar5 = RecF8_GetSub14(pRVar6,(int)aCStack_50,uVar10);
            pRVar7 = Rec9ec_GetObjState(this_01,uVar9);
            Rec9_SetFlag(pRVar7,uVar10,*(undefined1 *)(iVar5 + 4));
            CString_Dtor(aCStack_48);
            CString_Dtor(aCStack_50);
            uVar10 = (int)((uVar10 + 1) * 0x1000000) >> 0x18;
          } while ((int)uVar10 < (int)cVar3);
        }
        uVar9 = uVar9 + 1;
      } while ((int)(uVar9 * 0x1000000) >> 0x18 < (int)cVar2);
    }
    cVar2 = Scene_GetNumExits((Scene *)param_3);
    uVar9 = 0;
    if (0 < cVar2) {
      do {
        this_00 = Rec9ec_GetRecE1(this_01,uVar9);
        pZVar8 = (Zoom *)Scene_GetZoom((Scene *)param_3,uVar9);
        cVar3 = Zoom_GetCount(pZVar8);
        uVar10 = 0;
        if (0 < cVar3) {
          do {
            pZVar8 = (Zoom *)Scene_GetZoom((Scene *)param_3,uVar9);
            pRVar6 = Zoom_GetRec(pZVar8,uVar10);
            uVar1 = RecF8_IsVisible(pRVar6);
            pRVar7 = RecE1_GetObjState(this_00,uVar10);
            Rec9_SetVisible(pRVar7,uVar1);
            pZVar8 = (Zoom *)Scene_GetZoom((Scene *)param_3,uVar9);
            pRVar6 = Zoom_GetRec(pZVar8,uVar10);
            cVar4 = RecF8_GetNumActions(pRVar6);
            if (0 < cVar4) {
              uVar11 = 0;
              do {
                pZVar8 = (Zoom *)Scene_GetZoom((Scene *)param_3,uVar9);
                pRVar6 = Zoom_GetRec(pZVar8,uVar10);
                iVar5 = RecF8_GetSub14(pRVar6,(int)aCStack_38,uVar11);
                pRVar7 = RecE1_GetObjState(this_00,uVar10);
                Rec9_SetFlag(pRVar7,uVar11,*(undefined1 *)(iVar5 + 4));
                CString_Dtor(aCStack_30);
                CString_Dtor(aCStack_38);
                uVar11 = (int)((uVar11 + 1) * 0x1000000) >> 0x18;
              } while ((int)uVar11 < (int)cVar4);
            }
            uVar10 = uVar10 + 1;
          } while ((int)(uVar10 * 0x1000000) >> 0x18 < (int)cVar3);
        }
        uVar9 = uVar9 + 1;
      } while ((int)(uVar9 * 0x1000000) >> 0x18 < (int)cVar2);
    }
  }
  return;
}


// 00021510 GameState_SetCurScene

void GameState_SetCurScene(GameState *this,ushort param_2)

{
  this->curScene = param_2;
  return;
}


// 00021520 GameState_GetCurScene

ushort GameState_GetCurScene(GameState *this)

{
  return this->curScene;
}


// 00021530 WriteSaveFile

void WriteSaveFile(GameState *this,uint param_2,Screen *param_3)

{
  int iVar1;
  char cVar2;
  ushort uVar3;
  uint *puVar4;
  int *piVar5;
  Tm *pTVar6;
  CString *pCVar7;
  HANDLE hFile;
  uint uVar8;
  int iVar9;
  Screen *pSVar10;
  ushort *puVar11;
  char local_60;
  char local_5f;
  char local_5e;
  char local_5d;
  char local_5c [4];
  DWORD DStack_58;
  CString local_54;
  uint local_50;
  CString CStack_4c;
  CString local_48;
  undefined4 local_44;
  int local_40;
  int iStack_3c;
  ushort *local_38 [3];
  int iStack_2c;
  int iStack_28;
  
  local_54.str = g_afxEmptyString;
  CString_CtorA(&CStack_4c,s_Menu_smallfade_bmp_00043c80);
  CString_Plus(&local_48,&g_installDir,&CStack_4c);
  LoadImage(local_48,&iStack_28,&iStack_2c,local_38,1);
  CString_Dtor(&CStack_4c);
  puVar4 = (uint *)CTime_GetCurrentTime(&local_48);
  local_50 = *puVar4;
  local_48.str = (wchar_t *)this->lastTime;
  piVar5 = CTime_Sub((int *)&local_50,(int *)&CStack_4c,(int)local_48.str);
  local_48.str = (wchar_t *)*piVar5;
  puVar4 = (uint *)CTime_Add((int *)&this->playTime,&iStack_3c,(int)local_48.str);
  this->playTime = *puVar4;
  this->lastTime = local_50;
  pTVar6 = CTime_GetLocalTm(&local_50,(undefined1 *)0x0);
  local_5c[0] = (char)pTVar6->mon + '\x01';
  pTVar6 = CTime_GetLocalTm(&local_50,(undefined1 *)0x0);
  local_5d = (char)pTVar6->mday;
  local_44 = __rt_udiv(0x15180,this->playTime);
  uVar8 = this->playTime;
  cVar2 = __rt_udiv(0x15180,uVar8);
  local_5e = __rt_udiv(0xe10,uVar8);
  local_5e = local_5e + cVar2 * -0x18;
  cVar2 = __rt_udiv(0xe10,uVar8);
  local_5f = __rt_udiv(0x3c,uVar8);
  local_5f = local_5f + cVar2 * -0x3c;
  cVar2 = __rt_udiv(0x3c,uVar8);
  local_60 = (char)uVar8 + cVar2 * -0x3c;
  CString_CtorA(&CStack_4c,s_save_save_00043c04);
  pCVar7 = CString_Plus(&local_48,&g_installDir,&CStack_4c);
  CString_Assign(&local_54,pCVar7);
  CString_Dtor(&local_48);
  CString_Dtor(&CStack_4c);
  CString_AppendChar(&local_54,(short)(char)((param_2 + 0x30) * 0x1000000 >> 0x18));
  CString_CtorA(&CStack_4c,s__fad_00043bfc);
  CString_Append(&local_54,&CStack_4c);
  CString_Dtor(&CStack_4c);
  hFile = CreateFileW(local_54.str,0x40000000,1,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  WriteFile(hFile,&this->curScene,2,&DStack_58,(LPOVERLAPPED)0x0);
  WriteFile(hFile,local_5c,1,&DStack_58,(LPOVERLAPPED)0x0);
  WriteFile(hFile,&local_5d,1,&DStack_58,(LPOVERLAPPED)0x0);
  WriteFile(hFile,&local_44,4,&DStack_58,(LPOVERLAPPED)0x0);
  WriteFile(hFile,&local_5e,1,&DStack_58,(LPOVERLAPPED)0x0);
  WriteFile(hFile,&local_5f,1,&DStack_58,(LPOVERLAPPED)0x0);
  WriteFile(hFile,&local_60,1,&DStack_58,(LPOVERLAPPED)0x0);
  local_40 = (uint)this->curScene +
             ((((local_60 * 2 + (int)local_5f) * 2 + (int)local_5e) * 2 + (int)local_5d) * 2 +
             (int)local_5c[0]) * 2;
  WriteFile(hFile,&local_40,4,&DStack_58,(LPOVERLAPPED)0x0);
  Book_Save(&this->book,hFile);
  Inventory_SaveState(&this->inventory,hFile);
  uVar3 = ReadDataIndexCount();
  iVar1 = (int)(short)uVar3;
  if (0 < iVar1) {
    iVar9 = 1;
    do {
      Rec9ec_Save(this->scenes + iVar9,hFile);
      pSVar10 = param_3;
      puVar11 = local_38[0];
      cVar2 = __rt_sdiv(iVar1,iVar9 * 0x50);
      DrawSaveProgress(this,8,(param_2 & 0xff) * 0x44 - 0x3d,(int)cVar2 & 0xffff,(int)pSVar10,
                       puVar11);
      iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
    } while (iVar9 <= iVar1);
  }
  CloseHandle(hFile);
  free(local_38[0]);
  CString_Dtor(&local_54);
  return;
}


// 000219c8 CTime_Add

int * CTime_Add(int *param_1,int *param_2,int param_3)

{
  *param_2 = *param_1 + param_3;
  return param_2;
}


// 000219dc DrawSaveProgress

void DrawSaveProgress(undefined4 param_1,uint param_2,uint param_3,uint param_4,int param_5,
                     undefined2 *param_6)

{
  Screen_DrawDirectStride
            ((Screen *)param_5,param_2 & 0xffff,param_3 & 0xffff,0x50,0x3c,param_4 & 0xffff,param_6)
  ;
  return;
}


// 00021a24 ReadSaveFile

int ReadSaveFile(GameState *this,uint param_2,Screen *param_3)

{
  char cVar1;
  ushort uVar2;
  CString *pCVar3;
  HANDLE hFile;
  int iVar4;
  uint uVar5;
  Screen *pSVar6;
  ushort *puVar7;
  char local_58;
  char local_57;
  char local_56;
  char local_55;
  char local_54 [4];
  DWORD DStack_50;
  CString local_4c;
  CString CStack_48;
  CString local_44;
  int local_40;
  int local_3c;
  ushort *local_38 [3];
  int iStack_2c;
  int iStack_28;
  
  local_4c.str = g_afxEmptyString;
  CString_CtorA(&CStack_48,s_Menu_smallfade_bmp_00043c80);
  CString_Plus(&local_44,&g_installDir,&CStack_48);
  LoadImage(local_44,&iStack_28,&iStack_2c,local_38,1);
  CString_Dtor(&CStack_48);
  Book_LoadText(&this->book);
  GameState_OnActivate(this);
  CString_CtorA(&CStack_48,s_save_save_00043c04);
  pCVar3 = CString_Plus(&local_44,&g_installDir,&CStack_48);
  CString_Assign(&local_4c,pCVar3);
  CString_Dtor(&local_44);
  CString_Dtor(&CStack_48);
  CString_AppendChar(&local_4c,(short)(char)((param_2 + 0x30) * 0x1000000 >> 0x18));
  CString_CtorA(&CStack_48,s__fad_00043bfc);
  CString_Append(&local_4c,&CStack_48);
  CString_Dtor(&CStack_48);
  hFile = CreateFileW(local_4c.str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffff) {
    iVar4 = 0;
  }
  else {
    ReadFile(hFile,&this->curScene,2,&DStack_50,(LPOVERLAPPED)0x0);
    ReadFile(hFile,local_54,1,&DStack_50,(LPOVERLAPPED)0x0);
    ReadFile(hFile,&local_55,1,&DStack_50,(LPOVERLAPPED)0x0);
    ReadFile(hFile,&local_40,4,&DStack_50,(LPOVERLAPPED)0x0);
    ReadFile(hFile,&local_56,1,&DStack_50,(LPOVERLAPPED)0x0);
    ReadFile(hFile,&local_57,1,&DStack_50,(LPOVERLAPPED)0x0);
    ReadFile(hFile,&local_58,1,&DStack_50,(LPOVERLAPPED)0x0);
    this->playTime =
         ((local_40 * 0x18 + (int)local_56) * 0x3c + (int)local_57) * 0x3c + (int)local_58;
    ReadFile(hFile,&local_3c,4,&DStack_50,(LPOVERLAPPED)0x0);
    if (local_3c !=
        (uint)this->curScene +
        ((((local_58 * 2 + (int)local_57) * 2 + (int)local_56) * 2 + (int)local_55) * 2 +
        (int)local_54[0]) * 2) {
      MessageBoxW((HWND)0x0,u_Error_SaveFile_is_not_valid___00043c94,u_Fade_00043458,0x10);
      CloseHandle(hFile);
      iVar4 = 0;
      goto LAB_00021de4;
    }
    Book_Load(&this->book,hFile);
    Inventory_LoadState(&this->inventory,hFile);
    uVar2 = ReadDataIndexCount();
    uVar5 = 1;
    iVar4 = (int)(short)uVar2;
    if (0 < iVar4) {
      do {
        Rec9ec_Load(this->scenes + uVar5,hFile);
        ReadDataRecord(&local_44,uVar5);
        Rec9ec_SetName(this->scenes + uVar5,local_44);
        pSVar6 = param_3;
        puVar7 = local_38[0];
        cVar1 = __rt_sdiv(iVar4,uVar5 * 0x50);
        DrawSaveProgress(this,8,(param_2 & 0xff) * 0x44 - 0x3d,(int)cVar1 & 0xffff,(int)pSVar6,
                         puVar7);
        uVar5 = (int)((uVar5 + 1) * 0x10000) >> 0x10;
      } while ((int)uVar5 <= iVar4);
    }
    CloseHandle(hFile);
    iVar4 = 1;
  }
  free(local_38[0]);
LAB_00021de4:
  CString_Dtor(&local_4c);
  return iVar4;
}


// 00021df8 GameState_OnActivate

void GameState_OnActivate(GameState *this)

{
  uint *puVar1;
  undefined1 auStack_c [4];
  
  puVar1 = (uint *)CTime_GetCurrentTime(auStack_c);
  this->lastTime = *puVar1;
  return;
}


// 00021e24 GameState_OnDeactivate

void GameState_OnDeactivate(GameState *this)

{
  int *piVar1;
  uint *puVar2;
  uint local_1c;
  int local_18;
  int iStack_14;
  int iStack_10;
  
  piVar1 = (int *)CTime_GetCurrentTime(&local_1c);
  local_18 = *piVar1;
  local_1c = this->lastTime;
  puVar2 = (uint *)CTime_Sub(&local_18,&iStack_14,local_1c);
  local_1c = *puVar2;
  puVar2 = (uint *)CTime_Add((int *)&this->playTime,&iStack_10,local_1c);
  this->playTime = *puVar2;
  return;
}


// 00021e98 GameObj_Ctor

int GameObj_Ctor(GameObj *this)

{
  Rec14 *pRVar1;
  int iVar2;
  ScriptOpList *this_00;
  
  iVar2 = 8;
  (this->name).str = g_afxEmptyString;
  pRVar1 = this->subs;
  do {
    iVar2 = iVar2 + -1;
    (pRVar1->label).str = g_afxEmptyString;
    (pRVar1->text).str = g_afxEmptyString;
    pRVar1 = pRVar1 + 1;
  } while (iVar2 != 0);
  this_00 = this->scripts;
  iVar2 = 0x1e;
  do {
    ScriptOpList_Ctor(this_00);
    iVar2 = iVar2 + -1;
    this_00 = this_00 + 1;
  } while (iVar2 != 0);
  return (int)this;
}


// 00021f00 GameObj_Dtor

void GameObj_Dtor(GameObj *this)

{
  ScriptOpList *this_00;
  Rec14 *pRVar1;
  int iVar2;
  
  this_00 = (ScriptOpList *)&this->link;
  iVar2 = 0x1e;
  do {
    this_00 = this_00 + -1;
    ScriptOpList_Dtor(this_00);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar2 = 8;
  pRVar1 = (Rec14 *)&this->fbc;
  do {
    CString_Dtor(&pRVar1[-1].text);
    CString_Dtor(&pRVar1[-1].label);
    iVar2 = iVar2 + -1;
    pRVar1 = pRVar1 + -1;
  } while (iVar2 != 0);
  CString_Dtor(&this->name);
  return;
}


// 00021f64 GameObj_Assign

void GameObj_Assign(GameObj *this,GameObj *param_2)

{
  bool bVar1;
  undefined2 uVar2;
  Link LVar3;
  byte bVar4;
  ImgRect *pIVar5;
  CString *pCVar6;
  Rec14 *pRVar7;
  ScriptOpList *pSVar8;
  Link *pLVar9;
  int iVar10;
  int iVar11;
  GameObj *pGVar12;
  uint uVar13;
  Link aLStack_44 [2];
  CString aCStack_3c [2];
  CString aCStack_34 [4];
  ImgRect IStack_24;
  
  pIVar5 = GameObj_GetIcon(param_2,&IStack_24);
  iVar10 = 0x14;
  pGVar12 = this;
  do {
    iVar11 = iVar10 + -1;
    *(undefined1 *)&(pGVar12->icon).pixels = *(undefined1 *)&pIVar5->pixels;
    bVar1 = 0 < iVar10;
    pIVar5 = (ImgRect *)((int)&pIVar5->pixels + 1);
    iVar10 = iVar11;
    pGVar12 = (GameObj *)((int)&(pGVar12->icon).pixels + 1);
  } while (iVar11 != 0 && bVar1);
  pCVar6 = GameObj_GetName(param_2,(CString *)aLStack_44);
  CString_Assign(&this->name,pCVar6);
  CString_Dtor((CString *)aLStack_44);
  bVar4 = GameObj_GetId(param_2);
  this->id = bVar4;
  bVar4 = GameObj_IsSelected(param_2);
  this->selected = bVar4;
  bVar4 = GameObj_GetNumSubs(param_2);
  this->nSubs = bVar4;
  if (bVar4 != 0) {
    uVar13 = 0;
    do {
      pRVar7 = (Rec14 *)GameObj_GetSub14(param_2,(int)aCStack_3c,uVar13);
      Rec14_Assign(this->subs + uVar13,pRVar7);
      CString_Dtor(aCStack_34);
      CString_Dtor(aCStack_3c);
      uVar13 = (int)((uVar13 + 1) * 0x1000000) >> 0x18;
    } while ((int)uVar13 < (int)(uint)this->nSubs);
  }
  uVar13 = GameObj_GetBc(param_2);
  this->fbc = (byte)uVar13;
  if ((uVar13 & 0xff) != 0) {
    uVar13 = 0;
    do {
      pSVar8 = GameObj_GetScript(param_2,uVar13);
      ScriptOpList_Assign(this->scripts + uVar13,pSVar8);
      uVar13 = (int)((uVar13 + 1) * 0x1000000) >> 0x18;
    } while ((int)uVar13 < (int)(uint)this->fbc);
  }
  pLVar9 = GameObj_GetField8220(param_2,aLStack_44);
  LVar3 = *pLVar9;
  (this->link).id = LVar3.id;
  uVar2 = LVar3._2_2_;
  (this->link).script = (char)uVar2;
  (this->link).f3 = (char)((ushort)uVar2 >> 8);
  bVar4 = GameObj_GetF8224(param_2);
  *(byte *)&this->f8224 = bVar4;
  return;
}


// 000220f0 Rec14_Assign

int Rec14_Assign(Rec14 *this,Rec14 *param_2)

{
  CString_Assign(&this->label,&param_2->label);
  this->enabled = param_2->enabled;
  CString_Assign(&this->text,&param_2->text);
  this->kind = param_2->kind;
  this->arg = param_2->arg;
  this->b11 = param_2->b11;
  this->b12 = param_2->b12;
  return (int)this;
}


// 0002213c GameObj_GetField8220

Link * GameObj_GetField8220(GameObj *this,Link *param_2)

{
  undefined2 uVar1;
  Link LVar2;
  
  LVar2 = this->link;
  param_2->id = LVar2.id;
  uVar1 = LVar2._2_2_;
  param_2->script = (char)uVar1;
  param_2->f3 = (char)((ushort)uVar1 >> 8);
  return param_2;
}


// 00022168 GameObj_GetF8224

byte GameObj_GetF8224(GameObj *this)

{
  return (byte)this->f8224;
}


// 00022178 GameObj_GetIcon

ImgRect * GameObj_GetIcon(GameObj *this,ImgRect *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  ImgRect *pIVar4;
  
  iVar2 = 0x14;
  pIVar4 = param_2;
  do {
    iVar3 = iVar2 + -1;
    *(undefined1 *)&pIVar4->pixels = *(undefined1 *)&(this->icon).pixels;
    bVar1 = 0 < iVar2;
    this = (GameObj *)((int)&(this->icon).pixels + 1);
    iVar2 = iVar3;
    pIVar4 = (ImgRect *)((int)&pIVar4->pixels + 1);
  } while (iVar3 != 0 && bVar1);
  return param_2;
}


// 0002219c GameObj_GetName

CString * GameObj_GetName(GameObj *this,CString *param_2)

{
  CString_CopyCtor(param_2,&this->name);
  return param_2;
}


// 000221b8 GameObj_GetId

byte GameObj_GetId(GameObj *this)

{
  return this->id;
}


// 000221c0 GameObj_IsSelected

byte GameObj_IsSelected(GameObj *this)

{
  return this->selected;
}


// 000221c8 GameObj_SetSelected

void GameObj_SetSelected(GameObj *this,byte param_2)

{
  this->selected = param_2;
  return;
}


// 000221d0 GameObj_GetNumSubs

byte GameObj_GetNumSubs(GameObj *this)

{
  return this->nSubs;
}


// 000221d8 GameObj_GetSub14

int GameObj_GetSub14(GameObj *this,int param_2,uint param_3)

{
  Rec14_Copy((Rec14 *)param_2,this->subs + (param_3 & 0xff));
  return param_2;
}


// 00022204 GameObj_SetSubFlag

void GameObj_SetSubFlag(GameObj *this,uint param_2,byte param_3)

{
  this->subs[param_2 & 0xff].enabled = param_3;
  return;
}


// 0002221c GameObj_FreeBuf

void GameObj_FreeBuf(GameObj *this)

{
  free((this->icon).pixels);
  return;
}


// 00022224 GameObj_GetBc

int GameObj_GetBc(GameObj *this)

{
  return (int)(char)this->fbc;
}


// 0002222c GameObj_GetScript

ScriptOpList * GameObj_GetScript(GameObj *this,uint param_2)

{
  return this->scripts + (param_2 & 0xff);
}


// 00022244 GameObj_GetScripts

ScriptOpList * GameObj_GetScripts(GameObj *this)

{
  return this->scripts;
}


// 0002224c ParseObjectRecord

void ParseObjectRecord(GameObj *this,char *param_2)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  bool bVar5;
  CString *pCVar6;
  int iVar7;
  int iVar8;
  CString *pCVar9;
  wchar_t *pwVar10;
  ScriptOpList *pSVar11;
  uint uVar12;
  uint uVar13;
  char *local_48c;
  CString local_488;
  CString CStack_484;
  CString local_480;
  CString CStack_47c;
  CString CStack_478;
  ScriptOpList SStack_474;
  
  local_480.str = g_afxEmptyString;
  local_48c = param_2;
  pCVar6 = Fad_ReadString(&CStack_484,&local_48c);
  CString_Assign(&this->name,pCVar6);
  CString_Dtor(&CStack_484);
  iVar7 = Fad_ReadInt(&local_48c);
  this->id = (byte)iVar7;
  this->selected = 1;
  iVar7 = 0xffff;
  uVar13 = 0xff;
  uVar12 = 0xff;
  bVar2 = false;
  do {
    iVar8 = Fad_ReadU16AfterUnderscore(&local_48c);
    cVar4 = (char)iVar8;
    cVar3 = (char)((uint)iVar8 >> 8);
    if (cVar3 == 'F') {
      bVar2 = true;
    }
    else if (cVar3 == 'O') {
      if (cVar4 == 'b') {
        uVar12 = Fad_ReadInt(&local_48c);
        uVar12 = uVar12 & 0xff;
      }
    }
    else if (cVar3 == 'S') {
      if (cVar4 == 'c') {
        iVar7 = Fad_ReadInt(&local_48c);
      }
    }
    else if ((cVar3 == 'Z') && (cVar4 == 'o')) {
      uVar13 = Fad_ReadInt(&local_48c);
      uVar13 = uVar13 & 0xff;
    }
  } while (!bVar2);
  (this->link).f3 = (byte)uVar12;
  (this->link).id = (ushort)iVar7;
  (this->link).script = (byte)uVar13;
  iVar7 = Fad_ReadInt(&local_48c);
  *(char *)&this->f8224 = (char)iVar7;
  pCVar6 = Fad_ReadString(&local_488,&local_48c);
  CString_CtorA(&CStack_484,s_inventaire__00043cd0);
  pCVar9 = CString_Plus(&CStack_47c,&g_installDir,&CStack_484);
  pCVar6 = CString_Plus(&CStack_478,pCVar9,pCVar6);
  CString_Assign(&local_480,pCVar6);
  CString_Dtor(&CStack_478);
  CString_Dtor(&CStack_47c);
  CString_Dtor(&local_488);
  CString_Dtor(&CStack_484);
  (this->icon).x = 0;
  (this->icon).y = 0;
  pwVar10 = CString_GetBuffer(&local_480,*(int *)(local_480.str + -4));
  CString_CtorW(&local_488,pwVar10);
  LoadImage(local_488,&(this->icon).h,&(this->icon).w,(ushort **)this,1);
  this->fbc = 0;
  bVar2 = false;
  this->nSubs = 0;
  do {
    cVar4 = Fad_ReadCharAfterUnderscore(&local_48c);
    if (cVar4 == 'A') {
      pSVar11 = (ScriptOpList *)ParseSceneScript(&SStack_474,&local_48c);
      ScriptOpList_Assign(this->scripts + this->fbc,pSVar11);
      ScriptOpList_Dtor(&SStack_474);
      this->fbc = this->fbc + 1;
    }
    else if (cVar4 == 'F') {
      bVar2 = true;
    }
    else if (cVar4 == 'P') {
      pCVar6 = Fad_ReadString(&local_488,&local_48c);
      CString_Assign(&this->subs[this->nSubs].label,pCVar6);
      CString_Dtor(&local_488);
      cVar4 = Fad_ReadCharAfterUnderscore(&local_48c);
      if (cVar4 == 'A') {
        this->subs[this->nSubs].kind = 2;
        bVar5 = Fad_ReadBool(&local_48c);
        this->subs[this->nSubs].enabled = bVar5;
LAB_00022618:
        iVar7 = Fad_ReadInt(&local_48c);
        this->subs[this->nSubs].arg = (byte)iVar7;
      }
      else {
        if (cVar4 == 'C') {
          bVar1 = this->nSubs;
          uVar13 = 4;
LAB_000225b4:
          this->subs[bVar1].kind = uVar13;
          bVar5 = Fad_ReadBool(&local_48c);
          this->subs[this->nSubs].enabled = bVar5;
          iVar7 = Fad_ReadInt(&local_48c);
          this->subs[this->nSubs].b11 = (byte)iVar7;
          goto LAB_00022618;
        }
        if (cVar4 == 'D') {
          this->subs[this->nSubs].kind = 0;
          bVar5 = Fad_ReadBool(&local_48c);
          this->subs[this->nSubs].enabled = bVar5;
          pCVar6 = Fad_ReadString(&CStack_47c,&local_48c);
          CString_Assign(&this->subs[this->nSubs].text,pCVar6);
          CString_Dtor(&CStack_47c);
        }
        else {
          if (cVar4 == 'U') {
            bVar1 = this->nSubs;
            uVar13 = 3;
            goto LAB_000225b4;
          }
          if (cVar4 == 'Z') {
            this->subs[this->nSubs].kind = 1;
            bVar5 = Fad_ReadBool(&local_48c);
            this->subs[this->nSubs].enabled = bVar5;
            iVar7 = Fad_ReadInt(&local_48c);
            this->subs[this->nSubs].b12 = (byte)iVar7;
          }
        }
      }
      this->nSubs = this->nSubs + 1;
    }
    if (bVar2) {
      CString_Dtor(&local_480);
      return;
    }
  } while( true );
}


// 000226a4 ReadObjectIndex

uint ReadObjectIndex(uint param_1)

{
  CString *pCVar1;
  HANDLE hFile;
  CString CStack_20;
  CString CStack_1c;
  uint local_18;
  DWORD DStack_14;
  
  CString_CtorA(&CStack_20,s_data_indexobjets_fad_00043b84);
  pCVar1 = CString_Plus(&CStack_1c,&g_installDir,&CStack_20);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_1c);
  CString_Dtor(&CStack_20);
  SetFilePointer(hFile,(param_1 & 0xffff) << 2,(PLONG)0x0,0);
  ReadFile(hFile,&local_18,4,&DStack_14,(LPOVERLAPPED)0x0);
  CloseHandle(hFile);
  return local_18;
}


// 0002275c LoadObjectRecord

void LoadObjectRecord(undefined4 *param_1,uint param_2)

{
  uint lDistanceToMove;
  uint uVar1;
  byte *lpBuffer;
  CString *pCVar2;
  HANDLE hFile;
  byte *pbVar3;
  DWORD nNumberOfBytesToRead;
  CString CStack_28;
  CString CStack_24;
  DWORD DStack_20;
  
  lDistanceToMove = ReadObjectIndex(param_2 & 0xff);
  uVar1 = ReadObjectIndex((param_2 & 0xff) + 1);
  nNumberOfBytesToRead = (uVar1 - lDistanceToMove) - 1;
  lpBuffer = (byte *)operator_new(nNumberOfBytesToRead);
  CString_CtorA(&CStack_28,s_data_dataobjets_fad_00043cdc);
  pCVar2 = CString_Plus(&CStack_24,&g_installDir,&CStack_28);
  hFile = CreateFileW(pCVar2->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_24);
  CString_Dtor(&CStack_28);
  SetFilePointer(hFile,lDistanceToMove,(PLONG)0x0,0);
  ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,&DStack_20,(LPOVERLAPPED)0x0);
  CloseHandle(hFile);
  pbVar3 = lpBuffer;
  for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
    *pbVar3 = *pbVar3 ^ 0x77;
    pbVar3 = pbVar3 + 1;
  }
  ParseObjectRecord((GameObj *)param_1,lpBuffer);
  free(lpBuffer);
  return;
}


// 0002286c GameObj_LoadState

void GameObj_LoadState(GameObj *this,HANDLE param_2)

{
  int iVar1;
  DWORD DStack_24;
  undefined1 auStack_20 [4];
  
  ReadFile(param_2,&this->nSubs,1,&DStack_24,(LPOVERLAPPED)0x0);
  ReadFile(param_2,&this->id,1,&DStack_24,(LPOVERLAPPED)0x0);
  LoadObjectRecord((undefined4 *)this,(uint)this->id);
  ReadFile(param_2,&this->selected,1,&DStack_24,(LPOVERLAPPED)0x0);
  ReadFile(param_2,&this->fbc,1,&DStack_24,(LPOVERLAPPED)0x0);
  ReadFile(param_2,auStack_20,4,&DStack_24,(LPOVERLAPPED)0x0);
  ReadFile(param_2,&this->f8224,1,&DStack_24,(LPOVERLAPPED)0x0);
  if (this->nSubs != 0) {
    iVar1 = 0;
    do {
      ReadFile(param_2,&this->subs[iVar1].enabled,1,&DStack_24,(LPOVERLAPPED)0x0);
      ReadFile(param_2,&this->subs[iVar1].arg,1,&DStack_24,(LPOVERLAPPED)0x0);
      ReadFile(param_2,&this->subs[iVar1].b11,1,&DStack_24,(LPOVERLAPPED)0x0);
      ReadFile(param_2,&this->subs[iVar1].b12,1,&DStack_24,(LPOVERLAPPED)0x0);
      ReadFile(param_2,&this->subs[iVar1].kind,1,&DStack_24,(LPOVERLAPPED)0x0);
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
    } while (iVar1 < (int)(uint)this->nSubs);
  }
  return;
}


// 000229e4 GameObj_SaveState

void GameObj_SaveState(GameObj *this,HANDLE param_2)

{
  int iVar1;
  DWORD DStack_20;
  
  WriteFile(param_2,&this->nSubs,1,&DStack_20,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->id,1,&DStack_20,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->selected,1,&DStack_20,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->fbc,1,&DStack_20,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->link,4,&DStack_20,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->f8224,1,&DStack_20,(LPOVERLAPPED)0x0);
  if (this->nSubs != 0) {
    iVar1 = 0;
    do {
      WriteFile(param_2,&this->subs[iVar1].enabled,1,&DStack_20,(LPOVERLAPPED)0x0);
      WriteFile(param_2,&this->subs[iVar1].arg,1,&DStack_20,(LPOVERLAPPED)0x0);
      WriteFile(param_2,&this->subs[iVar1].b11,1,&DStack_20,(LPOVERLAPPED)0x0);
      WriteFile(param_2,&this->subs[iVar1].b12,1,&DStack_20,(LPOVERLAPPED)0x0);
      WriteFile(param_2,&this->subs[iVar1].kind,1,&DStack_20,(LPOVERLAPPED)0x0);
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
    } while (iVar1 < (int)(uint)this->nSubs);
  }
  return;
}


// 00022b58 Inventory_Ctor

Inventory * Inventory_Ctor(Inventory *this)

{
  GameObj *this_00;
  int iVar1;
  
  this_00 = this->objs;
  iVar1 = 0x28;
  do {
    GameObj_Ctor(this_00);
    iVar1 = iVar1 + -1;
    this_00 = this_00 + 1;
  } while (iVar1 != 0);
  this->count = 0;
  return this;
}


// 00022b98 Inventory_Dtor

void Inventory_Dtor(Inventory *this)

{
  Inventory *this_00;
  int iVar1;
  
  iVar1 = 0x28;
  this_00 = this + 1;
  do {
    this_00 = (Inventory *)(this_00[-1].objs + 0x27);
    GameObj_Dtor((GameObj *)this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 00022bd0 Inventory_Count

int Inventory_Count(Inventory *this)

{
  return (int)(char)this->count;
}


// 00022bd8 Inventory_Selected

int Inventory_Selected(Inventory *this)

{
  return (int)(char)this->selected;
}


// 00022be0 Inventory_SetSelected

void Inventory_SetSelected(Inventory *this,byte param_2)

{
  this->selected = param_2;
  return;
}


// 00022be8 Inventory_GetObj

GameObj * Inventory_GetObj(Inventory *this,uint param_2)

{
  return this->objs + (param_2 & 0xff);
}


// 00022c04 Inventory_Add

void Inventory_Add(Inventory *this,int param_2)

{
  char cVar1;
  uint uVar2;
  
  if ((char)this->count < 0x28) {
    GameObj_Assign(this->objs + (char)this->count,(GameObj *)param_2);
    this->count = this->count + 1;
  }
  Inventory_SortByName(this);
  cVar1 = GameObj_GetId((GameObj *)param_2);
  uVar2 = Inventory_IndexOfId(this,cVar1);
  this->selected = (byte)uVar2;
  return;
}


// 00022c64 Inventory_Contains

int Inventory_Contains(Inventory *this,char param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if ('\0' < (char)this->count) {
    iVar2 = 0;
    do {
      cVar1 = GameObj_GetId(this->objs + iVar2);
      iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18;
      if (cVar1 == param_2) {
        iVar3 = 1;
      }
    } while (iVar2 < (char)this->count);
  }
  return iVar3;
}


// 00022ccc Inventory_RemoveAt

void Inventory_RemoveAt(Inventory *this,byte param_2)

{
  int iVar1;
  
  if ((uint)param_2 < (uint)this->selected) {
    this->selected = this->selected - 1;
  }
  GameObj_FreeBuf(this->objs + param_2);
  for (iVar1 = (int)(char)param_2; iVar1 < (char)this->count + -1;
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18) {
    GameObj_Assign(this->objs + iVar1,this->objs + iVar1 + 1);
  }
  this->count = this->count - 1;
  return;
}


// 00022d5c Inventory_Clear

void Inventory_Clear(Inventory *this)

{
  int iVar1;
  
  if ('\0' < (char)this->count) {
    iVar1 = 0;
    do {
      GameObj_FreeBuf(this->objs + iVar1);
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
    } while (iVar1 < (char)this->count);
  }
  this->count = 0;
  return;
}


// 00022db4 Inventory_SortByName

void Inventory_SortByName(Inventory *this)

{
  int iVar1;
  CString *pCVar2;
  CString *pCVar3;
  GameObj *this_00;
  int iVar4;
  GameObj *this_01;
  int iVar5;
  CString CStack_8250;
  CString CStack_824c;
  GameObj GStack_8248;
  
  GameObj_Ctor(&GStack_8248);
  iVar1 = (int)(char)this->count;
  if (0 < iVar1 + -1) {
    iVar5 = 0;
    do {
      iVar4 = (iVar5 + 1) * 0x1000000 >> 0x18;
      if (iVar4 < iVar1) {
        this_01 = this->objs + iVar5;
        do {
          this_00 = this->objs + iVar4;
          pCVar2 = GameObj_GetName(this_00,&CStack_8250);
          pCVar3 = GameObj_GetName(this_01,&CStack_824c);
          iVar1 = wcscmp(pCVar3->str,pCVar2->str);
          CString_Dtor(&CStack_824c);
          CString_Dtor(&CStack_8250);
          if (0 < iVar1) {
            GameObj_Assign(&GStack_8248,this_01);
            GameObj_Assign(this_01,this_00);
            GameObj_Assign(this_00,&GStack_8248);
          }
          iVar4 = (iVar4 + 1) * 0x1000000 >> 0x18;
        } while (iVar4 < (char)this->count);
      }
      iVar1 = (int)(char)this->count;
      iVar5 = (iVar5 + 1) * 0x1000000 >> 0x18;
    } while (iVar5 < iVar1 + -1);
  }
  GameObj_Dtor(&GStack_8248);
  return;
}


// 00022ee4 Inventory_FindSelected

uint Inventory_FindSelected(Inventory *this)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  uVar4 = 0;
  do {
    bVar1 = this->count;
    cVar3 = GameObj_IsSelected(this->objs + uVar4);
    if (cVar3 != '\0') {
      uVar5 = uVar4;
    }
    bVar2 = (int)uVar4 < (int)(char)bVar1;
    uVar4 = uVar4 + 1 & 0xff;
  } while (cVar3 == '\0' && bVar2);
  return uVar5;
}


// 00022f4c Inventory_IndexOfId

uint Inventory_IndexOfId(Inventory *this,char param_2)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0xff;
  uVar4 = 0;
  do {
    bVar1 = this->count;
    cVar3 = GameObj_GetId(this->objs + uVar4);
    if (cVar3 == param_2) {
      uVar5 = uVar4;
    }
    bVar2 = (int)uVar4 < (int)(char)bVar1;
    uVar4 = uVar4 + 1 & 0xff;
  } while (cVar3 != param_2 && bVar2);
  return uVar5;
}


// 00022fbc Inventory_LoadState

void Inventory_LoadState(Inventory *this,HANDLE param_2)

{
  int iVar1;
  byte local_8240 [4];
  DWORD DStack_823c;
  GameObj GStack_8238;
  
  GameObj_Ctor(&GStack_8238);
  local_8240[0] = this->count;
  if ('\0' < (char)local_8240[0]) {
    iVar1 = 0;
    do {
      Inventory_RemoveAt(this,0);
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
    } while (iVar1 < (char)local_8240[0]);
  }
  ReadFile(param_2,local_8240,1,&DStack_823c,(LPOVERLAPPED)0x0);
  if ('\0' < (char)local_8240[0]) {
    iVar1 = 0;
    do {
      GameObj_LoadState(&GStack_8238,param_2);
      Inventory_Add(this,(int)&GStack_8238);
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
    } while (iVar1 < (char)local_8240[0]);
  }
  GameObj_Dtor(&GStack_8238);
  return;
}


// 00023088 Inventory_SelectId

void Inventory_SelectId(Inventory *this,char param_2,byte param_3)

{
  char cVar1;
  int iVar2;
  
  if ('\0' < (char)this->count) {
    iVar2 = 0;
    do {
      cVar1 = GameObj_GetId(this->objs + iVar2);
      if (cVar1 == param_2) {
        GameObj_SetSelected(this->objs + iVar2,param_3);
      }
      iVar2 = (iVar2 + 1) * 0x1000000 >> 0x18;
    } while (iVar2 < (char)this->count);
  }
  return;
}


// 000230f8 Inventory_SaveState

void Inventory_SaveState(Inventory *this,HANDLE param_2)

{
  int iVar1;
  DWORD DStack_14;
  
  WriteFile(param_2,this,1,&DStack_14,(LPOVERLAPPED)0x0);
  if ('\0' < (char)this->count) {
    iVar1 = 0;
    do {
      GameObj_SaveState(this->objs + iVar1,param_2);
      iVar1 = (iVar1 + 1) * 0x1000000 >> 0x18;
    } while (iVar1 < (char)this->count);
  }
  return;
}


// 00023174 Book_Ctor

void Book_Ctor(Book *this)

{
  CString *pCVar1;
  int iVar2;
  
  pCVar1 = this->text;
  iVar2 = 0x4d;
  do {
    iVar2 = iVar2 + -1;
    pCVar1->str = g_afxEmptyString;
    pCVar1 = pCVar1 + 1;
  } while (iVar2 != 0);
  return;
}


// 000231a4 Book_Dtor

void Book_Dtor(Book *this)

{
  CString *this_00;
  int iVar1;
  
  this_00 = (CString *)this->pageLen;
  iVar1 = 0x4d;
  do {
    this_00 = this_00 + -1;
    CString_Dtor(this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 000231cc Book_GetFlag

byte Book_GetFlag(Book *this,char param_2,char param_3)

{
  return this->flags[param_2 * 0xb + (int)param_3];
}


// 000231ec Book_SetFlag

void Book_SetFlag(Book *this,char param_2,char param_3,byte param_4)

{
  this->flags[param_2 * 0xb + (int)param_3] = param_4;
  return;
}


// 00023210 Book_Save

void Book_Save(Book *this,HANDLE param_2)

{
  DWORD DStack_14;
  
  WriteFile(param_2,this,0x4d,&DStack_14,(LPOVERLAPPED)0x0);
  WriteFile(param_2,&this->curPage,1,&DStack_14,(LPOVERLAPPED)0x0);
  return;
}


// 00023264 Book_Load

void Book_Load(Book *this,HANDLE param_2)

{
  DWORD DStack_14;
  
  ReadFile(param_2,this,0x4d,&DStack_14,(LPOVERLAPPED)0x0);
  ReadFile(param_2,&this->curPage,1,&DStack_14,(LPOVERLAPPED)0x0);
  return;
}


// 000232b8 Book_GetText

CString * Book_GetText(Book *this,CString *param_2,char param_3,char param_4)

{
  CString_CopyCtor(param_2,this->text + param_3 * 0xb + (int)param_4);
  return param_2;
}


// 000232f0 Book_GetPageLen

int Book_GetPageLen(Book *this,char param_2)

{
  return (int)(char)this->pageLen[param_2];
}


// 00023304 ReadBookIndex

uint ReadBookIndex(undefined4 param_1,char param_2)

{
  CString *pCVar1;
  HANDLE hFile;
  CString CStack_20;
  CString CStack_1c;
  uint local_18;
  DWORD DStack_14;
  
  CString_CtorA(&CStack_20,s_data_indexbook_fad_00043cf0);
  pCVar1 = CString_Plus(&CStack_1c,&g_installDir,&CStack_20);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_1c);
  CString_Dtor(&CStack_20);
  if (hFile == (HANDLE)0xffffffff) {
    local_18 = 0;
  }
  else {
    SetFilePointer(hFile,(int)param_2 << 2,(PLONG)0x0,0);
    ReadFile(hFile,&local_18,4,&DStack_14,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
  }
  return local_18;
}


// 000233d0 Book_SetCurPage

void Book_SetCurPage(Book *this,byte param_2)

{
  this->curPage = param_2;
  return;
}


// 000233e0 Book_GetCurPage

int Book_GetCurPage(Book *this)

{
  return (int)(char)this->curPage;
}


// 000233f0 LoadBookPage

CString * LoadBookPage(undefined4 param_1,CString *param_2,char param_3,char param_4)

{
  CString *pCVar1;
  HANDLE hFile;
  uint lDistanceToMove;
  uint uVar2;
  byte *lpBuffer;
  byte *pbVar3;
  int iVar4;
  DWORD nNumberOfBytesToRead;
  byte *local_34;
  CString local_30;
  CString CStack_2c;
  CString CStack_28;
  DWORD DStack_24;
  
  local_30.str = g_afxEmptyString;
  CString_CtorA(&CStack_2c,s_data_book_fad_00043d04);
  pCVar1 = CString_Plus(&CStack_28,&g_installDir,&CStack_2c);
  hFile = CreateFileW(pCVar1->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
  CString_Dtor(&CStack_28);
  CString_Dtor(&CStack_2c);
  if (hFile == (HANDLE)0xffffffff) {
    CString_CtorA(param_2,&g_emptyA);
  }
  else {
    lDistanceToMove = ReadBookIndex(param_1,param_3 + '\x01');
    uVar2 = ReadBookIndex(param_1,param_3 + '\x02');
    nNumberOfBytesToRead = uVar2 - lDistanceToMove;
    lpBuffer = (byte *)operator_new(nNumberOfBytesToRead);
    SetFilePointer(hFile,lDistanceToMove,(PLONG)0x0,0);
    ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,&DStack_24,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    pbVar3 = lpBuffer;
    for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
      *pbVar3 = *pbVar3 ^ 0x77;
      pbVar3 = pbVar3 + 1;
    }
    local_34 = lpBuffer;
    local_34 = (byte *)Fad_SkipField((char *)lpBuffer);
    if (0 < param_4) {
      iVar4 = 0;
      do {
        local_34 = (byte *)Fad_SkipField((char *)local_34);
        local_34 = (byte *)Fad_SkipField((char *)local_34);
        local_34 = (byte *)Fad_SkipField((char *)local_34);
        iVar4 = (iVar4 + 1) * 0x1000000 >> 0x18;
      } while (iVar4 < param_4);
    }
    local_34 = (byte *)Fad_SkipField((char *)local_34);
    local_34 = (byte *)Fad_SkipField((char *)local_34);
    pCVar1 = Fad_ReadString(&CStack_28,(char **)&local_34);
    CString_Assign(&local_30,pCVar1);
    CString_Dtor(&CStack_28);
    free(lpBuffer);
    CString_CopyCtor(param_2,&local_30);
  }
  CString_Dtor(&local_30);
  return param_2;
}


// 000235d0 Book_LoadText

void Book_LoadText(Book *this)

{
  int iVar1;
  bool bVar2;
  CString *pCVar3;
  HANDLE hFile;
  uint lDistanceToMove;
  uint uVar4;
  CString lpBuffer;
  wchar_t *pwVar5;
  int iVar6;
  DWORD nNumberOfBytesToRead;
  int iVar7;
  char cVar8;
  wchar_t *local_38;
  CString CStack_34;
  CString CStack_30;
  CString local_2c;
  DWORD DStack_28;
  
  this->curPage = 0;
  cVar8 = '\0';
  lpBuffer.str = local_2c.str;
  do {
    CString_CtorA(&CStack_34,s_data_book_fad_00043d04);
    pCVar3 = CString_Plus(&CStack_30,&g_installDir,&CStack_34);
    hFile = CreateFileW(pCVar3->str,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0x80,(HANDLE)0x0);
    CString_Dtor(&CStack_30);
    CString_Dtor(&CStack_34);
    if (hFile != (HANDLE)0xffffffff) {
      lDistanceToMove = ReadBookIndex(this,cVar8 + '\x01');
      uVar4 = ReadBookIndex(this,cVar8 + '\x02');
      nNumberOfBytesToRead = uVar4 - lDistanceToMove;
      lpBuffer.str = (wchar_t *)operator_new(nNumberOfBytesToRead);
      SetFilePointer(hFile,lDistanceToMove,(PLONG)0x0,0);
      ReadFile(hFile,lpBuffer.str,nNumberOfBytesToRead,&DStack_28,(LPOVERLAPPED)0x0);
      CloseHandle(hFile);
      pwVar5 = lpBuffer.str;
      for (; nNumberOfBytesToRead != 0; nNumberOfBytesToRead = nNumberOfBytesToRead - 1) {
        *(byte *)pwVar5 = (byte)*pwVar5 ^ 0x77;
        pwVar5 = (wchar_t *)((int)pwVar5 + 1);
      }
      local_38 = lpBuffer.str;
      iVar6 = Fad_ReadInt((char **)&local_38);
      iVar1 = (int)cVar8;
      this->pageLen[iVar1] = (byte)iVar6;
      if ('\0' < (char)(byte)iVar6) {
        iVar6 = 0;
        do {
          pCVar3 = Fad_ReadString(&local_2c,(char **)&local_38);
          iVar7 = iVar1 * 0xb + iVar6;
          CString_Assign(this->text + iVar7,pCVar3);
          CString_Dtor(&local_2c);
          bVar2 = Fad_ReadBool((char **)&local_38);
          this->flags[iVar7] = bVar2;
          local_38 = (wchar_t *)Fad_SkipField((char *)local_38);
          iVar6 = (iVar6 + 1) * 0x1000000 >> 0x18;
        } while (iVar6 < (char)this->pageLen[iVar1]);
      }
    }
    free(lpBuffer.str);
    cVar8 = cVar8 + '\x01';
  } while (cVar8 < '\a');
  return;
}


// 000237a4 Str_FirstWord

CString * Str_FirstWord(CString *param_1,CString param_2)

{
  int iVar1;
  int iVar2;
  CString local_24;
  CString local_c [3];
  
  local_24.str = g_afxEmptyString;
  local_c[0].str = param_2.str;
  CString_AssignA(&local_24,&g_emptyA);
  iVar2 = 0;
  while( true ) {
    iVar1 = (int)(char)iVar2;
    if ((*(int *)(local_c[0].str + -4) <= iVar1) || (local_c[0].str[iVar1] == L' ')) break;
    iVar2 = (iVar1 + 1) * 0x1000000 >> 0x18;
    CString_AppendChar(&local_24,local_c[0].str[iVar1]);
  }
  CString_CopyCtor(param_1,&local_24);
  CString_Dtor(&local_24);
  CString_Dtor(local_c);
  return param_1;
}


// 0002384c Str_SecondWord

CString * Str_SecondWord(CString *param_1,CString param_2)

{
  int iVar1;
  int iVar2;
  CString local_24;
  CString local_c [3];
  
  iVar2 = 0;
  local_24.str = g_afxEmptyString;
  while ((iVar1 = (int)(char)iVar2, iVar1 < *(int *)(param_2.str + -4) &&
         (param_2.str[iVar1] != L' '))) {
    iVar2 = (iVar1 + 1) * 0x1000000 >> 0x18;
  }
  local_c[0].str = param_2.str;
  CString_AssignA(&local_24,&g_emptyA);
  iVar2 = iVar2 + 1;
  while ((iVar1 = (int)(char)iVar2, iVar1 < *(int *)(local_c[0].str + -4) &&
         (local_c[0].str[iVar1] != L' '))) {
    iVar2 = (iVar1 + 1) * 0x1000000 >> 0x18;
    CString_AppendChar(&local_24,local_c[0].str[iVar1]);
  }
  CString_CopyCtor(param_1,&local_24);
  CString_Dtor(&local_24);
  CString_Dtor(local_c);
  return param_1;
}


// 0002392c nop_2392c

void nop_2392c(void)

{
  return;
}


// 00023930 Button_Dtor

void Button_Dtor(Button *this)

{
  free(this->img);
  free(this->imgDown);
  return;
}


// 0002394c Button_Draw

void Button_Draw(Button *this)

{
  if (this->state == 1) {
    Screen_DrawDirect(this->screen,this->x,this->y,this->w,this->h,this->img);
  }
  else {
    Screen_DrawDirect(this->screen,this->x,this->y,this->w,this->h,this->imgDown);
  }
  return;
}


// 000239ac Button_Track

int Button_Track(Button *this,uint param_2,uint param_3)

{
  int iVar1;
  ushort local_10;
  ushort local_e;
  
  iVar1 = 0;
  if (((((uint)this->x <= param_2) && (param_2 <= (uint)(this->w + this->x))) &&
      ((uint)this->y <= param_3)) && ((param_3 <= (uint)(this->h + this->y) && (this->state == 1))))
  {
    this->state = 2;
    Button_Draw(this);
    WaitForPenUp((short *)&local_10,(short *)&local_e);
    if (((uint)this->x <= (uint)local_10) && ((uint)local_10 <= (uint)(this->w + this->x))) {
      if (((uint)this->y <= (uint)local_e) && ((uint)local_e <= (uint)(this->h + this->y))) {
        iVar1 = 1;
      }
    }
    this->state = 1;
    Button_Draw(this);
  }
  return iVar1;
}


// 00023a78 Button_Init

void Button_Init(Button *this,uint param_2,uint param_3,wchar_t *param_4,CString param_5,
                Screen *param_6,int param_7)

{
  CString local_38;
  CString local_34;
  CString CStack_4;
  
  CStack_4.str = param_4;
  CString_CopyCtor(&local_38,&param_5);
  LoadImage(local_38,&this->h,&this->w,&this->img,1);
  CString_CopyCtor(&local_34,&CStack_4);
  LoadImage(local_34,&this->h,&this->w,&this->imgDown,1);
  this->state = 1;
  this->screen = param_6;
  this->f20 = param_7;
  this->x = param_2 & 0xffff;
  this->y = param_3 & 0xffff;
  CString_Dtor(&CStack_4);
  CString_Dtor(&param_5);
  return;
}


// 00023b2c Button_SetState

void Button_SetState(Button *this,byte param_2)

{
  this->state = param_2;
  return;
}


// 00023b34 Button_GetF20

int Button_GetF20(Button *this)

{
  return this->f20;
}


// 00023b3c Game_Ctor

int Game_Ctor(Game *this)

{
  int iVar1;
  
  iVar1 = 6;
  do {
    nop_2392c();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  (this->descStr).str = g_afxEmptyString;
  (this->statusStr).str = g_afxEmptyString;
  (this->invStr).str = g_afxEmptyString;
  (this->str138).str = g_afxEmptyString;
  TextList_Ctor(&this->desc);
  TextList_Ctor(&this->status);
  TextList_Ctor(&this->inv);
  (this->str238).str = g_afxEmptyString;
  Scene_Ctor(&this->scene);
  PopupMenu_Ctor(&this->popup);
  return (int)this;
}


// 00023bcc Game_Dtor

void Game_Dtor(Game *this)

{
  Button *this_00;
  int iVar1;
  
  PopupMenu_Dtor(&this->popup);
  Scene_Dtor(&this->scene);
  CString_Dtor(&this->str238);
  TextList_Reset(&this->inv);
  TextList_Reset(&this->status);
  TextList_Reset(&this->desc);
  CString_Dtor(&this->str138);
  CString_Dtor(&this->invStr);
  CString_Dtor(&this->statusStr);
  CString_Dtor(&this->descStr);
  this_00 = (Button *)&this->screen;
  iVar1 = 6;
  do {
    this_00 = this_00 + -1;
    Button_Dtor(this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 00023c50 LoadUIImages

void LoadUIImages(Game *this,Screen *param_2,FontGlyphs *param_3,FontGlyphs *param_4,
                 FontGlyphs *param_5,FontGlyphs *param_6,FontGlyphs *param_7,GameState *param_8)

{
  CString *this_00;
  CString CStack_38;
  CString local_34;
  CString local_30;
  CString local_2c;
  CString local_28;
  
  CString_CtorA(&CStack_38,s_ui_Zoom_Mask_bmp_00043e58);
  CString_Plus(&local_34,&g_installDir,&CStack_38);
  LoadImage(local_34,&(this->zoom).h,&(this->zoom).w,&(this->zoom).pixels,1);
  CString_Dtor(&CStack_38);
  this->descFont = param_3;
  this->state = param_8;
  this->font = param_6;
  this->titleFont = param_4;
  this->font2 = param_7;
  this->screen = param_2;
  this->hiFont = param_5;
  (this->frame).x = 0;
  (this->frame).y = 0;
  (this->bg).x = 0;
  (this->bg).y = 0;
  (this->overlay).x = 0;
  (this->overlay).y = 0;
  CString_CtorA(&CStack_38,s_ui_UIText_bmp_00043e48);
  CString_Plus(&local_34,&g_installDir,&CStack_38);
  TextList_Init(&this->desc,this->descFont,0x15,0xe8,0xd6,299,local_34,param_2);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_UIAction_bmp_00043e38);
  CString_Plus(&local_34,&g_installDir,&CStack_38);
  TextList_Init(&this->status,this->font,0x32,0xb7,0xc1,0xc2,local_34,param_2);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_UIinv_bmp_00043e28);
  CString_Plus(&local_34,&g_installDir,&CStack_38);
  TextList_Init(&this->inv,this->font,0x92,0xd,0xeb,0xad,local_34,param_2);
  CString_Dtor(&CStack_38);
  this_00 = &this->descStr;
  CString_AssignA(this_00,&g_emptyA);
  CString_AssignA(&this->statusStr,&g_emptyA);
  CString_AssignA(&this->invStr,&g_emptyA);
  CString_AssignA(&this->str138,&g_emptyA);
  CString_CopyCtor(&local_30,this_00);
  TextList_SetText(&this->desc,local_30);
  CString_CopyCtor(&local_2c,this_00);
  TextList_SetText(&this->status,local_2c);
  CString_CopyCtor(&local_28,this_00);
  TextList_SetText(&this->inv,local_28);
  this->f22c = 0;
  this->f22d = 0;
  CString_CtorA(&CStack_38,s_ui_book_bmp_00043e1c);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  LoadImage(local_28,&(this->overlay).h,&(this->overlay).w,&(this->overlay).pixels,1);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_inventaire_jpg_00043e08);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  LoadImage(local_28,&(this->bg).h,&(this->bg).w,&(this->bg).pixels,1);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_ui_bmp_00043dfc);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  LoadImage(local_28,&(this->frame).h,&(this->frame).w,(ushort **)this,1);
  CString_Dtor(&CStack_38);
  CString_CtorA(&local_34,s_ui_UiOptionsOFF_bmp_00043de8);
  CString_Plus(&local_28,&g_installDir,&local_34);
  CString_CtorA(&CStack_38,s_ui_UiOptionsON_bmp_00043dd4);
  CString_Plus(&local_2c,&g_installDir,&CStack_38);
  Button_Init(this->buttons,0x17,0xc1,local_2c.str,local_28,param_2,1);
  CString_Dtor(&CStack_38);
  CString_Dtor(&local_34);
  CString_CtorA(&CStack_38,s_ui_UiBookOFF_bmp_00043dc0);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  CString_CtorA(&local_34,s_ui_UiBookON_bmp_00043db0);
  CString_Plus(&local_2c,&g_installDir,&local_34);
  Button_Init(this->buttons + 1,0x4e,0xc1,local_2c.str,local_28,param_2,3);
  CString_Dtor(&local_34);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_UiInvOFF_bmp_00043da0);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  CString_CtorA(&local_34,s_ui_UiInvON_bmp_00043d90);
  CString_Plus(&local_2c,&g_installDir,&local_34);
  Button_Init(this->buttons + 2,0x7c,0xc1,local_2c.str,local_28,param_2,2);
  CString_Dtor(&local_34);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_UiAllerOFF_bmp_00043d7c);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  CString_CtorA(&local_34,s_ui_UiAllerON_bmp_00043d68);
  CString_Plus(&local_2c,&g_installDir,&local_34);
  Button_Init(this->buttons + 3,0xbb,0xc1,local_2c.str,local_28,param_2,4);
  CString_Dtor(&local_34);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_FlecheUpOFF_jpg_00043d54);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  CString_CtorA(&local_34,s_ui_FlecheUpON_jpg_00043d40);
  CString_Plus(&local_2c,&g_installDir,&local_34);
  Button_Init(this->buttons + 4,0xdb,0xe5,local_2c.str,local_28,param_2,5);
  CString_Dtor(&local_34);
  CString_Dtor(&CStack_38);
  CString_CtorA(&CStack_38,s_ui_FlecheDownOFF_jpg_00043d28);
  CString_Plus(&local_28,&g_installDir,&CStack_38);
  CString_CtorA(&local_34,s_ui_FlecheDownON_jpg_00043d14);
  CString_Plus(&local_2c,&g_installDir,&local_34);
  Button_Init(this->buttons + 5,0xdb,0x10d,local_2c.str,local_28,param_2,6);
  CString_Dtor(&local_34);
  CString_Dtor(&CStack_38);
  CString_CtorA(&local_34,s_ui_PopUpAller_jpg_00043bc4);
  CString_Plus(&local_28,&g_installDir,&local_34);
  PopupMenu_Init(&this->popup,this->screen,this->font2,this->font,local_28,0,0x19,0xe2,10,0xb4);
  CString_Dtor(&local_34);
  return;
}


// 00024434 Game_DrawBackground

void Game_DrawBackground(Game *this)

{
  Screen_BlitToLayer(this->screen,(this->frame).x,(this->frame).y,(this->frame).w,(this->frame).h,
                     (this->frame).pixels,'\x01');
  return;
}


// 00024470 Game_DrawInventoryBar

void Game_DrawInventoryBar(Game *this)

{
  char cVar1;
  uint uVar2;
  GameObj *pGVar3;
  CString *pCVar4;
  GameState **ppGVar5;
  CString *this_00;
  uint uVar6;
  CString CStack_28;
  CString local_24;
  
  this_00 = &this->invStr;
  CString_AssignA(this_00,&g_emptyA);
  ppGVar5 = &this->state;
  uVar2 = Inventory_Count(&(*ppGVar5)->inventory);
  if ((uVar2 & 0xff) != 0) {
    uVar6 = 0;
    do {
      pGVar3 = Inventory_GetObj(&(*ppGVar5)->inventory,uVar6);
      cVar1 = GameObj_IsSelected(pGVar3);
      if (cVar1 != '\0') {
        pGVar3 = Inventory_GetObj(&(*ppGVar5)->inventory,uVar6);
        pCVar4 = GameObj_GetName(pGVar3,&local_24);
        CString_Append(this_00,pCVar4);
        CString_Dtor(&local_24);
        CString_CtorA(&CStack_28,s__00043bc0);
        CString_Append(this_00,&CStack_28);
        CString_Dtor(&CStack_28);
      }
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < (uVar2 & 0xff));
  }
  Screen_BlitToLayer(this->screen,(this->bg).x,(this->bg).y,(this->bg).w,(this->bg).h,
                     (this->bg).pixels,'\x03');
  CString_CopyCtor(&local_24,this_00);
  Game_SetInventoryText(this,local_24);
  Game_DrawText1cc(this);
  Game_DrawSelectedItem(this);
  Screen_PresentRows(this->screen,0xf0);
  return;
}


// 000245ac Game_DrawSelectedItem

void Game_DrawSelectedItem(Game *this)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  GameObj *pGVar4;
  ImgRect *pIVar5;
  int iVar6;
  ImgRect *pIVar7;
  GameState **ppGVar8;
  ImgRect local_24;
  
  ppGVar8 = &this->state;
  iVar3 = Inventory_Count(&(*ppGVar8)->inventory);
  if ((int)(uint)this->invSel < (int)(char)iVar3) {
    pGVar4 = Inventory_GetObj(&(*ppGVar8)->inventory,(uint)this->invSel);
    cVar2 = GameObj_IsSelected(pGVar4);
    if (cVar2 != '\0') {
      pGVar4 = Inventory_GetObj(&(*ppGVar8)->inventory,(uint)this->invSel);
      pIVar5 = GameObj_GetIcon(pGVar4,&local_24);
      iVar3 = 0x14;
      pIVar7 = &local_24;
      do {
        iVar6 = iVar3 + -1;
        *(undefined1 *)&pIVar7->pixels = *(undefined1 *)&pIVar5->pixels;
        bVar1 = 0 < iVar3;
        pIVar5 = (ImgRect *)((int)&pIVar5->pixels + 1);
        iVar3 = iVar6;
        pIVar7 = (ImgRect *)((int)&pIVar7->pixels + 1);
      } while (iVar6 != 0 && bVar1);
      Screen_BlitToLayer(this->screen,0x15,0xf,local_24.w,local_24.h,local_24.pixels,'\x03');
    }
  }
  return;
}


// 00024664 Game_DrawOverlay

void Game_DrawOverlay(Game *this)

{
  Screen_BlitKeyedToLayer
            (this->screen,(this->overlay).x,(this->overlay).y,(this->overlay).w,(this->overlay).h,
             (short *)(this->overlay).pixels,'\x02');
  Screen_Present(this->screen);
  return;
}


// 000246ac Game_DrawScene

void Game_DrawScene(Game *this)

{
  byte bVar1;
  char cVar2;
  ImgRect *pIVar3;
  ImgRect *pIVar4;
  ImgRect *pIVar5;
  ImgRect *pIVar6;
  ImgRect *pIVar7;
  RecF8 *pRVar8;
  Rec9 *this_00;
  Scene *this_01;
  uint uVar9;
  ImgRect IStack_98;
  ImgRect IStack_80;
  ImgRect IStack_68;
  ImgRect IStack_50;
  ImgRect IStack_38;
  
  this_01 = &this->scene;
  pIVar3 = Scene_GetBgImg(this_01,&IStack_98);
  pIVar4 = Scene_GetBgImg(this_01,&IStack_80);
  pIVar5 = Scene_GetBgImg(this_01,&IStack_68);
  pIVar6 = Scene_GetBgImg(this_01,&IStack_50);
  pIVar7 = Scene_GetBgImg(this_01,&IStack_38);
  Screen_BlitToLayer(this->screen,pIVar7->x,pIVar6->y,pIVar5->w,pIVar4->h,pIVar3->pixels,'\x03');
  bVar1 = Scene_GetNumObjs(this_01);
  if (bVar1 != 0) {
    uVar9 = 0;
    do {
      pRVar8 = Scene_GetObj(this_01,uVar9);
      cVar2 = RecF8_GetNoSprite(pRVar8);
      if (cVar2 == '\0') {
        this_00 = Rec9ec_GetObjState(this->state->scenes + this->dlgTopic,uVar9);
        cVar2 = Rec9_IsVisible(this_00);
        if (cVar2 != '\0') {
          pRVar8 = Scene_GetObj(this_01,uVar9);
          Game_DrawSprite(this,0,0,'\x03',(int)pRVar8);
        }
      }
      uVar9 = uVar9 + 1 & 0xff;
    } while (uVar9 < bVar1);
  }
  return;
}


// 000247e4 Game_DrawSceneToLayer

void Game_DrawSceneToLayer(Game *this,char param_2)

{
  byte bVar1;
  char cVar2;
  ImgRect *pIVar3;
  ImgRect *pIVar4;
  ImgRect *pIVar5;
  ImgRect *pIVar6;
  ImgRect *pIVar7;
  RecF8 *pRVar8;
  Rec9 *this_00;
  Scene *this_01;
  uint uVar9;
  ImgRect IStack_98;
  ImgRect IStack_80;
  ImgRect IStack_68;
  ImgRect IStack_50;
  ImgRect IStack_38;
  
  this_01 = &this->scene;
  pIVar3 = Scene_GetBgImg(this_01,&IStack_98);
  pIVar4 = Scene_GetBgImg(this_01,&IStack_80);
  pIVar5 = Scene_GetBgImg(this_01,&IStack_68);
  pIVar6 = Scene_GetBgImg(this_01,&IStack_50);
  pIVar7 = Scene_GetBgImg(this_01,&IStack_38);
  Screen_BlitToLayer(this->screen,pIVar7->x,pIVar6->y,pIVar5->w,pIVar4->h,pIVar3->pixels,param_2);
  bVar1 = Scene_GetNumObjs(this_01);
  if (bVar1 != 0) {
    uVar9 = 0;
    do {
      pRVar8 = Scene_GetObj(this_01,uVar9);
      cVar2 = RecF8_GetNoSprite(pRVar8);
      if (cVar2 == '\0') {
        this_00 = Rec9ec_GetObjState(this->state->scenes + this->dlgTopic,uVar9);
        cVar2 = Rec9_IsVisible(this_00);
        if (cVar2 != '\0') {
          pRVar8 = Scene_GetObj(this_01,uVar9);
          Game_DrawSprite(this,0,0,param_2,(int)pRVar8);
        }
      }
      uVar9 = uVar9 + 1 & 0xff;
    } while (uVar9 < bVar1);
  }
  return;
}


// 0002491c Game_DrawZoom

void Game_DrawZoom(Game *this,undefined1 *param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  ImgRect *pIVar4;
  ImgRect *pIVar5;
  ImgRect *pIVar6;
  RecF8 *pRVar7;
  RecE1 *this_00;
  Rec9 *this_01;
  uint uVar8;
  ImgRect IStack_64;
  ImgRect IStack_4c;
  ImgRect IStack_34;
  
  pIVar4 = Zoom_GetImg((Zoom *)param_2,&IStack_64);
  pIVar5 = Zoom_GetImg((Zoom *)param_2,&IStack_4c);
  pIVar6 = Zoom_GetImg((Zoom *)param_2,&IStack_34);
  Screen_BlitMaskedToLayer
            (this->screen,0x29,0x1e,pIVar6->w,pIVar5->h,(short *)pIVar4->pixels,
             (short *)(this->zoom).pixels,'\x02');
  bVar1 = Zoom_GetCount((Zoom *)param_2);
  if (bVar1 != 0) {
    uVar8 = 0;
    do {
      pRVar7 = Zoom_GetRec((Zoom *)param_2,uVar8);
      cVar2 = RecF8_GetNoSprite(pRVar7);
      if (cVar2 == '\0') {
        bVar3 = Zoom_GetSlot((Zoom *)param_2);
        this_00 = Rec9ec_GetRecE1(this->state->scenes + this->dlgTopic,(uint)bVar3);
        this_01 = RecE1_GetObjState(this_00,uVar8);
        cVar2 = Rec9_IsVisible(this_01);
        if (cVar2 != '\0') {
          pRVar7 = Zoom_GetRec((Zoom *)param_2,uVar8);
          Game_DrawSprite(this,0x29,0x1e,'\x02',(int)pRVar7);
        }
      }
      uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < bVar1);
  }
  Screen_Present(this->screen);
  return;
}


// 00024a54 Game_DrawSprite

void Game_DrawSprite(Game *this,int param_2,int param_3,char param_4,int param_5)

{
  bool bVar1;
  Point *pPVar2;
  ImgRect *pIVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  ImgRect *pIVar8;
  Point PStack_34;
  ImgRect local_2c;
  
  pPVar2 = RecF8_GetPos((RecF8 *)param_5,&PStack_34);
  iVar6 = pPVar2->x;
  pPVar2 = RecF8_GetPos((RecF8 *)param_5,&PStack_34);
  iVar7 = pPVar2->y;
  pIVar3 = RecF8_GetImg((RecF8 *)param_5,&local_2c);
  iVar4 = 0x14;
  pIVar8 = &local_2c;
  do {
    iVar5 = iVar4 + -1;
    *(undefined1 *)&pIVar8->pixels = *(undefined1 *)&pIVar3->pixels;
    bVar1 = 0 < iVar4;
    pIVar3 = (ImgRect *)((int)&pIVar3->pixels + 1);
    iVar4 = iVar5;
    pIVar8 = (ImgRect *)((int)&pIVar8->pixels + 1);
  } while (iVar5 != 0 && bVar1);
  Screen_BlitKeyedToLayer
            (this->screen,iVar6 + param_2,iVar7 + param_3,local_2c.w,local_2c.h,
             (short *)local_2c.pixels,param_4);
  return;
}


// 00024aec Game_ClearOverlay

void Game_ClearOverlay(Game *this)

{
  Screen_FillLayer(this->screen,g_colorKey,'\x02');
  Screen_Present(this->screen);
  return;
}


// 00024b18 Game_Redraw

void Game_Redraw(Game *this)

{
  Game_DrawBackground(this);
  Game_DrawScene(this);
  Game_DrawText13c(this);
  Game_DrawText184(this);
  Screen_Present(this->screen);
  return;
}


// 00024b48 Game_ShowTextTyped

void Game_ShowTextTyped(Game *this,byte param_2,char param_3)

{
  bool bVar1;
  int iVar2;
  uint extraout_r3;
  uint uVar3;
  TextList *this_00;
  
  this_00 = &this->desc;
  TextList_DrawTyped(this_00,'\x01',param_2);
  Screen_PresentRect(this->screen,0x15,0xe8,0xc1,0x43,'\x01');
  bVar1 = TextList_AtEnd(this_00);
  if ((!bVar1) && (param_3 != '\0')) {
    Game_BlinkButton5(this,2,100);
  }
  bVar1 = TextList_AtEnd(this_00);
  if ((bVar1) && (param_3 != '\0')) {
    iVar2 = Scene_GetKind(&this->scene);
    uVar3 = extraout_r3;
    if (iVar2 == 1) {
      uVar3 = (uint)this->dlgState;
    }
    if (iVar2 == 1 && uVar3 == 0) {
      Game_BlinkButton5(this,2,100);
    }
  }
  return;
}


// 00024c00 Game_ShowText

void Game_ShowText(Game *this,char param_2)

{
  bool bVar1;
  int iVar2;
  uint extraout_r3;
  uint uVar3;
  TextList *this_00;
  
  this_00 = &this->desc;
  TextList_Draw(this_00,'\x01');
  Screen_PresentRect(this->screen,0x15,0xe8,0xc1,0x43,'\x01');
  bVar1 = TextList_AtEnd(this_00);
  if ((!bVar1) && (param_2 != '\0')) {
    Game_BlinkButton5(this,2,100);
  }
  bVar1 = TextList_AtEnd(this_00);
  if ((bVar1) && (param_2 != '\0')) {
    iVar2 = Scene_GetKind(&this->scene);
    uVar3 = extraout_r3;
    if (iVar2 == 1) {
      uVar3 = (uint)this->dlgState;
    }
    if (iVar2 == 1 && uVar3 == 0) {
      Game_BlinkButton5(this,2,100);
    }
  }
  return;
}


// 00024cb4 Game_DrawStatusLine

void Game_DrawStatusLine(Game *this)

{
  TextList_Draw(&this->status,'\x01');
  Screen_PresentRect(this->screen,0x32,0xb7,0x8f,0xb,'\x01');
  return;
}


// 00024cf8 Game_DrawText13c

void Game_DrawText13c(Game *this)

{
  TextList_Draw(&this->desc,'\x01');
  return;
}


// 00024d04 Game_DrawText184

void Game_DrawText184(Game *this)

{
  TextList_Draw(&this->status,'\x01');
  return;
}


// 00024d10 Game_DrawText1cc

void Game_DrawText1cc(Game *this)

{
  TextList_Draw(&this->inv,'\x03');
  return;
}


// 00024d1c Game_PlayPanelAnim

void Game_PlayPanelAnim(Game *this)

{
  byte *pbVar1;
  GameState *pGVar2;
  uint uVar3;
  
  uVar3 = 0;
  do {
    pbVar1 = this->state->scenes[0].flags + uVar3 * 0x14 + -1;
    Screen_BlitToLayer(this->screen,*(int *)(pbVar1 + 0x25c8ac),
                       *(int *)(&DAT_0025c8b0 + (int)pbVar1),*(int *)(pbVar1 + 0x25c8b4),
                       *(int *)(pbVar1 + 0x25c8b8),*(ushort **)(pbVar1 + 0x25c8a8),'\x03');
    Screen_PresentRows(this->screen,0xb4);
    Sleep(0x5a);
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 < 8);
  uVar3 = 8;
  do {
    pGVar2 = this->state;
    Screen_BlitToLayer(this->screen,(int)(pGVar2->book).text[uVar3 * 5 + 0x4b].str,
                       (int)(pGVar2->book).text[uVar3 * 5 + 0x4c].str,
                       *(int *)((pGVar2->book).pageLen + uVar3 * 0x14),
                       pGVar2->panelAnim[uVar3 - 1].h,
                       (ushort *)(pGVar2->book).text[uVar3 * 5 + 0x4a].str,'\x03');
    Screen_PresentRows(this->screen,0xb4);
    Sleep(0x28);
    uVar3 = uVar3 + 0xff & 0xff;
  } while (uVar3 != 0);
  return;
}


// 00024e54 Game_HitTest

int Game_HitTest(Game *this,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  Game *pGVar3;
  
  TextList_Draw(&this->desc,'\x01');
  Screen_PresentRect(this->screen,0x15,0xe8,0xc1,0x43,'\x01');
  iVar2 = 0;
  pGVar3 = this;
  do {
    uVar1 = Button_Track(pGVar3->buttons,param_2 & 0xffff,param_3 & 0xffff);
    if ((uVar1 & 0xff) != 0) {
      iVar2 = Button_GetF20(this->buttons + iVar2);
      return iVar2;
    }
    iVar2 = iVar2 + 1;
    pGVar3 = (Game *)&(pGVar3->bg).h;
  } while (iVar2 < 6);
  Game_OnSceneTap(this,param_2,param_3);
  return 0;
}


// 00024f0c Game_BuildBookMenu

void Game_BuildBookMenu(Game *this,char param_2,int param_3)

{
  char cVar1;
  int iVar2;
  CString *pCVar3;
  int iVar4;
  GameState **ppGVar5;
  int iVar6;
  CString CStack_28;
  
  iVar4 = 0;
  do {
    CString_AssignA((CString *)(param_3 + iVar4 * 4),&g_emptyA);
    iVar4 = (iVar4 + 1) * 0x1000000 >> 0x18;
  } while (iVar4 < 0xf);
  ppGVar5 = &this->state;
  iVar4 = 0;
  iVar2 = Book_GetPageLen(&(*ppGVar5)->book,param_2);
  if (0 < (char)iVar2) {
    iVar6 = 0;
    do {
      cVar1 = Book_GetFlag(&(*ppGVar5)->book,param_2,(char)iVar6);
      if (cVar1 != '\0') {
        pCVar3 = Book_GetText(&(*ppGVar5)->book,&CStack_28,param_2,(char)iVar6);
        CString_Assign((CString *)(param_3 + (char)iVar4 * 4),pCVar3);
        CString_Dtor(&CStack_28);
        iVar4 = ((char)iVar4 + 1) * 0x1000000 >> 0x18;
      }
      iVar6 = (iVar6 + 1) * 0x1000000 >> 0x18;
    } while (iVar6 < (char)iVar2);
  }
  return;
}


// 00025000 Game_BookMenu

uint Game_BookMenu(Game *this,int param_2,int param_3)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  CString *this_00;
  GameState **ppGVar7;
  uint uVar8;
  uint uVar9;
  undefined4 local_5c [15];
  
  this_00 = (CString *)&stack0xffffffe0;
  puVar2 = local_5c;
  iVar6 = 0xf;
  do {
    iVar6 = iVar6 + -1;
    *puVar2 = g_afxEmptyString;
    puVar2 = puVar2 + 1;
  } while (iVar6 != 0);
  ppGVar7 = &this->state;
  iVar6 = Book_GetCurPage(&(*ppGVar7)->book);
  cVar5 = (char)iVar6;
  Game_BuildBookMenu(this,cVar5,(int)local_5c);
  uVar3 = PopupMenu_Run(&this->popup,param_2,param_3,(int)local_5c);
  iVar6 = 0;
  iVar4 = Book_GetPageLen(&(*ppGVar7)->book,cVar5);
  uVar8 = 0;
  uVar9 = uVar3;
  if (0 < (char)iVar4) {
    do {
      cVar1 = Book_GetFlag(&(*ppGVar7)->book,cVar5,(char)uVar8);
      if (cVar1 != '\0') {
        uVar9 = uVar8;
        if ((int)(char)iVar6 == (int)(char)uVar3) break;
        iVar6 = ((char)iVar6 + 1) * 0x1000000 >> 0x18;
      }
      uVar8 = uVar8 + 1;
      uVar9 = uVar3;
    } while ((int)(uVar8 * 0x1000000) >> 0x18 < (int)(char)iVar4);
  }
  iVar6 = 0xf;
  do {
    this_00 = this_00 + -1;
    CString_Dtor(this_00);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return uVar9;
}


// 0002513c OpenBook

void OpenBook(undefined4 *param_1)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  CString *pCVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  int *piVar10;
  undefined1 uVar11;
  Scene *this;
  ushort local_5c;
  ushort local_5a;
  CString local_58;
  CString local_54;
  CString CStack_50;
  CString local_4c;
  CString local_48;
  CString local_44;
  CString local_40;
  CString CStack_3c;
  CString local_38;
  CString local_34;
  CString local_30;
  CString CStack_2c;
  CString local_28;
  CString local_24;
  
  this = (Scene *)(param_1 + 0x8f);
  local_58.str = g_afxEmptyString;
  local_54.str = local_58.str;
  iVar4 = Scene_GetKind(this);
  if (iVar4 == 2) {
    piVar10 = param_1 + 0x6a50;
    uVar5 = Book_GetCurPage((Book *)(*piVar10 + 0x25c71c));
    CString_Assign(&local_54,(CString *)(param_1 + 0x4b));
    CString_Assign(&local_58,(CString *)(param_1 + 0x4c));
    if ((char)uVar5 == '\0') {
      Book_GetText((Book *)(*piVar10 + 0x25c71cU),&local_4c,'\x01','\0');
    }
    else {
      Book_GetText((Book *)(*piVar10 + 0x25c71cU),&local_4c,'\0',(char)uVar5 + -1);
    }
    Game_SetStatusText((Game *)param_1,local_4c);
    Game_DrawStatusLine((Game *)param_1);
    CString_CtorA(&local_4c,s_space);
    Game_SetDescText((Game *)param_1,local_4c);
    Game_ShowText((Game *)param_1,'\x01');
    Scene_SetKind(this,0);
    bVar2 = false;
    Game_DrawOverlay((Game *)param_1);
    do {
      WaitForPenDown((short *)&local_5c,(short *)&local_5a);
      iVar4 = Game_HitTest((Game *)param_1,(uint)local_5c,(uint)local_5a);
      if (iVar4 == 0) {
        uVar7 = (uint)local_5c;
        if ((((uVar7 < 0x1a) || (0xcf < uVar7)) || (uVar8 = (uint)local_5a, uVar8 < 0x24)) ||
           (0x8e < uVar8)) goto LAB_000254b4;
        uVar7 = Game_BookMenu((Game *)param_1,uVar7,uVar8);
        cVar9 = (char)uVar7;
        if (cVar9 == -1) goto LAB_000254b8;
        cVar1 = (char)uVar5;
        if (cVar1 == '\0') {
          Book_GetText((Book *)(*piVar10 + 0x25c71c),&local_48,'\0',cVar9);
          Game_SetStatusText((Game *)param_1,local_48);
          Game_DrawStatusLine((Game *)param_1);
          CString_CtorA(&local_44,s_space);
          Game_SetDescText((Game *)param_1,local_44);
          Game_ShowText((Game *)param_1,'\x01');
          CString_CtorA(&CStack_50,s_sounds_feuilletter_wav_00043e6c);
          CString_Plus(&local_40,&g_installDir,&CStack_50);
          pCVar6 = MangleAssetPath(&CStack_3c,local_40);
          sndPlaySoundW(pCVar6->str,3);
          CString_Dtor(&CStack_3c);
          CString_Dtor(&CStack_50);
          uVar7 = uVar7 + 1;
          uVar11 = (undefined1)uVar7;
        }
        else {
          if (cVar9 != '\0') {
            LoadBookPage((Book *)(*piVar10 + 0x25c71cU),&local_28,cVar1,cVar9);
            Game_SetDescText((Game *)param_1,local_28);
            Book_GetText((Book *)(*piVar10 + 0x25c71c),&local_24,cVar1,cVar9);
            Game_SetStatusText((Game *)param_1,local_24);
            Game_DrawStatusLine((Game *)param_1);
            goto LAB_00025290;
          }
          Book_GetText((Book *)(*piVar10 + 0x25c71cU),&local_38,cVar1,'\0');
          Game_SetStatusText((Game *)param_1,local_38);
          Game_DrawStatusLine((Game *)param_1);
          CString_CtorA(&local_34,s_space);
          Game_SetDescText((Game *)param_1,local_34);
          Game_ShowText((Game *)param_1,'\x01');
          CString_CtorA(&local_4c,s_sounds_feuilletter_wav_00043e6c);
          CString_Plus(&local_30,&g_installDir,&local_4c);
          pCVar6 = MangleAssetPath(&CStack_2c,local_30);
          sndPlaySoundW(pCVar6->str,3);
          CString_Dtor(&CStack_2c);
          CString_Dtor(&local_4c);
          uVar11 = 0;
        }
        Book_SetCurPage((Book *)(*piVar10 + 0x25c71c),uVar11);
        uVar5 = uVar7;
      }
      else if (iVar4 == 3) {
LAB_000254b4:
        bVar2 = true;
      }
      else if (iVar4 == 5) {
        bVar3 = TextList_PageUp((TextList *)(param_1 + 0x4f));
        if (bVar3) {
          cVar9 = *(char *)(param_1 + 0x8b) + -1;
          goto LAB_0002528c;
        }
      }
      else if ((iVar4 == 6) && (bVar3 = TextList_PageDown((TextList *)(param_1 + 0x4f)), bVar3)) {
        cVar9 = *(char *)(param_1 + 0x8b) + '\x01';
LAB_0002528c:
        *(char *)(param_1 + 0x8b) = cVar9;
LAB_00025290:
        Game_ShowText((Game *)param_1,'\x01');
      }
LAB_000254b8:
    } while (!bVar2);
    CString_CopyCtor(&local_24,&local_54);
    Game_SetDescText((Game *)param_1,local_24);
    CString_CopyCtor(&local_28,&local_58);
    Game_SetStatusText((Game *)param_1,local_28);
    Scene_SetKind(this,2);
    Game_ClearOverlay((Game *)param_1);
    Game_Redraw((Game *)param_1);
    Book_SetCurPage((Book *)(*piVar10 + 0x25c71c),0);
  }
  CString_Dtor(&local_58);
  CString_Dtor(&local_54);
  return;
}


// 00025534 Game_OpenInventory

void Game_OpenInventory(Game *this)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  GameObj *pGVar4;
  GameState **ppGVar5;
  byte local_18;
  char local_17;
  undefined1 auStack_16 [2];
  ushort local_14;
  ushort local_12;
  
  iVar2 = Scene_GetKind(&this->scene);
  if (iVar2 != 1) {
    ppGVar5 = &this->state;
    uVar3 = Inventory_FindSelected(&(*ppGVar5)->inventory);
    this->invSel = (byte)uVar3;
    Game_DrawInventoryBar(this);
    local_18 = 0;
    do {
      Game_InventoryInput(this,auStack_16,&local_18,&local_17,&local_12,&local_14);
      if (local_17 != '\0') {
        pGVar4 = Inventory_GetObj(&(*ppGVar5)->inventory,(uint)this->invSel);
        cVar1 = GameObj_IsSelected(pGVar4);
        if (cVar1 != '\0') {
          pGVar4 = Inventory_GetObj(&(*ppGVar5)->inventory,(uint)this->invSel);
          local_18 = Game_UseInventoryItem(this,(uint)local_12,(uint)local_14,(int)pGVar4);
        }
      }
    } while (local_18 == 0);
    Game_Redraw(this);
  }
  return;
}


// 00025614 Game_InventoryInput

void Game_InventoryInput(Game *this,undefined1 *param_2,undefined1 *param_3,undefined1 *param_4,
                        ushort *param_5,ushort *param_6)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  GameObj *this_00;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  *param_2 = 0xff;
  *param_3 = 0;
  *param_4 = 0;
  uVar2 = Inventory_Count(&this->state->inventory);
  WaitForPenDown((short *)param_5,(short *)param_6);
  uVar4 = (uint)*param_6;
  if (uVar4 < 0xb5) {
    uVar4 = TextList_HitTest(&this->inv,(uint)*param_5,uVar4);
    if ((uVar4 & 0xff) == 0) {
      if ((((0x15 < *param_5) && (*param_5 < 0x80)) && (0xf < *param_6)) && (*param_6 < 0xa8)) {
        *param_4 = 1;
      }
    }
    else {
      uVar4 = TextList_LineAt(&this->inv,(uint)*param_5,(uint)*param_6);
      uVar5 = uVar4 & 0xff;
      if (uVar5 < (uVar2 & 0xff)) {
        uVar6 = 0;
        do {
          this_00 = Inventory_GetObj(&this->state->inventory,uVar6);
          cVar1 = GameObj_IsSelected(this_00);
          if (cVar1 == '\0') {
            uVar4 = uVar5 + 1 & 0xff;
          }
          uVar6 = uVar6 + 1 & 0xff;
          uVar5 = uVar4 & 0xff;
        } while (uVar6 <= uVar5);
        if ((uVar4 & 0xff) < (uVar2 & 0xff)) {
          *param_2 = (byte)uVar4;
          this->invSel = (byte)uVar4;
          Game_DrawInventoryBar(this);
        }
      }
    }
  }
  else {
    iVar3 = Game_HitTest(this,(uint)*param_5,uVar4);
    if (iVar3 == 2) {
      *param_3 = 1;
    }
    else if (iVar3 == 5) {
      Game_OnKeyUp(this);
    }
    else if (iVar3 == 6) {
      Game_OnKeyDown(this);
    }
  }
  return;
}


// 0002579c Game_UseInventoryItem

byte Game_UseInventoryItem(Game *this,int param_2,int param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  CString *pCVar6;
  CString *pCVar7;
  CString *pCVar8;
  GameObj *pGVar9;
  CString *pCVar10;
  ScriptOpList *pSVar11;
  RecF8 *pRVar12;
  Rec9 *pRVar13;
  CString *pCVar14;
  Link *pLVar15;
  Zoom *pZVar16;
  RecE1 *this_00;
  int iVar17;
  GameState *pGVar18;
  CString *this_01;
  uint uVar19;
  GameState **ppGVar20;
  Scene *this_02;
  uint uVar21;
  uint uVar22;
  byte local_2e0;
  byte local_2df;
  byte local_2de;
  byte local_2dd;
  ushort local_2dc;
  ushort local_2da;
  byte local_2d8 [4];
  CString local_2d4;
  CString local_2d0;
  CString CStack_2cc;
  CString CStack_2c8;
  CString local_2c4;
  CString local_2c0;
  undefined1 auStack_2bc [4];
  CString CStack_2b8;
  CString CStack_2b4;
  CString CStack_2b0;
  CString CStack_2ac;
  CString CStack_2a8;
  CString CStack_2a4;
  CString CStack_2a0;
  CString CStack_29c;
  CString CStack_298;
  CString CStack_294;
  CString CStack_290;
  CString CStack_28c;
  CString CStack_288;
  CString CStack_284;
  CString CStack_280;
  CString CStack_27c;
  CString CStack_278;
  CString CStack_274;
  CString CStack_270;
  CString CStack_26c;
  CString local_268;
  CString local_264;
  CString local_260;
  CString CStack_25c;
  CString local_258;
  CString CStack_254;
  CString CStack_250;
  CString CStack_24c;
  CString CStack_248;
  CString CStack_244;
  CString CStack_240;
  CString CStack_23c;
  CString CStack_238;
  CString local_234;
  CString CStack_230;
  CString local_22c;
  CString CStack_228;
  CString CStack_224;
  CString CStack_220;
  CString CStack_21c;
  CString CStack_218;
  CString CStack_214;
  CString CStack_210;
  CString local_20c;
  CString local_208;
  CString local_204;
  CString local_200;
  CString CStack_1fc;
  CString local_1f8;
  CString CStack_1f4;
  CString local_1f0;
  CString CStack_1ec;
  CString local_1e8;
  CString CStack_1e4;
  CString local_1e0;
  CString local_1dc;
  CString CStack_1d8;
  CString CStack_1d4;
  CString CStack_1d0;
  CString CStack_1cc;
  CString local_1c8;
  CString local_1c4;
  CString local_1c0;
  CString CStack_1bc;
  CString CStack_1b8;
  CString CStack_1b4;
  CString CStack_1b0;
  CString CStack_1ac;
  CString CStack_1a8;
  CString CStack_1a4;
  Link LStack_1a0;
  Link LStack_19c;
  Link LStack_198;
  Link LStack_194;
  Link LStack_190;
  Link LStack_18c;
  CString aCStack_188 [2];
  CString aCStack_180 [4];
  CString aCStack_170 [2];
  CString aCStack_168 [4];
  CString aCStack_158 [2];
  CString aCStack_150 [4];
  CString aCStack_140 [2];
  CString aCStack_138 [4];
  CString aCStack_128 [2];
  CString aCStack_120 [4];
  CString aCStack_110 [2];
  CString aCStack_108 [4];
  CString aCStack_f8 [2];
  CString aCStack_f0 [4];
  CString aCStack_e0 [2];
  CString aCStack_d8 [4];
  CString aCStack_c8 [2];
  CString aCStack_c0 [4];
  CString aCStack_b0 [2];
  CString aCStack_a8 [4];
  CString aCStack_98 [2];
  CString aCStack_90 [4];
  CString aCStack_80 [2];
  CString aCStack_78 [4];
  CString local_68 [15];
  
  this_01 = (CString *)&stack0xffffffd4;
  pCVar6 = local_68;
  iVar17 = 0xf;
  do {
    iVar17 = iVar17 + -1;
    pCVar6->str = g_afxEmptyString;
    pCVar6 = pCVar6 + 1;
  } while (iVar17 != 0);
  local_1f8.str = g_afxEmptyString;
  local_2df = 0;
  uVar19 = 0;
  local_1f0.str = local_1f8.str;
  do {
    CString_AssignA(local_68 + uVar19,&g_emptyA);
    uVar19 = uVar19 + 1 & 0xff;
  } while (uVar19 < 0xf);
  uVar19 = 0;
  bVar1 = GameObj_GetNumSubs((GameObj *)param_4);
  if (bVar1 != 0) {
    uVar22 = 0;
    do {
      iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_80,uVar22);
      cVar4 = *(char *)(iVar17 + 4);
      CString_Dtor(aCStack_78);
      CString_Dtor(aCStack_80);
      if (cVar4 != '\0') {
        pCVar6 = (CString *)GameObj_GetSub14((GameObj *)param_4,(int)aCStack_e0,uVar22);
        CString_Assign(local_68 + uVar19,pCVar6);
        CString_Dtor(aCStack_d8);
        CString_Dtor(aCStack_e0);
        uVar19 = uVar19 + 1 & 0xff;
      }
      uVar22 = uVar22 + 1 & 0xff;
    } while (uVar22 < bVar1);
  }
  GameObj_GetName((GameObj *)param_4,&local_2d4);
  Game_SetStatusText(this,local_2d4);
  CString_CtorA(&local_2d0,&g_emptyA);
  Game_SetDescText(this,local_2d0);
  Game_ShowText(this,'\x01');
  Game_DrawStatusLine(this);
  uVar19 = PopupMenu_Run(&this->popup,param_2,param_3,(int)local_68);
  uVar21 = 0;
  local_2e0 = (byte)uVar19;
  bVar1 = GameObj_GetNumSubs((GameObj *)param_4);
  uVar22 = 0;
  if (bVar1 != 0) {
    do {
      iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_140,uVar22);
      cVar4 = *(char *)(iVar17 + 4);
      CString_Dtor(aCStack_138);
      CString_Dtor(aCStack_140);
      if (cVar4 != '\0') {
        if (uVar21 == (int)(char)local_2e0) {
          local_2e0 = (byte)uVar22;
          uVar19 = uVar22;
          break;
        }
        uVar21 = uVar21 + 1 & 0xff;
      }
      uVar22 = uVar22 + 1;
    } while ((uVar22 & 0xff) < (uint)bVar1);
  }
  if ((char)uVar19 == -1) {
    CString_CtorA(&local_2c4,&g_emptyA);
    Game_SetStatusText(this,local_2c4);
    CString_CtorA(&local_2c0,&g_emptyA);
    Game_SetDescText(this,local_2c0);
    Game_ShowText(this,'\x01');
LAB_00026850:
    Game_DrawStatusLine(this);
    goto LAB_00026858;
  }
  pCVar6 = GameObj_GetName((GameObj *)param_4,&CStack_2c8);
  CString_CtorA(&CStack_2cc,s_space);
  pCVar10 = local_68 + uVar21;
  pCVar7 = CString_Plus(&local_2d0,pCVar10,&CStack_2cc);
  CString_Plus(&local_2d4,pCVar7,pCVar6);
  Game_SetStatusText(this,local_2d4);
  CString_Dtor(&local_2d0);
  CString_Dtor(&CStack_2c8);
  CString_Dtor(&CStack_2cc);
  iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_188,uVar19);
  iVar17 = *(int *)(iVar17 + 0xc);
  CString_Dtor(aCStack_180);
  CString_Dtor(aCStack_188);
  if (iVar17 == 0) {
    iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_98,uVar19);
    CString_CopyCtor(&local_2c4,(CString *)(iVar17 + 8));
    Game_SetDescText(this,local_2c4);
    CString_Dtor(aCStack_90);
    CString_Dtor(aCStack_98);
    Game_DrawStatusLine(this);
    Game_ShowTextTyped(this,1,'\x01');
    goto LAB_00026858;
  }
  if (iVar17 == 2) {
    Game_DrawStatusLine(this);
    iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_c8,uVar19);
    pSVar11 = GameObj_GetScripts((GameObj *)param_4);
    Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x10));
    CString_Dtor(aCStack_c0);
    CString_Dtor(aCStack_c8);
    if (this->f230[3] != 0) {
      local_2df = 1;
    }
    pGVar18 = this->state;
LAB_000267a4:
    iVar17 = Inventory_Selected(&pGVar18->inventory);
    this->invSel = (byte)iVar17;
  }
  else {
    if (iVar17 == 3) {
      local_2df = 1;
      CString_CtorA(&CStack_2ac,s_____00043e84);
      CString_CopyCtor(&local_234,pCVar10);
      pCVar6 = Str_SecondWord(&CStack_28c,local_234);
      CString_CtorA(&CStack_294,s_space);
      pCVar7 = GameObj_GetName((GameObj *)param_4,&CStack_214);
      CString_CtorA(&CStack_290,s_space);
      CString_CopyCtor(&local_1e8,pCVar10);
      pCVar8 = Str_FirstWord(&CStack_1cc,local_1e8);
      pCVar8 = CString_Plus(&CStack_1d4,pCVar8,&CStack_290);
      pCVar7 = CString_Plus(&CStack_21c,pCVar8,pCVar7);
      pCVar7 = CString_Plus(&CStack_224,pCVar7,&CStack_294);
      pCVar6 = CString_Plus(&CStack_1e4,pCVar7,pCVar6);
      CString_Plus(&local_22c,pCVar6,&CStack_2ac);
      Game_SetStatusText(this,local_22c);
      CString_Dtor(&CStack_1e4);
      CString_Dtor(&CStack_224);
      CString_Dtor(&CStack_28c);
      CString_Dtor(&CStack_21c);
      CString_Dtor(&CStack_1d4);
      CString_Dtor(&CStack_214);
      CString_Dtor(&CStack_1cc);
      CString_Dtor(&CStack_290);
      CString_Dtor(&CStack_294);
      CString_Dtor(&CStack_2ac);
      Game_DrawStatusLine(this);
      Game_Redraw(this);
      uVar19 = 0xff;
      local_2dd = 0xff;
      local_2de = 10;
      do {
        bVar1 = local_2de;
        WaitForPenDown((short *)&local_2da,(short *)&local_2dc);
        this_02 = &this->scene;
        if (this->f230[0] == 0xff) {
          bVar2 = Scene_GetNumObjs(this_02);
          uVar22 = 0;
          if (bVar2 != 0) {
            do {
              pRVar12 = Scene_GetObj(this_02,uVar22);
              bVar3 = RecF8_HitTest(pRVar12,(uint)local_2da,(uint)local_2dc);
              if (bVar3) {
                pRVar13 = Rec9ec_GetObjState(this->state->scenes + this->dlgTopic,uVar22);
                cVar4 = Rec9_IsVisible(pRVar13);
                if (cVar4 != '\0') {
                  pRVar12 = Scene_GetObj(this_02,uVar22);
                  bVar5 = RecF8_Get6(pRVar12);
                  if (bVar5 < bVar1) {
                    pRVar12 = Scene_GetObj(this_02,uVar22);
                    bVar1 = RecF8_Get6(pRVar12);
                    local_2dd = (byte)uVar22;
                    uVar19 = uVar22;
                    local_2de = bVar1;
                  }
                }
              }
            } while ((bVar1 != 0) && (uVar22 = uVar22 + 1, (uVar22 & 0xff) < (uint)bVar2));
          }
          uVar22 = uVar19 & 0xff;
          if (uVar22 != 0xff) {
            pRVar12 = Scene_GetObj(this_02,uVar19);
            pCVar6 = RecF8_GetName(pRVar12,&CStack_1fc);
            CString_CtorA(&CStack_2b4,s_space);
            CString_CopyCtor(&local_20c,pCVar10);
            pCVar7 = Str_SecondWord(&CStack_1ac,local_20c);
            CString_CtorA(&CStack_2a4,s_space);
            pCVar8 = GameObj_GetName((GameObj *)param_4,&CStack_278);
            CString_CtorA(&CStack_29c,s_space);
            CString_CopyCtor(&local_1c4,pCVar10);
            pCVar14 = Str_FirstWord(&CStack_270,local_1c4);
            pCVar14 = CString_Plus(&CStack_280,pCVar14,&CStack_29c);
            pCVar8 = CString_Plus(&CStack_288,pCVar14,pCVar8);
            pCVar8 = CString_Plus(&CStack_1f4,pCVar8,&CStack_2a4);
            pCVar7 = CString_Plus(&CStack_1b4,pCVar8,pCVar7);
            pCVar7 = CString_Plus(&CStack_1bc,pCVar7,&CStack_2b4);
            CString_Plus(&local_204,pCVar7,pCVar6);
            Game_SetStatusText(this,local_204);
            CString_Dtor(&CStack_1bc);
            CString_Dtor(&CStack_1fc);
            CString_Dtor(&CStack_1b4);
            CString_Dtor(&CStack_1f4);
            CString_Dtor(&CStack_1ac);
            CString_Dtor(&CStack_288);
            CString_Dtor(&CStack_280);
            CString_Dtor(&CStack_278);
            CString_Dtor(&CStack_270);
            CString_Dtor(&CStack_29c);
            CString_Dtor(&CStack_2a4);
            CString_Dtor(&CStack_2b4);
            Game_DrawStatusLine(this);
            pLVar15 = GameObj_GetField8220((GameObj *)param_4,&LStack_1a0);
            if (((uVar22 == pLVar15->f3) &&
                (pLVar15 = GameObj_GetField8220((GameObj *)param_4,&LStack_198),
                this->dlgTopic == pLVar15->id)) &&
               (pLVar15 = GameObj_GetField8220((GameObj *)param_4,&LStack_190),
               this->f230[0] == pLVar15->script)) {
              iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_170,(uint)local_2e0);
              pSVar11 = GameObj_GetScripts((GameObj *)param_4);
              Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x10));
              CString_Dtor(aCStack_168);
              pCVar6 = aCStack_170;
              goto LAB_00026324;
            }
            iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_158,(uint)local_2e0);
            pSVar11 = GameObj_GetScripts((GameObj *)param_4);
            Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x11));
            CString_Dtor(aCStack_150);
            pCVar6 = aCStack_158;
LAB_000266f0:
            CString_Dtor(pCVar6);
          }
        }
        else {
          local_2da = local_2da - 0x29;
          local_2dc = local_2dc - 0x1e;
          pZVar16 = (Zoom *)Scene_GetZoom(this_02,(uint)this->f230[0]);
          bVar2 = Zoom_GetCount(pZVar16);
          uVar22 = 0;
          if (bVar2 != 0) {
            do {
              pZVar16 = (Zoom *)Scene_GetZoom(this_02,(uint)this->f230[0]);
              pRVar12 = Zoom_GetRec(pZVar16,uVar22);
              bVar3 = RecF8_HitTest(pRVar12,(uint)local_2da,(uint)local_2dc);
              if (bVar3) {
                this_00 = Rec9ec_GetRecE1(this->state->scenes + this->dlgTopic,(uint)this->f230[0]);
                pRVar13 = RecE1_GetObjState(this_00,uVar22);
                cVar4 = Rec9_IsVisible(pRVar13);
                if (cVar4 != '\0') {
                  pZVar16 = (Zoom *)Scene_GetZoom(this_02,(uint)this->f230[0]);
                  pRVar12 = Zoom_GetRec(pZVar16,uVar22);
                  bVar5 = RecF8_Get6(pRVar12);
                  if (bVar5 < bVar1) {
                    pZVar16 = (Zoom *)Scene_GetZoom(this_02,(uint)this->f230[0]);
                    pRVar12 = Zoom_GetRec(pZVar16,uVar22);
                    bVar1 = RecF8_Get6(pRVar12);
                    local_2dd = (byte)uVar22;
                    uVar19 = uVar22;
                    local_2de = bVar1;
                  }
                }
              }
            } while ((bVar1 != 0) && (uVar22 = uVar22 + 1, (uVar22 & 0xff) < (uint)bVar2));
          }
          uVar22 = uVar19 & 0xff;
          if (uVar22 != 0xff) {
            pZVar16 = (Zoom *)Scene_GetZoom(this_02,(uint)this->f230[0]);
            pRVar12 = Zoom_GetRec(pZVar16,uVar19);
            pCVar6 = RecF8_GetName(pRVar12,&CStack_248);
            CString_CtorA(&local_2d4,s_space);
            CString_CopyCtor(&local_268,pCVar10);
            pCVar7 = Str_SecondWord(&CStack_230,local_268);
            CString_CtorA(&local_2d0,s_space);
            pCVar8 = GameObj_GetName((GameObj *)param_4,&CStack_218);
            CString_CtorA(&CStack_2c8,s_space);
            CString_CopyCtor(&local_260,pCVar10);
            pCVar14 = Str_FirstWord(&CStack_210,local_260);
            pCVar14 = CString_Plus(&CStack_220,pCVar14,&CStack_2c8);
            pCVar8 = CString_Plus(&CStack_228,pCVar14,pCVar8);
            pCVar8 = CString_Plus(&CStack_238,pCVar8,&local_2d0);
            pCVar7 = CString_Plus(&CStack_240,pCVar8,pCVar7);
            pCVar7 = CString_Plus(&CStack_250,pCVar7,&local_2d4);
            CString_Plus(&local_258,pCVar7,pCVar6);
            Game_SetStatusText(this,local_258);
            CString_Dtor(&CStack_250);
            CString_Dtor(&CStack_248);
            CString_Dtor(&CStack_240);
            CString_Dtor(&CStack_238);
            CString_Dtor(&CStack_230);
            CString_Dtor(&CStack_228);
            CString_Dtor(&CStack_220);
            CString_Dtor(&CStack_218);
            CString_Dtor(&CStack_210);
            CString_Dtor(&CStack_2c8);
            CString_Dtor(&local_2d0);
            CString_Dtor(&local_2d4);
            Game_DrawStatusLine(this);
            pLVar15 = GameObj_GetField8220((GameObj *)param_4,&LStack_19c);
            if (((uVar22 != pLVar15->f3) ||
                (pLVar15 = GameObj_GetField8220((GameObj *)param_4,&LStack_194),
                this->dlgTopic != pLVar15->id)) ||
               (pLVar15 = GameObj_GetField8220((GameObj *)param_4,&LStack_18c),
               this->f230[0] != pLVar15->script)) {
              iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_f8,(uint)local_2e0);
              pSVar11 = GameObj_GetScripts((GameObj *)param_4);
              Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x11));
              CString_Dtor(aCStack_f0);
              pCVar6 = aCStack_f8;
              goto LAB_000266f0;
            }
            iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_128,(uint)local_2e0);
            pSVar11 = GameObj_GetScripts((GameObj *)param_4);
            Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x10));
            CString_Dtor(aCStack_120);
            pCVar6 = aCStack_128;
LAB_00026324:
            CString_Dtor(pCVar6);
            iVar17 = Inventory_Selected(&this->state->inventory);
            this->invSel = (byte)iVar17;
          }
        }
        if (0xb4 < local_2dc) {
          CString_CtorA(&local_2c0,&g_emptyA);
          Game_SetStatusText(this,local_2c0);
          goto LAB_00026850;
        }
        if (uVar22 != 0xff) goto LAB_00026858;
        uVar19 = (uint)local_2dd;
      } while( true );
    }
    if (iVar17 != 4) goto LAB_00026858;
    CString_CtorA(&CStack_2b0,s_____00043e84);
    CString_CopyCtor(&local_1dc,pCVar10);
    pCVar6 = Str_SecondWord(&CStack_27c,local_1dc);
    CString_CtorA(&CStack_2a0,s_space);
    pCVar7 = GameObj_GetName((GameObj *)param_4,&CStack_1a8);
    CString_CtorA(&CStack_2cc,s_space);
    CString_CopyCtor(&local_208,pCVar10);
    pCVar8 = Str_FirstWord(&CStack_26c,local_208);
    pCVar8 = CString_Plus(&CStack_274,pCVar8,&CStack_2cc);
    pCVar7 = CString_Plus(&CStack_1a4,pCVar8,pCVar7);
    pCVar7 = CString_Plus(&CStack_1ec,pCVar7,&CStack_2a0);
    pCVar6 = CString_Plus(&CStack_284,pCVar7,pCVar6);
    CString_Plus(&local_200,pCVar6,&CStack_2b0);
    Game_SetStatusText(this,local_200);
    CString_Dtor(&CStack_284);
    CString_Dtor(&CStack_1ec);
    CString_Dtor(&CStack_27c);
    CString_Dtor(&CStack_1a4);
    CString_Dtor(&CStack_274);
    CString_Dtor(&CStack_1a8);
    CString_Dtor(&CStack_26c);
    CString_Dtor(&CStack_2cc);
    CString_Dtor(&CStack_2a0);
    CString_Dtor(&CStack_2b0);
    Game_DrawStatusLine(this);
    Game_InventoryInput(this,local_2d8,&local_2df,auStack_2bc,&local_2da,&local_2dc);
    if (local_2d8[0] == 0xff) {
      CString_CtorA(&local_1c8,s_space);
      Game_SetStatusText(this,local_1c8);
      Game_DrawStatusLine(this);
    }
    else {
      ppGVar20 = &this->state;
      pGVar9 = Inventory_GetObj(&(*ppGVar20)->inventory,(uint)local_2d8[0]);
      pCVar6 = GameObj_GetName(pGVar9,&CStack_1d8);
      CString_CtorA(&CStack_298,s_space);
      CString_CopyCtor(&local_1e0,pCVar10);
      pCVar7 = Str_SecondWord(&CStack_24c,local_1e0);
      CString_CtorA(&CStack_2b8,s_space);
      pCVar8 = GameObj_GetName((GameObj *)param_4,&CStack_1b8);
      CString_CtorA(&CStack_2a8,s_space);
      CString_CopyCtor(&local_264,pCVar10);
      pCVar10 = Str_FirstWord(&CStack_23c,local_264);
      pCVar10 = CString_Plus(&CStack_244,pCVar10,&CStack_2a8);
      pCVar10 = CString_Plus(&CStack_1d0,pCVar10,pCVar8);
      pCVar10 = CString_Plus(&CStack_1b0,pCVar10,&CStack_2b8);
      pCVar7 = CString_Plus(&CStack_254,pCVar10,pCVar7);
      pCVar7 = CString_Plus(&CStack_25c,pCVar7,&CStack_298);
      CString_Plus(&local_1c0,pCVar7,pCVar6);
      Game_SetStatusText(this,local_1c0);
      CString_Dtor(&CStack_25c);
      CString_Dtor(&CStack_1d8);
      CString_Dtor(&CStack_254);
      CString_Dtor(&CStack_1b0);
      CString_Dtor(&CStack_24c);
      CString_Dtor(&CStack_1d0);
      CString_Dtor(&CStack_244);
      CString_Dtor(&CStack_1b8);
      CString_Dtor(&CStack_23c);
      CString_Dtor(&CStack_2a8);
      CString_Dtor(&CStack_2b8);
      CString_Dtor(&CStack_298);
      Game_DrawStatusLine(this);
      bVar1 = GameObj_GetF8224((GameObj *)param_4);
      pGVar9 = Inventory_GetObj(&(*ppGVar20)->inventory,(uint)local_2d8[0]);
      bVar2 = GameObj_GetId(pGVar9);
      if (bVar1 == bVar2) {
        iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_110,(uint)local_2e0);
        pSVar11 = GameObj_GetScripts((GameObj *)param_4);
        Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x10));
        CString_Dtor(aCStack_108);
        CString_Dtor(aCStack_110);
        pGVar18 = *ppGVar20;
        goto LAB_000267a4;
      }
      iVar17 = GameObj_GetSub14((GameObj *)param_4,(int)aCStack_b0,(uint)local_2e0);
      pSVar11 = GameObj_GetScripts((GameObj *)param_4);
      Script_RunList(this,(int)pSVar11,(uint)*(byte *)(iVar17 + 0x11));
      CString_Dtor(aCStack_a8);
      CString_Dtor(aCStack_b0);
    }
  }
  Game_DrawInventoryBar(this);
LAB_00026858:
  bVar1 = local_2df;
  CString_Dtor(&local_1f8);
  CString_Dtor(&local_1f0);
  iVar17 = 0xf;
  do {
    this_01 = this_01 + -1;
    CString_Dtor(this_01);
    iVar17 = iVar17 + -1;
  } while (iVar17 != 0);
  return bVar1;
}


// 0002689c Game_OnKeyUp

void Game_OnKeyUp(Game *this)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = Scene_GetKind(&this->scene);
  if ((iVar2 == 1) && (this->dlgState == 2)) {
    bVar1 = TextList_LineUp(&this->desc);
    if (!bVar1) {
      return;
    }
  }
  else {
    bVar1 = TextList_PageUp(&this->desc);
    if (!bVar1) {
      return;
    }
    this->f22c = this->f22c - 1;
  }
  Game_ShowText(this,'\0');
  return;
}


// 00026908 Game_OnKeyDown

void Game_OnKeyDown(Game *this)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  char cVar4;
  Scene *this_00;
  TextList *this_01;
  
  this_00 = &this->scene;
  iVar3 = Scene_GetKind(this_00);
  if ((iVar3 == 1) && (this->dlgState == 2)) {
    bVar1 = TextList_LineDown(&this->desc);
    if (bVar1) {
      Game_ShowText(this,'\0');
      return;
    }
  }
  else {
    this_01 = &this->desc;
    bVar1 = TextList_PageDown(this_01);
    if (bVar1) {
      bVar2 = this->f22c + 1;
      this->f22c = bVar2;
      if ((this->f22d < bVar2) &&
         ((iVar3 = Scene_GetKind(this_00), iVar3 == 0 || (this->dlgState != 2)))) {
        this->f22d = this->f22d + 1;
        iVar3 = Scene_GetKind(this_00);
        if ((iVar3 != 1) || (cVar4 = '\0', this->dlgState == 0)) {
          cVar4 = '\x01';
        }
        TextList_DrawTyped(this_01,'\x01',cVar4);
        iVar3 = Scene_GetKind(this_00);
        if ((iVar3 == 1) && (this->dlgState == 1)) {
          Game_DialogAdvance(this);
        }
      }
      else {
        Scene_GetKind(this_00);
        TextList_Draw(this_01,'\x01');
      }
      Game_ShowText(this,'\x01');
      iVar3 = Scene_GetKind(this_00);
      if (iVar3 != 0) {
        return;
      }
      bVar1 = TextList_AtEnd(this_01);
      if (!bVar1) {
        return;
      }
      Game_BlinkButton5(this,3,100);
      return;
    }
    iVar3 = Scene_GetKind(this_00);
    if (iVar3 != 1) {
      return;
    }
  }
  Game_DialogAdvance(this);
  return;
}


// 00026a94 Game_ExitMenu

void Game_ExitMenu(Game *this)

{
  ushort uVar1;
  char cVar2;
  byte bVar3;
  Link *pLVar4;
  CString *pCVar5;
  CString *this_00;
  ScriptOpList *pSVar6;
  int iVar7;
  uint uVar8;
  CString *this_01;
  uint uVar9;
  uint uVar10;
  GameState **ppGVar11;
  Scene *this_02;
  uint uVar12;
  CString CStack_70;
  Link LStack_6c;
  Link aLStack_68 [2];
  CString local_60 [15];
  
  this_01 = (CString *)&stack0xffffffdc;
  pCVar5 = local_60;
  iVar7 = 0xf;
  do {
    iVar7 = iVar7 + -1;
    pCVar5->str = g_afxEmptyString;
    pCVar5 = pCVar5 + 1;
  } while (iVar7 != 0);
  this_02 = &this->scene;
  iVar7 = Scene_GetKind(this_02);
  if (iVar7 == 2) {
    uVar8 = 0;
    do {
      CString_AssignA(local_60 + uVar8,&g_emptyA);
      uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < 10);
    uVar10 = 0;
    ppGVar11 = &this->state;
    uVar8 = 0;
    do {
      pLVar4 = Scene_GetExit(this_02,&LStack_6c,uVar8);
      cVar2 = Rec9ec_Get0((*ppGVar11)->scenes + pLVar4->id);
      if (cVar2 == '\0') {
        pLVar4 = Scene_GetExit(this_02,aLStack_68,uVar8);
        pCVar5 = Rec9ec_GetName((*ppGVar11)->scenes + pLVar4->id,&CStack_70);
        this_00 = local_60 + uVar10;
        uVar10 = uVar10 + 1 & 0xff;
        CString_Assign(this_00,pCVar5);
        CString_Dtor(&CStack_70);
      }
      uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < 10);
    uVar8 = PopupMenu_Run(&this->popup,0xf0,0xb4,(int)local_60);
    uVar12 = 0;
    uVar10 = 0;
    do {
      pLVar4 = Scene_GetExit(this_02,aLStack_68,uVar10);
      cVar2 = Rec9ec_Get0((*ppGVar11)->scenes + pLVar4->id);
      if (cVar2 == '\0') {
        uVar9 = uVar10;
        if (uVar12 == (int)(char)uVar8) break;
        uVar12 = uVar12 + 1 & 0xff;
      }
      uVar10 = uVar10 + 1;
      uVar9 = uVar8;
    } while ((uVar10 & 0xff) < 10);
    if ((char)uVar9 != -1) {
      pLVar4 = Scene_GetExit(this_02,aLStack_68,uVar9);
      uVar1 = pLVar4->id;
      cVar2 = Rec9ec_Get1((*ppGVar11)->scenes + uVar1);
      if (cVar2 == '\0') {
        bVar3 = Scene_GetF12598(this_02);
        pSVar6 = Scene_GetScripts(this_02);
        Script_RunList(this,(int)pSVar6,(uint)bVar3);
      }
      else {
        GameState_SetCurScene(*ppGVar11,uVar1);
        pLVar4 = Scene_GetExit(this_02,aLStack_68,uVar9);
        if (pLVar4->script != 0xff) {
          pLVar4 = Scene_GetExit(this_02,aLStack_68,uVar9);
          pSVar6 = Scene_GetScripts(this_02);
          Script_RunList(this,(int)pSVar6,(uint)pLVar4->script);
        }
        Game_OnUserMsg1(this);
      }
    }
  }
  iVar7 = 0xf;
  do {
    this_01 = this_01 + -1;
    CString_Dtor(this_01);
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return;
}


// 00026d24 Game_LoadScene

void Game_LoadScene(Game *this,uint param_2)

{
  char cVar1;
  int iVar2;
  GameState **ppGVar3;
  Scene *this_00;
  CString local_20;
  CString local_1c;
  
  this_00 = &this->scene;
  LoadSceneScript((int)this_00,param_2,1);
  this->f230[0] = 0xff;
  ppGVar3 = &this->state;
  cVar1 = Rec9ec_Get2((*ppGVar3)->scenes + (param_2 & 0xffff));
  if (cVar1 != '\0') {
    Rec9ec_InitFromScene((*ppGVar3)->scenes,param_2,(int)this_00);
  }
  this->dlgTopic = (ushort)param_2;
  GameState_SetCurScene(*ppGVar3,(ushort)param_2);
  this->dlgState = 0;
  this->dlgSel = 0xff;
  iVar2 = Rec9ec_Get3((*ppGVar3)->scenes + (param_2 & 0xffff));
  Scene_SetCurStr(this_00,(char)iVar2);
  Scene_GetCurString(this_00,&local_20);
  Game_SetDescText(this,local_20);
  CString_CtorA(&local_1c,&g_emptyA);
  Game_SetStatusText(this,local_1c);
  return;
}


// 00026e18 Game_SetDescText

void Game_SetDescText(Game *this,CString param_2)

{
  CString local_24;
  CString aCStack_c [3];
  
  this->f22c = 0;
  this->f22d = 0;
  aCStack_c[0].str = param_2.str;
  CString_Assign(&this->descStr,aCStack_c);
  CString_CopyCtor(&local_24,&this->descStr);
  TextList_SetText(&this->desc,local_24);
  CString_Dtor(aCStack_c);
  return;
}


// 00026e78 Game_SetStatusText

void Game_SetStatusText(Game *this,CString param_2)

{
  CString local_24;
  CString aCStack_c [3];
  
  aCStack_c[0].str = param_2.str;
  CString_Assign(&this->statusStr,aCStack_c);
  CString_CopyCtor(&local_24,&this->statusStr);
  TextList_SetText(&this->status,local_24);
  CString_Dtor(aCStack_c);
  return;
}


// 00026ec4 Game_SetInventoryText

void Game_SetInventoryText(Game *this,CString param_2)

{
  char cVar1;
  GameObj *this_00;
  uint uVar2;
  char cVar3;
  CString local_30;
  CString aCStack_c [3];
  
  aCStack_c[0].str = param_2.str;
  CString_Assign(&this->invStr,aCStack_c);
  CString_CopyCtor(&local_30,&this->invStr);
  TextList_SetText(&this->inv,local_30);
  cVar3 = '\0';
  if (this->invSel != 0) {
    uVar2 = 0;
    cVar3 = '\0';
    do {
      this_00 = Inventory_GetObj(&this->state->inventory,uVar2);
      cVar1 = GameObj_IsSelected(this_00);
      uVar2 = uVar2 + 1 & 0xff;
      if (cVar1 == '\0') {
        cVar3 = cVar3 + '\x01';
      }
    } while (uVar2 < this->invSel);
  }
  TextList_SetLineTag(&this->inv,this->invSel - cVar3,this->font2);
  CString_Dtor(aCStack_c);
  return;
}


// 00026f94 Game_DialogChoiceAtLine

uint Game_DialogChoiceAtLine(Game *this,byte param_2)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  uint uVar4;
  Rec15c *pRVar5;
  CString *pCVar6;
  GameState **ppGVar7;
  Scene *this_00;
  uint uVar8;
  byte local_78;
  CString local_74;
  CString local_70;
  CString local_6c;
  Rec44 RStack_68;
  
  local_74.str = g_afxEmptyString;
  ppGVar7 = &this->state;
  uVar8 = 0xffffffff;
  uVar4 = Rec9ec_GetDialogTopic((*ppGVar7)->scenes + this->dlgTopic);
  this_00 = &this->scene;
  pRVar5 = Scene_GetTopic(this_00,uVar4);
  pCVar6 = Rec15c_GetName(pRVar5,&local_70);
  CString_Assign(&local_74,pCVar6);
  CString_Dtor(&local_70);
  CString_CopyCtor(&local_6c,&local_74);
  local_78 = Text_CountLines(this->descFont,0x15,0xd6,local_6c);
  uVar4 = Rec9ec_GetDialogTopic((*ppGVar7)->scenes + this->dlgTopic);
  pRVar5 = Scene_GetTopic(this_00,uVar4);
  cVar1 = Rec15c_GetCount(pRVar5);
  if (local_78 < param_2) {
    local_6c.str = (wchar_t *)(cVar1 + -1);
    do {
      if ((int)local_6c.str <= (int)(char)uVar8) break;
      uVar8 = ((char)uVar8 + 1) * 0x1000000 >> 0x18;
      uVar4 = Rec9ec_GetDialogTopic((*ppGVar7)->scenes + this->dlgTopic);
      pRVar5 = Scene_GetTopic(this_00,uVar4);
      bVar2 = Rec44_AnyActive((Rec44 *)pRVar5,uVar8);
      if (bVar2) {
        CString_AssignA(&local_74,s__00043e8c);
        uVar4 = Rec9ec_GetDialogTopic((*ppGVar7)->scenes + this->dlgTopic);
        pRVar5 = Scene_GetTopic(this_00,uVar4);
        pCVar6 = (CString *)Rec15c_GetRec44(pRVar5,(int)&RStack_68,uVar8);
        CString_Append(&local_74,pCVar6);
        Rec44_Dtor(&RStack_68);
        CString_CopyCtor(&local_70,&local_74);
        bVar3 = Text_CountLines(this->descFont,0x15,0xd6,local_70);
        local_78 = local_78 + bVar3;
      }
    } while (local_78 < param_2);
  }
  uVar4 = Rec9ec_GetDialogTopic((*ppGVar7)->scenes + this->dlgTopic);
  pRVar5 = Scene_GetTopic(this_00,uVar4);
  bVar3 = Rec15c_GetCount(pRVar5);
  if (((int)(bVar3 - 1) < (int)(char)uVar8) || (local_78 < param_2)) {
    uVar8 = 0xffffffff;
  }
  CString_Dtor(&local_74);
  return uVar8;
}


// 000271b8 Game_DialogHighlight

void Game_DialogHighlight(Game *this,char param_2)

{
  uint uVar1;
  Rec15c *pRVar2;
  
  if (param_2 != -1) {
    uVar1 = Rec9ec_GetDialogTopic(this->state->scenes + this->dlgTopic);
    pRVar2 = Scene_GetTopic(&this->scene,uVar1);
    TextList_SetDialogMenu
              (&this->desc,(int)pRVar2,this->titleFont,this->descFont,this->hiFont,param_2);
    Game_ShowText(this,'\0');
  }
  return;
}


// 00027248 Game_OnUserMsg1

void Game_OnUserMsg1(Game *this)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  ScriptOpList *pSVar4;
  TextList *this_00;
  GameState **ppGVar5;
  CString local_28;
  
  this->f230[3] = 0;
  ppGVar5 = &this->state;
  cVar1 = Rec9ec_Get5((*ppGVar5)->scenes + this->dlgTopic);
  if (cVar1 != '\0') {
    uVar3 = Rec9ec_Get7((*ppGVar5)->scenes + this->dlgTopic);
    pSVar4 = Scene_GetScripts(&this->scene);
    Script_RunList(this,(int)pSVar4,uVar3);
  }
  this_00 = &this->desc;
  TextList_SetFont(this_00,this->descFont);
  CString_CtorA(&local_28,&g_emptyA);
  Game_SetStatusText(this,local_28);
  this->dlgState = 0;
  TextList_BlitToLayer(this_00,'\x01');
  TextList_DrawDirect(this_00);
  TextList_BlitToLayer(&this->status,'\x01');
  TextList_DrawDirect(&this->status);
  if (this->f230[5] == 0) {
    FadeIn565((int)this->screen,0,0,0xf0,0xb4,'\x03');
  }
  else {
    Screen_FadeToWhite(this->screen,0,0,0xf0,0xb4,'\x03');
  }
  Scene_FreeResources(&this->scene);
  uVar2 = GameState_GetCurScene(*ppGVar5);
  Game_LoadScene(this,(uint)uVar2);
  Game_DrawSceneToLayer(this,'\x04');
  if (this->f230[5] == 0) {
    Screen_FadeFromBlack(this->screen,0,0,0xf0,0xb4,'\x04','\x03');
  }
  else {
    if (this->f230[4] != 0) {
      Game_PlayPanelAnim(this);
    }
    Screen_FadeFromWhite(this->screen,0,0,0xf0,0xb4,'\x04','\x03');
    Screen_FillAll(this->screen,g_colorKey);
    Game_DrawSceneToLayer(this,'\x03');
    Game_Redraw(this);
    this->f230[4] = 0;
    this->f230[5] = 0;
  }
  FlushInputMessages();
  cVar1 = Rec9ec_Get6((*ppGVar5)->scenes + this->dlgTopic);
  if (cVar1 == '\0') {
    FlushInputMessages();
    Game_ShowTextTyped(this,1,'\x01');
  }
  else {
    uVar3 = Rec9ec_Get8((*ppGVar5)->scenes + this->dlgTopic);
    pSVar4 = Scene_GetScripts(&this->scene);
    Script_RunList(this,(int)pSVar4,uVar3);
  }
  return;
}


// 000274a8 Game_DialogAdvance

void Game_DialogAdvance(Game *this)

{
  bool bVar1;
  uint uVar2;
  Rec15c *pRVar3;
  int iVar4;
  GameState **ppGVar5;
  byte *pbVar6;
  Rec44 RStack_68;
  
  pbVar6 = &this->dlgState;
  if (*pbVar6 == 0) {
    uVar2 = Rec9ec_GetDialogTopic(this->state->scenes + this->dlgTopic);
    pRVar3 = Scene_GetTopic(&this->scene,uVar2);
    TextList_SetDialogTitle(&this->desc,pRVar3,this->titleFont);
    Game_ShowTextTyped(this,0,'\0');
    *pbVar6 = 1;
  }
  if (*pbVar6 == 1) {
    bVar1 = TextList_AtEnd(&this->desc);
    if (bVar1) {
      uVar2 = Rec9ec_GetDialogTopic(this->state->scenes + this->dlgTopic);
      pRVar3 = Scene_GetTopic(&this->scene,uVar2);
      TextList_SetDialogMenu2
                (&this->desc,(int)pRVar3,this->titleFont,this->descFont,this->hiFont,-1);
      Game_ShowText(this,'\x01');
      *pbVar6 = 2;
    }
    else {
      Game_BlinkButton5(this,2,100);
    }
  }
  if (*pbVar6 == 3) {
    TextList_Clear(&this->desc);
    ppGVar5 = &this->state;
    uVar2 = Rec9ec_GetDialogTopic((*ppGVar5)->scenes + this->dlgTopic);
    pRVar3 = Scene_GetTopic(&this->scene,uVar2);
    iVar4 = Rec15c_GetRec44(pRVar3,(int)&RStack_68,(uint)this->dlgSel);
    Rec9ec_Set4((*ppGVar5)->scenes + this->dlgTopic,*(undefined1 *)(iVar4 + 8));
    Rec44_Dtor(&RStack_68);
    uVar2 = Rec9ec_GetDialogTopic((*ppGVar5)->scenes + this->dlgTopic);
    pRVar3 = Scene_GetTopic(&this->scene,uVar2);
    TextList_SetDialogMenu(&this->desc,(int)pRVar3,this->titleFont,this->descFont,this->hiFont,-1);
    Game_ShowText(this,'\x01');
    *pbVar6 = 2;
  }
  return;
}


// 0002769c Game_DialogOnTap

void Game_DialogOnTap(Game *this,uint param_2,uint param_3)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  Rec15c *pRVar7;
  Rec44 *this_00;
  undefined1 *puVar8;
  ScriptOpList *pSVar9;
  TextList *this_01;
  Scene *this_02;
  GameState **ppGVar10;
  int iVar11;
  undefined1 *puVar12;
  ushort local_196;
  ushort local_194 [2];
  byte *local_190;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined1 auStack_17c [60];
  Rec44 RStack_140;
  Rec44 RStack_f8;
  Rec44 RStack_b0;
  Rec44 RStack_68;
  
  this_01 = &this->desc;
  uVar4 = TextList_HitTest(this_01,param_2 & 0xffff,param_3 & 0xffff);
  if (((uVar4 & 0xff) != 0) && (local_190 = &this->dlgState, *local_190 == 2)) {
    iVar5 = TextList_LineAt(this_01,param_2 & 0xffff,param_3 & 0xffff);
    uVar4 = Game_DialogChoiceAtLine(this,(byte)iVar5);
    bVar3 = (byte)uVar4;
    if (bVar3 != 0xff) {
      Game_DialogHighlight(this,bVar3);
      WaitForPenUp((short *)local_194,(short *)&local_196);
      iVar5 = TextList_LineAt(this_01,(uint)local_194[0],(uint)local_196);
      uVar6 = Game_DialogChoiceAtLine(this,(byte)iVar5);
      if (bVar3 == (byte)uVar6) {
        ppGVar10 = &this->state;
        uVar6 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
        this_02 = &this->scene;
        pRVar7 = Scene_GetTopic(this_02,uVar6);
        iVar5 = Rec15c_GetRec44(pRVar7,(int)&RStack_b0,uVar4);
        bVar2 = RandomRange(*(char *)(iVar5 + 0x40));
        this_00 = &RStack_b0;
        while( true ) {
          Rec44_Dtor(this_00);
          uVar6 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
          pRVar7 = Scene_GetTopic(this_02,uVar6);
          iVar5 = Rec15c_GetRec44(pRVar7,(int)&RStack_140,uVar4);
          iVar5 = *(int *)((uint)bVar2 * 0xc + iVar5 + 4);
          Rec44_Dtor(&RStack_140);
          if (iVar5 != 1) break;
          uVar6 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
          pRVar7 = Scene_GetTopic(this_02,uVar6);
          iVar5 = Rec15c_GetRec44(pRVar7,(int)&RStack_f8,uVar4);
          bVar2 = RandomRange(*(char *)(iVar5 + 0x40));
          this_00 = &RStack_f8;
        }
        uVar6 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
        pRVar7 = Scene_GetTopic(this_02,uVar6);
        Rec15c_GetRec44(pRVar7,(int)&local_188,uVar4);
        puVar8 = auStack_17c;
        iVar5 = 0x38;
        puVar12 = &stack0xfffffe24;
        do {
          iVar11 = iVar5 + -1;
          *puVar12 = *puVar8;
          bVar1 = 0 < iVar5;
          puVar8 = puVar8 + 1;
          iVar5 = iVar11;
          puVar12 = puVar12 + 1;
        } while (iVar11 != 0 && bVar1);
        TextList_SetDialogReply(&this->desc,local_188,local_184,local_180);
        *local_190 = 3;
        this->dlgSel = bVar3;
        Game_ShowTextTyped(this,0,'\x01');
        uVar6 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
        pRVar7 = Scene_GetTopic(this_02,uVar6);
        Rec15c_Advance(pRVar7,uVar4,(uint)bVar2);
        uVar4 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
        pRVar7 = Scene_GetTopic(this_02,uVar4);
        iVar5 = Rec15c_GetRec44(pRVar7,(int)&RStack_68,(uint)this->dlgSel);
        uVar4 = (uint)*(byte *)((uint)bVar2 * 0xc + iVar5 + 9);
        Rec44_Dtor(&RStack_68);
        if (uVar4 != 0xff) {
          pSVar9 = Scene_GetScripts(this_02);
          Script_RunList(this,(int)pSVar9,uVar4);
        }
        iVar5 = Scene_GetKind(this_02);
        if (iVar5 == 1) {
          Game_BlinkButton5(this,2,100);
        }
        uVar4 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
        pRVar7 = Scene_GetTopic(this_02,uVar4);
        uVar4 = Rec15c_AllDone(pRVar7);
        if ((uVar4 & 0xff) != 0) {
          uVar4 = Rec9ec_GetDialogTopic((*ppGVar10)->scenes + this->dlgTopic);
          pRVar7 = Scene_GetTopic(this_02,uVar4);
          bVar3 = Rec15c_GetScript(pRVar7);
          if (bVar3 != 0xff) {
            pSVar9 = Scene_GetScripts(this_02);
            Script_RunList(this,(int)pSVar9,(uint)bVar3);
          }
        }
      }
      else {
        uVar4 = Rec9ec_GetDialogTopic(this->state->scenes + this->dlgTopic);
        pRVar7 = Scene_GetTopic(&this->scene,uVar4);
        TextList_SetDialogMenu(this_01,(int)pRVar7,this->titleFont,this->descFont,this->hiFont,-1);
        Game_ShowText(this,'\0');
      }
    }
  }
  return;
}


// 00027aa4 Game_OnSceneTap

void Game_OnSceneTap(Game *this,uint param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = Scene_GetKind(&this->scene);
  if (iVar1 == 1) {
    Game_DialogOnTap(this,param_2,param_3);
  }
  else if (iVar1 == 2) {
    Game_ExploreOnTap(this,(ushort)param_2,(ushort)param_3);
  }
  return;
}


// 00027af4 Game_ExploreOnTap

void Game_ExploreOnTap(Game *this,ushort param_2,ushort param_3)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  RecF8 *pRVar6;
  Rec9 *pRVar7;
  uint uVar8;
  Scene *this_00;
  uint uVar9;
  uint local_8;
  uint local_4;
  
  local_8 = (uint)param_2;
  this_00 = &this->scene;
  local_4 = (uint)param_3;
  bVar1 = Scene_GetNumObjs(this_00);
  uVar9 = 0xff;
  bVar5 = 10;
  uVar8 = 0;
  if (bVar1 != 0) {
    do {
      pRVar6 = Scene_GetObj(this_00,uVar8);
      bVar2 = RecF8_HitTest(pRVar6,local_8,local_4);
      if (bVar2) {
        pRVar7 = Rec9ec_GetObjState(this->state->scenes + this->dlgTopic,uVar8);
        cVar3 = Rec9_IsVisible(pRVar7);
        if (cVar3 != '\0') {
          pRVar6 = Scene_GetObj(this_00,uVar8);
          bVar4 = RecF8_Get6(pRVar6);
          if (bVar4 < bVar5) {
            pRVar6 = Scene_GetObj(this_00,uVar8);
            bVar5 = RecF8_Get6(pRVar6);
            uVar9 = uVar8;
          }
        }
      }
    } while ((bVar5 != 0) && (uVar8 = uVar8 + 1, (uVar8 & 0xff) < (uint)bVar1));
  }
  if ((uVar9 & 0xff) != 0xff) {
    pRVar6 = Scene_GetObj(this_00,uVar9);
    pRVar7 = Rec9ec_GetObjState(this->state->scenes + this->dlgTopic,uVar9);
    Game_ObjectAction(this,(int)pRVar7,(int)pRVar6,local_8,param_3);
  }
  return;
}


// 00027c50 Game_BuildActionMenu

void Game_BuildActionMenu(Game *this,int param_2,int param_3,int param_4)

{
  byte bVar1;
  char cVar2;
  CString *pCVar3;
  uint uVar4;
  uint uVar5;
  CString aCStack_34 [2];
  CString aCStack_2c [3];
  
  uVar4 = 0;
  do {
    CString_AssignA((CString *)(param_4 + uVar4 * 4),&g_emptyA);
    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 0xf);
  uVar4 = 0;
  bVar1 = RecF8_GetNumActions((RecF8 *)param_3);
  if (bVar1 != 0) {
    uVar5 = 0;
    do {
      cVar2 = Rec9_GetFlag((Rec9 *)param_2,uVar5);
      if (cVar2 != '\0') {
        pCVar3 = (CString *)RecF8_GetSub14((RecF8 *)param_3,(int)aCStack_34,uVar5);
        CString_Assign((CString *)(param_4 + uVar4 * 4),pCVar3);
        CString_Dtor(aCStack_2c);
        CString_Dtor(aCStack_34);
        uVar4 = uVar4 + 1 & 0xff;
      }
      uVar5 = uVar5 + 1 & 0xff;
    } while (uVar5 < bVar1);
  }
  return;
}


// 00027d10 Game_MapActionIndex

void Game_MapActionIndex(Game *this,int param_2,int param_3,char *param_4)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  bVar1 = RecF8_GetNumActions((RecF8 *)param_3);
  uVar3 = 0;
  if (bVar1 != 0) {
    do {
      cVar2 = Rec9_GetFlag((Rec9 *)param_2,uVar3);
      if (cVar2 != '\0') {
        if (uVar4 == (int)*param_4) {
          *param_4 = (char)uVar3;
          return;
        }
        uVar4 = uVar4 + 1 & 0xff;
      }
      uVar3 = uVar3 + 1;
    } while ((uVar3 & 0xff) < (uint)bVar1);
  }
  return;
}


// 00027d80 Game_ObjectAction

undefined4 Game_ObjectAction(Game *this,int param_2,int param_3,uint param_4,ushort param_5)

{
  byte bVar1;
  uint uVar2;
  CString *pCVar3;
  CString *pCVar4;
  ScriptOpList *pSVar5;
  int iVar6;
  CString *this_00;
  undefined4 uVar7;
  byte local_e8 [4];
  CString local_e4;
  CString local_e0;
  CString local_dc;
  CString aCStack_d8 [2];
  CString aCStack_d0 [2];
  CString aCStack_c8 [4];
  CString aCStack_b8 [2];
  CString aCStack_b0 [4];
  CString aCStack_a0 [2];
  CString aCStack_98 [4];
  CString aCStack_88 [2];
  CString aCStack_80 [4];
  CString aCStack_70 [2];
  CString aCStack_68 [4];
  CString local_58 [15];
  
  this_00 = (CString *)&stack0xffffffe4;
  pCVar3 = local_58;
  iVar6 = 0xf;
  do {
    iVar6 = iVar6 + -1;
    pCVar3->str = g_afxEmptyString;
    pCVar3 = pCVar3 + 1;
  } while (iVar6 != 0);
  uVar7 = 0;
  Game_BuildActionMenu(this,param_2,param_3,(int)local_58);
  RecF8_GetName((RecF8 *)param_3,&local_e0);
  Game_SetStatusText(this,local_e0);
  CString_CtorA(&local_dc,&g_emptyA);
  Game_SetDescText(this,local_dc);
  Game_ShowText(this,'\x01');
  Game_DrawStatusLine(this);
  uVar2 = PopupMenu_Run(&this->popup,param_4 & 0xffff,(uint)param_5,(int)local_58);
  local_e8[0] = (byte)uVar2;
  Game_MapActionIndex(this,param_2,param_3,(char *)local_e8);
  if (local_e8[0] == 0xff) {
    CString_CtorA(&local_e4,&g_emptyA);
    Game_SetStatusText(this,local_e4);
  }
  else {
    pCVar3 = RecF8_GetName((RecF8 *)param_3,&local_e4);
    CString_CtorA(&local_e0,s_space);
    pCVar4 = CString_Plus(aCStack_d8,local_58 + (uVar2 & 0xff),&local_e0);
    CString_Plus(&local_dc,pCVar4,pCVar3);
    Game_SetStatusText(this,local_dc);
    CString_Dtor(aCStack_d8);
    CString_Dtor(&local_e4);
    CString_Dtor(&local_e0);
    iVar6 = RecF8_GetSub14((RecF8 *)param_3,(int)aCStack_d0,(uint)local_e8[0]);
    iVar6 = *(int *)(iVar6 + 0xc);
    CString_Dtor(aCStack_c8);
    CString_Dtor(aCStack_d0);
    if (iVar6 == 0) {
      iVar6 = RecF8_GetSub14((RecF8 *)param_3,(int)aCStack_88,(uint)local_e8[0]);
      CString_CopyCtor(&local_e4,(CString *)(iVar6 + 8));
      Game_SetDescText(this,local_e4);
      CString_Dtor(aCStack_80);
      CString_Dtor(aCStack_88);
      Game_DrawStatusLine(this);
      Game_ShowTextTyped(this,1,'\x01');
    }
    else if (iVar6 == 1) {
      iVar6 = RecF8_GetSub14((RecF8 *)param_3,(int)aCStack_70,(uint)local_e8[0]);
      Scene_GetZoom(&this->scene,(uint)*(byte *)(iVar6 + 0x12));
      CString_Dtor(aCStack_68);
      CString_Dtor(aCStack_70);
      bVar1 = this->f230[0];
      uVar7 = 1;
      iVar6 = RecF8_GetSub14((RecF8 *)param_3,(int)aCStack_b8,(uint)local_e8[0]);
      this->f230[0] = *(byte *)(iVar6 + 0x12);
      CString_Dtor(aCStack_b0);
      CString_Dtor(aCStack_b8);
      Game_OnUserMsg3(this,(int)(char)this->f230[0]);
      this->f230[0] = bVar1;
    }
    else if (iVar6 == 2) {
      Game_DrawStatusLine(this);
      iVar6 = RecF8_GetSub14((RecF8 *)param_3,(int)aCStack_a0,(uint)local_e8[0]);
      pSVar5 = Scene_GetScripts(&this->scene);
      Script_RunList(this,(int)pSVar5,(uint)*(byte *)(iVar6 + 0x10));
      CString_Dtor(aCStack_98);
      CString_Dtor(aCStack_a0);
    }
  }
  iVar6 = 0xf;
  do {
    this_00 = this_00 + -1;
    CString_Dtor(this_00);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  return uVar7;
}


// 00028070 Game_RunZoom

void Game_RunZoom(Game *this,int param_2,undefined1 *param_3)

{
  byte bVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  ImgRect *pIVar6;
  RecF8 *pRVar7;
  Rec9 *pRVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  ushort local_4e;
  ushort local_4c;
  ushort local_4a;
  ushort local_48;
  ImgRect IStack_40;
  
  this->f230[2] = 0;
  this->f230[1] = 0;
  uVar12 = 0;
  Img_Load((Zoom *)param_3);
  Game_DrawZoom(this,param_3);
  pIVar6 = Zoom_GetImg((Zoom *)param_3,&IStack_40);
  local_4a = (short)pIVar6->w + 0x29;
  pIVar6 = Zoom_GetImg((Zoom *)param_3,&IStack_40);
  local_48 = (short)pIVar6->h + 0x1e;
  bVar1 = Zoom_GetCount((Zoom *)param_3);
  do {
    if (this->f230[1] != 0) break;
    WaitForPenDown((short *)&local_4c,(short *)&local_4e);
    uVar10 = (uint)local_4c;
    uVar11 = (uint)local_4e;
    if ((((uVar10 < 0x29) || (local_4a <= uVar10)) || (uVar11 < 0x1e)) || (local_48 <= uVar11)) {
      if (uVar11 < 0xb4) {
        uVar12 = 1;
      }
      else {
        iVar9 = Game_HitTest(this,uVar10,uVar11);
        if (iVar9 == 2) {
          Game_OpenInventory(this);
        }
        else if (iVar9 == 5) {
          Game_OnKeyUp(this);
        }
        else if (iVar9 == 6) {
          Game_OnKeyDown(this);
        }
      }
    }
    else {
      local_4c = local_4c - 0x29;
      local_4e = local_4e - 0x1e;
      uVar10 = 0xff;
      bVar5 = 10;
      uVar11 = 0;
      if (bVar1 != 0) {
        do {
          pRVar7 = Zoom_GetRec((Zoom *)param_3,uVar11);
          bVar2 = RecF8_HitTest(pRVar7,(uint)local_4c,(uint)local_4e);
          if (bVar2) {
            pRVar8 = RecE1_GetObjState((RecE1 *)param_2,uVar11);
            cVar3 = Rec9_IsVisible(pRVar8);
            if (cVar3 != '\0') {
              pRVar7 = Zoom_GetRec((Zoom *)param_3,uVar11);
              bVar4 = RecF8_Get6(pRVar7);
              if (bVar4 < bVar5) {
                pRVar7 = Zoom_GetRec((Zoom *)param_3,uVar11);
                bVar5 = RecF8_Get6(pRVar7);
                uVar10 = uVar11;
              }
            }
          }
        } while ((bVar5 != 0) && (uVar11 = uVar11 + 1, (uVar11 & 0xff) < (uint)bVar1));
      }
      if ((uVar10 & 0xff) != 0xff) {
        pRVar7 = Zoom_GetRec((Zoom *)param_3,uVar10);
        pRVar8 = RecE1_GetObjState((RecE1 *)param_2,uVar10);
        uVar12 = Game_ObjectAction(this,(int)pRVar8,(int)pRVar7,local_4c + 0x29,local_4e + 0x1e);
      }
    }
  } while ((uVar12 & 0xff) == 0);
  Img_Free2((Zoom *)param_3);
  if (this->f230[2] == 0) {
    Game_ClearOverlay(this);
  }
  this->f230[0] = 0xff;
  return;
}


// 000282ec Script_RunList

void Script_RunList(Game *this,int param_2,uint param_3)

{
  bool bVar1;
  byte bVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte abStack_8ac [1092];
  ScriptOpList local_468;
  
  this->f230[3] = 0;
  uVar4 = param_3 & 0xff;
  while (uVar4 != 0xff) {
    ScriptOpList_Copy(&local_468,(ScriptOpList *)(uVar4 * 0x450 + param_2));
    pbVar3 = &local_468.ops[0].bc;
    iVar5 = 0x444;
    pbVar7 = abStack_8ac;
    do {
      iVar6 = iVar5 + -1;
      *pbVar7 = *pbVar3;
      bVar1 = 0 < iVar5;
      pbVar3 = pbVar3 + 1;
      iVar5 = iVar6;
      pbVar7 = pbVar7 + 1;
    } while (iVar6 != 0 && bVar1);
    bVar2 = Script_Run(this,local_468.ops[0].op,local_468.ops[0]._4_4_,local_468.ops[0]._8_4_);
    uVar4 = (uint)bVar2;
  }
  if (this->f230[3] != 0) {
    PostMessageW(g_hwnd,0x400,1,0);
  }
  return;
}


// 000283b0 Script_Run

undefined1 Script_Run(Game *this,int param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  ushort uVar4;
  ushort uVar5;
  bool bVar6;
  byte bVar7;
  char cVar8;
  bool bVar9;
  char cVar10;
  undefined4 *puVar11;
  CString *pCVar12;
  GameObj *pGVar13;
  RecE1 *pRVar14;
  Rec9 *pRVar15;
  undefined1 *puVar16;
  ScriptOp *this_00;
  int iVar17;
  undefined1 uVar18;
  uint uVar19;
  GameState **ppGVar20;
  undefined4 uVar21;
  uint uVar22;
  uint uVar23;
  undefined1 local_8f07;
  ushort local_8f06;
  CString local_8f04;
  CString local_8f00;
  ushort local_8efc [2];
  CString local_8ef8;
  CString CStack_8ef4;
  CString CStack_8ef0;
  CString CStack_8eec;
  CString local_8ee8;
  CString CStack_8ee4;
  CString local_8ee0;
  CString CStack_8edc;
  CString CStack_8ed8;
  CString local_8ed4;
  CString CStack_8ed0;
  CString CStack_8ecc;
  CString CStack_8ec8;
  CString CStack_8ec4;
  CString local_8ec0;
  CString local_8ebc;
  CString local_8eb8;
  CString local_8eb4;
  CString CStack_8eb0;
  CString local_8eac;
  CString local_8ea8;
  CString local_8ea4;
  CString CStack_8ea0;
  uint local_8e9c;
  ScriptOp SStack_8e98;
  ScriptOp SStack_8e68;
  ScriptOp SStack_8e38;
  ScriptOp SStack_8e08;
  ScriptOp SStack_8dd8;
  ScriptOp SStack_8da8;
  ScriptOp SStack_8d78;
  ScriptOp SStack_8d48;
  ScriptOp SStack_8d18;
  ScriptOp SStack_8ce8;
  ScriptOp SStack_8cb8;
  ScriptOp SStack_8c88;
  ScriptOp SStack_8c58;
  ScriptOp SStack_8c28;
  ScriptOp SStack_8bf8;
  ScriptOp SStack_8bc8;
  ScriptOp SStack_8b98;
  ScriptOp SStack_8b68;
  ScriptOp SStack_8b38;
  ScriptOp SStack_8b08;
  ScriptOp SStack_8ad8;
  ScriptOp SStack_8aa8;
  ScriptOp SStack_8a78;
  ScriptOp SStack_8a48;
  ScriptOp SStack_8a18;
  ScriptOp SStack_89e8;
  ScriptOp SStack_89b8;
  ScriptOp SStack_8988;
  ScriptOp SStack_8958;
  ScriptOp SStack_8928;
  ScriptOp SStack_88f8;
  undefined4 auStack_88c8 [12];
  ScriptOp SStack_8898;
  undefined4 auStack_8868 [12];
  ScriptOp SStack_8838;
  undefined4 auStack_8808 [12];
  ScriptOp SStack_87d8;
  undefined4 auStack_87a8 [12];
  ScriptOp SStack_8778;
  ScriptOp SStack_8748;
  ScriptOp SStack_8718;
  ScriptOp SStack_86e8;
  ScriptOp SStack_86b8;
  ScriptOp SStack_8688;
  ScriptOp SStack_8658;
  ScriptOp SStack_8628;
  ScriptOp SStack_85f8;
  ScriptOp SStack_85c8;
  ScriptOp SStack_8598;
  ScriptOp SStack_8568;
  ScriptOp SStack_8538;
  ScriptOp SStack_8508;
  ScriptOp SStack_84d8;
  ScriptOp SStack_84a8;
  ScriptOp SStack_8478;
  ScriptOp SStack_8448;
  ScriptOp SStack_8418;
  ScriptOp SStack_83e8;
  ScriptOp SStack_83b8;
  ScriptOp SStack_8388;
  RecF8 RStack_8358;
  GameObj GStack_8260;
  int iStack_c;
  undefined4 uStack_8;
  int iStack_4;
  
  local_8f00.str = g_afxEmptyString;
  local_8f04.str = g_afxEmptyString;
  iStack_c = param_2;
  uStack_8 = param_3;
  iStack_4 = param_4;
  GameObj_Ctor(&GStack_8260);
  RecF8_Ctor(&RStack_8358);
  local_8f07 = 0xff;
  bVar7 = ScriptOpList_GetCount((ScriptOpList *)&iStack_c);
  local_8e9c = (uint)bVar7;
  uVar19 = 0;
  if (local_8e9c != 0) {
    do {
      puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8b98.op,uVar19);
      uVar21 = *puVar11;
      ScriptOp_Dtor(&SStack_8b98);
      switch(uVar21) {
      case 0:
        CString_AssignA(&local_8f04,&g_emptyA);
        while( true ) {
          CString_CtorA(&local_8ee8,&g_emptyA);
          iVar17 = wcscmp(local_8f04.str,local_8ee8.str);
          CString_Dtor(&local_8ee8);
          if (iVar17 != 0) break;
          puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8d18.op,uVar19);
          cVar10 = RandomRange('\x03');
          CString_Assign(&local_8f04,(CString *)(puVar11 + cVar10 + 8));
          ScriptOp_Dtor(&SStack_8d18);
        }
        CString_CopyCtor(&local_8ebc,&local_8f04);
        Game_SetDescText(this,local_8ebc);
        goto LAB_000297c8;
      case 1:
        CString_AssignA(&local_8f04,&g_emptyA);
        while( true ) {
          CString_CtorA(&local_8ee0,&g_emptyA);
          iVar17 = wcscmp(local_8f04.str,local_8ee0.str);
          CString_Dtor(&local_8ee0);
          if (iVar17 != 0) break;
          puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8598.op,uVar19);
          cVar10 = RandomRange('\x03');
          CString_Assign(&local_8f04,(CString *)(puVar11 + cVar10 + 8));
          ScriptOp_Dtor(&SStack_8598);
        }
        TextList_SetFont(&this->desc,this->titleFont);
        CString_CopyCtor(&local_8eb4,&local_8f04);
        Game_SetDescText(this,local_8eb4);
        TextList_SetFont(&this->desc,this->descFont);
        bVar7 = 0;
        goto LAB_000297cc;
      case 2:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_89e8.op,uVar19);
        cVar10 = *(char *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_89e8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8988.op,uVar19);
        cVar8 = *(char *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_8988);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8928.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8928);
        Book_SetFlag(&this->state->book,cVar10,cVar8,uVar18);
        break;
      case 3:
        break;
      case 4:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8898.op,uVar19);
        uVar5 = *(ushort *)((int)puVar11 + 6);
        uVar23 = (uint)uVar5;
        ScriptOp_Dtor(&SStack_8898);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8dd8.op,uVar19);
        uVar4 = *(ushort *)(puVar11 + 2);
        ScriptOp_Dtor(&SStack_8dd8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8478.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8478);
        local_8f06 = uVar5;
        if (uVar23 <= uVar4) {
          do {
            Rec9ec_Set1(this->state->scenes + uVar23,uVar18);
            local_8f06 = local_8f06 + 1;
            uVar23 = (uint)local_8f06;
          } while (uVar23 <= uVar4);
        }
        break;
      case 5:
        break;
      case 6:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8658.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8658);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8958.op,uVar19);
        Rec9ec_Set3((*ppGVar20)->scenes + uVar23,*(undefined1 *)(puVar11 + 1));
        this_00 = &SStack_8958;
        goto LAB_000296ac;
      case 7:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8a78.op,uVar19);
        bVar7 = *(byte *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_8a78);
        uVar23 = Inventory_Contains(&this->state->inventory,bVar7);
        if ((uVar23 & 0xff) == 0) {
          LoadObjectRecord((undefined4 *)&GStack_8260,(uint)bVar7);
          Inventory_Add(&this->state->inventory,(int)&GStack_8260);
        }
        break;
      case 8:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8cb8.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8cb8);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_87d8.op,uVar19);
        bVar7 = *(byte *)((int)puVar11 + 0xb);
        ScriptOp_Dtor(&SStack_87d8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8c58.op,uVar19);
        bVar1 = *(byte *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_8c58);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_83b8.op,uVar19);
        bVar2 = *(byte *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_83b8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8bf8.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8bf8);
        pRVar14 = Rec9ec_GetRecE1((*ppGVar20)->scenes + uVar23,(uint)bVar7);
        pRVar15 = RecE1_GetObjState(pRVar14,(uint)bVar1);
        goto LAB_00028c24;
      case 9:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8778.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8778);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8e98.op,uVar19);
        bVar7 = *(byte *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_8e98);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8538.op,uVar19);
        bVar2 = *(byte *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_8538);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8b38.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8b38);
        pRVar15 = Rec9ec_GetObjState((*ppGVar20)->scenes + uVar23,(uint)bVar7);
LAB_00028c24:
        Rec9_SetFlag(pRVar15,(uint)bVar2,uVar18);
        break;
      case 10:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8d78.op,uVar19);
        CString_Assign(&local_8f00,(CString *)(puVar11 + 8));
        ScriptOp_Dtor(&SStack_8d78);
        CString_MakeUpper(&local_8f00);
        CString_CtorA(&local_8ef8,s_STOP_00043e98);
        iVar17 = wcscmp(local_8f00.str,local_8ef8.str);
        CString_Dtor(&local_8ef8);
        if (iVar17 == 0) {
          sndPlaySoundW((LPCWSTR)0x0,2);
        }
        else {
          puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8838.op,uVar19);
          cVar10 = *(char *)(puVar11 + 1);
          ScriptOp_Dtor(&SStack_8838);
          if (cVar10 == '\0') {
            CString_CtorA(&CStack_8ef0,s_sounds__00043e90);
            pCVar12 = CString_Plus(&CStack_8ec4,&g_installDir,&CStack_8ef0);
            CString_Plus(&local_8ed4,pCVar12,&local_8f00);
            pCVar12 = MangleAssetPath(&CStack_8ecc,local_8ed4);
            sndPlaySoundW(pCVar12->str,0xb);
            CString_Dtor(&CStack_8ecc);
            CString_Dtor(&CStack_8ec4);
            pCVar12 = &CStack_8ef0;
          }
          else if (cVar10 == '\x01') {
            CString_CtorA(&CStack_8ef4,s_sounds__00043e90);
            pCVar12 = CString_Plus(&CStack_8ed8,&g_installDir,&CStack_8ef4);
            CString_Plus(&local_8ec0,pCVar12,&local_8f00);
            pCVar12 = MangleAssetPath(&CStack_8ea0,local_8ec0);
            sndPlaySoundW(pCVar12->str,3);
            CString_Dtor(&CStack_8ea0);
            CString_Dtor(&CStack_8ed8);
            pCVar12 = &CStack_8ef4;
          }
          else if (cVar10 == 'c') {
            CString_CtorA(&CStack_8eec,s_sounds__00043e90);
            pCVar12 = CString_Plus(&CStack_8eb0,&g_installDir,&CStack_8eec);
            CString_Plus(&local_8ea8,pCVar12,&local_8f00);
            pCVar12 = MangleAssetPath(&CStack_8ec8,local_8ea8);
            sndPlaySoundW(pCVar12->str,0);
            CString_Dtor(&CStack_8ec8);
            CString_Dtor(&CStack_8eb0);
            pCVar12 = &CStack_8eec;
          }
          else {
            CString_CtorA(&CStack_8ee4,s_sounds__00043e90);
            pCVar12 = CString_Plus(&CStack_8ed0,&g_installDir,&CStack_8ee4);
            CString_Plus(&local_8eb8,pCVar12,&local_8f00);
            pCVar12 = MangleAssetPath(&CStack_8edc,local_8eb8);
            sndPlaySoundW(pCVar12->str,3);
            CString_Dtor(&CStack_8edc);
            CString_Dtor(&CStack_8ed0);
            pCVar12 = &CStack_8ee4;
          }
          CString_Dtor(pCVar12);
        }
        break;
      case 0xb:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8e38.op,uVar19);
        GameState_SetCurScene(this->state,*(undefined2 *)((int)puVar11 + 6));
        ScriptOp_Dtor(&SStack_8e38);
        this->f230[3] = 1;
        bVar7 = Scene_GetNumScripts(&this->scene);
        bVar7 = bVar7 | this->f230[4];
        this->f230[4] = bVar7;
        bVar7 = bVar7 | this->f230[5];
        goto LAB_00029a3c;
      case 0xc:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8c28.op,uVar19);
        cVar10 = *(char *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_8c28);
        ppGVar20 = &this->state;
        uVar23 = 0;
        iVar17 = Inventory_Count(&(*ppGVar20)->inventory);
        if ('\0' < (char)iVar17) {
          do {
            pGVar13 = Inventory_GetObj(&(*ppGVar20)->inventory,uVar23);
            cVar8 = GameObj_GetId(pGVar13);
            if (cVar8 == cVar10) {
              Inventory_RemoveAt(&(*ppGVar20)->inventory,(byte)uVar23);
              break;
            }
            uVar23 = uVar23 + 1;
            iVar17 = Inventory_Count(&(*ppGVar20)->inventory);
          } while ((int)(uVar23 & 0xff) < (int)(char)iVar17);
        }
        break;
      case 0xd:
        Inventory_Clear(&this->state->inventory);
        break;
      case 0xe:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_86b8.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_86b8);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8a18.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8a18);
        Rec9ec_Set0((*ppGVar20)->scenes + uVar23,uVar18);
        break;
      case 0xf:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_84d8.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_84d8);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_89b8.op,uVar19);
        Rec9ec_Set4((*ppGVar20)->scenes + uVar23,*(undefined1 *)(puVar11 + 1));
        this_00 = &SStack_89b8;
        goto LAB_000296ac;
      case 0x10:
        this->dlgState = 0;
        Scene_SetKind(&this->scene,1);
        Game_DialogAdvance(this);
        break;
      case 0x11:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8da8.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8da8);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8d48.op,uVar19);
        bVar7 = *(byte *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_8d48);
        ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8ce8.op,uVar19);
        ScriptOp_Dtor(&SStack_8ce8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8c88.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8c88);
        pRVar15 = Rec9ec_GetObjState((*ppGVar20)->scenes + uVar23,(uint)bVar7);
        Rec9_SetVisible(pRVar15,uVar18);
        if (uVar23 == this->dlgTopic) {
          Game_Redraw(this);
        }
        break;
      case 0x12:
        uVar21 = 2;
        goto LAB_000295e0;
      case 0x13:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8718.op,uVar19);
        cVar10 = *(char *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_8718);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8ad8.op,uVar19);
        bVar7 = *(byte *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_8ad8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8418.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8418);
        ppGVar20 = &this->state;
        uVar23 = 0;
        iVar17 = Inventory_Count(&(*ppGVar20)->inventory);
        if ('\0' < (char)iVar17) {
          do {
            pGVar13 = Inventory_GetObj(&(*ppGVar20)->inventory,uVar23);
            cVar8 = GameObj_GetId(pGVar13);
            if (cVar8 == cVar10) {
              pGVar13 = Inventory_GetObj(&(*ppGVar20)->inventory,uVar23);
              GameObj_SetSubFlag(pGVar13,(uint)bVar7,uVar18);
              break;
            }
            uVar23 = uVar23 + 1;
            iVar17 = Inventory_Count(&(*ppGVar20)->inventory);
          } while ((int)(uVar23 & 0xff) < (int)(char)iVar17);
        }
        break;
      case 0x14:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8388.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8388);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_88f8.op,uVar19);
        uVar22 = (uint)*(byte *)((int)puVar11 + 0xb);
        ScriptOp_Dtor(&SStack_88f8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_85f8.op,uVar19);
        bVar7 = *(byte *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_85f8);
        ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8e68.op,uVar19);
        ScriptOp_Dtor(&SStack_8e68);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8e08.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8e08);
        pRVar14 = Rec9ec_GetRecE1((*ppGVar20)->scenes + uVar23,uVar22);
        pRVar15 = RecE1_GetObjState(pRVar14,(uint)bVar7);
        Rec9_SetVisible(pRVar15,uVar18);
        if ((uVar23 == this->dlgTopic) && (uVar22 == this->f230[0])) {
          puVar16 = (undefined1 *)Scene_GetZoom(&this->scene,uVar22);
          Game_DrawZoom(this,puVar16);
        }
        break;
      case 0x15:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8bc8.op,uVar19);
        bVar7 = *(byte *)((int)puVar11 + 0xb);
        ScriptOp_Dtor(&SStack_8bc8);
        this->f230[2] = 1;
        PostMessageW(g_hwnd,0x400,3,(uint)bVar7);
        goto LAB_00029300;
      case 0x16:
        uVar22 = 0;
        uVar23 = 1;
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,auStack_88c8,uVar19);
        cVar10 = *(char *)((int)puVar11 + 0x15);
        puVar16 = &stack0x00000608;
        while ((ScriptOp_Dtor((ScriptOp *)(puVar16 + -0x8ed0)), cVar10 != -1 &&
               ((uVar23 & 0xff) != 0))) {
          uVar23 = Inventory_Contains(&this->state->inventory,cVar10);
          uVar22 = uVar22 + 1;
          puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,auStack_8868,uVar19);
          cVar10 = *(char *)((int)puVar11 + (uVar22 & 0xff) + 0x15);
          puVar16 = &stack0x00000668;
        }
        if ((uVar23 & 0xff) == 0) {
          puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,auStack_87a8,uVar19);
          local_8f07 = *(undefined1 *)((int)puVar11 + 0xd);
          puVar16 = &stack0x00000728;
        }
        else {
          puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,auStack_8808,uVar19);
          local_8f07 = *(undefined1 *)(puVar11 + 3);
          puVar16 = &stack0x000006c8;
        }
        this_00 = (ScriptOp *)(puVar16 + -0x8ed0);
LAB_000296ac:
        ScriptOp_Dtor(this_00);
        break;
      case 0x17:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8b68.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8b68);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8b08.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8b08);
        Rec9ec_Set6((*ppGVar20)->scenes + uVar23,uVar18);
        break;
      case 0x18:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8aa8.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8aa8);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8a48.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8a48);
        Rec9ec_Set5((*ppGVar20)->scenes + uVar23,uVar18);
        break;
      case 0x19:
        FlushInputMessages();
        bVar6 = false;
        uVar21 = Scene_GetKind(&this->scene);
        Scene_SetKind(&this->scene,0);
        do {
          Game_BlinkButton5(this,3,100);
          WaitForPenDown((short *)&local_8f06,(short *)local_8efc);
          iVar17 = Game_HitTest(this,(uint)local_8f06,(uint)local_8efc[0]);
          if (iVar17 == 6) {
            bVar9 = TextList_PageDown(&this->desc);
            if (!bVar9) {
              bVar6 = true;
              goto LAB_00029594;
            }
            bVar7 = this->f22c + 1;
            this->f22c = bVar7;
            if (bVar7 <= this->f22d) goto LAB_000295b8;
            this->f22d = this->f22d + 1;
            TextList_DrawTyped(&this->desc,'\x01','\x01');
          }
          else {
LAB_00029594:
            if ((iVar17 == 5) && (bVar9 = TextList_PageUp(&this->desc), bVar9)) {
              this->f22c = this->f22c - 1;
LAB_000295b8:
              Game_ShowText(this,'\0');
            }
          }
          Game_ShowText(this,'\0');
        } while (!bVar6);
LAB_000295e0:
        Scene_SetKind(&this->scene,uVar21);
        break;
      case 0x1a:
        break;
      case 0x1b:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8748.op,uVar19);
        bVar7 = *(byte *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_8748);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_86e8.op,uVar19);
        cVar10 = *(char *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_86e8);
        ppGVar20 = &this->state;
        Inventory_SelectId(&(*ppGVar20)->inventory,cVar10,bVar7);
        if (bVar7 != 0) {
          uVar23 = Inventory_IndexOfId(&(*ppGVar20)->inventory,cVar10);
          Inventory_SetSelected(&(*ppGVar20)->inventory,(char)uVar23);
        }
        break;
      case 0x1c:
        iVar17 = Rec9ec_Get3(this->state->scenes + this->dlgTopic);
        Scene_SetCurStr(&this->scene,(char)iVar17);
        Scene_GetCurString(&this->scene,&local_8eac);
        Game_SetDescText(this,local_8eac);
        CString_CtorA(&local_8ea4,&g_emptyA);
        Game_SetStatusText(this,local_8ea4);
LAB_000297c8:
        bVar7 = 1;
LAB_000297cc:
        Game_ShowTextTyped(this,bVar7,'\x01');
        break;
      case 0x1d:
LAB_00029300:
        Script_Op1d(this);
        break;
      case 0x1e:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8688.op,uVar19);
        uVar5 = *(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8688);
        Sleep((uint)uVar5);
        FlushInputMessages();
        break;
      case 0x1f:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8628.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8628);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_85c8.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_85c8);
        Rec9ec_Set8((*ppGVar20)->scenes + uVar23,uVar18);
        break;
      case 0x20:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8568.op,uVar19);
        uVar23 = (uint)*(ushort *)((int)puVar11 + 6);
        ScriptOp_Dtor(&SStack_8568);
        ppGVar20 = &this->state;
        cVar10 = Rec9ec_Get2((*ppGVar20)->scenes + uVar23);
        if (cVar10 != '\0') {
          GameState_InitScene(*ppGVar20,uVar23);
        }
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8508.op,uVar19);
        uVar18 = *(undefined1 *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_8508);
        Rec9ec_Set7((*ppGVar20)->scenes + uVar23,uVar18);
        break;
      case 0x21:
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_84a8.op,uVar19);
        cVar10 = *(char *)((int)puVar11 + 10);
        ScriptOp_Dtor(&SStack_84a8);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_8448.op,uVar19);
        cVar8 = *(char *)(puVar11 + 3);
        ScriptOp_Dtor(&SStack_8448);
        puVar11 = ScriptOpList_Get((ScriptOpList *)&iStack_c,&SStack_83e8.op,uVar19);
        cVar3 = *(char *)(puVar11 + 5);
        ScriptOp_Dtor(&SStack_83e8);
        cVar10 = Book_GetFlag(&this->state->book,cVar10,cVar8);
        if (cVar10 == cVar3) {
          Game_BlinkButton1(this,2,0xa0);
        }
        break;
      case 0x22:
        Screen_FadeEffect2((Screen *)this,2,0x50);
        break;
      case 0x23:
        PostMessageW(g_hwnd,0x400,2,0);
        break;
      case 0x24:
        this->f230[4] = 1;
        break;
      case 0x25:
        bVar7 = 1;
LAB_00029a3c:
        this->f230[5] = bVar7;
      }
      uVar19 = uVar19 + 1;
    } while ((uVar19 & 0xff) < local_8e9c);
  }
  RecF8_Dtor(&RStack_8358);
  GameObj_Dtor(&GStack_8260);
  CString_Dtor(&local_8f04);
  CString_Dtor(&local_8f00);
  ScriptOpList_Dtor((ScriptOpList *)&iStack_c);
  return local_8f07;
}


// 00029aa4 ScriptOp_Dtor

void ScriptOp_Dtor(ScriptOp *this)

{
  ScriptOp *this_00;
  int iVar1;
  
  this_00 = this + 1;
  iVar1 = 3;
  do {
    this_00 = (ScriptOp *)(this_00[-1].str + 2);
    CString_Dtor((CString *)this_00);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// 00029acc Game_BlinkButton5

void Game_BlinkButton5(Game *this,byte param_2,short param_3)

{
  Button *this_00;
  byte bVar1;
  
  if (param_2 != 0) {
    this_00 = this->buttons + 5;
    bVar1 = 0;
    do {
      Button_SetState(this_00,2);
      Button_Draw(this_00);
      Sleep((int)param_3);
      Button_SetState(this_00,1);
      Button_Draw(this_00);
      Sleep((int)param_3);
      bVar1 = bVar1 + 1;
    } while (bVar1 < param_2);
  }
  return;
}


// 00029b38 Screen_FadeEffect2

void Screen_FadeEffect2(Screen *this,byte param_2,short param_3)

{
  int *this_00;
  byte bVar1;
  
  if (param_2 != 0) {
    this_00 = &this[3].w;
    bVar1 = 0;
    do {
      Button_SetState((Button *)this_00,2);
      Button_Draw((Button *)this_00);
      Sleep((int)param_3);
      Button_SetState((Button *)this_00,1);
      Button_Draw((Button *)this_00);
      Sleep((int)param_3);
      bVar1 = bVar1 + 1;
    } while (bVar1 < param_2);
  }
  return;
}


// 00029ba4 Game_BlinkButton1

void Game_BlinkButton1(Game *this,byte param_2,short param_3)

{
  Button *this_00;
  byte bVar1;
  
  if (param_2 != 0) {
    this_00 = this->buttons + 1;
    bVar1 = 0;
    do {
      Button_SetState(this_00,2);
      Button_Draw(this_00);
      Sleep((int)param_3);
      Button_SetState(this_00,1);
      Button_Draw(this_00);
      Sleep((int)param_3);
      bVar1 = bVar1 + 1;
    } while (bVar1 < param_2);
  }
  return;
}


// 00029c10 Game_SceneIntro

void Game_SceneIntro(Game *this)

{
  char cVar1;
  uint uVar2;
  ScriptOpList *pSVar3;
  
  this->f230[5] = 0;
  this->f230[4] = 0;
  cVar1 = Rec9ec_Get6(this->state->scenes + this->dlgTopic);
  if (cVar1 == '\0') {
    FlushInputMessages();
    Game_ShowTextTyped(this,1,'\x01');
  }
  else {
    uVar2 = Rec9ec_Get8(this->state->scenes + this->dlgTopic);
    pSVar3 = Scene_GetScripts(&this->scene);
    Script_RunList(this,(int)pSVar3,uVar2);
  }
  return;
}


// 00029cb0 Script_Op1d

void Script_Op1d(Game *this)

{
  this->f230[1] = 1;
  this->f230[0] = 0xff;
  return;
}


// 00029ccc Game_OnUserMsg3

void Game_OnUserMsg3(Game *this,uint param_2)

{
  undefined1 *puVar1;
  RecE1 *pRVar2;
  
  this->f230[0] = (byte)param_2;
  puVar1 = (undefined1 *)Scene_GetZoom(&this->scene,param_2);
  pRVar2 = Rec9ec_GetRecE1(this->state->scenes + this->dlgTopic,param_2);
  Game_RunZoom(this,(int)pRVar2,puVar1);
  Script_Op1d(this);
  return;
}


// 00029d34 DecompressImageIndirect

void DecompressImageIndirect(void)

{
                    /* WARNING: Could not recover jumptable at 0x00029d38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DecompressImageIndirect();
  return;
}


