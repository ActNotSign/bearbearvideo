#include <windows.h>
#include <stdio.h>
//#include "stdafx.h"

HHOOK g_mouse=NULL;
HHOOK g_keyboard=NULL;
//自定义消息
#define MS_START	WM_USER+1
#define MS_STOP	WM_USER+2
#define MS_FINSH	WM_USER+3



#pragma data_seg("MouseDate")

int  px=0,py=0;
HWND g_hWnd=NULL;
BOOL g_isSend=FALSE;

#pragma data_seg()

LRESULT CALLBACK MouseProc( int nCode,
    WPARAM wParam,
    LPARAM lParam
	)
{
	MOUSEHOOKSTRUCT   *msdt=(MOUSEHOOKSTRUCT  FAR*)lParam;   
	px=msdt->pt.x -10;
	py=msdt->pt .y-5;

	return   CallNextHookEx(g_mouse,   nCode,   wParam,   lParam);   
}

LRESULT CALLBACK KeyboardProc( int code,
    WPARAM wParam,
    LPARAM lParam
)
{
	if(((DWORD)lParam & 0x40000000) && (HC_ACTION==code))
	{
	
		if(wParam==VK_F2)
		{
			SendMessage(g_hWnd,MS_START,0,0);
		}else
			if(wParam==VK_F3)
			{
				SendMessage(g_hWnd,MS_STOP,0,0);
			}else
				if(wParam==VK_F4)
				{
					SendMessage(g_hWnd,MS_FINSH,0,0);
				}

	}
	return   CallNextHookEx(g_keyboard,   code,   wParam,   lParam);   
}



void SetHook(HWND hWnd)
{
	g_hWnd=hWnd;

	g_mouse=SetWindowsHookEx(WH_MOUSE,MouseProc,GetModuleHandle("Key"),0);
	g_keyboard=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,GetModuleHandle("Key"),0);

}
void UnHook()
{
	UnhookWindowsHookEx(g_mouse);
	UnhookWindowsHookEx(g_keyboard);

}



HBITMAP CatchScreen(LPRECT lpRect)
{
	HDC hScrDC, hMemDC;   
	// 屏幕和内存设备描述表
	HBITMAP hBitmap,hOldBitmap;   
	// 位图句柄
	int       nX, nY, nX2, nY2,xScrn,yScrn;      
	// 选定区域坐标
	int       nWidth, nHeight;      
	// 位图宽度和高度
      
	// 屏幕分辨率
	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
//	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	hScrDC=GetWindowDC(::GetDesktopWindow ());
	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// 获得屏幕分辨率
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//确保选定区域是可见的
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > xScrn)
		nX2 = xScrn;
	if (nY2 > yScrn)
		nY2 = yScrn;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;


	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	

	// 把屏幕设备描述表拷贝到内存设备描述表中
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//	画鼠标
	HICON hico=LoadCursor (NULL,IDC_ARROW);
	::DrawIcon (hMemDC,
		px ,py ,hico);

	//得到屏幕位图的句柄
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	::DeleteObject (hico);
	// 返回位图句柄
	return hBitmap;
}