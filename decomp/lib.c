// 00029d40 FUN_00029d40

undefined4 FUN_00029d40(int *param_1)

{
  int iVar1;
  int iVar2;
  int local_2c;
  int local_28;
  int local_24;
  int local_1c;
  int local_18;
  int local_14;
  
  local_2c = -1;
  local_1c = -1;
  local_28 = 0;
  local_24 = 0;
  local_18 = 0;
  local_14 = 0;
  if (g_bUseDST != 0) {
    if (DAT_002dc52c == 0) {
      crt_tzset(0,0);
    }
    iVar1 = param_1[5];
    if ((iVar1 != local_2c) || (iVar1 != local_1c)) {
      if (DAT_002dc518 != 0) {
        return 0;
      }
      if (DAT_002dc4c4 != 0) {
        return 0;
      }
      FUN_00029fd0(1,iVar1,DAT_002dc51a,DAT_002dc51e,DAT_002dc51c,0,DAT_002dc520,DAT_002dc522,
                   DAT_002dc524,DAT_002dc526,&local_2c);
      FUN_00029fd0(0,param_1[5],DAT_002dc4c6,DAT_002dc4ca,DAT_002dc4c8,0,DAT_002dc4cc,DAT_002dc4ce,
                   DAT_002dc4d0,DAT_002dc4d2,&local_1c);
    }
    iVar1 = param_1[7];
    if (local_28 < local_18) {
      if (iVar1 < local_28) {
        return 0;
      }
      if (local_18 < iVar1) {
        return 0;
      }
      if ((local_28 < iVar1) && (iVar1 < local_18)) {
        return 1;
      }
    }
    else {
      if (iVar1 < local_18) {
        return 1;
      }
      if (local_28 < iVar1) {
        return 1;
      }
      if ((local_18 < iVar1) && (iVar1 < local_28)) {
        return 0;
      }
    }
    iVar2 = ((param_1[2] * 0x3c + param_1[1]) * 0x3c + *param_1) * 1000;
    if (iVar1 == local_28) {
      if (local_24 <= iVar2) {
        return 1;
      }
    }
    else if (iVar2 < local_14) {
      return 1;
    }
  }
  return 0;
}


// 00029f2c crt_tzset

void crt_tzset(undefined4 *param_1,int *param_2)

{
  DWORD DVar1;
  int *extraout_r1;
  int *piVar2;
  bool bVar3;
  
  piVar2 = param_2;
  if (DAT_002dc52c == 0) {
    DVar1 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_002dc480);
    if (DVar1 == 0xffffffff) {
      return;
    }
    DAT_002dc52c = 1;
    piVar2 = extraout_r1;
  }
  bVar3 = param_1 == (undefined4 *)0x0;
  if (!bVar3) {
    piVar2 = (int *)(DAT_002dc480 * 0x3c);
    *param_1 = piVar2;
    bVar3 = DAT_002dc4c6 == 0;
  }
  if (!bVar3) {
    *param_1 = piVar2 + DAT_002dc4d4 * 0xf;
  }
  if (param_2 != (int *)0x0) {
    if (DAT_002dc51a != 0) {
      piVar2 = DAT_002dc528;
    }
    if (DAT_002dc51a != 0 && piVar2 != (int *)0x0) {
      *param_2 = ((int)piVar2 - DAT_002dc4d4) * 0x3c;
    }
    else {
      *param_2 = 0;
    }
  }
  return;
}


// 00029fd0 FUN_00029fd0

void FUN_00029fd0(int param_1,uint param_2,int param_3,int param_4,int param_5,undefined4 param_6,
                 int param_7,int param_8,int param_9,int param_10,uint *param_11)

{
  int iVar1;
  uint uVar2;
  int extraout_r1;
  undefined4 *puVar3;
  bool bVar4;
  int local_94 [2];
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_4c = 0x3a;
  local_48 = 0x59;
  local_44 = 0x77;
  local_40 = 0x96;
  local_3c = 0xb4;
  local_38 = 0xd3;
  local_34 = 0xf2;
  local_30 = 0x110;
  local_2c = 0x12f;
  local_28 = 0x14d;
  local_24 = 0x16c;
  local_84 = 0x3b;
  local_80 = 0x5a;
  local_7c = 0x78;
  local_78 = 0x97;
  local_74 = 0xb5;
  local_70 = 0xd4;
  local_6c = 0xf3;
  local_68 = 0x111;
  local_64 = 0x130;
  local_60 = 0x14e;
  local_54 = 0xffffffff;
  local_50 = 0x1e;
  local_8c = 0xffffffff;
  bVar4 = (param_2 & 3) != 0;
  local_88 = 0x1e;
  local_5c = 0x16d;
  crt_tzset(0,local_94);
  puVar3 = &local_8c;
  if (bVar4) {
    puVar3 = &local_54;
  }
  iVar1 = puVar3[param_3 + -1];
  __rt_sdiv(7,param_2 * 0x16d + ((int)(param_2 - 1) >> 2) + iVar1 + 1 + -0x63db);
  iVar1 = (param_4 * 7 - extraout_r1) + iVar1 + 1;
  if (param_5 < extraout_r1) {
    uVar2 = iVar1 + param_5;
  }
  else {
    uVar2 = (iVar1 + param_5) - 7;
  }
  if (param_4 == 5) {
    puVar3 = &local_8c;
    if (bVar4) {
      puVar3 = &local_54;
    }
    if ((int)puVar3[param_3] < (int)uVar2) {
      uVar2 = uVar2 - 7;
    }
  }
  param_11[1] = uVar2;
  iVar1 = (param_7 * 0x3c + param_8) * 0x3c;
  if (param_1 == 1) {
    uVar2 = (iVar1 + param_9) * 1000 + param_10;
  }
  else {
    uVar2 = (iVar1 + local_94[0] + param_9) * 1000 + param_10;
    if ((int)uVar2 < 0) {
      param_10 = 86399999;
    }
    param_11[2] = uVar2;
    if ((int)uVar2 < 0) {
      uVar2 = uVar2 + param_10;
    }
    else {
      if ((int)uVar2 < 86400000) goto LAB_0002a1fc;
      uVar2 = uVar2 + 0xfad9a401;
    }
  }
  param_11[2] = uVar2;
LAB_0002a1fc:
  *param_11 = param_2;
  return;
}


// 0002a214 FUN_0002a214

int FUN_0002a214(void)

{
  _SYSTEMTIME _Stack_14;
  
  GetSystemTime(&_Stack_14);
  return (((uint)_Stack_14.wHour * 0x3c + (uint)_Stack_14.wMinute) * 0x3c + (uint)_Stack_14.wSecond)
         * 1000 + (uint)_Stack_14.wMilliseconds;
}


// 0002a25c FUN_0002a25c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0002a25c(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  SYSTEMTIME *pSVar7;
  int local_44;
  int local_40;
  _FILETIME local_3c;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  SYSTEMTIME SStack_1c;
  
  if ((DAT_002dc478 & 1) == 0) {
    DAT_002dc478 = DAT_002dc478 | 1;
    puVar2 = (undefined4 *)FUN_0002a48c(&local_2c,0x7b2);
    local_34 = *(undefined1 *)puVar2;
    local_33 = *(undefined1 *)((int)puVar2 + 1);
    local_32 = *(undefined1 *)((int)puVar2 + 2);
    local_31 = *(undefined1 *)((int)puVar2 + 3);
    _DAT_002dc470 = *puVar2;
    local_30 = *(undefined1 *)(puVar2 + 1);
    local_2f = *(undefined1 *)((int)puVar2 + 5);
    local_2e = *(undefined1 *)((int)puVar2 + 6);
    local_2d = *(undefined1 *)((int)puVar2 + 7);
    _DAT_002dc474 = puVar2[1];
  }
  puVar3 = (undefined1 *)FUN_0002a410(&local_2c,param_1);
  iVar5 = 0x10;
  puVar2 = &local_2c;
  do {
    iVar6 = iVar5 + -1;
    *(undefined1 *)puVar2 = *puVar3;
    bVar1 = 0 < iVar5;
    puVar3 = puVar3 + 1;
    iVar5 = iVar6;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  } while (iVar6 != 0 && bVar1);
  iVar5 = 0x10;
  pSVar7 = &SStack_1c;
  puVar2 = &local_2c;
  do {
    iVar6 = iVar5 + -1;
    *(undefined1 *)&pSVar7->wYear = *(undefined1 *)puVar2;
    bVar1 = 0 < iVar5;
    iVar5 = iVar6;
    pSVar7 = (SYSTEMTIME *)((int)&pSVar7->wYear + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  } while (iVar6 != 0 && bVar1);
  uVar4 = FUN_0002a520(local_2c,local_28,local_24,local_20);
  *(undefined4 *)(param_1 + 0x1c) = uVar4;
  SystemTimeToFileTime(&SStack_1c,&local_3c);
  crt_tzset(&local_44,&local_40);
  iVar5 = FUN_00029d40(param_1);
  if (iVar5 != 0) {
    local_44 = local_44 + local_40;
  }
  iVar5 = FUN_0002a3d8(_DAT_002dc470,_DAT_002dc474,local_3c.dwLowDateTime,local_3c.dwHighDateTime);
  return iVar5 + local_44;
}


// 0002a3d8 FUN_0002a3d8

void FUN_0002a3d8(uint param_1,int param_2,uint param_3,int param_4)

{
  __rt_sdiv64by64(param_3 - param_1,param_4 - (param_2 + (uint)(param_3 < param_1)),10000000,0);
  return;
}


// 0002a410 FUN_0002a410

void FUN_0002a410(undefined1 *param_1,undefined2 *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  short local_18;
  short local_16;
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  
  local_18 = param_2[10] + 0x76c;
  local_16 = param_2[8] + 1;
  local_14 = param_2[0xc];
  local_12 = param_2[6];
  local_10 = param_2[4];
  local_e = param_2[2];
  local_c = *param_2;
  local_a = 0;
  iVar2 = 0x10;
  psVar4 = &local_18;
  do {
    iVar3 = iVar2 + -1;
    *param_1 = *(undefined1 *)psVar4;
    bVar1 = 0 < iVar2;
    iVar2 = iVar3;
    param_1 = param_1 + 1;
    psVar4 = (short *)((int)psVar4 + 1);
  } while (iVar3 != 0 && bVar1);
  return;
}


// 0002a48c FUN_0002a48c

undefined1 * FUN_0002a48c(undefined1 *param_1,WORD param_2)

{
  _FILETIME local_20;
  SYSTEMTIME local_18;
  
  local_18.wMonth = 1;
  local_18.wDayOfWeek = 1;
  local_18.wDay = 1;
  local_18.wHour = 0;
  local_18.wMinute = 0;
  local_18.wSecond = 0;
  local_18.wMilliseconds = 0;
  local_18.wYear = param_2;
  SystemTimeToFileTime(&local_18,&local_20);
  *param_1 = (undefined1)local_20.dwLowDateTime;
  param_1[1] = local_20.dwLowDateTime._1_1_;
  param_1[2] = local_20.dwLowDateTime._2_1_;
  param_1[3] = local_20.dwLowDateTime._3_1_;
  param_1[4] = (undefined1)local_20.dwHighDateTime;
  param_1[5] = local_20.dwHighDateTime._1_1_;
  param_1[6] = local_20.dwHighDateTime._2_1_;
  param_1[7] = local_20.dwHighDateTime._3_1_;
  return param_1;
}


// 0002a520 FUN_0002a520

void FUN_0002a520(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  _FILETIME local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 auStack_24 [8];
  SYSTEMTIME local_10;
  
  local_10._0_4_ = param_1;
  local_10._4_4_ = param_2;
  local_10._8_4_ = param_3;
  local_10._12_4_ = param_4;
  puVar1 = (undefined4 *)FUN_0002a48c(auStack_24,param_1 & 0xffff);
  local_2c = *puVar1;
  local_28 = puVar1[1];
  SystemTimeToFileTime(&local_10,&local_34);
  uVar2 = FUN_0002a3d8(local_2c,local_28,local_34.dwLowDateTime,local_34.dwHighDateTime);
  __rt_sdiv64by64((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),0x15180,0);
  return;
}


// 0002a5c8 FUN_0002a5c8

undefined1 * FUN_0002a5c8(uint *param_1)

{
  bool bVar1;
  undefined3 uVar2;
  undefined3 uVar3;
  undefined4 *puVar4;
  uint uVar5;
  BOOL BVar6;
  undefined1 *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined1 *puVar11;
  uint uVar12;
  int iVar13;
  undefined8 uVar14;
  uint local_98;
  uint local_94;
  FILETIME local_90;
  undefined4 local_88;
  undefined4 local_84;
  undefined1 auStack_80 [8];
  undefined1 auStack_78 [8];
  _SYSTEMTIME _Stack_70;
  undefined1 auStack_60 [40];
  undefined1 auStack_38 [36];
  
  uVar14 = CONCAT44(DAT_002dc464,DAT_002dc460);
  if ((DAT_002dc468 & 1) == 0) {
    DAT_002dc468 = DAT_002dc468 | 1;
    puVar4 = (undefined4 *)FUN_0002a48c(auStack_80,0x7b2);
    local_88 = *puVar4;
    local_84 = puVar4[1];
    puVar4 = (undefined4 *)FUN_0002a48c(auStack_78,0x641);
    uVar14 = FUN_0002a3d8(*puVar4,puVar4[1],local_88,local_84);
  }
  DAT_002dc464 = (int)((ulonglong)uVar14 >> 0x20);
  DAT_002dc460 = (uint)uVar14;
  memset(&DAT_002dc438,0,0x24);
  crt_tzset(&local_98,&local_94);
  uVar10 = *param_1 - local_98;
  uVar5 = uVar10 + DAT_002dc460;
  uVar12 = uVar5 * 10000000;
  iVar13 = ((DAT_002dc464 - (((int)local_98 >> 0x1f) + (uint)(*param_1 < local_98))) +
           (uint)CARRY4(uVar10,DAT_002dc460)) * 10000000 +
           (int)((ulonglong)uVar5 * 10000000 >> 0x20);
  puVar4 = (undefined4 *)FUN_0002a8e4(auStack_78,uVar12,iVar13);
  uVar2 = *(undefined3 *)puVar4;
  local_90.dwLowDateTime._3_1_ = *(undefined1 *)((int)puVar4 + 3);
  uVar3 = *(undefined3 *)(puVar4 + 1);
  local_90.dwHighDateTime._3_1_ = *(undefined1 *)((int)puVar4 + 7);
  local_88._0_1_ = (undefined1)uVar2;
  local_90.dwLowDateTime._0_1_ = (undefined1)local_88;
  local_88._1_1_ = (undefined1)((uint3)uVar2 >> 8);
  local_90.dwLowDateTime._1_1_ = local_88._1_1_;
  local_88._2_1_ = (undefined1)((uint3)uVar2 >> 0x10);
  local_90.dwLowDateTime._2_1_ = local_88._2_1_;
  local_84._0_1_ = (undefined1)uVar3;
  local_90.dwHighDateTime._0_1_ = (undefined1)local_84;
  local_84._1_1_ = (undefined1)((uint3)uVar3 >> 8);
  local_90.dwHighDateTime._1_1_ = local_84._1_1_;
  local_84._2_1_ = (undefined1)((uint3)uVar3 >> 0x10);
  local_90.dwHighDateTime._2_1_ = local_84._2_1_;
  local_88 = *puVar4;
  local_84 = puVar4[1];
  BVar6 = FileTimeToSystemTime(&local_90,&_Stack_70);
  if (BVar6 != 0) {
    puVar7 = (undefined1 *)FUN_0002a940(auStack_60,&_Stack_70);
    iVar8 = 0x24;
    puVar11 = auStack_60;
    do {
      iVar9 = iVar8 + -1;
      *puVar11 = *puVar7;
      bVar1 = 0 < iVar8;
      puVar7 = puVar7 + 1;
      iVar8 = iVar9;
      puVar11 = puVar11 + 1;
    } while (iVar9 != 0 && bVar1);
    iVar8 = 0x24;
    puVar7 = auStack_38;
    puVar11 = auStack_60;
    do {
      iVar9 = iVar8 + -1;
      *puVar7 = *puVar11;
      bVar1 = 0 < iVar8;
      iVar8 = iVar9;
      puVar7 = puVar7 + 1;
      puVar11 = puVar11 + 1;
    } while (iVar9 != 0 && bVar1);
    iVar8 = FUN_00029d40(auStack_38);
    if (iVar8 != 0) {
      puVar4 = (undefined4 *)
               FUN_0002a8e4(auStack_78,uVar12 + local_94 * -10000000,
                            iVar13 - (((int)local_94 >> 0x1f) * 10000000 +
                                      (int)((ulonglong)local_94 * 10000000 >> 0x20) +
                                     (uint)(uVar12 < local_94 * 10000000)));
      uVar2 = *(undefined3 *)puVar4;
      local_90.dwLowDateTime._3_1_ = *(undefined1 *)((int)puVar4 + 3);
      uVar3 = *(undefined3 *)(puVar4 + 1);
      local_90.dwHighDateTime._3_1_ = *(undefined1 *)((int)puVar4 + 7);
      local_88._0_1_ = (undefined1)uVar2;
      local_90.dwLowDateTime._0_1_ = (undefined1)local_88;
      local_88._1_1_ = (undefined1)((uint3)uVar2 >> 8);
      local_90.dwLowDateTime._1_1_ = local_88._1_1_;
      local_88._2_1_ = (undefined1)((uint3)uVar2 >> 0x10);
      local_90.dwLowDateTime._2_1_ = local_88._2_1_;
      local_84._0_1_ = (undefined1)uVar3;
      local_90.dwHighDateTime._0_1_ = (undefined1)local_84;
      local_84._1_1_ = (undefined1)((uint3)uVar3 >> 8);
      local_90.dwHighDateTime._1_1_ = local_84._1_1_;
      local_84._2_1_ = (undefined1)((uint3)uVar3 >> 0x10);
      local_90.dwHighDateTime._2_1_ = local_84._2_1_;
      local_88 = *puVar4;
      local_84 = puVar4[1];
      FileTimeToSystemTime(&local_90,&_Stack_70);
    }
    puVar7 = (undefined1 *)FUN_0002a940(auStack_60,&_Stack_70);
    iVar13 = 0x24;
    puVar11 = auStack_38;
    do {
      iVar8 = iVar13 + -1;
      *puVar11 = *puVar7;
      bVar1 = 0 < iVar13;
      puVar7 = puVar7 + 1;
      iVar13 = iVar8;
      puVar11 = puVar11 + 1;
    } while (iVar8 != 0 && bVar1);
    iVar13 = 0x24;
    puVar7 = &DAT_002dc438;
    puVar11 = auStack_38;
    do {
      iVar8 = iVar13 + -1;
      *puVar7 = *puVar11;
      bVar1 = 0 < iVar13;
      iVar13 = iVar8;
      puVar7 = puVar7 + 1;
      puVar11 = puVar11 + 1;
    } while (iVar8 != 0 && bVar1);
  }
  return &DAT_002dc438;
}


// 0002a8e4 FUN_0002a8e4

void FUN_0002a8e4(undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 local_8;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 uStack_5;
  undefined1 local_4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  undefined1 uStack_1;
  
  local_8 = (undefined1)param_2;
  *param_1 = local_8;
  uStack_7 = (undefined1)((uint)param_2 >> 8);
  param_1[1] = uStack_7;
  uStack_6 = (undefined1)((uint)param_2 >> 0x10);
  param_1[2] = uStack_6;
  uStack_5 = (undefined1)((uint)param_2 >> 0x18);
  param_1[3] = uStack_5;
  local_4 = (undefined1)param_3;
  param_1[4] = local_4;
  uStack_3 = (undefined1)((uint)param_3 >> 8);
  param_1[5] = uStack_3;
  uStack_2 = (undefined1)((uint)param_3 >> 0x10);
  param_1[6] = uStack_2;
  uStack_1 = (undefined1)((uint)param_3 >> 0x18);
  param_1[7] = uStack_1;
  return;
}


// 0002a940 FUN_0002a940

undefined1 * FUN_0002a940(undefined1 *param_1,ushort *param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  uint *puVar5;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  int local_1c;
  uint local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  local_1c = *param_2 - 0x76c;
  local_20 = param_2[1] - 1;
  local_18 = (uint)param_2[2];
  local_24 = (uint)param_2[3];
  local_14 = FUN_0002a520(*(undefined4 *)param_2,*(undefined4 *)(param_2 + 2),
                          *(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 6));
  local_28 = (uint)param_2[4];
  local_2c = (uint)param_2[5];
  local_30 = (uint)param_2[6];
  local_10 = 0;
  iVar2 = 0x24;
  puVar4 = param_1;
  puVar5 = &local_30;
  do {
    iVar3 = iVar2 + -1;
    *puVar4 = *(undefined1 *)puVar5;
    bVar1 = 0 < iVar2;
    iVar2 = iVar3;
    puVar4 = puVar4 + 1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while (iVar3 != 0 && bVar1);
  return param_1;
}


// 0002aa00 time

void time(void)

{
  bool bVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  _SYSTEMTIME _Stack_60;
  undefined1 auStack_50 [40];
  undefined1 auStack_28 [36];
  
  GetLocalTime(&_Stack_60);
  puVar2 = (undefined1 *)FUN_0002a940(auStack_50,&_Stack_60);
  iVar3 = 0x24;
  puVar5 = auStack_50;
  do {
    iVar4 = iVar3 + -1;
    *puVar5 = *puVar2;
    bVar1 = 0 < iVar3;
    puVar2 = puVar2 + 1;
    iVar3 = iVar4;
    puVar5 = puVar5 + 1;
  } while (iVar4 != 0 && bVar1);
  iVar3 = 0x24;
  puVar2 = auStack_28;
  puVar5 = auStack_50;
  do {
    iVar4 = iVar3 + -1;
    *puVar2 = *puVar5;
    bVar1 = 0 < iVar3;
    iVar3 = iVar4;
    puVar2 = puVar2 + 1;
    puVar5 = puVar5 + 1;
  } while (iVar4 != 0 && bVar1);
  FUN_0002a25c(auStack_28);
  return;
}


// 0002aa60 FUN_0002aa60

int FUN_0002aa60(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x28) < *(int *)(param_1 + 0x24) + 2U) {
    FUN_000358ec();
  }
  puVar1 = *(undefined1 **)(param_1 + 0x24);
  *puVar1 = (char)param_2;
  puVar1[1] = (char)((uint)param_2 >> 8);
  *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 2;
  return param_1;
}


// 0002aaa4 FUN_0002aaa4

int FUN_0002aaa4(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  
  if (*(uint *)(param_1 + 0x28) < *(int *)(param_1 + 0x24) + 4U) {
    FUN_000358ec();
  }
  puVar1 = *(undefined1 **)(param_1 + 0x24);
  *puVar1 = (char)param_2;
  puVar1[1] = (char)((uint)param_2 >> 8);
  puVar1[2] = (char)((uint)param_2 >> 0x10);
  puVar1[3] = (char)((uint)param_2 >> 0x18);
  *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 4;
  return param_1;
}


// 0002aaf8 FUN_0002aaf8

int FUN_0002aaf8(int param_1,undefined2 *param_2)

{
  if (*(uint *)(param_1 + 0x28) < *(int *)(param_1 + 0x24) + 2U) {
    FUN_000359e4(param_1,(*(int *)(param_1 + 0x24) - *(uint *)(param_1 + 0x28)) + 2);
  }
  *param_2 = **(undefined2 **)(param_1 + 0x24);
  *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 2;
  return param_1;
}


// 0002ab4c FUN_0002ab4c

int FUN_0002ab4c(int param_1,undefined4 *param_2)

{
  if (*(uint *)(param_1 + 0x28) < *(int *)(param_1 + 0x24) + 4U) {
    FUN_000359e4(param_1,(*(int *)(param_1 + 0x24) - *(uint *)(param_1 + 0x28)) + 4);
  }
  *param_2 = **(undefined4 **)(param_1 + 0x24);
  *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + 4;
  return param_1;
}


// 0002abb4 FUN_0002abb4

undefined1 * FUN_0002abb4(undefined1 *param_1,uint param_2)

{
  *param_1 = 0x88;
  param_1[1] = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002abf4 FUN_0002abf4

undefined1 * FUN_0002abf4(undefined1 *param_1,uint param_2)

{
  *param_1 = 0xa0;
  param_1[1] = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002ac34 FUN_0002ac34

void FUN_0002ac34(uint param_1,SIZE_T param_2)

{
  UINT uFlags;
  
  uFlags = 0;
  if ((param_1 & 0x40) != 0) {
    uFlags = 0x40;
  }
  if ((param_1 & 2) != 0) {
    uFlags = uFlags | 2;
  }
  LocalAlloc(uFlags,param_2);
  return;
}


// 0002ac50 FUN_0002ac50

void FUN_0002ac50(HLOCAL param_1,SIZE_T param_2,uint param_3)

{
  UINT uFlags;
  
  uFlags = 0;
  if ((param_3 & 0x40) != 0) {
    uFlags = 0x40;
  }
  if ((param_3 & 2) != 0) {
    uFlags = uFlags | 2;
  }
  LocalReAlloc(param_1,param_2,uFlags);
  return;
}


// 0002ac74 FUN_0002ac74

undefined1 * FUN_0002ac74(undefined1 *param_1,uint param_2)

{
  *param_1 = 0xe0;
  param_1[1] = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  CString_Dtor((CString *)(param_1 + 0xc));
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002acc0 FUN_0002acc0

undefined4 FUN_0002acc0(void)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = (int *)FUN_0002f1d0();
  if (piVar1 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(*piVar1 + 0x6c))();
  }
  return uVar2;
}


// 0002acec FUN_0002acec

HMODULE FUN_0002acec(void)

{
  LPCWSTR lpModuleName;
  HMODULE pHVar1;
  
  lpModuleName = (LPCWSTR)FUN_0002adfc();
  pHVar1 = GetModuleHandleW(lpModuleName);
  free(lpModuleName);
  return pHVar1;
}


// 0002ad10 FUN_0002ad10

void FUN_0002ad10(int param_1)

{
  if (*(int *)(param_1 + 0x24) == 0) {
    GetParent(*(HWND *)(param_1 + 0x1c));
  }
  FUN_0002ffec();
  return;
}


// 0002ad4c FUN_0002ad4c

void * FUN_0002ad4c(void *param_1,uint param_2)

{
  FUN_0002ad70();
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002ad70 FUN_0002ad70

void FUN_0002ad70(undefined1 *param_1)

{
  *param_1 = 0x48;
  param_1[1] = 6;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_00033988(param_1);
  FUN_0002e158(param_1 + 0x20);
  FUN_0002e158(param_1 + 4);
  return;
}


// 0002adb8 FUN_0002adb8

short * FUN_0002adb8(short *param_1,char *param_2)

{
  short *psVar1;
  
  psVar1 = param_1;
  for (; *param_2 != '\0'; param_2 = param_2 + 1) {
    *psVar1 = (short)*param_2;
    psVar1 = psVar1 + 1;
  }
  *psVar1 = 0;
  return param_1;
}


// 0002adfc FUN_0002adfc

undefined4 FUN_0002adfc(char *param_1)

{
  size_t sVar1;
  undefined4 uVar2;
  
  sVar1 = strlen(param_1);
  uVar2 = operator_new((sVar1 + 1) * 2);
  if (param_1 == (char *)0x0) {
    SetLastError(8);
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0002adb8(uVar2,param_1);
  }
  return uVar2;
}


// 0002ae38 FUN_0002ae38

void FUN_0002ae38(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_20c;
  undefined1 local_20b;
  undefined1 auStack_20a [510];
  
  local_20c = g_emptyW;
  local_20b = DAT_002dc3f5;
  memset(auStack_20a,0,0x1fe);
  FUN_0002adb8(&local_20c,param_2);
  GetProcAddressW(param_1,&local_20c);
  return;
}


// 0002ae98 FUN_0002ae98

undefined4 FUN_0002ae98(undefined4 param_1,undefined4 param_2,LPRECT param_3)

{
  int yBottom;
  int xRight;
  
  yBottom = FUN_0002b30c(1);
  xRight = FUN_0002b30c(0);
  SetRect(param_3,0,0,xRight,yBottom);
  return 1;
}


// 0002aedc FUN_0002aedc

void FUN_0002aedc(undefined4 param_1)

{
  undefined1 local_210;
  undefined1 local_20f;
  undefined1 auStack_20e [518];
  
  local_210 = g_emptyW;
  local_20f = DAT_002dc3f5;
  memset(auStack_20e,0,0x206);
  FUN_0002adb8(&local_210,param_1);
  LoadLibraryW((LPCWSTR)&local_210);
  return;
}


// 0002af34 AfxWinHelp_PegHelp

BOOL AfxWinHelp_PegHelp(undefined4 param_1,wchar_t *param_2)

{
  BOOL BVar1;
  _PROCESS_INFORMATION _Stack_428;
  undefined1 local_418;
  undefined1 local_417;
  undefined1 auStack_416 [1038];
  
  local_418 = g_emptyW;
  local_417 = DAT_002dc3f5;
  memset(auStack_416,0,0x40e);
  if (param_2 == (wchar_t *)0x0) {
    BVar1 = 0;
  }
  else {
    wcscpy((wchar_t *)&local_418,u_file__0004401c);
    wcscat((wchar_t *)&local_418,param_2);
    BVar1 = CreateProcessW(u_PegHelp_exe_00044004,(LPWSTR)&local_418,(LPSECURITY_ATTRIBUTES)0x0,
                           (LPSECURITY_ATTRIBUTES)0x0,0,0,(LPVOID)0x0,(LPCWSTR)0x0,
                           (LPSTARTUPINFOW)0x0,&_Stack_428);
  }
  return BVar1;
}


// 0002afe8 FUN_0002afe8

UINT FUN_0002afe8(HMENU param_1,UINT param_2)

{
  UINT local_38 [4];
  UINT local_28;
  
  memset(local_38,0,0x2c);
  local_38[0] = 0x2c;
  local_38[1] = 2;
  GetMenuItemInfoW(param_1,param_2,1,(LPMENUITEMINFOW)local_38);
  return local_28;
}


// 0002b038 FUN_0002b038

undefined4 FUN_0002b038(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0002ffec();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0x20);
  }
  return uVar2;
}


// 0002b050 FUN_0002b050

bool FUN_0002b050(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0002ffec();
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x20) = param_2;
  }
  return iVar1 != 0;
}


// 0002b070 FUN_0002b070

UINT FUN_0002b070(HMENU param_1,UINT param_2,uint param_3)

{
  UINT local_3c [3];
  UINT local_30;
  
  memset(local_3c,0,0x2c);
  local_3c[0] = 0x2c;
  local_3c[1] = 2;
  GetMenuItemInfoW(param_1,param_2,(uint)((param_3 & 0x400) != 0),(LPMENUITEMINFOW)local_3c);
  return local_30;
}


// 0002b0cc FUN_0002b0cc

void FUN_0002b0cc(HMENU param_1,UINT param_2,uint param_3,UINT_PTR param_4,LPCWSTR param_5)

{
  int iVar1;
  UINT UVar2;
  BOOL BVar3;
  UINT uPosition;
  
  uPosition = param_2;
  if ((param_3 & 0x400) != 0x400) {
    iVar1 = FUN_0002b16c();
    for (uPosition = 0;
        (UVar2 = FUN_0002afe8(param_1,uPosition), param_2 != UVar2 && ((int)uPosition < iVar1));
        uPosition = uPosition + 1) {
    }
    param_3 = param_3 | 0x400;
  }
  BVar3 = DeleteMenu(param_1,uPosition,param_3);
  if (BVar3 != 0) {
    InsertMenuW(param_1,uPosition,param_3,param_4,param_5);
  }
  return;
}


// 0002b16c FUN_0002b16c

int FUN_0002b16c(HMENU param_1)

{
  BOOL BVar1;
  UINT item;
  int iVar2;
  UINT local_3c [11];
  
  memset(local_3c,0,0x2c);
  local_3c[0] = 0x2c;
  iVar2 = 0;
  item = 0;
  do {
    BVar1 = GetMenuItemInfoW(param_1,item,1,(LPMENUITEMINFOW)local_3c);
    if (BVar1 == 0) {
      return iVar2;
    }
    item = item + 1;
    iVar2 = iVar2 + 1;
  } while ((int)item < 0x100);
  return iVar2;
}


// 0002b228 FUN_0002b228

void FUN_0002b228(HWND param_1,int param_2,int param_3)

{
  HWND hWnd;
  tagRECT local_28;
  
  for (hWnd = GetWindow(param_1,5); hWnd != (HWND)0x0; hWnd = GetWindow(hWnd,2)) {
    GetWindowRect(hWnd,&local_28);
    ScreenToClient(param_1,(LPPOINT)&local_28);
    SetWindowPos(hWnd,(HWND)0x0,local_28.left - param_2,local_28.top - param_3,0,0,0x15);
  }
  return;
}


// 0002b2b0 FUN_0002b2b0

bool FUN_0002b2b0(HWND param_1,int param_2,int param_3)

{
  uint uVar1;
  LONG LVar2;
  uint uVar3;
  
  uVar1 = GetWindowLongW(param_1,-0x10);
  uVar3 = 0x100000;
  if (param_3 == 0) {
    if (param_2 != 0) {
      uVar3 = 0x200000;
    }
    uVar3 = uVar1 & ~uVar3;
  }
  else {
    if (param_2 != 0) {
      uVar3 = 0x200000;
    }
    uVar3 = uVar3 | uVar1;
  }
  LVar2 = SetWindowLongW(param_1,-0x10,uVar3);
  return LVar2 != 0;
}


// 0002b30c FUN_0002b30c

void FUN_0002b30c(int param_1)

{
  if (param_1 != 0x2a) {
    GetSystemMetrics(param_1);
  }
  return;
}


// 0002b320 FUN_0002b320

void FUN_0002b320(HWND param_1)

{
  int iVar1;
  WCHAR aWStack_64 [4];
  tagRECT local_5c;
  tagRECT local_4c;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  HWND local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  LONG local_1c;
  LPWSTR local_18;
  LPWSTR local_14;
  LONG local_10;
  
  iVar1 = GetWindowTextW(param_1,aWStack_64,1);
  local_18 = (LPWSTR)operator_new((iVar1 + 1) * 2);
  if (local_18 != (LPWSTR)0x0) {
    GetWindowTextW(param_1,local_18,iVar1);
    local_14 = (LPWSTR)operator_new(0x80);
    GetClassNameW(param_1,local_14,0x40);
    local_1c = GetWindowLongW(param_1,-0x10);
    local_10 = GetWindowLongW(param_1,-0x14);
    local_30 = GetParent(param_1);
    iVar1 = FUN_0003f4f4();
    local_38 = *(undefined4 *)(iVar1 + 8);
    GetWindowRect(param_1,&local_5c);
    if (local_30 != (HWND)0x0) {
      GetWindowRect(local_30,&local_4c);
      OffsetRect(&local_5c,-local_4c.left,-local_4c.right);
    }
    local_28 = local_5c.right - local_5c.left;
    local_20 = local_5c.left;
    local_24 = local_5c.top;
    local_2c = local_5c.bottom - local_5c.top;
    local_34 = 0;
    local_3c = 0;
    SendMessageW(param_1,1,0,(LPARAM)&local_3c);
    free(local_18);
    free(local_14);
  }
  return;
}


// 0002b44c FUN_0002b44c

void FUN_0002b44c(HWND param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  HWND pHVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar1 = FUN_0003f170();
  iVar5 = *(int *)(iVar1 + 0x14);
  if (*(int *)(iVar1 + 0x1c) != 0) {
    pHVar2 = GetParent(param_1);
    uVar4 = *(undefined4 *)(iVar1 + 0x14);
    *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(iVar1 + 0x1c);
    FUN_0003016c(3,pHVar2,0);
    *(undefined4 *)(iVar1 + 0x14) = uVar4;
    (**(code **)(**(int **)(iVar1 + 0x1c) + 0xb8))();
    *(undefined4 *)(iVar1 + 0x1c) = 0;
  }
  SetWindowLongW(param_1,-4,0x2ce4c);
  iVar1 = FUN_0002ed1c(iVar5,&CCommonDialog::classCCommonDialog);
  if (iVar1 == 0) {
    SetWindowLongW(param_1,4,0x34080);
  }
  FUN_0003016c(3,param_1,0);
  pcVar3 = (code *)FUN_00030160();
  if ((iVar5 != 0) && (iVar1 = FUN_0002ed1c(iVar5,&CFormView::classCFormView), iVar1 != 0)) {
    FUN_0002b320(param_1);
  }
  (*pcVar3)(param_1,param_2,param_3,param_4);
  return;
}


// 0002b550 FUN_0002b550

undefined4 FUN_0002b550(int param_1)

{
  WNDPROC pWVar1;
  int iVar2;
  BOOL BVar3;
  int iVar4;
  size_t sVar5;
  size_t sVar6;
  tagWNDCLASSW tStack_84;
  undefined1 auStack_5c [56];
  
  if (*(uint *)(param_1 + 8) >> 0x10 != 0) {
    *(undefined4 *)(param_1 + 8) = 0;
  }
  iVar2 = FUN_0003f170();
  BVar3 = GetClassInfoW(*(HINSTANCE *)(param_1 + 4),*(LPCWSTR *)(param_1 + 0x28),&tStack_84);
  if (BVar3 != 0) {
    iVar4 = _wcsnicmp(*(wchar_t **)(param_1 + 0x28),(wchar_t *)&DAT_00044034,3);
    if (iVar4 == 0) {
      *(code **)(iVar2 + 0x18) = DefWindowProcW;
      return 1;
    }
    FUN_0002f060(auStack_5c);
    iVar4 = setjmp(auStack_5c);
    if (iVar4 == 0) {
      sVar5 = wcslen(*(wchar_t **)(param_1 + 0x28));
      sVar6 = wcslen(u_WCE__00044028);
      tStack_84.lpszClassName = (LPCWSTR)operator_new((sVar5 + sVar6 + 1) * 2);
      FUN_0002f0c0();
      if (tStack_84.lpszClassName != (wchar_t *)0x0) {
        wcscpy(tStack_84.lpszClassName,u_WCE__00044028);
        wcscat(tStack_84.lpszClassName,*(wchar_t **)(param_1 + 0x28));
        pWVar1 = tStack_84.lpfnWndProc;
        tStack_84.lpfnWndProc = FUN_0002b684;
        iVar4 = FUN_00030ba4(&tStack_84);
        if (iVar4 != 0) {
          *(WNDPROC *)(iVar2 + 0x18) = pWVar1;
          *(LPCWSTR *)(param_1 + 0x28) = tStack_84.lpszClassName;
          return 1;
        }
        free(tStack_84.lpszClassName);
      }
    }
    else {
      FUN_0002f0c0();
    }
  }
  return 0;
}


// 0002b684 FUN_0002b684

void FUN_0002b684(HWND param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  pcVar2 = (code *)FUN_00030160();
  SetWindowLongW(param_1,-4,*(LONG *)(iVar1 + 0x18));
  *(undefined4 *)(iVar1 + 0x18) = 0;
  FUN_0003016c(3,param_1,0);
  (*pcVar2)(param_1,param_2,param_3,param_4);
  return;
}


// 0002b6fc FUN_0002b6fc

void FUN_0002b6fc(int param_1,HWND param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = FUN_0003f170();
  if (*(int *)(iVar1 + 0x14) != 0) {
    if (param_2 == (HWND)0x0) {
      *(undefined4 *)(iVar1 + 0x14) = 0;
      *(undefined4 *)(iVar1 + 0x18) = 0;
    }
    else {
      SetWindowLongW(param_2,-4,*(LONG *)(iVar1 + 0x18));
      *(undefined4 *)(iVar1 + 0x18) = 0;
      FUN_0003016c(3,param_2,0);
    }
  }
  iVar1 = _wcsnicmp(*(wchar_t **)(param_1 + 0x28),u_WCE__00044028,4);
  if (iVar1 == 0) {
    free(*(void **)(param_1 + 0x28));
  }
  if (param_2 != (HWND)0x0 && param_3 >> 0x10 != 0) {
    FUN_0002b050(param_2,param_3);
  }
  return;
}


// 0002b7a0 FUN_0002b7a0

undefined1 * FUN_0002b7a0(undefined1 *param_1,uint param_2)

{
  *param_1 = 0x78;
  param_1[1] = 7;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_00033f6c(param_1);
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002b7ec FUN_0002b7ec

undefined1 * FUN_0002b7ec(undefined1 *param_1,uint param_2)

{
  *param_1 = 0x58;
  param_1[1] = 9;
  param_1[2] = 4;
  param_1[3] = 0;
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002b82c FUN_0002b82c

undefined1 * FUN_0002b82c(undefined1 *param_1,uint param_2)

{
  *param_1 = 0x70;
  param_1[1] = 9;
  param_1[2] = 4;
  param_1[3] = 0;
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002b86c FUN_0002b86c

undefined1 * FUN_0002b86c(undefined1 *param_1,uint param_2)

{
  *param_1 = 0x88;
  param_1[1] = 9;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_000364e4(param_1);
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 0002b8c0 FUN_0002b8c0

void FUN_0002b8c0(int param_1,int param_2,int param_3,UINT param_4,RECT *param_5,LPCWSTR param_6,
                 UINT param_7,INT *param_8)

{
  ExtTextOutW(*(HDC *)(param_1 + 4),param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}


// 0002b8f8 FUN_0002b8f8

void FUN_0002b8f8(int param_1,LPCWSTR param_2,int param_3,LPRECT param_4,UINT param_5)

{
  DrawTextW(*(HDC *)(param_1 + 4),param_2,param_3,param_4,param_5);
  return;
}


// 0002b948 FUN_0002b948

void FUN_0002b948(int param_1)

{
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x474,0,0);
  FUN_0002ffec();
  return;
}


// 0002b9a4 FUN_0002b9a4

void FUN_0002b9a4(int param_1,WPARAM param_2,LPARAM param_3)

{
  BOOL BVar1;
  int iVar2;
  
  BVar1 = IsWindowVisible(*(HWND *)(param_1 + 0x1c));
  if (BVar1 == 0) {
    FUN_0002ffec(*(undefined4 *)(param_1 + 0x7c));
    iVar2 = FUN_00031b24();
    SendMessageW(*(HWND *)(iVar2 + 0x1c),0x1a,param_2,param_3);
  }
  else {
    FUN_00034d88(param_1,param_2,param_3);
  }
  return;
}


// 0002b9fc FUN_0002b9fc

void FUN_0002b9fc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  LRESULT LVar3;
  BOOL BVar4;
  UINT Msg;
  WPARAM wParam;
  
  iVar1 = FUN_00032a4c(param_1,1);
  if (iVar1 == 0) {
    return;
  }
  *(undefined4 *)(param_1 + 0x84) = 0x108;
  uVar2 = FUN_00033a44(param_1,0xe500);
  FUN_00033bec(uVar2,*(undefined4 *)(param_1 + 0x88),*(undefined2 *)(param_1 + 0x90));
  if (*(int *)(param_1 + 0x58) == 0x700b) {
    uVar2 = FUN_00033a44(param_1,0xe501);
    FUN_00033bec(uVar2,*(undefined4 *)(param_1 + 0x8c),*(undefined2 *)(param_1 + 0x92));
  }
  iVar1 = FUN_00033a44(param_1,0xe502);
  LVar3 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0xf0,0,0);
  if (0 < LVar3) {
    *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 2;
  }
  iVar1 = FUN_00033a44(param_1,0xe503);
  LVar3 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0xf0,0,0);
  if (0 < LVar3) {
    *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 4;
  }
  *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 1;
  if ((*(int *)(param_1 + 0x58) == 0x700a) && (iVar1 = FUN_00033a7c(param_1,0xe505), iVar1 != 0)) {
    *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) & 0xfffffffe;
  }
  *(undefined4 *)(param_1 + 0xa0) = 1;
  iVar1 = FUN_00033a44(param_1,0xe508);
  if ((iVar1 != 0) && (BVar4 = IsWindowVisible(*(HWND *)(iVar1 + 0x1c)), BVar4 != 0)) {
    iVar1 = FUN_00033d98(iVar1);
    wParam = 0;
    if (iVar1 != 0) goto LAB_0002bb54;
  }
  wParam = 1;
LAB_0002bb54:
  PostMessageW(*(HWND *)(param_1 + 0x1c),0x6bc,wParam,0);
  Msg = RegisterWindowMessageW(u_commdlg_FindReplace_0004439c);
  SendMessageW(*(HWND *)(param_1 + 0x7c),Msg,0,param_1 + 0x78);
  return;
}


// 0002bb8c FUN_0002bb8c

undefined4 FUN_0002bb8c(int param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 auStack_34 [16];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  FUN_00034c84();
  iVar2 = operator_new(0xdc);
  if (iVar2 == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = (int *)FUN_00037fb8();
  }
  *(int **)(param_1 + 0x48) = piVar3;
  if (piVar3 != (int *)0x0) {
    iVar7 = *piVar3;
    local_24 = 0xe800;
    local_20 = 0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    iVar2 = 0x10;
    puVar5 = auStack_34;
    puVar6 = &local_20;
    do {
      iVar4 = iVar2 + -1;
      *puVar5 = *(undefined1 *)puVar6;
      bVar1 = 0 < iVar2;
      iVar2 = iVar4;
      puVar5 = puVar5 + 1;
      puVar6 = (undefined4 *)((int)puVar6 + 1);
    } while (iVar4 != 0 && bVar1);
    (**(code **)(iVar7 + 0xd8))(piVar3,param_1,0x800,0x50002000);
  }
  return 1;
}


// 0002bc2c FUN_0002bc2c

void FUN_0002bc2c(int param_1)

{
  int iVar1;
  
  FUN_00033a44(param_1,0xe50a);
  iVar1 = FUN_00033d98();
  if (iVar1 == 0) {
    FUN_0002be78();
  }
  else if (*(int *)(param_1 + 0x58) == 0x700a) {
    FUN_0002b9fc();
  }
  else {
    FUN_0002bfa8(param_1);
  }
  return;
}


// 0002bc7c FUN_0002bc7c

undefined4 FUN_0002bc7c(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  tagRECT local_34;
  tagRECT tStack_24;
  
  if ((*(int *)(param_1 + 0x2a4) == 0) && (*(int *)(param_1 + 0xa0) != 0)) {
    iVar1 = operator_new(0x8c);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_0002c6b4(iVar1,param_1);
    }
    *(int *)(param_1 + 0x2a4) = iVar1;
    if (iVar1 != 0) {
      FUN_00033d64(param_1,0);
      *(undefined4 *)(*(int *)(param_1 + 0x2a4) + 0x44) = 1;
      if (*(int **)(param_1 + 0x48) != (int *)0x0) {
        (**(code **)(**(int **)(param_1 + 0x48) + 0x54))();
        piVar2 = *(int **)(param_1 + 0x48);
        if (piVar2 != (int *)0x0) {
          (**(code **)(*piVar2 + 4))(piVar2,1);
        }
        *(undefined4 *)(param_1 + 0x48) = 0;
      }
      FUN_0002ffec(*(undefined4 *)(param_1 + 0x7c));
      piVar2 = (int *)FUN_00031b24();
      FUN_0003ab6c(*(undefined4 *)(param_1 + 0x2a4),piVar2,u_WCE_FINDREPLACEBAR_00044430,0x8200,
                   0xe821);
      iVar1 = FUN_0002ed1c(piVar2,&CFrameWnd::classCFrameWnd);
      if (iVar1 == 0) {
        GetClientRect((HWND)piVar2[7],&local_34);
        GetWindowRect(*(HWND *)(*(int *)(param_1 + 0x2a4) + 0x1c),&tStack_24);
        local_34.top = (tStack_24.top - tStack_24.bottom) + local_34.bottom;
        FUN_00033c90(*(undefined4 *)(param_1 + 0x2a4),local_34.left,local_34.top,
                     local_34.right - local_34.left,local_34.bottom - local_34.top,1);
        FUN_00033d64(*(undefined4 *)(param_1 + 0x2a4),5);
        UpdateWindow(*(HWND *)(*(int *)(param_1 + 0x2a4) + 0x1c));
      }
      else {
        (**(code **)(*piVar2 + 0xc0))(piVar2,0);
      }
      if (param_2 != 1) {
        uVar3 = FUN_00033a44(*(undefined4 *)(param_1 + 0x2a4),0xe508);
        FUN_00033dcc(uVar3,1);
        uVar3 = FUN_00033a44(*(undefined4 *)(param_1 + 0x2a4),0xe509);
      }
      else {
        uVar3 = FUN_00033a44(*(undefined4 *)(param_1 + 0x2a4),0xe508);
        FUN_00033dcc(uVar3,0);
        uVar3 = FUN_00033a44(*(undefined4 *)(param_1 + 0x2a4),0xe509);
      }
      FUN_00033dcc(uVar3,param_2 != 1);
      FUN_00033e00(piVar2);
      return 1;
    }
    FUN_0002be78();
  }
  return 0;
}


// 0002be78 FUN_0002be78

void FUN_0002be78(int *param_1)

{
  UINT Msg;
  int *piVar1;
  uint uVar2;
  
  uVar2 = param_1[0x21];
  param_1[0x21] = uVar2 | 0x40;
  if ((uVar2 & 8) == 8) {
    param_1[0x21] = uVar2 & 0xfffffff7 | 0x40;
  }
  if ((param_1[0x21] & 0x10U) == 0x10) {
    param_1[0x21] = param_1[0x21] & 0xffffffef;
  }
  if ((param_1[0x21] & 0x20U) == 0x20) {
    param_1[0x21] = param_1[0x21] & 0xffffffdf;
  }
  Msg = RegisterWindowMessageW(u_commdlg_FindReplace_0004439c);
  SendMessageW((HWND)param_1[0x1f],Msg,0,(LPARAM)(param_1 + 0x1e));
  if ((int *)param_1[0x12] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0x12] + 0x54))();
    piVar1 = (int *)param_1[0x12];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 4))(piVar1,1);
    }
    param_1[0x12] = 0;
  }
  if (param_1[0xa9] != 0) {
    FUN_00033d64(param_1[0xa9],0);
    SetFocus((HWND)param_1[0x1f]);
    piVar1 = (int *)FUN_00031b9c(param_1[0xa9]);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0xc0))(piVar1,1);
    }
    (**(code **)(*(int *)param_1[0xa9] + 0x54))();
    param_1[0xa9] = 0;
  }
  param_1[0xc] = 2;
  (**(code **)(*param_1 + 0x54))();
  return;
}


// 0002bfa8 FUN_0002bfa8

void FUN_0002bfa8(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  LRESULT LVar3;
  UINT Msg;
  
  iVar1 = FUN_00032a4c(param_1,1);
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 0x84) = 0x111;
    uVar2 = FUN_00033a44(param_1,0xe500);
    FUN_00033bec(uVar2,*(undefined4 *)(param_1 + 0x88),*(undefined2 *)(param_1 + 0x90));
    uVar2 = FUN_00033a44(param_1,0xe501);
    FUN_00033bec(uVar2,*(undefined4 *)(param_1 + 0x8c),*(undefined2 *)(param_1 + 0x92));
    iVar1 = FUN_00033a44(param_1,0xe502);
    LVar3 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0xf0,0,0);
    if (0 < LVar3) {
      *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 2;
    }
    iVar1 = FUN_00033a44(param_1,0xe503);
    LVar3 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0xf0,0,0);
    if (0 < LVar3) {
      *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 4;
    }
    *(undefined4 *)(param_1 + 0xa0) = 1;
    PostMessageW(*(HWND *)(param_1 + 0x1c),0x6bc,0,0);
    Msg = RegisterWindowMessageW(u_commdlg_FindReplace_0004439c);
    SendMessageW(*(HWND *)(param_1 + 0x7c),Msg,0,param_1 + 0x78);
  }
  return;
}


// 0002c0ac FUN_0002c0ac

void FUN_0002c0ac(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  LRESULT LVar3;
  UINT Msg;
  BOOL BVar4;
  
  iVar1 = FUN_00032a4c(param_1,1);
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 0x84) = 0x121;
    uVar2 = FUN_00033a44(param_1,0xe500);
    FUN_00033bec(uVar2,*(undefined4 *)(param_1 + 0x88),*(undefined2 *)(param_1 + 0x90));
    uVar2 = FUN_00033a44(param_1,0xe501);
    FUN_00033bec(uVar2,*(undefined4 *)(param_1 + 0x8c),*(undefined2 *)(param_1 + 0x92));
    iVar1 = FUN_00033a44(param_1,0xe502);
    LVar3 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0xf0,0,0);
    if (0 < LVar3) {
      *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 2;
    }
    iVar1 = FUN_00033a44(param_1,0xe503);
    LVar3 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0xf0,0,0);
    if (0 < LVar3) {
      *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 4;
    }
    Msg = RegisterWindowMessageW(u_commdlg_FindReplace_0004439c);
    SendMessageW(*(HWND *)(param_1 + 0x7c),Msg,0,param_1 + 0x78);
    BVar4 = IsWindow(*(HWND *)(param_1 + 0x1c));
    if (BVar4 != 0) {
      FUN_0002be78(param_1);
    }
  }
  return;
}


// 0002c1b8 FUN_0002c1b8

void FUN_0002c1b8(int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  CString local_10;
  
  local_10.str = g_afxEmptyString;
  FUN_000308bc(param_1,0xe500,&local_10);
  bVar2 = *(int *)(local_10.str + -4) != 0;
  uVar1 = FUN_00033a44(param_1,0xe50a);
  FUN_00033dcc(uVar1,bVar2);
  if (*(int *)(param_1 + 0x58) != 0x700a) {
    uVar1 = FUN_00033a44(param_1,0xe508);
    FUN_00033dcc(uVar1,bVar2);
    uVar1 = FUN_00033a44(param_1,0xe509);
    FUN_00033dcc(uVar1,bVar2);
  }
  CString_Dtor(&local_10);
  return;
}


// 0002c264 FUN_0002c264

HWND FUN_0002c264(int param_1)

{
  int iVar1;
  HRSRC hResInfo;
  LPCDLGTEMPLATEW lpTemplate;
  HWND hDlg;
  HWND pHVar2;
  HMODULE hModule;
  bool bVar3;
  
  iVar1 = FUN_0003f4f4();
  hModule = *(HMODULE *)(iVar1 + 0xc);
  if (hModule == (HMODULE)0x0) {
    return (HWND)0x0;
  }
  hResInfo = FindResourceW(hModule,u_WCE_FINDDLG_00044458,(LPCWSTR)0x5);
  lpTemplate = LoadResource(hModule,hResInfo);
  hDlg = CreateDialogIndirectParamW
                   (hModule,lpTemplate,*(HWND *)(param_1 + 4),*(DLGPROC *)(param_1 + 0x20),0);
  pHVar2 = GetDlgItem(hDlg,0xe500);
  SetWindowTextW(pHVar2,*(LPCWSTR *)(param_1 + 0x10));
  if ((*(uint *)(param_1 + 0xc) & 0x10000) == 0) {
    if ((*(uint *)(param_1 + 0xc) & 0x1000) == 0) {
      pHVar2 = GetDlgItem(hDlg,0xe502);
      iVar1 = 5;
      goto LAB_0002c31c;
    }
    pHVar2 = GetDlgItem(hDlg,0xe502);
    EnableWindow(pHVar2,0);
  }
  else {
    pHVar2 = GetDlgItem(hDlg,0xe502);
    iVar1 = 0;
LAB_0002c31c:
    ShowWindow(pHVar2,iVar1);
  }
  if ((*(uint *)(param_1 + 0xc) & 0x8000) == 0) {
    if ((*(uint *)(param_1 + 0xc) & 0x800) == 0) {
      pHVar2 = GetDlgItem(hDlg,0xe503);
      iVar1 = 5;
      goto LAB_0002c368;
    }
    pHVar2 = GetDlgItem(hDlg,0xe503);
    EnableWindow(pHVar2,0);
  }
  else {
    pHVar2 = GetDlgItem(hDlg,0xe503);
    iVar1 = 0;
LAB_0002c368:
    ShowWindow(pHVar2,iVar1);
  }
  bVar3 = (*(uint *)(param_1 + 0xc) & 1) == 0;
  if (bVar3) {
    pHVar2 = GetDlgItem(hDlg,0xe505);
    SendMessageW(pHVar2,0xf1,1,0);
    pHVar2 = GetDlgItem(hDlg,0xe506);
  }
  else {
    pHVar2 = GetDlgItem(hDlg,0xe505);
    SendMessageW(pHVar2,0xf1,0,0);
    pHVar2 = GetDlgItem(hDlg,0xe506);
  }
  SendMessageW(pHVar2,0xf1,(uint)!bVar3,0);
  if ((*(uint *)(param_1 + 0xc) & 0x4000) == 0) {
    if ((*(uint *)(param_1 + 0xc) & 0x400) != 0) {
      pHVar2 = GetDlgItem(hDlg,0xe504);
      EnableWindow(pHVar2,0);
      pHVar2 = GetDlgItem(hDlg,0xe505);
      EnableWindow(pHVar2,0);
      pHVar2 = GetDlgItem(hDlg,0xe506);
      EnableWindow(pHVar2,0);
      goto LAB_0002c4c0;
    }
    pHVar2 = GetDlgItem(hDlg,0xe504);
    ShowWindow(pHVar2,5);
    pHVar2 = GetDlgItem(hDlg,0xe505);
    ShowWindow(pHVar2,5);
    pHVar2 = GetDlgItem(hDlg,0xe506);
    iVar1 = 5;
  }
  else {
    pHVar2 = GetDlgItem(hDlg,0xe504);
    ShowWindow(pHVar2,0);
    pHVar2 = GetDlgItem(hDlg,0xe505);
    ShowWindow(pHVar2,0);
    pHVar2 = GetDlgItem(hDlg,0xe506);
    iVar1 = 0;
  }
  ShowWindow(pHVar2,iVar1);
LAB_0002c4c0:
  if ((*(uint *)(param_1 + 0xc) & 0x80) == 0) {
    pHVar2 = GetDlgItem(hDlg,0xe507);
    iVar1 = 0;
  }
  else {
    pHVar2 = GetDlgItem(hDlg,0xe507);
    iVar1 = 5;
  }
  ShowWindow(pHVar2,iVar1);
  pHVar2 = GetDlgItem(hDlg,0xe500);
  SetFocus(pHVar2);
  ShowWindow(hDlg,5);
  UpdateWindow(hDlg);
  return hDlg;
}


// 0002c520 FUN_0002c520

HWND FUN_0002c520(int param_1)

{
  int iVar1;
  HRSRC hResInfo;
  LPCDLGTEMPLATEW lpTemplate;
  HWND hDlg;
  HWND pHVar2;
  HMODULE hModule;
  
  iVar1 = FUN_0003f4f4();
  hModule = *(HMODULE *)(iVar1 + 0xc);
  if (hModule == (HMODULE)0x0) {
    return (HWND)0x0;
  }
  hResInfo = FindResourceW(hModule,u_WCE_REPLACEDLG_00044470,(LPCWSTR)0x5);
  lpTemplate = LoadResource(hModule,hResInfo);
  hDlg = CreateDialogIndirectParamW
                   (hModule,lpTemplate,*(HWND *)(param_1 + 4),*(DLGPROC *)(param_1 + 0x20),0);
  pHVar2 = GetDlgItem(hDlg,0xe500);
  SetWindowTextW(pHVar2,*(LPCWSTR *)(param_1 + 0x10));
  pHVar2 = GetDlgItem(hDlg,0xe501);
  SetWindowTextW(pHVar2,*(LPCWSTR *)(param_1 + 0x14));
  if ((*(uint *)(param_1 + 0xc) & 0x10000) == 0x10000) {
    pHVar2 = GetDlgItem(hDlg,0xe502);
    iVar1 = 0;
LAB_0002c600:
    ShowWindow(pHVar2,iVar1);
  }
  else {
    if ((*(uint *)(param_1 + 0xc) & 0x1000) != 0x1000) {
      pHVar2 = GetDlgItem(hDlg,0xe502);
      iVar1 = 5;
      goto LAB_0002c600;
    }
    pHVar2 = GetDlgItem(hDlg,0xe502);
    EnableWindow(pHVar2,0);
  }
  if ((*(uint *)(param_1 + 0xc) & 0x8000) == 0x8000) {
    pHVar2 = GetDlgItem(hDlg,0xe503);
    iVar1 = 0;
  }
  else {
    if ((*(uint *)(param_1 + 0xc) & 0x800) == 0x800) {
      pHVar2 = GetDlgItem(hDlg,0xe503);
      EnableWindow(pHVar2,0);
      goto LAB_0002c660;
    }
    pHVar2 = GetDlgItem(hDlg,0xe503);
    iVar1 = 5;
  }
  ShowWindow(pHVar2,iVar1);
LAB_0002c660:
  if ((*(uint *)(param_1 + 0xc) & 0x80) == 0x80) {
    pHVar2 = GetDlgItem(hDlg,0xe507);
    iVar1 = 5;
  }
  else {
    pHVar2 = GetDlgItem(hDlg,0xe507);
    iVar1 = 0;
  }
  ShowWindow(pHVar2,iVar1);
  ShowWindow(hDlg,5);
  UpdateWindow(hDlg);
  return hDlg;
}


// 0002c6b4 FUN_0002c6b4

undefined1 * FUN_0002c6b4(undefined1 *param_1,undefined4 param_2)

{
  FUN_0003aa9c();
  *(undefined4 *)(param_1 + 0x88) = param_2;
  *param_1 = 200;
  param_1[1] = 0x24;
  param_1[2] = 4;
  param_1[3] = 0;
  return param_1;
}


// 0002c718 FUN_0002c718

void FUN_0002c718(undefined1 *param_1)

{
  *param_1 = 200;
  param_1[1] = 0x24;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0003ab2c();
  return;
}


// 0002c774 MessageBoxW

int MessageBoxW(HWND hWnd,LPCWSTR lpText,LPCWSTR lpCaption,UINT uType)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c778. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = MessageBoxW(hWnd,lpText,lpCaption,uType);
  return iVar1;
}


// 0002c780 GetMessageW

BOOL GetMessageW(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c784. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetMessageW(lpMsg,hWnd,wMsgFilterMin,wMsgFilterMax);
  return BVar1;
}


// 0002c78c DispatchMessageW

LRESULT DispatchMessageW(MSG *lpMsg)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c790. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = DispatchMessageW(lpMsg);
  return LVar1;
}


// 0002c798 TranslateMessage

BOOL TranslateMessage(MSG *lpMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c79c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TranslateMessage(lpMsg);
  return BVar1;
}


// 0002c7a4 srand

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void srand(uint _Seed)

{
                    /* WARNING: Could not recover jumptable at 0x0002c7a8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  srand(_Seed);
  return;
}


// 0002c7b0 RegisterClassW

ATOM RegisterClassW(WNDCLASSW *lpWndClass)

{
  ATOM AVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  AVar1 = RegisterClassW(lpWndClass);
  return AVar1;
}


// 0002c7bc GetStockObject

HGDIOBJ GetStockObject(int i)

{
  HGDIOBJ pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7c0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = GetStockObject(i);
  return pvVar1;
}


// 0002c7c8 UpdateWindow

BOOL UpdateWindow(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7cc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = UpdateWindow(hWnd);
  return BVar1;
}


// 0002c7d4 ShowWindow

BOOL ShowWindow(HWND hWnd,int nCmdShow)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ShowWindow(hWnd,nCmdShow);
  return BVar1;
}


// 0002c7e0 CreateWindowExW

HWND CreateWindowExW(DWORD dwExStyle,LPCWSTR lpClassName,LPCWSTR lpWindowName,DWORD dwStyle,int X,
                    int Y,int nWidth,int nHeight,HWND hWndParent,HMENU hMenu,HINSTANCE hInstance,
                    LPVOID lpParam)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7e4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateWindowExW(dwExStyle,lpClassName,lpWindowName,dwStyle,X,Y,nWidth,nHeight,hWndParent,
                           hMenu,hInstance,lpParam);
  return pHVar1;
}


// 0002c7ec GetSystemMetrics

int GetSystemMetrics(int nIndex)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetSystemMetrics(nIndex);
  return iVar1;
}


// 0002c7f8 SetForegroundWindow

BOOL SetForegroundWindow(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c7fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetForegroundWindow(hWnd);
  return BVar1;
}


// 0002c804 FindWindowW

HWND FindWindowW(LPCWSTR lpClassName,LPCWSTR lpWindowName)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c808. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = FindWindowW(lpClassName,lpWindowName);
  return pHVar1;
}


// 0002c810 memcpy

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *_Dst,void *_Src,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c814. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memcpy(_Dst,_Src,_Size);
  return pvVar1;
}


// 0002c81c SetTimer

UINT_PTR SetTimer(HWND hWnd,UINT_PTR nIDEvent,UINT uElapse,TIMERPROC lpTimerFunc)

{
  UINT_PTR UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c820. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = SetTimer(hWnd,nIDEvent,uElapse,lpTimerFunc);
  return UVar1;
}


// 0002c828 KillTimer

BOOL KillTimer(HWND hWnd,UINT_PTR uIDEvent)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c82c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = KillTimer(hWnd,uIDEvent);
  return BVar1;
}


// 0002c834 DefWindowProcW

LRESULT DefWindowProcW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c838. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = DefWindowProcW(hWnd,Msg,wParam,lParam);
  return LVar1;
}


// 0002c840 EndPaint

BOOL EndPaint(HWND hWnd,PAINTSTRUCT *lpPaint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c844. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EndPaint(hWnd,lpPaint);
  return BVar1;
}


// 0002c84c GetForegroundWindow

HWND GetForegroundWindow(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c850. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetForegroundWindow();
  return pHVar1;
}


// 0002c858 BeginPaint

HDC BeginPaint(HWND hWnd,LPPAINTSTRUCT lpPaint)

{
  HDC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c85c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = BeginPaint(hWnd,lpPaint);
  return pHVar1;
}


// 0002c864 PostQuitMessage

void PostQuitMessage(int nExitCode)

{
                    /* WARNING: Could not recover jumptable at 0x0002c868. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  PostQuitMessage(nExitCode);
  return;
}


// 0002c870 SendMessageW

LRESULT SendMessageW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c874. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SendMessageW(hWnd,Msg,wParam,lParam);
  return LVar1;
}


// 0002c87c sndPlaySoundW

BOOL sndPlaySoundW(LPCWSTR pszSound,UINT fuSound)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c880. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = sndPlaySoundW(pszSound,fuSound);
  return BVar1;
}


// 0002c888 Sleep

void Sleep(DWORD dwMilliseconds)

{
                    /* WARNING: Could not recover jumptable at 0x0002c88c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  Sleep(dwMilliseconds);
  return;
}


// 0002c894 CreateDirectoryW

BOOL CreateDirectoryW(LPCWSTR lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c898. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CreateDirectoryW(lpPathName,lpSecurityAttributes);
  return BVar1;
}


// 0002c8a0 RegCloseKey

LSTATUS RegCloseKey(HKEY hKey)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegCloseKey(hKey);
  return LVar1;
}


// 0002c8ac RegQueryValueExW

LSTATUS RegQueryValueExW(HKEY hKey,LPCWSTR lpValueName,LPDWORD lpReserved,LPDWORD lpType,
                        LPBYTE lpData,LPDWORD lpcbData)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8b0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegQueryValueExW(hKey,lpValueName,lpReserved,lpType,lpData,lpcbData);
  return LVar1;
}


// 0002c8b8 RegOpenKeyExW

LSTATUS RegOpenKeyExW(HKEY hKey,LPCWSTR lpSubKey,DWORD ulOptions,REGSAM samDesired,PHKEY phkResult)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8bc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegOpenKeyExW(hKey,lpSubKey,ulOptions,samDesired,phkResult);
  return LVar1;
}


// 0002c8c4 CloseHandle

BOOL CloseHandle(HANDLE hObject)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8c8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CloseHandle(hObject);
  return BVar1;
}


// 0002c8d0 CreateFileW

HANDLE CreateFileW(LPCWSTR lpFileName,DWORD dwDesiredAccess,DWORD dwShareMode,
                  LPSECURITY_ATTRIBUTES lpSecurityAttributes,DWORD dwCreationDisposition,
                  DWORD dwFlagsAndAttributes,HANDLE hTemplateFile)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = CreateFileW(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,
                       dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
  return pvVar1;
}


// 0002c8dc div

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

div_t * div(div_t *__return_storage_ptr__,int _Numerator,int _Denominator)

{
  div_t *pdVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pdVar1 = div(__return_storage_ptr__,_Numerator,_Denominator);
  return pdVar1;
}


// 0002c8e8 RegSetValueExW

LSTATUS RegSetValueExW(HKEY hKey,LPCWSTR lpValueName,DWORD Reserved,DWORD dwType,BYTE *lpData,
                      DWORD cbData)

{
  LSTATUS LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8ec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = RegSetValueExW(hKey,lpValueName,Reserved,dwType,lpData,cbData);
  return LVar1;
}


// 0002c8f4 wcscmp

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wcscmp(wchar_t *_Str1,wchar_t *_Str2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c8f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = wcscmp(_Str1,_Str2);
  return iVar1;
}


// 0002c900 WriteFile

BOOL WriteFile(HANDLE hFile,LPCVOID lpBuffer,DWORD nNumberOfBytesToWrite,
              LPDWORD lpNumberOfBytesWritten,LPOVERLAPPED lpOverlapped)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c904. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = WriteFile(hFile,lpBuffer,nNumberOfBytesToWrite,lpNumberOfBytesWritten,lpOverlapped);
  return BVar1;
}


// 0002c90c SetFilePointer

DWORD SetFilePointer(HANDLE hFile,LONG lDistanceToMove,PLONG lpDistanceToMoveHigh,DWORD dwMoveMethod
                    )

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c910. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = SetFilePointer(hFile,lDistanceToMove,lpDistanceToMoveHigh,dwMoveMethod);
  return DVar1;
}


// 0002c918 ReadFile

BOOL ReadFile(HANDLE hFile,LPVOID lpBuffer,DWORD nNumberOfBytesToRead,LPDWORD lpNumberOfBytesRead,
             LPOVERLAPPED lpOverlapped)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c91c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ReadFile(hFile,lpBuffer,nNumberOfBytesToRead,lpNumberOfBytesRead,lpOverlapped);
  return BVar1;
}


// 0002c924 memset

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memset(void *_Dst,int _Val,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c928. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memset(_Dst,_Val,_Size);
  return pvVar1;
}


// 0002c930 DeleteObject

BOOL DeleteObject(HGDIOBJ ho)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c934. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteObject(ho);
  return BVar1;
}


// 0002c93c GetObjectW

int GetObjectW(HANDLE h,int c,LPVOID pv)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c940. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetObjectW(h,c,pv);
  return iVar1;
}


// 0002c948 PeekMessageW

BOOL PeekMessageW(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c94c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = PeekMessageW(lpMsg,hWnd,wMsgFilterMin,wMsgFilterMax,wRemoveMsg);
  return BVar1;
}


// 0002c954 rand

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int rand(void)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c958. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = rand();
  return iVar1;
}


// 0002c960 DeleteFileW

BOOL DeleteFileW(LPCWSTR lpFileName)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c964. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteFileW(lpFileName);
  return BVar1;
}


// 0002c96c PostMessageW

BOOL PostMessageW(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c970. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = PostMessageW(hWnd,Msg,wParam,lParam);
  return BVar1;
}


// 0002c978 InterlockedIncrement

LONG InterlockedIncrement(LONG *lpAddend)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c97c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = InterlockedIncrement(lpAddend);
  return LVar1;
}


// 0002c984 InterlockedDecrement

LONG InterlockedDecrement(LONG *lpAddend)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c988. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = InterlockedDecrement(lpAddend);
  return LVar1;
}


// 0002c990 memmove

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memmove(void *_Dst,void *_Src,size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c994. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = memmove(_Dst,_Src,_Size);
  return pvVar1;
}


// 0002c99c wcslen

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t wcslen(wchar_t *_Str)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c9a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = wcslen(_Str);
  return sVar1;
}


// 0002c9a8 strlen

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strlen(char *_Str)

{
  size_t sVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c9ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  sVar1 = strlen(_Str);
  return sVar1;
}


// 0002c9b4 wcschr

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

wchar_t * wcschr(wchar_t *_Str,wchar_t _Ch)

{
  wchar_t *pwVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c9b8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pwVar1 = wcschr(_Str,_Ch);
  return pwVar1;
}


// 0002c9cc MultiByteToWideChar

int MultiByteToWideChar(UINT CodePage,DWORD dwFlags,LPCSTR lpMultiByteStr,int cbMultiByte,
                       LPWSTR lpWideCharStr,int cchWideChar)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c9d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = MultiByteToWideChar(CodePage,dwFlags,lpMultiByteStr,cbMultiByte,lpWideCharStr,cchWideChar)
  ;
  return iVar1;
}


// 0002c9d8 malloc

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t _Size)

{
  void *pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c9dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = malloc(_Size);
  return pvVar1;
}


// 0002c9e4 free

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *_Memory)

{
                    /* WARNING: Could not recover jumptable at 0x0002c9e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(_Memory);
  return;
}


// 0002c9f0 GetTimeZoneInformation

DWORD GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002c9f4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetTimeZoneInformation(lpTimeZoneInformation);
  return DVar1;
}


// 0002c9fc GetSystemTime

void GetSystemTime(LPSYSTEMTIME lpSystemTime)

{
                    /* WARNING: Could not recover jumptable at 0x0002ca00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  GetSystemTime(lpSystemTime);
  return;
}


// 0002ca08 SystemTimeToFileTime

BOOL SystemTimeToFileTime(SYSTEMTIME *lpSystemTime,LPFILETIME lpFileTime)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SystemTimeToFileTime(lpSystemTime,lpFileTime);
  return BVar1;
}


// 0002ca14 FileTimeToSystemTime

BOOL FileTimeToSystemTime(FILETIME *lpFileTime,LPSYSTEMTIME lpSystemTime)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FileTimeToSystemTime(lpFileTime,lpSystemTime);
  return BVar1;
}


// 0002ca20 GetLocalTime

void GetLocalTime(LPSYSTEMTIME lpSystemTime)

{
                    /* WARNING: Could not recover jumptable at 0x0002ca24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  GetLocalTime(lpSystemTime);
  return;
}


// 0002ca2c wsprintfW

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int wsprintfW(LPWSTR param_1,LPCWSTR param_2,...)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = wsprintfW(param_1,param_2);
  return iVar1;
}


// 0002ca38 wcsncpy

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

wchar_t * wcsncpy(wchar_t *_Dest,wchar_t *_Source,size_t _Count)

{
  wchar_t *pwVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pwVar1 = wcsncpy(_Dest,_Source,_Count);
  return pwVar1;
}


// 0002ca44 _wtol

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long _wtol(wchar_t *_Str)

{
  long lVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  lVar1 = _wtol(_Str);
  return lVar1;
}


// 0002ca50 setjmp

void setjmp(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002ca54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  setjmp();
  return;
}


// 0002ca5c strcmp

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strcmp(char *_Str1,char *_Str2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = strcmp(_Str1,_Str2);
  return iVar1;
}


// 0002ca68 LoadStringW

int LoadStringW(HINSTANCE hInstance,UINT uID,LPWSTR lpBuffer,int cchBufferMax)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = LoadStringW(hInstance,uID,lpBuffer,cchBufferMax);
  return iVar1;
}


// 0002ca74 SetLastError

void SetLastError(DWORD dwErrCode)

{
                    /* WARNING: Could not recover jumptable at 0x0002ca78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SetLastError(dwErrCode);
  return;
}


// 0002ca80 GetLastError

DWORD GetLastError(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ca84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetLastError();
  return DVar1;
}


// 0002ca8c longjmp

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void longjmp(int *_Buf,int _Value)

{
                    /* WARNING: Could not recover jumptable at 0x0002ca90. Too many branches */
                    /* WARNING: Subroutine does not return */
                    /* WARNING: Treating indirect jump as call */
  longjmp(_Buf,_Value);
  return;
}


// 0002ca98 InitializeCriticalSection

void InitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0002ca9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  InitializeCriticalSection(lpCriticalSection);
  return;
}


// 0002caa4 LeaveCriticalSection

void LeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0002caa8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LeaveCriticalSection(lpCriticalSection);
  return;
}


// 0002cab0 EnterCriticalSection

void EnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection)

{
                    /* WARNING: Could not recover jumptable at 0x0002cab4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EnterCriticalSection(lpCriticalSection);
  return;
}


// 0002cabc LocalAlloc

HLOCAL LocalAlloc(UINT uFlags,SIZE_T uBytes)

{
  HLOCAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cac0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LocalAlloc(uFlags,uBytes);
  return pvVar1;
}


// 0002cac8 LocalFree

HLOCAL LocalFree(HLOCAL hMem)

{
  HLOCAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cacc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LocalFree(hMem);
  return pvVar1;
}


// 0002cad4 TlsCall

void TlsCall(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002cad8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  TlsCall();
  return;
}


// 0002cae0 TlsSetValue

BOOL TlsSetValue(DWORD dwTlsIndex,LPVOID lpTlsValue)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cae4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = TlsSetValue(dwTlsIndex,lpTlsValue);
  return BVar1;
}


// 0002caec LocalReAlloc

HLOCAL LocalReAlloc(HLOCAL hMem,SIZE_T uBytes,UINT uFlags)

{
  HLOCAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002caf0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LocalReAlloc(hMem,uBytes,uFlags);
  return pvVar1;
}


// 0002caf8 TlsGetValue

LPVOID TlsGetValue(DWORD dwTlsIndex)

{
  LPVOID pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cafc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = TlsGetValue(dwTlsIndex);
  return pvVar1;
}


// 0002cb04 EnableWindow

BOOL EnableWindow(HWND hWnd,BOOL bEnable)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EnableWindow(hWnd,bEnable);
  return BVar1;
}


// 0002cb10 IsWindowEnabled

BOOL IsWindowEnabled(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb14. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsWindowEnabled(hWnd);
  return BVar1;
}


// 0002cb1c GetActiveWindow

HWND GetActiveWindow(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetActiveWindow();
  return pHVar1;
}


// 0002cb28 GetParent

HWND GetParent(HWND hWnd)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetParent(hWnd);
  return pHVar1;
}


// 0002cb34 GetWindowLongW

LONG GetWindowLongW(HWND hWnd,int nIndex)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = GetWindowLongW(hWnd,nIndex);
  return LVar1;
}


// 0002cb40 wcscpy

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

wchar_t * wcscpy(wchar_t *_Dest,wchar_t *_Source)

{
  wchar_t *pwVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pwVar1 = wcscpy(_Dest,_Source);
  return pwVar1;
}


// 0002cb4c IsWindowVisible

BOOL IsWindowVisible(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb50. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsWindowVisible(hWnd);
  return BVar1;
}


// 0002cb58 GetKeyState

SHORT GetKeyState(int nVirtKey)

{
  SHORT SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = GetKeyState(nVirtKey);
  return SVar1;
}


// 0002cb64 UnregisterClassW

BOOL UnregisterClassW(LPCWSTR lpClassName,HINSTANCE hInstance)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = UnregisterClassW(lpClassName,hInstance);
  return BVar1;
}


// 0002cb70 GetNextDlgTabItem

HWND GetNextDlgTabItem(HWND hDlg,HWND hCtl,BOOL bPrevious)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetNextDlgTabItem(hDlg,hCtl,bPrevious);
  return pHVar1;
}


// 0002cb7c GetFocus

HWND GetFocus(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetFocus();
  return pHVar1;
}


// 0002cb88 EnableMenuItem

BOOL EnableMenuItem(HMENU hMenu,UINT uIDEnableItem,UINT uEnable)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EnableMenuItem(hMenu,uIDEnableItem,uEnable);
  return BVar1;
}


// 0002cb94 CheckMenuItem

DWORD CheckMenuItem(HMENU hMenu,UINT uIDCheckItem,UINT uCheck)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cb98. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = CheckMenuItem(hMenu,uIDCheckItem,uCheck);
  return DVar1;
}


// 0002cba0 RegisterWindowMessageW

UINT RegisterWindowMessageW(LPCWSTR lpString)

{
  UINT UVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cba4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  UVar1 = RegisterWindowMessageW(lpString);
  return UVar1;
}


// 0002cbac SetWindowPos

BOOL SetWindowPos(HWND hWnd,HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetWindowPos(hWnd,hWndInsertAfter,X,Y,cx,cy,uFlags);
  return BVar1;
}


// 0002cbb8 SetWindowLongW

LONG SetWindowLongW(HWND hWnd,int nIndex,LONG dwNewLong)

{
  LONG LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbbc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = SetWindowLongW(hWnd,nIndex,dwNewLong);
  return LVar1;
}


// 0002cbc4 GetWindowRect

BOOL GetWindowRect(HWND hWnd,LPRECT lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbc8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetWindowRect(hWnd,lpRect);
  return BVar1;
}


// 0002cbd0 GetWindow

HWND GetWindow(HWND hWnd,UINT uCmd)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetWindow(hWnd,uCmd);
  return pHVar1;
}


// 0002cbdc GetMessagePos

DWORD GetMessagePos(void)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbe0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetMessagePos();
  return DVar1;
}


// 0002cbe8 DestroyWindow

BOOL DestroyWindow(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DestroyWindow(hWnd);
  return BVar1;
}


// 0002cbf4 CallWindowProcW

LRESULT CallWindowProcW(WNDPROC lpPrevWndFunc,HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)

{
  LRESULT LVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cbf8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  LVar1 = CallWindowProcW(lpPrevWndFunc,hWnd,Msg,wParam,lParam);
  return LVar1;
}


// 0002cc00 GetWindowTextW

int GetWindowTextW(HWND hWnd,LPWSTR lpString,int nMaxCount)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetWindowTextW(hWnd,lpString,nMaxCount);
  return iVar1;
}


// 0002cc0c GetWindowTextLengthW

int GetWindowTextLengthW(HWND hWnd)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetWindowTextLengthW(hWnd);
  return iVar1;
}


// 0002cc18 GetDlgItem

HWND GetDlgItem(HWND hDlg,int nIDDlgItem)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetDlgItem(hDlg,nIDDlgItem);
  return pHVar1;
}


// 0002cc24 GetSubMenu

HMENU GetSubMenu(HMENU hMenu,int nPos)

{
  HMENU pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetSubMenu(hMenu,nPos);
  return pHVar1;
}


// 0002cc30 wcscat

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

wchar_t * wcscat(wchar_t *_Dest,wchar_t *_Source)

{
  wchar_t *pwVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pwVar1 = wcscat(_Dest,_Source);
  return pwVar1;
}


// 0002cc3c GetClassInfoW

BOOL GetClassInfoW(HINSTANCE hInstance,LPCWSTR lpClassName,LPWNDCLASSW lpWndClass)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetClassInfoW(hInstance,lpClassName,lpWndClass);
  return BVar1;
}


// 0002cc48 GetCapture

HWND GetCapture(void)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetCapture();
  return pHVar1;
}


// 0002cc54 GetDlgCtrlID

int GetDlgCtrlID(HWND hWnd)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetDlgCtrlID(hWnd);
  return iVar1;
}


// 0002cc60 IsChild

BOOL IsChild(HWND hWndParent,HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsChild(hWndParent,hWnd);
  return BVar1;
}


// 0002cc78 SetScrollRange

BOOL SetScrollRange(HWND hWnd,int nBar,int nMinPos,int nMaxPos,BOOL bRedraw)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetScrollRange(hWnd,nBar,nMinPos,nMaxPos,bRedraw);
  return BVar1;
}


// 0002cc84 SetScrollInfo

int SetScrollInfo(HWND hwnd,int nBar,LPCSCROLLINFO lpsi,BOOL redraw)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SetScrollInfo(hwnd,nBar,lpsi,redraw);
  return iVar1;
}


// 0002cc90 GetScrollInfo

BOOL GetScrollInfo(HWND hwnd,int nBar,LPSCROLLINFO lpsi)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cc94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetScrollInfo(hwnd,nBar,lpsi);
  return BVar1;
}


// 0002cc9c ScrollWindowEx

int ScrollWindowEx(HWND hWnd,int dx,int dy,RECT *prcScroll,RECT *prcClip,HRGN hrgnUpdate,
                  LPRECT prcUpdate,UINT flags)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cca0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ScrollWindowEx(hWnd,dx,dy,prcScroll,prcClip,hrgnUpdate,prcUpdate,flags);
  return iVar1;
}


// 0002cca8 CopyRect

BOOL CopyRect(LPRECT lprcDst,RECT *lprcSrc)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ccac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CopyRect(lprcDst,lprcSrc);
  return BVar1;
}


// 0002ccb4 GetClientRect

BOOL GetClientRect(HWND hWnd,LPRECT lpRect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ccb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetClientRect(hWnd,lpRect);
  return BVar1;
}


// 0002ccc0 EqualRect

BOOL EqualRect(RECT *lprc1,RECT *lprc2)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ccc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = EqualRect(lprc1,lprc2);
  return BVar1;
}


// 0002cccc ScreenToClient

BOOL ScreenToClient(HWND hWnd,LPPOINT lpPoint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ccd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ScreenToClient(hWnd,lpPoint);
  return BVar1;
}


// 0002cce4 SetTextColor

COLORREF SetTextColor(HDC hdc,COLORREF color)

{
  COLORREF CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cce8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = SetTextColor(hdc,color);
  return CVar1;
}


// 0002ccf0 GetSysColor

DWORD GetSysColor(int nIndex)

{
  DWORD DVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ccf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  DVar1 = GetSysColor(nIndex);
  return DVar1;
}


// 0002ccfc SetBkColor

COLORREF SetBkColor(HDC hdc,COLORREF color)

{
  COLORREF CVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CVar1 = SetBkColor(hdc,color);
  return CVar1;
}


// 0002cd08 MapWindowPoints

int MapWindowPoints(HWND hWndFrom,HWND hWndTo,LPPOINT lpPoints,UINT cPoints)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = MapWindowPoints(hWndFrom,hWndTo,lpPoints,cPoints);
  return iVar1;
}


// 0002cd14 LoadResource

HGLOBAL LoadResource(HMODULE hModule,HRSRC hResInfo)

{
  HGLOBAL pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LoadResource(hModule,hResInfo);
  return pvVar1;
}


// 0002cd20 FindResourceW

HRSRC FindResourceW(HMODULE hModule,LPCWSTR lpName,LPCWSTR lpType)

{
  HRSRC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = FindResourceW(hModule,lpName,lpType);
  return pHVar1;
}


// 0002cd2c FreeLibrary

BOOL FreeLibrary(HMODULE hLibModule)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = FreeLibrary(hLibModule);
  return BVar1;
}


// 0002cd38 GetModuleHandleW

HMODULE GetModuleHandleW(LPCWSTR lpModuleName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetModuleHandleW(lpModuleName);
  return pHVar1;
}


// 0002cd44 SetWindowTextW

BOOL SetWindowTextW(HWND hWnd,LPCWSTR lpString)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetWindowTextW(hWnd,lpString);
  return BVar1;
}


// 0002cd50 IsDialogMessageW

BOOL IsDialogMessageW(HWND hDlg,LPMSG lpMsg)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd54. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsDialogMessageW(hDlg,lpMsg);
  return BVar1;
}


// 0002cd5c MoveWindow

BOOL MoveWindow(HWND hWnd,int X,int Y,int nWidth,int nHeight,BOOL bRepaint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd60. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = MoveWindow(hWnd,X,Y,nWidth,nHeight,bRepaint);
  return BVar1;
}


// 0002cd68 SetFocus

HWND SetFocus(HWND hWnd)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd6c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SetFocus(hWnd);
  return pHVar1;
}


// 0002cd74 lstrcmpiW

int lstrcmpiW(LPCWSTR lpString1,LPCWSTR lpString2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = lstrcmpiW(lpString1,lpString2);
  return iVar1;
}


// 0002cd80 GetClassNameW

int GetClassNameW(HWND hWnd,LPWSTR lpClassName,int nMaxCount)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetClassNameW(hWnd,lpClassName,nMaxCount);
  return iVar1;
}


// 0002cd8c ClientToScreen

BOOL ClientToScreen(HWND hWnd,LPPOINT lpPoint)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ClientToScreen(hWnd,lpPoint);
  return BVar1;
}


// 0002cd98 lstrcmpW

int lstrcmpW(LPCWSTR lpString1,LPCWSTR lpString2)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cd9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = lstrcmpW(lpString1,lpString2);
  return iVar1;
}


// 0002cda4 GetProcAddressW

void GetProcAddressW(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002cda8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  GetProcAddressW();
  return;
}


// 0002cdb0 SetRect

BOOL SetRect(LPRECT lprc,int xLeft,int yTop,int xRight,int yBottom)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cdb4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetRect(lprc,xLeft,yTop,xRight,yBottom);
  return BVar1;
}


// 0002cdbc LoadLibraryW

HMODULE LoadLibraryW(LPCWSTR lpLibFileName)

{
  HMODULE pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cdc0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadLibraryW(lpLibFileName);
  return pHVar1;
}


// 0002cdc8 CreateProcessW

BOOL CreateProcessW(LPCWSTR lpApplicationName,LPWSTR lpCommandLine,
                   LPSECURITY_ATTRIBUTES lpProcessAttributes,
                   LPSECURITY_ATTRIBUTES lpThreadAttributes,BOOL bInheritHandles,
                   DWORD dwCreationFlags,LPVOID lpEnvironment,LPCWSTR lpCurrentDirectory,
                   LPSTARTUPINFOW lpStartupInfo,LPPROCESS_INFORMATION lpProcessInformation)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cdcc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = CreateProcessW(lpApplicationName,lpCommandLine,lpProcessAttributes,lpThreadAttributes,
                         bInheritHandles,dwCreationFlags,lpEnvironment,lpCurrentDirectory,
                         lpStartupInfo,lpProcessInformation);
  return BVar1;
}


// 0002cdd4 GetMenuItemInfoW

BOOL GetMenuItemInfoW(HMENU hmenu,UINT item,BOOL fByPosition,LPMENUITEMINFOW lpmii)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cdd8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = GetMenuItemInfoW(hmenu,item,fByPosition,lpmii);
  return BVar1;
}


// 0002cde0 InsertMenuW

BOOL InsertMenuW(HMENU hMenu,UINT uPosition,UINT uFlags,UINT_PTR uIDNewItem,LPCWSTR lpNewItem)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cde4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = InsertMenuW(hMenu,uPosition,uFlags,uIDNewItem,lpNewItem);
  return BVar1;
}


// 0002cdec DeleteMenu

BOOL DeleteMenu(HMENU hMenu,UINT uPosition,UINT uFlags)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cdf0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteMenu(hMenu,uPosition,uFlags);
  return BVar1;
}


// 0002cdf8 CreateFontIndirectW

HFONT CreateFontIndirectW(LOGFONTW *lplf)

{
  HFONT pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cdfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateFontIndirectW(lplf);
  return pHVar1;
}


// 0002ce04 ReleaseDC

int ReleaseDC(HWND hWnd,HDC hDC)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ReleaseDC(hWnd,hDC);
  return iVar1;
}


// 0002ce1c SelectObject

HGDIOBJ SelectObject(HDC hdc,HGDIOBJ h)

{
  HGDIOBJ pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = SelectObject(hdc,h);
  return pvVar1;
}


// 0002ce28 InvalidateRect

BOOL InvalidateRect(HWND hWnd,RECT *lpRect,BOOL bErase)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = InvalidateRect(hWnd,lpRect,bErase);
  return BVar1;
}


// 0002ce34 GetDC

HDC GetDC(HWND hWnd)

{
  HDC pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce38. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetDC(hWnd);
  return pHVar1;
}


// 0002ce40 OffsetRect

BOOL OffsetRect(LPRECT lprc,int dx,int dy)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = OffsetRect(lprc,dx,dy);
  return BVar1;
}


// 0002ce58 _wcsnicmp

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int _wcsnicmp(wchar_t *_Str1,wchar_t *_Str2,size_t _MaxCount)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = _wcsnicmp(_Str1,_Str2,_MaxCount);
  return iVar1;
}


// 0002ce64 DestroyMenu

BOOL DestroyMenu(HMENU hMenu)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DestroyMenu(hMenu);
  return BVar1;
}


// 0002ce70 DeleteDC

BOOL DeleteDC(HDC hdc)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = DeleteDC(hdc);
  return BVar1;
}


// 0002ce7c SaveDC

int SaveDC(HDC hdc)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce80. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = SaveDC(hdc);
  return iVar1;
}


// 0002ce88 RestoreDC

BOOL RestoreDC(HDC hdc,int nSavedDC)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ce8c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = RestoreDC(hdc,nSavedDC);
  return BVar1;
}


// 0002cea0 ExtTextOutW

BOOL ExtTextOutW(HDC hdc,int x,int y,UINT options,RECT *lprect,LPCWSTR lpString,UINT c,INT *lpDx)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cea4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ExtTextOutW(hdc,x,y,options,lprect,lpString,c,lpDx);
  return BVar1;
}


// 0002ceac DrawTextW

int DrawTextW(HDC hdc,LPCWSTR lpchText,int cchText,LPRECT lprc,UINT format)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ceb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = DrawTextW(hdc,lpchText,cchText,lprc,format);
  return iVar1;
}


// 0002ceb8 SetRectEmpty

BOOL SetRectEmpty(LPRECT lprc)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cebc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = SetRectEmpty(lprc);
  return BVar1;
}


// 0002cec4 LoadAcceleratorsW

HACCEL LoadAcceleratorsW(HINSTANCE hInstance,LPCWSTR lpTableName)

{
  HACCEL pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cec8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadAcceleratorsW(hInstance,lpTableName);
  return pHVar1;
}


// 0002ced0 TranslateAcceleratorW

int TranslateAcceleratorW(HWND hWnd,HACCEL hAccTable,LPMSG lpMsg)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ced4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = TranslateAcceleratorW(hWnd,hAccTable,lpMsg);
  return iVar1;
}


// 0002cedc SetCursor

HCURSOR SetCursor(HCURSOR hCursor)

{
  HCURSOR pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cee0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SetCursor(hCursor);
  return pHVar1;
}


// 0002cee8 IsWindow

BOOL IsWindow(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002ceec. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsWindow(hWnd);
  return BVar1;
}


// 0002cef4 LoadImageW

HANDLE LoadImageW(HINSTANCE hInst,LPCWSTR name,UINT type,int cx,int cy,UINT fuLoad)

{
  HANDLE pvVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cef8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pvVar1 = LoadImageW(hInst,name,type,cx,cy,fuLoad);
  return pvVar1;
}


// 0002cf00 LoadIconW

HICON LoadIconW(HINSTANCE hInstance,LPCWSTR lpIconName)

{
  HICON pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf04. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadIconW(hInstance,lpIconName);
  return pHVar1;
}


// 0002cf0c BringWindowToTop

BOOL BringWindowToTop(HWND hWnd)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = BringWindowToTop(hWnd);
  return BVar1;
}


// 0002cf18 LoadCursorW

HCURSOR LoadCursorW(HINSTANCE hInstance,LPCWSTR lpCursorName)

{
  HCURSOR pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadCursorW(hInstance,lpCursorName);
  return pHVar1;
}


// 0002cf24 GetSysColorBrush

HBRUSH GetSysColorBrush(int nIndex)

{
  HBRUSH pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = GetSysColorBrush(nIndex);
  return pHVar1;
}


// 0002cf30 GetDeviceCaps

int GetDeviceCaps(HDC hdc,int index)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf34. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = GetDeviceCaps(hdc,index);
  return iVar1;
}


// 0002cf3c CreateDialogIndirectParamW

HWND CreateDialogIndirectParamW
               (HINSTANCE hInstance,LPCDLGTEMPLATEW lpTemplate,HWND hWndParent,DLGPROC lpDialogFunc,
               LPARAM dwInitParam)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf40. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreateDialogIndirectParamW(hInstance,lpTemplate,hWndParent,lpDialogFunc,dwInitParam);
  return pHVar1;
}


// 0002cf48 VirtualProtect

BOOL VirtualProtect(LPVOID lpAddress,SIZE_T dwSize,DWORD flNewProtect,PDWORD lpflOldProtect)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = VirtualProtect(lpAddress,dwSize,flNewProtect,lpflOldProtect);
  return BVar1;
}


// 0002cf54 VirtualQuery

SIZE_T VirtualQuery(LPCVOID lpAddress,PMEMORY_BASIC_INFORMATION lpBuffer,SIZE_T dwLength)

{
  SIZE_T SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf58. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = VirtualQuery(lpAddress,lpBuffer,dwLength);
  return SVar1;
}


// 0002cf60 SetActiveWindow

HWND SetActiveWindow(HWND hWnd)

{
  HWND pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf64. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = SetActiveWindow(hWnd);
  return pHVar1;
}


// 0002cf78 ImageList_Add

int ImageList_Add(HIMAGELIST himl,HBITMAP hbmImage,HBITMAP hbmMask)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ImageList_Add(himl,hbmImage,hbmMask);
  return iVar1;
}


// 0002cf84 LoadBitmapW

HBITMAP LoadBitmapW(HINSTANCE hInstance,LPCWSTR lpBitmapName)

{
  HBITMAP pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = LoadBitmapW(hInstance,lpBitmapName);
  return pHVar1;
}


// 0002cf90 ImageList_GetImageCount

int ImageList_GetImageCount(HIMAGELIST himl)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cf94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = ImageList_GetImageCount(himl);
  return iVar1;
}


// 0002cf9c memcmp

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int memcmp(void *_Buf1,void *_Buf2,size_t _Size)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cfa0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = memcmp(_Buf1,_Buf2,_Size);
  return iVar1;
}


// 0002cfa8 ImageList_Destroy

BOOL ImageList_Destroy(HIMAGELIST himl)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cfac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = ImageList_Destroy(himl);
  return BVar1;
}


// 0002cfb4 IsClipboardFormatAvailable

BOOL IsClipboardFormatAvailable(UINT format)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cfb8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = IsClipboardFormatAvailable(format);
  return BVar1;
}


// 0002cfc0 MessageBeep

BOOL MessageBeep(UINT uType)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002cfc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = MessageBeep(uType);
  return BVar1;
}


// 0002cfcc SHSipInfo

void SHSipInfo(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002cfd0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHSipInfo();
  return;
}


// 0002cfd8 SHDoneButton

void SHDoneButton(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002cfdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHDoneButton();
  return;
}


// 0002cfe4 SHRecognizeGesture

void SHRecognizeGesture(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002cfe8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHRecognizeGesture();
  return;
}


// 0002cff0 SHHandleWMSettingChange

void SHHandleWMSettingChange(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002cff4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHHandleWMSettingChange();
  return;
}


// 0002cffc SHHandleWMActivate

void SHHandleWMActivate(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002d000. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHHandleWMActivate();
  return;
}


// 0002d008 SHSipPreference

void SHSipPreference(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002d00c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHSipPreference();
  return;
}


// 0002d014 SHInitDialog

void SHInitDialog(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002d018. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHInitDialog();
  return;
}


// 0002d020 SHCreateMenuBar

void SHCreateMenuBar(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002d024. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SHCreateMenuBar();
  return;
}


// 0002d02c entry

void entry(HINSTANCE param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  FUN_0002d120();
  WinMain(param_1,param_2,param_3,param_4);
  crt_exit();
  return;
}


// 0002d060 FUN_0002d060

undefined4 FUN_0002d060(undefined4 param_1)

{
  SIZE_T SVar1;
  HLOCAL pvVar2;
  
  SVar1 = LocalSize(DAT_002de58c);
  if (SVar1 < (uint)((int)DAT_002de588 + (4 - (int)DAT_002de58c))) {
    if (DAT_002de58c == (HLOCAL)0x0) {
      pvVar2 = LocalAlloc(0,0x10);
    }
    else {
      SVar1 = LocalSize(DAT_002de58c);
      pvVar2 = LocalReAlloc(DAT_002de58c,SVar1 + 0x10,2);
    }
    if (pvVar2 == (HLOCAL)0x0) {
      return 0;
    }
    DAT_002de588 = (undefined4 *)((int)pvVar2 + ((int)DAT_002de588 - (int)DAT_002de58c >> 2) * 4);
    DAT_002de58c = pvVar2;
  }
  *DAT_002de588 = param_1;
  DAT_002de588 = DAT_002de588 + 1;
  return param_1;
}


// 0002d108 atexit

undefined4 atexit(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0002d060();
  uVar2 = 0;
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


// 0002d120 FUN_0002d120

void FUN_0002d120(void)

{
  FUN_0002d150(&DAT_000433e0,&DAT_000433e4);
  FUN_0002d150(&DAT_00043370,&DAT_000433dc);
  return;
}


// 0002d150 FUN_0002d150

void FUN_0002d150(undefined4 *param_1,undefined4 *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if ((code *)*param_1 != (code *)0x0) {
      (*(code *)*param_1)();
    }
  }
  return;
}


// 0002d180 crt_exit

void crt_exit(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  DAT_002de584 = 0;
  puVar1 = DAT_002de58c;
  puVar2 = DAT_002de588;
  if (DAT_002de58c != (undefined4 *)0x0) {
    while (puVar2 = puVar2 + -1, puVar1 <= puVar2) {
      if ((code *)*puVar2 != (code *)0x0) {
        (*(code *)*puVar2)();
        puVar1 = DAT_002de58c;
      }
    }
  }
  FUN_0002d150(&DAT_000433e8,&DAT_000433ec);
  FUN_0002d150(&DAT_000433f0,g_monthNames);
  (*(code *)&SUB_f000f7f8)(0x42,param_1);
  return;
}


// 0002d240 InitCommonControls

void InitCommonControls(void)

{
                    /* WARNING: Could not recover jumptable at 0x0002d244. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  InitCommonControls();
  return;
}


// 0002d24c LocalSize

SIZE_T LocalSize(HLOCAL hMem)

{
  SIZE_T SVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0002d250. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SVar1 = LocalSize(hMem);
  return SVar1;
}


// 0002d258 CString_AssignChar

CString * CString_AssignChar(CString *this,wchar_t param_2)

{
  int aiStack_c [3];
  
  aiStack_c[0] = (int)param_2;
  CString_AssignCopy(this,1,aiStack_c);
  return this;
}


// 0002d27c CString_PlusChar

CString * CString_PlusChar(CString *this,CString *param_2,wchar_t param_3)

{
  CString local_20;
  int aiStack_8 [2];
  
  aiStack_8[0] = (int)param_3;
  local_20.str = g_afxEmptyString;
  CString_ConcatCopy(&local_20,*(int *)(param_2->str + -4),param_2->str,1,aiStack_8);
  CString_CopyCtor(this,&local_20);
  CString_Dtor(&local_20);
  return this;
}


// 0002d2dc CTime_GetCurrentTime

undefined4 * CTime_GetCurrentTime(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = time(0);
  *param_1 = uVar1;
  return param_1;
}


// 0002d2f8 CTime_GetLocalTm

Tm * CTime_GetLocalTm(undefined4 param_1,undefined1 *param_2)

{
  bool bVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  
  if (param_2 == (undefined1 *)0x0) {
    param_2 = (undefined1 *)FUN_0002a5c8();
  }
  else {
    puVar2 = (undefined1 *)FUN_0002a5c8();
    if (puVar2 == (undefined1 *)0x0) {
      param_2 = (undefined1 *)0x0;
    }
    else {
      iVar3 = 0x24;
      puVar5 = param_2;
      do {
        iVar4 = iVar3 + -1;
        *puVar5 = *puVar2;
        bVar1 = 0 < iVar3;
        puVar2 = puVar2 + 1;
        iVar3 = iVar4;
        puVar5 = puVar5 + 1;
      } while (iVar4 != 0 && bVar1);
    }
  }
  return (Tm *)param_2;
}


// 0002d340 FUN_0002d340

void FUN_0002d340(int param_1)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0xc) = 1;
  iVar1 = FUN_0002eec8(*(undefined4 *)(param_1 + 0x114),param_1 + 0x14,0x80);
  *(uint *)(param_1 + 0x10) = (uint)(iVar1 != 0);
  return;
}


// 0002d374 FUN_0002d374

undefined4 FUN_0002d374(int param_1,wchar_t *param_2,size_t param_3,undefined4 *param_4)

{
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = 0;
  }
  if (*(int *)(param_1 + 0xc) == 0) {
    FUN_0002d340(param_1);
  }
  if (*(int *)(param_1 + 0x10) == 0) {
    *param_2 = L'\0';
  }
  else {
    wcsncpy(param_2,(wchar_t *)(param_1 + 0x14),param_3);
  }
  return *(undefined4 *)(param_1 + 0x10);
}


// 0002d3cc FUN_0002d3cc

void FUN_0002d3cc(void)

{
  FUN_0002f108(&DAT_002dc648);
  return;
}


// 0002d3d8 FUN_0002d3d8

void FUN_0002d3d8(void)

{
  FUN_0002f108(&DAT_002dc530);
  return;
}


// 0002d3f8 FUN_0002d3f8

void FUN_0002d3f8(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  iVar1 = (**(code **)(**(int **)(iVar1 + 4) + 0x74))
                    (*(int **)(iVar1 + 4),*(undefined4 *)(param_2 + 0x10));
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0xb4))(param_1);
  }
  return;
}


// 0002d440 FUN_0002d440

undefined1 * FUN_0002d440(undefined1 *param_1)

{
  int iVar1;
  
  FUN_000346e8(param_1,0,0);
  *param_1 = 0xa8;
  param_1[1] = 0x20;
  param_1[2] = 4;
  param_1[3] = 0;
  memset(param_1 + 0x78,0,0x28);
  *(undefined2 *)(param_1 + 0xa4) = 0;
  *(undefined2 *)(param_1 + 0x1a4) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0x100;
  if ((DAT_002de53c == 0) && (iVar1 = FUN_00034bec(), iVar1 != 0)) {
    *(uint *)(param_1 + 0x84) = *(uint *)(param_1 + 0x84) | 0x80;
  }
  *(undefined1 **)(param_1 + 0x88) = param_1 + 0xa4;
  *(code **)(param_1 + 0x98) = FUN_0002b44c;
  *(undefined4 *)(param_1 + 0x78) = 0x28;
  *(undefined4 *)(param_1 + 0x2a4) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 1;
  return param_1;
}


// 0002d51c FUN_0002d51c

void FUN_0002d51c(int *param_1)

{
  if (param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 4))(param_1,1);
  }
  return;
}


// 0002d53c FUN_0002d53c

bool FUN_0002d53c(int *param_1,int param_2,wchar_t *param_3,wchar_t *param_4,uint param_5,
                 int param_6)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0) {
    iVar1 = 0x700b;
  }
  else {
    iVar1 = 0x700a;
  }
  param_1[0x16] = iVar1;
  *(undefined2 *)(param_1 + 0x24) = 0x80;
  *(undefined2 *)((int)param_1 + 0x92) = 0x80;
  param_1[0x23] = (int)(param_1 + 0x69);
  param_1[0x21] = param_1[0x21] | param_5;
  if (param_6 == 0) {
    iVar1 = FUN_0002acc0();
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x1c);
    }
    param_1[0x1f] = iVar1;
  }
  else {
    param_1[0x1f] = *(int *)(param_6 + 0x1c);
  }
  if (param_3 != (wchar_t *)0x0) {
    wcsncpy((wchar_t *)(param_1 + 0x29),param_3,0x80);
  }
  if (param_4 != (wchar_t *)0x0) {
    wcsncpy((wchar_t *)(param_1 + 0x69),param_4,0x80);
  }
  FUN_0003020c(param_1);
  if (param_2 == 0) {
    iVar1 = FUN_0002c520(param_1 + 0x1e);
  }
  else {
    iVar1 = FUN_0002c264();
  }
  iVar2 = FUN_00030238();
  if (iVar2 == 0) {
    (**(code **)(*param_1 + 0x9c))(param_1);
  }
  return iVar1 != 0;
}


// 0002d62c FUN_0002d62c

int FUN_0002d62c(int param_1)

{
  return param_1 + -0x78;
}


// 0002d634 FUN_0002d634

undefined4 FUN_0002d634(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0002ff50();
  if (iVar1 == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x41e,0x14,0);
    uVar2 = 0;
  }
  return uVar2;
}


// 0002d670 FUN_0002d670

void FUN_0002d670(int param_1,WPARAM param_2)

{
  int iVar1;
  
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x1002,param_2,0);
  iVar1 = FUN_0002d8dc();
  if (iVar1 != 0) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x1003,param_2,0);
  }
  return;
}


// 0002d6b8 FUN_0002d6b8

void FUN_0002d6b8(undefined4 param_1)

{
  FUN_0002d670(param_1,0);
  FUN_0002d670(param_1,1);
  FUN_0002d670(param_1,2);
  FUN_00030608(param_1);
  return;
}


// 0002d6ec FUN_0002d6ec

void FUN_0002d6ec(int param_1,WPARAM param_2)

{
  int iVar1;
  
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x1108,param_2,0);
  iVar1 = FUN_0002d8dc();
  if (iVar1 != 0) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x1109,param_2,0);
  }
  return;
}


// 0002d734 FUN_0002d734

void FUN_0002d734(int param_1)

{
  int *piVar1;
  undefined4 extraout_r2;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  FUN_0002d6ec(param_1,0);
  FUN_0002d6ec(param_1,2);
  piVar1 = *(int **)(param_1 + 0x38);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(piVar1,1,extraout_r2,*(code **)(*piVar1 + 4),unaff_r4,unaff_lr);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_000336d0(param_1,0);
  }
  FUN_0002ff50(param_1);
  return;
}


// 0002d75c FUN_0002d75c

void FUN_0002d75c(int param_1)

{
  int iVar1;
  int *piVar2;
  
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x1302,0,0);
  iVar1 = FUN_0002d8dc();
  if (iVar1 != 0) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x1303,0,0);
  }
  piVar2 = *(int **)(param_1 + 0x38);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 4))(piVar2,1);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_000336d0(param_1,0);
  }
  FUN_0002ff50(param_1);
  return;
}


// 0002d7a8 FUN_0002d7a8

undefined4 FUN_0002d7a8(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f52c();
  if ((*(int *)(iVar1 + 0x24) == 0) && (param_1 != 0)) {
    iVar2 = operator_new(0x48);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00033818(iVar2,&CImageList::classCImageList,4,1);
    }
    *(undefined4 *)(iVar1 + 0x24) = uVar3;
  }
  return *(undefined4 *)(iVar1 + 0x24);
}


// 0002d858 FUN_0002d858

void FUN_0002d858(undefined1 *param_1)

{
  *param_1 = 0x78;
  param_1[1] = 0x1a;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0002d8bc();
  return;
}


// 0002d880 FUN_0002d880

int FUN_0002d880(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 4);
  if ((iVar2 != 0) && (iVar1 = FUN_0002d7a8(0), iVar1 != 0)) {
    FUN_0002e394(iVar1 + 4,*(undefined4 *)(param_1 + 4));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  return iVar2;
}


// 0002d8bc FUN_0002d8bc

void FUN_0002d8bc(int param_1)

{
  HIMAGELIST himl;
  
  if (*(int *)(param_1 + 4) != 0) {
    himl = (HIMAGELIST)FUN_0002d880(param_1);
    ImageList_Destroy(himl);
  }
  return;
}


// 0002d8dc FUN_0002d8dc

void FUN_0002d8dc(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0002d7a8(0);
  if (iVar1 != 0) {
    FUN_0002e298(iVar1 + 4,param_1);
  }
  return;
}


// 0002d904 CPlex_Create

void CPlex_Create(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)operator_new(param_2 * param_3 + 4);
  *puVar1 = *param_1;
  *param_1 = puVar1;
  return;
}


// 0002d928 CPlex_FreeDataChain

void CPlex_FreeDataChain(undefined4 *param_1)

{
  void *pvVar1;
  
  while (param_1 != (void *)0x0) {
    pvVar1 = (void *)*param_1;
    free(param_1);
    param_1 = pvVar1;
  }
  return;
}


// 0002d9b4 FUN_0002d9b4

void FUN_0002d9b4(int param_1)

{
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  CPlex_FreeDataChain(*(undefined4 *)(param_1 + 0x14));
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}


// 0002d9e0 FUN_0002d9e0

void FUN_0002d9e0(undefined1 *param_1)

{
  *param_1 = 0x38;
  param_1[1] = 1;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0002d9b4();
  return;
}


// 0002da08 FUN_0002da08

void FUN_0002da08(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    iVar1 = CPlex_Create(param_1 + 0x14,*(undefined4 *)(param_1 + 0x18),0xc);
    iVar2 = *(int *)(param_1 + 0x18);
    puVar3 = (undefined4 *)(iVar2 * 0xc + iVar1 + -8);
    if (-1 < iVar2 + -1) {
      do {
        iVar2 = iVar2 + -1;
        *puVar3 = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 **)(param_1 + 0x10) = puVar3;
        puVar3 = puVar3 + -3;
      } while (iVar2 != 0);
    }
  }
  puVar3 = *(undefined4 **)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x10) = *puVar3;
  puVar3[1] = param_2;
  *puVar3 = param_3;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  puVar3[2] = 0;
  return;
}


// 0002daa4 FUN_0002daa4

void FUN_0002daa4(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  *param_2 = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 **)(param_1 + 0x10) = param_2;
  iVar1 = *(int *)(param_1 + 0xc) + -1;
  *(int *)(param_1 + 0xc) = iVar1;
  if (iVar1 == 0) {
    FUN_0002d9b4();
  }
  return;
}


// 0002dac8 FUN_0002dac8

void FUN_0002dac8(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0002da08(param_1,*(undefined4 *)(param_1 + 8),0);
  *(undefined4 *)(iVar1 + 8) = param_2;
  if (*(int **)(param_1 + 8) == (int *)0x0) {
    *(int *)(param_1 + 4) = iVar1;
  }
  else {
    **(int **)(param_1 + 8) = iVar1;
  }
  *(int *)(param_1 + 8) = iVar1;
  return;
}


// 0002dafc FUN_0002dafc

int FUN_0002dafc(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = **(int **)(param_1 + 4);
  iVar2 = (*(int **)(param_1 + 4))[2];
  *(int *)(param_1 + 4) = iVar1;
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 8) = 0;
  }
  else {
    *(undefined4 *)(iVar1 + 4) = 0;
  }
  FUN_0002daa4();
  return iVar2;
}


// 0002db2c FUN_0002db2c

void FUN_0002db2c(int param_1,int *param_2)

{
  if (param_2 == *(int **)(param_1 + 4)) {
    *(int *)(param_1 + 4) = *param_2;
  }
  else {
    *(int *)param_2[1] = *param_2;
  }
  if (param_2 == *(int **)(param_1 + 8)) {
    *(int *)(param_1 + 8) = param_2[1];
  }
  else {
    *(int *)(*param_2 + 4) = param_2[1];
  }
  FUN_0002daa4();
  return;
}


// 0002db68 FUN_0002db68

undefined4 * FUN_0002db68(int param_1,int param_2,undefined4 *param_3)

{
  if (param_3 == (undefined4 *)0x0) {
    param_3 = *(undefined4 **)(param_1 + 4);
  }
  else {
    param_3 = (undefined4 *)*param_3;
  }
  while( true ) {
    if (param_3 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    if (param_3[2] == param_2) break;
    param_3 = (undefined4 *)*param_3;
  }
  return param_3;
}


// 0002db9c FUN_0002db9c

void FUN_0002db9c(undefined1 *param_1)

{
  *param_1 = 0x98;
  param_1[1] = 0x18;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  param_1[2] = 4;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  param_1[3] = 0;
  return;
}


// 0002dbfc FUN_0002dbfc

void FUN_0002dbfc(undefined1 *param_1)

{
  *param_1 = 0x98;
  param_1[1] = 0x18;
  param_1[2] = 4;
  param_1[3] = 0;
  free(*(void **)(param_1 + 4));
  return;
}


// 0002dc28 FUN_0002dc28

void FUN_0002dc28(int param_1,int param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  
  if (param_3 != -1) {
    *(int *)(param_1 + 0x10) = param_3;
  }
  if (param_2 == 0) {
    free(*(void **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    return;
  }
  if (*(int *)(param_1 + 4) == 0) {
    pvVar1 = (void *)operator_new(param_2 << 2);
    *(void **)(param_1 + 4) = pvVar1;
    memset(pvVar1,0,param_2 << 2);
    *(int *)(param_1 + 0xc) = param_2;
    goto LAB_0002dd54;
  }
  if (param_2 <= *(int *)(param_1 + 0xc)) {
    iVar2 = *(int *)(param_1 + 8);
    if (iVar2 < param_2) {
      memset((void *)(*(int *)(param_1 + 4) + iVar2 * 4),0,(param_2 - iVar2) * 4);
    }
    goto LAB_0002dd54;
  }
  iVar2 = *(int *)(param_1 + 0x10);
  if (iVar2 == 0) {
    iVar2 = *(int *)(param_1 + 8);
    if (iVar2 < 0) {
      iVar2 = iVar2 + 7;
    }
    iVar2 = iVar2 >> 3;
    if (iVar2 < 4) {
LAB_0002dd00:
      iVar2 = 4;
    }
    else if (iVar2 < 0x401) {
      if (iVar2 < 4) goto LAB_0002dd00;
    }
    else {
      iVar2 = 0x400;
    }
  }
  iVar2 = *(int *)(param_1 + 0xc) + iVar2;
  if (iVar2 <= param_2) {
    iVar2 = param_2;
  }
  pvVar1 = (void *)operator_new(iVar2 << 2);
  memmove(pvVar1,*(void **)(param_1 + 4),*(int *)(param_1 + 8) << 2);
  memset((void *)((int)pvVar1 + *(int *)(param_1 + 8) * 4),0,(param_2 - *(int *)(param_1 + 8)) * 4);
  free(*(void **)(param_1 + 4));
  *(void **)(param_1 + 4) = pvVar1;
  *(int *)(param_1 + 0xc) = iVar2;
LAB_0002dd54:
  *(int *)(param_1 + 8) = param_2;
  return;
}


// 0002dd5c FUN_0002dd5c

void FUN_0002dd5c(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  if (param_2 < iVar1) {
    FUN_0002dc28(param_1,iVar1 + param_4,0xffffffff);
    memmove((void *)(*(int *)(param_1 + 4) + (param_2 + param_4) * 4),
            (void *)(*(int *)(param_1 + 4) + param_2 * 4),(param_2 * 0x3fffffff + iVar1) * 4);
    memset((void *)(*(int *)(param_1 + 4) + param_2 * 4),0,param_4 << 2);
  }
  else {
    FUN_0002dc28(param_1,param_2 + param_4,0xffffffff);
  }
  if (param_4 != 0) {
    param_2 = param_2 << 2;
    do {
      param_4 = param_4 + -1;
      *(undefined4 *)(*(int *)(param_1 + 4) + param_2) = param_3;
      param_2 = param_2 + 4;
    } while (param_4 != 0);
  }
  return;
}


// 0002ddf8 FUN_0002ddf8

void FUN_0002ddf8(undefined1 *param_1)

{
  *param_1 = 0x88;
  param_1[1] = 0x1a;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  param_1[2] = 4;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  param_1[3] = 0;
  return;
}


// 0002de58 FUN_0002de58

void FUN_0002de58(undefined1 *param_1)

{
  *param_1 = 0x88;
  param_1[1] = 0x1a;
  param_1[2] = 4;
  param_1[3] = 0;
  free(*(void **)(param_1 + 4));
  return;
}


// 0002de84 FUN_0002de84

void FUN_0002de84(int param_1,int param_2,int param_3)

{
  void *pvVar1;
  int iVar2;
  
  if (param_3 != -1) {
    *(int *)(param_1 + 0x10) = param_3;
  }
  if (param_2 == 0) {
    free(*(void **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
    *(undefined4 *)(param_1 + 8) = 0;
    return;
  }
  if (*(int *)(param_1 + 4) == 0) {
    pvVar1 = (void *)operator_new(param_2 << 2);
    *(void **)(param_1 + 4) = pvVar1;
    memset(pvVar1,0,param_2 << 2);
    *(int *)(param_1 + 0xc) = param_2;
    goto LAB_0002dfb0;
  }
  if (param_2 <= *(int *)(param_1 + 0xc)) {
    iVar2 = *(int *)(param_1 + 8);
    if (iVar2 < param_2) {
      memset((void *)(*(int *)(param_1 + 4) + iVar2 * 4),0,(param_2 - iVar2) * 4);
    }
    goto LAB_0002dfb0;
  }
  iVar2 = *(int *)(param_1 + 0x10);
  if (iVar2 == 0) {
    iVar2 = *(int *)(param_1 + 8);
    if (iVar2 < 0) {
      iVar2 = iVar2 + 7;
    }
    iVar2 = iVar2 >> 3;
    if (iVar2 < 4) {
LAB_0002df5c:
      iVar2 = 4;
    }
    else if (iVar2 < 0x401) {
      if (iVar2 < 4) goto LAB_0002df5c;
    }
    else {
      iVar2 = 0x400;
    }
  }
  iVar2 = *(int *)(param_1 + 0xc) + iVar2;
  if (iVar2 <= param_2) {
    iVar2 = param_2;
  }
  pvVar1 = (void *)operator_new(iVar2 << 2);
  memmove(pvVar1,*(void **)(param_1 + 4),*(int *)(param_1 + 8) << 2);
  memset((void *)((int)pvVar1 + *(int *)(param_1 + 8) * 4),0,(param_2 - *(int *)(param_1 + 8)) * 4);
  free(*(void **)(param_1 + 4));
  *(void **)(param_1 + 4) = pvVar1;
  *(int *)(param_1 + 0xc) = iVar2;
LAB_0002dfb0:
  *(int *)(param_1 + 8) = param_2;
  return;
}


// 0002dfb8 FUN_0002dfb8

void FUN_0002dfb8(int param_1,CArchive *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if ((param_2->mode & 1) == 0) {
    CArchive_WriteCount(param_2,*(uint *)(param_1 + 8));
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 8)) {
      do {
        FUN_00037450(param_2,*(undefined4 *)(*(int *)(param_1 + 4) + iVar4 * 4));
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 8));
    }
  }
  else {
    uVar1 = CArchive_ReadCount(param_2);
    FUN_0002de84(param_1,uVar1,0xffffffff);
    iVar4 = 0;
    if (0 < *(int *)(param_1 + 8)) {
      do {
        iVar3 = *(int *)(param_1 + 4);
        uVar2 = FUN_00037530(param_2,0);
        *(undefined4 *)(iVar3 + iVar4 * 4) = uVar2;
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(param_1 + 8));
    }
  }
  return;
}


// 0002e060 FUN_0002e060

void FUN_0002e060(undefined1 *param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  *param_1 = 0x10;
  param_1[1] = 1;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  param_1[2] = 4;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 8) = 0x11;
  return;
}


// 0002e0cc FUN_0002e0cc

void FUN_0002e0cc(int param_1,int param_2,int param_3)

{
  void *_Dst;
  
  if (*(void **)(param_1 + 4) != (void *)0x0) {
    free(*(void **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  if (param_3 != 0) {
    _Dst = (void *)operator_new(param_2 << 2);
    *(void **)(param_1 + 4) = _Dst;
    memset(_Dst,0,param_2 << 2);
  }
  *(int *)(param_1 + 8) = param_2;
  return;
}


// 0002e120 FUN_0002e120

void FUN_0002e120(int param_1)

{
  if (*(void **)(param_1 + 4) != (void *)0x0) {
    free(*(void **)(param_1 + 4));
    *(undefined4 *)(param_1 + 4) = 0;
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  CPlex_FreeDataChain(*(undefined4 *)(param_1 + 0x14));
  *(undefined4 *)(param_1 + 0x14) = 0;
  return;
}


// 0002e158 FUN_0002e158

void FUN_0002e158(undefined1 *param_1)

{
  *param_1 = 0x10;
  param_1[1] = 1;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0002e120();
  return;
}


// 0002e180 FUN_0002e180

void FUN_0002e180(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 0x10) == 0) {
    iVar1 = CPlex_Create(param_1 + 0x14,*(undefined4 *)(param_1 + 0x18),0xc);
    iVar2 = *(int *)(param_1 + 0x18);
    puVar3 = (undefined4 *)(iVar2 * 0xc + iVar1 + -8);
    if (-1 < iVar2 + -1) {
      do {
        iVar2 = iVar2 + -1;
        *puVar3 = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 **)(param_1 + 0x10) = puVar3;
        puVar3 = puVar3 + -3;
      } while (iVar2 != 0);
    }
  }
  puVar3 = *(undefined4 **)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x10) = *puVar3;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  puVar3[1] = 0;
  puVar3[2] = 0;
  return;
}


// 0002e210 FUN_0002e210

void FUN_0002e210(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  *param_2 = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 **)(param_1 + 0x10) = param_2;
  iVar1 = *(int *)(param_1 + 0xc) + -1;
  *(int *)(param_1 + 0xc) = iVar1;
  if (iVar1 == 0) {
    FUN_0002e120();
  }
  return;
}


// 0002e234 FUN_0002e234

undefined4 * FUN_0002e234(int param_1,uint param_2,int *param_3)

{
  undefined4 *puVar1;
  int extraout_r1;
  
  __rt_udiv(*(undefined4 *)(param_1 + 8),param_2 >> 4);
  *param_3 = extraout_r1;
  if (*(int *)(param_1 + 4) != 0) {
    for (puVar1 = *(undefined4 **)(*(int *)(param_1 + 4) + extraout_r1 * 4);
        puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      if (puVar1[1] == param_2) {
        return puVar1;
      }
    }
  }
  return (undefined4 *)0x0;
}


// 0002e298 FUN_0002e298

undefined4 FUN_0002e298(int param_1,uint param_2)

{
  undefined4 *puVar1;
  int extraout_r1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 != 0) {
    __rt_udiv(*(undefined4 *)(param_1 + 8),param_2 >> 4);
    for (puVar1 = *(undefined4 **)(iVar2 + extraout_r1 * 4); puVar1 != (undefined4 *)0x0;
        puVar1 = (undefined4 *)*puVar1) {
      if (puVar1[1] == param_2) {
        return puVar1[2];
      }
    }
  }
  return 0;
}


// 0002e2f8 FUN_0002e2f8

bool FUN_0002e2f8(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined1 auStack_c [4];
  
  iVar1 = FUN_0002e234(param_1,param_2,auStack_c);
  if (iVar1 != 0) {
    *param_3 = *(undefined4 *)(iVar1 + 8);
  }
  return iVar1 != 0;
}


// 0002e328 FUN_0002e328

undefined4 * FUN_0002e328(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int local_10;
  
  puVar1 = (undefined4 *)FUN_0002e234(param_1,param_2,&local_10);
  if (puVar1 == (undefined4 *)0x0) {
    if (*(int *)(param_1 + 4) == 0) {
      FUN_0002e0cc(param_1,*(undefined4 *)(param_1 + 8),1);
    }
    puVar1 = (undefined4 *)FUN_0002e180(param_1);
    puVar1[1] = param_2;
    *puVar1 = *(undefined4 *)(*(int *)(param_1 + 4) + local_10 * 4);
    *(undefined4 **)(*(int *)(param_1 + 4) + local_10 * 4) = puVar1;
  }
  return puVar1 + 2;
}


// 0002e394 FUN_0002e394

undefined4 FUN_0002e394(int param_1,uint param_2)

{
  undefined4 *puVar1;
  int extraout_r1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 4);
  if (iVar3 != 0) {
    __rt_udiv(*(undefined4 *)(param_1 + 8),param_2 >> 4);
    puVar1 = (undefined4 *)(iVar3 + extraout_r1 * 4);
    for (puVar2 = (undefined4 *)*puVar1; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2
        ) {
      if (puVar2[1] == param_2) {
        *puVar1 = *puVar2;
        FUN_0002e210(param_1);
        return 1;
      }
      puVar1 = puVar2;
    }
  }
  return 0;
}


// 0002e410 FUN_0002e410

void FUN_0002e410(int param_1,int *param_2,int *param_3,int *param_4)

{
  int *piVar1;
  uint uVar2;
  int extraout_r1;
  int *piVar3;
  uint uVar4;
  int iVar5;
  
  piVar3 = (int *)*param_2;
  if (piVar3 == (int *)0xffffffff) {
    uVar2 = 0;
    if (*(uint *)(param_1 + 8) != 0) {
      piVar1 = *(int **)(param_1 + 4);
      do {
        piVar3 = (int *)*piVar1;
        if (piVar3 != (int *)0x0) break;
        uVar2 = uVar2 + 1;
        piVar1 = piVar1 + 1;
      } while (uVar2 < *(uint *)(param_1 + 8));
    }
  }
  iVar5 = *piVar3;
  if (iVar5 == 0) {
    uVar4 = *(uint *)(param_1 + 8);
    __rt_udiv(uVar4,(uint)piVar3[1] >> 4);
    uVar2 = extraout_r1 + 1;
    if (uVar2 < uVar4) {
      piVar1 = (int *)(*(int *)(param_1 + 4) + uVar2 * 4);
      do {
        iVar5 = *piVar1;
        if (iVar5 != 0) break;
        uVar2 = uVar2 + 1;
        piVar1 = piVar1 + 1;
      } while (uVar2 < uVar4);
    }
  }
  *param_2 = iVar5;
  *param_3 = piVar3[1];
  *param_4 = piVar3[2];
  return;
}


// 0002e4dc CString_CopyCtor

int * CString_CopyCtor(CString *this,CString *param_2)

{
  wchar_t *pwVar1;
  
  pwVar1 = param_2->str;
  if (*(int *)(pwVar1 + -6) < 0) {
    this->str = g_afxEmptyString;
    CString_AssignW(this,param_2->str);
  }
  else {
    this->str = pwVar1;
    InterlockedIncrement((LONG *)(pwVar1 + -6));
  }
  return (int *)this;
}


// 0002e528 CString_AllocBuffer

void CString_AllocBuffer(CString *this,int param_2)

{
  undefined4 *puVar1;
  
  if (param_2 == 0) {
    this->str = g_afxEmptyString;
  }
  else {
    puVar1 = (undefined4 *)operator_new((param_2 + 7) * 2);
    *puVar1 = 1;
    puVar1[2] = param_2;
    *(undefined2 *)((int)puVar1 + (param_2 + 6) * 2) = 0;
    puVar1[1] = param_2;
    this->str = (wchar_t *)(puVar1 + 3);
  }
  return;
}


// 0002e584 free

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *_Memory)

{
                    /* WARNING: Could not recover jumptable at 0x0002c9e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(_Memory);
  return;
}


// 0002e588 CString_Release

void CString_Release(CString *this)

{
  LONG LVar1;
  
  if (this->str + -6 != DAT_00043eb8) {
    LVar1 = InterlockedDecrement((LONG *)(this->str + -6));
    if (LVar1 < 1) {
      free(this->str + -6);
    }
    this->str = g_afxEmptyString;
  }
  return;
}


// 0002e5d8 FUN_0002e5d8

void FUN_0002e5d8(LONG *param_1)

{
  LONG LVar1;
  
  if ((param_1 != DAT_00043eb8) && (LVar1 = InterlockedDecrement(param_1), LVar1 < 1)) {
    free(param_1);
  }
  return;
}


// 0002e60c FUN_0002e60c

void FUN_0002e60c(CString *param_1)

{
  if (*(int *)(param_1->str + -4) != 0) {
    if (*(int *)(param_1->str + -6) < 0) {
      CString_AssignW(param_1,(wchar_t *)&afxChNil);
    }
    else {
      CString_Release(param_1);
    }
  }
  return;
}


// 0002e644 FUN_0002e644

void FUN_0002e644(CString *param_1)

{
  wchar_t *_Src;
  
  _Src = param_1->str;
  if (1 < *(int *)(_Src + -6)) {
    CString_Release(param_1);
    CString_AllocBuffer(param_1,*(int *)(_Src + -4));
    memmove(param_1->str,_Src,(*(int *)(_Src + -4) + 1) * 2);
  }
  return;
}


// 0002e688 FUN_0002e688

void FUN_0002e688(CString *param_1,int param_2)

{
  if ((1 < *(int *)(param_1->str + -6)) || (*(int *)(param_1->str + -2) < param_2)) {
    CString_Release(param_1);
    CString_AllocBuffer(param_1,param_2);
  }
  return;
}


// 0002e6c8 CString_Dtor

void CString_Dtor(CString *this)

{
  LONG LVar1;
  
  if ((this->str + -6 != DAT_00043eb8) &&
     (LVar1 = InterlockedDecrement((LONG *)(this->str + -6)), LVar1 < 1)) {
    free(this->str + -6);
  }
  return;
}


// 0002e708 CString_CtorW

CString * CString_CtorW(CString *this,wchar_t *param_2)

{
  size_t sVar1;
  
  this->str = g_afxEmptyString;
  if (param_2 != (wchar_t *)0x0) {
    if ((uint)param_2 >> 0x10 == 0) {
      FUN_0002ee30(this,(uint)param_2 & 0xffff);
    }
    else {
      sVar1 = wcslen(param_2);
      if (sVar1 != 0) {
        CString_AllocBuffer(this,sVar1);
        memmove(this->str,param_2,sVar1 << 1);
      }
    }
  }
  return this;
}


// 0002e77c CString_CtorA

CString * CString_CtorA(CString *this,char *param_2)

{
  size_t sVar1;
  
  this->str = g_afxEmptyString;
  if (param_2 == (char *)0x0) {
    sVar1 = 0;
  }
  else {
    sVar1 = strlen(param_2);
  }
  if (sVar1 != 0) {
    CString_AllocBuffer(this,sVar1);
    AtoW(this->str,param_2,sVar1 + 1);
    CString_ReleaseBuffer(this,0xffffffff);
  }
  return this;
}


// 0002e7ec CString_AssignCopy

void CString_AssignCopy(CString *this,int param_2,void *param_3)

{
  FUN_0002e688();
  memmove(this->str,param_3,param_2 << 1);
  *(int *)(this->str + -4) = param_2;
  this->str[param_2] = L'\0';
  return;
}


// 0002e82c CString_Assign

CString * CString_Assign(CString *this,CString *param_2)

{
  wchar_t *pwVar1;
  wchar_t *pwVar2;
  
  pwVar1 = this->str;
  pwVar2 = param_2->str;
  if (pwVar1 != pwVar2) {
    if (((*(int *)(pwVar1 + -6) < 0) && (pwVar1 + -6 != DAT_00043eb8)) ||
       (*(int *)(pwVar2 + -6) < 0)) {
      CString_AssignCopy(this,*(int *)(pwVar2 + -4),pwVar2);
    }
    else {
      CString_Release(this);
      pwVar1 = param_2->str;
      this->str = pwVar1;
      InterlockedIncrement((LONG *)(pwVar1 + -6));
    }
  }
  return this;
}


// 0002e8a8 CString_AssignW

CString * CString_AssignW(CString *this,wchar_t *param_2)

{
  size_t sVar1;
  
  if (param_2 == (wchar_t *)0x0) {
    sVar1 = 0;
  }
  else {
    sVar1 = wcslen(param_2);
  }
  CString_AssignCopy(this,sVar1,param_2);
  return this;
}


// 0002e8dc CString_AssignA

undefined4 * CString_AssignA(CString *this,char *param_2)

{
  size_t sVar1;
  
  if (param_2 == (char *)0x0) {
    sVar1 = 0;
  }
  else {
    sVar1 = strlen(param_2);
  }
  FUN_0002e688(this,sVar1);
  AtoW(this->str,param_2,sVar1 + 1);
  CString_ReleaseBuffer(this,0xffffffff);
  return this;
}


// 0002e934 CString_ConcatCopy

void CString_ConcatCopy(CString *this,int param_2,void *param_3,int param_4,void *param_5)

{
  if (param_2 + param_4 != 0) {
    CString_AllocBuffer(this,param_2 + param_4);
    memmove(this->str,param_3,param_2 << 1);
    memmove(this->str + param_2,param_5,param_4 << 1);
  }
  return;
}


// 0002e97c CString_Plus

CString * CString_Plus(CString *this,CString *param_2,CString *param_3)

{
  CString local_c;
  
  local_c.str = g_afxEmptyString;
  CString_ConcatCopy(&local_c,*(int *)(param_2->str + -4),param_2->str,*(int *)(param_3->str + -4),
                     param_3->str);
  CString_CopyCtor(this,&local_c);
  CString_Dtor(&local_c);
  return this;
}


// 0002e9d4 CString_PlusW

CString * CString_PlusW(CString *this,CString *param_2,wchar_t *param_3)

{
  size_t sVar1;
  CString local_14;
  
  local_14.str = g_afxEmptyString;
  if (param_3 == (wchar_t *)0x0) {
    sVar1 = 0;
  }
  else {
    sVar1 = wcslen(param_3);
  }
  CString_ConcatCopy(&local_14,*(int *)(param_2->str + -4),param_2->str,sVar1,param_3);
  CString_CopyCtor(this,&local_14);
  CString_Dtor(&local_14);
  return this;
}


// 0002ea40 CString_ConcatInPlace

void CString_ConcatInPlace(CString *this,int param_2,void *param_3)

{
  wchar_t *pwVar1;
  
  if (param_2 != 0) {
    pwVar1 = this->str;
    if ((*(int *)(pwVar1 + -6) < 2) && (*(int *)(pwVar1 + -4) + param_2 <= *(int *)(pwVar1 + -2))) {
      memmove(pwVar1 + *(int *)(pwVar1 + -4),param_3,param_2 << 1);
      *(int *)(this->str + -4) = *(int *)(this->str + -4) + param_2;
      this->str[*(int *)(this->str + -4)] = L'\0';
    }
    else {
      CString_ConcatCopy(this,*(int *)(pwVar1 + -4),pwVar1,param_2,param_3);
      FUN_0002e5d8(pwVar1 + -6);
    }
  }
  return;
}


// 0002eae0 CString_AppendChar

CString * CString_AppendChar(CString *this,wchar_t param_2)

{
  int aiStack_c [3];
  
  aiStack_c[0] = (int)param_2;
  CString_ConcatInPlace(this,1,aiStack_c);
  return this;
}


// 0002eb04 CString_Append

CString * CString_Append(CString *this,CString *param_2)

{
  CString_ConcatInPlace(this,*(int *)(param_2->str + -4),param_2->str);
  return this;
}


// 0002eb20 CString_GetBuffer

wchar_t * CString_GetBuffer(CString *this,int param_2)

{
  wchar_t *_Src;
  int iVar1;
  
  _Src = this->str;
  if ((1 < *(int *)(_Src + -6)) || (*(int *)(_Src + -2) < param_2)) {
    iVar1 = *(int *)(_Src + -4);
    if (param_2 < iVar1) {
      param_2 = iVar1;
    }
    CString_AllocBuffer(this,param_2);
    memmove(this->str,_Src,(iVar1 + 1) * 2);
    *(int *)(this->str + -4) = iVar1;
    FUN_0002e5d8(_Src + -6);
  }
  return this->str;
}


// 0002eb88 CString_ReleaseBuffer

void CString_ReleaseBuffer(CString *this,size_t param_2)

{
  FUN_0002e644();
  if (param_2 == 0xffffffff) {
    param_2 = wcslen(this->str);
  }
  *(size_t *)(this->str + -4) = param_2;
  this->str[param_2] = L'\0';
  return;
}


// 0002ebcc FUN_0002ebcc

wchar_t * FUN_0002ebcc(CString *param_1,int param_2)

{
  CString_GetBuffer(param_1,param_2);
  *(int *)(param_1->str + -4) = param_2;
  param_1->str[param_2] = L'\0';
  return param_1->str;
}


// 0002ebfc CString_MakeUpper

void CString_MakeUpper(CString *this)

{
  FUN_0002e644();
                    /* WARNING: Could not recover jumptable at 0x0002c9c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  CharUpperW(this->str);
  return;
}


// 0002ec14 CString_SetAt

void CString_SetAt(CString *this,int param_2,wchar_t param_3)

{
  FUN_0002e644();
  this->str[param_2] = param_3;
  return;
}


// 0002ec38 AtoW

int AtoW(LPWSTR param_1,LPCSTR param_2,int param_3)

{
  int iVar1;
  
  if ((param_3 == 0) && (param_1 != (LPWSTR)0x0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = MultiByteToWideChar(0,0,param_2,-1,param_1,param_3);
    if (0 < iVar1) {
      param_1[iVar1 + -1] = L'\0';
    }
  }
  return iVar1;
}


// 0002ec8c FUN_0002ec8c

undefined4 FUN_0002ec8c(void)

{
  FUN_0002d3cc();
  return 0;
}


// 0002ec9c set_new_handler

undefined4 set_new_handler(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00043ebc;
  DAT_00043ebc = param_1;
  return uVar1;
}


// 0002ecb4 operator_new

void * operator_new(size_t param_1)

{
  void *pvVar1;
  int iVar2;
  
  pvVar1 = malloc(param_1);
  while (((pvVar1 == (void *)0x0 && (DAT_00043ebc != (code *)0x0)) &&
         (iVar2 = (*DAT_00043ebc)(param_1), iVar2 != 0))) {
    pvVar1 = malloc(param_1);
  }
  return pvVar1;
}


// 0002ed0c free

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *_Memory)

{
                    /* WARNING: Could not recover jumptable at 0x0002c9e8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  free(_Memory);
  return;
}


// 0002ed1c FUN_0002ed1c

void FUN_0002ed1c(undefined4 *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)*param_1)();
  thunk_FUN_0002ee18(uVar1,param_2);
  return;
}


// 0002ed40 FUN_0002ed40

int FUN_0002ed40(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if ((param_2 == 0) || (iVar1 = FUN_0002ed1c(param_2,param_1), iVar1 == 0)) {
    param_2 = 0;
  }
  return param_2;
}


// 0002ed70 FUN_0002ed70

undefined4 FUN_0002ed70(int param_1)

{
  int iVar1;
  undefined4 local_58;
  undefined1 auStack_50 [56];
  
  if (*(int *)(param_1 + 0xc) == 0) {
    local_58 = 0;
  }
  else {
    local_58 = 0;
    FUN_0002f060(auStack_50);
    iVar1 = setjmp(auStack_50);
    if (iVar1 == 0) {
      local_58 = (**(code **)(param_1 + 0xc))();
    }
    FUN_0002f0c0();
  }
  return local_58;
}


// 0002edd8 FUN_0002edd8

void FUN_0002edd8(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  FUN_0003ea90(0);
  FUN_0003eb5c(iVar1 + 0x1c,param_1);
  FUN_0003eb2c(0);
  return;
}


// 0002ee08 thunk_FUN_0002ee18

undefined4 thunk_FUN_0002ee18(int param_1,int param_2)

{
  while( true ) {
    if (param_1 == 0) {
      return 0;
    }
    if (param_1 == param_2) break;
    param_1 = *(int *)(param_1 + 0x10);
  }
  return 1;
}


// 0002ee18 FUN_0002ee18

undefined4 FUN_0002ee18(int param_1,int param_2)

{
  while( true ) {
    if (param_1 == 0) {
      return 0;
    }
    if (param_1 == param_2) break;
    param_1 = *(int *)(param_1 + 0x10);
  }
  return 1;
}


// 0002ee30 FUN_0002ee30

bool FUN_0002ee30(CString *param_1,undefined4 param_2)

{
  int iVar1;
  wchar_t *pwVar2;
  int iVar3;
  wchar_t awStack_214 [256];
  int iVar4;
  
  iVar1 = FUN_0002eec8(param_2,awStack_214,0x100);
  if (0x100U - iVar1 < 2) {
    iVar4 = 0x100;
    do {
      iVar3 = iVar4 + 0x100;
      pwVar2 = CString_GetBuffer(param_1,iVar4 + 0xff);
      iVar1 = FUN_0002eec8(param_2,pwVar2,iVar3);
      iVar4 = iVar3;
    } while (iVar3 - iVar1 < 2);
    CString_ReleaseBuffer(param_1,0xffffffff);
  }
  else {
    CString_AssignW(param_1,awStack_214);
  }
  return 0 < iVar1;
}


// 0002eec8 FUN_0002eec8

void FUN_0002eec8(UINT param_1,LPWSTR param_2,int param_3)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  iVar1 = LoadStringW(*(HINSTANCE *)(iVar1 + 0xc),param_1,param_2,param_3);
  if (iVar1 == 0) {
    *param_2 = L'\0';
  }
  return;
}


// 0002ef00 FUN_0002ef00

undefined4 FUN_0002ef00(undefined4 param_1,wchar_t *param_2,int param_3,wchar_t param_4)

{
  wchar_t *pwVar1;
  size_t sVar2;
  void *_Dst;
  undefined4 uVar3;
  
  if (param_2 == (wchar_t *)0x0) {
LAB_0002ef74:
    uVar3 = 0;
  }
  else {
    while (param_3 != 0) {
      param_3 = param_3 + -1;
      param_2 = wcschr(param_2,param_4);
      if (param_2 == (wchar_t *)0x0) {
        FUN_0002e60c(param_1);
        goto LAB_0002ef74;
      }
      param_2 = param_2 + 1;
    }
    pwVar1 = wcschr(param_2,param_4);
    if (pwVar1 == (wchar_t *)0x0) {
      sVar2 = wcslen(param_2);
    }
    else {
      sVar2 = (int)pwVar1 - (int)param_2 >> 1;
    }
    _Dst = (void *)FUN_0002ebcc(param_1,sVar2);
    memmove(_Dst,param_2,sVar2 << 1);
    uVar3 = 1;
  }
  return uVar3;
}


// 0002efa4 FUN_0002efa4

void FUN_0002efa4(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 1;
  return;
}


// 0002efb0 FUN_0002efb0

void FUN_0002efb0(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}


// 0002efb8 FUN_0002efb8

void FUN_0002efb8(int *param_1)

{
  if ((0 < param_1[1]) && (param_1 != (int *)0x0)) {
    (**(code **)(*param_1 + 4))(param_1,1);
  }
  return;
}


// 0002efe4 FUN_0002efe4

void FUN_0002efe4(int *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 local_418 [2];
  undefined1 auStack_410 [1024];
  
  iVar1 = (**(code **)(*param_1 + 0xc))(param_1,auStack_410,0x200,local_418);
  if (iVar1 == 0) {
    if (param_3 == 0) {
      param_3 = 0xf020;
    }
    FUN_00037b9c(param_3,param_2,local_418[0]);
  }
  else {
    FUN_00037b50(auStack_410,param_2,local_418[0]);
  }
  return;
}


// 0002f060 FUN_0002f060

int FUN_0002f060(int param_1)

{
  int *piVar1;
  
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  piVar1 = (int *)FUN_0002f08c();
  *(int *)(param_1 + 0x30) = *piVar1;
  *piVar1 = param_1;
  return param_1;
}


// 0002f08c FUN_0002f08c

int FUN_0002f08c(void)

{
  DWORD dwErrCode;
  int iVar1;
  
  dwErrCode = GetLastError();
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  SetLastError(dwErrCode);
  return iVar1 + 0x10;
}


// 0002f0c0 FUN_0002f0c0

void FUN_0002f0c0(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_0002f08c();
  iVar2 = *piVar1;
  if (*(int *)(iVar2 + 0x34) != 0) {
    FUN_0002efb8();
  }
  *piVar1 = *(int *)(iVar2 + 0x30);
  return;
}


// 0002f108 FUN_0002f108

void FUN_0002f108(int param_1)

{
  int iVar1;
  int *piVar2;
  int *_Buf;
  
  iVar1 = FUN_0003f4f4();
  piVar2 = *(int **)(iVar1 + 4);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x88))(piVar2,0x80000000);
  }
  piVar2 = (int *)FUN_0002f08c();
  if (param_1 == 0) {
    param_1 = *(int *)(*piVar2 + 0x34);
  }
  while( true ) {
    while( true ) {
      _Buf = (int *)*piVar2;
      if (_Buf == (int *)0x0) {
        iVar1 = FUN_0003f4f4();
        (**(code **)(iVar1 + 0x2034))();
        return;
      }
      if (_Buf[0xd] == 0) break;
      if (_Buf[0xd] != param_1) {
        FUN_0002efb8();
      }
      _Buf[0xd] = 0;
      *piVar2 = _Buf[0xc];
    }
    if (_Buf[0xb] == 0) break;
    (*(code *)*_Buf)(_Buf);
  }
  _Buf[0xd] = param_1;
                    /* WARNING: Subroutine does not return */
  longjmp(_Buf,1);
}


// 0002f1b0 FUN_0002f1b0

void FUN_0002f1b0(undefined4 param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0002f08c();
  FUN_0002ed1c(*(undefined4 *)(*piVar1 + 0x34),param_1);
  return;
}


// 0002f1d0 FUN_0002f1d0

int FUN_0002f1d0(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f52c();
  iVar1 = *(int *)(iVar1 + 4);
  if (iVar1 == 0) {
    iVar1 = FUN_0003f4f4();
    iVar1 = *(int *)(iVar1 + 4);
  }
  return iVar1;
}


// 0002f1f0 FUN_0002f1f0

void FUN_0002f1f0(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 1;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return;
}


// 0002f234 FUN_0002f234

uint FUN_0002f234(undefined4 param_1,undefined4 param_2,undefined4 param_3,code *param_4,
                 undefined4 *param_5,uint param_6,undefined4 *param_7)

{
  uint uVar1;
  
  if (param_7 != (undefined4 *)0x0) {
    *param_7 = param_1;
    param_7[1] = param_4;
    return 1;
  }
  if (param_6 < 0x29) {
    if (param_6 == 0x28) {
      (*param_4)(param_1,param_2,param_5[1],*param_5);
      return 1;
    }
    if (param_6 == 2) {
      uVar1 = (*param_4)();
      return uVar1;
    }
    if (param_6 == 0xc) {
      (*param_4)();
      return 1;
    }
    if (param_6 == 0xd) {
      (*param_4)();
      return 1;
    }
    if (param_6 == 0x23) {
      uVar1 = (*param_4)();
      return uVar1;
    }
    if (param_6 == 0x26) {
      (*param_4)(param_1,param_5[1],*param_5);
      return 1;
    }
    if (param_6 == 0x27) {
      uVar1 = (*param_4)(param_1,param_5[1],*param_5);
      return uVar1;
    }
LAB_0002f338:
    uVar1 = 0;
  }
  else {
    if (param_6 == 0x29) {
      uVar1 = (*param_4)(param_1,param_2,param_5[1],*param_5);
      return uVar1;
    }
    if (param_6 == 0x2c) {
      (*param_4)(param_1,param_5);
    }
    else {
      if (param_6 != 0x2d) {
        if (param_6 == 0x2e) {
          (*param_4)(param_1,param_5);
          return 1;
        }
        if (param_6 == 0x2f) {
          uVar1 = (*param_4)(param_1,param_5);
          return uVar1;
        }
        goto LAB_0002f338;
      }
      (*param_4)(param_1,param_5,param_2);
    }
    uVar1 = (uint)(param_5[7] == 0);
    param_5[7] = 0;
  }
  return uVar1;
}


// 0002f3c4 FUN_0002f3c4

undefined4
FUN_0002f3c4(int *param_1,undefined4 param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  
  if (param_3 == 0xfffffffe) {
    iVar1 = FUN_0003f4f4();
    uVar2 = (**(code **)(**(int **)(iVar1 + 0x2038) + 4))
                      (*(int **)(iVar1 + 0x2038),param_1,param_2,param_4,param_5);
    return uVar2;
  }
  if (param_3 != 0xffffffff) {
    uVar4 = param_3 >> 0x10;
    param_3 = param_3 & 0xffff;
    if (uVar4 != 0) goto LAB_0002f444;
  }
  uVar4 = 0x111;
LAB_0002f444:
  piVar3 = (int *)(**(code **)(*param_1 + 0x28))(param_1);
  while( true ) {
    if (piVar3 == (int *)0x0) {
      return 0;
    }
    iVar1 = FUN_00030ec4(piVar3[1],uVar4,param_3,param_2);
    if (iVar1 != 0) break;
    piVar3 = (int *)*piVar3;
  }
  uVar2 = FUN_0002f234(param_1,param_2,param_3,*(undefined4 *)(iVar1 + 0x14),param_4,
                       *(undefined4 *)(iVar1 + 0x10),param_5);
  return uVar2;
}


// 0002f4ec FUN_0002f4ec

void FUN_0002f4ec(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  (**(code **)(**(int **)(iVar1 + 4) + 0x88))(*(int **)(iVar1 + 4),1);
  return;
}


// 0002f510 FUN_0002f510

void FUN_0002f510(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  (**(code **)(**(int **)(iVar1 + 4) + 0x88))(*(int **)(iVar1 + 4),0xffffffff);
  return;
}


// 0002f584 FUN_0002f584

void FUN_0002f584(undefined1 *param_1)

{
  *param_1 = 0x40;
  param_1[1] = 2;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  param_1[2] = 4;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  return;
}


// 0002f5d4 FUN_0002f5d4

void FUN_0002f5d4(int param_1,int param_2)

{
  HWND pHVar1;
  int iVar2;
  HWND hWnd;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    if (param_2 == 0) {
      pHVar1 = GetFocus();
      hWnd = *(HWND *)(*(int *)(param_1 + 0x14) + 0x1c);
      if (pHVar1 == hWnd) {
        GetParent(hWnd);
        iVar2 = FUN_0002ffec();
        if (*(int *)(param_1 + 0x14) == 0) {
          pHVar1 = (HWND)0x0;
        }
        else {
          pHVar1 = *(HWND *)(*(int *)(param_1 + 0x14) + 0x1c);
        }
        GetNextDlgTabItem(*(HWND *)(iVar2 + 0x1c),pHVar1,0);
        FUN_0002ffec();
        FUN_00033e00();
      }
    }
    FUN_00033dcc(*(undefined4 *)(param_1 + 0x14),param_2);
  }
  else {
    if (*(int *)(param_1 + 0x10) != 0) {
      return;
    }
    EnableMenuItem(*(HMENU *)(*(int *)(param_1 + 0xc) + 4),*(UINT *)(param_1 + 8),
                   param_2 == 0 | 0x400);
  }
  *(undefined4 *)(param_1 + 0x18) = 1;
  return;
}


// 0002f680 FUN_0002f680

void FUN_0002f680(int param_1,WPARAM param_2)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    uVar1 = SendMessageW(*(HWND *)(*(int *)(param_1 + 0x14) + 0x1c),0x87,0,0);
    if ((uVar1 & 0x2000) != 0) {
      SendMessageW(*(HWND *)(*(int *)(param_1 + 0x14) + 0x1c),0xf1,param_2,0);
    }
  }
  else if (*(int *)(param_1 + 0x10) == 0) {
    uVar1 = 8;
    if (param_2 == 0) {
      uVar1 = 0;
    }
    CheckMenuItem(*(HMENU *)(*(int *)(param_1 + 0xc) + 4),*(UINT *)(param_1 + 8),uVar1 | 0x400);
  }
  return;
}


// 0002f6fc FUN_0002f6fc

void FUN_0002f6fc(int *param_1,int param_2)

{
  (**(code **)(*param_1 + 4))(param_1,param_2 != 0);
  return;
}


// 0002f720 FUN_0002f720

void FUN_0002f720(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    FUN_00035e10(*(undefined4 *)(*(int *)(param_1 + 0x14) + 0x1c),param_2);
  }
  else if (*(int *)(param_1 + 0x10) == 0) {
    uVar1 = FUN_0002b070(*(undefined4 *)(*(int *)(param_1 + 0xc) + 4),*(undefined4 *)(param_1 + 8),
                         0x400);
    FUN_0002b0cc(*(undefined4 *)(*(int *)(param_1 + 0xc) + 4),*(undefined4 *)(param_1 + 8),
                 uVar1 & 0xfffff6fb | 0x400,*(undefined4 *)(param_1 + 4),param_2);
  }
  return;
}


// 0002f79c FUN_0002f79c

undefined4 FUN_0002f79c(undefined4 *param_1,int *param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_24 [2];
  
  uVar3 = param_1[1];
  if ((uVar3 == 0) || ((uVar3 & 0xffff) == 0xffff)) {
    uVar1 = 1;
  }
  else {
    param_1[6] = 0;
    uVar1 = (**(code **)(*param_2 + 0xc))(param_2,uVar3,0xffffffff,param_1,0);
    if ((param_3 != 0) && (param_1[6] == 0)) {
      local_24[0] = 0;
      uVar2 = (**(code **)(*param_2 + 0xc))(param_2,param_1[1],0,param_1,local_24);
      (**(code **)*param_1)(param_1,uVar2);
    }
  }
  return uVar1;
}


// 0002f8a0 FUN_0002f8a0

void FUN_0002f8a0(void)

{
  FUN_0002fa74(&CWnd::wndTop,0);
  return;
}


// 0002f8bc FUN_0002f8bc

void FUN_0002f8bc(void)

{
  if ((DAT_002de244 & 1) == 0) {
    DAT_002de244 = DAT_002de244 | 1;
    FUN_00030500(&CWnd::wndTop);
  }
  return;
}


// 0002f8fc FUN_0002f8fc

void FUN_0002f8fc(void)

{
  FUN_0002fa74(&CWnd::wndBottom,1);
  return;
}


// 0002f918 FUN_0002f918

void FUN_0002f918(void)

{
  if ((DAT_002de244 & 2) == 0) {
    DAT_002de244 = DAT_002de244 | 2;
    FUN_00030500(&CWnd::wndBottom);
  }
  return;
}


// 0002f958 FUN_0002f958

void FUN_0002f958(void)

{
  FUN_0002fa74(&CWnd::wndTopMost,0xffffffff);
  return;
}


// 0002f974 FUN_0002f974

void FUN_0002f974(void)

{
  if ((DAT_002de244 & 4) == 0) {
    DAT_002de244 = DAT_002de244 | 4;
    FUN_00030500(&CWnd::wndTopMost);
  }
  return;
}


// 0002f9b4 FUN_0002f9b4

void FUN_0002f9b4(void)

{
  FUN_0002fa74(&CWnd::wndNoTopMost,0xfffffffe);
  return;
}


// 0002f9d0 FUN_0002f9d0

void FUN_0002f9d0(void)

{
  if ((DAT_002de244 & 8) == 0) {
    DAT_002de244 = DAT_002de244 | 8;
    FUN_00030500(&CWnd::wndNoTopMost);
  }
  return;
}


// 0002fa00 FUN_0002fa00

undefined1 * FUN_0002fa00(undefined1 *param_1)

{
  FUN_0002f1f0();
  *param_1 = 0x88;
  param_1[1] = 5;
  param_1[2] = 4;
  param_1[3] = 0;
  memset(param_1 + 0x1c,0,0x28);
  *(undefined4 *)(param_1 + 0x40) = 0;
  return param_1;
}


// 0002fa74 FUN_0002fa74

undefined1 * FUN_0002fa74(undefined1 *param_1,undefined4 param_2)

{
  FUN_0002f1f0();
  *param_1 = 0x88;
  param_1[1] = 5;
  param_1[2] = 4;
  param_1[3] = 0;
  memset(param_1 + 0x1c,0,0x28);
  *(undefined4 *)(param_1 + 0x1c) = param_2;
  *(undefined4 *)(param_1 + 0x40) = 0;
  return param_1;
}


// 0002facc FUN_0002facc

undefined4 FUN_0002facc(HWND param_1,int param_2,uint param_3,uint param_4,uint param_5)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = GetWindowLongW(param_1,param_2);
  param_4 = uVar1 & ~param_3 | param_4;
  if (uVar1 == param_4) {
    uVar2 = 0;
  }
  else {
    SetWindowLongW(param_1,param_2,param_4);
    if (param_5 != 0) {
      SetWindowPos(param_1,(HWND)0x0,0,0,0,0,param_5 | 0x17);
    }
    uVar2 = 1;
  }
  return uVar2;
}


// 0002fb48 FUN_0002fb48

void FUN_0002fb48(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0002facc(param_1,0xfffffff0,param_2,param_3,param_4);
  return;
}


// 0002fb6c FUN_0002fb6c

void FUN_0002fb6c(int param_1,LPRECT param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  GetWindowRect(*(HWND *)(param_1 + 0x1c),param_2);
  uVar1 = FUN_00033b14(param_1);
  *param_3 = uVar1;
  return;
}


// 0002fb90 FUN_0002fb90

void FUN_0002fb90(int *param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  tagRECT local_1c;
  
  if (((((param_3 & 0x10000000) == 0) && (uVar1 = FUN_00033b14(), (uVar1 & 0x50000000) == 0)) &&
      (GetWindowRect((HWND)param_1[7],&local_1c), *param_2 == local_1c.left)) &&
     (param_2[1] == local_1c.top)) {
    GetWindow((HWND)param_1[7],4);
    iVar2 = FUN_0002ffec();
    if (((iVar2 == 0) || (iVar2 = FUN_00033d98(), iVar2 == 0)) &&
       (iVar2 = (**(code **)(*param_1 + 0xa4))(param_1), iVar2 != 0)) {
      FUN_00032b30(param_1,0);
    }
  }
  return;
}


// 0002fc30 FUN_0002fc30

void FUN_0002fc30(int param_1,WPARAM param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_1c;
  undefined4 local_18;
  
  uVar1 = FUN_00033b14();
  if ((uVar1 & 0x40000000) == 0) {
    iVar2 = FUN_00031b24(param_1);
    iVar3 = FUN_00031b24(param_3);
    if (iVar2 != iVar3) {
      local_1c = *(undefined4 *)(param_1 + 0x1c);
      local_18 = 0;
      if (param_3 != 0) {
        local_18 = *(undefined4 *)(param_3 + 0x1c);
      }
      SendMessageW(*(HWND *)(iVar2 + 0x1c),0x36e,param_2,(LPARAM)&local_1c);
    }
  }
  return;
}


// 0002fca4 FUN_0002fca4

undefined4 FUN_0002fca4(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (((param_2 == -2) && (((param_3 == 0x201 || (param_3 == 0x207)) || (param_3 == 0x204)))) &&
     (iVar1 = FUN_00031b24(), iVar1 != 0)) {
    GetActiveWindow();
    iVar1 = FUN_0002ffec();
    if (iVar1 != 0) {
      GetForegroundWindow();
      iVar2 = FUN_0002ffec();
      if ((iVar1 != iVar2) && (iVar2 = FUN_00033d98(iVar1), iVar2 != 0)) {
        SetForegroundWindow(*(HWND *)(iVar1 + 0x1c));
        return 1;
      }
    }
  }
  return 0;
}


// 0002fd40 FUN_0002fd40

undefined4
FUN_0002fd40(int *param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  bool bVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 *puVar7;
  undefined4 local_a0;
  int local_9c;
  undefined1 auStack_98 [16];
  undefined1 auStack_88 [32];
  undefined1 auStack_68 [52];
  undefined4 local_34;
  
  local_9c = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  iVar5 = 0x1c;
  puVar6 = auStack_88;
  puVar7 = (undefined1 *)(local_9c + 0x3c);
  do {
    iVar4 = iVar5 + -1;
    *puVar6 = *puVar7;
    bVar1 = 0 < iVar5;
    iVar5 = iVar4;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  } while (iVar4 != 0 && bVar1);
  *(undefined4 *)(local_9c + 0x3c) = param_2;
  *(int *)(local_9c + 0x40) = param_3;
  *(undefined4 *)(local_9c + 0x44) = param_4;
  *(undefined4 *)(local_9c + 0x48) = param_5;
  FUN_0002f060(auStack_68);
  iVar4 = setjmp(auStack_68);
  iVar5 = local_9c;
  if (iVar4 == 0) {
    if ((param_3 == 2) && (piVar2 = (int *)param_1[0xe], piVar2 != (int *)0x0)) {
      (**(code **)(*piVar2 + 0x58))(piVar2,0);
    }
    iVar4 = 0;
    local_a0 = 0;
    if (param_3 == 0x110) {
      iVar4 = param_1[0x11];
    }
    if (param_3 == 0x110 && iVar4 == 0) {
      FUN_0002fb6c(param_1,auStack_98,&local_a0);
    }
    uVar3 = (**(code **)(*param_1 + 0x90))(param_1,param_3,param_4,param_5);
    if ((param_3 == 0x110) && (param_1[0x11] == 0)) {
      FUN_0002fb90(param_1,auStack_98,local_a0);
    }
  }
  else {
    piVar2 = (int *)FUN_0002f1d0();
    uVar3 = (**(code **)(*piVar2 + 0x68))(piVar2,local_34,iVar5 + 0x3c);
  }
  FUN_0002f0c0();
  iVar4 = 0x1c;
  puVar6 = auStack_88;
  puVar7 = (undefined1 *)(iVar5 + 0x3c);
  do {
    iVar5 = iVar4 + -1;
    *puVar7 = *puVar6;
    bVar1 = 0 < iVar4;
    iVar4 = iVar5;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  } while (iVar5 != 0 && bVar1);
  return uVar3;
}


// 0002feb8 FUN_0002feb8

int FUN_0002feb8(void)

{
  int iVar1;
  undefined4 uVar2;
  DWORD DVar3;
  undefined1 local_10;
  undefined1 uStack_f;
  char cStack_e;
  undefined1 local_c;
  char cStack_b;
  char cStack_a;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  uVar2 = FUN_0002a214();
  *(undefined4 *)(iVar1 + 0x4c) = uVar2;
  DVar3 = GetMessagePos();
  local_10 = (undefined1)DVar3;
  *(undefined1 *)(iVar1 + 0x50) = local_10;
  uStack_f = (undefined1)(DVar3 >> 8);
  *(undefined1 *)(iVar1 + 0x51) = uStack_f;
  cStack_e = (char)((short)DVar3 >> 0xf);
  *(char *)(iVar1 + 0x52) = cStack_e;
  *(char *)(iVar1 + 0x53) = cStack_e;
  local_c = (undefined1)(DVar3 >> 0x10);
  *(undefined1 *)(iVar1 + 0x54) = local_c;
  cStack_b = (char)(DVar3 >> 0x18);
  *(char *)(iVar1 + 0x55) = cStack_b;
  cStack_a = cStack_b >> 7;
  *(char *)(iVar1 + 0x56) = cStack_a;
  *(char *)(iVar1 + 0x57) = cStack_a;
  return iVar1 + 0x3c;
}


// 0002ff50 FUN_0002ff50

void FUN_0002ff50(int *param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  (**(code **)(*param_1 + 0x98))
            (param_1,*(undefined4 *)(iVar1 + 0x40),*(undefined4 *)(iVar1 + 0x44),
             *(undefined4 *)(iVar1 + 0x48));
  return;
}


// 0002ff90 FUN_0002ff90

undefined4 FUN_0002ff90(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f52c();
  if ((*(int *)(iVar1 + 0x14) == 0) && (param_1 != 0)) {
    iVar2 = operator_new(0x48);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00033818(iVar2,&CWnd::classCWnd,0x1c,1);
    }
    *(undefined4 *)(iVar1 + 0x14) = uVar3;
  }
  return *(undefined4 *)(iVar1 + 0x14);
}


// 0002ffec FUN_0002ffec

undefined4 FUN_0002ffec(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0002ff90(1);
  uVar2 = FUN_00033890(uVar1,param_1);
  FUN_00033e38(uVar2,uVar1);
  return uVar2;
}


// 0003001c FUN_0003001c

void FUN_0003001c(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0002ff90(0);
  if (iVar1 != 0) {
    FUN_0002e298(iVar1 + 4,param_1);
  }
  return;
}


// 00030044 FUN_00030044

bool FUN_00030044(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 != 0) {
    iVar1 = FUN_0002ff90(1);
    *(int *)(param_1 + 0x1c) = param_2;
    piVar2 = (int *)FUN_0002e328(iVar1 + 4,param_2);
    *piVar2 = param_1;
    FUN_00033e38(param_1,iVar1);
  }
  return param_2 != 0;
}


// 00030090 FUN_00030090

int FUN_00030090(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x1c);
  if (iVar2 != 0) {
    iVar1 = FUN_0002ff90(0);
    if (iVar1 != 0) {
      FUN_0002e394(iVar1 + 4,*(undefined4 *)(param_1 + 0x1c));
    }
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return iVar2;
}


// 000300d4 FUN_000300d4

undefined4 FUN_000300d4(HWND param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_2 == 0x360) {
    uVar1 = 1;
  }
  else {
    iVar2 = FUN_0003001c(param_1);
    uVar1 = FUN_0002fd40(iVar2,param_1,param_2,param_3,param_4);
    if (param_2 == 2) {
      SendMessageW(*(HWND *)(iVar2 + 0x1c),0x7fff,0,0);
      SetWindowLongW(param_1,-4,0x2b798);
    }
  }
  return uVar1;
}


// 00030160 FUN_00030160

code * FUN_00030160(void)

{
  return FUN_000300d4;
}


// 0003016c FUN_0003016c

undefined4 FUN_0003016c(undefined4 param_1,HWND param_2)

{
  int iVar1;
  LONG *pLVar2;
  int dwNewLong;
  LONG LVar3;
  int *piVar4;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  GetWindowLongW(param_2,-0x10);
  piVar4 = *(int **)(iVar1 + 0x14);
  if (piVar4 != (int *)0x0) {
    FUN_00030044(piVar4,param_2);
    (**(code **)(*piVar4 + 0x4c))(piVar4);
    pLVar2 = (LONG *)(**(code **)(*piVar4 + 0x78))(piVar4);
    dwNewLong = FUN_00030160();
    LVar3 = SetWindowLongW(param_2,-4,dwNewLong);
    if (LVar3 != dwNewLong) {
      *pLVar2 = LVar3;
    }
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  return 1;
}


// 0003020c FUN_0003020c

void FUN_0003020c(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  if (*(int *)(iVar1 + 0x14) != param_1) {
    *(int *)(iVar1 + 0x14) = param_1;
  }
  return;
}


// 00030238 FUN_00030238

bool FUN_00030238(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  iVar2 = FUN_0003f4f4();
  bVar3 = *(char *)(iVar2 + 0x14) != '\0';
  iVar2 = 0;
  if (bVar3) {
    iVar2 = *(int *)(iVar1 + 0x34);
  }
  if (bVar3 && iVar2 != 0) {
    *(undefined4 *)(iVar1 + 0x34) = 0;
  }
  bVar3 = *(int *)(iVar1 + 0x14) != 0;
  if (bVar3) {
    *(undefined4 *)(iVar1 + 0x14) = 0;
  }
  return !bVar3;
}


// 00030288 FUN_00030288

undefined4
FUN_00030288(int *param_1,DWORD param_2,LPCWSTR param_3,LPCWSTR param_4,uint param_5,int param_6,
            int param_7,int param_8,int param_9,HWND param_10,HMENU param_11,LPVOID param_12)

{
  int iVar1;
  HWND pHVar2;
  LPVOID local_70;
  HINSTANCE local_6c;
  HMENU local_68;
  HWND local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  uint local_50;
  LPCWSTR local_4c;
  LPCWSTR local_48;
  DWORD local_44;
  undefined4 local_40;
  uint local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  
  local_50 = param_5;
  local_54 = param_6;
  local_58 = param_7;
  local_5c = param_8;
  local_68 = param_11;
  local_60 = param_9;
  local_64 = param_10;
  local_4c = param_4;
  local_48 = param_3;
  local_44 = param_2;
  iVar1 = FUN_0003f4f4();
  local_6c = *(HINSTANCE *)(iVar1 + 8);
  local_70 = param_12;
  iVar1 = (**(code **)(*param_1 + 0x58))(param_1,&local_70);
  if ((iVar1 == 0) || (iVar1 = FUN_0002b550(&local_70), iVar1 == 0)) {
    (**(code **)(*param_1 + 0x9c))(param_1);
  }
  else {
    if ((local_50 & 0xc0000000) == 0) {
      local_54 = -0x80000000;
      local_58 = -0x80000000;
      memset(&local_40,0,0x30);
      local_40 = 0x30;
      iVar1 = SHSipInfo(0xe1,0,&local_40,0);
      if (iVar1 != 0) {
        local_60 = 0;
        if ((local_3c & 1) == 0) {
          local_60 = 0x1a;
        }
        local_5c = local_30 - local_38;
        local_60 = (local_2c - local_34) - local_60;
      }
    }
    FUN_0003020c(param_1);
    pHVar2 = CreateWindowExW(local_44,local_48,local_4c,local_50,local_54,local_58,local_5c,local_60
                             ,local_64,local_68,local_6c,local_70);
    FUN_0002b6fc(&local_70,pHVar2,param_11);
    iVar1 = FUN_00030238();
    if (iVar1 == 0) {
      (**(code **)(*param_1 + 0x9c))(param_1);
    }
    if (pHVar2 != (HWND)0x0) {
      return 1;
    }
  }
  return 0;
}


// 00030458 FUN_00030458

undefined4 FUN_00030458(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x28) == 0) {
    FUN_00033358(1);
    *(wchar_t **)(param_2 + 0x28) = L"AfxWnd42su";
  }
  return 1;
}


// 00030488 FUN_00030488

void FUN_00030488(undefined4 param_1,undefined4 param_2,undefined4 param_3,uint param_4,int *param_5
                 ,int param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_6 != 0) {
    uVar1 = *(undefined4 *)(param_6 + 0x1c);
  }
  FUN_00030288(param_1,0,param_2,param_3,param_4 | 0x40000000,*param_5,param_5[1],
               param_5[2] - *param_5,param_5[3] - param_5[1],uVar1,param_7,param_8);
  return;
}


// 00030500 FUN_00030500

void FUN_00030500(CWnd *param_1)

{
  CWnd *pCVar1;
  int *piVar2;
  int iVar3;
  
  *param_1 = (CWnd)0x88;
  param_1[1] = (CWnd)0x5;
  param_1[2] = (CWnd)0x4;
  param_1[3] = (CWnd)0x0;
  if (((*(int *)(param_1 + 0x1c) != 0) && (param_1 != &CWnd::wndTop)) &&
     (param_1 != &CWnd::wndBottom)) {
    pCVar1 = &CWnd::wndTopMost;
    if (param_1 != &CWnd::wndTopMost) {
      pCVar1 = &CWnd::wndNoTopMost;
    }
    if (param_1 != &CWnd::wndTopMost && param_1 != pCVar1) {
      FUN_00030748(param_1);
    }
  }
  piVar2 = *(int **)(param_1 + 0x38);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 4))(piVar2,1);
  }
  iVar3 = *(int *)(param_1 + 0x3c);
  if ((iVar3 != 0) && (*(CWnd **)(iVar3 + 0x24) == param_1)) {
    *(undefined4 *)(iVar3 + 0x24) = 0;
  }
  if (*(int *)(param_1 + 0x10) != 0) {
    (**(code **)(*(int *)(param_1 + 0x10) + 0x1c))(param_1 + 0x10);
  }
  return;
}


// 00030608 FUN_00030608

void FUN_00030608(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  LONG LVar4;
  LONG LVar5;
  LONG *pLVar6;
  
  iVar1 = FUN_0002f1d0();
  if (iVar1 != 0) {
    if (*(int **)(iVar1 + 0x1c) == param_1) {
      iVar2 = FUN_0003f4f4();
      if ((*(char *)(iVar2 + 0x14) == '\0') &&
         ((iVar2 = FUN_0003f4f4(), iVar1 != *(int *)(iVar2 + 4) ||
          (iVar2 = FUN_0003ae5c(), iVar2 != 0)))) {
        FUN_0003fd90(0);
      }
      *(undefined4 *)(iVar1 + 0x1c) = 0;
    }
    if (*(int **)(iVar1 + 0x20) == param_1) {
      *(undefined4 *)(iVar1 + 0x20) = 0;
    }
  }
  piVar3 = (int *)param_1[0xe];
  if (param_1[0xd] != 0) {
    param_1[0xd] = 0;
  }
  if (piVar3 != (int *)0x0) {
    (**(code **)(*piVar3 + 4))(piVar3,1);
  }
  param_1[0xe] = 0;
  LVar4 = GetWindowLongW((HWND)param_1[7],-4);
  FUN_0002ff50(param_1);
  LVar5 = GetWindowLongW((HWND)param_1[7],-4);
  if (LVar5 == LVar4) {
    pLVar6 = (LONG *)(**(code **)(*param_1 + 0x78))(param_1);
    if (*pLVar6 != 0) {
      SetWindowLongW((HWND)param_1[7],-4,*pLVar6);
    }
  }
  FUN_00030090(param_1);
  (**(code **)(*param_1 + 0x9c))(param_1);
  return;
}


// 00030714 FUN_00030714

void FUN_00030714(int *param_1)

{
  if (param_1[7] == 0) {
    (**(code **)(*param_1 + 0x9c))();
  }
  else {
    (**(code **)(*param_1 + 0x54))();
  }
  return;
}


// 00030748 FUN_00030748

BOOL FUN_00030748(int param_1)

{
  BOOL BVar1;
  int iVar2;
  
  BVar1 = 0;
  if (*(int *)(param_1 + 0x1c) != 0) {
    iVar2 = FUN_0002ff90(0);
    iVar2 = FUN_0002e298(iVar2 + 4,*(undefined4 *)(param_1 + 0x1c));
    if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
      BVar1 = DestroyWindow(*(HWND *)(param_1 + 0x1c));
    }
    else {
      BVar1 = (**(code **)(**(int **)(param_1 + 0x3c) + 0x4c))();
    }
    if (iVar2 == 0) {
      FUN_00030090(param_1);
    }
  }
  return BVar1;
}


// 000307b4 FUN_000307b4

void FUN_000307b4(int *param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  undefined4 *puVar1;
  
  if ((WNDPROC)param_1[0xb] == (WNDPROC)0x0) {
    puVar1 = (undefined4 *)(**(code **)(*param_1 + 0x78))(param_1);
    if ((WNDPROC)*puVar1 == (WNDPROC)0x0) {
      DefWindowProcW((HWND)param_1[7],param_2,param_3,param_4);
    }
    else {
      CallWindowProcW((WNDPROC)*puVar1,(HWND)param_1[7],param_2,param_3,param_4);
    }
  }
  else {
    CallWindowProcW((WNDPROC)param_1[0xb],(HWND)param_1[7],param_2,param_3,param_4);
  }
  return;
}


// 0003084c FUN_0003084c

undefined4 FUN_0003084c(void)

{
  return 0;
}


// 00030854 FUN_00030854

void FUN_00030854(int param_1,CString *param_2)

{
  int *piVar1;
  int iVar2;
  LPWSTR lpString;
  
  piVar1 = *(int **)(param_1 + 0x3c);
  if (piVar1 == (int *)0x0) {
    iVar2 = GetWindowTextLengthW(*(HWND *)(param_1 + 0x1c));
    lpString = (LPWSTR)FUN_0002ebcc(param_2,iVar2);
    GetWindowTextW(*(HWND *)(param_1 + 0x1c),lpString,iVar2 + 1);
    CString_ReleaseBuffer(param_2,0xffffffff);
  }
  else {
    (**(code **)(*piVar1 + 0x84))(piVar1,param_2);
  }
  return;
}


// 000308bc FUN_000308bc

undefined4 FUN_000308bc(int param_1,int param_2,CString *param_3)

{
  HWND hWnd;
  int iVar1;
  LPWSTR lpString;
  
  CString_AssignW(param_3,(wchar_t *)&afxChNil);
  if (*(int *)(param_1 + 0x38) == 0) {
    hWnd = GetDlgItem(*(HWND *)(param_1 + 0x1c),param_2);
    if (hWnd != (HWND)0x0) {
      iVar1 = GetWindowTextLengthW(hWnd);
      lpString = (LPWSTR)FUN_0002ebcc(param_3,iVar1);
      GetWindowTextW(hWnd,lpString,iVar1 + 1);
      CString_ReleaseBuffer(param_3,0xffffffff);
    }
  }
  else {
    iVar1 = FUN_00033a44(param_1);
    if (iVar1 != 0) {
      FUN_00030854(iVar1,param_3);
    }
  }
  return *(undefined4 *)(param_3->str + -4);
}


// 00030954 FUN_00030954

void FUN_00030954(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  
  if (*param_3 == 1) {
    piVar1 = (int *)FUN_00033f08();
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0xc))(piVar1,param_3);
      return;
    }
  }
  else {
    iVar2 = FUN_00032494(param_3[5],0);
    if (iVar2 != 0) {
      return;
    }
  }
  FUN_0002ff50(param_1);
  return;
}


// 000309b0 FUN_000309b0

void FUN_000309b0(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined1 local_c [4];
  
  iVar1 = FUN_00032494(*(undefined4 *)(param_3 + 8),local_c);
  if (iVar1 == 0) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 000309e0 FUN_000309e0

void FUN_000309e0(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  iVar1 = FUN_00032494(*(undefined4 *)(param_3 + 0xc),0);
  if (iVar1 == 0) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 00030a04 FUN_00030a04

undefined4 FUN_00030a04(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 local_c;
  
  if ((param_3 == 0) || (iVar1 = FUN_00032444(param_3,&local_c), iVar1 == 0)) {
    local_c = FUN_0002ff50(param_1);
  }
  return local_c;
}


// 00030a40 FUN_00030a40

undefined4 FUN_00030a40(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 local_c;
  
  if ((param_3 == 0) || (iVar1 = FUN_00032444(param_3,&local_c), iVar1 == 0)) {
    local_c = FUN_0002ff50(param_1);
  }
  return local_c;
}


// 00030a7c FUN_00030a7c

int FUN_00030a7c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int nPos;
  
  iVar1 = FUN_0002b16c(*(undefined4 *)(param_1 + 4));
  nPos = 0;
  if (0 < iVar1) {
    do {
      GetSubMenu(*(HMENU *)(param_1 + 4),nPos);
      iVar2 = FUN_00033eec();
      if (iVar2 == 0) {
        iVar2 = FUN_0002afe8(*(undefined4 *)(param_1 + 4),nPos);
        if (iVar2 == param_2) {
          iVar1 = FUN_00033f08(*(undefined4 *)(param_1 + 4));
          return iVar1;
        }
      }
      else {
        iVar2 = FUN_00030a7c(iVar2,param_2);
        if (iVar2 != 0) {
          return iVar2;
        }
      }
      nPos = nPos + 1;
    } while (nPos < iVar1);
  }
  return 0;
}


// 00030b00 FUN_00030b00

void FUN_00030b00(int param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  
  if (*param_3 == 1) {
    iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
    if (*(int *)(iVar1 + 0x58) != *(int *)(param_1 + 0x1c)) {
      FUN_0002b038(*(int *)(param_1 + 0x1c));
    }
    uVar2 = FUN_00033eec();
    piVar3 = (int *)FUN_00030a7c(uVar2,param_3[2]);
    if (piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 0x10))(piVar3,param_3);
    }
  }
  else {
    iVar1 = FUN_00031c4c(*(undefined4 *)(param_1 + 0x1c),param_3[1],1);
    if ((iVar1 != 0) && (iVar1 = FUN_00032444(iVar1,0), iVar1 != 0)) {
      return;
    }
  }
  FUN_0002ff50(param_1);
  return;
}


// 00030ba4 FUN_00030ba4

undefined4 FUN_00030ba4(WNDCLASSW *param_1)

{
  ATOM AVar1;
  BOOL BVar2;
  int iVar3;
  wchar_t local_84 [4];
  tagWNDCLASSW tStack_7c;
  undefined1 auStack_54 [56];
  
  BVar2 = GetClassInfoW(param_1->hInstance,param_1->lpszClassName,&tStack_7c);
  if (BVar2 == 0) {
    AVar1 = RegisterClassW(param_1);
    if (AVar1 == 0) {
      return 0;
    }
    iVar3 = FUN_0003f4f4(AVar1);
    if (*(char *)(iVar3 + 0x14) != '\0') {
      FUN_0003ea90(1);
      FUN_0002f060(auStack_54);
      iVar3 = setjmp(auStack_54);
      if (iVar3 == 0) {
        iVar3 = FUN_0003f4f4();
        wcscat((wchar_t *)(iVar3 + 0x34),param_1->lpszClassName);
        local_84[0] = L'\n';
        local_84[1] = 0;
        wcscat((wchar_t *)(iVar3 + 0x34),local_84);
      }
      else {
        FUN_0003eb2c(1);
        FUN_0002f108(0);
      }
      FUN_0002f0c0();
      FUN_0003eb2c(1);
    }
  }
  return 1;
}


// 00030c7c FUN_00030c7c

LPCWSTR FUN_00030c7c(UINT param_1,HCURSOR param_2,HBRUSH param_3,HICON param_4)

{
  int iVar1;
  BOOL BVar2;
  LPCWSTR lpClassName;
  HINSTANCE hInstance;
  tagWNDCLASSW local_44;
  
  iVar1 = FUN_0003f170();
  lpClassName = (LPCWSTR)(iVar1 + 0x60);
  iVar1 = FUN_0003f4f4();
  hInstance = *(HINSTANCE *)(iVar1 + 8);
  if (((param_2 == (HCURSOR)0x0) && (param_3 == (HBRUSH)0x0)) && (param_4 == (HICON)0x0)) {
    wsprintfW(lpClassName,u_Afx__x__x_00043fb4,hInstance,param_1);
  }
  else {
    wsprintfW(lpClassName,(LPCWSTR)&DAT_00043f8c,hInstance,param_1,param_2,param_3,param_4);
  }
  BVar2 = GetClassInfoW(hInstance,lpClassName,&local_44);
  if (BVar2 == 0) {
    local_44.cbWndExtra = 0;
    local_44.cbClsExtra = 0;
    local_44.lpszMenuName = (LPCWSTR)0x0;
    local_44.lpfnWndProc = FUN_0002b684;
    local_44.style = param_1;
    local_44.hInstance = hInstance;
    local_44.hIcon = param_4;
    local_44.hCursor = param_2;
    local_44.hbrBackground = param_3;
    local_44.lpszClassName = lpClassName;
    iVar1 = FUN_00030ba4(&local_44);
    if (iVar1 == 0) {
      FUN_00036504();
    }
  }
  return lpClassName;
}


// 00030d64 FUN_00030d64

void FUN_00030d64(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  
  local_18 = param_3;
  local_14 = param_2;
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  local_10 = *(int *)(iVar1 + 0x40) + -0x132;
  (**(code **)(*param_1 + 0x90))(param_1,0x19,0,&local_18);
  return;
}


// 00030dc8 FUN_00030dc8

void FUN_00030dc8(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  HWND hWnd;
  int iVar2;
  
  iVar1 = FUN_0003f4f4();
  iVar2 = *(int *)(iVar1 + 4);
  iVar1 = FUN_0003f4f4();
  FUN_0002f4ec(*(undefined4 *)(iVar1 + 4));
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x1f,0,0);
  FUN_00031cf4(*(undefined4 *)(param_1 + 0x1c),0x1f,0,0,1,1);
  iVar1 = FUN_00031b24(param_1);
  SendMessageW(*(HWND *)(iVar1 + 0x1c),0x1f,0,0);
  FUN_00031cf4(*(undefined4 *)(iVar1 + 0x1c),0x1f,0,0,1,1);
  hWnd = GetCapture();
  if (hWnd != (HWND)0x0) {
    SendMessageW(hWnd,0x1f,0,0);
  }
  iVar1 = AfxWinHelp_PegHelp(*(undefined4 *)(iVar1 + 0x1c),*(undefined4 *)(iVar2 + 0x88),param_3,
                             param_2);
  if (iVar1 == 0) {
    FUN_00037b9c(0xf107,0,0xffffffff);
  }
  iVar1 = FUN_0003f4f4();
  FUN_0002f510(*(undefined4 *)(iVar1 + 4));
  return;
}


// 00030ec4 FUN_00030ec4

int * FUN_00030ec4(int *param_1,int param_2,int param_3,uint param_4)

{
  while( true ) {
    if (param_1[4] == 0) {
      return (int *)0x0;
    }
    if ((((*param_1 == param_2) && (param_1[1] == param_3)) && ((uint)param_1[2] <= param_4)) &&
       (param_4 <= (uint)param_1[3])) break;
    param_1 = param_1 + 6;
  }
  return param_1;
}


// 00030f14 FUN_00030f14

undefined4 FUN_00030f14(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_1c;
  
  local_1c = 0;
  puVar2 = &local_1c;
  iVar1 = (**(code **)(*param_1 + 0x94))();
  if (iVar1 == 0) {
    local_1c = (**(code **)(*param_1 + 0x98))(param_1,param_2,param_3,param_4,puVar2);
  }
  return local_1c;
}


// 00030f88 FUN_00030f88

undefined4 FUN_00030f88(int *param_1,uint param_2,uint param_3,int *param_4,undefined4 *param_5)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint *puVar5;
  uint uVar6;
  undefined1 *puVar7;
  undefined4 uVar8;
  code *pcVar9;
  int iVar10;
  undefined4 local_88 [2];
  undefined1 auStack_80 [4];
  int local_7c;
  undefined1 auStack_68 [28];
  int local_4c;
  int local_2c;
  
  local_88[0] = 0;
  if (param_2 == 0x111) {
    iVar3 = (**(code **)(*param_1 + 0x70))(param_1,param_3,param_4);
    if (iVar3 == 0) {
      return 0;
    }
    goto LAB_00031758;
  }
  if (param_2 == 0x4e) {
    if (*param_4 == 0) {
      return 0;
    }
    iVar3 = (**(code **)(*param_1 + 0x74))(param_1,param_3,param_4,local_88);
    if (iVar3 == 0) {
      return 0;
    }
    goto LAB_00031864;
  }
  if (param_2 == 6) {
    uVar4 = FUN_0002ffec(param_4);
    FUN_0002fc30(param_1,param_3,uVar4);
  }
  sVar1 = (short)param_4;
  if ((param_2 == 0x20) &&
     (iVar3 = FUN_0002fca4(param_1,(int)sVar1,(uint)param_4 >> 0x10), iVar3 != 0))
  goto LAB_00031758;
  puVar5 = (uint *)(**(code **)(*param_1 + 0x28))(param_1);
  FUN_0003ea90(7);
  iVar3 = ((uint)puVar5 & 0x1ff ^ param_2 & 0x1ff) * 0xc;
  if ((param_2 != *(uint *)(&DAT_002dc970 + iVar3)) || (puVar5 != *(uint **)(&DAT_002dc978 + iVar3))
     ) {
    *(uint *)(&DAT_002dc970 + iVar3) = param_2;
    *(uint **)(&DAT_002dc978 + iVar3) = puVar5;
    do {
      if (puVar5 == (uint *)0x0) {
        *(undefined4 *)(&DAT_002dc974 + iVar3) = 0;
        FUN_0003eb2c(7);
        return 0;
      }
      uVar6 = puVar5[1];
      if (param_2 < 0xc000) {
        iVar10 = FUN_00030ec4(uVar6,param_2,0,0);
        if (iVar10 != 0) {
          *(int *)(&DAT_002dc974 + iVar3) = iVar10;
          FUN_0003eb2c(7);
          goto LAB_00031128;
        }
      }
      else {
        while (iVar10 = FUN_00030ec4(uVar6,0xc000,0,0), iVar10 != 0) {
          if (**(uint **)(iVar10 + 0x10) == param_2) {
            *(int *)(&DAT_002dc974 + iVar3) = iVar10;
            FUN_0003eb2c(7);
            goto LAB_00031848;
          }
          uVar6 = iVar10 + 0x18;
        }
      }
      puVar5 = (uint *)*puVar5;
    } while( true );
  }
  iVar10 = *(int *)(&DAT_002dc974 + iVar3);
  FUN_0003eb2c(7);
  if (iVar10 == 0) {
    return 0;
  }
  if (0xbfff < param_2) {
LAB_00031848:
    local_88[0] = (**(code **)(iVar10 + 0x14))(param_1,param_3,param_4);
    goto LAB_00031864;
  }
LAB_00031128:
  pcVar9 = *(code **)(iVar10 + 0x14);
  iVar3 = *(int *)(iVar10 + 0x10);
  if (*(int *)(iVar10 + 8) == 0x1a) {
    iVar3 = 0x2f;
  }
  if (0x30 < iVar3 - 1U) goto LAB_00031864;
  iVar2 = (int)param_4 >> 0x10;
  switch(iVar3) {
  case 1:
    uVar4 = FUN_00035ff4(param_3);
    local_88[0] = (*pcVar9)(param_1,uVar4);
    break;
  case 2:
    local_88[0] = (*pcVar9)(param_1,param_3);
    break;
  case 3:
    uVar4 = FUN_0002ffec(param_3);
    local_88[0] = (*pcVar9)(param_1,uVar4,(int)sVar1,(uint)param_4 >> 0x10);
    break;
  case 4:
    FUN_00035f38(auStack_80);
    local_7c = param_4[1];
    FUN_0002fa00(auStack_68);
    local_4c = *param_4;
    iVar3 = param_4[2];
    puVar7 = (undefined1 *)FUN_0003001c();
    if (puVar7 == (undefined1 *)0x0) {
      if ((param_1[0xe] != 0) && (iVar10 = FUN_0002e298(param_1[0xe] + 0x20,local_4c), iVar10 != 0))
      {
        local_2c = iVar10;
      }
      puVar7 = auStack_68;
    }
    local_88[0] = (*pcVar9)(param_1,auStack_80,puVar7,iVar3);
    local_7c = 0;
    local_4c = 0;
    FUN_00030500(auStack_68);
    goto LAB_00031370;
  case 5:
    FUN_00035f38(auStack_80);
    local_7c = param_4[1];
    local_88[0] = (*pcVar9)(param_1,auStack_80,param_4[2]);
    local_7c = 0;
LAB_00031370:
    FUN_000360b4(auStack_80);
    break;
  case 6:
    uVar4 = FUN_0002ffec(param_4);
    local_88[0] = (*pcVar9)(param_1,param_3 & 0xffff,uVar4,param_3 >> 0x10);
    break;
  case 7:
    local_88[0] = (*pcVar9)(param_1,param_3 & 0xffff,param_3 >> 0x10);
    break;
  case 8:
    uVar4 = FUN_0002ffec(param_3);
    local_88[0] = (*pcVar9)(param_1,uVar4,(int)sVar1,(uint)param_4 >> 0x10);
    break;
  case 9:
    local_88[0] = (*pcVar9)(param_1,param_4);
    break;
  case 10:
    local_88[0] = (*pcVar9)(param_1,param_3,param_4);
    break;
  case 0xb:
    uVar4 = FUN_00033eec(param_4);
    local_88[0] = (*pcVar9)(param_1,param_3 & 0xffff,param_3 >> 0x10,uVar4);
    break;
  case 0xc:
    (*pcVar9)(param_1);
    break;
  case 0xd:
    (*pcVar9)(param_1,param_3);
    break;
  case 0xe:
    (*pcVar9)(param_1,param_3,param_4);
    break;
  case 0xf:
    (*pcVar9)(param_1,(int)sVar1,iVar2);
    break;
  case 0x10:
    (*pcVar9)(param_1,param_3,(uint)param_4 & 0xffff,(uint)param_4 >> 0x10);
    break;
  case 0x11:
    (*pcVar9)(param_1,param_3,(uint)param_4 & 0xffff,(uint)param_4 >> 0x10);
    break;
  case 0x12:
    (*pcVar9)(param_1,param_3,param_4);
    break;
  case 0x13:
    uVar4 = FUN_0002ffec(param_3);
    uVar8 = FUN_0002ffec(param_4);
    (*pcVar9)(param_1,(int *)param_1[7] == param_4,uVar8,uVar4);
    break;
  case 0x14:
    uVar4 = FUN_00035ff4(param_3);
    (*pcVar9)(param_1,uVar4);
    break;
  case 0x15:
    uVar4 = FUN_00033eec(param_3);
    (*pcVar9)(param_1,uVar4);
    break;
  case 0x16:
    uVar4 = FUN_00033eec(param_3);
    (*pcVar9)(param_1,uVar4,(uint)param_4 & 0xffff,(uint)param_4 >> 0x10);
    break;
  case 0x17:
    uVar4 = FUN_0002ffec(param_3);
    (*pcVar9)(param_1,uVar4);
    break;
  case 0x18:
    uVar4 = FUN_0002ffec(param_3);
    (*pcVar9)(param_1,uVar4,(uint)param_4 & 0xffff,(uint)param_4 >> 0x10);
    break;
  case 0x19:
    uVar4 = FUN_0002ffec(param_3);
    (*pcVar9)(param_1,uVar4,(int)sVar1,iVar2);
    break;
  case 0x1a:
    uVar4 = FUN_0002ffec(param_3);
    (*pcVar9)(param_1,uVar4,param_4);
    break;
  case 0x1b:
    uVar4 = FUN_0002ffec(param_4);
    (*pcVar9)(param_1,param_3,uVar4);
    break;
  case 0x1c:
    uVar4 = FUN_0002ffec(param_4);
    (*pcVar9)(param_1,param_3 & 0xffff,uVar4,param_3 >> 0x10);
    break;
  case 0x1d:
    goto LAB_000316c0;
  case 0x1e:
LAB_000316c0:
    if (*(int *)(iVar10 + 0x10) == 0x1d) {
      uVar4 = FUN_0002ffec(param_4);
      (*pcVar9)(param_1,(int)(short)param_3,(int)param_3 >> 0x10,uVar4);
    }
    else {
      (*pcVar9)(param_1,(int)(short)param_3,(int)param_3 >> 0x10);
    }
    break;
  case 0x1f:
    (*pcVar9)(param_1,param_4);
    break;
  case 0x20:
    (*pcVar9)(param_1,param_3,param_4);
    goto LAB_00031758;
  case 0x21:
    local_88[0] = (*pcVar9)(param_1,param_3,param_4);
    break;
  case 0x22:
    local_88[0] = (*pcVar9)(param_1,(int)sVar1,iVar2);
    break;
  case 0x23:
    local_88[0] = (*pcVar9)(param_1);
    break;
  case 0x24:
    (*pcVar9)(param_1,param_4);
    break;
  case 0x25:
    (*pcVar9)(param_1,param_3,param_4);
    break;
  case 0x26:
    break;
  case 0x27:
    break;
  case 0x28:
    break;
  case 0x29:
    break;
  case 0x2a:
    local_88[0] = (*pcVar9)(param_1,param_4);
    break;
  case 0x2b:
    (*pcVar9)(param_1,param_3,param_4);
LAB_00031758:
    local_88[0] = 1;
    break;
  case 0x2c:
    uVar4 = FUN_0002ffec(param_4);
    (*pcVar9)(param_1,uVar4);
    break;
  case 0x2d:
    uVar4 = FUN_0002ffec(param_3);
    local_88[0] = (*pcVar9)(param_1,uVar4,param_4);
    break;
  case 0x2e:
    break;
  case 0x2f:
    (*pcVar9)(param_1,param_3,param_4);
    break;
  case 0x30:
    (*pcVar9)(param_1,param_3 & 0xffff,param_3 >> 0x10,param_4);
    break;
  case 0x31:
    (*pcVar9)(param_1,param_3,(int)sVar1,iVar2);
  }
LAB_00031864:
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = local_88[0];
  }
  return 1;
}


// 0003187c FUN_0003187c

undefined1 * FUN_0003187c(undefined1 *param_1)

{
  FUN_0002f584();
  *param_1 = 0x38;
  param_1[1] = 6;
  param_1[2] = 4;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0x28) = 1;
  return param_1;
}


// 000318d8 FUN_000318d8

undefined4 FUN_000318d8(int *param_1,uint param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_48 [4];
  uint local_44;
  int local_20;
  
  uVar1 = param_2 & 0xffff;
  param_2 = param_2 >> 0x10;
  if (param_3 == 0) {
    if (uVar1 == 0) {
      return 0;
    }
    FUN_0003187c(auStack_48);
    local_44 = uVar1;
    (**(code **)(*param_1 + 0xc))(param_1,uVar1,0xffffffff,auStack_48,0);
    if (local_20 != 0) {
      param_2 = 0;
LAB_00031948:
      uVar2 = (**(code **)(*param_1 + 0xc))(param_1,uVar1,param_2,0,0);
      return uVar2;
    }
  }
  else {
    iVar3 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
    if ((*(int *)(iVar3 + 0x120) != param_1[7]) && (iVar3 = FUN_00032494(param_3,0), iVar3 == 0)) {
      if (uVar1 == 0) {
        return 0;
      }
      goto LAB_00031948;
    }
  }
  return 1;
}


// 000319c4 FUN_000319c4

undefined4 FUN_000319c4(int *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  HWND hWnd;
  uint uVar4;
  undefined4 local_28;
  undefined4 *local_24;
  
  hWnd = (HWND)*param_3;
  uVar1 = GetDlgCtrlID(hWnd);
  uVar4 = param_3[2];
  iVar2 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  if ((*(int *)(iVar2 + 0x120) == param_1[7]) || (iVar2 = FUN_00032494(hWnd,param_4), iVar2 != 0)) {
    uVar3 = 1;
  }
  else {
    local_28 = param_4;
    local_24 = param_3;
    uVar3 = (**(code **)(*param_1 + 0xc))
                      (param_1,uVar1 & 0xffff,uVar4 & 0xffff | 0x4e0000,&local_28,0);
  }
  return uVar3;
}


// 00031a70 FUN_00031a70

int * FUN_00031a70(int param_1)

{
  HWND hWnd;
  int iVar1;
  int *piVar2;
  
  if ((param_1 != 0) && (hWnd = *(HWND *)(param_1 + 0x1c), hWnd != (HWND)0x0)) {
    while( true ) {
      GetParent(hWnd);
      piVar2 = (int *)FUN_0002ffec();
      if (piVar2 == (int *)0x0) break;
      iVar1 = (**(code **)(*piVar2 + 0xa8))(piVar2);
      if (iVar1 != 0) {
        return piVar2;
      }
      hWnd = (HWND)piVar2[7];
    }
  }
  return (int *)0x0;
}


// 00031acc FUN_00031acc

HWND FUN_00031acc(HWND param_1)

{
  int iVar1;
  HWND pHVar2;
  uint uVar3;
  
  iVar1 = FUN_0003001c();
  if (iVar1 == 0) {
    uVar3 = GetWindowLongW(param_1,-0x10);
    if ((uVar3 & 0x40000000) == 0) {
      pHVar2 = GetWindow(param_1,4);
    }
    else {
      pHVar2 = GetParent(param_1);
    }
  }
  else {
    iVar1 = FUN_0002ad10();
    if (iVar1 == 0) {
      pHVar2 = (HWND)0x0;
    }
    else {
      pHVar2 = *(HWND *)(iVar1 + 0x1c);
    }
  }
  return pHVar2;
}


// 00031b24 FUN_00031b24

undefined4 FUN_00031b24(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if ((param_1 == 0) || (iVar2 = *(int *)(param_1 + 0x1c), *(int *)(param_1 + 0x1c) == 0)) {
    uVar1 = 0;
  }
  else {
    do {
      iVar3 = iVar2;
      iVar2 = FUN_00031acc(iVar3);
    } while (iVar2 != 0);
    uVar1 = FUN_0002ffec(iVar3);
  }
  return uVar1;
}


// 00031b68 FUN_00031b68

bool FUN_00031b68(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  GetForegroundWindow();
  iVar1 = FUN_0002ffec();
  FUN_00031b24(param_1);
  GetActiveWindow();
  iVar2 = FUN_0002ffec();
  return iVar1 == iVar2;
}


// 00031b9c FUN_00031b9c

int * FUN_00031b9c(int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  if ((param_1 == (int *)0x0) || (param_1[7] == 0)) {
    param_1 = (int *)0x0;
  }
  else {
    iVar2 = (**(code **)(*param_1 + 0xa8))(param_1);
    piVar3 = param_1;
    if (iVar2 == 0) {
      param_1 = (int *)FUN_00031a70(param_1);
      piVar3 = param_1;
    }
    while (piVar1 = piVar3, piVar1 != (int *)0x0) {
      piVar3 = (int *)FUN_00031a70(piVar1);
      param_1 = piVar1;
    }
  }
  return param_1;
}


// 00031c10 FUN_00031c10

void FUN_00031c10(int param_1,LPCWSTR param_2,LPCWSTR param_3,UINT param_4)

{
  int iVar1;
  HWND hWnd;
  
  if (param_3 == (LPCWSTR)0x0) {
    iVar1 = FUN_0003f4f4();
    param_3 = *(LPCWSTR *)(iVar1 + 0x10);
  }
  hWnd = (HWND)0x0;
  if (param_1 != 0) {
    hWnd = *(HWND *)(param_1 + 0x1c);
  }
  MessageBoxW(hWnd,param_2,param_3,param_4);
  return;
}


// 00031c4c FUN_00031c4c

int FUN_00031c4c(HWND param_1,int param_2,int param_3)

{
  HWND hWnd;
  HWND pHVar1;
  int iVar2;
  UINT uCmd;
  
  hWnd = GetDlgItem(param_1,param_2);
  if (hWnd != (HWND)0x0) {
    pHVar1 = GetWindow(hWnd,5);
    if ((pHVar1 != (HWND)0x0) && (iVar2 = FUN_00031c4c(hWnd,param_2,param_3), iVar2 != 0)) {
      return iVar2;
    }
    if (param_3 == 0) {
      iVar2 = FUN_0002ffec();
      return iVar2;
    }
    iVar2 = FUN_0003001c(hWnd);
    if (iVar2 != 0) {
      return iVar2;
    }
  }
  uCmd = 5;
  while( true ) {
    param_1 = GetWindow(param_1,uCmd);
    if (param_1 == (HWND)0x0) {
      return 0;
    }
    iVar2 = FUN_00031c4c(param_1,param_2,param_3);
    if (iVar2 != 0) break;
    uCmd = 2;
  }
  return iVar2;
}


// 00031cf4 FUN_00031cf4

void FUN_00031cf4(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4,int param_5,int param_6)

{
  HWND hWnd;
  int iVar1;
  HWND pHVar2;
  int iVar3;
  
  for (hWnd = GetWindow(param_1,5); hWnd != (HWND)0x0; hWnd = GetWindow(hWnd,2)) {
    if (param_6 == 0) {
      SendMessageW(hWnd,param_2,param_3,param_4);
    }
    else {
      iVar1 = FUN_0003001c();
      if (iVar1 != 0) {
        FUN_0002fd40(iVar1,*(undefined4 *)(iVar1 + 0x1c),param_2,param_3,param_4);
      }
    }
    if ((param_5 != 0) && (pHVar2 = GetWindow(hWnd,5), pHVar2 != (HWND)0x0)) {
      FUN_00031cf4(hWnd,param_2,param_3,param_4,param_5,param_6);
    }
  }
  iVar1 = FUN_0003001c(param_1);
  if (((iVar1 != 0) && (iVar3 = FUN_0002ed1c(iVar1,&CFrameWnd::classCFrameWnd), iVar3 != 0)) &&
     (*(HWND *)(iVar1 + 0x48) != (HWND)0x0)) {
    if (param_6 == 0) {
      SendMessageW(*(HWND *)(iVar1 + 0x48),param_2,param_3,param_4);
    }
    else {
      iVar1 = FUN_0003001c();
      if (iVar1 != 0) {
        FUN_0002fd40(iVar1,*(undefined4 *)(iVar1 + 0x1c),param_2,param_3,param_4);
      }
    }
  }
  return;
}


// 00031e2c FUN_00031e2c

void FUN_00031e2c(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x60))();
  if (iVar1 == 0) {
    iVar1 = param_1[7];
  }
  else {
    iVar1 = *(int *)(iVar1 + 0x1c);
    param_2 = 2;
  }
                    /* WARNING: Could not recover jumptable at 0x0002cc70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  SetScrollPos(iVar1,param_2,param_3,param_4);
  return;
}


// 00031e74 FUN_00031e74

int FUN_00031e74(int *param_1,int param_2)

{
  BOOL BVar1;
  int iVar2;
  HWND hwnd;
  tagSCROLLINFO local_28;
  
  iVar2 = (**(code **)(*param_1 + 0x60))();
  if (iVar2 == 0) {
    hwnd = (HWND)param_1[7];
  }
  else {
    hwnd = *(HWND *)(iVar2 + 0x1c);
    param_2 = 2;
  }
  memset(&local_28,0,0x1c);
  local_28.cbSize = 0x1c;
  local_28.fMask = 4;
  BVar1 = GetScrollInfo(hwnd,param_2,&local_28);
  iVar2 = 0;
  if (BVar1 != 0) {
    iVar2 = local_28.nPos;
  }
  return iVar2;
}


// 00031eac FUN_00031eac

void FUN_00031eac(int *param_1,int param_2,int param_3,int param_4,BOOL param_5)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x60))();
  if (iVar1 == 0) {
    SetScrollRange((HWND)param_1[7],param_2,param_3,param_4,param_5);
  }
  else {
    SetScrollRange(*(HWND *)(iVar1 + 0x1c),2,param_3,param_4,param_5);
  }
  return;
}


// 00031f18 FUN_00031f18

void FUN_00031f18(int *param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if (param_2 == 3) {
    FUN_00031f18(param_1,0);
    param_2 = 1;
  }
  iVar1 = (**(code **)(*param_1 + 0x60))(param_1,param_2);
  if (iVar1 == 0) {
    FUN_0002b2b0(param_1[7],param_2,param_3);
  }
  else {
    FUN_00033dcc(iVar1,param_3);
  }
  return;
}


// 00031f7c FUN_00031f7c

undefined4 FUN_00031f7c(int *param_1,int param_2,LPCSCROLLINFO param_3,BOOL param_4)

{
  undefined4 uVar1;
  int iVar2;
  HWND hwnd;
  
  if (DAT_002de534 < 0x333) {
    uVar1 = 0;
  }
  else {
    hwnd = (HWND)param_1[7];
    if ((param_2 != 2) && (iVar2 = (**(code **)(*param_1 + 0x60))(param_1,param_2), iVar2 != 0)) {
      hwnd = *(HWND *)(iVar2 + 0x1c);
      param_2 = 2;
    }
    param_3->cbSize = 0x1c;
    SetScrollInfo(hwnd,param_2,param_3,param_4);
    uVar1 = 1;
  }
  return uVar1;
}


// 00031ffc FUN_00031ffc

void FUN_00031ffc(int param_1,int param_2,int param_3,RECT *param_4,RECT *param_5)

{
  BOOL BVar1;
  HWND hWnd;
  int *piVar2;
  tagRECT local_2c;
  
  BVar1 = IsWindowVisible(*(HWND *)(param_1 + 0x1c));
  if (((BVar1 == 0) && (param_4 == (RECT *)0x0)) && (param_5 == (RECT *)0x0)) {
    for (hWnd = GetWindow(*(HWND *)(param_1 + 0x1c),5); hWnd != (HWND)0x0; hWnd = GetWindow(hWnd,2))
    {
      GetWindowRect(hWnd,&local_2c);
      FUN_000362e0(param_1,&local_2c);
      SetWindowPos(hWnd,(HWND)0x0,local_2c.left + param_2,local_2c.top + param_3,0,0,0x15);
    }
  }
  else {
    ScrollWindowEx(*(HWND *)(param_1 + 0x1c),param_2,param_3,param_4,param_5,(HRGN)0x0,(LPRECT)0x0,6
                  );
  }
  piVar2 = *(int **)(param_1 + 0x38);
  if ((piVar2 != (int *)0x0) && (param_4 == (RECT *)0x0)) {
    (**(code **)(*piVar2 + 0x54))(piVar2,param_2,param_3);
  }
  return;
}


// 00032108 FUN_00032108

void FUN_00032108(int param_1,uint param_2,uint param_3,uint param_4,int param_5,LPRECT param_6,
                 undefined1 *param_7,int param_8)

{
  bool bVar1;
  HWND hWnd;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  tagRECT *ptVar7;
  int iVar8;
  HWND pHVar9;
  HWND pHVar10;
  uint local_4c;
  tagRECT local_48;
  LONG local_38;
  LONG local_34;
  int local_30;
  
  local_30 = param_8;
  local_34 = 0;
  pHVar9 = (HWND)0x0;
  local_38 = 0;
  if (param_7 == (undefined1 *)0x0) {
    GetClientRect(*(HWND *)(param_1 + 0x1c),&local_48);
  }
  else {
    iVar3 = 0x10;
    ptVar7 = &local_48;
    do {
      iVar6 = iVar3 + -1;
      *(undefined1 *)&ptVar7->left = *param_7;
      bVar1 = 0 < iVar3;
      param_7 = param_7 + 1;
      iVar3 = iVar6;
      ptVar7 = (tagRECT *)((int)&ptVar7->left + 1);
    } while (iVar6 != 0 && bVar1);
  }
  local_4c = (uint)(param_5 != 1);
  for (hWnd = GetWindow(*(HWND *)(param_1 + 0x1c),5); hWnd != (HWND)0x0; hWnd = GetWindow(hWnd,2)) {
    uVar2 = GetDlgCtrlID(hWnd);
    uVar2 = uVar2 & 0xffff;
    iVar3 = FUN_0003001c(hWnd);
    pHVar10 = pHVar9;
    if ((uVar2 == 0xe40a) && (iVar6 = FUN_0003001c(hWnd), iVar6 != 0)) {
      iVar4 = FUN_0002ed1c(iVar6,&CCeDocList::classCCeDocList);
      iVar8 = 0;
      if (iVar4 != 0) {
        iVar8 = *(int *)(iVar6 + 0x44);
      }
      if (iVar4 != 0 && iVar8 != 0) {
        pHVar10 = hWnd;
      }
    }
    pHVar9 = hWnd;
    if ((((uVar2 != param_4) && (pHVar9 = pHVar10, param_2 <= uVar2)) && (uVar2 <= param_3)) &&
       (iVar3 != 0)) {
      SendMessageW(hWnd,0x361,0,(LPARAM)&local_4c);
    }
  }
  if (param_5 == 1) {
    if (param_8 == 0) {
      param_6->top = 0;
      param_6->right = local_38;
      param_6->left = 0;
      param_6->bottom = local_34;
    }
    else {
      CopyRect(param_6,&local_48);
    }
  }
  else if ((param_4 != 0) && (pHVar9 != (HWND)0x0)) {
    piVar5 = (int *)FUN_0002ffec(pHVar9);
    if (param_5 == 2) {
      local_48.left = param_6->left + local_48.left;
      local_48.top = param_6->top + local_48.top;
      local_48.right = local_48.right - param_6->right;
      local_48.bottom = local_48.bottom - param_6->bottom;
    }
    (**(code **)(*piVar5 + 0x5c))(piVar5,&local_48,0);
    FUN_00032324(&local_4c,pHVar9,&local_48);
  }
  return;
}


// 00032324 FUN_00032324

void FUN_00032324(int *param_1,HWND param_2,RECT *param_3)

{
  HWND hWnd;
  BOOL BVar1;
  int X;
  int Y;
  undefined1 auStack_24 [16];
  
  hWnd = GetParent(param_2);
  if ((param_1 == (int *)0x0) || (*param_1 != 0)) {
    GetWindowRect(param_2,(LPRECT)auStack_24);
    ScreenToClient(hWnd,(LPPOINT)auStack_24);
    ScreenToClient(hWnd,(LPPOINT)(auStack_24 + 8));
    BVar1 = EqualRect((RECT *)auStack_24,param_3);
    if (BVar1 == 0) {
      X = param_3->left;
      Y = param_3->top;
      if (param_1 == (int *)0x0) {
        SetWindowPos(param_2,(HWND)0x0,X,Y,param_3->right - X,param_3->bottom - Y,0x14);
      }
      else {
        SetWindowPos(param_2,(HWND)0x0,X,Y,param_3->right - X,param_3->bottom - Y,0x14);
        *param_1 = 1;
      }
    }
  }
  return;
}


// 00032404 FUN_00032404

void FUN_00032404(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_00033b4c();
  if (param_3 == 0) {
    uVar1 = uVar1 & 0xfffffdff;
  }
  uVar2 = FUN_00033b14(param_1);
                    /* WARNING: Could not recover jumptable at 0x0002ccdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  AdjustWindowRectEx(param_2,uVar2 & 0xffcfffff,0,uVar1);
  return;
}


// 00032444 FUN_00032444

void FUN_00032444(int *param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  (**(code **)(*param_1 + 0xa0))
            (param_1,*(undefined4 *)(iVar1 + 0x40),*(undefined4 *)(iVar1 + 0x44),
             *(undefined4 *)(iVar1 + 0x48),param_2);
  return;
}


// 00032494 FUN_00032494

undefined4 FUN_00032494(HWND param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  HWND pHVar3;
  undefined4 uVar4;
  undefined1 auStack_54 [28];
  undefined4 local_38;
  int local_18;
  
  iVar1 = FUN_0002ff90(0);
  if (iVar1 != 0) {
    iVar2 = FUN_0002e298(iVar1 + 4,param_1);
    if (iVar2 != 0) {
      uVar4 = FUN_00032444(iVar2,param_2);
      return uVar4;
    }
    pHVar3 = GetParent(param_1);
    iVar1 = FUN_0002e298(iVar1 + 4,pHVar3);
    if (((iVar1 != 0) && (*(int *)(iVar1 + 0x38) != 0)) &&
       (local_18 = FUN_0002e298(*(int *)(iVar1 + 0x38) + 0x20,param_1), local_18 != 0)) {
      FUN_0002fa74(auStack_54,param_1);
      uVar4 = FUN_00032444(auStack_54,param_2);
      local_38 = 0;
      FUN_00030500(auStack_54);
      return uVar4;
    }
  }
  return 0;
}


// 00032558 FUN_00032558

undefined4 FUN_00032558(int param_1,uint param_2,WPARAM param_3,LPARAM param_4,LRESULT *param_5)

{
  LRESULT LVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0x3c) == 0) {
    uVar2 = FUN_000325d0(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    LVar1 = SendMessageW(*(HWND *)(param_1 + 0x1c),param_2 + 0x2000,param_3,param_4);
    if (((param_2 < 0x132) || (0x138 < param_2)) || (LVar1 != 0)) {
      if (param_5 != (LRESULT *)0x0) {
        *param_5 = LVar1;
      }
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}


// 000325d0 FUN_000325d0

undefined4 FUN_000325d0(undefined4 param_1,uint param_2,uint param_3,int param_4,int *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int *local_14;
  uint local_10;
  int local_c;
  
  if (param_2 < 0x2b) {
LAB_00032628:
    if ((0x131 < param_2) && (param_2 < 0x139)) {
      local_c = param_2 - 0x132;
      local_10 = param_3;
      uVar1 = FUN_00030f88(param_1,0xbc19,0,&local_14,param_5);
      if (*param_5 != 0) {
        return uVar1;
      }
    }
LAB_00032678:
    uVar1 = 0;
  }
  else {
    if ((0x2f < param_2) && (param_2 != 0x39)) {
      if (param_2 == 0x4e) {
        local_14 = param_5;
        local_10 = param_4;
        uVar1 = FUN_0002f3c4(param_1,0,*(ushort *)(param_4 + 8) | 0xbc4e0000,&local_14,0);
        return uVar1;
      }
      if (param_2 == 0x111) {
        iVar2 = FUN_0002f3c4(param_1,0,param_3 >> 0x10 | 0xbd110000,0,0);
        if (iVar2 != 0) {
          if (param_5 != (int *)0x0) {
            *param_5 = 1;
          }
          return 1;
        }
        goto LAB_00032678;
      }
      if ((param_2 < 0x114) || (0x115 < param_2)) goto LAB_00032628;
    }
    uVar1 = FUN_00030f88(param_1,param_2 + 0xbc00,param_3,param_4,param_5);
  }
  return uVar1;
}


// 00032710 FUN_00032710

undefined4 FUN_00032710(void)

{
  return 0;
}


// 00032718 FUN_00032718

void FUN_00032718(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0003f4f4();
  if ((*(int *)(iVar1 + 4) != 0) && (*(int *)(*(int *)(iVar1 + 4) + 0x1c) == param_1)) {
    FUN_00033f94(&afxData);
  }
  uVar2 = FUN_00033b14(param_1);
  if ((uVar2 & 0x40000000) == 0) {
    FUN_00031cf4(*(undefined4 *)(param_1 + 0x1c),0x15,0,0,1,1);
  }
  FUN_0002ff50(param_1);
  return;
}


// 000327a0 FUN_000327a0

undefined4 FUN_000327a0(undefined4 param_1)

{
  SHORT SVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar2 = FUN_00033b14();
  if (((((uVar2 & 0x40000000) == 0) && (iVar3 = FUN_0002acc0(), iVar3 != 0)) &&
      (SVar1 = GetKeyState(0x10), -1 < SVar1)) &&
     ((SVar1 = GetKeyState(0x11), -1 < SVar1 && (SVar1 = GetKeyState(0x12), -1 < SVar1)))) {
    SendMessageW(*(HWND *)(iVar3 + 0x1c),0x111,0xe146,0);
    uVar4 = 1;
  }
  else {
    uVar4 = FUN_0002ff50(param_1);
  }
  return uVar4;
}


// 00032890 FUN_00032890

void FUN_00032890(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  if ((param_4 == 0) || (iVar1 = FUN_00032444(param_4,0), iVar1 == 0)) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 000328c0 FUN_000328c0

void FUN_000328c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  if ((param_4 == 0) || (iVar1 = FUN_00032444(param_4,0), iVar1 == 0)) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 000328f0 FUN_000328f0

void FUN_000328f0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 local_c [4];
  
  iVar1 = FUN_00032444(param_3,local_c);
  if (iVar1 == 0) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 00032920 FUN_00032920

undefined4 FUN_00032920(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_1c;
  
  iVar1 = FUN_00032444(param_3,&local_1c);
  if (iVar1 == 0) {
    iVar1 = FUN_0003f014(&DAT_002de290,&LAB_0003f644);
    uVar3 = 0;
    if (param_3 != 0) {
      uVar3 = *(undefined4 *)(param_3 + 0x1c);
    }
    iVar2 = FUN_000329ac(*(undefined4 *)(param_2 + 4),uVar3,param_4,*(undefined4 *)(iVar1 + 4),
                         *(undefined4 *)(iVar1 + 8));
    if (iVar2 == 0) {
      local_1c = FUN_0002ff50(param_1);
    }
    else {
      local_1c = *(undefined4 *)(iVar1 + 4);
    }
  }
  return local_1c;
}


// 000329ac FUN_000329ac

undefined4 FUN_000329ac(HDC param_1,undefined4 param_2,int param_3,HANDLE param_4,COLORREF param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_18 [4];
  COLORREF local_14;
  
  if ((((param_1 == (HDC)0x0) || (param_4 == (HANDLE)0x0)) || (param_3 == 1)) ||
     ((param_3 == 0 || ((param_3 == 2 && (iVar1 = FUN_00035d74(param_2,2), iVar1 == 0)))))) {
    uVar2 = 0;
  }
  else {
    GetObjectW(param_4,0xc,auStack_18);
    SetBkColor(param_1,local_14);
    if (param_5 == 0xffffffff) {
      param_5 = GetSysColor(0x40000008);
    }
    SetTextColor(param_1,param_5);
    uVar2 = 1;
  }
  return uVar2;
}


// 00032a4c FUN_00032a4c

undefined4 FUN_00032a4c(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_74;
  undefined1 auStack_64 [16];
  undefined1 auStack_54 [52];
  int *local_20;
  
  FUN_00032b1c(auStack_64,param_1,param_2);
  iVar1 = FUN_0003f170();
  uVar3 = *(undefined4 *)(iVar1 + 0x120);
  *(int *)(iVar1 + 0x120) = param_1[7];
  local_74 = 0;
  FUN_0002f060(auStack_54);
  iVar2 = setjmp(auStack_54);
  if (iVar2 == 0) {
    (**(code **)(*param_1 + 0x7c))(param_1,auStack_64);
    local_74 = 1;
  }
  else {
    iVar2 = FUN_0002f1b0(&CUserException::classCUserException);
    if (iVar2 == 0) {
      (**(code **)(*local_20 + 0x10))(local_20,0x30,0xf108);
    }
  }
  FUN_0002f0c0();
  *(undefined4 *)(iVar1 + 0x120) = uVar3;
  return local_74;
}


// 00032b1c FUN_00032b1c

void FUN_00032b1c(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  param_1[1] = param_2;
  param_1[2] = 0;
  return;
}


// 00032b30 FUN_00032b30

void FUN_00032b30(int param_1,int param_2)

{
  uint uVar1;
  HWND hWnd;
  HWND pHVar2;
  int iVar3;
  tagRECT *ptVar4;
  int iVar5;
  tagRECT *ptVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  bool bVar11;
  tagRECT local_4c;
  tagRECT local_3c;
  tagRECT local_2c;
  
  uVar1 = FUN_00033b14();
  if (param_2 == 0) {
    if ((uVar1 & 0x40000000) == 0) {
      hWnd = GetWindow(*(HWND *)(param_1 + 0x1c),4);
    }
    else {
      hWnd = GetParent(*(HWND *)(param_1 + 0x1c));
    }
    if ((hWnd != (HWND)0x0) && (pHVar2 = (HWND)SendMessageW(hWnd,0x36b,0,0), pHVar2 != (HWND)0x0)) {
      hWnd = pHVar2;
    }
  }
  else {
    hWnd = *(HWND *)(param_2 + 0x1c);
  }
  GetWindowRect(*(HWND *)(param_1 + 0x1c),&local_2c);
  if ((uVar1 & 0x40000000) == 0) {
    if ((hWnd != (HWND)0x0) && (uVar1 = GetWindowLongW(hWnd,-0x10), (uVar1 & 0x10000000) == 0)) {
      hWnd = (HWND)0x0;
    }
    FUN_0002ae98(0x30,0,&local_3c,0);
    if (hWnd == (HWND)0x0) {
      iVar7 = 0x10;
      ptVar4 = &local_4c;
      ptVar6 = &local_3c;
      do {
        iVar3 = iVar7 + -1;
        *(char *)&ptVar4->left = (char)ptVar6->left;
        bVar10 = 0 < iVar7;
        iVar7 = iVar3;
        ptVar4 = (tagRECT *)((int)&ptVar4->left + 1);
        ptVar6 = (tagRECT *)((int)&ptVar6->left + 1);
      } while (iVar3 != 0 && bVar10);
    }
    else {
      GetWindowRect(hWnd,&local_4c);
    }
  }
  else {
    pHVar2 = GetParent(*(HWND *)(param_1 + 0x1c));
    GetClientRect(pHVar2,&local_3c);
    GetClientRect(hWnd,&local_4c);
    MapWindowPoints(hWnd,pHVar2,(LPPOINT)&local_4c,2);
  }
  iVar7 = local_4c.right + local_4c.left;
  if (iVar7 < 0) {
    iVar7 = iVar7 + 1;
  }
  iVar3 = local_2c.right - local_2c.left;
  iVar5 = iVar3;
  if (iVar3 < 0) {
    iVar5 = iVar3 + 1;
  }
  iVar5 = (iVar7 >> 1) - (iVar5 >> 1);
  iVar7 = local_2c.bottom - local_2c.top;
  iVar8 = local_4c.bottom + local_4c.top;
  if (iVar8 < 0) {
    iVar8 = iVar8 + 1;
  }
  iVar9 = iVar7;
  if (iVar7 < 0) {
    iVar9 = iVar7 + 1;
  }
  iVar9 = (iVar8 >> 1) - (iVar9 >> 1);
  bVar11 = SBORROW4(iVar5,local_3c.left);
  iVar8 = iVar5 - local_3c.left;
  bVar10 = iVar5 == local_3c.left;
  if (local_3c.left <= iVar5) {
    iVar3 = iVar3 + iVar5;
    bVar11 = SBORROW4(iVar3,local_3c.right);
    iVar8 = iVar3 - local_3c.right;
    bVar10 = iVar3 == local_3c.right;
    iVar3 = local_3c.right;
    local_3c.left = iVar5;
  }
  if (!bVar10 && iVar8 < 0 == bVar11) {
    local_3c.left = (iVar3 - local_2c.right) + local_2c.left;
  }
  bVar11 = SBORROW4(iVar9,local_4c.top);
  iVar5 = iVar9 - local_4c.top;
  bVar10 = iVar9 == local_4c.top;
  if (local_4c.top <= iVar9) {
    iVar7 = iVar7 + iVar9;
    bVar11 = SBORROW4(iVar7,local_3c.bottom);
    iVar5 = iVar7 - local_3c.bottom;
    bVar10 = iVar7 == local_3c.bottom;
    iVar3 = local_3c.bottom;
    local_4c.top = iVar9;
  }
  if (!bVar10 && iVar5 < 0 == bVar11) {
    local_4c.top = (local_2c.top - local_2c.bottom) + iVar3;
  }
  FUN_00033cec(param_1,0,local_3c.left,local_4c.top,0xffffffff,0xffffffff,0x15);
  return;
}


// 00032d14 FUN_00032d14

undefined4 FUN_00032d14(undefined4 param_1,LPCWSTR param_2)

{
  int iVar1;
  HRSRC hResInfo;
  undefined4 uVar2;
  HMODULE hModule;
  HGLOBAL pvVar3;
  
  pvVar3 = (HGLOBAL)0x0;
  if (param_2 != (LPCWSTR)0x0) {
    iVar1 = FUN_0003f4f4();
    hModule = *(HMODULE *)(iVar1 + 0xc);
    hResInfo = FindResourceW(hModule,param_2,(LPCWSTR)0xf0);
    if ((hResInfo != (HRSRC)0x0) &&
       (pvVar3 = LoadResource(hModule,hResInfo), pvVar3 == (HGLOBAL)0x0)) {
      return 0;
    }
  }
  uVar2 = FUN_00032d70(param_1,pvVar3);
  return uVar2;
}


// 00032d70 FUN_00032d70

int FUN_00032d70(int param_1,ushort *param_2)

{
  ushort uVar1;
  size_t _Size;
  void *_Dst;
  HWND hWnd;
  LRESULT LVar2;
  uint uVar3;
  UINT Msg;
  int iVar4;
  int local_28;
  
  iVar4 = 1;
  local_28 = 1;
  if (param_2 != (ushort *)0x0) {
    do {
      uVar1 = *param_2;
      if (uVar1 == 0) break;
      uVar3 = (uint)param_2[1];
      _Size = *(size_t *)(param_2 + 2);
      Msg = 0x403;
      if (uVar3 != 0x1234) {
        if (uVar3 == 0x401) {
          Msg = 0x180;
        }
        else {
          Msg = uVar3;
          if (uVar3 == 0x403) {
            Msg = 0x143;
          }
        }
      }
      if ((Msg != 0x403) &&
         (((Msg == 0x180 || (Msg == 0x143)) &&
          (_Dst = malloc(_Size), iVar4 = local_28, _Dst != (void *)0x0)))) {
        memmove(_Dst,param_2 + 4,_Size);
        hWnd = GetDlgItem(*(HWND *)(param_1 + 0x1c),(uint)uVar1);
        LVar2 = SendMessageW(hWnd,Msg,0,(LPARAM)_Dst);
        if (LVar2 == -1) {
          local_28 = 0;
        }
        free(_Dst);
        iVar4 = local_28;
      }
      param_2 = (ushort *)(_Size + (int)(param_2 + 4));
    } while (iVar4 != 0);
    if (iVar4 == 0) {
      return 0;
    }
  }
  FUN_00031cf4(*(undefined4 *)(param_1 + 0x1c),0x364,0,0,0,0);
  return iVar4;
}


// 00032ee4 FUN_00032ee4

void FUN_00032ee4(int param_1,undefined4 param_2,int param_3)

{
  HWND hWnd;
  int iVar1;
  uint uVar2;
  undefined1 auStack_88 [4];
  uint local_84;
  undefined1 *local_74;
  undefined1 auStack_60 [28];
  HWND local_44;
  
  FUN_0002f584(auStack_88);
  FUN_0002fa00(auStack_60);
  hWnd = GetWindow(*(HWND *)(param_1 + 0x1c),5);
  do {
    if (hWnd == (HWND)0x0) {
      local_44 = (HWND)0x0;
      FUN_00030500(auStack_60);
      return;
    }
    local_44 = hWnd;
    local_84 = GetDlgCtrlID(hWnd);
    local_84 = local_84 & 0xffff;
    local_74 = auStack_60;
    iVar1 = FUN_0003001c(hWnd);
    if (((iVar1 == 0) || (iVar1 = FUN_0002f3c4(iVar1,0,0xbd11ffff,auStack_88,0), iVar1 == 0)) &&
       (iVar1 = FUN_0002f3c4(param_1,local_84,0xffffffff,auStack_88,0), iVar1 == 0)) {
      iVar1 = param_3;
      if (param_3 != 0) {
        uVar2 = SendMessageW(local_44,0x87,0,0);
        if ((uVar2 & 0x2000) != 0) {
          uVar2 = FUN_00033b14(auStack_60);
          uVar2 = uVar2 & 0xf;
          if (((uVar2 != 3) && (uVar2 != 6)) && ((uVar2 != 7 && (uVar2 != 9)))) goto LAB_00032fe4;
        }
        iVar1 = 0;
      }
LAB_00032fe4:
      FUN_0002f79c(auStack_88,param_2,iVar1);
    }
    hWnd = GetWindow(hWnd,2);
  } while( true );
}


// 00033020 FUN_00033020

undefined4 FUN_00033020(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_2 + 4);
  if (((uVar2 < 0x100) || (0x108 < uVar2)) && ((uVar2 < 0x200 || (0x209 < uVar2)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00033ac0();
  }
  return uVar1;
}


// 0003306c FUN_0003306c

int FUN_0003306c(int *param_1,uint param_2)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  BOOL BVar5;
  int iVar6;
  int *piVar7;
  LPMSG lpMsg;
  
  bVar1 = true;
  if ((param_2 & 4) != 0) {
    uVar3 = FUN_00033b14();
    bVar2 = true;
    if ((uVar3 & 0x10000000) == 0) goto LAB_0003309c;
  }
  bVar2 = false;
LAB_0003309c:
  GetParent((HWND)param_1[7]);
  param_1[10] = param_1[10] | 0x18;
  iVar4 = FUN_0002f1d0();
  lpMsg = (LPMSG)(iVar4 + 0x30);
  do {
    if ((bVar1) && (BVar5 = PeekMessageW(lpMsg,(HWND)0x0,0,0,0), BVar5 == 0)) {
      if (bVar2) {
        FUN_00033d64(param_1,1);
        UpdateWindow((HWND)param_1[7]);
        bVar2 = false;
      }
      bVar1 = false;
    }
    do {
      BVar5 = PeekMessageW(lpMsg,(HWND)0x0,0,0,0);
      if ((((BVar5 == 0) || (*(uint *)(iVar4 + 0x34) < 0x200)) || (0x209 < *(uint *)(iVar4 + 0x34)))
         || ((BVar5 = IsWindowEnabled(lpMsg->hwnd), BVar5 != 0 || (!bVar2)))) {
        piVar7 = (int *)FUN_0002f1d0();
        iVar6 = (**(code **)(*piVar7 + 0x58))();
        if (iVar6 == 0) {
          FUN_0003fd90(0);
          return -1;
        }
      }
      else {
        PeekMessageW(lpMsg,(HWND)0x0,0,0,1);
      }
      if ((bVar2) && ((*(int *)(iVar4 + 0x34) == 0x118 || (*(int *)(iVar4 + 0x34) == 0x104)))) {
        FUN_00033d64(param_1,1);
        UpdateWindow((HWND)param_1[7]);
        bVar2 = false;
      }
      iVar6 = (**(code **)(*param_1 + 0x68))(param_1);
      if (iVar6 == 0) {
        param_1[10] = param_1[10] & 0xffffffe7;
        return param_1[0xc];
      }
      piVar7 = (int *)FUN_0002f1d0();
      iVar6 = (**(code **)(*piVar7 + 0x60))(piVar7,lpMsg);
      if (iVar6 != 0) {
        bVar1 = true;
      }
      BVar5 = PeekMessageW(lpMsg,(HWND)0x0,0,0,0);
    } while (BVar5 != 0);
  } while( true );
}


// 00033268 FUN_00033268

void FUN_00033268(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x30) = param_2;
  if ((*(uint *)(param_1 + 0x28) & 0x10) != 0) {
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xffffffef;
    PostMessageW(*(HWND *)(param_1 + 0x1c),0,0,0);
  }
  return;
}


// 000332a0 FUN_000332a0

void FUN_000332a0(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x24) = param_2;
  FUN_0003f4f4();
  FUN_00030ba4(param_1);
  return;
}


// 000332bc FUN_000332bc

uint FUN_000332bc(undefined4 param_1,uint param_2)

{
  int iVar1;
  HMODULE hLibModule;
  uint uVar2;
  code *pcVar3;
  int iVar4;
  
  iVar1 = FUN_0002acec(s_COMMCTRL_DLL_00043fe0);
  hLibModule = (HMODULE)FUN_0002aedc(s_COMMCTRL_DLL_00043fe0);
  if (hLibModule == (HMODULE)0x0) {
    uVar2 = 0;
  }
  else {
    pcVar3 = (code *)FUN_0002ae38(hLibModule,s_InitCommonControlsEx_00043fc8);
    uVar2 = 0;
    if (pcVar3 == (code *)0x0) {
      if ((param_2 & 0x3fc0) == param_2) {
        InitCommonControls();
        uVar2 = 0x3fc0;
      }
    }
    else {
      iVar4 = (*pcVar3)(param_1);
      if ((iVar4 != 0) && (uVar2 = param_2, iVar1 == 0)) {
        InitCommonControls();
        uVar2 = param_2 | 0x3fc0;
      }
    }
    FreeLibrary(hLibModule);
  }
  return uVar2;
}


// 00033358 FUN_00033358

undefined4 FUN_00033358(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  code *local_40;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_28;
  wchar_t *local_20;
  
  iVar1 = FUN_0003f4f4();
  param_1 = param_1 & ~*(uint *)(iVar1 + 0x18);
  if (param_1 == 0) {
    uVar2 = 1;
  }
  else {
    uVar5 = 0;
    memset(&local_44,0,0x28);
    local_40 = FUN_0002b684;
    iVar3 = FUN_0003f4f4();
    local_34 = *(undefined4 *)(iVar3 + 8);
    local_2c = DAT_002de520;
    local_4c = 8;
    if ((param_1 & 1) != 0) {
      local_44 = 0xb;
      local_20 = L"AfxWnd42su";
      iVar3 = FUN_00030ba4(&local_44);
      if (iVar3 != 0) {
        uVar5 = 1;
      }
    }
    if ((param_1 & 0x20) != 0) {
      local_44 = local_44 | 0x8b;
      local_20 = L"AfxOleControl42su";
      iVar3 = FUN_00030ba4(&local_44);
      if (iVar3 != 0) {
        uVar5 = uVar5 | 0x20;
      }
    }
    if ((param_1 & 2) != 0) {
      local_44 = 0;
      local_20 = L"AfxControlBar42su";
      local_28 = 0x40000010;
      iVar3 = FUN_00030ba4(&local_44);
      if (iVar3 != 0) {
        uVar5 = uVar5 | 2;
      }
    }
    if ((param_1 & 4) != 0) {
      local_44 = 8;
      local_28 = 0;
      iVar3 = FUN_000332a0(&local_44,L"AfxMDIFrame42su",0x7a01);
      if (iVar3 != 0) {
        uVar5 = uVar5 | 4;
      }
    }
    if ((param_1 & 8) != 0) {
      local_44 = 0xb;
      local_28 = 0x40000006;
      iVar3 = FUN_000332a0(&local_44,L"AfxFrameOrView42su",0x7a02);
      if (iVar3 != 0) {
        uVar5 = uVar5 | 8;
      }
    }
    if ((param_1 & 0x10) != 0) {
      local_48 = 0xff;
      uVar4 = FUN_000332bc(&local_4c,0x3fc0);
      param_1 = param_1 & 0xffffc03f;
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x40) != 0) {
      local_48 = 0x10;
      uVar4 = FUN_000332bc(&local_4c,0x40);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x80) != 0) {
      local_48 = 2;
      uVar4 = FUN_000332bc(&local_4c,0x80);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x100) != 0) {
      local_48 = 8;
      uVar4 = FUN_000332bc(&local_4c,0x100);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x200) != 0) {
      local_48 = 0x20;
      uVar4 = FUN_000332bc(&local_4c,0x200);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x400) != 0) {
      local_48 = 1;
      uVar4 = FUN_000332bc(&local_4c,0x400);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x1000) != 0) {
      local_48 = 4;
      uVar4 = FUN_000332bc(&local_4c,0x1000);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x8000) != 0) {
      local_48 = 0x400;
      uVar4 = FUN_000332bc(&local_4c,0x8000);
      uVar5 = uVar5 | uVar4;
    }
    if ((param_1 & 0x20000) != 0) {
      local_48 = 0x100;
      uVar4 = FUN_000332bc(&local_4c,0x20000);
      uVar5 = uVar5 | uVar4;
    }
    uVar4 = *(uint *)(iVar1 + 0x18) | uVar5;
    *(uint *)(iVar1 + 0x18) = uVar4;
    if ((uVar4 & 0x3fc0) == 0x3fc0) {
      uVar5 = uVar5 | 0x10;
      *(uint *)(iVar1 + 0x18) = uVar4 | 0x10;
    }
    uVar2 = 1;
    if ((param_1 & uVar5) != param_1) {
      uVar2 = 0;
    }
  }
  return uVar2;
}


// 00033628 FUN_00033628

undefined4 FUN_00033628(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0xa0);
  if (((iVar1 == 0) || (iVar1 == 0xe002)) || (uVar2 = 1, iVar1 == 0xe001)) {
    uVar2 = 0;
  }
  return uVar2;
}


// 00033660 FUN_00033660

undefined4 FUN_00033660(int *param_1,HWND param_2)

{
  int iVar1;
  undefined4 uVar2;
  LONG *pLVar3;
  LONG LVar4;
  
  iVar1 = FUN_00030044();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    (**(code **)(*param_1 + 0x4c))(param_1);
    pLVar3 = (LONG *)(**(code **)(*param_1 + 0x78))(param_1);
    LVar4 = FUN_00030160();
    LVar4 = SetWindowLongW(param_2,-4,LVar4);
    if (*pLVar3 == 0) {
      *pLVar3 = LVar4;
    }
    uVar2 = 1;
  }
  return uVar2;
}


// 000336d0 FUN_000336d0

undefined4 FUN_000336d0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00031b9c();
  if (iVar1 == 0) {
LAB_00033714:
    uVar3 = 0;
  }
  else {
    if (param_2 == 0) {
      iVar2 = FUN_0002acc0();
      SetForegroundWindow(*(HWND *)(iVar2 + 0x1c));
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(iVar1 + 0xc4) = 0;
      iVar1 = SHDoneButton(*(undefined4 *)(iVar1 + 0x1c),2);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else {
      if (*(int *)(iVar1 + 0xc4) != 0) {
        *(undefined4 *)(*(int *)(iVar1 + 0xc4) + 0x40) = 0;
      }
      iVar2 = SHDoneButton(*(undefined4 *)(iVar1 + 0x1c),1);
      if (iVar2 == 0) goto LAB_00033714;
      *(int *)(iVar1 + 0xc4) = param_1;
      *(undefined4 *)(param_1 + 0x40) = 1;
    }
    uVar3 = 1;
  }
  return uVar3;
}


// 00033764 FUN_00033764

undefined4 FUN_00033764(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  memset(&local_24,0,0x10);
  local_28 = 0x14;
  local_24 = *(undefined4 *)(param_1 + 0x1c);
  local_18 = 1;
  local_20 = param_2;
  local_1c = param_3;
  iVar1 = SHRecognizeGesture(&local_28);
  if (iVar1 == 1000) {
    if (param_4 != 0) {
      local_18 = 2;
      SHRecognizeGesture(&local_28);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// 000337e8 FUN_000337e8

void FUN_000337e8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = FUN_00033764(param_1,param_3,param_4,1);
  if (iVar1 == 0) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 00033818 FUN_00033818

undefined1 *
FUN_00033818(undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  FUN_0002e060(param_1 + 4,10);
  FUN_0002e060(param_1 + 0x20,4);
  *param_1 = 0x48;
  param_1[1] = 6;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0002e0cc(param_1 + 0x20,7,0);
  *(undefined4 *)(param_1 + 0x3c) = param_2;
  *(undefined4 *)(param_1 + 0x40) = param_3;
  *(undefined4 *)(param_1 + 0x44) = param_4;
  return param_1;
}


// 00033890 FUN_00033890

int FUN_00033890(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined1 auStack_5c [56];
  
  if (param_2 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0002e298(param_1 + 4,param_2);
    if (iVar1 == 0) {
      iVar1 = FUN_0002e298(param_1 + 0x20,param_2);
      if (iVar1 == 0) {
        FUN_0002f060(auStack_5c);
        iVar1 = setjmp(auStack_5c);
        if (iVar1 == 0) {
          iVar1 = FUN_0002ed70(*(undefined4 *)(param_1 + 0x3c));
          if (iVar1 == 0) {
            FUN_0002d3cc();
          }
          piVar2 = (int *)FUN_0002e328(param_1 + 0x20,param_2);
          *piVar2 = iVar1;
        }
        else {
          FUN_0002f108(0);
          iVar1 = 0;
        }
        FUN_0002f0c0();
        piVar2 = (int *)(*(int *)(param_1 + 0x40) + iVar1);
        *piVar2 = param_2;
        if (*(int *)(param_1 + 0x44) == 2) {
          piVar2[1] = param_2;
        }
      }
      else {
        piVar2 = (int *)(*(int *)(param_1 + 0x40) + iVar1);
        *piVar2 = param_2;
        if (*(int *)(param_1 + 0x44) == 2) {
          piVar2[1] = param_2;
        }
      }
    }
  }
  return iVar1;
}


// 00033988 FUN_00033988

void FUN_00033988(int param_1)

{
  undefined4 *puVar1;
  int local_1c;
  int *local_18;
  undefined1 auStack_14 [4];
  
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x2c) == 0) {
      local_1c = 0;
    }
    else {
      local_1c = -1;
      do {
        FUN_0002e410(param_1 + 0x20,&local_1c,auStack_14,&local_18);
        puVar1 = (undefined4 *)(*(int *)(param_1 + 0x40) + (int)local_18);
        *puVar1 = 0;
        if (*(int *)(param_1 + 0x44) == 2) {
          puVar1[1] = 0;
        }
        if (local_18 != (int *)0x0) {
          (**(code **)(*local_18 + 4))(local_18,1);
        }
      } while (local_1c != 0);
    }
    FUN_0002e120(param_1 + 0x20);
  }
  return;
}


// 00033a28 FUN_00033a28

void FUN_00033a28(int param_1)

{
  (**(code **)(**(int **)(param_1 + 0x38) + 0x50))();
  return;
}


// 00033a44 FUN_00033a44

void FUN_00033a44(int param_1,int param_2)

{
  if (*(int **)(param_1 + 0x38) == (int *)0x0) {
    GetDlgItem(*(HWND *)(param_1 + 0x1c),param_2);
    FUN_0002ffec();
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x6c))();
  }
  return;
}


// 00033a7c FUN_00033a7c

void FUN_00033a7c(int param_1,int param_2)

{
  HWND hWnd;
  
  if (*(int **)(param_1 + 0x38) == (int *)0x0) {
    hWnd = GetDlgItem(*(HWND *)(param_1 + 0x1c),param_2);
    SendMessageW(hWnd,0xf0,0,0);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x38) + 0x84))();
  }
  return;
}


// 00033ac0 FUN_00033ac0

void FUN_00033ac0(int param_1,LPMSG param_2)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + 0x28) & 0x100) == 0) {
    IsDialogMessageW(*(HWND *)(param_1 + 0x1c),param_2);
  }
  else {
    iVar1 = FUN_0003f4f4();
    (**(code **)(**(int **)(iVar1 + 0x2038) + 0x24))(*(int **)(iVar1 + 0x2038),param_1,param_2);
  }
  return;
}


// 00033b14 FUN_00033b14

void FUN_00033b14(int param_1)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    GetWindowLongW(*(HWND *)(param_1 + 0x1c),-0x10);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x6c))();
  }
  return;
}


// 00033b4c FUN_00033b4c

void FUN_00033b4c(int param_1)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    GetWindowLongW(*(HWND *)(param_1 + 0x1c),-0x14);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x70))();
  }
  return;
}


// 00033b84 FUN_00033b84

void FUN_00033b84(int param_1)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    FUN_0002fb48(*(undefined4 *)(param_1 + 0x1c));
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x74))();
  }
  return;
}


// 00033bb8 FUN_00033bb8

void FUN_00033bb8(int param_1,LPCWSTR param_2)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    SetWindowTextW(*(HWND *)(param_1 + 0x1c),param_2);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x7c))();
  }
  return;
}


// 00033bec FUN_00033bec

void FUN_00033bec(int param_1,LPWSTR param_2,int param_3)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    GetWindowTextW(*(HWND *)(param_1 + 0x1c),param_2,param_3);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x80))();
  }
  return;
}


// 00033c20 FUN_00033c20

void FUN_00033c20(int param_1)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    GetWindowTextLengthW(*(HWND *)(param_1 + 0x1c));
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x88))();
  }
  return;
}


// 00033c54 FUN_00033c54

void FUN_00033c54(int param_1,LONG param_2)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    SetWindowLongW(*(HWND *)(param_1 + 0x1c),-0xc,param_2);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x90))();
  }
  return;
}


// 00033c90 FUN_00033c90

void FUN_00033c90(int param_1,int param_2,int param_3,int param_4,int param_5,BOOL param_6)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    MoveWindow(*(HWND *)(param_1 + 0x1c),param_2,param_3,param_4,param_5,param_6);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x94))();
  }
  return;
}


// 00033cec FUN_00033cec

void FUN_00033cec(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 UINT param_7)

{
  HWND hWndInsertAfter;
  
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    if (param_2 == 0) {
      hWndInsertAfter = (HWND)0x0;
    }
    else {
      hWndInsertAfter = *(HWND *)(param_2 + 0x1c);
    }
    SetWindowPos(*(HWND *)(param_1 + 0x1c),hWndInsertAfter,param_3,param_4,param_5,param_6,param_7);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x98))();
  }
  return;
}


// 00033d64 FUN_00033d64

void FUN_00033d64(int param_1,int param_2)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    ShowWindow(*(HWND *)(param_1 + 0x1c),param_2);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0x9c))();
  }
  return;
}


// 00033d98 FUN_00033d98

void FUN_00033d98(int param_1)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    IsWindowEnabled(*(HWND *)(param_1 + 0x1c));
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0xa0))();
  }
  return;
}


// 00033dcc FUN_00033dcc

void FUN_00033dcc(int param_1,BOOL param_2)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    EnableWindow(*(HWND *)(param_1 + 0x1c),param_2);
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0xa4))();
  }
  return;
}


// 00033e00 FUN_00033e00

void FUN_00033e00(int param_1)

{
  if (*(int **)(param_1 + 0x3c) == (int *)0x0) {
    SetFocus(*(HWND *)(param_1 + 0x1c));
    FUN_0002ffec();
  }
  else {
    (**(code **)(**(int **)(param_1 + 0x3c) + 0xa8))();
  }
  return;
}


// 00033e38 FUN_00033e38

void FUN_00033e38(int param_1,int param_2)

{
  HWND pHVar1;
  int iVar2;
  int *piVar3;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 0x3c) == 0)) {
    pHVar1 = GetParent(*(HWND *)(param_1 + 0x1c));
    iVar2 = FUN_0002e298(param_2 + 4,pHVar1);
    piVar3 = (int *)0x0;
    if (iVar2 != 0) {
      piVar3 = *(int **)(iVar2 + 0x38);
    }
    if (iVar2 != 0 && piVar3 != (int *)0x0) {
      (**(code **)(*piVar3 + 0x88))(piVar3,param_1);
    }
  }
  return;
}


// 00033e90 FUN_00033e90

undefined4 FUN_00033e90(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f52c();
  if ((*(int *)(iVar1 + 0x18) == 0) && (param_1 != 0)) {
    iVar2 = operator_new(0x48);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00033818(iVar2,&CMenu::classCMenu,4,1);
    }
    *(undefined4 *)(iVar1 + 0x18) = uVar3;
  }
  return *(undefined4 *)(iVar1 + 0x18);
}


// 00033eec FUN_00033eec

void FUN_00033eec(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00033e90(1);
  FUN_00033890(uVar1,param_1);
  return;
}


// 00033f08 FUN_00033f08

void FUN_00033f08(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00033e90(0);
  if (iVar1 != 0) {
    FUN_0002e298(iVar1 + 4,param_1);
  }
  return;
}


// 00033f30 FUN_00033f30

int FUN_00033f30(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 4);
  if ((iVar2 != 0) && (iVar1 = FUN_00033e90(0), iVar1 != 0)) {
    FUN_0002e394(iVar1 + 4,*(undefined4 *)(param_1 + 4));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  return iVar2;
}


// 00033f6c FUN_00033f6c

void FUN_00033f6c(int param_1)

{
  HMENU hMenu;
  
  if (*(int *)(param_1 + 4) != 0) {
    hMenu = (HMENU)FUN_00033f30(param_1);
    DestroyMenu(hMenu);
  }
  return;
}


// 00033f94 FUN_00033f94

void FUN_00033f94(int param_1)

{
  DWORD DVar1;
  HBRUSH pHVar2;
  
  DVar1 = GetSysColor(0x4000000f);
  *(DWORD *)(param_1 + 0x28) = DVar1;
  DVar1 = GetSysColor(0x40000010);
  *(DWORD *)(param_1 + 0x2c) = DVar1;
  DVar1 = GetSysColor(0x40000014);
  *(DWORD *)(param_1 + 0x30) = DVar1;
  DVar1 = GetSysColor(0x40000012);
  *(DWORD *)(param_1 + 0x34) = DVar1;
  DVar1 = GetSysColor(0x40000006);
  *(DWORD *)(param_1 + 0x38) = DVar1;
  pHVar2 = GetSysColorBrush(0x4000000f);
  *(HBRUSH *)(param_1 + 0x24) = pHVar2;
  pHVar2 = GetSysColorBrush(0x40000006);
  *(HBRUSH *)(param_1 + 0x20) = pHVar2;
  return;
}


// 00034010 FUN_00034010

void FUN_00034010(int param_1)

{
  undefined4 uVar1;
  HDC hdc;
  int iVar2;
  
  uVar1 = FUN_0002b30c(0xb);
  *(undefined4 *)(param_1 + 8) = uVar1;
  uVar1 = FUN_0002b30c(0xc);
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  if (*(int *)(param_1 + 0x68) == 0) {
    FUN_0003f97c();
  }
  else {
    FUN_0003f938();
  }
  hdc = GetDC((HWND)0x0);
  iVar2 = GetDeviceCaps(hdc,0x58);
  *(int *)(param_1 + 0x18) = iVar2;
  iVar2 = GetDeviceCaps(hdc,0x5a);
  *(int *)(param_1 + 0x1c) = iVar2;
  ReleaseDC((HWND)0x0,hdc);
  return;
}


// 00034080 FUN_00034080

undefined4 FUN_00034080(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  
  if (param_2 == 0x110) {
    uVar1 = FUN_0003001c();
    piVar2 = (int *)FUN_0002ed40(&CDialog::classCDialog,uVar1);
    if (piVar2 == (int *)0x0) {
      uVar1 = 1;
    }
    else {
      uVar1 = (**(code **)(*piVar2 + 0xb4))();
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// 000340dc FUN_000340dc

undefined4 FUN_000340dc(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  HWND hWnd;
  BOOL BVar4;
  undefined4 uVar5;
  int extraout_r3;
  
  iVar1 = FUN_0003084c();
  if (iVar1 == 0) {
    iVar2 = FUN_00031b9c(param_1);
    iVar1 = extraout_r3;
    if (iVar2 != 0) {
      iVar1 = *(int *)(iVar2 + 100);
    }
    if (iVar2 != 0 && iVar1 != 0) {
      return 0;
    }
    if ((((param_2[1] != 0x100) ||
         (((param_2[2] != 0x1b && (param_2[2] != 3)) ||
          (uVar3 = GetWindowLongW((HWND)*param_2,-0x10), (uVar3 & 4) == 0)))) ||
        (iVar1 = FUN_00035dd8(*param_2,u_Edit_0004412c), iVar1 == 0)) ||
       ((hWnd = GetDlgItem(*(HWND *)(param_1 + 0x1c),2), hWnd != (HWND)0x0 &&
        (BVar4 = IsWindowEnabled(hWnd), BVar4 == 0)))) {
      uVar5 = FUN_00033020(param_1,param_2);
      return uVar5;
    }
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x111,2,0);
  }
  return 1;
}


// 000341b0 FUN_000341b0

undefined4 FUN_000341b0(int param_1,uint param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0002f3c4();
  if (iVar1 == 0) {
    if ((((param_3 == 0) || (param_3 == -1)) && ((param_2 & 0x8000) != 0)) && (param_2 < 0xf000)) {
      GetParent(*(HWND *)(param_1 + 0x1c));
      piVar2 = (int *)FUN_0002ffec();
      if ((piVar2 != (int *)0x0) &&
         (iVar1 = (**(code **)(*piVar2 + 0xc))(piVar2,param_2,param_3,param_4,param_5), iVar1 != 0))
      goto LAB_00034240;
      piVar2 = (int *)FUN_0002f1d0();
      if ((piVar2 != (int *)0x0) &&
         (iVar1 = (**(code **)(*piVar2 + 0xc))(piVar2,param_2,param_3,param_4,param_5), iVar1 != 0))
      {
        return 1;
      }
    }
    uVar3 = 0;
  }
  else {
LAB_00034240:
    uVar3 = 1;
  }
  return uVar3;
}


// 0003428c FUN_0003428c

void * FUN_0003428c(void *param_1,uint param_2)

{
  FUN_000342b0();
  if ((param_2 & 1) != 0) {
    free(param_1);
  }
  return param_1;
}


// 000342b0 FUN_000342b0

void FUN_000342b0(undefined1 *param_1)

{
  *param_1 = 0x40;
  param_1[1] = 0x10;
  param_1[2] = 4;
  param_1[3] = 0;
  if (*(int *)(param_1 + 0x1c) != 0) {
    FUN_00030748(param_1);
  }
  FUN_00030500(param_1);
  return;
}


// 000342f8 FUN_000342f8

void FUN_000342f8(undefined4 param_1,LPCWSTR param_2,undefined4 param_3)

{
  int iVar1;
  HRSRC hResInfo;
  HGLOBAL pvVar2;
  HMODULE hModule;
  HGLOBAL pvVar3;
  
  iVar1 = FUN_0003f4f4();
  hModule = *(HMODULE *)(iVar1 + 0xc);
  hResInfo = FindResourceW(hModule,param_2,(LPCWSTR)0x5);
  pvVar2 = LoadResource(hModule,hResInfo);
  pvVar3 = (HGLOBAL)0x0;
  if (pvVar2 != (HGLOBAL)0x0) {
    pvVar3 = pvVar2;
  }
  FUN_00034350(param_1,pvVar3,param_3,hModule);
  return;
}


// 00034350 FUN_00034350

undefined4 FUN_00034350(int *param_1,LPCDLGTEMPLATEW param_2,int param_3,HINSTANCE param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  LPCDLGTEMPLATEW hMem;
  HWND pHVar4;
  uint uVar5;
  bool bVar6;
  short local_c0 [2];
  CString local_bc;
  LPCDLGTEMPLATEW local_b8;
  HWND local_b4;
  int *local_b0;
  SIZE_T local_ac;
  undefined1 auStack_a8 [16];
  undefined1 auStack_98 [16];
  _MEMORY_BASIC_INFORMATION _Stack_88;
  undefined1 auStack_68 [56];
  HINSTANCE local_4;
  
  local_4 = param_4;
  if (param_4 == (HINSTANCE)0x0) {
    iVar2 = FUN_0003f4f4();
    local_4 = *(HINSTANCE *)(iVar2 + 8);
  }
  iVar2 = FUN_0003f4f4();
  local_b0 = *(int **)(iVar2 + 0x2038);
  local_b8 = (LPCDLGTEMPLATEW)0x0;
  local_b4 = (HWND)0x0;
  FUN_0002f060(auStack_68);
  iVar2 = setjmp(auStack_68);
  piVar1 = local_b0;
  if (iVar2 == 0) {
    FUN_00033358(0x10);
    FUN_00033358(0x3c000);
    if (piVar1 == (int *)0x0) {
LAB_0003441c:
      if (param_2 != (LPCDLGTEMPLATEW)0x0) {
        local_c0[0] = 0;
        local_bc.str = g_afxEmptyString;
        iVar2 = FUN_00035248(param_2,&local_bc,local_c0);
        bVar6 = iVar2 == 0;
        if (bVar6) {
LAB_000344f8:
          FUN_00034ff0(auStack_a8,param_2);
          FUN_00035458(auStack_a8,local_c0[0]);
          hMem = (LPCDLGTEMPLATEW)FUN_000350a8(auStack_a8);
          local_b8 = hMem;
          FUN_00035094(auStack_a8);
        }
        else {
          iVar2 = GetSystemMetrics(0x2a);
          if (iVar2 == 0) {
LAB_000344f0:
            hMem = local_b8;
            if (bVar6) goto LAB_000344f8;
          }
          else {
            iVar2 = wcscmp(local_bc.str,u_MS_Shell_Dlg_00044160);
            if ((iVar2 == 0) || (iVar2 = wcscmp(local_bc.str,u_MS_Sans_Serif_00044144), iVar2 == 0))
            {
LAB_000344d8:
              bVar6 = true;
            }
            else {
              iVar2 = wcscmp(local_bc.str,u_Helv_00044138);
              bVar6 = false;
              if (iVar2 == 0) goto LAB_000344d8;
            }
            hMem = local_b8;
            if (bVar6) {
              bVar6 = true;
              if (local_c0[0] == 8) {
                local_c0[0] = 0;
              }
              goto LAB_000344f0;
            }
          }
        }
        param_1[0xc] = -1;
        if (hMem != (LPCDLGTEMPLATEW)0x0) {
          param_2 = hMem;
        }
        param_1[10] = param_1[10] | 0x10;
        FUN_0003020c(param_1);
        if ((param_2->style & 0x80) != 0) {
          memset(&_Stack_88,0,0x1c);
          local_ac = VirtualQuery(param_2,&_Stack_88,0x1c);
          if (local_ac == 0x1c) {
            if (_Stack_88.Protect != 4) {
              if (_Stack_88.Protect != 2) goto LAB_000345ec;
              VirtualProtect(param_2,0x12,4,&local_ac);
            }
            uVar5 = param_2->style & 0xffffff7f;
            *(short *)&param_2->style = (short)uVar5;
            *(short *)((int)&param_2->style + 2) = (short)(uVar5 >> 0x10);
          }
        }
LAB_000345ec:
        pHVar4 = (HWND)0x0;
        if (param_3 != 0) {
          pHVar4 = *(HWND *)(param_3 + 0x1c);
        }
        pHVar4 = CreateDialogIndirectParamW(local_4,param_2,pHVar4,FUN_0002b44c,0);
        local_b4 = pHVar4;
        CString_Dtor(&local_bc);
        goto LAB_0003463c;
      }
    }
    else {
      iVar2 = (**(code **)(*param_1 + 0xac))(param_1,auStack_98);
      if (iVar2 != 0) {
        param_2 = (LPCDLGTEMPLATEW)(**(code **)(*piVar1 + 0x10))(piVar1,auStack_98,param_2);
        goto LAB_0003441c;
      }
    }
    FUN_0002f0c0();
    uVar3 = 0;
  }
  else {
    param_1[0xc] = -1;
    pHVar4 = local_b4;
    hMem = local_b8;
LAB_0003463c:
    FUN_0002f0c0();
    if ((piVar1 != (int *)0x0) &&
       ((**(code **)(*piVar1 + 0x14))(piVar1,auStack_98), pHVar4 != (HWND)0x0)) {
      (**(code **)(*param_1 + 0xac))(param_1,0);
    }
    iVar2 = FUN_00030238();
    if (iVar2 == 0) {
      (**(code **)(*param_1 + 0x9c))();
    }
    if ((pHVar4 != (HWND)0x0) && ((param_1[10] & 0x10U) == 0)) {
      DestroyWindow(pHVar4);
      pHVar4 = (HWND)0x0;
      local_b4 = (HWND)0x0;
    }
    if (hMem != (LPCDLGTEMPLATEW)0x0) {
      LocalFree(hMem);
    }
    uVar3 = 0;
    if (pHVar4 != (HWND)0x0) {
      uVar3 = 1;
    }
  }
  return uVar3;
}


// 000346e8 FUN_000346e8

undefined1 * FUN_000346e8(undefined1 *param_1,uint param_2,undefined4 param_3)

{
  FUN_0002fa00();
  *param_1 = 0x40;
  param_1[1] = 0x10;
  param_1[2] = 4;
  param_1[3] = 0;
  memset(param_1 + 0x44,0,0x34);
  *(undefined4 *)(param_1 + 0x6c) = param_3;
  *(uint *)(param_1 + 0x5c) = param_2 & 0xffff;
  *(uint *)(param_1 + 0x58) = param_2;
  *(undefined4 *)(param_1 + 0x44) = 1;
  memset(param_1 + 0x4c,0,0xc);
  *(undefined4 *)(param_1 + 0x4c) = 0xc;
  return param_1;
}


// 0003476c FUN_0003476c

undefined4 FUN_0003476c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0003f4f4();
  if (*(int *)(iVar1 + 4) != 0) {
    FUN_00037a38(*(int *)(iVar1 + 4),0);
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x6c) + 0x1c);
  }
  uVar2 = FUN_00037c00(uVar2,param_1 + 0x70);
  FUN_0003020c(param_1);
  return uVar2;
}


// 000347b4 FUN_000347b4

void FUN_000347b4(int param_1)

{
  BOOL BVar1;
  int iVar2;
  
  FUN_00030238();
  FUN_00030090(param_1);
  BVar1 = IsWindow(*(HWND *)(param_1 + 0x70));
  if (BVar1 != 0) {
    EnableWindow(*(HWND *)(param_1 + 0x70),1);
  }
  *(undefined4 *)(param_1 + 0x70) = 0;
  iVar2 = FUN_0003f4f4();
  if (*(int *)(iVar2 + 4) != 0) {
    FUN_00037a38(*(int *)(iVar2 + 4),1);
  }
  return;
}


// 00034a14 FUN_00034a14

void FUN_00034a14(int *param_1,undefined4 param_2)

{
  if ((param_1[10] & 0x18U) != 0) {
    (**(code **)(*param_1 + 0x6c))();
  }
                    /* WARNING: Could not recover jumptable at 0x0002cf70. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  EndDialog(param_1[7],param_2);
  return;
}


// 00034a48 FUN_00034a48

void FUN_00034a48(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0003648c(param_2);
  (**(code **)(*param_1 + 0xb8))(param_1,uVar1);
  FUN_0002ff50(param_1);
  return;
}


// 00034a80 FUN_00034a80

int FUN_00034a80(int *param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 auStack_38 [16];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  (**(code **)(*param_1 + 0xc4))();
  iVar2 = FUN_0003f4f4();
  piVar3 = *(int **)(iVar2 + 0x2038);
  if ((piVar3 != (int *)0x0) && (param_1[0x1d] != 0)) {
    if (param_1[0x1a] == 0) {
      iVar2 = (**(code **)(*piVar3 + 0x20))(piVar3,param_1,param_1[0x17]);
    }
    else {
      iVar2 = (**(code **)(*piVar3 + 0x1c))();
    }
    if (iVar2 == 0) {
      FUN_00034a14(param_1,0xffffffff);
      return 0;
    }
  }
  if ((param_1[10] & 0x10U) != 0) {
    iVar2 = operator_new(0xdc);
    if (iVar2 == 0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)FUN_00037fb8();
    }
    param_1[0x12] = (int)piVar3;
    if (piVar3 != (int *)0x0) {
      iVar7 = *piVar3;
      local_28 = 0xe800;
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_18 = 0;
      iVar2 = 0x10;
      puVar5 = auStack_38;
      puVar6 = &local_24;
      do {
        iVar4 = iVar2 + -1;
        *puVar5 = *(undefined1 *)puVar6;
        bVar1 = 0 < iVar2;
        iVar2 = iVar4;
        puVar5 = puVar5 + 1;
        puVar6 = (undefined4 *)((int)puVar6 + 1);
      } while (iVar4 != 0 && bVar1);
      (**(code **)(iVar7 + 0xd8))(piVar3,param_1,0x800,0x50002000);
    }
  }
  iVar2 = FUN_0002ff50(param_1);
  if ((iVar2 != 0) && ((param_1[10] & 0x100U) != 0)) {
    GetNextDlgTabItem((HWND)param_1[7],(HWND)0x0,0);
    iVar7 = FUN_0002ffec();
    if (iVar7 != 0) {
      FUN_00033e00();
      iVar2 = 0;
    }
  }
  return iVar2;
}


// 00034bec FUN_00034bec

void FUN_00034bec(void)

{
  int iVar1;
  int *piVar2;
  undefined1 auStack_10 [8];
  
  iVar1 = FUN_0003f4f4();
  if ((*(int *)(iVar1 + 4) != 0) &&
     ((piVar2 = (int *)FUN_0002acc0(iVar1), piVar2 == (int *)0x0 ||
      (iVar1 = (**(code **)(*piVar2 + 0xc))(piVar2,0xe146,0,0,auStack_10), iVar1 == 0)))) {
    iVar1 = FUN_0003f4f4(0);
    (**(code **)(**(int **)(iVar1 + 4) + 0xc))(*(int **)(iVar1 + 4),0xe146,0,0,auStack_10);
  }
  return;
}


// 00034c84 FUN_00034c84

undefined4 FUN_00034c84(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_18;
  HWND local_14;
  undefined4 local_10;
  
  if (*(int *)(param_1 + 0x68) == 0) {
    iVar1 = FUN_00032d14(param_1,*(undefined4 *)(param_1 + 0x5c));
  }
  else {
    iVar1 = FUN_00032d70();
  }
  if ((iVar1 == 0) || (iVar1 = FUN_00032a4c(param_1,0), iVar1 == 0)) {
    FUN_00034a14(param_1,0xffffffff);
    uVar2 = 0;
  }
  else {
    iVar1 = FUN_00033a44(param_1,0xe146);
    if (iVar1 != 0) {
      iVar3 = FUN_00034bec();
      uVar2 = 5;
      if (iVar3 == 0) {
        uVar2 = 0;
      }
      FUN_00033d64(iVar1,uVar2);
    }
    if (*(int *)(param_1 + 0x44) != 0) {
      memset(&local_18,0,0xc);
      local_14 = *(HWND *)(param_1 + 0x1c);
      local_18 = 1;
      local_10 = 0xd;
      SetForegroundWindow(local_14);
      iVar1 = SHInitDialog(&local_18);
      if (iVar1 == 0) {
        GetLastError();
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


// 00034d5c FUN_00034d5c

void FUN_00034d5c(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00032a4c(param_1,1);
  if (iVar1 != 0) {
    FUN_00034a14(param_1,1);
  }
  return;
}


// 00034d88 FUN_00034d88

void FUN_00034d88(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  uVar1 = FUN_00033b14();
  if ((uVar1 & 0x40000000) == 0) {
    iVar2 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
    SHHandleWMSettingChange
              (*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(iVar2 + 0x44),
               *(undefined4 *)(iVar2 + 0x48),param_1 + 0x4c);
  }
  DAT_002dc968 = 0;
  iVar2 = FUN_0002acc0(param_1,0,0);
  if (iVar2 == param_1) {
    FUN_00034010(&afxData);
  }
  uVar1 = FUN_00033b14(param_1);
  if ((uVar1 & 0x40000000) == 0) {
    iVar2 = FUN_0002feb8();
    FUN_00031cf4(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(iVar2 + 4),
                 *(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc),1,1,unaff_r4,unaff_lr);
  }
  FUN_0002ff50(param_1);
  return;
}


// 00034de0 FUN_00034de0

void FUN_00034de0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_00033b14();
  if ((uVar1 & 0x40000000) == 0) {
    iVar2 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
    SHHandleWMActivate(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(iVar2 + 0x44),
                       *(undefined4 *)(iVar2 + 0x48),param_1 + 0x4c,0);
  }
  FUN_0002ff50(param_1);
  return;
}


// 00034e38 FUN_00034e38

undefined4 FUN_00034e38(int param_1)

{
  short sVar1;
  short sVar2;
  uint *puVar3;
  int iVar4;
  HRSRC hResInfo;
  undefined4 uVar5;
  uint uVar6;
  uint *puVar7;
  HMODULE hModule;
  
  puVar7 = *(uint **)(param_1 + 100);
  puVar3 = *(uint **)(param_1 + 0x60);
  if (*(int *)(param_1 + 0x5c) != 0) {
    iVar4 = FUN_0003f4f4();
    hModule = *(HMODULE *)(iVar4 + 0xc);
    hResInfo = FindResourceW(hModule,*(LPCWSTR *)(param_1 + 0x5c),(LPCWSTR)0x5);
    puVar3 = LoadResource(hModule,hResInfo);
  }
  if (puVar3 != (uint *)0x0) {
    puVar7 = puVar3;
  }
  uVar5 = 1;
  if (puVar7 != (uint *)0x0) {
    uVar6 = *puVar7;
    if (*(short *)((int)puVar7 + 2) == -1) {
      uVar6 = puVar7[3];
      sVar1 = *(short *)((int)puVar7 + 0x12);
      sVar2 = (short)puVar7[5];
    }
    else {
      sVar1 = *(short *)((int)puVar7 + 10);
      sVar2 = (short)puVar7[3];
    }
    if ((((uVar6 & 0x1801) != 0) || (sVar1 != 0)) || (uVar5 = 1, sVar2 != 0)) {
      uVar5 = 0;
    }
  }
  return uVar5;
}


// 00034f30 thunk_FUN_00032920

undefined4 thunk_FUN_00032920(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uStack_1c;
  
  iVar1 = FUN_00032444(param_3,&uStack_1c);
  if (iVar1 == 0) {
    iVar1 = FUN_0003f014(&DAT_002de290,&LAB_0003f644);
    uVar3 = 0;
    if (param_3 != 0) {
      uVar3 = *(undefined4 *)(param_3 + 0x1c);
    }
    iVar2 = FUN_000329ac(*(undefined4 *)(param_2 + 4),uVar3,param_4,*(undefined4 *)(iVar1 + 4),
                         *(undefined4 *)(iVar1 + 8));
    if (iVar2 == 0) {
      uStack_1c = FUN_0002ff50(param_1);
    }
    else {
      uStack_1c = *(undefined4 *)(iVar1 + 4);
    }
  }
  return uStack_1c;
}


// 00034f34 FUN_00034f34

undefined4 FUN_00034f34(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  if ((param_3 == 0) &&
     ((*(int *)(param_1 + 0x58) == 0 || (param_3 = *(int *)(param_1 + 0x58) + 0x20000, param_3 == 0)
      ))) {
    uVar3 = 0;
  }
  else {
    iVar1 = FUN_0003f4f4();
    piVar2 = *(int **)(iVar1 + 4);
    if (piVar2 != (int *)0x0) {
      (**(code **)(*piVar2 + 0x90))(piVar2,param_3,0);
    }
    uVar3 = 1;
  }
  return uVar3;
}


// 00034fa0 FUN_00034fa0

ushort FUN_00034fa0(ushort *param_1)

{
  ushort uVar1;
  
  if (param_1[1] == 0xffff) {
    uVar1 = (ushort)(byte)param_1[6];
  }
  else {
    uVar1 = *param_1;
  }
  return uVar1 & 0x40;
}


// 00034ff0 FUN_00034ff0

undefined4 * FUN_00034ff0(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
  }
  else {
    uVar1 = FUN_00035138(param_2);
    FUN_00035034(param_1,param_2,uVar1);
  }
  return param_1;
}


// 00035034 FUN_00035034

bool FUN_00035034(undefined4 *param_1,void *param_2,int param_3)

{
  void *_Dst;
  int iVar1;
  
  param_1[1] = param_3;
  _Dst = (void *)FUN_0002ac34(0x40,param_3 + 0x40);
  *param_1 = _Dst;
  if (_Dst != (void *)0x0) {
    memmove(_Dst,param_2,param_1[1]);
    iVar1 = FUN_00034fa0(_Dst);
    param_1[2] = (uint)(iVar1 == 0);
  }
  return _Dst != (void *)0x0;
}


// 00035094 FUN_00035094

void FUN_00035094(undefined4 *param_1)

{
  if ((HLOCAL)*param_1 != (HLOCAL)0x0) {
    LocalFree((HLOCAL)*param_1);
  }
  return;
}


// 000350a8 FUN_000350a8

undefined4 FUN_000350a8(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = *param_1;
  *param_1 = 0;
  return uVar1;
}


// 000350bc FUN_000350bc

void FUN_000350bc(int param_1)

{
  short sVar1;
  short *psVar2;
  
  if (*(short *)(param_1 + 2) == -1) {
    psVar2 = (short *)(param_1 + 0x1a);
  }
  else {
    psVar2 = (short *)(param_1 + 0x12);
  }
  if (*psVar2 == -1) {
    psVar2 = psVar2 + 2;
  }
  else {
    do {
      sVar1 = *psVar2;
      psVar2 = psVar2 + 1;
    } while (sVar1 != 0);
  }
  if (*psVar2 == -1) {
    psVar2 = psVar2 + 2;
  }
  else {
    do {
      sVar1 = *psVar2;
      psVar2 = psVar2 + 1;
    } while (sVar1 != 0);
  }
  do {
    sVar1 = *psVar2;
    psVar2 = psVar2 + 1;
  } while (sVar1 != 0);
  return;
}


// 00035138 FUN_00035138

int FUN_00035138(int param_1)

{
  ushort uVar1;
  short sVar2;
  wchar_t *pwVar3;
  int iVar4;
  size_t sVar5;
  ushort *puVar6;
  bool bVar7;
  
  bVar7 = *(short *)(param_1 + 2) == -1;
  pwVar3 = (wchar_t *)FUN_000350bc(param_1);
  iVar4 = FUN_00034fa0(param_1);
  if (iVar4 != 0) {
    iVar4 = 3;
    if (!bVar7) {
      iVar4 = 1;
    }
    sVar5 = wcslen(pwVar3 + iVar4);
    pwVar3 = pwVar3 + iVar4 + sVar5 + 1;
  }
  if (bVar7) {
    sVar2 = *(short *)(param_1 + 0x10);
  }
  else {
    sVar2 = *(short *)(param_1 + 8);
  }
  for (; sVar2 != 0; sVar2 = sVar2 + -1) {
    iVar4 = 0x18;
    if (!bVar7) {
      iVar4 = 0x12;
    }
    puVar6 = (ushort *)(iVar4 + ((int)pwVar3 + 3U & 0xfffffffc));
    if (*puVar6 == 0xffff) {
      puVar6 = puVar6 + 2;
    }
    else {
      do {
        uVar1 = *puVar6;
        puVar6 = puVar6 + 1;
      } while (uVar1 != 0);
    }
    if (*puVar6 == 0xffff) {
      puVar6 = puVar6 + 2;
    }
    else {
      do {
        uVar1 = *puVar6;
        puVar6 = puVar6 + 1;
      } while (uVar1 != 0);
    }
    pwVar3 = (wchar_t *)((int)puVar6 + *puVar6 + 2);
  }
  return (int)pwVar3 - param_1;
}


// 00035248 FUN_00035248

undefined4 FUN_00035248(int param_1,CString *param_2,undefined2 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 *puVar3;
  
  iVar1 = FUN_00034fa0();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    puVar3 = (undefined2 *)FUN_000350bc(param_1);
    iVar1 = 3;
    *param_3 = *puVar3;
    if (*(short *)(param_1 + 2) != -1) {
      iVar1 = 1;
    }
    CString_AssignW(param_2,puVar3 + iVar1);
    uVar2 = 1;
  }
  return uVar2;
}


// 000352b4 FUN_000352b4

undefined4 FUN_000352b4(undefined4 *param_1,wchar_t *param_2,undefined2 param_3)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  size_t sVar5;
  undefined2 *puVar6;
  ushort *puVar7;
  void *_Src;
  void *_Dst;
  int iVar8;
  bool bVar9;
  
  if (param_1[1] == 0) {
    uVar2 = 0;
  }
  else {
    puVar7 = (ushort *)*param_1;
    bVar9 = puVar7[1] != 0xffff;
    iVar3 = FUN_00034fa0(puVar7);
    iVar4 = 3;
    if (bVar9) {
      iVar4 = 1;
    }
    if (bVar9) {
      uVar2 = *(undefined4 *)puVar7;
      *puVar7 = (ushort)uVar2 | 0x40;
      puVar7[1] = (ushort)((uint)uVar2 >> 0x10);
    }
    else {
      uVar2 = *(undefined4 *)(puVar7 + 6);
      *(byte *)(puVar7 + 6) = (byte)uVar2 | 0x40;
      *(char *)((int)puVar7 + 0xd) = (char)((uint)uVar2 >> 8);
      *(char *)(puVar7 + 7) = (char)((uint)uVar2 >> 0x10);
      *(char *)((int)puVar7 + 0xf) = (char)((uint)uVar2 >> 0x18);
    }
    sVar5 = wcslen(param_2);
    iVar8 = iVar4 * 2 + (sVar5 + 1) * 2;
    puVar6 = (undefined2 *)FUN_000350bc(puVar7);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      sVar5 = wcslen(puVar6 + iVar4);
      iVar3 = iVar4 * 2 + (sVar5 + 1) * 2;
    }
    _Src = (void *)((int)puVar6 + iVar3 + 3 & 0xfffffffc);
    _Dst = (void *)((int)puVar6 + iVar8 + 3 & 0xfffffffc);
    if (bVar9) {
      uVar1 = puVar7[4];
    }
    else {
      uVar1 = puVar7[8];
    }
    if ((iVar8 != iVar3) && (uVar1 != 0)) {
      memmove(_Dst,_Src,(int)puVar7 + (param_1[1] - (int)_Src));
    }
    *puVar6 = param_3;
    memmove(puVar6 + iVar4,param_2,iVar8 + iVar4 * -2);
    uVar2 = 1;
    param_1[1] = (int)_Dst + (param_1[1] - (int)_Src);
    param_1[2] = 0;
  }
  return uVar2;
}


// 00035458 FUN_00035458

void FUN_00035458(undefined4 param_1,uint param_2)

{
  HANDLE h;
  int iVar1;
  HDC hdc;
  uint uVar2;
  wchar_t *pwVar3;
  uint local_78 [7];
  wchar_t awStack_5c [32];
  
  pwVar3 = u_System_0004418c;
  uVar2 = 10;
  h = GetStockObject(0xd);
  if (((h != (HGDIOBJ)0x0) || (h = GetStockObject(0xd), h != (HGDIOBJ)0x0)) &&
     (iVar1 = GetObjectW(h,0x5c,local_78), iVar1 != 0)) {
    pwVar3 = awStack_5c;
    hdc = GetDC((HWND)0x0);
    if ((int)local_78[0] < 0) {
      local_78[0] = -local_78[0];
    }
    iVar1 = GetDeviceCaps(hdc,0x5a);
    uVar2 = __rt_sdiv64by64(local_78[0] * 0x48,
                            ((int)local_78[0] >> 0x1f) * 0x48 +
                            (int)((ulonglong)local_78[0] * 0x48 >> 0x20),iVar1,iVar1 >> 0x1f);
    uVar2 = uVar2 & 0xffff;
    ReleaseDC((HWND)0x0,hdc);
  }
  if ((param_2 & 0xffff) == 0) {
    param_2 = uVar2;
  }
  FUN_000352b4(param_1,pwVar3,param_2);
  return;
}


// 00035544 FUN_00035544

undefined4 * FUN_00035544(CArchive *param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  ushort local_54;
  ushort local_52 [3];
  char acStack_4c [64];
  
  FUN_0002aaf8(param_1,local_52);
  *param_2 = (uint)local_52[0];
  FUN_0002aaf8(param_1,&local_54);
  if (local_54 < 0x40) {
    uVar1 = CArchive_Read(param_1,acStack_4c,(uint)local_54);
    if (uVar1 == local_54) {
      acStack_4c[local_54] = '\0';
      iVar2 = FUN_0003f4f4();
      FUN_0003ea90(0);
      for (puVar3 = *(undefined4 **)(iVar2 + 0x1c); puVar3 != (undefined4 *)0x0;
          puVar3 = (undefined4 *)puVar3[5]) {
        iVar2 = strcmp(acStack_4c,(char *)*puVar3);
        if (iVar2 == 0) goto LAB_000355e0;
      }
      puVar3 = (undefined4 *)0x0;
LAB_000355e0:
      FUN_0003eb2c(0);
      return puVar3;
    }
  }
  return (undefined4 *)0x0;
}


// 000355fc FUN_000355fc

void FUN_000355fc(undefined4 *param_1,CArchive *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  
  sVar1 = strlen((char *)*param_1);
  uVar2 = FUN_0002aa60(param_2,*(undefined2 *)(param_1 + 2));
  FUN_0002aa60(uVar2,sVar1 & 0xffff);
  CArchive_Write(param_2,(void *)*param_1,sVar1 & 0xffff);
  return;
}


// 00035644 CArchive_Read

int CArchive_Read(CArchive *this,void *param_2,uint param_3)

{
  size_t _Size;
  int iVar1;
  int iVar2;
  int extraout_r1;
  byte *_Src;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  void *_Dst;
  
  if (param_3 == 0) {
    iVar1 = 0;
  }
  else {
    uVar3 = (int)this->max - (int)this->cur;
    _Size = param_3;
    if (uVar3 <= param_3) {
      _Size = uVar3;
    }
    memmove(param_2,this->cur,_Size);
    _Dst = (void *)(_Size + (int)param_2);
    this->cur = this->cur + _Size;
    uVar3 = param_3 - _Size;
    if (uVar3 != 0) {
      __rt_udiv(*(undefined4 *)&this->field_0x1c,uVar3);
      iVar6 = uVar3 - extraout_r1;
      iVar5 = 0;
      iVar1 = iVar6;
      do {
        iVar2 = (**(code **)(**(int **)&this->field_0x20 + 0x30))
                          (*(int **)&this->field_0x20,_Dst,iVar1);
        _Dst = (void *)(iVar2 + (int)_Dst);
        iVar5 = iVar2 + iVar5;
        iVar1 = iVar1 - iVar2;
        if (iVar2 == 0) break;
      } while (iVar1 != 0);
      uVar3 = uVar3 - iVar5;
      if (iVar5 == iVar6) {
        if (*(int *)&this->field_0x8 == 0) {
          uVar4 = 0;
          iVar1 = *(int *)&this->field_0x2c;
          uVar7 = *(uint *)&this->field_0x1c;
          if (*(uint *)&this->field_0x1c < uVar3) {
            uVar7 = uVar3;
          }
          do {
            iVar5 = (**(code **)(**(int **)&this->field_0x20 + 0x30))
                              (*(int **)&this->field_0x20,iVar1,uVar7);
            iVar1 = iVar5 + iVar1;
            uVar4 = iVar5 + uVar4;
            uVar7 = uVar7 - iVar5;
            if ((iVar5 == 0) || (uVar7 == 0)) break;
          } while (uVar4 < uVar3);
          _Src = *(byte **)&this->field_0x2c;
          this->max = _Src + uVar4;
        }
        else {
          (**(code **)(**(int **)&this->field_0x20 + 0x44))
                    (*(int **)&this->field_0x20,0,*(undefined4 *)&this->field_0x1c,&this->field_0x2c
                     ,&this->max);
          _Src = *(byte **)&this->field_0x2c;
        }
        this->cur = _Src;
        uVar7 = (int)this->max - (int)_Src;
        if (uVar3 < uVar7) {
          uVar7 = uVar3;
        }
        memmove(_Dst,_Src,uVar7);
        uVar3 = uVar3 - uVar7;
        this->cur = this->cur + uVar7;
      }
    }
    iVar1 = param_3 - uVar3;
  }
  return iVar1;
}


// 000357e4 CArchive_Write

void CArchive_Write(CArchive *this,void *param_2,uint param_3)

{
  size_t _Size;
  int extraout_r1;
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_3 != 0) {
    uVar1 = (int)this->max - (int)this->cur;
    _Size = param_3;
    if (uVar1 <= param_3) {
      _Size = uVar1;
    }
    memmove(this->cur,param_2,_Size);
    iVar2 = param_3 - _Size;
    this->cur = this->cur + _Size;
    if (iVar2 != 0) {
      FUN_000358ec(this);
      __rt_udiv(*(undefined4 *)&this->field_0x1c,iVar2);
      iVar3 = iVar2 - extraout_r1;
      (**(code **)(**(int **)&this->field_0x20 + 0x34))
                (*(int **)&this->field_0x20,_Size + (int)param_2,iVar3);
      if (*(int *)&this->field_0x8 != 0) {
        (**(code **)(**(int **)&this->field_0x20 + 0x44))
                  (*(int **)&this->field_0x20,1,*(undefined4 *)&this->field_0x1c,&this->field_0x2c,
                   &this->max);
        this->cur = *(byte **)&this->field_0x2c;
      }
      memmove(this->cur,(void *)(iVar3 + _Size + (int)param_2),iVar2 - iVar3);
      this->cur = this->cur + (iVar2 - iVar3);
    }
  }
  return;
}


// 000358ec FUN_000358ec

void FUN_000358ec(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((*(uint *)(param_1 + 0x14) & 1) == 0) {
    if (*(int *)(param_1 + 8) == 0) {
      iVar1 = *(int *)(param_1 + 0x2c);
      if (*(int *)(param_1 + 0x24) != iVar1) {
        (**(code **)(**(int **)(param_1 + 0x20) + 0x34))
                  (*(int **)(param_1 + 0x20),iVar1,*(int *)(param_1 + 0x24) - iVar1);
      }
    }
    else {
      if (*(int *)(param_1 + 0x24) != *(int *)(param_1 + 0x2c)) {
        (**(code **)(**(int **)(param_1 + 0x20) + 0x44))
                  (*(int **)(param_1 + 0x20),2,*(int *)(param_1 + 0x24) - *(int *)(param_1 + 0x2c),0
                   ,0);
      }
      (**(code **)(**(int **)(param_1 + 0x20) + 0x44))
                (*(int **)(param_1 + 0x20),1,*(undefined4 *)(param_1 + 0x1c),param_1 + 0x2c,
                 param_1 + 0x28);
    }
    uVar2 = *(undefined4 *)(param_1 + 0x2c);
  }
  else {
    if (*(int *)(param_1 + 0x28) != *(int *)(param_1 + 0x24)) {
      (**(code **)(**(int **)(param_1 + 0x20) + 0x24))
                (*(int **)(param_1 + 0x20),*(int *)(param_1 + 0x24) - *(int *)(param_1 + 0x28),1);
    }
    uVar2 = *(undefined4 *)(param_1 + 0x28);
  }
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  return;
}


// 000359e4 FUN_000359e4

void FUN_000359e4(int param_1,uint param_2)

{
  void *_Dst;
  int iVar1;
  void *_Src;
  size_t _Size;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  _Src = *(void **)(param_1 + 0x24);
  _Size = *(int *)(param_1 + 0x28) - (int)_Src;
  uVar4 = _Size + param_2;
  if (*(int *)(param_1 + 8) == 0) {
    _Dst = *(void **)(param_1 + 0x2c);
    if (_Dst < _Src) {
      if (0 < (int)_Size) {
        memmove(_Dst,_Src,_Size);
        _Dst = *(void **)(param_1 + 0x2c);
        *(void **)(param_1 + 0x24) = _Dst;
        *(size_t *)(param_1 + 0x28) = (int)_Dst + _Size;
      }
      iVar3 = (int)_Dst + _Size;
      iVar2 = *(int *)(param_1 + 0x1c) - _Size;
      do {
        iVar1 = (**(code **)(**(int **)(param_1 + 0x20) + 0x30))
                          (*(int **)(param_1 + 0x20),iVar3,iVar2);
        iVar3 = iVar1 + iVar3;
        _Size = iVar1 + _Size;
        iVar2 = iVar2 - iVar1;
        if ((iVar1 == 0) || (iVar2 == 0)) break;
      } while (_Size < param_2);
      *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x2c);
      *(size_t *)(param_1 + 0x28) = *(int *)(param_1 + 0x2c) + _Size;
    }
  }
  else {
    if (_Size != 0) {
      (**(code **)(**(int **)(param_1 + 0x20) + 0x24))(*(int **)(param_1 + 0x20),-_Size,1);
    }
    (**(code **)(**(int **)(param_1 + 0x20) + 0x44))
              (*(int **)(param_1 + 0x20),0,*(undefined4 *)(param_1 + 0x1c),param_1 + 0x2c,
               (int *)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x2c);
  }
  if ((uint)(*(int *)(param_1 + 0x28) - *(int *)(param_1 + 0x24)) < uVar4) {
    FUN_00035c3c(3,0);
  }
  return;
}


// 00035b10 CArchive_WriteCount

void CArchive_WriteCount(CArchive *this,uint param_2)

{
  if (param_2 < 0xffff) {
    FUN_0002aa60(this,param_2 & 0xffff);
  }
  else {
    FUN_0002aa60(this,0xffff);
    FUN_0002aaa4(this,param_2);
  }
  return;
}


// 00035b58 CArchive_ReadCount

uint CArchive_ReadCount(CArchive *this)

{
  uint uVar1;
  ushort local_10 [2];
  uint local_c;
  
  FUN_0002aaf8(this,local_10);
  uVar1 = (uint)local_10[0];
  if (local_10[0] == 0xffff) {
    FUN_0002ab4c(this,&local_c);
    uVar1 = local_c;
  }
  return uVar1;
}


// 00035b98 FUN_00035b98

undefined4 FUN_00035b98(int param_1,wchar_t *param_2,size_t param_3,int *param_4)

{
  CString local_1c;
  CString local_18;
  
  if (param_4 != (int *)0x0) {
    *param_4 = *(int *)(param_1 + 8) + 0xf1b0;
  }
  local_18.str = g_afxEmptyString;
  CString_CopyCtor(&local_1c,(CString *)(param_1 + 0xc));
  if (*(int *)(local_1c.str + -4) == 0) {
    FUN_0002ee30(&local_1c,0xf006);
  }
  FUN_00037e94(&local_18,*(int *)(param_1 + 8) + 0xf1b0,local_1c.str);
  wcsncpy(param_2,local_18.str,param_3);
  CString_Dtor(&local_1c);
  CString_Dtor(&local_18);
  return 1;
}


// 00035c3c FUN_00035c3c

void FUN_00035c3c(undefined4 param_1,wchar_t *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)operator_new(0x10);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    FUN_0002efa4(puVar1);
    ((CString *)(puVar1 + 0xc))->str = g_afxEmptyString;
    *(undefined4 *)(puVar1 + 8) = param_1;
    *puVar1 = 0xe0;
    puVar1[1] = 0;
    puVar1[2] = 4;
    puVar1[3] = 0;
    CString_AssignW((CString *)(puVar1 + 0xc),param_2);
  }
  FUN_0002f108(puVar1);
  return;
}


// 00035cb8 FUN_00035cb8

undefined4 FUN_00035cb8(undefined4 param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  wchar_t *pwVar3;
  uint uVar4;
  wchar_t awStack_210 [256];
  
  iVar1 = FUN_0002eec8(param_1,awStack_210,0x100);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    pwVar3 = wcschr(awStack_210,L'\n');
    if (pwVar3 != (wchar_t *)0x0) {
      uVar4 = _wtol(pwVar3 + 1);
      *param_2 = uVar4;
      uVar4 = __rt_sdiv64by64(uVar4 * DAT_002de4fc,
                              uVar4 * ((int)DAT_002de4fc >> 0x1f) +
                              ((int)uVar4 >> 0x1f) * DAT_002de4fc +
                              (int)((ulonglong)DAT_002de4fc * (ulonglong)uVar4 >> 0x20),0x48,0);
      *param_2 = uVar4;
      *pwVar3 = L'\0';
    }
    wcsncpy((wchar_t *)(param_2 + 7),awStack_210,0x20);
    uVar2 = 1;
  }
  return uVar2;
}


// 00035d74 FUN_00035d74

undefined4 FUN_00035d74(HWND param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  WCHAR aWStack_20 [10];
  
  if ((param_1 != (HWND)0x0) && (uVar1 = GetWindowLongW(param_1,-0x10), (uVar1 & 0xf) == param_2)) {
    GetClassNameW(param_1,aWStack_20,10);
    iVar2 = lstrcmpiW(aWStack_20,u_combobox_00043ff0);
    if (iVar2 == 0) {
      return 1;
    }
  }
  return 0;
}


// 00035dd8 FUN_00035dd8

bool FUN_00035dd8(HWND param_1,LPCWSTR param_2)

{
  int iVar1;
  WCHAR aWStack_48 [32];
  
  GetClassNameW(param_1,aWStack_48,0x20);
  iVar1 = lstrcmpiW(aWStack_48,param_2);
  return iVar1 == 0;
}


// 00035e10 FUN_00035e10

void FUN_00035e10(HWND param_1,wchar_t *param_2)

{
  size_t sVar1;
  size_t sVar2;
  int iVar3;
  WCHAR aWStack_210 [256];
  
  sVar1 = wcslen(param_2);
  if (((0x100 < sVar1) || (sVar2 = GetWindowTextW(param_1,aWStack_210,0x100), sVar2 != sVar1)) ||
     (iVar3 = lstrcmpW(aWStack_210,param_2), iVar3 != 0)) {
    SetWindowTextW(param_1,param_2);
  }
  return;
}


// 00035e78 FUN_00035e78

void FUN_00035e78(undefined4 *param_1)

{
  if ((HGDIOBJ)*param_1 != (HGDIOBJ)0x0) {
    DeleteObject((HGDIOBJ)*param_1);
    *param_1 = 0;
  }
  return;
}


// 00035e9c FUN_00035e9c

void FUN_00035e9c(HWND param_1)

{
  HWND hWnd;
  int iVar1;
  uint uVar2;
  HWND pHVar3;
  
  hWnd = GetFocus();
  if ((((hWnd != (HWND)0x0) && (hWnd != param_1)) &&
      ((iVar1 = FUN_00035d74(hWnd,3), iVar1 != 0 ||
       ((hWnd = GetParent(hWnd), hWnd != param_1 && (iVar1 = FUN_00035d74(hWnd,2), iVar1 != 0))))))
     && ((param_1 == (HWND)0x0 ||
         ((uVar2 = GetWindowLongW(param_1,-0x10), (uVar2 & 0x40000000) == 0 ||
          (pHVar3 = GetParent(param_1), pHVar3 != (HWND)0x0)))))) {
    SendMessageW(hWnd,0x14f,0,0);
  }
  return;
}


// 00035f38 FUN_00035f38

void FUN_00035f38(undefined1 *param_1)

{
  *param_1 = 200;
  param_1[1] = 8;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  param_1[2] = 4;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  param_1[3] = 0;
  return;
}


// 00035f98 FUN_00035f98

undefined4 FUN_00035f98(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f52c();
  if ((*(int *)(iVar1 + 0x1c) == 0) && (param_1 != 0)) {
    iVar2 = operator_new(0x48);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00033818(iVar2,&CDC::classCDC,4,2);
    }
    *(undefined4 *)(iVar1 + 0x1c) = uVar3;
  }
  return *(undefined4 *)(iVar1 + 0x1c);
}


// 00035ff4 FUN_00035ff4

void FUN_00035ff4(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00035f98(1);
  FUN_00033890(uVar1,param_1);
  return;
}


// 00036010 FUN_00036010

bool FUN_00036010(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_2 != 0) {
    iVar1 = FUN_00035f98(1);
    param_1[1] = param_2;
    piVar2 = (int *)FUN_0002e328(iVar1 + 4,param_2);
    *piVar2 = (int)param_1;
    (**(code **)(*param_1 + 0xc))(param_1,param_1[1]);
  }
  return param_2 != 0;
}


// 00036064 FUN_00036064

int FUN_00036064(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  if ((iVar2 != 0) && (iVar1 = FUN_00035f98(0), iVar1 != 0)) {
    FUN_0002e394(iVar1 + 4,param_1[1]);
  }
  (**(code **)(*param_1 + 0x14))(param_1);
  param_1[1] = 0;
  return iVar2;
}


// 000360b4 FUN_000360b4

void FUN_000360b4(undefined1 *param_1)

{
  HDC hdc;
  
  *param_1 = 200;
  param_1[1] = 8;
  param_1[2] = 4;
  param_1[3] = 0;
  if (*(int *)(param_1 + 4) != 0) {
    hdc = (HDC)FUN_00036064();
    DeleteDC(hdc);
  }
  return;
}


// 0003611c FUN_0003611c

int FUN_0003611c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (*(HDC *)(param_1 + 8) != (HDC)0x0) {
    iVar2 = SaveDC(*(HDC *)(param_1 + 8));
  }
  if ((*(HDC *)(param_1 + 4) != *(HDC *)(param_1 + 8)) &&
     (iVar1 = SaveDC(*(HDC *)(param_1 + 4)), iVar1 != 0)) {
    iVar2 = -1;
  }
  return iVar2;
}


// 00036160 FUN_00036160

int FUN_00036160(int param_1,int param_2)

{
  int iVar1;
  BOOL BVar2;
  
  iVar1 = 1;
  if (*(HDC *)(param_1 + 4) != *(HDC *)(param_1 + 8)) {
    iVar1 = RestoreDC(*(HDC *)(param_1 + 4),param_2);
  }
  if (*(HDC *)(param_1 + 8) != (HDC)0x0) {
    if ((iVar1 != 0) && (BVar2 = RestoreDC(*(HDC *)(param_1 + 8),param_2), BVar2 != 0)) {
      return 1;
    }
    iVar1 = 0;
  }
  return iVar1;
}


// 000361b8 FUN_000361b8

void FUN_000361b8(int param_1,int param_2)

{
  HGDIOBJ h;
  
  h = GetStockObject(param_2);
  if (*(HDC *)(param_1 + 4) != *(HDC *)(param_1 + 8)) {
    SelectObject(*(HDC *)(param_1 + 4),h);
  }
  if (*(HDC *)(param_1 + 8) != (HDC)0x0) {
    SelectObject(*(HDC *)(param_1 + 8),h);
  }
  FUN_0003648c();
  return;
}


// 00036204 FUN_00036204

void FUN_00036204(int param_1,int param_2)

{
  HGDIOBJ pvVar1;
  
  pvVar1 = (HGDIOBJ)0x0;
  if (*(HDC *)(param_1 + 4) != *(HDC *)(param_1 + 8)) {
    pvVar1 = (HGDIOBJ)0x0;
    if (param_2 != 0) {
      pvVar1 = *(HGDIOBJ *)(param_2 + 4);
    }
    pvVar1 = SelectObject(*(HDC *)(param_1 + 4),pvVar1);
  }
  if (*(HDC *)(param_1 + 8) != (HDC)0x0) {
    pvVar1 = (HGDIOBJ)0x0;
    if (param_2 != 0) {
      pvVar1 = *(HGDIOBJ *)(param_2 + 4);
    }
    pvVar1 = SelectObject(*(HDC *)(param_1 + 8),pvVar1);
  }
  FUN_0003648c(pvVar1);
  return;
}


// 00036260 FUN_00036260

void FUN_00036260(int param_1,COLORREF param_2)

{
  if (*(HDC *)(param_1 + 4) != *(HDC *)(param_1 + 8)) {
    SetBkColor(*(HDC *)(param_1 + 4),param_2);
  }
  if (*(HDC *)(param_1 + 8) != (HDC)0x0) {
    SetBkColor(*(HDC *)(param_1 + 8),param_2);
  }
  return;
}


// 0003629c FUN_0003629c

void FUN_0003629c(int param_1,COLORREF param_2)

{
  if (*(HDC *)(param_1 + 4) != *(HDC *)(param_1 + 8)) {
    SetTextColor(*(HDC *)(param_1 + 4),param_2);
  }
  if (*(HDC *)(param_1 + 8) != (HDC)0x0) {
    SetTextColor(*(HDC *)(param_1 + 8),param_2);
  }
  return;
}


// 000362e0 FUN_000362e0

void FUN_000362e0(int param_1,LPPOINT param_2)

{
  uint uVar1;
  LONG LVar2;
  
  ScreenToClient(*(HWND *)(param_1 + 0x1c),param_2);
  ScreenToClient(*(HWND *)(param_1 + 0x1c),param_2 + 1);
  uVar1 = FUN_00033b4c(param_1);
  if ((uVar1 & 0x400000) != 0) {
    LVar2 = param_2[1].x;
    param_2[1].x = param_2->x;
    param_2->x = LVar2;
  }
  return;
}


// 00036320 FUN_00036320

void FUN_00036320(int param_1,LPPOINT param_2)

{
  uint uVar1;
  LONG LVar2;
  
  ClientToScreen(*(HWND *)(param_1 + 0x1c),param_2);
  ClientToScreen(*(HWND *)(param_1 + 0x1c),param_2 + 1);
  uVar1 = FUN_00033b4c(param_1);
  if ((uVar1 & 0x400000) != 0) {
    LVar2 = param_2[1].x;
    param_2[1].x = param_2->x;
    param_2->x = LVar2;
  }
  return;
}


// 00036360 FUN_00036360

undefined1 * FUN_00036360(undefined1 *param_1,int param_2)

{
  HWND hWnd;
  HDC pHVar1;
  int iVar2;
  
  FUN_00035f38();
  *param_1 = 0x10;
  param_1[1] = 9;
  param_1[2] = 4;
  param_1[3] = 0;
  hWnd = *(HWND *)(param_2 + 0x1c);
  *(HWND *)(param_1 + 0x14) = hWnd;
  pHVar1 = BeginPaint(hWnd,(LPPAINTSTRUCT)(param_1 + 0x18));
  iVar2 = FUN_00036010(param_1,pHVar1);
  if (iVar2 == 0) {
    FUN_00036504();
  }
  return param_1;
}


// 000363e4 FUN_000363e4

void FUN_000363e4(undefined1 *param_1)

{
  *param_1 = 0x10;
  param_1[1] = 9;
  param_1[2] = 4;
  param_1[3] = 0;
  EndPaint(*(HWND *)(param_1 + 0x14),(PAINTSTRUCT *)(param_1 + 0x18));
  FUN_00036064(param_1);
  FUN_000360b4(param_1);
  return;
}


// 00036430 FUN_00036430

undefined4 FUN_00036430(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f52c();
  if ((*(int *)(iVar1 + 0x20) == 0) && (param_1 != 0)) {
    iVar2 = operator_new(0x48);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00033818(iVar2,&CGdiObject::classCGdiObject,4,1);
    }
    *(undefined4 *)(iVar1 + 0x20) = uVar3;
  }
  return *(undefined4 *)(iVar1 + 0x20);
}


// 0003648c FUN_0003648c

void FUN_0003648c(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00036430(1);
  FUN_00033890(uVar1,param_1);
  return;
}


// 000364a8 FUN_000364a8

int FUN_000364a8(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 4);
  if ((iVar2 != 0) && (iVar1 = FUN_00036430(0), iVar1 != 0)) {
    FUN_0002e394(iVar1 + 4,*(undefined4 *)(param_1 + 4));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  return iVar2;
}


// 000364e4 FUN_000364e4

void FUN_000364e4(int param_1)

{
  HGDIOBJ ho;
  
  if (*(int *)(param_1 + 4) != 0) {
    ho = (HGDIOBJ)FUN_000364a8(param_1);
    DeleteObject(ho);
  }
  return;
}


// 00036504 FUN_00036504

void FUN_00036504(void)

{
  FUN_0002f108(&DAT_002de3b8);
  return;
}


// 0003651c FUN_0003651c

void FUN_0003651c(int param_1)

{
  BOOL BVar1;
  
  BVar1 = IsWindow(*(HWND *)(param_1 + 0x7c));
  if ((BVar1 == 0) ||
     (BVar1 = IsChild(*(HWND *)(param_1 + 0x1c),*(HWND *)(param_1 + 0x7c)), BVar1 == 0)) {
    *(undefined4 *)(param_1 + 0x7c) = 0;
    FUN_0002ff50(param_1);
  }
  else {
    SetFocus(*(HWND *)(param_1 + 0x7c));
  }
  return;
}


// 00036568 FUN_00036568

undefined4 FUN_00036568(int param_1)

{
  int iVar1;
  int *piVar2;
  
  FUN_0002ff50();
  iVar1 = FUN_0003f4f4();
  piVar2 = *(int **)(iVar1 + 0x2038);
  if ((piVar2 != (int *)0x0) && (*(int *)(param_1 + 0x80) != 0)) {
    (**(code **)(*piVar2 + 0x20))(piVar2,param_1,*(undefined4 *)(param_1 + 0x74));
  }
  return 0;
}


// 000365d4 FUN_000365d4

void FUN_000365d4(void)

{
  return;
}


// 000365d8 FUN_000365d8

undefined1 * FUN_000365d8(int param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  tagRECT local_20;
  
  local_24 = FUN_00031e74(param_1,1);
  local_28 = FUN_00031e74(param_1,0);
  if (*(int *)(param_1 + 0x6c) != 0) {
    GetClientRect(*(HWND *)(param_1 + 0x1c),&local_20);
    if (*(int *)(param_1 + 0x54) < local_20.right - local_20.left) {
      iVar1 = (local_20.right - local_20.left) - *(int *)(param_1 + 0x54);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 1;
      }
      local_28 = -(iVar1 >> 1);
    }
    if (*(int *)(param_1 + 0x58) < local_20.bottom - local_20.top) {
      iVar1 = (local_20.bottom - local_20.top) - *(int *)(param_1 + 0x58);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 1;
      }
      local_24 = -(iVar1 >> 1);
    }
  }
  *param_2 = (undefined1)local_28;
  param_2[1] = local_28._1_1_;
  param_2[2] = local_28._2_1_;
  param_2[3] = local_28._3_1_;
  param_2[4] = (undefined1)local_24;
  param_2[5] = local_24._1_1_;
  param_2[6] = local_24._2_1_;
  param_2[7] = local_24._3_1_;
  return param_2;
}


// 000366d4 FUN_000366d4

void FUN_000366d4(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00031e74(param_1,0);
  FUN_00031e2c(param_1,0,param_2,1);
  iVar2 = FUN_00031e74(param_1,1);
  FUN_00031e2c(param_1,1,param_3,1);
  FUN_0002b228(*(undefined4 *)(param_1 + 0x1c),param_2 - iVar1,param_3 - iVar2);
  FUN_00031ffc(param_1,iVar1 - param_2,iVar2 - param_3,0,0);
  return;
}


// 00036760 FUN_00036760

void FUN_00036760(int param_1)

{
  FUN_0002ff50();
  if (*(int *)(param_1 + 0x48) == -1) {
    FUN_000365d4(param_1,*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50));
  }
  else {
    FUN_00036a90(param_1);
  }
  return;
}


// 00036798 FUN_00036798

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00036798(int *param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  param_2[1] = 0;
  *param_2 = 0;
  uVar1 = FUN_00033b14(param_1);
  iVar2 = (**(code **)(*param_1 + 0x60))(param_1,1);
  if (iVar2 == 0) {
    bVar3 = (uVar1 & 0x800000) != 0;
    iVar2 = 0;
    if (bVar3) {
      iVar2 = _afxData;
    }
    *param_2 = _afxData;
    if (bVar3) {
      *param_2 = iVar2 + -1;
    }
  }
  iVar2 = (**(code **)(*param_1 + 0x60))(param_1,0);
  if (iVar2 == 0) {
    bVar3 = (uVar1 & 0x800000) != 0;
    iVar2 = 0;
    if (bVar3) {
      iVar2 = DAT_002de4e4;
    }
    param_2[1] = DAT_002de4e4;
    if (bVar3) {
      param_2[1] = iVar2 + -1;
    }
  }
  return;
}


// 00036838 FUN_00036838

undefined4 FUN_00036838(int param_1,int *param_2,int *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  tagRECT tStack_24;
  
  GetClientRect(*(HWND *)(param_1 + 0x1c),&tStack_24);
  *param_2 = tStack_24.right;
  param_2[1] = tStack_24.bottom;
  uVar1 = FUN_00033b14(param_1);
  FUN_00036798(param_1,param_3);
  if (*param_3 != 0 && (uVar1 & 0x200000) != 0) {
    *param_2 = *param_2 + *param_3;
  }
  if (param_3[1] != 0 && (uVar1 & 0x100000) != 0) {
    param_2[1] = param_2[1] + param_3[1];
  }
  if ((*param_2 <= *param_3) || (uVar2 = 1, param_2[1] <= param_3[1])) {
    uVar2 = 0;
  }
  return uVar2;
}


// 000368e0 FUN_000368e0

void FUN_000368e0(int param_1,int param_2,int param_3,int *param_4,int *param_5,int *param_6,
                 int param_7)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  int local_2c;
  
  FUN_00036798(param_1,&local_30);
  param_2 = *(int *)(param_1 + 0x54) - param_2;
  param_3 = *(int *)(param_1 + 0x58) - param_3;
  local_38._0_1_ = (undefined1)param_2;
  *(undefined1 *)param_5 = (undefined1)local_38;
  local_38._1_1_ = (undefined1)((uint)param_2 >> 8);
  *(undefined1 *)((int)param_5 + 1) = local_38._1_1_;
  local_38._2_1_ = (undefined1)((uint)param_2 >> 0x10);
  *(undefined1 *)((int)param_5 + 2) = local_38._2_1_;
  local_38._3_1_ = (undefined1)((uint)param_2 >> 0x18);
  *(undefined1 *)((int)param_5 + 3) = local_38._3_1_;
  local_34._0_1_ = (undefined1)param_3;
  *(undefined1 *)(param_5 + 1) = (undefined1)local_34;
  local_34._1_1_ = (undefined1)((uint)param_3 >> 8);
  *(undefined1 *)((int)param_5 + 5) = local_34._1_1_;
  local_34._2_1_ = (undefined1)((uint)param_3 >> 0x10);
  *(undefined1 *)((int)param_5 + 6) = local_34._2_1_;
  local_34._3_1_ = (undefined1)((uint)param_3 >> 0x18);
  *(undefined1 *)((int)param_5 + 7) = local_34._3_1_;
  local_38 = param_2;
  local_34 = param_3;
  puVar1 = (undefined1 *)FUN_000365d8(param_1,&local_38);
  *(undefined1 *)param_6 = *puVar1;
  *(undefined1 *)((int)param_6 + 1) = puVar1[1];
  *(undefined1 *)((int)param_6 + 2) = puVar1[2];
  *(undefined1 *)((int)param_6 + 3) = puVar1[3];
  *(undefined1 *)(param_6 + 1) = puVar1[4];
  *(undefined1 *)((int)param_6 + 5) = puVar1[5];
  *(undefined1 *)((int)param_6 + 6) = puVar1[6];
  *(undefined1 *)((int)param_6 + 7) = puVar1[7];
  iVar3 = 0;
  if (*param_5 < 1) {
    *param_6 = 0;
  }
  else {
    if (param_7 != 0) {
      puVar1 = (undefined1 *)param_5[1];
    }
    iVar3 = 1;
    if (param_7 != 0) {
      param_5[1] = (int)(puVar1 + local_2c);
    }
  }
  if (param_5[1] < 1) {
    iVar4 = 0;
    param_6[1] = 0;
  }
  else {
    iVar4 = 1;
    if (param_7 != 0) {
      *param_5 = *param_5 + local_30;
    }
    if (iVar3 == 0) {
      if (*param_5 < 1) goto LAB_00036a68;
      iVar3 = 1;
      param_5[1] = param_5[1] + local_2c;
    }
  }
  iVar2 = *param_5;
  if ((0 < iVar2) && (iVar2 <= *param_6)) {
    *param_6 = iVar2;
  }
LAB_00036a68:
  iVar2 = param_5[1];
  if ((0 < iVar2) && (iVar2 <= param_6[1])) {
    param_6[1] = iVar2;
  }
  *param_4 = iVar3;
  param_4[1] = iVar4;
  return;
}


// 00036a90 FUN_00036a90

void FUN_00036a90(int param_1)

{
  int iVar1;
  LRESULT LVar2;
  undefined4 uVar3;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  tagRECT tStack_40;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  
  if (*(int *)(param_1 + 0x70) == 0) {
    *(undefined4 *)(param_1 + 0x70) = 1;
    uVar3 = 1;
    GetParent(*(HWND *)(param_1 + 0x1c));
    iVar1 = FUN_0002ffec();
    if ((iVar1 == 0) ||
       (LVar2 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0x368,0,(LPARAM)&local_50), LVar2 == 0)) {
      iVar1 = FUN_00036838(param_1,&local_78,&local_68);
      if (iVar1 == 0) {
        GetClientRect(*(HWND *)(param_1 + 0x1c),&tStack_40);
        if (0 < tStack_40.right) {
          tStack_40.right = tStack_40.bottom;
        }
        if (0 < tStack_40.right) {
          FUN_00031f18(param_1,3,0);
        }
        *(undefined4 *)(param_1 + 0x70) = 0;
        return;
      }
    }
    else {
      uVar3 = 0;
      FUN_00036798(param_1,&local_68);
      local_78 = local_48 - local_50;
      local_74 = local_44 - local_4c;
    }
    FUN_000368e0(param_1,local_78,local_74,&local_70,&local_58,&local_60,uVar3);
    if (local_70 != 0) {
      local_74 = local_74 - local_64;
    }
    if (local_6c != 0) {
      local_78 = local_78 - local_68;
    }
    FUN_000366d4(param_1,local_60,local_5c);
    memset(&local_30,0,0x1c);
    local_30 = 0x1c;
    local_2c = 3;
    local_28 = 0;
    FUN_00031f18(param_1,0,local_70);
    if (local_70 != 0) {
      local_20 = local_78;
      local_24 = *(int *)(param_1 + 0x54) + -1;
      iVar1 = FUN_00031f7c(param_1,0,&local_30,1);
      if (iVar1 == 0) {
        FUN_00031eac(param_1,0,0,local_58,1);
      }
    }
    FUN_00031f18(param_1,1,local_6c);
    if (local_6c != 0) {
      local_20 = local_74;
      local_24 = *(int *)(param_1 + 0x58) + -1;
      iVar1 = FUN_00031f7c(param_1,1,&local_30,1);
      if (iVar1 == 0) {
        FUN_00031eac(param_1,1,0,local_54,1);
      }
    }
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  return;
}


// 00036cc0 FUN_00036cc0

void FUN_00036cc0(int *param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  if (((param_4 == 0) || (iVar1 = FUN_00032444(param_4,0), iVar1 == 0)) &&
     ((iVar1 = (**(code **)(*param_1 + 0x60))(param_1,1), iVar1 == 0 || (param_4 == iVar1)))) {
    (**(code **)(*param_1 + 0xb4))(param_1,param_2 & 0xff | 0xff00,param_3,1);
  }
  return;
}


// 00036d40 FUN_00036d40

void FUN_00036d40(int *param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  if (((param_4 == 0) || (iVar1 = FUN_00032444(param_4,0), iVar1 == 0)) &&
     ((iVar1 = (**(code **)(*param_1 + 0x60))(param_1,1), iVar1 == 0 || (param_4 == iVar1)))) {
    (**(code **)(*param_1 + 0xb4))(param_1,(param_2 & 0xff) << 8 | 0xff,param_3,1);
  }
  return;
}


// 00036dcc FUN_00036dcc

int FUN_00036dcc(int param_1)

{
  FUN_0002fa00();
  *(undefined4 *)(param_1 + 0x44) = 0;
  return param_1;
}


// 00036de8 FUN_00036de8

void FUN_00036de8(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003f170();
  if (*(int *)(iVar1 + 0x128) == param_1) {
    iVar1 = FUN_0003f170();
    *(undefined4 *)(iVar1 + 0x128) = 0;
  }
  if (*(int *)(param_1 + 0x44) != 0) {
    FUN_000373e4(*(int *)(param_1 + 0x44),param_1);
  }
  FUN_00030500(param_1);
  return;
}


// 00036e28 FUN_00036e28

undefined4 FUN_00036e28(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x28) == 0) {
    FUN_00033358(8);
    *(wchar_t **)(param_2 + 0x28) = L"AfxFrameOrView42su";
  }
  return 1;
}


// 00036e58 FUN_00036e58

undefined4 FUN_00036e58(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_0002ff50();
  if (iVar1 == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    iVar3 = *param_2;
    iVar1 = 0;
    if (iVar3 != 0) {
      iVar1 = *(int *)(iVar3 + 4);
    }
    if (iVar3 != 0 && iVar1 != 0) {
      FUN_000373b4(iVar1,param_1);
    }
    uVar2 = 0;
  }
  return uVar2;
}


// 00036e98 FUN_00036e98

void FUN_00036e98(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_00031a70();
  if ((iVar2 != 0) && (iVar3 = FUN_0003c120(iVar2), iVar3 == param_1)) {
    FUN_0003c128(iVar2,0,1);
  }
  piVar1 = *(int **)(param_1 + 0x38);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(piVar1,1);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_000336d0(param_1,0);
  }
  FUN_0002ff50(param_1);
  return;
}


// 00036ef4 FUN_00036ef4

undefined4
FUN_00036ef4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0002f3c4();
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x44) == 0) {
      uVar2 = 0;
    }
    else {
      iVar1 = FUN_0003f170(0);
      uVar3 = *(undefined4 *)(iVar1 + 0x128);
      *(int *)(iVar1 + 0x128) = param_1;
      uVar2 = (**(code **)(**(int **)(param_1 + 0x44) + 0xc))
                        (*(int **)(param_1 + 0x44),param_2,param_3,param_4,param_5);
      *(undefined4 *)(iVar1 + 0x128) = uVar3;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}


// 00036f78 FUN_00036f78

void FUN_00036f78(int *param_1)

{
  undefined1 auStack_60 [88];
  
  FUN_00036360(auStack_60,param_1);
  (**(code **)(*param_1 + 0xbc))(param_1,auStack_60,0);
  (**(code **)(*param_1 + 0xd0))(param_1,auStack_60);
  FUN_000363e4(auStack_60);
  return;
}


// 00036fd4 FUN_00036fd4

void FUN_00036fd4(int *param_1)

{
  (**(code **)(*param_1 + 0xcc))(param_1,0,0,0);
  return;
}


// 00037010 FUN_00037010

void FUN_00037010(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if ((param_2 != 0) && (iVar1 = FUN_00031b68(), iVar1 != 0)) {
    FUN_00033e00(param_1);
  }
  return;
}


// 00037048 FUN_00037048

undefined4 FUN_00037048(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  BOOL BVar3;
  
  GetParent(*(HWND *)(param_1 + 0x1c));
  uVar1 = FUN_0002ffec();
  iVar2 = FUN_0002ed1c(uVar1,&CSplitterWnd::classCSplitterWnd);
  if (iVar2 != 0) {
    if (param_2 != 0) {
      return uVar1;
    }
    do {
      GetParent(*(HWND *)(param_1 + 0x1c));
      param_1 = FUN_0002ffec();
      if (param_1 == 0) {
        return uVar1;
      }
      BVar3 = IsWindowEnabled(*(HWND *)(param_1 + 0x1c));
    } while (BVar3 != 0);
  }
  return 0;
}


// 000370b8 FUN_000370b8

undefined4 FUN_000370b8(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  
  uVar1 = FUN_00033b14();
  uVar4 = 0x100000;
  if (param_2 != 0) {
    uVar4 = 0x200000;
  }
  if (((uVar1 & uVar4) == 0) && (iVar2 = FUN_00037048(param_1,1), iVar2 != 0)) {
    uVar4 = GetDlgCtrlID(*(HWND *)(param_1 + 0x1c));
    uVar1 = uVar4 & 0xffff;
    if ((0xe8ff < uVar1) && (uVar1 < 0xea00)) {
      if (param_2 == 0) {
        iVar5 = (uVar4 & 0xf) + 0xea00;
      }
      else {
        iVar5 = (uVar1 - 0xe900 >> 4) + 0xea10;
      }
      uVar3 = FUN_00033a44(iVar2,iVar5);
      return uVar3;
    }
  }
  return 0;
}


// 0003714c FUN_0003714c

void FUN_0003714c(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00037048(param_1,0);
  if ((iVar1 == 0) || (uVar2 = 1, *(int *)(iVar1 + 0x88) != 0)) {
    uVar2 = 0;
  }
  (**(code **)*param_2)(param_2,uVar2);
  return;
}


// 00037190 FUN_00037190

bool FUN_00037190(undefined4 param_1)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00037048(param_1,0);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0xe8))();
  }
  return piVar1 != (int *)0x0;
}


// 000371c0 FUN_000371c0

void FUN_000371c0(undefined4 param_1,undefined4 *param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = (int *)FUN_00037048(param_1,0);
  if (piVar1 != (int *)0x0) {
    iVar2 = (**(code **)(*piVar1 + 0xe0))(piVar1,param_2[1] == 0xe151);
    uVar3 = 1;
    if (iVar2 != 0) goto LAB_00037210;
  }
  uVar3 = 0;
LAB_00037210:
  (**(code **)*param_2)(param_2,uVar3);
  return;
}


// 00037228 FUN_00037228

bool FUN_00037228(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00037048(param_1,0);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0xe4))(piVar1,param_2 == 0xe151);
  }
  return piVar1 != (int *)0x0;
}


// 00037274 FUN_00037274

int FUN_00037274(int param_1,wchar_t *param_2,undefined4 param_3)

{
  FUN_00036dcc();
  ((CString *)(param_1 + 0x48))->str = g_afxEmptyString;
  CString_AssignW((CString *)(param_1 + 0x48),param_2);
  *(undefined4 *)(param_1 + 0x4c) = param_3;
  return param_1;
}


// 000372b0 FUN_000372b0

void FUN_000372b0(int param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x48);
  FUN_00033358(0x10);
  FUN_00033358(0x3c000);
  if ((*(uint *)(param_2 + 0x20) | 0x800000) == 0x50800000) {
    *(uint *)(param_2 + 0x20) = (*(uint *)(param_2 + 0x20) | 0xff7fffff) & *(uint *)(param_1 + 0x4c)
    ;
  }
  FUN_00036e28(param_1,param_2);
  return;
}


// 00037314 FUN_00037314

void FUN_00037314(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x8c))();
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0x78))(param_1);
  }
  return;
}


// 00037348 FUN_00037348

void FUN_00037348(int *param_1)

{
  (**(code **)(*param_1 + 0x98))();
  return;
}


// 00037360 FUN_00037360

void FUN_00037360(int *param_1)

{
  (**(code **)(*param_1 + 0x94))(param_1,0,1);
  return;
}


// 00037380 FUN_00037380

void FUN_00037380(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x8c))();
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0x78))(param_1);
  }
  return;
}


// 000373b4 FUN_000373b4

void FUN_000373b4(int *param_1,int param_2)

{
  FUN_0002dac8(param_1 + 10);
  *(int **)(param_2 + 0x44) = param_1;
  (**(code **)(*param_1 + 100))(param_1);
  return;
}


// 000373e4 FUN_000373e4

void FUN_000373e4(int *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0002db68(param_1 + 10,param_2,0);
  FUN_0002db2c(param_1 + 10,uVar1);
  *(undefined4 *)(param_2 + 0x44) = 0;
  (**(code **)(*param_1 + 100))(param_1);
  return;
}


// 0003742c FUN_0003742c

void FUN_0003742c(int param_1)

{
  if (0x3ffffffd < *(uint *)(param_1 + 0x30)) {
    FUN_00035c3c(5,*(undefined4 *)(param_1 + 0x10));
  }
  return;
}


// 00037450 FUN_00037450

void FUN_00037450(int param_1,int *param_2)

{
  uint *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  
  FUN_0003761c(param_1,0);
  if (param_2 == (int *)0x0) {
    uVar4 = 0;
  }
  else {
    puVar1 = (uint *)FUN_0002e328(*(undefined4 *)(param_1 + 0x34),param_2);
    uVar4 = *puVar1;
    if (uVar4 == 0) {
      uVar2 = (**(code **)*param_2)(param_2);
      FUN_0003773c(param_1,uVar2);
      FUN_0003742c(param_1);
      puVar3 = (undefined4 *)FUN_0002e328(*(undefined4 *)(param_1 + 0x34),param_2);
      *puVar3 = *(undefined4 *)(param_1 + 0x30);
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
      (**(code **)(*param_2 + 8))(param_2,param_1);
      return;
    }
    if (0x7ffe < uVar4) {
      FUN_0002aa60(param_1,0x7fff);
      FUN_0002aaa4(param_1,uVar4);
      return;
    }
    uVar4 = uVar4 & 0xffff;
  }
  FUN_0002aa60(param_1,uVar4);
  return;
}


// 00037530 FUN_00037530

int * FUN_00037530(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  uint local_18;
  undefined4 local_14;
  
  iVar1 = FUN_00037808(param_1,param_2,&local_14,&local_18);
  if (iVar1 == 0) {
    if (*(int *)(*(int *)(param_1 + 0x34) + 8) - 1U < local_18) {
      FUN_00035c3c(5,*(undefined4 *)(param_1 + 0x10));
    }
    piVar2 = *(int **)(*(int *)(*(int *)(param_1 + 0x34) + 4) + local_18 * 4);
    if (((piVar2 != (int *)0x0) && (param_2 != 0)) &&
       (iVar1 = FUN_0002ed1c(piVar2,param_2), iVar1 == 0)) {
      FUN_00035c3c(6,*(undefined4 *)(param_1 + 0x10));
    }
  }
  else {
    piVar2 = (int *)FUN_0002ed70();
    if (piVar2 == (int *)0x0) {
      FUN_0002d3cc();
    }
    FUN_0003742c(param_1);
    iVar1 = *(int *)(param_1 + 0x30);
    *(int *)(param_1 + 0x30) = iVar1 + 1;
    FUN_0002dd5c(*(undefined4 *)(param_1 + 0x34),iVar1,piVar2,1);
    uVar3 = *(undefined4 *)(param_1 + 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    (**(code **)(*piVar2 + 8))(piVar2,param_1);
    *(undefined4 *)(param_1 + 0xc) = uVar3;
  }
  return piVar2;
}


// 0003761c FUN_0003761c

void FUN_0003761c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  if ((*(uint *)(param_1 + 0x14) & 1) == 0) {
    if (*(int *)(param_1 + 0x34) == 0) {
      iVar1 = operator_new(0x1c);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_0002e060(iVar1,*(undefined4 *)(param_1 + 0x3c));
      }
      *(undefined4 *)(param_1 + 0x34) = uVar2;
      FUN_0002e0cc(uVar2,*(undefined4 *)(param_1 + 0x40),1);
      puVar3 = (undefined4 *)FUN_0002e328(*(undefined4 *)(param_1 + 0x34),0);
      *puVar3 = 0;
      *(undefined4 *)(param_1 + 0x30) = 1;
    }
    if (param_2 != 0) {
      FUN_0003742c(param_1);
      puVar3 = (undefined4 *)FUN_0002e328(*(undefined4 *)(param_1 + 0x34),param_2);
      *puVar3 = *(undefined4 *)(param_1 + 0x30);
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
    }
  }
  else {
    if (*(int *)(param_1 + 0x34) == 0) {
      iVar1 = operator_new(0x14);
      if (iVar1 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = FUN_0002db9c();
      }
      *(undefined4 *)(param_1 + 0x34) = uVar2;
      FUN_0002dc28(uVar2,1,*(undefined4 *)(param_1 + 0x3c));
      **(undefined4 **)(*(int *)(param_1 + 0x34) + 4) = 0;
      *(undefined4 *)(param_1 + 0x30) = 1;
    }
    if (param_2 != 0) {
      FUN_0003742c(param_1);
      iVar1 = *(int *)(param_1 + 0x30);
      *(int *)(param_1 + 0x30) = iVar1 + 1;
      FUN_0002dd5c(*(undefined4 *)(param_1 + 0x34),iVar1,param_2,1);
    }
  }
  return;
}


// 0003773c FUN_0003773c

void FUN_0003773c(int param_1,int param_2)

{
  uint *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if (*(int *)(param_2 + 8) == 0xffff) {
    FUN_0002d3d8();
  }
  FUN_0003761c(param_1,0);
  puVar1 = (uint *)FUN_0002e328(*(undefined4 *)(param_1 + 0x34),param_2);
  uVar3 = *puVar1;
  if (uVar3 == 0) {
    FUN_0002aa60(param_1,0xffff);
    FUN_000355fc(param_2,param_1);
    FUN_0003742c(param_1);
    puVar2 = (undefined4 *)FUN_0002e328(*(undefined4 *)(param_1 + 0x34),param_2);
    *puVar2 = *(undefined4 *)(param_1 + 0x30);
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + 1;
  }
  else if (uVar3 < 0x7fff) {
    FUN_0002aa60(param_1,uVar3 & 0xffff | 0x8000);
  }
  else {
    FUN_0002aa60(param_1,0x7fff);
    FUN_0002aaa4(param_1,uVar3 | 0x80000000);
  }
  return;
}


// 00037808 FUN_00037808

int FUN_00037808(int param_1,int param_2,uint *param_3,uint *param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint *puVar4;
  int iVar5;
  ushort local_30 [2];
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  
  if ((param_2 != 0) && (*(int *)(param_2 + 8) == 0xffff)) {
    FUN_0002d3d8();
  }
  FUN_0003761c(param_1,0);
  FUN_0002aaf8(param_1,local_30);
  uVar1 = (uint)local_30[0];
  if (uVar1 == 0x7fff) {
    FUN_0002ab4c(param_1,&local_28);
  }
  else {
    local_28 = uVar1 & 0xffff7fff | (uVar1 & 0xffff8000) << 0x10;
  }
  uVar1 = local_28;
  if ((local_28 & 0x80000000) == 0) {
    if (param_4 == (uint *)0x0) {
      FUN_00035c3c(5,*(undefined4 *)(param_1 + 0x10));
    }
    iVar2 = 0;
    *param_4 = local_28;
  }
  else {
    if (local_30[0] == 0xffff) {
      iVar2 = FUN_00035544(param_1,&local_2c);
      if (iVar2 == 0) {
        FUN_00035c3c(6,*(undefined4 *)(param_1 + 0x10));
      }
      if ((*(uint *)(iVar2 + 8) & 0x7fffffff) != local_2c) {
        if ((*(uint *)(iVar2 + 8) & 0x80000000) == 0) {
          FUN_00035c3c(7,*(undefined4 *)(param_1 + 0x10));
        }
        else {
          if (*(int *)(param_1 + 0x38) == 0) {
            iVar5 = operator_new(0x1c);
            if (iVar5 == 0) {
              uVar3 = 0;
            }
            else {
              uVar3 = FUN_0002e060(iVar5,10);
            }
            *(undefined4 *)(param_1 + 0x38) = uVar3;
          }
          uVar1 = local_2c;
          puVar4 = (uint *)FUN_0002e328(*(undefined4 *)(param_1 + 0x38),iVar2);
          *puVar4 = uVar1;
        }
      }
      FUN_0003742c(param_1);
      iVar5 = *(int *)(param_1 + 0x30);
      *(int *)(param_1 + 0x30) = iVar5 + 1;
      FUN_0002dd5c(*(undefined4 *)(param_1 + 0x34),iVar5,iVar2,1);
    }
    else {
      if (((local_28 & 0x7fffffff) == 0) ||
         (*(int *)(*(int *)(param_1 + 0x34) + 8) - 1U < (local_28 & 0x7fffffff))) {
        FUN_00035c3c(5,*(undefined4 *)(param_1 + 0x10));
      }
      iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x34) + 4) + uVar1 * 4);
      local_2c = 0;
      if ((*(int *)(param_1 + 0x38) == 0) ||
         (local_20 = FUN_0002e2f8(*(int *)(param_1 + 0x38),iVar2,&local_24), local_2c = local_24,
         local_20 == 0)) {
        local_2c = *(uint *)(iVar2 + 8) & 0x7fffffff;
      }
    }
    if ((param_2 != 0) && (iVar5 = thunk_FUN_0002ee18(iVar2,param_2), iVar5 == 0)) {
      FUN_00035c3c(6,*(undefined4 *)(param_1 + 0x10));
    }
    if (param_3 == (uint *)0x0) {
      *(uint *)(param_1 + 0xc) = local_2c;
    }
    else {
      *param_3 = local_2c;
    }
    if (param_4 != (uint *)0x0) {
      *param_4 = local_28;
    }
  }
  return iVar2;
}


// 00037a38 FUN_00037a38

void FUN_00037a38(void)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_0002acc0();
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0xa8))();
  }
  return;
}


// 00037a58 FUN_00037a58

int FUN_00037a58(int *param_1,LPCWSTR param_2,uint param_3,int param_4)

{
  HWND hWnd;
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  HWND local_24;
  
  (**(code **)(*param_1 + 0x88))(param_1,0x80000000);
  FUN_00037a38(param_1,0);
  hWnd = (HWND)FUN_00037c00(0,&local_24);
  if ((hWnd == (HWND)0x0) ||
     (piVar1 = (int *)SendMessageW(local_24,0x376,0,0), piVar1 == (int *)0x0)) {
    piVar1 = param_1 + 0x25;
  }
  iVar4 = 0;
  if (piVar1 != (int *)0x0) {
    iVar4 = *piVar1;
  }
  if (piVar1 != (int *)0x0 && param_4 != 0) {
    *piVar1 = param_4 + 0x30000;
  }
  if (((param_3 & 0xf0) == 0) &&
     ((uVar2 = param_3 & 0xf, uVar2 < 2 || ((2 < uVar2 && (uVar2 < 5)))))) {
    param_3 = param_3 | 0x30;
  }
  iVar3 = MessageBoxW(hWnd,param_2,(LPCWSTR)param_1[0x1d],param_3 | 0x10000);
  if (piVar1 != (int *)0x0) {
    *piVar1 = iVar4;
  }
  if (local_24 != (HWND)0x0) {
    EnableWindow(local_24,1);
  }
  FUN_00037a38(param_1,1);
  return iVar3;
}


// 00037b50 FUN_00037b50

void FUN_00037b50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  if (*(int **)(iVar1 + 4) == (int *)0x0) {
    FUN_00037a58(0,param_1,param_2,param_3);
  }
  else {
    (**(code **)(**(int **)(iVar1 + 4) + 0x84))();
  }
  return;
}


// 00037b9c FUN_00037b9c

undefined4 FUN_00037b9c(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  CString local_14;
  
  local_14.str = g_afxEmptyString;
  FUN_0002ee30(&local_14,param_1);
  if (param_3 == -1) {
    param_3 = param_1;
  }
  uVar1 = FUN_00037b50(local_14.str,param_2,param_3);
  CString_Dtor(&local_14);
  return uVar1;
}


// 00037c00 FUN_00037c00

HWND FUN_00037c00(HWND param_1,undefined4 *param_2)

{
  HWND hWnd;
  int iVar1;
  uint uVar2;
  HWND pHVar3;
  HWND pHVar4;
  BOOL BVar5;
  HWND hWnd_00;
  
  hWnd_00 = param_1;
  if (param_1 == (HWND)0x0) {
    iVar1 = FUN_00037ce8();
    if ((iVar1 == 0) && (iVar1 = FUN_0002acc0(), iVar1 == 0)) {
      hWnd_00 = (HWND)0x0;
      pHVar3 = hWnd_00;
      pHVar4 = hWnd_00;
      goto joined_r0x00037c70;
    }
    hWnd_00 = *(HWND *)(iVar1 + 0x1c);
    pHVar3 = hWnd_00;
    pHVar4 = hWnd_00;
    if (hWnd_00 == (HWND)0x0) goto joined_r0x00037c70;
  }
  do {
    uVar2 = GetWindowLongW(hWnd_00,-0x10);
    pHVar3 = hWnd_00;
    pHVar4 = hWnd_00;
    if ((uVar2 & 0x40000000) == 0) break;
    hWnd_00 = GetParent(hWnd_00);
    pHVar3 = hWnd_00;
    pHVar4 = hWnd_00;
  } while (hWnd_00 != (HWND)0x0);
joined_r0x00037c70:
  while (hWnd = pHVar3, hWnd != (HWND)0x0) {
    pHVar3 = GetParent(hWnd);
    hWnd_00 = hWnd;
  }
  if ((param_1 == (HWND)0x0) && (pHVar4 != (HWND)0x0)) {
    pHVar4 = GetActiveWindow();
  }
  if (param_2 != (undefined4 *)0x0) {
    if (((hWnd_00 == (HWND)0x0) || (BVar5 = IsWindowEnabled(hWnd_00), BVar5 == 0)) ||
       (hWnd_00 == pHVar4)) {
      *param_2 = 0;
    }
    else {
      *param_2 = hWnd_00;
      EnableWindow(hWnd_00,0);
    }
  }
  return pHVar4;
}


// 00037ce8 FUN_00037ce8

undefined4 FUN_00037ce8(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f170();
  return *(undefined4 *)(iVar1 + 300);
}


// 00037cf8 FUN_00037cf8

void FUN_00037cf8(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 auStack_210 [512];
  
  iVar1 = FUN_0002eec8(param_2,auStack_210,0x100);
  if (iVar1 != 0) {
    FUN_00037d3c(param_1,auStack_210,param_3,param_4);
  }
  return;
}


// 00037d3c FUN_00037d3c

void FUN_00037d3c(CString *param_1,wchar_t *param_2,int param_3,int param_4)

{
  wchar_t wVar1;
  int iVar2;
  wchar_t *pwVar3;
  wchar_t *pwVar4;
  uint uVar5;
  size_t sVar6;
  wchar_t *_Source;
  int iVar7;
  
  iVar7 = 0;
  wVar1 = *param_2;
  pwVar4 = param_2;
  while (wVar1 != L'\0') {
    if (*pwVar4 == L'%') {
      uVar5 = (uint)(ushort)pwVar4[1];
      if ((uVar5 < 0x30) || (0x39 < uVar5)) {
        if ((uVar5 < 0x41) || (0x5a < uVar5)) goto LAB_00037dc4;
        if (uVar5 < 0x3a) goto LAB_00037d9c;
        iVar2 = uVar5 - 0x38;
      }
      else {
LAB_00037d9c:
        iVar2 = uVar5 - 0x31;
      }
      pwVar4 = pwVar4 + 2;
      if (param_4 <= iVar2) goto LAB_00037dc8;
      pwVar3 = *(wchar_t **)(param_3 + iVar2 * 4);
      if (pwVar3 != (wchar_t *)0x0) {
        sVar6 = wcslen(pwVar3);
        iVar7 = iVar7 + sVar6;
      }
    }
    else {
LAB_00037dc4:
      pwVar4 = pwVar4 + 1;
LAB_00037dc8:
      iVar7 = iVar7 + 1;
    }
    wVar1 = *pwVar4;
  }
  pwVar4 = CString_GetBuffer(param_1,iVar7);
LAB_00037e70:
  do {
    if (*param_2 == L'\0') {
      CString_ReleaseBuffer(param_1,(int)pwVar4 - (int)param_1->str >> 1);
      return;
    }
    if (*param_2 == L'%') {
      uVar5 = (uint)(ushort)param_2[1];
      if ((uVar5 < 0x30) || (0x39 < uVar5)) {
        if ((uVar5 < 0x41) || (0x5a < uVar5)) goto LAB_00037e64;
        if (uVar5 < 0x3a) goto LAB_00037e28;
        iVar7 = uVar5 - 0x38;
      }
      else {
LAB_00037e28:
        iVar7 = uVar5 - 0x31;
      }
      pwVar3 = param_2 + 2;
      param_2 = param_2 + 2;
      if (iVar7 < param_4) {
        _Source = *(wchar_t **)(param_3 + iVar7 * 4);
        param_2 = pwVar3;
        if (_Source != (wchar_t *)0x0) {
          wcscpy(pwVar4,_Source);
          sVar6 = wcslen(pwVar4);
          pwVar4 = pwVar4 + sVar6;
        }
        goto LAB_00037e70;
      }
      *pwVar4 = L'?';
    }
    else {
LAB_00037e64:
      *pwVar4 = *param_2;
      param_2 = param_2 + 1;
    }
    pwVar4 = pwVar4 + 1;
  } while( true );
}


// 00037e94 FUN_00037e94

void FUN_00037e94(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_00037cf8(param_1,param_2,&uStack_8,1,&stack0x00000000);
  return;
}


// 00037eb0 FUN_00037eb0

void FUN_00037eb0(int param_1)

{
  FUN_00033d64(*(undefined4 *)(param_1 + 0x1c),0);
  FUN_00033cec(*(undefined4 *)(param_1 + 0x1c),&CWnd::wndBottom,0,0,0,0,0x13);
  return;
}


// 00037efc FUN_00037efc

void FUN_00037efc(int param_1)

{
  if (*(int **)(param_1 + 0x7c) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0x7c) + 0x20))();
  }
  return;
}


// 00037f1c FUN_00037f1c

void FUN_00037f1c(int param_1,undefined4 *param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0xa0);
  if (piVar1 == (int *)0x0) {
    (**(code **)*param_2)(param_2,0);
  }
  else {
    (**(code **)(*piVar1 + 8))(piVar1,param_2);
  }
  return;
}


// 00037f64 FUN_00037f64

undefined4 FUN_00037f64(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = (**(code **)(*param_1 + 0x74))
                    (param_1,*(undefined4 *)(*(int *)(param_1[0x28] + 8) + (param_2 + -0xe110) * 4))
  ;
  if (iVar1 == 0) {
    (*(code *)**(undefined4 **)param_1[0x28])((undefined4 *)param_1[0x28],param_2 + -0xe110);
  }
  return 1;
}


// 00037fb8 FUN_00037fb8

undefined1 * FUN_00037fb8(undefined1 *param_1)

{
  FUN_0003849c();
  FUN_0002ddf8(param_1 + 0xa0);
  FUN_0002ddf8(param_1 + 0xb4);
  *param_1 = 0xd0;
  param_1[1] = 0x12;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0002de84(param_1 + 0xb4,0,0xffffffff);
  FUN_0002de84(param_1 + 0xa0,0,0xffffffff);
  *(undefined1 **)(param_1 + 0x88) = param_1;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  *(undefined2 *)(param_1 + 0xd4) = 0xf000;
  return param_1;
}


// 0003806c FUN_0003806c

void FUN_0003806c(undefined1 *param_1)

{
  int iVar1;
  HWND hWnd;
  
  *param_1 = 0xd0;
  param_1[1] = 0x12;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_00038370(param_1);
  if (*(int *)(param_1 + 0x1c) != 0) {
    iVar1 = FUN_00031a70(param_1);
    if ((iVar1 != 0) && (*(int *)(iVar1 + 0x48) == *(int *)(param_1 + 0x1c))) {
      *(undefined4 *)(iVar1 + 0x48) = 0;
    }
    hWnd = *(HWND *)(param_1 + 0x1c);
    FUN_00030090(param_1);
    DestroyWindow(hWnd);
  }
  FUN_0002de58(param_1 + 0xb4);
  FUN_0002de58(param_1 + 0xa0);
  FUN_00038544(param_1);
  return;
}


// 0003810c FUN_0003810c

void FUN_0003810c(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  (**(code **)(**(int **)(iVar1 + 4) + 0xc))(*(int **)(iVar1 + 4),0xe100,0,0,0);
  return;
}


// 00038148 FUN_00038148

void FUN_00038148(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined1 auStack_34 [16];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  iVar6 = *param_1;
  puVar2 = &local_20;
  iVar3 = 0x10;
  puVar5 = auStack_34;
  local_24 = param_4;
  do {
    iVar4 = iVar3 + -1;
    *puVar5 = *(undefined1 *)puVar2;
    bVar1 = 0 < iVar3;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
    iVar3 = iVar4;
    puVar5 = puVar5 + 1;
  } while (iVar4 != 0 && bVar1);
  (**(code **)(iVar6 + 0xd8))(param_1,param_2,0,param_3);
  return;
}


// 000381a8 FUN_000381a8

undefined4 FUN_000381a8(int *param_1,int *param_2)

{
  int iVar1;
  LRESULT LVar2;
  undefined4 uVar3;
  undefined4 local_34;
  int local_30;
  undefined4 local_28;
  undefined4 local_24;
  int local_18;
  
  iVar1 = FUN_0003f4f4();
  uVar3 = *(undefined4 *)(iVar1 + 0xc);
  memset(&local_34,0,0x20);
  local_34 = 0x20;
  local_30 = 0;
  if (param_2 != (int *)0x0) {
    local_30 = param_2[7];
  }
  local_28 = 0x701c;
  local_24 = uVar3;
  SHCreateMenuBar(&local_34);
  if (local_18 == 0) {
    uVar3 = 0;
  }
  else {
    FUN_00033660(param_1);
    iVar1 = (**(code **)(*param_2 + 0xa8))(param_2);
    if (iVar1 != 0) {
      param_1[0x1d] = (int)param_2;
      FUN_0002dac8(param_2 + 0x1f,param_1);
      *(int *)(param_1[0x1d] + 0x48) = local_18;
    }
    if (param_1[0x36] == 0) {
      (**(code **)(*param_1 + 0x98))(param_1,0x416,0,0);
    }
    LVar2 = SendMessageW((HWND)param_1[7],0x418,0,0);
    param_1[0x18] = LVar2;
    uVar3 = 1;
  }
  return uVar3;
}


// 00038370 FUN_00038370

void FUN_00038370(int param_1)

{
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  uVar6 = FUN_00031a70();
  uVar1 = (undefined4)((ulonglong)uVar6 >> 0x20);
  iVar3 = (int)uVar6;
  iVar5 = *(int *)(param_1 + 0xbc);
  iVar4 = 0;
  if (0 < iVar5) {
    do {
      piVar2 = *(int **)(*(int *)(param_1 + 0xb8) + iVar4 * 4);
      if (iVar3 != 0) {
        FUN_0002b038(*(undefined4 *)(iVar3 + 0x1c),uVar1);
        uVar6 = FUN_00033eec();
        uVar1 = (undefined4)((ulonglong)uVar6 >> 0x20);
        if ((int *)uVar6 == piVar2) {
          FUN_0002b050(*(undefined4 *)(iVar3 + 0x1c));
          uVar1 = extraout_r1;
        }
      }
      if (piVar2[1] != 0) {
        FUN_00033f6c(piVar2);
        uVar1 = extraout_r1_00;
      }
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 4))();
        uVar1 = extraout_r1_01;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar5);
  }
  iVar4 = *(int *)(param_1 + 0xa8);
  iVar3 = 0;
  if (0 < iVar4) {
    do {
      piVar2 = *(int **)(*(int *)(param_1 + 0xa4) + iVar3 * 4);
      if (piVar2[7] != 0) {
        FUN_00030090(piVar2,uVar1);
        uVar1 = extraout_r1_02;
      }
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 4))();
        uVar1 = extraout_r1_03;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar4);
  }
  FUN_0002de84(param_1 + 0xb4,0,0xffffffff);
  FUN_0002de84(param_1 + 0xa0,0,0xffffffff);
  return;
}


// 00038468 FUN_00038468

undefined4 FUN_00038468(int param_1)

{
  BOOL BVar1;
  
  if (((*(char *)(param_1 + 9) == '\x01') && (*(HWND *)(param_1 + 0xc) != (HWND)0x0)) &&
     (BVar1 = IsWindow(*(HWND *)(param_1 + 0xc)), BVar1 != 0)) {
    return 1;
  }
  return 0;
}


// 0003849c FUN_0003849c

undefined1 * FUN_0003849c(undefined1 *param_1)

{
  FUN_0003fa68();
  *param_1 = 0x20;
  param_1[1] = 0x14;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  param_1[2] = 4;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0x84) = 1;
  *(undefined4 *)(param_1 + 0x8c) = 0x10;
  *(undefined4 *)(param_1 + 0x90) = 0xf;
  *(undefined4 *)(param_1 + 0x94) = 0x17;
  *(undefined4 *)(param_1 + 0x98) = 0x16;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 2;
  return param_1;
}


// 00038544 FUN_00038544

void FUN_00038544(undefined1 *param_1)

{
  int *piVar1;
  
  *param_1 = 0x20;
  param_1[1] = 0x14;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_00035e78(param_1 + 0x80);
  piVar1 = *(int **)(param_1 + 0x9c);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(piVar1,1);
  }
  *(undefined4 *)(param_1 + 0x60) = 0;
  FUN_0003a1d8();
  if (*(int *)(param_1 + 0x74) != 0) {
    FUN_0003bd4c(*(int *)(param_1 + 0x74),param_1);
  }
  if (*(void **)(param_1 + 100) != (void *)0x0) {
    free(*(void **)(param_1 + 100));
  }
  FUN_00030500(param_1);
  return;
}


// 000385a8 FUN_000385a8

void FUN_000385a8(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined1 auStack_34 [16];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  local_20 = param_1[0x12];
  local_1c = param_1[0x14];
  local_18 = param_1[0x13];
  local_14 = param_1[0x15];
  iVar6 = *param_1;
  piVar2 = &local_20;
  iVar3 = 0x10;
  puVar5 = auStack_34;
  local_24 = param_4;
  do {
    iVar4 = iVar3 + -1;
    *puVar5 = (char)*piVar2;
    bVar1 = 0 < iVar3;
    piVar2 = (int *)((int)piVar2 + 1);
    iVar3 = iVar4;
    puVar5 = puVar5 + 1;
  } while (iVar4 != 0 && bVar1);
  (**(code **)(iVar6 + 0xd8))(param_1,param_2,0,param_3);
  return;
}


// 0003871c FUN_0003871c

void FUN_0003871c(int *param_1,uint param_2,int param_3,uint param_4,int param_5)

{
  BOOL BVar1;
  undefined1 local_c;
  undefined1 uStack_b;
  undefined1 uStack_a;
  undefined1 uStack_9;
  undefined1 local_8;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 uStack_5;
  undefined1 local_4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  undefined1 uStack_1;
  
  BVar1 = IsWindow((HWND)param_1[7]);
  if (BVar1 == 0) {
    local_c = (undefined1)param_2;
    *(undefined1 *)(param_1 + 0x25) = local_c;
    uStack_b = (undefined1)(param_2 >> 8);
    *(undefined1 *)((int)param_1 + 0x95) = uStack_b;
    uStack_a = (undefined1)(param_2 >> 0x10);
    *(undefined1 *)((int)param_1 + 0x96) = uStack_a;
    uStack_9 = (undefined1)(param_2 >> 0x18);
    *(undefined1 *)((int)param_1 + 0x97) = uStack_9;
    local_8 = (undefined1)param_3;
    *(undefined1 *)(param_1 + 0x26) = local_8;
    uStack_7 = (undefined1)((uint)param_3 >> 8);
    *(undefined1 *)((int)param_1 + 0x99) = uStack_7;
    uStack_6 = (undefined1)((uint)param_3 >> 0x10);
    *(undefined1 *)((int)param_1 + 0x9a) = uStack_6;
    uStack_5 = (undefined1)((uint)param_3 >> 0x18);
    *(undefined1 *)((int)param_1 + 0x9b) = uStack_5;
    local_4 = (undefined1)param_4;
    *(undefined1 *)(param_1 + 0x23) = local_4;
    uStack_3 = (undefined1)(param_4 >> 8);
    *(undefined1 *)((int)param_1 + 0x8d) = uStack_3;
    uStack_2 = (undefined1)(param_4 >> 0x10);
    *(undefined1 *)((int)param_1 + 0x8e) = uStack_2;
    uStack_1 = (undefined1)(param_4 >> 0x18);
    *(undefined1 *)((int)param_1 + 0x8f) = uStack_1;
    *(undefined1 *)(param_1 + 0x24) = (undefined1)param_5;
    *(undefined1 *)((int)param_1 + 0x91) = param_5._1_1_;
    *(undefined1 *)((int)param_1 + 0x92) = param_5._2_1_;
    *(undefined1 *)((int)param_1 + 0x93) = param_5._3_1_;
  }
  else {
    SendMessageW((HWND)param_1[7],0x420,0,param_5 << 0x10 | param_4 & 0xffff);
    SendMessageW((HWND)param_1[7],0x41f,0,param_3 << 0x10 | param_2 & 0xffff);
    if (param_1[9] != 0) {
      (**(code **)(*param_1 + 0x98))(param_1,0x425,param_1[9],0);
    }
    (**(code **)(*param_1 + 0x98))(param_1,0x41e,0x14,0);
    InvalidateRect((HWND)param_1[7],(RECT *)0x0,1);
  }
  return;
}


// 00038888 FUN_00038888

undefined4 FUN_00038888(undefined4 param_1,LPCWSTR param_2)

{
  int iVar1;
  HRSRC hResInfo;
  HGLOBAL pvVar2;
  undefined4 uVar3;
  uint *_Memory;
  HGLOBAL pvVar4;
  uint uVar5;
  uint *puVar6;
  HMODULE hModule;
  undefined1 local_20;
  
  iVar1 = FUN_0003f4f4();
  hModule = *(HMODULE *)(iVar1 + 0xc);
  hResInfo = FindResourceW(hModule,param_2,(LPCWSTR)0xf1);
  if ((hResInfo == (HRSRC)0x0) || (pvVar2 = LoadResource(hModule,hResInfo), pvVar2 == (HGLOBAL)0x0))
  {
    uVar3 = 0;
  }
  else {
    _Memory = (uint *)operator_new((uint)*(ushort *)((int)pvVar2 + 6) << 2);
    iVar1 = 0;
    pvVar4 = pvVar2;
    puVar6 = _Memory;
    if (*(short *)((int)pvVar2 + 6) != 0) {
      do {
        iVar1 = iVar1 + 1;
        *puVar6 = (uint)*(ushort *)((int)pvVar4 + 8);
        pvVar4 = (HGLOBAL)((int)pvVar4 + 2);
        puVar6 = puVar6 + 1;
      } while (iVar1 < (int)(uint)*(ushort *)((int)pvVar2 + 6));
    }
    iVar1 = FUN_00038b78(param_1,_Memory,*(undefined2 *)((int)pvVar2 + 6));
    free(_Memory);
    uVar3 = 0;
    if (iVar1 != 0) {
      uVar5 = (uint)*(ushort *)((int)pvVar2 + 2);
      local_20 = (undefined1)*(ushort *)((int)pvVar2 + 4);
      FUN_0003871c(param_1,uVar5 + 7,*(ushort *)((int)pvVar2 + 4) + 7,uVar5,local_20,uVar5);
      uVar3 = FUN_000389a4(param_1,param_2);
    }
  }
  return uVar3;
}


// 000389a4 FUN_000389a4

undefined4 FUN_000389a4(int *param_1,LPCWSTR param_2)

{
  int iVar1;
  HRSRC pHVar2;
  HBITMAP hbmImage;
  HIMAGELIST himl;
  HMODULE hModule;
  
  iVar1 = FUN_0003f4f4();
  hModule = *(HMODULE *)(iVar1 + 0xc);
  pHVar2 = FindResourceW(hModule,param_2,(LPCWSTR)0x2);
  if (pHVar2 != (HRSRC)0x0) {
    hbmImage = LoadBitmapW(hModule,param_2);
    himl = (HIMAGELIST)(**(code **)(*param_1 + 0x98))(param_1,0x431,0,0);
    if (((param_1[0x22] == 0) || (himl == (HIMAGELIST)0x0)) || (*(int *)(param_1[0x22] + 200) == 0))
    {
      iVar1 = FUN_00038a78(param_1,hbmImage);
      if (iVar1 != 0) {
        if (param_1[0x22] != 0) {
          *(undefined4 *)(param_1[0x22] + 200) = 1;
        }
        goto LAB_00038a68;
      }
    }
    else {
      iVar1 = ImageList_Add(himl,hbmImage,(HBITMAP)0x0);
      if (-1 < iVar1) {
LAB_00038a68:
        param_1[0x1f] = (int)hModule;
        param_1[0x1e] = (int)pHVar2;
        return 1;
      }
    }
  }
  return 0;
}


// 00038a78 FUN_00038a78

int FUN_00038a78(int *param_1,HANDLE param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_54;
  HANDLE local_50;
  undefined4 local_4c;
  int local_48;
  undefined4 local_44;
  HANDLE local_40;
  undefined4 local_3c;
  undefined1 auStack_34 [4];
  undefined4 local_30;
  
  GetObjectW(param_2,0x18,auStack_34);
  if (param_1[0x20] == 0) {
    iVar2 = *param_1;
    local_54 = 0;
    local_50 = param_2;
    uVar1 = __rt_sdiv(param_1[0x23],local_30);
    (**(code **)(iVar2 + 0x98))(param_1,0x413,uVar1,&local_54);
    iVar2 = 1;
  }
  else {
    local_4c = 0;
    local_44 = 0;
    local_48 = param_1[0x20];
    local_40 = param_2;
    local_3c = __rt_sdiv(param_1[0x23],local_30);
    iVar2 = (**(code **)(*param_1 + 0x98))(param_1,0x42e,0,&local_4c);
    if (iVar2 == 0) {
      return 0;
    }
  }
  FUN_00035e78(param_1 + 0x20);
  param_1[0x20] = (int)param_2;
  return iVar2;
}


// 00038b78 FUN_00038b78

undefined4 FUN_00038b78(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  HIMAGELIST himl;
  int iVar2;
  int iVar3;
  int local_34;
  int local_30;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined4 local_24;
  
  iVar1 = (**(code **)(*param_1 + 0x98))(param_1,0x418,0,0);
  iVar3 = 0;
  if (param_1[0x22] == 0) {
    for (; iVar1 != 0; iVar1 = iVar1 + -1) {
      (**(code **)(*param_1 + 0x98))(param_1,0x416,0,0);
    }
  }
  else {
    himl = (HIMAGELIST)(**(code **)(*param_1 + 0x98))(param_1,0x431,0,0);
    if (himl != (HIMAGELIST)0x0) {
      iVar3 = ImageList_GetImageCount(himl);
    }
  }
  memset(&local_34,0,0x14);
  local_24 = 0xffffffff;
  iVar1 = 0;
  if (param_2 == (int *)0x0) {
    local_2c = 4;
    if (0 < param_3) {
      do {
        iVar3 = (**(code **)(*param_1 + 0x98))(param_1,0x414,1,&local_34);
        if (iVar3 == 0) {
          return 0;
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < param_3);
    }
  }
  else if (0 < param_3) {
    do {
      local_30 = *param_2;
      local_2c = 4;
      local_2b = local_30 == 0;
      local_34 = iVar3;
      if ((bool)local_2b) {
        local_34 = 6;
      }
      param_2 = param_2 + 1;
      if (!(bool)local_2b) {
        iVar3 = iVar3 + 1;
      }
      iVar2 = (**(code **)(*param_1 + 0x98))(param_1,0x414,1,&local_34);
      if (iVar2 == 0) {
        return 0;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_3);
  }
  iVar1 = (**(code **)(*param_1 + 0x98))(param_1,0x418,0,0);
  param_1[0x21] = 1;
  param_1[0x18] = iVar1;
  return 1;
}


// 00038d58 FUN_00038d58

void FUN_00038d58(int *param_1,undefined4 param_2,int param_3)

{
  (**(code **)(*param_1 + 0x98))(param_1,0x417,param_2,param_3);
  *(byte *)(param_3 + 8) = *(byte *)(param_3 + 8) ^ 4;
  return;
}


// 00038d90 FUN_00038d90

void FUN_00038d90(int *param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  RECT *lpRect;
  RECT RStack_3c;
  int local_2c [2];
  byte local_23;
  undefined1 local_22;
  undefined1 local_21;
  
  lpRect = &RStack_3c;
  (**(code **)(*param_1 + 0x98))(param_1,0x417,param_2,local_2c);
  local_22 = 0;
  local_21 = 0;
  *(undefined1 *)((int)param_3 + 10) = 0;
  *(undefined1 *)((int)param_3 + 0xb) = 0;
  *(byte *)(param_3 + 2) = *(byte *)(param_3 + 2) ^ 4;
  iVar1 = memcmp(param_3,local_2c,0x14);
  if (iVar1 != 0) {
    uVar2 = FUN_00033b14(param_1);
    FUN_00033b84(param_1,0x10000000,0,0);
    if (param_1[0x22] == 0) {
      (**(code **)(*param_1 + 0x98))(param_1,0x416,param_2,0);
      (**(code **)(*param_1 + 0x98))(param_1,0x415,param_2,param_3);
    }
    else {
      SendMessageW(*(HWND *)(param_1[0x22] + 0x1c),0x401,param_3[1],*(byte *)(param_3 + 2) & 4);
    }
    FUN_00033b84(param_1,0,uVar2 & 0x10000000,0);
    if ((((*(byte *)((int)param_3 + 9) ^ local_23) & 1) == 0) &&
       (((*(byte *)((int)param_3 + 9) & 1) == 0 || (*param_3 == local_2c[0])))) {
      iVar1 = (**(code **)(*param_1 + 0x98))(param_1,0x41d,param_2,&RStack_3c);
      if (iVar1 == 0) {
        return;
      }
    }
    else {
      lpRect = (RECT *)0x0;
    }
    InvalidateRect((HWND)param_1[7],lpRect,1);
  }
  return;
}


// 00038f20 FUN_00038f20

void FUN_00038f20(int *param_1,undefined4 param_2,LPRECT param_3)

{
  int iVar1;
  
  if (param_1[0x21] != 0) {
    FUN_00038f70();
  }
  iVar1 = (**(code **)(*param_1 + 0x98))(param_1,0x41d,param_2,param_3);
  if (iVar1 == 0) {
    SetRectEmpty(param_3);
  }
  return;
}


// 00038f70 FUN_00038f70

void FUN_00038f70(int *param_1)

{
  uint uVar1;
  undefined1 auStack_10 [8];
  
  uVar1 = param_1[0x1b];
  param_1[0x21] = 0;
  if (((uVar1 & 1) == 0) || ((uVar1 & 4) == 0)) {
    if ((uVar1 & 0xa000) == 0) {
      (**(code **)(*param_1 + 0xb4))(param_1,auStack_10,0,0x50);
    }
    else {
      (**(code **)(*param_1 + 0xb4))(param_1,auStack_10,0,0x4a);
    }
  }
  else {
    (**(code **)(*param_1 + 0xb4))(param_1,auStack_10,0,0x46);
  }
  return;
}


// 00039000 FUN_00039000

uint FUN_00039000(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_18 [8];
  byte local_10;
  byte local_f;
  
  FUN_00038d58(param_1,param_2,auStack_18);
  return (uint)local_f | (uint)local_10 << 0x10;
}


// 00039024 FUN_00039024

void FUN_00039024(int param_1,undefined4 param_2,uint param_3)

{
  undefined1 auStack_24 [8];
  byte local_1c;
  byte local_1b;
  
  FUN_00038d58(param_1,param_2,auStack_24);
  if (((uint)local_1b != (param_3 & 0xff)) || ((uint)local_1c != (param_3 >> 0x10 & 0xff))) {
    local_1b = (byte)param_3;
    local_1c = (byte)(param_3 >> 0x10);
    FUN_00038d90(param_1,param_2,auStack_24);
    *(undefined4 *)(param_1 + 0x84) = 1;
  }
  return;
}


// 00039090 FUN_00039090

void FUN_00039090(int param_1,undefined1 *param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  int local_3c;
  undefined4 local_34;
  undefined4 local_30;
  
  iVar7 = 0;
  iVar4 = 0;
  local_34 = 0;
  iVar3 = 0;
  local_30 = 0;
  iVar2 = 0;
  local_3c = param_4;
  if (0 < param_4) {
    do {
      iVar6 = *param_3;
      if ((*(byte *)(param_3 + 2) & 8) == 0) {
        iVar5 = *(int *)(param_1 + 0x94);
        if ((*(byte *)((int)param_3 + 9) & 1) == 0) {
          iVar1 = iVar5 + iVar3;
          if (iVar7 < iVar1) {
            iVar7 = iVar1;
          }
LAB_00039144:
          iVar1 = *(int *)(param_1 + 0x98) + iVar2;
          if (iVar4 < iVar1) {
            iVar4 = iVar1;
          }
        }
        else {
          if ((*(byte *)(param_3 + 2) & 0x20) == 0) {
            if (iVar7 < iVar6 + iVar3) {
              iVar7 = iVar6 + iVar3;
            }
          }
          else {
            iVar1 = *(int *)(param_1 + 0x98) + iVar2 + iVar6;
            if (iVar4 < iVar1) {
              iVar4 = iVar1;
            }
          }
          iVar1 = FUN_00038468(param_3);
          if (iVar1 != 0) goto LAB_00039144;
        }
        bVar8 = (*(byte *)((int)param_3 + 9) & 1) != 0;
        if (bVar8) {
          iVar3 = *param_3 + iVar3;
        }
        if (!bVar8) {
          iVar3 = iVar5 + iVar3;
        }
        bVar8 = (*(byte *)(param_3 + 2) & 0x20) != 0;
        if (bVar8) {
          iVar3 = 0;
          iVar2 = *(int *)(param_1 + 0x98) + iVar2;
        }
        if (bVar8 && (*(byte *)((int)param_3 + 9) & 1) != 0) {
          iVar2 = iVar2 + iVar6;
        }
      }
      param_3 = param_3 + 5;
      local_3c = local_3c + -1;
      local_34 = iVar7;
      local_30 = iVar4;
    } while (local_3c != 0);
  }
  *param_2 = (undefined1)local_34;
  param_2[1] = local_34._1_1_;
  param_2[2] = local_34._2_1_;
  param_2[3] = local_34._3_1_;
  param_2[4] = (undefined1)local_30;
  param_2[5] = local_30._1_1_;
  param_2[6] = local_30._2_1_;
  param_2[7] = local_30._3_1_;
  return;
}


// 000391f8 FUN_000391f8

int FUN_000391f8(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 0;
  iVar3 = 0;
  iVar6 = 0;
  if (param_3 < 1) {
LAB_00039314:
    return iVar7 + 1;
  }
LAB_00039214:
  piVar4 = (int *)(iVar6 * 0x14 + param_2);
  bVar1 = *(byte *)(piVar4 + 2);
  *(byte *)(piVar4 + 2) = bVar1 & 0xdf;
  if ((bVar1 & 8) == 0) {
    if ((*(byte *)((int)piVar4 + 9) & 1) == 0) {
      iVar2 = *(int *)(param_1 + 0x94);
    }
    else {
      iVar2 = *piVar4;
    }
    iVar3 = iVar2 + iVar3;
    iVar2 = iVar6;
    if (param_4 < iVar3) {
      for (; (-1 < iVar2 && ((*(byte *)(piVar4 + 2) & 0x20) == 0)); piVar4 = piVar4 + -5) {
        if (((*(byte *)((int)piVar4 + 9) & 1) != 0) &&
           ((piVar4[1] == 0 && ((*(byte *)(piVar4 + 2) & 8) == 0)))) goto LAB_000392e8;
        iVar2 = iVar2 + -1;
      }
      iVar2 = iVar6 + -1;
      if (-1 < iVar2) {
        iVar5 = iVar2 * 0x14 + param_2;
        do {
          if ((*(byte *)(iVar5 + 8) & 0x20) != 0) break;
          if (((*(byte *)(iVar5 + 8) & 8) == 0) &&
             (((*(byte *)(iVar5 + 9) & 1) == 0 || (*(int *)(iVar5 + 4) == 0)))) goto LAB_000392e8;
          iVar2 = iVar2 + -1;
          iVar5 = iVar5 + -0x14;
        } while (-1 < iVar2);
      }
    }
  }
  goto LAB_00039308;
LAB_000392e8:
  iVar6 = iVar2 * 0x14 + param_2;
  iVar3 = 0;
  iVar7 = iVar7 + 1;
  *(byte *)(iVar6 + 8) = *(byte *)(iVar6 + 8) | 0x20;
  iVar6 = iVar2;
LAB_00039308:
  iVar6 = iVar6 + 1;
  if (param_3 <= iVar6) goto LAB_00039314;
  goto LAB_00039214;
}


// 0003931c FUN_0003931c

void FUN_0003931c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  bool bVar6;
  int local_44;
  int local_40;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  int local_2c;
  undefined1 auStack_28 [8];
  
  if (param_5 == 0) {
    iVar1 = FUN_000391f8();
    iVar5 = 0;
    iVar2 = FUN_000391f8(param_1,param_2,param_3,0);
    if ((iVar2 != iVar1) && (0 < param_4)) {
      do {
        iVar2 = iVar5 + param_4;
        if (iVar2 < 0) {
          iVar2 = iVar2 + 1;
        }
        iVar2 = iVar2 >> 1;
        iVar3 = FUN_000391f8(param_1,param_2,param_3,iVar2);
        if ((iVar3 != iVar1) && (bVar6 = iVar5 == iVar2, iVar5 = iVar2, iVar2 = param_4, bVar6)) {
          FUN_000391f8(param_1,param_2,param_3,param_4);
          break;
        }
        param_4 = iVar2;
      } while (iVar5 < param_4);
    }
    piVar4 = (int *)FUN_00039090(param_1,&local_30,param_2,param_3);
    local_40 = *piVar4;
LAB_00039690:
    FUN_000391f8(param_1,param_2,param_3,local_40);
  }
  else {
    FUN_000391f8();
    piVar4 = (int *)FUN_00039090(param_1,&local_30,param_2,param_3);
    iVar5 = *piVar4;
    local_44 = piVar4[1];
    FUN_000391f8(param_1,param_2,param_3,0x7fff);
    piVar4 = (int *)FUN_00039090(param_1,&local_30,param_2,param_3);
    local_40 = *piVar4;
    while (iVar5 < local_40) {
      iVar1 = iVar5 + local_40;
      if (iVar1 < 0) {
        iVar1 = iVar1 + 1;
      }
      FUN_000391f8(param_1,param_2,param_3,iVar1 >> 1);
      piVar4 = (int *)FUN_00039090(param_1,auStack_28,param_2,param_3);
      local_30 = (undefined1)*piVar4;
      local_2f = *(undefined1 *)((int)piVar4 + 1);
      local_2e = *(undefined1 *)((int)piVar4 + 2);
      local_2d = *(undefined1 *)((int)piVar4 + 3);
      local_2c = piVar4[1];
      if (param_4 < local_2c) {
        if ((iVar5 == *piVar4) && (local_44 == piVar4[1])) goto LAB_00039690;
        iVar5 = *piVar4;
        local_44 = piVar4[1];
      }
      else {
        if (param_4 <= local_2c) {
          return;
        }
        local_40 = *piVar4;
      }
    }
  }
  return;
}


// 000396a8 FUN_000396a8

void FUN_000396a8(int *param_1,undefined1 *param_2,uint param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  tagRECT *ptVar5;
  undefined4 uVar6;
  int *piVar7;
  int iVar8;
  int *piVar9;
  void *pvVar10;
  int iVar11;
  int iVar12;
  void *_Memory;
  bool bVar13;
  uint local_70 [2];
  tagRECT local_68;
  undefined4 local_58;
  undefined4 local_54;
  tagRECT local_50;
  tagRECT local_40;
  
  iVar12 = 0;
  local_58 = 0;
  _Memory = (void *)0x0;
  local_54 = 0;
  iVar1 = (**(code **)(*param_1 + 0x98))(param_1,0x418,0,0);
  if (iVar1 != 0) {
    _Memory = (void *)operator_new(iVar1 * 0x14);
    iVar8 = 0;
    pvVar10 = _Memory;
    if (iVar1 < 1) goto LAB_00039b24;
    do {
      FUN_00038d58(param_1,iVar8,pvVar10);
      iVar8 = iVar8 + 1;
      pvVar10 = (void *)((int)pvVar10 + 0x14);
    } while (iVar8 < iVar1);
  }
  if (iVar1 < 1) goto LAB_00039b24;
  uVar2 = param_1[0x1b];
  if ((uVar2 & 2) == 0) {
    local_70[0] = uVar2 & 4;
    if (local_70[0] == 0) {
LAB_00039858:
      if ((param_3 & 2) == 0) {
        uVar6 = 0;
      }
      else {
        uVar6 = 0x7fff;
      }
      FUN_0003931c(param_1,_Memory,iVar1,uVar6,0);
    }
    else if ((param_3 & 4) == 0) {
      if ((param_3 & 8) == 0) {
        if ((param_3 & 0x10) == 0) {
          if (param_4 == -1) {
            if ((uVar2 & 1) == 0) goto LAB_00039858;
            FUN_0003931c(param_1,_Memory,iVar1,param_1[0x17],0);
          }
          else {
            SetRectEmpty(&local_68);
            FUN_0003a9bc(param_1,&local_68,param_3 & 2);
            if ((param_3 & 0x20) == 0) {
              iVar8 = local_68.right - local_68.left;
            }
            else {
              iVar8 = local_68.bottom - local_68.top;
            }
            FUN_0003931c(param_1,_Memory,iVar1,iVar8 + param_4,param_3 & 0x20);
          }
        }
        else {
          FUN_0003931c(param_1,_Memory,iVar1,0,0);
        }
      }
      else {
        FUN_0003931c(param_1,_Memory,iVar1,0x7fff,0);
      }
    }
    else {
      FUN_0003931c(param_1,_Memory,iVar1,param_1[0x17],0);
    }
  }
  piVar3 = (int *)FUN_00039090(param_1,&local_68,_Memory,iVar1);
  local_58 = *piVar3;
  local_54 = piVar3[1];
  if ((param_3 & 0x40) != 0) {
    local_70[0] = param_1[0x21];
    piVar3 = (int *)0x0;
    param_1[0x21] = 0;
    pvVar10 = _Memory;
    iVar8 = iVar1;
    if (0 < iVar1) {
      do {
        iVar8 = iVar8 + -1;
        uVar2 = *(byte *)((int)pvVar10 + 9) & 1;
        bVar13 = (*(byte *)((int)pvVar10 + 9) & 1) != 0;
        if (bVar13) {
          uVar2 = *(uint *)((int)pvVar10 + 4);
        }
        if (bVar13 && uVar2 != 0) {
          iVar12 = iVar12 + 1;
        }
        pvVar10 = (void *)((int)pvVar10 + 0x14);
      } while (iVar8 != 0);
      if (0 < iVar12) {
        piVar3 = (int *)operator_new(iVar12 * 0x18);
        iVar8 = 0;
        if (piVar3 == (int *)0x0) {
          piVar3 = (int *)0x0;
        }
        else {
          local_68.left = iVar12 + -1;
        }
        iVar12 = 0;
        piVar9 = piVar3;
        pvVar10 = _Memory;
        do {
          if (((*(byte *)((int)pvVar10 + 9) & 1) != 0) && (*(int *)((int)pvVar10 + 4) != 0)) {
            *piVar9 = iVar8;
            piVar9[1] = *(int *)((int)pvVar10 + 4);
            (**(code **)(*param_1 + 0xe0))(param_1,iVar8,&local_40);
            FUN_00036320(param_1,&local_40);
            iVar11 = 0x10;
            ptVar5 = &local_40;
            piVar7 = piVar9 + 2;
            do {
              iVar4 = iVar11 + -1;
              *(char *)piVar7 = (char)ptVar5->left;
              bVar13 = 0 < iVar11;
              iVar11 = iVar4;
              ptVar5 = (tagRECT *)((int)&ptVar5->left + 1);
              piVar7 = (int *)((int)piVar7 + 1);
            } while (iVar4 != 0 && bVar13);
            iVar12 = iVar12 + 1;
            piVar9 = piVar9 + 6;
          }
          iVar8 = iVar8 + 1;
          pvVar10 = (void *)((int)pvVar10 + 0x14);
        } while (iVar8 < iVar1);
      }
    }
    iVar8 = 0;
    if ((param_1[0x1b] & 1U) != 0 && (param_1[0x1b] & 4U) != 0) {
      param_1[0x17] = local_58;
    }
    pvVar10 = _Memory;
    if (0 < iVar1) {
      do {
        FUN_00038d90(param_1,iVar8,pvVar10);
        iVar8 = iVar8 + 1;
        pvVar10 = (void *)((int)pvVar10 + 0x14);
      } while (iVar8 < iVar1);
    }
    piVar9 = piVar3;
    if (0 < iVar12) {
      do {
        iVar1 = FUN_00033a44(param_1,piVar9[1]);
        if (iVar1 != 0) {
          GetWindowRect(*(HWND *)(iVar1 + 0x1c),&local_50);
          local_68.left = piVar9[2];
          local_68.top = piVar9[3];
          iVar8 = local_50.left - local_68.left;
          iVar11 = local_50.top - local_68.top;
          (**(code **)(*param_1 + 0xe0))(param_1,*piVar9,&local_50);
          FUN_00033cec(iVar1,0,iVar8 + local_50.left,local_50.top + iVar11,0,0,0x15);
        }
        iVar12 = iVar12 + -1;
        piVar9 = piVar9 + 6;
      } while (iVar12 != 0);
      free(piVar3);
    }
    param_1[0x21] = local_70[0];
  }
  free(_Memory);
LAB_00039b24:
  SetRectEmpty(&local_40);
  FUN_0003a9bc(param_1,&local_40,param_3 & 2);
  iVar12 = (local_40.top - local_40.bottom) + local_54;
  iVar1 = (local_40.left - local_40.right) + local_58;
  local_58 = iVar1;
  local_54 = iVar12;
  piVar3 = (int *)FUN_0003a030(param_1,local_70,param_3 & 1,param_3 & 2);
  if (iVar1 <= *piVar3) {
    local_58 = *piVar3;
  }
  if (iVar12 <= piVar3[1]) {
    local_54 = piVar3[1];
  }
  *param_2 = (undefined1)local_58;
  param_2[1] = local_58._1_1_;
  param_2[2] = local_58._2_1_;
  param_2[3] = local_58._3_1_;
  param_2[4] = (undefined1)local_54;
  param_2[5] = local_54._1_1_;
  param_2[6] = local_54._2_1_;
  param_2[7] = local_54._3_1_;
  return;
}


// 00039c34 FUN_00039c34

undefined1 * FUN_00039c34(undefined4 param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  byte bVar2;
  undefined1 auStack_10 [8];
  
  bVar2 = 2;
  if (param_4 == 0) {
    bVar2 = 0;
  }
  puVar1 = (undefined1 *)FUN_000396a8(param_1,auStack_10,bVar2 | param_3 != 0,0xffffffff);
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  param_2[3] = puVar1[3];
  param_2[4] = puVar1[4];
  param_2[5] = puVar1[5];
  param_2[6] = puVar1[6];
  param_2[7] = puVar1[7];
  return param_2;
}


// 00039cb8 FUN_00039cb8

undefined1 * FUN_00039cb8(int *param_1,undefined1 *param_2,int param_3,uint param_4)

{
  undefined1 *puVar1;
  undefined1 auStack_14 [8];
  
  if ((((param_3 == -1) && ((param_4 & 4) == 0)) && ((param_4 & 0x40) == 0)) &&
     (((param_4 & 8) != 0 || ((param_4 & 0x10) != 0)))) {
    puVar1 = (undefined1 *)(**(code **)(*param_1 + 0xb0))(param_1,auStack_14,param_4 & 1);
  }
  else {
    puVar1 = (undefined1 *)FUN_000396a8(param_1,auStack_14,param_4,param_3);
  }
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  param_2[3] = puVar1[3];
  param_2[4] = puVar1[4];
  param_2[5] = puVar1[5];
  param_2[6] = puVar1[6];
  param_2[7] = puVar1[7];
  return param_2;
}


// 00039d80 FUN_00039d80

void FUN_00039d80(int param_1,uint param_2,uint param_3)

{
  if ((*(int *)(param_1 + 0x1c) != 0) && (((param_2 ^ param_3) & 0xf00) != 0)) {
    FUN_00033cec(param_1,0,0,0,0,0,0x33);
  }
  *(undefined4 *)(param_1 + 0x84) = 1;
  return;
}


// 00039ddc FUN_00039ddc

void FUN_00039ddc(int param_1)

{
  if (*(int *)(param_1 + 0x84) != 0) {
    FUN_00038f70();
  }
  FUN_0002ff50(param_1);
  return;
}


// 00039dfc FUN_00039dfc

void FUN_00039dfc(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x18) = 1;
  uVar1 = FUN_00039000(uVar3,*(undefined4 *)(param_1 + 8));
  uVar2 = uVar1 & 0xfffbffff;
  if (param_2 == 0) {
    uVar2 = uVar1 & 0xfff9ffff | 0x40000;
  }
  FUN_00039024(uVar3,*(undefined4 *)(param_1 + 8),uVar2);
  return;
}


// 00039e40 FUN_00039e40

void FUN_00039e40(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = *(undefined4 *)(param_1 + 0x14);
  uVar1 = FUN_00039000(uVar2,*(undefined4 *)(param_1 + 8));
  uVar1 = uVar1 & 0xffeeffff;
  if (param_2 == 1) {
    uVar1 = uVar1 | 0x10000;
  }
  else if (param_2 == 2) {
    uVar1 = uVar1 | 0x100000;
  }
  FUN_00039024(uVar2,*(undefined4 *)(param_1 + 8),uVar1 | 2);
  return;
}


// 00039e8c FUN_00039e8c

void FUN_00039e8c(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 auStack_58 [4];
  int local_54;
  byte local_4f;
  undefined **local_40;
  int local_3c;
  uint local_38;
  int *local_2c;
  uint local_20;
  
  FUN_0002f584(&local_40);
  local_40 = &PTR_FUN_00041508;
  local_2c = param_1;
  local_20 = (**(code **)(*param_1 + 0x98))(param_1,0x418,0,0);
  local_38 = 0;
  if (local_20 != 0) {
    do {
      FUN_00038d58(param_1,local_38,auStack_58);
      local_3c = local_54;
      if ((local_4f & 1) == 0) {
        iVar1 = FUN_0002f3c4(param_1,0,0xbd11ffff,&local_40,0);
        if (iVar1 == 0) {
          iVar1 = FUN_0002f3c4(param_1,local_3c,0xffffffff,&local_40,0);
          if ((iVar1 == 0) &&
             ((param_1[0x22] == 0 ||
              ((((local_54 != 0x53 && (local_54 != 0x10)) && ((local_4f & 8) == 0)) &&
               ((local_54 != 10 && (local_54 != 0xb)))))))) {
            FUN_0002f79c(&local_40,param_2,param_3);
          }
        }
      }
      local_38 = local_38 + 1;
    } while (local_38 < local_20);
  }
  FUN_00032ee4(param_1,param_2,param_3);
  return;
}


// 0003a008 FUN_0003a008

void FUN_0003a008(int *param_1)

{
  if (param_1[0x11] != 0 && param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 4))(param_1,1);
  }
  return;
}


// 0003a030 FUN_0003a030

void FUN_0003a030(undefined4 param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined2 local_10;
  undefined2 local_c;
  
  if ((param_3 == 0) || (local_10 = 0x7fff, param_4 == 0)) {
    local_10 = 0;
  }
  if ((param_3 == 0) || (local_c = 0x7fff, param_4 != 0)) {
    local_c = 0;
  }
  *param_2 = (undefined1)local_10;
  param_2[1] = local_10._1_1_;
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[4] = (undefined1)local_c;
  param_2[5] = local_c._1_1_;
  param_2[6] = 0;
  param_2[7] = 0;
  return;
}


// 0003a0c8 FUN_0003a0c8

undefined1 * FUN_0003a0c8(int *param_1,undefined1 *param_2,undefined4 param_3,uint param_4)

{
  undefined1 *puVar1;
  undefined1 auStack_14 [8];
  
  puVar1 = (undefined1 *)(**(code **)(*param_1 + 0xb0))(param_1,auStack_14,param_4 & 1,param_4 & 2);
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  param_2[2] = puVar1[2];
  param_2[3] = puVar1[3];
  param_2[4] = puVar1[4];
  param_2[5] = puVar1[5];
  param_2[6] = puVar1[6];
  param_2[7] = puVar1[7];
  return param_2;
}


// 0003a14c FUN_0003a14c

undefined4 FUN_0003a14c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  
  iVar1 = FUN_0002ff50();
  if (iVar1 == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    GetParent(*(HWND *)(param_1 + 0x1c));
    piVar3 = (int *)FUN_0002ffec();
    iVar1 = (**(code **)(*piVar3 + 0xa8))();
    if (iVar1 != 0) {
      *(int **)(param_1 + 0x74) = piVar3;
      FUN_0002dac8(piVar3 + 0x1f,param_1);
    }
    uVar2 = 0;
  }
  return uVar2;
}


// 0003a1a4 FUN_0003a1a4

void FUN_0003a1a4(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  FUN_0003f170();
  uVar2 = extraout_r2;
  if (*(int *)(param_1 + 0x74) != 0) {
    FUN_0003bd4c(*(int *)(param_1 + 0x74),param_1);
    *(undefined4 *)(param_1 + 0x74) = 0;
    uVar2 = extraout_r2_00;
  }
  piVar1 = *(int **)(param_1 + 0x38);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(piVar1,1,uVar2,*(code **)(*piVar1 + 4),unaff_r4,unaff_lr);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_000336d0(param_1,0);
  }
  FUN_0002ff50(param_1);
  return;
}


// 0003a1d8 FUN_0003a1d8

void FUN_0003a1d8(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if ((*(int *)(param_1 + 0x1c) == 0) || (iVar1 = FUN_0003ce54(), iVar1 == 0)) {
    FUN_00030748(param_1);
  }
  else {
    piVar2 = (int *)FUN_0003ce3c(param_1);
    (**(code **)(*piVar2 + 0x54))();
  }
  return;
}


// 0003a220 FUN_0003a220

void FUN_0003a220(int *param_1)

{
  int iVar1;
  undefined1 auStack_60 [88];
  
  FUN_00036360(auStack_60,param_1);
  iVar1 = (**(code **)(*param_1 + 0xc0))(param_1);
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0xd0))(param_1,auStack_60);
  }
  FUN_000363e4(auStack_60);
  return;
}


// 0003a278 FUN_0003a278

undefined4 FUN_0003a278(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_18;
  
  iVar1 = FUN_00032444(param_3,&local_18);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (param_3 != 0) {
      uVar2 = *(undefined4 *)(param_3 + 0x1c);
    }
    iVar1 = FUN_000329ac(*(undefined4 *)(param_2 + 4),uVar2,param_4,DAT_002de504,DAT_002de514);
    local_18 = DAT_002de504;
    if (iVar1 == 0) {
      local_18 = FUN_0002ff50(param_1);
    }
  }
  return local_18;
}


// 0003a2f4 FUN_0003a2f4

undefined4 FUN_0003a2f4(int *param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  
  uVar1 = FUN_00033b14();
  uVar2 = param_1[0x1a];
  uVar5 = 0;
  if ((uVar2 & 1) == 0 || (uVar1 & 0x10000000) == 0) {
    if (((uVar2 & 2) != 0) && ((uVar1 & 0x10000000) == 0)) {
      uVar5 = 0x40;
    }
  }
  else {
    uVar5 = 0x80;
  }
  param_1[0x1a] = uVar2 & 0xfffffffc;
  if (uVar5 != 0) {
    FUN_00033cec(param_1,0,0,0,0,0,uVar5 | 0x17);
  }
  uVar1 = FUN_00033b14(param_1);
  if ((uVar1 & 0x10000000) != 0) {
    piVar3 = (int *)FUN_0002ad10(param_1);
    if ((piVar3 == (int *)0x0) || (iVar4 = (**(code **)(*piVar3 + 0xa8))(piVar3), iVar4 == 0)) {
      piVar3 = (int *)FUN_00031a70(param_1);
    }
    if (piVar3 != (int *)0x0) {
      (**(code **)(*param_1 + 0xb8))(param_1,piVar3,param_2);
    }
  }
  return 0;
}


// 0003a3ec FUN_0003a3ec

uint FUN_0003a3ec(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = FUN_00033b14();
  uVar1 = uVar1 & 0x10000000;
  uVar2 = *(uint *)(param_1 + 0x68);
  uVar3 = *(uint *)(param_1 + 0x6c) & 0xff00 | uVar1;
  if ((uVar2 & 3) == 0) {
    return uVar3;
  }
  if ((uVar2 & 1) == 0) {
    if (uVar1 != 0) goto LAB_0003a48c;
    uVar1 = 0x40;
  }
  else {
    if (uVar1 == 0) {
LAB_0003a48c:
      *(uint *)(param_1 + 0x68) = uVar2 & 0xfffffffc;
      return uVar3;
    }
    uVar1 = 0x80;
  }
  if (*param_2 != 0) {
    *(uint *)(param_1 + 0x68) = uVar2 & 0xfffffffc;
    SetWindowPos(*(HWND *)(param_1 + 0x1c),(HWND)0x0,0,0,0,0,uVar1 | 0x17);
    *param_2 = 1;
  }
  return uVar3 ^ 0x10000000;
}


// 0003a4a0 FUN_0003a4a0

undefined4 FUN_0003a4a0(int *param_1,undefined4 param_2,int *param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  undefined1 auStack_34 [8];
  tagRECT local_2c;
  
  uVar1 = (**(code **)(*param_1 + 0xc4))(param_1,param_3);
  if (((uVar1 & 0x10000000) != 0) && ((uVar1 & 0xf000) != 0)) {
    CopyRect(&local_2c,(RECT *)(param_3 + 1));
    iVar5 = local_2c.right - local_2c.left;
    iVar6 = local_2c.bottom - local_2c.top;
    bVar7 = param_3[7] != 0;
    if ((param_1[0x1b] & 4U) == 0 || (param_1[0x1b] & 1U) == 0) {
      bVar4 = bVar7 | 10;
      if ((uVar1 & 0xa000) == 0) {
        bVar4 = bVar7 | 0x10;
      }
    }
    else {
      bVar4 = bVar7 | 6;
    }
    piVar2 = (int *)(**(code **)(*param_1 + 0xb4))(param_1,auStack_34,0xffffffff,bVar4);
    iVar3 = *piVar2;
    if (iVar5 <= *piVar2) {
      iVar3 = iVar5;
    }
    iVar5 = piVar2[1];
    if (iVar6 <= piVar2[1]) {
      iVar5 = iVar6;
    }
    if ((uVar1 & 0xa000) == 0) {
      if ((uVar1 & 0x5000) != 0) {
        param_3[5] = param_3[5] + iVar3;
        iVar6 = param_3[6];
        if (param_3[6] <= iVar5) {
          iVar6 = iVar5;
        }
        param_3[6] = iVar6;
        if ((uVar1 & 0x1000) == 0) {
          if ((uVar1 & 0x4000) != 0) {
            local_2c.left = local_2c.right - iVar3;
            param_3[3] = param_3[3] - iVar3;
          }
        }
        else {
          param_3[1] = param_3[1] + iVar3;
        }
      }
    }
    else {
      param_3[6] = param_3[6] + iVar5;
      iVar6 = param_3[5];
      if (param_3[5] <= iVar3) {
        iVar6 = iVar3;
      }
      param_3[5] = iVar6;
      if ((uVar1 & 0x2000) == 0) {
        if ((uVar1 & 0x8000) != 0) {
          local_2c.top = local_2c.bottom - iVar5;
          param_3[4] = param_3[4] - iVar5;
        }
      }
      else {
        param_3[2] = param_3[2] + iVar5;
      }
    }
    local_2c.right = iVar3 + local_2c.left;
    local_2c.bottom = local_2c.top + iVar5;
    if (*param_3 != 0) {
      FUN_00032324(param_3,param_1[7],&local_2c);
    }
  }
  return 0;
}


// 0003a690 FUN_0003a690

void FUN_0003a690(int param_1,int param_2)

{
  uint uVar1;
  
  *(uint *)(param_1 + 0x68) = *(uint *)(param_1 + 0x68) & 0xfffffffc;
  if (param_2 == 0) {
    uVar1 = FUN_00033b14();
    if ((uVar1 & 0x10000000) == 0) {
      return;
    }
    uVar1 = *(uint *)(param_1 + 0x68) | 1;
  }
  else {
    uVar1 = FUN_00033b14();
    if ((uVar1 & 0x10000000) != 0) {
      return;
    }
    uVar1 = *(uint *)(param_1 + 0x68) | 2;
  }
  *(uint *)(param_1 + 0x68) = uVar1;
  return;
}


// 0003a6e0 FUN_0003a6e0

undefined4 FUN_0003a6e0(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if ((*(uint *)(param_1 + 0x68) & 1) == 0) {
    if (((*(uint *)(param_1 + 0x68) & 2) == 0) &&
       (uVar2 = FUN_00033b14(param_1), (uVar2 & 0x10000000) == 0)) {
      return 0;
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}


// 0003a714 FUN_0003a714

void FUN_0003a714(int param_1,undefined4 param_2)

{
  tagRECT tStack_1c;
  
  GetClientRect(*(HWND *)(param_1 + 0x1c),&tStack_1c);
  FUN_0003a748(param_1,param_2,&tStack_1c);
  return;
}


// 0003a748 FUN_0003a748

void FUN_0003a748(int param_1,undefined4 param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  undefined1 auStack_44 [8];
  int local_3c;
  int local_38;
  undefined1 auStack_34 [4];
  int local_30;
  int local_28;
  
  uVar11 = *(uint *)(param_1 + 0x6c);
  if ((uVar11 & 0xf00) != 0) {
    iVar3 = 0x10;
    piVar4 = param_3;
    puVar5 = auStack_44;
    do {
      iVar2 = iVar3 + -1;
      *puVar5 = (char)*piVar4;
      bVar1 = 0 < iVar3;
      iVar3 = iVar2;
      piVar4 = (int *)((int)piVar4 + 1);
      puVar5 = puVar5 + 1;
    } while (iVar2 != 0 && bVar1);
    iVar3 = 0x10;
    piVar4 = param_3;
    puVar5 = auStack_34;
    do {
      iVar2 = iVar3 + -1;
      *puVar5 = (char)*piVar4;
      bVar1 = 0 < iVar3;
      iVar3 = iVar2;
      piVar4 = (int *)((int)piVar4 + 1);
      puVar5 = puVar5 + 1;
    } while (iVar2 != 0 && bVar1);
    uVar10 = DAT_002de50c;
    if (DAT_002de53c == 0) {
      uVar10 = DAT_002de518;
    }
    iVar3 = local_3c;
    if ((uVar11 & 0x80) != 0) {
      local_38 = local_38 + -1;
      iVar3 = local_3c + -1;
    }
    uVar6 = uVar11 & 0x200;
    iVar2 = local_30;
    if (uVar6 != 0) {
      iVar2 = DAT_002de4f4 + local_30;
    }
    uVar7 = uVar11 & 0x800;
    iVar12 = local_28;
    if (uVar7 != 0) {
      iVar12 = local_28 - DAT_002de4f4;
    }
    uVar8 = uVar11 & 0x100;
    if (uVar8 != 0) {
      FUN_0003d1bc(param_2,0,iVar2,1,iVar12 - iVar2,uVar10);
    }
    if (uVar6 != 0) {
      FUN_0003d1bc(param_2,0,0,param_3[2],1,uVar10);
    }
    uVar9 = uVar11 & 0x400;
    if (uVar9 != 0) {
      FUN_0003d1bc(param_2,iVar3,iVar2,0xffffffff,iVar12 - iVar2,uVar10);
    }
    if (uVar7 != 0) {
      FUN_0003d1bc(param_2,0,local_38,param_3[2],0xffffffff,uVar10);
    }
    uVar10 = DAT_002de510;
    if ((uVar11 & 0x80) != 0) {
      if (uVar8 != 0) {
        FUN_0003d1bc(param_2,1,iVar2,1,iVar12 - iVar2,DAT_002de510);
      }
      if (uVar6 != 0) {
        FUN_0003d1bc(param_2,0,1,param_3[2],1,uVar10);
      }
      if (uVar9 != 0) {
        FUN_0003d1bc(param_2,param_3[2],iVar2,0xffffffff,iVar12 - iVar2,uVar10);
      }
      if (uVar7 != 0) {
        FUN_0003d1bc(param_2,0,param_3[3],param_3[2],0xffffffff,uVar10);
      }
    }
    if (uVar8 != 0) {
      *param_3 = *param_3 + DAT_002de4f0;
    }
    if (uVar6 != 0) {
      param_3[1] = param_3[1] + DAT_002de4f4;
    }
    if (uVar9 != 0) {
      param_3[2] = param_3[2] - DAT_002de4f0;
    }
    if (uVar7 != 0) {
      param_3[3] = param_3[3] - DAT_002de4f4;
    }
  }
  return;
}


// 0003a9bc FUN_0003a9bc

void FUN_0003a9bc(int param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 0x6c);
  if ((uVar2 & 0x100) != 0) {
    *param_2 = *param_2 + DAT_002de4f0;
  }
  if ((uVar2 & 0x200) != 0) {
    param_2[1] = param_2[1] + DAT_002de4f4;
  }
  if ((uVar2 & 0x400) != 0) {
    param_2[2] = param_2[2] - DAT_002de4f0;
  }
  if ((uVar2 & 0x800) != 0) {
    param_2[3] = param_2[3] - DAT_002de4f4;
  }
  if (param_3 == 0) {
    *param_2 = *(int *)(param_1 + 0x50) + *param_2;
    param_2[1] = *(int *)(param_1 + 0x48) + param_2[1];
    param_2[2] = param_2[2] - *(int *)(param_1 + 0x54);
    iVar1 = *(int *)(param_1 + 0x4c);
  }
  else {
    *param_2 = *(int *)(param_1 + 0x48) + *param_2;
    param_2[1] = *(int *)(param_1 + 0x50) + param_2[1];
    param_2[2] = param_2[2] - *(int *)(param_1 + 0x4c);
    iVar1 = *(int *)(param_1 + 0x54);
  }
  param_2[3] = param_2[3] - iVar1;
  return;
}


// 0003aa9c FUN_0003aa9c

undefined1 * FUN_0003aa9c(undefined1 *param_1)

{
  FUN_0003fa68();
  *param_1 = 0xf0;
  param_1[1] = 0x25;
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x80) = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  return param_1;
}


// 0003ab04 FUN_0003ab04

bool FUN_0003ab04(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003fae4();
  if (iVar1 != 0) {
    *(uint *)(param_1 + 0x6c) = *(uint *)(param_1 + 0x6c) & 0xfffff07f;
  }
  return iVar1 != 0;
}


// 0003ab2c FUN_0003ab2c

void FUN_0003ab2c(undefined1 *param_1)

{
  *param_1 = 0xf0;
  param_1[1] = 0x25;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0003a1d8(param_1);
  FUN_0003a1d8();
  if (*(int *)(param_1 + 0x74) != 0) {
    FUN_0003bd4c(*(int *)(param_1 + 0x74),param_1);
  }
  if (*(void **)(param_1 + 100) != (void *)0x0) {
    free(*(void **)(param_1 + 100));
  }
  FUN_00030500(param_1);
  return;
}


// 0003ab6c FUN_0003ab6c

undefined4 FUN_0003ab6c(int *param_1,int param_2,int param_3,uint param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined1 local_60;
  undefined1 uStack_5f;
  undefined1 uStack_5e;
  undefined1 uStack_5d;
  undefined1 local_5c;
  undefined1 uStack_5b;
  undefined1 uStack_5a;
  undefined1 uStack_59;
  tagRECT local_58;
  undefined1 auStack_48 [4];
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_28;
  wchar_t *local_20;
  
  param_1[0x1b] = param_4 & 0x40ffff;
  memset(auStack_48,0,0x30);
  local_28 = param_4 | 0x40000000;
  local_20 = L"AfxControlBar42su";
  local_40 = param_5;
  iVar1 = FUN_0003f4f4();
  local_44 = *(undefined4 *)(iVar1 + 8);
  if (param_2 == 0) {
    local_3c = 0;
  }
  else {
    local_3c = *(undefined4 *)(param_2 + 0x1c);
  }
  iVar1 = (**(code **)(*param_1 + 0x58))(param_1,auStack_48);
  if (iVar1 != 0) {
    param_1[0x21] = param_3;
    FUN_00033358(0x10);
    FUN_00033358(0x3c000);
    iVar1 = FUN_000342f8(param_1,param_3,param_2);
    param_1[0x21] = 0;
    if (iVar1 != 0) {
      FUN_00033c54(param_1,param_5);
      GetWindowRect((HWND)param_1[7],&local_58);
      iVar1 = local_58.right - local_58.left;
      iVar2 = local_58.bottom - local_58.top;
      local_60 = (undefined1)iVar1;
      *(undefined1 *)(param_1 + 0x1e) = local_60;
      uStack_5f = (undefined1)((uint)iVar1 >> 8);
      *(undefined1 *)((int)param_1 + 0x79) = uStack_5f;
      uStack_5e = (undefined1)((uint)iVar1 >> 0x10);
      *(undefined1 *)((int)param_1 + 0x7a) = uStack_5e;
      uStack_5d = (undefined1)((uint)iVar1 >> 0x18);
      *(undefined1 *)((int)param_1 + 0x7b) = uStack_5d;
      local_5c = (undefined1)iVar2;
      *(undefined1 *)(param_1 + 0x1f) = local_5c;
      uStack_5b = (undefined1)((uint)iVar2 >> 8);
      *(undefined1 *)((int)param_1 + 0x7d) = uStack_5b;
      uStack_5a = (undefined1)((uint)iVar2 >> 0x10);
      *(undefined1 *)((int)param_1 + 0x7e) = uStack_5a;
      uStack_59 = (undefined1)((uint)iVar2 >> 0x18);
      *(undefined1 *)((int)param_1 + 0x7f) = uStack_59;
      FUN_00033b84(param_1,0,0x4000000,0);
      iVar1 = FUN_00032d14(param_1,param_3);
      if (iVar1 != 0) {
        FUN_00033cec(param_1,0,0,0,0,0,0x54);
        return 1;
      }
    }
  }
  return 0;
}


// 0003ad10 FUN_0003ad10

void FUN_0003ad10(int param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  undefined1 local_10;
  undefined1 uStack_f;
  undefined1 uStack_e;
  undefined1 uStack_d;
  undefined1 local_c;
  undefined1 uStack_b;
  undefined1 uStack_a;
  undefined1 uStack_9;
  
  if (param_3 == 0) {
    *param_2 = *(undefined1 *)(param_1 + 0x78);
    param_2[1] = *(undefined1 *)(param_1 + 0x79);
    param_2[2] = *(undefined1 *)(param_1 + 0x7a);
    param_2[3] = *(undefined1 *)(param_1 + 0x7b);
    param_2[4] = *(undefined1 *)(param_1 + 0x7c);
    param_2[5] = *(undefined1 *)(param_1 + 0x7d);
    param_2[6] = *(undefined1 *)(param_1 + 0x7e);
    param_2[7] = *(undefined1 *)(param_1 + 0x7f);
  }
  else {
    puVar1 = param_2;
    if (param_4 != 0) {
      puVar1 = *(undefined1 **)(param_1 + 0x7c);
    }
    puVar2 = (undefined1 *)0x7fff;
    if (param_4 == 0) {
      puVar2 = *(undefined1 **)(param_1 + 0x78);
      puVar1 = (undefined1 *)0x7fff;
    }
    local_10 = SUB41(puVar2,0);
    *param_2 = local_10;
    uStack_f = (undefined1)((uint)puVar2 >> 8);
    param_2[1] = uStack_f;
    uStack_e = (undefined1)((uint)puVar2 >> 0x10);
    param_2[2] = uStack_e;
    uStack_d = (undefined1)((uint)puVar2 >> 0x18);
    param_2[3] = uStack_d;
    local_c = SUB41(puVar1,0);
    param_2[4] = local_c;
    uStack_b = (undefined1)((uint)puVar1 >> 8);
    param_2[5] = uStack_b;
    uStack_a = (undefined1)((uint)puVar1 >> 0x10);
    param_2[6] = uStack_a;
    uStack_9 = (undefined1)((uint)puVar1 >> 0x18);
    param_2[7] = uStack_9;
  }
  return;
}


// 0003ae5c FUN_0003ae5c

bool FUN_0003ae5c(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  return *(int *)(iVar1 + 0x2c) == 0;
}


// 0003ae78 FUN_0003ae78

void FUN_0003ae78(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  *(undefined4 *)(iVar1 + 0x30) = param_1;
  return;
}


// 0003afc0 FUN_0003afc0

void FUN_0003afc0(undefined1 *param_1)

{
  int iVar1;
  
  *param_1 = 0x78;
  param_1[1] = 0xd;
  param_1[2] = 4;
  param_1[3] = 0;
  FUN_0003b06c(param_1);
  iVar1 = FUN_0003f170();
  if (*(undefined1 **)(iVar1 + 300) == param_1) {
    iVar1 = FUN_0003f170();
    *(undefined4 *)(iVar1 + 300) = 0;
  }
  if (*(void **)(param_1 + 0xb4) != (void *)0x0) {
    free(*(void **)(param_1 + 0xb4));
  }
  CString_Dtor((CString *)(param_1 + 0xbc));
  FUN_0002d9e0(param_1 + 0x7c);
  FUN_00030500(param_1);
  return;
}


// 0003b038 FUN_0003b038

void FUN_0003b038(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  iVar1 = FUN_0003ef20(iVar1 + 0x206c,&DAT_0003f550);
  FUN_0003eb5c(iVar1 + 8,param_1);
  return;
}


// 0003b06c FUN_0003b06c

void FUN_0003b06c(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  iVar1 = FUN_0003ef20(iVar1 + 0x206c,&DAT_0003f550);
  FUN_0003eb70(iVar1 + 8,param_1);
  return;
}


// 0003b0a0 FUN_0003b0a0

bool FUN_0003b0a0(int param_1,LPCWSTR param_2)

{
  int iVar1;
  HACCEL pHVar2;
  
  iVar1 = FUN_0003f4f4();
  pHVar2 = LoadAcceleratorsW(*(HINSTANCE *)(iVar1 + 0xc),param_2);
  *(HACCEL *)(param_1 + 0x5c) = pHVar2;
  return pHVar2 != (HACCEL)0x0;
}


// 0003b0d0 FUN_0003b0d0

int FUN_0003b0d0(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1[0x17];
  piVar1 = (int *)(**(code **)(*param_1 + 0xb4))();
  if ((piVar1 != (int *)0x0) && (iVar2 = (**(code **)(*piVar1 + 0xa4))(), iVar2 != 0)) {
    iVar3 = iVar2;
  }
  return iVar3;
}


// 0003b110 FUN_0003b110

undefined4 FUN_0003b110(int *param_1,LPMSG param_2)

{
  int iVar1;
  undefined4 uVar2;
  HACCEL hAccTable;
  
  if (param_2->message == 0x201) {
    FUN_00035e9c(param_2->hwnd);
  }
  iVar1 = FUN_0003084c(param_1,param_2);
  if (iVar1 == 0) {
    if ((((0xff < param_2->message) && (param_2->message < 0x109)) &&
        (hAccTable = (HACCEL)(**(code **)(*param_1 + 0xdc))(param_1), hAccTable != (HACCEL)0x0)) &&
       (iVar1 = TranslateAcceleratorW((HWND)param_1[7],hAccTable,param_2), iVar1 != 0)) {
      return 1;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}


// 0003b1a4 FUN_0003b1a4

void FUN_0003b1a4(int *param_1)

{
  if (param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 4))(param_1,1);
  }
  return;
}


// 0003b1cc FUN_0003b1cc

undefined4 FUN_0003b1cc(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00031b9c();
  if (*(int *)(iVar1 + 100) == 0) {
    uVar2 = FUN_0002ff50(param_1);
  }
  else {
    SetCursor(DAT_002de524);
    uVar2 = 1;
  }
  return uVar2;
}


// 0003b208 FUN_0003b208

undefined4 FUN_0003b208(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  if (param_3 == 0) {
    iVar1 = FUN_00033628();
    if (iVar1 == 0) {
      param_3 = *(int *)(param_1 + 0x9c) + 0x20000;
    }
    else {
      param_3 = *(int *)(param_1 + 0xa0) + 0x10000;
    }
    if (param_3 == 0) {
      return 0;
    }
  }
  iVar1 = FUN_0003f4f4();
  piVar2 = *(int **)(iVar1 + 4);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 0x90))(piVar2,param_3,0);
  }
  return 1;
}


// 0003b284 FUN_0003b284

undefined4 FUN_0003b284(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  LRESULT LVar3;
  undefined4 uVar4;
  
  uVar1 = param_2 & 0xffff;
  iVar2 = FUN_00031b9c();
  if ((((*(int *)(iVar2 + 100) == 0) || (param_3 != 0)) || (uVar1 == 0xe146)) ||
     ((uVar1 == 0xe147 || (uVar1 == 0xe145)))) {
    uVar4 = FUN_000318d8(param_1,param_2,param_3);
  }
  else {
    LVar3 = SendMessageW(*(HWND *)(param_1 + 0x1c),0x365,0,uVar1 + 0x10000);
    if (LVar3 == 0) {
      SendMessageW(*(HWND *)(param_1 + 0x1c),0x111,0xe147,0);
    }
    uVar4 = 1;
  }
  return uVar4;
}


// 0003b338 FUN_0003b338

undefined4 FUN_0003b338(int param_1,int param_2)

{
  do {
    if (param_1 == param_2) {
      return 1;
    }
    param_2 = FUN_00031acc();
  } while (param_2 != 0);
  return 0;
}


// 0003b368 FUN_0003b368

void FUN_0003b368(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  HWND pHVar4;
  BOOL BVar5;
  LRESULT LVar6;
  undefined4 uVar7;
  UINT uCmd;
  int iVar8;
  
  uVar1 = *(int *)(param_1 + 0xb0) + 1;
  *(uint *)(param_1 + 0xb0) = uVar1;
  if (uVar1 < 2) {
    iVar2 = FUN_00031b24(param_1);
    iVar8 = 0;
    iVar3 = FUN_0002acc0();
    if (iVar3 == 0) {
      pHVar4 = (HWND)0x0;
    }
    else {
      pHVar4 = *(HWND *)(iVar3 + 0x1c);
    }
    pHVar4 = GetWindow(pHVar4,0);
    if (pHVar4 != (HWND)0x0) {
      do {
        BVar5 = IsWindowEnabled(pHVar4);
        if ((((BVar5 != 0) && (iVar3 = FUN_0003001c(pHVar4), iVar3 != 0)) &&
            (iVar3 = FUN_0003b338(*(undefined4 *)(iVar2 + 0x1c),pHVar4), iVar3 != 0)) &&
           (LVar6 = SendMessageW(pHVar4,0x36c,0,0), LVar6 == 0)) {
          iVar8 = iVar8 + 1;
        }
        pHVar4 = GetWindow(pHVar4,2);
      } while (pHVar4 != (HWND)0x0);
      if (iVar8 != 0) {
        uVar7 = operator_new((iVar8 + 1) * 4);
        iVar8 = 0;
        *(undefined4 *)(param_1 + 0xb4) = uVar7;
        iVar3 = FUN_0002acc0();
        uCmd = 0;
        if (iVar3 == 0) {
          pHVar4 = (HWND)0x0;
        }
        else {
          pHVar4 = *(HWND *)(iVar3 + 0x1c);
        }
        while (pHVar4 = GetWindow(pHVar4,uCmd), pHVar4 != (HWND)0x0) {
          BVar5 = IsWindowEnabled(pHVar4);
          if (((BVar5 != 0) && (iVar3 = FUN_0003001c(pHVar4), iVar3 != 0)) &&
             ((iVar3 = FUN_0003b338(*(undefined4 *)(iVar2 + 0x1c),pHVar4), iVar3 != 0 &&
              (LVar6 = SendMessageW(pHVar4,0x36c,0,0), LVar6 == 0)))) {
            EnableWindow(pHVar4,0);
            *(HWND *)(*(int *)(param_1 + 0xb4) + iVar8 * 4) = pHVar4;
            iVar8 = iVar8 + 1;
          }
          uCmd = 2;
        }
        *(undefined4 *)(*(int *)(param_1 + 0xb4) + iVar8 * 4) = 0;
      }
    }
  }
  return;
}


// 0003b4d8 FUN_0003b4d8

void FUN_0003b4d8(int param_1)

{
  int iVar1;
  int *piVar2;
  BOOL BVar3;
  
  if (((*(int *)(param_1 + 0xb0) != 0) &&
      (iVar1 = *(int *)(param_1 + 0xb0) + -1, *(int *)(param_1 + 0xb0) = iVar1, iVar1 == 0)) &&
     (piVar2 = *(int **)(param_1 + 0xb4), piVar2 != (int *)0x0)) {
    if (*piVar2 != 0) {
      iVar1 = 0;
      do {
        BVar3 = IsWindow(*(HWND *)(iVar1 + (int)piVar2));
        if (BVar3 != 0) {
          EnableWindow(*(HWND *)(*(int *)(param_1 + 0xb4) + iVar1),1);
        }
        piVar2 = *(int **)(param_1 + 0xb4);
        iVar1 = iVar1 + 4;
      } while (*(int *)(iVar1 + (int)piVar2) != 0);
    }
    free(*(void **)(param_1 + 0xb4));
    *(undefined4 *)(param_1 + 0xb4) = 0;
  }
  return;
}


// 0003b55c FUN_0003b55c

void FUN_0003b55c(int *param_1,int param_2)

{
  int iVar1;
  HWND pHVar2;
  
  if ((param_2 == 0) || ((param_1[10] & 4U) == 0)) {
    GetParent((HWND)param_1[7]);
    iVar1 = FUN_0002ffec();
    if (iVar1 == 0) {
      if (param_2 == 0) {
        if (param_1[0x2c] == 0) {
          param_1[10] = param_1[10] | 0x80;
          (**(code **)(*param_1 + 0x80))(param_1);
        }
      }
      else if ((param_1[10] & 0x80U) != 0) {
        param_1[10] = param_1[10] & 0xffffff7f;
        (**(code **)(*param_1 + 0x84))(param_1);
        pHVar2 = GetActiveWindow();
        if (pHVar2 == (HWND)param_1[7]) {
          SendMessageW((HWND)param_1[7],6,1,0);
        }
      }
    }
  }
  else {
    FUN_00033dcc(param_1,0);
    SetFocus((HWND)0x0);
  }
  return;
}


// 0003b628 FUN_0003b628

undefined4 FUN_0003b628(wchar_t *param_1,int param_2)

{
  bool bVar1;
  
  if (*(int *)(param_2 + 0x28) == 0) {
    FUN_00033358(8);
    param_1 = L"AfxFrameOrView42su";
    *(wchar_t **)(param_2 + 0x28) = L"AfxFrameOrView42su";
  }
  bVar1 = (*(uint *)(param_2 + 0x20) & 0x8000) != 0;
  if (bVar1) {
    param_1 = DAT_002de53c;
  }
  if (bVar1 && param_1 != (wchar_t *)0x0) {
    *(uint *)(param_2 + 0x20) = *(uint *)(param_2 + 0x20) | 0x4000;
  }
  return 1;
}


// 0003b678 FUN_0003b678

undefined4
FUN_0003b678(int param_1,undefined4 param_2,wchar_t *param_3,undefined4 param_4,int *param_5,
            int param_6,LPCWSTR param_7,undefined4 param_8,undefined4 param_9)

{
  int iVar1;
  HANDLE lParam;
  undefined4 uVar2;
  
  *(LPCWSTR *)(param_1 + 0x4c) = param_7;
  CString_AssignW((CString *)(param_1 + 0xbc),param_3);
  uVar2 = 0;
  if (param_6 != 0) {
    uVar2 = *(undefined4 *)(param_6 + 0x1c);
  }
  iVar1 = FUN_00030288(param_1,param_8,param_2,param_3,param_4,*param_5,param_5[1],
                       param_5[2] - *param_5,param_5[3] - param_5[1],uVar2,0,param_9);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (param_7 != (LPCWSTR)0x0) {
      iVar1 = FUN_0003f4f4(iVar1);
      lParam = LoadImageW(*(HINSTANCE *)(iVar1 + 0xc),param_7,1,0x10,0x10,0);
      if (lParam != (HANDLE)0x0) {
        PostMessageW(*(HWND *)(param_1 + 0x1c),0x80,0,(LPARAM)lParam);
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}


// 0003b764 FUN_0003b764

int * FUN_0003b764(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  undefined4 local_38;
  undefined4 local_34;
  LONG local_30;
  LONG local_2c;
  tagRECT tStack_28;
  
  piVar1 = (int *)FUN_0002ed70(*param_2);
  if (piVar1 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    GetClientRect(*(HWND *)(param_1 + 0x1c),&tStack_28);
    local_38 = 0;
    local_30 = tStack_28.right;
    local_34 = 0;
    local_2c = tStack_28.bottom;
    iVar2 = (**(code **)(*piVar1 + 0x50))(piVar1,0,0,0x50800000,&local_38,param_1,param_3,param_2);
    piVar3 = (int *)0x0;
    if (iVar2 != 0) {
      piVar3 = piVar1;
    }
  }
  return piVar3;
}


// 0003b800 FUN_0003b800

undefined4 FUN_0003b800(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  
  if ((((param_3 != (int *)0x0) && (*param_3 != 0)) &&
      ((param_3[1] == 0 || (*(int *)(param_3[1] + 0x50) == 0)))) &&
     (iVar1 = FUN_0003b764(param_1,param_3,0xe900), iVar1 == 0)) {
    return 0;
  }
  return 1;
}


// 0003b858 FUN_0003b858

undefined4 FUN_0003b858(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0002ff50();
  if ((iVar1 == -1) || (iVar1 = (**(code **)(*param_1 + 0xd0))(param_1,param_2,param_3), iVar1 == 0)
     ) {
    uVar2 = 0xffffffff;
  }
  else {
    PostMessageW((HWND)param_1[7],0x362,0xe001,0);
    (**(code **)(*param_1 + 0xc0))(param_1,1);
    uVar2 = 0;
  }
  return uVar2;
}


// 0003b8e0 FUN_0003b8e0

undefined4 FUN_0003b8e0(int *param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  HICON pHVar2;
  BOOL BVar3;
  undefined4 uVar4;
  tagWNDCLASSW local_68;
  undefined1 auStack_40 [32];
  undefined4 local_20;
  LPCWSTR local_18;
  
  iVar1 = FUN_0003f4f4();
  pHVar2 = LoadIconW(*(HINSTANCE *)(iVar1 + 0xc),(LPCWSTR)(param_3 & 0xffff));
  if (pHVar2 != (HICON)0x0) {
    memset(auStack_40,0,0x30);
    local_20 = param_2;
    (**(code **)(*param_1 + 0x58))(param_1,auStack_40);
    if (local_18 != (LPCWSTR)0x0) {
      iVar1 = FUN_0003f4f4();
      BVar3 = GetClassInfoW(*(HINSTANCE *)(iVar1 + 8),local_18,&local_68);
      if ((BVar3 != 0) && (local_68.hIcon != pHVar2)) {
        uVar4 = FUN_00030c7c(local_68.style,local_68.hCursor,local_68.hbrBackground,pHVar2);
        return uVar4;
      }
    }
  }
  return 0;
}


// 0003b994 FUN_0003b994

undefined4 FUN_0003b994(int param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  CString local_18;
  
  *(uint *)(param_1 + 0x9c) = param_2;
  local_18.str = g_afxEmptyString;
  iVar1 = FUN_0002ee30(&local_18);
  if (iVar1 != 0) {
    FUN_0002ef00(param_1 + 0xbc,local_18.str,0,10);
  }
  FUN_00033358(8);
  uVar2 = FUN_0003b8e0(param_1,param_3,param_2);
  iVar1 = FUN_0003b678(param_1,uVar2,*(undefined4 *)(param_1 + 0xbc),0x10000000,
                       &CFrameWnd::rectDefault,param_4,param_2 & 0xffff,0,param_5);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0002b038(*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x58) = uVar2;
    FUN_0003b0a0(param_1,param_2 & 0xffff);
    if (param_5 == 0) {
      FUN_00031cf4(*(undefined4 *)(param_1 + 0x1c),0x364,0,0,1,1);
    }
    uVar2 = 1;
  }
  CString_Dtor(&local_18);
  return uVar2;
}


// 0003ba98 FUN_0003ba98

void FUN_0003ba98(int *param_1,int param_2)

{
  int *piVar1;
  
  if ((param_2 == 0) &&
     ((piVar1 = (int *)(**(code **)(*param_1 + 0xb4))(), piVar1 == (int *)0x0 ||
      (param_2 = (**(code **)(*piVar1 + 0xa0))(), param_2 == 0)))) {
    param_2 = param_1[0x16];
  }
  FUN_0002b050(param_1[7],param_2);
  return;
}


// 0003bae8 FUN_0003bae8

void FUN_0003bae8(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int local_14;
  
  if (((code *)param_1[0x2b] != (code *)0x0) && (iVar1 = (*(code *)param_1[0x2b])(), iVar1 == 0)) {
    return;
  }
  piVar2 = (int *)(**(code **)(*param_1 + 0xb4))(param_1);
  if ((piVar2 != (int *)0x0) && (iVar1 = (**(code **)(*piVar2 + 0x88))(piVar2,param_1), iVar1 == 0))
  {
    return;
  }
  iVar1 = FUN_0003f4f4();
  piVar3 = *(int **)(iVar1 + 4);
  if ((piVar3 != (int *)0x0) && ((int *)piVar3[7] == param_1)) {
    if ((piVar2 == (int *)0x0) && (iVar1 = (**(code **)(*piVar3 + 0x80))(piVar3), iVar1 == 0)) {
      return;
    }
    FUN_00037eb0(piVar3);
    FUN_00037efc(piVar3,0);
    iVar1 = FUN_0003ae5c();
    if (iVar1 == 0) {
      FUN_0003ae78(0);
      return;
    }
    iVar1 = FUN_0003f4f4();
    if ((*(char *)(iVar1 + 0x14) == '\0') && (piVar3[7] == 0)) {
      FUN_0003fd90(0);
      return;
    }
  }
  if ((piVar2 != (int *)0x0) && (piVar2[0x12] != 0)) {
    local_14 = (**(code **)(*piVar2 + 0x5c))(piVar2);
    do {
      if (local_14 == 0) {
        (**(code **)(*piVar2 + 0x78))(piVar2);
        return;
      }
      (**(code **)(*piVar2 + 0x60))(piVar2,&local_14);
      piVar3 = (int *)FUN_00031a70();
    } while (piVar3 == param_1);
    (**(code **)(*piVar2 + 0x90))(piVar2,param_1);
  }
  (**(code **)(*param_1 + 0x54))(param_1);
  return;
}


// 0003bc90 FUN_0003bc90

void FUN_0003bc90(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 extraout_r2_01;
  undefined4 extraout_r2_02;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  FUN_0003c62c();
  uVar3 = extraout_r2;
  if ((*(int *)(param_1 + 0x58) != 0) &&
     (iVar2 = FUN_0002b038(*(undefined4 *)(param_1 + 0x1c)), uVar3 = extraout_r2_00,
     iVar2 != *(int *)(param_1 + 0x58))) {
    FUN_0002b050(*(undefined4 *)(param_1 + 0x1c));
    uVar3 = extraout_r2_01;
  }
  if (*(int *)(param_1 + 0xc4) != 0) {
    SHDoneButton(*(undefined4 *)(param_1 + 0x1c),2);
    *(undefined4 *)(*(int *)(param_1 + 0xc4) + 0x40) = 0;
    *(undefined4 *)(param_1 + 0xc4) = 0;
    uVar3 = extraout_r2_02;
  }
  piVar1 = *(int **)(param_1 + 0x38);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 4))(piVar1,1,uVar3,*(code **)(*piVar1 + 4),unaff_r4,unaff_lr);
  }
  *(undefined4 *)(param_1 + 0x38) = 0;
  if (*(int *)(param_1 + 0x40) != 0) {
    FUN_000336d0(param_1,0);
  }
  FUN_0002ff50(param_1);
  return;
}


// 0003bcf4 FUN_0003bcf4

void FUN_0003bcf4(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 unaff_r4;
  undefined4 unaff_lr;
  
  iVar2 = FUN_00031b9c();
  if (iVar2 == param_1) {
    iVar2 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
    SHHandleWMSettingChange
              (*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(iVar2 + 0x44),
               *(undefined4 *)(iVar2 + 0x48),param_1 + 200);
  }
  DAT_002dc968 = 0;
  iVar2 = FUN_0002acc0(param_1,0,0);
  if (iVar2 == param_1) {
    FUN_00034010(&afxData);
  }
  uVar1 = FUN_00033b14(param_1);
  if ((uVar1 & 0x40000000) == 0) {
    iVar2 = FUN_0002feb8();
    FUN_00031cf4(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(iVar2 + 4),
                 *(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc),1,1,unaff_r4,unaff_lr);
  }
  FUN_0002ff50(param_1);
  return;
}


// 0003bd4c FUN_0003bd4c

void FUN_0003bd4c(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_0002db68(param_1 + 0x7c,param_2,0);
  if (iVar1 != 0) {
    FUN_0002db2c(param_1 + 0x7c);
  }
  return;
}


// 0003bd70 FUN_0003bd70

undefined4
FUN_0003bd70(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  iVar1 = FUN_0003f170();
  uVar5 = *(undefined4 *)(iVar1 + 300);
  *(undefined4 *)(iVar1 + 300) = param_1;
  piVar2 = (int *)FUN_0003c120(param_1);
  if (piVar2 == (int *)0x0) {
LAB_0003bdd4:
    iVar3 = FUN_0002f3c4(param_1,param_2,param_3,param_4,param_5);
    if (iVar3 == 0) {
      iVar3 = FUN_0003f4f4();
      piVar2 = *(int **)(iVar3 + 4);
      if (piVar2 != (int *)0x0) {
        iVar3 = (**(code **)(*piVar2 + 0xc))(piVar2,param_2,param_3,param_4,param_5);
        uVar4 = 1;
        if (iVar3 != 0) goto LAB_0003be3c;
      }
      uVar4 = 0;
      goto LAB_0003be3c;
    }
  }
  else {
    iVar3 = (**(code **)(*piVar2 + 0xc))(piVar2,param_2,param_3,param_4,param_5);
    if (iVar3 == 0) goto LAB_0003bdd4;
  }
  uVar4 = 1;
LAB_0003be3c:
  *(undefined4 *)(iVar1 + 300) = uVar5;
  return uVar4;
}


// 0003be48 FUN_0003be48

void FUN_0003be48(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0003c120();
  if (iVar1 != 0) {
    iVar2 = FUN_0002feb8();
    SendMessageW(*(HWND *)(iVar1 + 0x1c),0x114,*(WPARAM *)(iVar2 + 8),*(LPARAM *)(iVar2 + 0xc));
  }
  return;
}


// 0003be74 FUN_0003be74

void FUN_0003be74(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0003c120();
  if (iVar1 != 0) {
    iVar2 = FUN_0002feb8();
    SendMessageW(*(HWND *)(iVar1 + 0x1c),0x115,*(WPARAM *)(iVar2 + 8),*(LPARAM *)(iVar2 + 0xc));
  }
  return;
}


// 0003bea4 FUN_0003bea4

undefined4 FUN_0003bea4(int *param_1)

{
  int iVar1;
  int *piVar2;
  
  FUN_00032710();
  iVar1 = FUN_0002f1d0();
  if (*(int **)(iVar1 + 0x1c) == param_1) {
    piVar2 = (int *)FUN_0003c120(param_1);
    if (piVar2 == (int *)0x0) {
      (**(code **)(*param_1 + 0xb8))(param_1);
      piVar2 = (int *)FUN_0003c120();
      if (piVar2 == (int *)0x0) goto LAB_0003bf0c;
    }
    (**(code **)(*piVar2 + 0xc4))(piVar2,0,piVar2,piVar2);
  }
LAB_0003bf0c:
  PostMessageW((HWND)param_1[7],0x36a,0,0);
  return 0;
}


// 0003bf2c FUN_0003bf2c

void FUN_0003bf2c(int *param_1,int param_2,int *param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  LRESULT LVar5;
  bool bVar6;
  
  if (param_1[0x31] != 0) {
    if (param_2 == 0) {
      SHDoneButton(param_1[7],2);
    }
    if ((param_2 == 1) || (param_2 == 2)) {
      SHDoneButton(param_1[7],1);
    }
  }
  piVar1 = (int *)FUN_00031b9c(param_1);
  if (piVar1 == param_1) {
    iVar2 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
    SHHandleWMActivate(param_1[7],*(undefined4 *)(iVar2 + 0x44),*(undefined4 *)(iVar2 + 0x48),
                       param_1 + 0x32,0);
  }
  uVar3 = FUN_00033b14(param_1);
  piVar1 = param_1;
  if ((uVar3 & 0x40000000) == 0) {
    piVar1 = (int *)FUN_00031b9c(param_1);
  }
  if (param_2 != 0) {
    param_3 = param_1;
  }
  if ((piVar1 == param_3) ||
     ((piVar4 = (int *)FUN_00031b9c(param_3), piVar1 == piVar4 &&
      (LVar5 = SendMessageW((HWND)param_3[7],0x36d,0x40,0), LVar5 != 0)))) {
    bVar6 = true;
  }
  else {
    bVar6 = false;
  }
  uVar3 = piVar1[10];
  piVar1[10] = uVar3 & 0xffffffdf;
  if (bVar6) {
    piVar1[10] = uVar3 & 0xffffffdf | 0x20;
  }
  piVar1 = (int *)FUN_0003c120(param_1);
  if (piVar1 == (int *)0x0) {
    (**(code **)(*param_1 + 0xb8))(param_1);
    piVar1 = (int *)FUN_0003c120();
    if (piVar1 == (int *)0x0) goto LAB_0003c0b8;
  }
  if ((param_2 != 0) && (param_4 == 0)) {
    (**(code **)(*piVar1 + 0xc4))(piVar1,1,piVar1,piVar1);
  }
  (**(code **)(*piVar1 + 200))(piVar1,param_2,param_1);
LAB_0003c0b8:
  FUN_0002ff50(param_1);
  return;
}


// 0003c0c8 FUN_0003c0c8

void FUN_0003c0c8(int param_1)

{
  BOOL BVar1;
  
  if ((*(int *)(param_1 + 0xc4) != param_1) &&
     (BVar1 = IsWindow(*(HWND *)(*(int *)(param_1 + 0xc4) + 0x1c)), BVar1 != 0)) {
    SendMessageW(*(HWND *)(*(int *)(param_1 + 0xc4) + 0x1c),0x111,1,0);
  }
  return;
}


// 0003c108 FUN_0003c108

void FUN_0003c108(undefined4 param_1)

{
  FUN_00031b9c();
  FUN_0002ff50(param_1);
  return;
}


// 0003c120 FUN_0003c120

undefined4 FUN_0003c120(int param_1)

{
  return *(undefined4 *)(param_1 + 0xa8);
}


// 0003c128 FUN_0003c128

void FUN_0003c128(int param_1,int *param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_1 + 0xa8);
  if (param_2 != piVar1) {
    *(undefined4 *)(param_1 + 0xa8) = 0;
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0xc4))(piVar1,0,param_2,piVar1);
    }
    if ((*(int *)(param_1 + 0xa8) == 0) &&
       (*(int **)(param_1 + 0xa8) = param_2, param_2 != (int *)0x0 && param_3 != 0)) {
      (**(code **)(*param_2 + 0xc4))(param_2,1,param_2,piVar1);
    }
  }
  return;
}


// 0003c1ac FUN_0003c1ac

void FUN_0003c1ac(int param_1)

{
  if (*(int *)(param_1 + 0xa8) == 0) {
    FUN_0002ff50();
  }
  else {
    FUN_00033e00(*(int *)(param_1 + 0xa8));
  }
  return;
}


// 0003c1d0 FUN_0003c1d0

undefined4 FUN_0003c1d0(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0003c120();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar1 + 0x44);
  }
  return uVar2;
}


// 0003c1e8 FUN_0003c1e8

void FUN_0003c1e8(undefined4 param_1,int *param_2,int param_3,int param_4)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  piVar1 = (int *)FUN_0003ce3c(param_2);
  if (param_4 == 0) {
    uVar2 = 0x40;
    if (param_3 == 0) {
      uVar2 = 0x80;
    }
    FUN_00033cec(param_2,0,0,0,0,0,uVar2 | 0x17);
    (**(code **)(*param_2 + 0xbc))(param_2,param_3);
    if ((param_3 != 0) || (iVar3 = FUN_0003ce54(param_2), iVar3 == 0)) {
      (**(code **)(*piVar1 + 0xc0))(piVar1,0);
    }
  }
  else {
    (**(code **)(*param_2 + 0xbc))(param_2,param_3);
    piVar1[0x38] = piVar1[0x38] | 0xc;
  }
  return;
}


// 0003c2bc FUN_0003c2bc

void FUN_0003c2bc(int param_1,int param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  HMENU hMenu;
  HMENU pHVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  int nPos;
  undefined1 auStack_40 [4];
  uint local_3c;
  uint local_38;
  int local_34;
  int local_30;
  uint local_20;
  int local_1c;
  
  FUN_00035e9c(*(undefined4 *)(param_1 + 0x1c));
  if (param_4 == 0) {
    FUN_0002f584(auStack_40);
    local_34 = param_2;
    iVar1 = FUN_0003f170();
    iVar3 = param_2;
    if ((((*(int *)(iVar1 + 0x5c) != *(int *)(param_2 + 4)) &&
         (iVar1 = FUN_0002b038(*(undefined4 *)(param_1 + 0x1c)), iVar3 = local_1c, iVar1 != 0)) &&
        (iVar1 = FUN_00031b24(param_1), iVar3 = local_1c, iVar1 != 0)) &&
       (hMenu = (HMENU)FUN_0002b038(*(undefined4 *)(iVar1 + 0x1c)), iVar3 = local_1c,
       hMenu != (HMENU)0x0)) {
      iVar1 = FUN_0002b16c(hMenu);
      nPos = 0;
      iVar3 = local_1c;
      if (0 < iVar1) {
        do {
          pHVar2 = GetSubMenu(hMenu,nPos);
          if (pHVar2 == *(HMENU *)(param_2 + 4)) {
            iVar3 = FUN_00033eec(hMenu);
            break;
          }
          nPos = nPos + 1;
          iVar3 = local_1c;
        } while (nPos < iVar1);
      }
    }
    local_1c = iVar3;
    local_20 = FUN_0002b16c(*(undefined4 *)(param_2 + 4));
    local_38 = 0;
    if (local_20 != 0) {
      do {
        local_3c = FUN_0002afe8(*(undefined4 *)(param_2 + 4));
        uVar4 = local_20;
        if (local_3c != 0) {
          if (local_3c == 0xffffffff) {
            GetSubMenu(*(HMENU *)(param_2 + 4),local_38);
            local_30 = FUN_00033eec();
            uVar4 = local_20;
            if (((local_30 != 0) &&
                (local_3c = FUN_0002afe8(*(undefined4 *)(local_30 + 4),0), uVar4 = local_20,
                local_3c != 0)) && (local_3c != 0xffffffff)) goto LAB_0003c43c;
          }
          else {
            local_30 = 0;
            if ((*(int *)(param_1 + 0x50) == 0) || (uVar6 = 1, 0xefff < local_3c)) {
LAB_0003c43c:
              uVar6 = 0;
            }
            FUN_0002f79c(auStack_40,param_1,uVar6);
            uVar4 = FUN_0002b16c(*(undefined4 *)(param_2 + 4));
            if (uVar4 < local_20) {
              local_38 = (uVar4 - local_20) + local_38;
              while ((local_38 < uVar4 &&
                     (uVar5 = FUN_0002afe8(*(undefined4 *)(param_2 + 4)), uVar5 == local_3c))) {
                local_38 = local_38 + 1;
              }
            }
          }
        }
        local_20 = uVar4;
        local_38 = local_38 + 1;
      } while (local_38 < local_20);
    }
  }
  return;
}


// 0003c4ac FUN_0003c4ac

void FUN_0003c4ac(undefined4 param_1,undefined4 param_2,CString *param_3)

{
  wchar_t *pwVar1;
  int iVar2;
  
  pwVar1 = CString_GetBuffer(param_3,0xff);
  iVar2 = FUN_0002eec8(param_2,pwVar1,0x100);
  if ((iVar2 != 0) && (pwVar1 = wcschr(pwVar1,L'\n'), pwVar1 != (wchar_t *)0x0)) {
    *pwVar1 = L'\0';
  }
  CString_ReleaseBuffer(param_3,0xffffffff);
  return;
}


// 0003c534 FUN_0003c534

int FUN_0003c534(int *param_1,int param_2,CString param_3)

{
  int iVar1;
  int iVar2;
  CString local_1c;
  
  iVar2 = param_1[0x29];
  param_1[10] = param_1[10] & 0xffffffbf;
  iVar1 = (**(code **)(*param_1 + 200))();
  if (iVar1 != 0) {
    local_1c.str = g_afxEmptyString;
    if ((param_3.str == (wchar_t *)0x0) && (param_3.str = (wchar_t *)0x0, param_2 != 0)) {
      if ((param_2 == 0xef06) && (param_1[0x2b] != 0)) {
        param_2 = 0xf005;
      }
      (**(code **)(*param_1 + 0xbc))(param_1,param_2,&local_1c);
      param_3.str = local_1c.str;
    }
    FUN_00033bb8(iVar1,param_3.str);
    iVar1 = FUN_00031a70(iVar1);
    if (iVar1 != 0) {
      *(int *)(iVar1 + 0xa4) = param_2;
      *(int *)(iVar1 + 0xa0) = param_2;
    }
    CString_Dtor(&local_1c);
  }
  param_1[0x29] = param_2;
  param_1[0x28] = param_2;
  return iVar2;
}


// 0003c62c FUN_0003c62c

void FUN_0003c62c(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 0x80);
  while (puVar2 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar2;
    (**(code **)(*(int *)puVar2[2] + 0x54))();
    puVar2 = puVar1;
  }
  return;
}


// 0003c660 FUN_0003c660

int FUN_0003c660(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  if (param_2 == 0) {
LAB_0003c6a4:
    iVar2 = 0;
  }
  else {
    puVar4 = *(undefined4 **)(param_1 + 0x80);
    do {
      if (puVar4 == (undefined4 *)0x0) goto LAB_0003c6a4;
      puVar3 = (undefined4 *)*puVar4;
      iVar2 = puVar4[2];
      uVar1 = GetDlgCtrlID(*(HWND *)(iVar2 + 0x1c));
      puVar4 = puVar3;
    } while ((uVar1 & 0xffff) != param_2);
  }
  return iVar2;
}


// 0003c6b4 FUN_0003c6b4

void FUN_0003c6b4(undefined4 param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0003c660(param_1,param_2[1]);
  if (iVar1 == 0) {
    param_2[7] = 1;
  }
  else {
    uVar2 = FUN_00033b14();
    (**(code **)(*param_2 + 4))(param_2,(uVar2 & 0x10000000) != 0);
  }
  return;
}


// 0003c700 FUN_0003c700

bool FUN_0003c700(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_0003c660();
  if (iVar1 != 0) {
    uVar2 = FUN_00033b14(iVar1);
    FUN_0003c1e8(param_1,iVar1,(uVar2 & 0x10000000) == 0,0);
  }
  return iVar1 != 0;
}


// 0003c748 FUN_0003c748

void FUN_0003c748(undefined4 param_1,undefined4 *param_2)

{
  SHORT SVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_2[1];
  uVar3 = 1;
  if (iVar2 == 0xe701) {
    iVar2 = 0x14;
  }
  else if (iVar2 == 0xe702) {
    iVar2 = 0x90;
  }
  else if (iVar2 == 0xe703) {
    iVar2 = 0x91;
  }
  else {
    if (iVar2 != 0xe706) {
      param_2[7] = 1;
      return;
    }
    iVar2 = 0x15;
    if (DAT_002de53c == 0) {
      uVar3 = 0x8000;
    }
  }
  SVar1 = GetKeyState(iVar2);
  (**(code **)*param_2)(param_2,uVar3 & (int)SVar1);
  return;
}


// 0003c7f8 FUN_0003c7f8

void FUN_0003c7f8(int *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_00033b14();
  if ((uVar1 & 0x8000) != 0) {
    iVar2 = (**(code **)(*param_1 + 0xb4))(param_1);
    if (param_2 == 0 || iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = *(undefined4 *)(iVar2 + 0x1c);
    }
    FUN_0003c840(param_1,uVar3);
  }
  return;
}


// 0003c840 FUN_0003c840

void FUN_0003c840(int param_1,wchar_t *param_2)

{
  uint uVar1;
  size_t sVar2;
  wchar_t local_414 [516];
  
  uVar1 = FUN_00033b14();
  if ((uVar1 & 0x4000) == 0) {
    wcscpy(local_414,*(wchar_t **)(param_1 + 0xbc));
    if (param_2 != (wchar_t *)0x0) {
      wcscat(local_414,(wchar_t *)&DAT_000440fc);
      wcscat(local_414,param_2);
      if (0 < *(int *)(param_1 + 0x54)) {
        sVar2 = wcslen(local_414);
        wsprintfW(local_414 + sVar2,(LPCWSTR)&DAT_00044104,*(undefined4 *)(param_1 + 0x54));
      }
    }
  }
  else {
    local_414[0] = L'\0';
    if (param_2 != (wchar_t *)0x0) {
      wcscpy(local_414,param_2);
      if (0 < *(int *)(param_1 + 0x54)) {
        sVar2 = wcslen(local_414);
        wsprintfW(local_414 + sVar2,(LPCWSTR)&DAT_00044104,*(undefined4 *)(param_1 + 0x54));
      }
      wcscat(local_414,(wchar_t *)&DAT_000440fc);
    }
    wcscat(local_414,*(wchar_t **)(param_1 + 0xbc));
  }
  FUN_00035e10(*(undefined4 *)(param_1 + 0x1c),local_414);
  return;
}


// 0003c950 FUN_0003c950

void FUN_0003c950(int *param_1)

{
  if ((param_1[0x38] & 1U) != 0) {
    (**(code **)(*param_1 + 0xd8))(param_1,param_1[0x2e]);
  }
  if ((param_1[0x38] & 2U) != 0) {
    (**(code **)(*param_1 + 0xd4))(param_1,1);
  }
  if ((param_1[0x38] & 8U) != 0) {
    (**(code **)(*param_1 + 0xc0))(param_1,param_1[0x38] & 4);
    UpdateWindow((HWND)param_1[7]);
  }
  param_1[0x38] = 0;
  return;
}


// 0003c9d0 FUN_0003c9d0

void FUN_0003c9d0(int *param_1)

{
  uint uVar1;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  if (param_1[0x30] == 0) {
    param_1[0x30] = 1;
    param_1[0x38] = param_1[0x38] & 0xfffffff3;
    uVar1 = FUN_00033b14();
    if ((uVar1 & 0x2000) == 0) {
      FUN_00032108(param_1,0,0xffff,0xe900,2,param_1 + 0x1b,0,1);
    }
    else {
      local_20 = 0;
      local_1c = 0;
      local_18 = 0x7fff;
      local_14 = 0x7fff;
      FUN_00032108(param_1,0,0xffff,0xe900,1,&local_20,&local_20,0);
      FUN_00032108(param_1,0,0xffff,0xe900,2,param_1 + 0x1b,&local_20,1);
      (**(code **)(*param_1 + 0x5c))(param_1,&local_20,0);
      FUN_00033cec(param_1,0,0,0,local_18 - local_20,local_14 - local_1c,0x16);
    }
    param_1[0x30] = 0;
  }
  return;
}


// 0003cb14 FUN_0003cb14

undefined4 FUN_0003cb14(int param_1,int param_2,RECT *param_3)

{
  BOOL BVar1;
  
  if (param_2 == 1) {
    FUN_00032108(param_1,0,0xffff,0xe900,1,param_3,0,1);
  }
  else if ((param_2 != 2) && (param_2 == 3)) {
    if (param_3 == (RECT *)0x0) {
      if ((((((LPRECT)(param_1 + 0x6c))->left == 0) && (*(int *)(param_1 + 0x74) == 0)) &&
          (*(int *)(param_1 + 0x70) == 0)) && (*(int *)(param_1 + 0x78) == 0)) {
        return 0;
      }
      SetRectEmpty((LPRECT)(param_1 + 0x6c));
    }
    else {
      BVar1 = EqualRect((RECT *)(param_1 + 0x6c),param_3);
      if (BVar1 != 0) {
        return 0;
      }
      CopyRect((RECT *)(param_1 + 0x6c),param_3);
    }
  }
  return 1;
}


// 0003cbe4 FUN_0003cbe4

void FUN_0003cbe4(int *param_1,int param_2)

{
  FUN_0002ff50();
  if (param_2 != 1) {
    (**(code **)(*param_1 + 0xc0))(param_1,1);
  }
  return;
}


// 0003cc14 FUN_0003cc14

void FUN_0003cc14(int param_1)

{
  if (*(int *)(param_1 + 0xa8) == 0) {
    FUN_0002ff50(param_1);
  }
  return;
}


// 0003cc2c FUN_0003cc2c

void FUN_0003cc2c(int param_1,int param_2)

{
  BOOL BVar1;
  
  if (param_2 == -1) {
    BVar1 = IsWindowVisible(*(HWND *)(param_1 + 0x1c));
    if (BVar1 == 0) {
      param_2 = 1;
    }
    else {
      BVar1 = IsWindowEnabled(*(HWND *)(param_1 + 0x1c));
      if (BVar1 == 0) {
        param_2 = 0xd;
      }
    }
  }
  FUN_0003cc98(param_1,param_2);
  if (param_2 != -1) {
    FUN_00033d64(param_1,param_2);
    FUN_0003cc98(param_1,param_2);
  }
  return;
}


// 0003cc98 FUN_0003cc98

void FUN_0003cc98(undefined4 param_1,int param_2)

{
  HWND hWnd;
  
  if ((((param_2 != 0) && (param_2 != 6)) && (param_2 != 8)) && (param_2 != 4)) {
    hWnd = GetActiveWindow();
    BringWindowToTop(hWnd);
  }
  return;
}


// 0003ccc8 FUN_0003ccc8

void FUN_0003ccc8(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  CString *pCVar3;
  CString local_18;
  CString CStack_14;
  CString CStack_10;
  
  iVar1 = FUN_0003001c(*param_2);
  if (((iVar1 != 0) && (iVar2 = FUN_0002ed1c(iVar1,&CCeDocList::classCCeDocList), iVar2 != 0)) &&
     (*(int *)(iVar1 + 0x44) != 0)) {
    FUN_0002ee30(*(int *)(iVar1 + 0x44) + 0x70,0xff03);
    local_18.str = g_afxEmptyString;
    FUN_0002ee30(&local_18,0xff02);
    iVar2 = wcscmp((wchar_t *)param_2[4],local_18.str);
    if (iVar2 == 0) {
      CString_Assign((CString *)(*(int *)(iVar1 + 0x44) + 0x74),&local_18);
    }
    else {
      pCVar3 = CString_CtorA(&CStack_10,s___00043a9c);
      pCVar3 = CString_PlusW(&CStack_14,pCVar3,(wchar_t *)param_2[4]);
      CString_Append((CString *)(*(int *)(iVar1 + 0x44) + 0x70),pCVar3);
      CString_Dtor(&CStack_14);
      CString_Dtor(&CStack_10);
      CString_AssignW((CString *)(*(int *)(iVar1 + 0x44) + 0x74),(wchar_t *)param_2[4]);
    }
    CString_Dtor(&local_18);
  }
  return;
}


// 0003cde0 FUN_0003cde0

void FUN_0003cde0(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  
  SHSipPreference(*(undefined4 *)(param_1 + 0x1c),2);
  iVar2 = 0xc;
  puVar4 = (undefined1 *)(param_1 + 200);
  puVar5 = (undefined1 *)(param_1 + 0xd4);
  do {
    iVar3 = iVar2 + -1;
    *puVar4 = *puVar5;
    bVar1 = 0 < iVar2;
    iVar2 = iVar3;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  } while (iVar3 != 0 && bVar1);
  if ((*(uint *)(param_1 + 0xd0) & 1) != 0) {
    SHSipPreference(*(undefined4 *)(param_1 + 0x1c),0);
  }
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x1a,0xffffffff,0);
  return;
}


// 0003ce3c FUN_0003ce3c

int FUN_0003ce3c(int param_1)

{
  int iVar1;
  
  iVar1 = FUN_00031a70();
  if (iVar1 == 0) {
    iVar1 = *(int *)(param_1 + 0x74);
  }
  return iVar1;
}


// 0003ce54 FUN_0003ce54

undefined4 FUN_0003ce54(void)

{
  return 0;
}


// 0003ce5c FUN_0003ce5c

undefined4 FUN_0003ce5c(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  
  iVar1 = FUN_00032444(param_3,&local_1c);
  if (iVar1 == 0) {
    if (DAT_002de53c == 0) {
      uVar2 = 0;
      if (param_3 != 0) {
        uVar2 = *(undefined4 *)(param_3 + 0x1c);
      }
      iVar1 = FUN_000329ac(*(undefined4 *)(param_2 + 4),uVar2,param_4,DAT_002de504,DAT_002de514);
      local_1c = DAT_002de504;
      if (iVar1 == 0) {
        local_1c = FUN_0002ff50(param_1);
      }
    }
    else {
      local_1c = thunk_FUN_00032920(param_1,param_2,param_3,param_4);
    }
  }
  return local_1c;
}


// 0003cefc FUN_0003cefc

int FUN_0003cefc(int param_1)

{
  return param_1 + 0x44;
}


// 0003cf08 FUN_0003cf08

undefined4 FUN_0003cf08(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(HWND *)(param_1 + 0x1c) == (HWND)0x0) {
    iVar2 = FUN_0003cf4c(param_1);
    uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x70) + iVar2 * 4);
  }
  else {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x476,0,0);
    uVar1 = FUN_0002ffec();
  }
  return uVar1;
}


// 0003cf4c FUN_0003cf4c

LRESULT FUN_0003cf4c(int param_1)

{
  int iVar1;
  LRESULT LVar2;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    iVar1 = FUN_0003cefc();
    LVar2 = *(LRESULT *)(iVar1 + 0x1c);
  }
  else {
    iVar1 = FUN_0002b948();
    LVar2 = SendMessageW(*(HWND *)(iVar1 + 0x1c),0x130b,0,0);
  }
  return LVar2;
}


// 0003cf88 FUN_0003cf88

void FUN_0003cf88(int *param_1)

{
  param_1[0xc] = 2;
  if (param_1[0x23] == 0) {
    FUN_0002ff50();
  }
  else {
    (**(code **)(*param_1 + 0x54))();
  }
  return;
}


// 0003cfbc FUN_0003cfbc

void FUN_0003cfbc(int param_1,uint param_2)

{
  *(undefined4 *)(param_1 + 0x30) = 2;
  if (((param_2 & 0xfff0) == 0xf060) && (*(int *)(param_1 + 0x8c) != 0)) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0x10,0,0);
  }
  else {
    FUN_0002ff50();
  }
  return;
}


// 0003d010 FUN_0003d010

void FUN_0003d010(int *param_1)

{
  (**(code **)(*param_1 + 0xb8))();
  return;
}


// 0003d028 FUN_0003d028

void FUN_0003d028(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_0003cf08();
  FUN_0002fd40(iVar1,*(undefined4 *)(iVar1 + 0x1c),0x365,param_2,param_3);
  return;
}


// 0003d05c FUN_0003d05c

undefined4 FUN_0003d05c(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_1c;
  
  iVar1 = FUN_00032444(param_3,&local_1c);
  if (iVar1 == 0) {
    if (DAT_002de53c == 0) {
      uVar2 = 0;
      if (param_3 != 0) {
        uVar2 = *(undefined4 *)(param_3 + 0x1c);
      }
      iVar1 = FUN_000329ac(*(undefined4 *)(param_2 + 4),uVar2,param_4,DAT_002de504,DAT_002de514);
      local_1c = DAT_002de504;
      if (iVar1 == 0) {
        local_1c = FUN_0002ff50(param_1);
      }
    }
    else {
      local_1c = FUN_000328f0(param_1,param_2,param_3,param_4);
    }
  }
  return local_1c;
}


// 0003d1bc FUN_0003d1bc

void FUN_0003d1bc(int param_1,int param_2,int param_3,int param_4,int param_5,COLORREF param_6)

{
  RECT local_24;
  
  SetBkColor(*(HDC *)(param_1 + 4),param_6);
  local_24.right = param_2 + param_4;
  local_24.bottom = param_3 + param_5;
  local_24.left = param_2;
  local_24.top = param_3;
  ExtTextOutW(*(HDC *)(param_1 + 4),0,0,2,&local_24,(LPCWSTR)0x0,0,(INT *)0x0);
  return;
}


// 0003d294 FUN_0003d294

void FUN_0003d294(undefined1 *param_1)

{
  *(undefined4 *)(param_1 + 0xc) = g_afxEmptyString;
  *(undefined4 *)(param_1 + 0x10) = g_afxEmptyString;
  *param_1 = 0x70;
  param_1[1] = 0x1f;
  param_1[2] = 4;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0x18) = 1;
  return;
}


// 0003d300 FUN_0003d300

void FUN_0003d300(undefined1 *param_1)

{
  *param_1 = 0x70;
  param_1[1] = 0x1f;
  param_1[2] = 4;
  param_1[3] = 0;
  CString_Dtor((CString *)(param_1 + 0x10));
  CString_Dtor((CString *)(param_1 + 0xc));
  return;
}


// 0003d340 FUN_0003d340

undefined1 * FUN_0003d340(undefined1 *param_1)

{
  FUN_00037274(param_1,u_EDIT_00044350,0);
  *param_1 = 0x78;
  param_1[1] = 0x1f;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0x50) = 0x20;
  return param_1;
}


// 0003d3bc FUN_0003d3bc

void FUN_0003d3bc(undefined1 *param_1)

{
  *param_1 = 0x78;
  param_1[1] = 0x1f;
  param_1[2] = 4;
  param_1[3] = 0;
  free(*(void **)(param_1 + 0x54));
  CString_Dtor((CString *)(param_1 + 0x48));
  FUN_00036de8(param_1);
  return;
}


// 0003d514 FUN_0003d514

void FUN_0003d514(undefined4 param_1)

{
  int iVar1;
  BOOL BVar2;
  
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  if ((*(int *)(iVar1 + 4) != 0) &&
     (BVar2 = IsWindow(*(HWND *)(*(int *)(iVar1 + 4) + 0x1c)), BVar2 != 0)) {
    SendMessageW(*(HWND *)(*(int *)(iVar1 + 4) + 0x1c),0x10,0,0);
  }
  *(undefined4 *)(iVar1 + 4) = 0;
  FUN_00036e98(param_1);
  return;
}


// 0003d578 FUN_0003d578

void FUN_0003d578(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = FUN_00033b4c();
  uVar2 = FUN_00033b14(param_1);
                    /* WARNING: Could not recover jumptable at 0x0002ccdc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  AdjustWindowRectEx(param_2,uVar2 & 0xffcfffff,0,uVar1 & 0xfffffdff);
  return;
}


// 0003d5b4 FUN_0003d5b4

void FUN_0003d5b4(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  uint local_10;
  
  if ((*(uint *)(param_2 + 0x14) & 1) == 0) {
    uVar1 = FUN_0003daf4();
    FUN_0002aaa4(param_2,uVar1);
    FUN_0003d6d8(param_1,param_2);
  }
  else {
    FUN_0002ab4c(param_2,&local_10);
    if (0xfffff < local_10) {
      FUN_00035c3c(5,0);
    }
    FUN_0003d630(param_1,param_2,local_10);
  }
  return;
}


// 0003d630 FUN_0003d630

void FUN_0003d630(int param_1,CArchive *param_2,int param_3)

{
  LPCWSTR lpString;
  uint uVar1;
  BOOL BVar2;
  int iVar3;
  
  lpString = LocalAlloc(2,(param_3 + 1) * 2);
  if (lpString == (LPCWSTR)0x0) {
    FUN_0002d3cc();
  }
  uVar1 = CArchive_Read(param_2,lpString,param_3 * 2);
  if (uVar1 != param_3 * 2) {
    LocalFree(lpString);
    FUN_00035c3c(3,0);
  }
  lpString[param_3] = L'\0';
  BVar2 = SetWindowTextW(*(HWND *)(param_1 + 0x1c),lpString);
  LocalFree(lpString);
  if ((BVar2 == 0) || (iVar3 = GetWindowTextLengthW(*(HWND *)(param_1 + 0x1c)), iVar3 < param_3)) {
    FUN_0002d3cc();
  }
  free(*(void **)(param_1 + 0x54));
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  return;
}


// 0003d6d8 FUN_0003d6d8

void FUN_0003d6d8(undefined4 param_1,CArchive *param_2)

{
  void *pvVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_54 [56];
  
  pvVar1 = (void *)FUN_0003da58();
  iVar2 = FUN_0003daf4(param_1);
  FUN_0002f060(auStack_54);
  iVar3 = setjmp(auStack_54);
  if (iVar3 == 0) {
    CArchive_Write(param_2,pvVar1,iVar2 << 1);
  }
  else {
    FUN_0003daf0(param_1);
    FUN_0002f108(0);
  }
  FUN_0002f0c0();
  FUN_0003daf0(param_1);
  return;
}


// 0003d75c FUN_0003d75c

int FUN_0003d75c(int param_1,int param_2,int param_3)

{
  short *psVar1;
  
  for (psVar1 = (short *)(param_1 + param_3 * 2);
      (psVar1 < (short *)(param_1 + param_2 * 2) && (*psVar1 != 0xd)); psVar1 = psVar1 + 1) {
  }
  return (int)psVar1 - param_1 >> 1;
}


// 0003d78c FUN_0003d78c

void FUN_0003d78c(int param_1,undefined4 *param_2)

{
  int local_10;
  int local_c;
  
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_c,(LPARAM)&local_10);
  (**(code **)*param_2)(param_2,local_c != local_10);
  return;
}


// 0003d7dc FUN_0003d7dc

void FUN_0003d7dc(undefined4 param_1,undefined4 *param_2)

{
  BOOL BVar1;
  undefined4 uVar2;
  
  BVar1 = IsClipboardFormatAvailable(1);
  if ((BVar1 == 0) && (BVar1 = IsClipboardFormatAvailable(7), BVar1 == 0)) {
    BVar1 = IsClipboardFormatAvailable(0xd);
    uVar2 = 0;
    if (BVar1 == 0) goto LAB_0003d81c;
  }
  uVar2 = 1;
LAB_0003d81c:
  (**(code **)*param_2)(param_2,uVar2);
  return;
}


// 0003d834 FUN_0003d834

void FUN_0003d834(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = FUN_00033c20();
  (**(code **)*param_2)(param_2,iVar1 != 0);
  return;
}


// 0003d864 FUN_0003d864

void FUN_0003d864(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  iVar2 = FUN_00033c20(param_1);
  if ((iVar2 == 0) || (uVar3 = 1, *(int *)(*(int *)(iVar1 + 0xc) + -8) == 0)) {
    uVar3 = 0;
  }
  (**(code **)*param_2)(param_2,uVar3);
  return;
}


// 0003d8c8 FUN_0003d8c8

void FUN_0003d8c8(int param_1,undefined4 *param_2)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageW(*(HWND *)(param_1 + 0x1c),0xc6,0,0);
  (**(code **)*param_2)(param_2,LVar1);
  return;
}


// 0003d900 FUN_0003d900

undefined4 FUN_0003d900(int param_1)

{
  (**(code **)(**(int **)(param_1 + 0x44) + 0x58))(*(int **)(param_1 + 0x44),1);
  return 0;
}


// 0003d950 FUN_0003d950

void FUN_0003d950(int param_1)

{
  int iVar1;
  undefined4 local_14;
  undefined1 auStack_10 [4];
  
  SendMessageW(*(HWND *)(param_1 + 0x1c),0x302,0,0);
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  if ((*(int *)(iVar1 + 4) != 0) && (*(int *)(*(int *)(iVar1 + 4) + 0x2a4) != 0)) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_14,(LPARAM)auStack_10);
    *(undefined4 *)(iVar1 + 0x20) = local_14;
    *(undefined4 *)(iVar1 + 0x24) = 1;
  }
  return;
}


// 0003d9fc FUN_0003d9fc

void FUN_0003d9fc(int param_1)

{
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xb1,0,-1);
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xb7,0,0);
  return;
}


// 0003da30 FUN_0003da30

undefined4 FUN_0003da30(int param_1)

{
  FUN_0002ff50();
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xcb,1,param_1 + 0x50);
  return 0;
}


// 0003da58 FUN_0003da58

undefined4 FUN_0003da58(int param_1)

{
  LRESULT LVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  if ((*(int *)(param_1 + 0x54) == 0) ||
     (LVar1 = SendMessageW(*(HWND *)(param_1 + 0x1c),0xb8,0,0), LVar1 != 0)) {
    iVar2 = FUN_00033c20(param_1);
    uVar4 = iVar2 + 1;
    if (*(uint *)(param_1 + 0x58) < uVar4) {
      free(*(void **)(param_1 + 0x54));
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(undefined4 *)(param_1 + 0x58) = 0;
      uVar3 = operator_new(uVar4 * 2);
      *(uint *)(param_1 + 0x58) = uVar4;
      *(undefined4 *)(param_1 + 0x54) = uVar3;
    }
    FUN_00033bec(param_1,*(undefined4 *)(param_1 + 0x54),uVar4);
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb9,0,0);
  }
  return *(undefined4 *)(param_1 + 0x54);
}


// 0003daf0 FUN_0003daf0

void FUN_0003daf0(void)

{
  return;
}


// 0003daf4 FUN_0003daf4

size_t FUN_0003daf4(undefined4 param_1)

{
  wchar_t *_Str;
  size_t sVar1;
  
  _Str = (wchar_t *)FUN_0003da58();
  sVar1 = wcslen(_Str);
  FUN_0003daf0(param_1);
  return sVar1;
}


// 0003db18 FUN_0003db18

void FUN_0003db18(int param_1,CString *param_2)

{
  int iVar1;
  int iVar2;
  wchar_t *_Dst;
  size_t sVar3;
  int local_1c;
  undefined4 local_18;
  
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_1c,(LPARAM)&local_18);
  iVar1 = FUN_0003da58(param_1);
  iVar2 = FUN_0003d75c(iVar1,local_18,local_1c);
  sVar3 = iVar2 - local_1c;
  _Dst = CString_GetBuffer(param_2,sVar3);
  memmove(_Dst,(void *)(iVar1 + local_1c * 2),sVar3 * 2);
  CString_ReleaseBuffer(param_2,sVar3);
  FUN_0003daf0(param_1);
  return;
}


// 0003dba4 FUN_0003dba4

void FUN_0003dba4(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  iVar2 = FUN_0003e2f0(param_1,*(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x18),
                       *(undefined4 *)(iVar1 + 0x14));
  if (iVar2 == 0) {
    (**(code **)(*param_1 + 0xe0))(param_1,*(undefined4 *)(iVar1 + 0xc));
  }
  return;
}


// 0003dd44 FUN_0003dd44

void FUN_0003dd44(int *param_1,wchar_t *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  CString_AssignW((CString *)(iVar1 + 0xc),param_2);
  *(undefined4 *)(iVar1 + 0x14) = param_4;
  *(undefined4 *)(iVar1 + 0x18) = param_3;
  iVar2 = FUN_0003e2f0(param_1,*(undefined4 *)(iVar1 + 0xc),param_3,param_4);
  if (iVar2 == 0) {
    (**(code **)(*param_1 + 0xe0))(param_1,*(undefined4 *)(iVar1 + 0xc));
  }
  return;
}


// 0003ddb8 FUN_0003ddb8

void FUN_0003ddb8(int param_1,wchar_t *param_2,undefined4 param_3,undefined4 param_4,
                 wchar_t *param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint local_28;
  int local_24;
  
  iVar2 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  CString_AssignW((CString *)(iVar2 + 0xc),param_2);
  CString_AssignW((CString *)(iVar2 + 0x10),param_5);
  *(undefined4 *)(iVar2 + 0x14) = param_4;
  *(undefined4 *)(iVar2 + 0x18) = param_3;
  iVar3 = FUN_0003dff4(param_1);
  if (iVar3 != 0) {
    uVar4 = *(uint *)(iVar2 + 0x20);
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_28,(LPARAM)&local_24);
    uVar1 = local_28;
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xc2,0,*(LPARAM *)(iVar2 + 0x10));
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_28,(LPARAM)&local_24);
    if ((uVar4 == uVar1) && (uVar4 == local_28)) {
      *(undefined4 *)(iVar2 + 0x24) = 1;
    }
    if (uVar1 < uVar4) {
      *(uint *)(iVar2 + 0x20) = (local_28 - local_24) + *(int *)(iVar2 + 0x20);
    }
    if (((*(int *)(iVar2 + 0x24) == 0) && (uVar1 < uVar4)) && (uVar4 < local_28)) {
      *(uint *)(iVar2 + 0x20) = local_28;
    }
    FUN_0003e2f0(param_1,*(undefined4 *)(iVar2 + 0xc),param_3,param_4);
  }
  return;
}


// 0003dec4 FUN_0003dec4

void FUN_0003dec4(int param_1,wchar_t *param_2,wchar_t *param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint local_28;
  int local_24;
  
  iVar2 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  CString_AssignW((CString *)(iVar2 + 0xc),param_2);
  CString_AssignW((CString *)(iVar2 + 0x10),param_3);
  iVar5 = *(int *)(iVar2 + 0x24);
  *(undefined4 *)(iVar2 + 0x14) = param_4;
  *(undefined4 *)(iVar2 + 0x18) = 1;
  iVar3 = FUN_0003dff4(param_1);
  if (iVar3 != 0) goto LAB_0003df40;
  iVar3 = FUN_0003e244(param_1,*(undefined4 *)(iVar2 + 0xc),*(undefined4 *)(iVar2 + 0x14));
  while( true ) {
    if (iVar3 == 0) {
      return;
    }
LAB_0003df40:
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_28,(LPARAM)&local_24);
    iVar3 = local_24;
    uVar1 = local_28;
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xc2,0,*(LPARAM *)(iVar2 + 0x10));
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_28,(LPARAM)&local_24);
    uVar4 = *(uint *)(iVar2 + 0x20);
    if (((iVar5 != 0) && (uVar4 == local_28)) && (uVar4 == uVar1)) {
      *(undefined4 *)(iVar2 + 0x24) = 1;
    }
    if (uVar1 < uVar4) {
      *(uint *)(iVar2 + 0x20) = (uVar4 - iVar3) + local_28;
    }
    if (((iVar5 == 0) && (uVar1 < uVar4)) && (uVar4 < local_28)) break;
    iVar3 = FUN_0003e2f0(param_1,*(undefined4 *)(iVar2 + 0xc),1,param_4);
  }
  return;
}


// 0003dff4 FUN_0003dff4

undefined4 FUN_0003dff4(int *param_1)

{
  int iVar1;
  int iVar2;
  int local_14;
  int local_10;
  
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  SendMessageW((HWND)param_1[7],0xb0,(WPARAM)&local_10,(LPARAM)&local_14);
  if (local_10 == local_14) {
    iVar2 = FUN_0003e2f0(param_1,*(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x18),
                         *(undefined4 *)(iVar1 + 0x14));
    if (iVar2 == 0) {
      (**(code **)(*param_1 + 0xe0))(param_1,*(undefined4 *)(iVar1 + 0xc));
    }
  }
  else {
    iVar2 = FUN_0003e244(param_1,*(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x14));
    if (iVar2 != 0) {
      return 1;
    }
    iVar2 = FUN_0003e2f0(param_1,*(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar1 + 0x18),
                         *(undefined4 *)(iVar1 + 0x14));
    if (iVar2 == 0) {
      (**(code **)(*param_1 + 0xe0))(param_1,*(undefined4 *)(iVar1 + 0xc));
    }
  }
  return 0;
}


// 0003e0c8 FUN_0003e0c8

undefined4 FUN_0003e0c8(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  CString *this;
  CString local_30;
  CString local_2c;
  CString local_28;
  CString local_24;
  CString local_20;
  
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  iVar2 = FUN_0002d62c(param_3);
  uVar3 = *(uint *)(iVar2 + 0x84);
  if ((uVar3 & 0x40) == 0) {
    if ((uVar3 & 8) == 0) {
      if ((uVar3 & 0x10) == 0) {
        if ((uVar3 & 0x20) == 0) {
          return 0;
        }
        CString_CtorW(&local_20,*(wchar_t **)(iVar2 + 0x8c));
        CString_CtorW(&local_24,*(wchar_t **)(iVar2 + 0x88));
        (**(code **)(*param_1 + 0xdc))(param_1,local_24.str,local_20.str,(uVar3 & 4) != 0);
        CString_Dtor(&local_24);
        this = &local_20;
      }
      else {
        CString_CtorW(&local_28,*(wchar_t **)(iVar2 + 0x8c));
        uVar3 = *(uint *)(iVar2 + 0x84);
        CString_CtorW(&local_2c,*(wchar_t **)(iVar2 + 0x88));
        (**(code **)(*param_1 + 0xd8))
                  (param_1,local_2c.str,(uVar3 & 1) != 0,(uVar3 & 4) != 0,local_28.str);
        CString_Dtor(&local_2c);
        this = &local_28;
      }
    }
    else {
      CString_CtorW(&local_30,*(wchar_t **)(iVar2 + 0x88));
      (**(code **)(*param_1 + 0xd4))(param_1,local_30.str,(uVar3 & 1) != 0,(uVar3 & 4) != 0);
      this = &local_30;
    }
    CString_Dtor(this);
  }
  else {
    *(undefined4 *)(iVar1 + 4) = 0;
  }
  return 0;
}


// 0003e244 FUN_0003e244

bool FUN_0003e244(int param_1,wchar_t *param_2,int param_3)

{
  size_t sVar1;
  int iVar2;
  bool bVar3;
  CString local_20;
  int local_1c;
  int local_18;
  
  sVar1 = wcslen(param_2);
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_18,(LPARAM)&local_1c);
  if (sVar1 == local_1c - local_18) {
    local_20.str = g_afxEmptyString;
    FUN_0003db18(param_1,&local_20);
    if (param_3 == 0) {
      iVar2 = lstrcmpiW(param_2,local_20.str);
    }
    else {
      iVar2 = lstrcmpW(param_2,local_20.str);
    }
    bVar3 = iVar2 == 0;
    CString_Dtor(&local_20);
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}


// 0003e2f0 FUN_0003e2f0

undefined4 FUN_0003e2f0(int param_1,wchar_t *param_2,int param_3,int param_4)

{
  WPARAM wParam;
  undefined1 uVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  code *pcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  size_t sVar9;
  code *pcVar10;
  code *pcVar11;
  code *pcVar12;
  code *pcVar13;
  int iVar14;
  code *pcVar15;
  code *local_4c;
  code *local_48;
  uint local_44;
  size_t local_40;
  code *local_3c;
  int local_38;
  int local_34;
  
  iVar4 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  pcVar15 = *(code **)(iVar4 + 0x20);
  iVar14 = *(int *)(iVar4 + 0x24);
  local_38 = iVar14;
  pcVar5 = (code *)FUN_0003daf4(param_1);
  SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_4c,(LPARAM)&local_3c);
  pcVar13 = local_4c;
  pcVar10 = (code *)0x1;
  if (param_3 == 0) {
    pcVar10 = (code *)0xffffffff;
  }
  iVar6 = FUN_0003f4f4();
  FUN_0002f4ec(*(undefined4 *)(iVar6 + 4));
  uVar7 = FUN_0003da58(param_1);
  pcVar11 = pcVar5;
  local_44 = uVar7;
  if ((int)pcVar10 < 0) {
    if ((pcVar13 == pcVar15) && (iVar14 == 0)) goto LAB_0003e628;
    uVar8 = (int)pcVar13 * 2 + uVar7;
    if ((uVar7 < uVar8) && (uVar8 != 2)) {
      if (uVar7 < uVar8) {
        iVar6 = uVar8 - 2;
      }
      else {
        iVar6 = 0;
      }
      pcVar11 = pcVar13 + -((int)(((int)pcVar13 * 2 - iVar6) + uVar7) >> 1);
    }
  }
  else {
    pcVar11 = pcVar13;
    if (((local_4c != local_3c) && (iVar6 = FUN_0003e244(param_1,param_2,param_4), iVar6 != 0)) &&
       (iVar14 == 0)) {
      pcVar11 = pcVar10 + (int)pcVar13;
    }
  }
  if ((pcVar11 != pcVar15) || (iVar14 != 0)) {
    sVar9 = wcslen(param_2);
    local_48 = pcVar11 + (sVar9 - 1);
    if ((pcVar5 <= pcVar11 + (sVar9 - 1)) &&
       ((local_48 = pcVar10, 0 < (int)pcVar10 && (pcVar15 <= pcVar11)))) {
      pcVar11 = (code *)0x0;
    }
    if (param_4 != 0) {
      local_48 = lstrcmpW;
    }
    uVar8 = uVar7 + (int)pcVar11 * 2;
    if (param_4 == 0) {
      local_48 = lstrcmpiW;
    }
    bVar2 = false;
    local_40 = sVar9;
    do {
      if ((pcVar11 == pcVar15) && (local_38 == 0)) {
        FUN_0003daf0(param_1);
        goto LAB_0003e628;
      }
      if ((int)pcVar10 < 1) {
        if (pcVar11 <= pcVar15) {
          if (!bVar2) {
            if ((pcVar15 == (code *)0x0) || (bVar3 = true, pcVar15 == pcVar5)) {
              bVar3 = false;
            }
            pcVar12 = pcVar10;
            if (pcVar11 == (code *)0x0) {
              pcVar12 = pcVar15;
            }
            pcVar13 = pcVar11 + 1;
            if (pcVar11 == (code *)0x0 && pcVar12 == (code *)0x0) {
              uVar8 = uVar7 + (int)pcVar5 * 2;
              pcVar11 = pcVar5;
              pcVar13 = pcVar5;
            }
            if (pcVar13 == (code *)0x0) {
              uVar8 = uVar7 + (int)pcVar5 * 2;
              pcVar11 = pcVar5;
            }
            goto LAB_0003e4fc;
          }
          break;
        }
        if (bVar2) {
          pcVar11 = pcVar5;
        }
        if (bVar2) {
          uVar8 = uVar7 + (int)pcVar5 * 2;
          bVar2 = false;
        }
        pcVar13 = pcVar11 + (1 - (int)pcVar15);
LAB_0003e58c:
        bVar3 = false;
      }
      else {
        if (pcVar11 < pcVar15) {
          if (bVar2) {
            pcVar11 = (code *)0x0;
            bVar2 = false;
            uVar8 = uVar7;
          }
          pcVar13 = pcVar15 + -(int)pcVar11;
          goto LAB_0003e58c;
        }
        if (bVar2) break;
        if ((pcVar15 == (code *)0x0) || (bVar3 = true, pcVar15 == pcVar5)) {
          bVar3 = false;
        }
        pcVar12 = pcVar10;
        if (pcVar11 == pcVar5) {
          pcVar12 = pcVar15;
        }
        pcVar13 = pcVar5 + -(int)pcVar11;
        if (pcVar11 == pcVar5 && pcVar12 == pcVar5) {
          pcVar11 = (code *)0x0;
          uVar8 = uVar7;
          pcVar13 = pcVar5;
        }
        if (pcVar13 == (code *)0x0) {
          pcVar11 = (code *)0x0;
          uVar8 = uVar7;
        }
LAB_0003e4fc:
        bVar2 = true;
      }
      if (pcVar13 != (code *)0x0) {
        iVar14 = sVar9 * 2;
        pcVar12 = pcVar11;
        do {
          uVar1 = *(undefined1 *)(iVar14 + uVar8);
          *(undefined1 *)(iVar14 + uVar8) = 0;
          local_34 = (*local_48)(uVar8,param_2);
          *(undefined1 *)(iVar14 + uVar8) = uVar1;
          if (local_34 == 0) {
            FUN_0003daf0(param_1);
            wParam = (int)(uVar8 - local_44) >> 1;
            FUN_00033e00(param_1);
            SendMessageW(*(HWND *)(param_1 + 0x1c),0xb1,wParam,wParam + local_40);
            SendMessageW(*(HWND *)(param_1 + 0x1c),0xb7,0,0);
            *(undefined4 *)(iVar4 + 0x24) = 0;
            iVar4 = FUN_0003f4f4();
            FUN_0002f510(*(undefined4 *)(iVar4 + 4));
            return 1;
          }
          pcVar13 = pcVar13 + -1;
          *(undefined1 *)(iVar14 + uVar8) = uVar1;
          uVar8 = uVar8 + (int)pcVar10 * 2;
          if (((0 < (int)pcVar10) || (pcVar11 = pcVar5, pcVar12 != (code *)0x0)) &&
             (pcVar11 = pcVar10 + (int)pcVar12, pcVar5 <= pcVar10 + (int)pcVar12)) {
            pcVar11 = (code *)0x0;
          }
          sVar9 = local_40;
          pcVar12 = pcVar11;
          uVar7 = local_44;
        } while (pcVar13 != (code *)0x0);
      }
    } while (bVar3);
    FUN_0003daf0(param_1);
    *(undefined4 *)(iVar4 + 0x24) = 0;
  }
LAB_0003e628:
  iVar4 = FUN_0003f4f4();
  FUN_0002f510(*(undefined4 *)(iVar4 + 4));
  return 0;
}


// 0003e6c0 FUN_0003e6c0

void FUN_0003e6c0(void)

{
  int iVar1;
  int iVar2;
  CString local_c;
  
  MessageBeep(0);
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  iVar2 = *(int *)(iVar1 + 4);
  if (iVar2 != 0) {
    if (*(int *)(iVar2 + 0x2a4) == 0) {
      *(undefined4 *)(iVar2 + 0xa0) = 0;
      local_c.str = g_afxEmptyString;
      iVar2 = FUN_0002ee30(&local_c,0xff01);
      if (iVar2 == 0) {
        FUN_00037b9c(0xff01,0,0xffffffff);
      }
      else {
        FUN_00031c10(*(undefined4 *)(iVar1 + 4),local_c.str,0,0);
      }
      *(undefined4 *)(iVar1 + 0x24) = 1;
      CString_Dtor(&local_c);
    }
    else {
      FUN_00037b9c(0xff00,0,0xffffffff);
      SendMessageW(*(HWND *)(*(int *)(iVar1 + 4) + 0x1c),0x10,0,0);
    }
  }
  return;
}


// 0003e7a0 FUN_0003e7a0

void FUN_0003e7a0(int param_1)

{
  int iVar1;
  undefined4 local_14;
  undefined1 auStack_10 [4];
  
  FUN_0002ff50();
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  if ((*(int *)(iVar1 + 4) != 0) && (*(int *)(*(int *)(iVar1 + 4) + 0x2a4) != 0)) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_14,(LPARAM)auStack_10);
    *(undefined4 *)(iVar1 + 0x20) = local_14;
    *(undefined4 *)(iVar1 + 0x24) = 1;
  }
  return;
}


// 0003e80c FUN_0003e80c

void FUN_0003e80c(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_18;
  undefined1 auStack_14 [4];
  
  FUN_0002ff50();
  iVar1 = FUN_0003f014(&DAT_002de574,&DAT_0003fc94);
  if (((*(int *)(iVar1 + 4) != 0) && (*(int *)(*(int *)(iVar1 + 4) + 0x2a4) != 0)) &&
     (((param_2 == 0x25 || (((param_2 == 0x27 || (param_2 == 0x26)) || (param_2 == 0x28)))) ||
      (((param_2 == 0x24 || (param_2 == 0x23)) || (param_2 == 0x2e)))))) {
    SendMessageW(*(HWND *)(param_1 + 0x1c),0xb0,(WPARAM)&local_18,(LPARAM)auStack_14);
    *(undefined4 *)(iVar1 + 0x20) = local_18;
    *(undefined4 *)(iVar1 + 0x24) = 1;
  }
  return;
}


// 0003e93c FUN_0003e93c

void FUN_0003e93c(void)

{
  FUN_0002efb0(&DAT_002dc648,0);
  DAT_002dc654 = 0;
  DAT_002dc658 = 0;
  DAT_002dc648 = &DAT_00040088;
  DAT_002dc75c = 0xf023;
  return;
}


// 0003e9c0 FUN_0003e9c0

void FUN_0003e9c0(void)

{
  FUN_0002efb0(&DAT_002dc530,0);
  DAT_002dc53c = 0;
  DAT_002dc540 = 0;
  DAT_002dc530 = &PTR_LAB_000400a0;
  DAT_002dc644 = 0xf021;
  return;
}


// 0003ea4c FUN_0003ea4c

int FUN_0003ea4c(void)

{
  if (DAT_002dc760 == 0) {
    DAT_002dc760 = 1;
    DAT_002dc764 = 0;
    InitializeCriticalSection((LPCRITICAL_SECTION)&DAT_002dc8c0);
  }
  return DAT_002dc760;
}


// 0003ea90 FUN_0003ea90

void FUN_0003ea90(int param_1)

{
  int *piVar1;
  
  if (DAT_002dc760 == 0) {
    FUN_0003ea4c();
  }
  if (DAT_002dc764 == 0) {
    piVar1 = (int *)(&DAT_002dc8d8 + param_1 * 4);
    if (*piVar1 == 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_002dc8c0);
      if (*piVar1 == 0) {
        InitializeCriticalSection((LPCRITICAL_SECTION)(&DAT_002dc768 + param_1 * 0x14));
        *piVar1 = *piVar1 + 1;
      }
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_002dc8c0);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)(&DAT_002dc768 + param_1 * 0x14));
  }
  return;
}


// 0003eb2c FUN_0003eb2c

void FUN_0003eb2c(int param_1)

{
  if (DAT_002dc764 == 0) {
    LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_002dc768 + param_1 * 0x14));
  }
  return;
}


// 0003eb5c FUN_0003eb5c

void FUN_0003eb5c(int *param_1,int param_2)

{
  *(int *)(param_1[1] + param_2) = *param_1;
  *param_1 = param_2;
  return;
}


// 0003eb70 FUN_0003eb70

undefined4 FUN_0003eb70(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *param_1;
  if (iVar1 == 0) {
    return 0;
  }
  if (iVar1 == param_2) {
    *param_1 = *(int *)(param_1[1] + param_2);
  }
  else {
    if (iVar1 == 0) {
      return 0;
    }
    iVar2 = param_1[1];
    do {
      iVar3 = *(int *)(iVar2 + iVar1);
      if (iVar3 == param_2) break;
      iVar1 = iVar3;
    } while (iVar3 != 0);
    if (iVar1 == 0) {
      return 0;
    }
    *(undefined4 *)(iVar2 + iVar1) = *(undefined4 *)(iVar2 + param_2);
  }
  return 1;
}


// 0003ebd8 FUN_0003ebd8

HLOCAL FUN_0003ebd8(SIZE_T param_1)

{
  HLOCAL pvVar1;
  
  pvVar1 = LocalAlloc(0x40,param_1);
  if (pvVar1 == (HLOCAL)0x0) {
    FUN_0002d3cc();
  }
  return pvVar1;
}


// 0003ebf8 FUN_0003ebf8

void FUN_0003ebf8(HLOCAL param_1)

{
  if (param_1 != (HLOCAL)0x0) {
    LocalFree(param_1);
  }
  return;
}


// 0003ec08 FUN_0003ec08

int * FUN_0003ec08(int *param_1)

{
  int iVar1;
  
  param_1[5] = 0;
  param_1[6] = 0;
  param_1[6] = 4;
  param_1[1] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[2] = 1;
  iVar1 = TlsCall(0,0);
  *param_1 = iVar1;
  if (iVar1 == -1) {
    FUN_0002d3cc();
  }
  InitializeCriticalSection((LPCRITICAL_SECTION)(param_1 + 7));
  return param_1;
}


// 0003ec68 FUN_0003ec68

int FUN_0003ec68(int param_1)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  LPCRITICAL_SECTION lpCriticalSection;
  
  lpCriticalSection = (LPCRITICAL_SECTION)(param_1 + 0x1c);
  EnterCriticalSection(lpCriticalSection);
  iVar1 = *(int *)(param_1 + 4);
  iVar4 = *(int *)(param_1 + 8);
  if ((iVar1 <= iVar4) || ((*(uint *)(*(int *)(param_1 + 0x10) + iVar4 * 8) & 1) != 0)) {
    iVar4 = 1;
    if (1 < iVar1) {
      puVar3 = *(uint **)(param_1 + 0x10);
      do {
        puVar3 = puVar3 + 2;
        if ((*puVar3 & 1) == 0) break;
        iVar4 = iVar4 + 1;
      } while (iVar4 < iVar1);
      if (iVar4 < iVar1) goto LAB_0003ed34;
    }
    iVar1 = iVar1 + 0x20;
    if (*(int *)(param_1 + 0x10) == 0) {
      iVar2 = FUN_0002ac34(2);
    }
    else {
      iVar2 = FUN_0002ac50(*(int *)(param_1 + 0x10),iVar1 * 8,2);
    }
    if (iVar2 == 0) {
      LeaveCriticalSection(lpCriticalSection);
      FUN_0002d3cc();
    }
    memset((void *)(iVar2 + *(int *)(param_1 + 4) * 8),0,(iVar1 - *(int *)(param_1 + 4)) * 8);
    *(int *)(param_1 + 4) = iVar1;
    *(int *)(param_1 + 0x10) = iVar2;
  }
LAB_0003ed34:
  if (*(int *)(param_1 + 0xc) <= iVar4) {
    *(int *)(param_1 + 0xc) = iVar4 + 1;
  }
  puVar3 = (uint *)(*(int *)(param_1 + 0x10) + iVar4 * 8);
  *puVar3 = *puVar3 | 1;
  *(int *)(param_1 + 8) = iVar4 + 1;
  LeaveCriticalSection(lpCriticalSection);
  return iVar4;
}


// 0003ed6c FUN_0003ed6c

void FUN_0003ed6c(int param_1,int param_2)

{
  undefined4 *puVar1;
  uint *puVar2;
  int iVar3;
  
  EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x1c));
  for (iVar3 = *(int *)(param_1 + 0x14); iVar3 != 0; iVar3 = *(int *)(iVar3 + 4)) {
    if (param_2 < *(int *)(iVar3 + 8)) {
      puVar1 = *(undefined4 **)(*(int *)(iVar3 + 0xc) + param_2 * 4);
      if (puVar1 != (undefined4 *)0x0) {
        (**(code **)*puVar1)(puVar1,1);
      }
      *(undefined4 *)(*(int *)(iVar3 + 0xc) + param_2 * 4) = 0;
    }
  }
  puVar2 = (uint *)(*(int *)(param_1 + 0x10) + param_2 * 8);
  *puVar2 = *puVar2 & 0xfffffffe;
  LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x1c));
  return;
}


// 0003edf0 FUN_0003edf0

void FUN_0003edf0(DWORD *param_1,int param_2,int param_3)

{
  undefined1 *lpTlsValue;
  HLOCAL pvVar1;
  
  lpTlsValue = TlsGetValue(*param_1);
  if (lpTlsValue == (undefined1 *)0x0) {
    lpTlsValue = (undefined1 *)FUN_0003ebd8(0x10);
    if (lpTlsValue == (undefined1 *)0x0) {
      lpTlsValue = (undefined1 *)0x0;
    }
    else {
      *lpTlsValue = 0xb4;
      lpTlsValue[1] = 0;
      lpTlsValue[2] = 4;
      lpTlsValue[3] = 0;
    }
    *(undefined4 *)(lpTlsValue + 8) = 0;
    *(undefined4 *)(lpTlsValue + 0xc) = 0;
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 7));
    FUN_0003eb5c(param_1 + 5,lpTlsValue);
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 7));
  }
  else if ((param_2 < *(int *)(lpTlsValue + 8)) || (param_3 == 0)) goto LAB_0003eefc;
  if (*(HLOCAL *)(lpTlsValue + 0xc) == (HLOCAL)0x0) {
    pvVar1 = LocalAlloc(0,param_1[3] << 2);
  }
  else {
    pvVar1 = LocalReAlloc(*(HLOCAL *)(lpTlsValue + 0xc),param_1[3] << 2,2);
  }
  *(HLOCAL *)(lpTlsValue + 0xc) = pvVar1;
  if (pvVar1 == (HLOCAL)0x0) {
    FUN_0002d3cc();
  }
  memset((void *)(*(int *)(lpTlsValue + 0xc) + *(int *)(lpTlsValue + 8) * 4),0,
         (param_1[3] - *(int *)(lpTlsValue + 8)) * 4);
  *(DWORD *)(lpTlsValue + 8) = param_1[3];
  TlsSetValue(*param_1,lpTlsValue);
LAB_0003eefc:
  *(int *)(*(int *)(lpTlsValue + 0xc) + param_2 * 4) = param_3;
  return;
}


// 0003ef08 FUN_0003ef08

undefined4 FUN_0003ef08(undefined4 param_1,uint param_2)

{
  if ((param_2 & 1) != 0) {
    FUN_0003ebf8();
  }
  return param_1;
}


// 0003ef20 FUN_0003ef20

/* WARNING: Removing unreachable block (ram,0x0003ef78) */

int FUN_0003ef20(int *param_1,code *param_2)

{
  int iVar1;
  LPVOID pvVar2;
  
  if ((*param_1 == 0) || ((DAT_002dc920 != (DWORD *)0x0 && ((int)DAT_002dc920[3] <= *param_1)))) {
    if (DAT_002dc920 == (DWORD *)0x0) {
      DAT_002dc920 = (DWORD *)FUN_0003ec08();
    }
    iVar1 = FUN_0003ec68();
    *param_1 = iVar1;
  }
  iVar1 = *param_1;
  pvVar2 = TlsGetValue(*DAT_002dc920);
  if ((pvVar2 == (LPVOID)0x0) || (*(int *)((int)pvVar2 + 8) <= iVar1)) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(*(int *)((int)pvVar2 + 0xc) + iVar1 * 4);
  }
  if (iVar1 == 0) {
    iVar1 = (*param_2)();
    FUN_0003edf0(DAT_002dc920,*param_1,iVar1);
  }
  return iVar1;
}


// 0003efe4 FUN_0003efe4

void FUN_0003efe4(int *param_1)

{
  int *piVar1;
  
  piVar1 = param_1;
  if (*param_1 != 0) {
    piVar1 = DAT_002dc920;
  }
  if (*param_1 != 0 && piVar1 != (int *)0x0) {
    FUN_0003ed6c();
  }
  *param_1 = 0;
  return;
}


// 0003f014 FUN_0003f014

int FUN_0003f014(int *param_1,code *param_2)

{
  int iVar1;
  undefined1 auStack_54 [56];
  
  if (*param_1 == 0) {
    FUN_0003ea90(0x10);
    FUN_0002f060(auStack_54);
    iVar1 = setjmp(auStack_54);
    if (iVar1 == 0) {
      if (*param_1 == 0) {
        iVar1 = (*param_2)();
        *param_1 = iVar1;
      }
    }
    else {
      FUN_0003eb2c(0x10);
      FUN_0002f108(0);
    }
    FUN_0002f0c0();
    FUN_0003eb2c(0x10);
  }
  return *param_1;
}


// 0003f0a4 FUN_0003f0a4

void FUN_0003f0a4(int *param_1)

{
  undefined4 *puVar1;
  undefined4 local_8;
  
  puVar1 = (undefined4 *)0x0;
  if (*param_1 != 0) {
    puVar1 = (undefined4 *)*param_1;
    local_8 = puVar1;
  }
  if (*param_1 != 0 && puVar1 != (undefined4 *)0x0) {
    (**(code **)*local_8)(local_8,1);
  }
  return;
}


// 0003f138 FUN_0003f138

void FUN_0003f138(undefined1 *param_1)

{
  *param_1 = 0xb8;
  param_1[1] = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  if (*(void **)(param_1 + 0xc) != (void *)0x0) {
    free(*(void **)(param_1 + 0xc));
  }
  return;
}


// 0003f170 FUN_0003f170

void FUN_0003f170(void)

{
  FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  return;
}


// 0003f194 FUN_0003f194

void FUN_0003f194(void)

{
  return;
}


// 0003f1b0 FUN_0003f1b0

void FUN_0003f1b0(undefined1 *param_1,undefined1 param_2)

{
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x203c) = 0;
  *(undefined4 *)(param_1 + 0x2040) = 0;
  *(undefined4 *)(param_1 + 0x204c) = 0;
  *(undefined4 *)(param_1 + 0x2060) = 0;
  *(undefined4 *)(param_1 + 0x2064) = 0;
  *(undefined4 *)(param_1 + 0x2048) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *param_1 = 0xbc;
  param_1[1] = 0;
  param_1[0x14] = param_2;
  param_1[2] = 4;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0x28) = 0x1c;
  *(undefined4 *)(param_1 + 0x20) = 0x14;
  *(undefined4 *)(param_1 + 0x30) = 1;
  *(undefined4 *)(param_1 + 0x2040) = 0x18;
  *(undefined1 **)(param_1 + 0x2034) = &LAB_0002d3e4;
  return;
}


// 0003f290 FUN_0003f290

void FUN_0003f290(undefined1 *param_1)

{
  int *piVar1;
  
  *param_1 = 0xbc;
  param_1[1] = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  piVar1 = *(int **)(param_1 + 0x2068);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0xc))(piVar1,param_1 + 0x2044);
    piVar1 = *(int **)(param_1 + 0x2068);
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 4))(piVar1,1);
    }
  }
  FUN_0003efe4(param_1 + 0x206c);
  return;
}


// 0003f320 FUN_0003f320

void FUN_0003f320(undefined1 *param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *param_1 = 0xc0;
  param_1[1] = 0;
  param_1[2] = 4;
  param_1[3] = 0;
  *(undefined4 *)(param_1 + 0xc) = 0x68;
  *(code **)(param_1 + 0x28) = FUN_0002ec8c;
  return;
}


// 0003f390 FUN_0003f390

void FUN_0003f390(undefined1 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  void *_Memory;
  int *piVar2;
  
  *param_1 = 0xc0;
  param_1[1] = 0;
  puVar1 = *(undefined4 **)(param_1 + 0x14);
  param_1[2] = 4;
  if (puVar1 != (undefined4 *)0x0) {
    param_2 = 1;
  }
  param_1[3] = 0;
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1,param_2);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x18);
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x1c);
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x20);
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  puVar1 = *(undefined4 **)(param_1 + 0x24);
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1,1);
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    while (*(int *)(*(int *)(param_1 + 0x38) + 0xc) != 0) {
      _Memory = (void *)FUN_0002dafc();
      free(_Memory);
    }
  }
  piVar2 = *(int **)(param_1 + 0x30);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 4))(piVar2,1);
  }
  piVar2 = *(int **)(param_1 + 0x34);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 4))(piVar2,1);
  }
  piVar2 = *(int **)(param_1 + 0x38);
  if (piVar2 != (int *)0x0) {
    (**(code **)(*piVar2 + 4))(piVar2,1);
  }
  return;
}


// 0003f4c8 FUN_0003f4c8

void FUN_0003f4c8(void)

{
  FUN_0003f4d8();
  atexit(&DAT_0003f4e8);
  return;
}


// 0003f4d8 FUN_0003f4d8

void FUN_0003f4d8(void)

{
  return;
}


// 0003f4f4 FUN_0003f4f4

void FUN_0003f4f4(void)

{
  int iVar1;
  
  iVar1 = FUN_0003ef20(&DAT_002dc960,&DAT_0003ea28);
  if (*(int *)(iVar1 + 4) == 0) {
    FUN_0003f014(&DAT_002dc95c,FUN_0003f574);
  }
  return;
}


// 0003f52c FUN_0003f52c

void FUN_0003f52c(void)

{
  int iVar1;
  
  iVar1 = FUN_0003f4f4();
  FUN_0003ef20(iVar1 + 0x206c,&DAT_0003f550);
  return;
}


// 0003f574 FUN_0003f574

undefined1 * FUN_0003f574(void)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)FUN_0003ebd8(0x2070);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    FUN_0003f1b0(puVar1,1);
    *puVar1 = 0xc4;
    puVar1[1] = 0;
    puVar1[2] = 4;
    puVar1[3] = 0;
  }
  return puVar1;
}


// 0003f5cc FUN_0003f5cc

undefined4 FUN_0003f5cc(undefined4 param_1,uint param_2)

{
  FUN_0003f290();
  if ((param_2 & 1) != 0) {
    FUN_0003ebf8(param_1);
  }
  return param_1;
}


// 0003f668 FUN_0003f668

void FUN_0003f668(undefined1 *param_1)

{
  *param_1 = 0x58;
  param_1[1] = 7;
  param_1[2] = 4;
  param_1[3] = 0;
  return;
}


// 0003f6b4 FUN_0003f6b4

void FUN_0003f6b4(void)

{
  FUN_0003f6c4();
  atexit(&LAB_0003f6d4);
  return;
}


// 0003f6c4 FUN_0003f6c4

void FUN_0003f6c4(void)

{
  return;
}


// 0003f6e0 FUN_0003f6e0

undefined1 * FUN_0003f6e0(void)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)operator_new(8);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    *puVar1 = 0x78;
    puVar1[1] = 7;
    puVar1[2] = 4;
    puVar1[3] = 0;
    *(undefined4 *)(puVar1 + 4) = 0;
  }
  return puVar1;
}


// 0003f754 FUN_0003f754

void FUN_0003f754(void)

{
  FUN_0002efb0(&DAT_002de3b8,0);
  DAT_002de3c4 = 0;
  DAT_002de3c8 = 0;
  DAT_002de3b8 = &PTR_LAB_00040958;
  DAT_002de4cc = 0xf022;
  return;
}


// 0003f7d8 FUN_0003f7d8

void FUN_0003f7d8(void)

{
  FUN_0002efb0(&DAT_002de2a0,0);
  DAT_002de2ac = 0;
  DAT_002de2b0 = 0;
  DAT_002de2a0 = &PTR_LAB_00040970;
  DAT_002de3b4 = 0xf024;
  return;
}


// 0003f87c FUN_0003f87c

undefined1 * FUN_0003f87c(void)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)operator_new(8);
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = (undefined1 *)0x0;
  }
  else {
    *puVar1 = 0x88;
    puVar1[1] = 9;
    puVar1[2] = 4;
    puVar1[3] = 0;
    *(undefined4 *)(puVar1 + 4) = 0;
  }
  return puVar1;
}


// 0003f914 FUN_0003f914

AUX_DATA * FUN_0003f914(void)

{
  DAT_002de538 = 0;
  DAT_002de534 = 0x400;
  DAT_002de53c = 1;
  DAT_002de540 = 0;
  DAT_002de544 = 1;
  DAT_002de548 = 0;
  FUN_00034010();
  DAT_002de504 = 0;
  FUN_00033f94(&afxData);
  DAT_002de51c = LoadCursorW((HINSTANCE)0x0,(LPCWSTR)&DAT_00007f02);
  DAT_002de520 = LoadCursorW((HINSTANCE)0x0,(LPCWSTR)&DAT_00007f00);
  DAT_002de4f0 = 2;
  DAT_002de530 = 0;
  DAT_002de524 = 0;
  if (DAT_002de53c == 0) {
    DAT_002de4f0 = 1;
  }
  DAT_002de4f4 = 2;
  if (DAT_002de53c == 0) {
    DAT_002de4f4 = 1;
  }
  return &afxData;
}


// 0003f938 FUN_0003f938

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0003f938(void)

{
  int iVar1;
  
  if (DAT_002de53c != 0) {
    _afxData = FUN_0002b30c(2);
    _afxData = _afxData + 1;
    iVar1 = FUN_0002b30c(3);
    DAT_002de4e4 = iVar1 + 1;
    DAT_002de548 = 1;
  }
  return;
}


// 0003f97c FUN_0003f97c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0003f97c(void)

{
  _afxData = FUN_0002b30c(2);
  DAT_002de4e4 = FUN_0002b30c(3);
  DAT_002de548 = 0;
  return;
}


// 0003fa68 FUN_0003fa68

int FUN_0003fa68(int param_1)

{
  FUN_0002fa00();
  *(undefined4 *)(param_1 + 0x58) = 2;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x48) = 6;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x54) = 1;
  *(undefined4 *)(param_1 + 0x50) = 1;
  *(undefined4 *)(param_1 + 0x5c) = 0x7fff;
  return param_1;
}


// 0003facc FUN_0003facc

void FUN_0003facc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0x4c) = param_4;
  *(undefined4 *)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x50) = param_3;
  *(undefined4 *)(param_1 + 0x54) = param_5;
  return;
}


// 0003fae4 FUN_0003fae4

undefined4 FUN_0003fae4(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = FUN_00030458();
  if (iVar1 == 0) {
    return 0;
  }
  *(uint *)(param_2 + 0x20) = *(uint *)(param_2 + 0x20) | 0x4000000;
  if (DAT_002de53c == 0) {
    return 1;
  }
  uVar3 = *(uint *)(param_1 + 0x6c);
  if ((uVar3 & 0x80) != 0) {
    return 1;
  }
  uVar2 = uVar3 & 0xff00;
  if (uVar2 != 0x1400) {
    if (uVar2 == 0x2800) {
      uVar2 = 0x200;
      goto LAB_0003fb74;
    }
    if (uVar2 != 0x4100) {
      if (uVar2 != 0x8200) {
        return 1;
      }
      uVar2 = 0x800;
      goto LAB_0003fb74;
    }
  }
  uVar2 = 0xa00;
LAB_0003fb74:
  *(uint *)(param_1 + 0x6c) = uVar3 & 0xfffff0ff | uVar2 | 0x80;
  return 1;
}


// 0003fb90 FUN_0003fb90

void FUN_0003fb90(void)

{
  FUN_0003fba0();
  atexit(&LAB_0003fbb0);
  return;
}


// 0003fba0 FUN_0003fba0

void FUN_0003fba0(void)

{
  return;
}


// 0003fc78 FUN_0003fc78

void FUN_0003fc78(void)

{
  return;
}


// 0003fcd0 FUN_0003fcd0

void FUN_0003fcd0(void)

{
  wchar_t wVar1;
  int iVar2;
  wchar_t *pwVar3;
  int iVar4;
  code *extraout_r2;
  code *pcVar5;
  wchar_t *_Str;
  
  iVar2 = FUN_0003f4f4();
  FUN_0003ea90(1);
  _Str = (wchar_t *)(iVar2 + 0x34);
  wVar1 = *_Str;
  while (wVar1 != L'\0') {
    pwVar3 = wcschr(_Str,L'\n');
    *pwVar3 = L'\0';
    iVar4 = FUN_0003f4f4();
    UnregisterClassW(_Str,*(HINSTANCE *)(iVar4 + 8));
    _Str = pwVar3 + 1;
    wVar1 = *_Str;
  }
  *(undefined2 *)(iVar2 + 0x34) = 0;
  FUN_0003eb2c(1);
  iVar2 = FUN_0003f4f4();
  iVar2 = *(int *)(iVar2 + 4);
  pcVar5 = extraout_r2;
  if (iVar2 != 0) {
    pcVar5 = *(code **)(iVar2 + 0x54);
  }
  if (iVar2 != 0 && pcVar5 != (code *)0x0) {
    (*pcVar5)(1,0);
  }
  FUN_0003f170();
  return;
}


// 0003fd90 FUN_0003fd90

void FUN_0003fd90(int param_1)

{
  int iVar1;
  code *extraout_r2;
  code *pcVar2;
  
  iVar1 = FUN_0002f1d0();
  pcVar2 = extraout_r2;
  if (iVar1 != 0) {
    pcVar2 = *(code **)(iVar1 + 0x54);
  }
  if (iVar1 != 0 && pcVar2 != (code *)0x0) {
    (*pcVar2)(1,1);
  }
  PostQuitMessage(param_1);
  return;
}


