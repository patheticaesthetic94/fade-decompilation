// Everything game code calls outside itself: Win32/CE, GAPI, MFC CString/CArchive/CPlex/CTime, CRT.
// Signatures follow how decomp/game.c calls them (not always the real API), implemented in port/src/.
#pragma once

typedef tagMSG *LPMSG;
typedef void *_P32 HGDIOBJ;
typedef uint REGSAM;
typedef HKEY *PHKEY;
typedef const void *LPCVOID;
typedef tagPAINTSTRUCT *LPPAINTSTRUCT;
typedef tagPAINTSTRUCT PAINTSTRUCT;
typedef void (*TIMERPROC)(HWND, UINT, UINT_PTR, DWORD);

// Win32 / CE
int MessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT);
BOOL GetMessageW(LPMSG, HWND, UINT, UINT);
BOOL PeekMessageW(LPMSG, HWND, UINT, UINT, UINT);
LRESULT DispatchMessageW(MSG *);
BOOL TranslateMessage(MSG *);
BOOL PostMessageW(HWND, UINT, WPARAM, LPARAM);
LRESULT SendMessageW(HWND, UINT, WPARAM, LPARAM);
void PostQuitMessage(int);
LRESULT DefWindowProcW(HWND, UINT, WPARAM, LPARAM);
ATOM RegisterClassW(WNDCLASSW *);
HGDIOBJ GetStockObject(int);
BOOL DeleteObject(HGDIOBJ);
int GetObjectW(HANDLE, int, LPVOID);
BOOL UpdateWindow(HWND);
BOOL ShowWindow(HWND, int);
HWND CreateWindowExW(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
HWND FindWindowW(LPCWSTR, LPCWSTR);
HWND GetForegroundWindow(void);
BOOL SetForegroundWindow(HWND);
int GetSystemMetrics(int);
HDC BeginPaint(HWND, LPPAINTSTRUCT);
BOOL EndPaint(HWND, PAINTSTRUCT *);
UINT_PTR SetTimer(HWND, UINT_PTR, UINT, TIMERPROC);
BOOL KillTimer(HWND, UINT_PTR);
void Sleep(DWORD);
BOOL sndPlaySoundW(LPCWSTR, UINT);
HANDLE CreateFileW(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
BOOL ReadFile(HANDLE, LPVOID, DWORD, DWORD *, LPOVERLAPPED);
BOOL WriteFile(HANDLE, LPCVOID, DWORD, DWORD *, LPOVERLAPPED);
DWORD SetFilePointer(HANDLE, LONG, LONG *, DWORD);
BOOL CloseHandle(HANDLE);
BOOL DeleteFileW(LPCWSTR);
BOOL CreateDirectoryW(LPCWSTR, LPSECURITY_ATTRIBUTES);
LSTATUS RegOpenKeyExW(HKEY, LPCWSTR, DWORD, REGSAM, PHKEY);
LSTATUS RegQueryValueExW(HKEY, LPCWSTR, DWORD *, DWORD *, BYTE *, DWORD *);
LSTATUS RegSetValueExW(HKEY, LPCWSTR, DWORD, DWORD, BYTE *, DWORD);
LSTATUS RegCloseKey(HKEY);

// GAPI (gx.dll)
int GXOpenDisplay(HWND, DWORD);
int GXCloseDisplay(void);
void *GXBeginDraw(void);
int GXEndDraw(void);
int GXOpenInput(void);
int GXCloseInput(void);
GXDisplayProperties *GXGetDisplayProperties(void);   // really returns the struct by value
GXKeyList *GXGetDefaultKeys(int);                     // idem
int GXSuspend(void);
int GXResume(void);

// MFC
CString *CString_CtorW(CString *, wchar16 *);
CString *CString_CtorA(CString *, char *);
int *CString_CopyCtor(CString *, CString *);
void CString_Dtor(CString *);
CString *CString_Assign(CString *, CString *);
CString *CString_AssignW(CString *, wchar16 *);
undefined4 *CString_AssignA(CString *, char *);
CString *CString_AssignChar(CString *, wchar16);
CString *CString_Plus(CString *, CString *, CString *);
CString *CString_PlusChar(CString *, CString *, wchar16);
CString *CString_Append(CString *, CString *);
CString *CString_AppendChar(CString *, wchar16);
wchar16 *CString_GetBuffer(CString *, int);
void CString_MakeUpper(CString *);
void CString_SetAt(CString *, int, wchar16);
undefined4 *CTime_GetCurrentTime(undefined4 *);
Tm *CTime_GetLocalTm(undefined4, undefined1 *);
int CPlex_Create(void *, int, int);
void CPlex_FreeDataChain(void *);
int CArchive_Read(CArchive *, void *, uint);
void CArchive_Write(CArchive *, void *, uint);
void CArchive_WriteCount(CArchive *, uint);
uint CArchive_ReadCount(CArchive *);

// CRT
void *operator_new(size_t);
void game_free(void *);
undefined4 set_new_handler(void (*)(void));
void crt_exit(int);
uint time32(int);
int wcscmp16(const wchar16 *, const wchar16 *);
gdiv_t *div32(gdiv_t *, int, int);
int rand15(void);           // WinCE CRT rand: 0..0x7fff
void srand15(uint);

// IMGDECMP, ARM runtime helpers
int DecompressImageIndirect();   // reads g_imgDecompInfo (Ghidra drops the argument)
int __rt_sdiv();
uint __rt_udiv();
extern int __rt_sdiv_exref;
