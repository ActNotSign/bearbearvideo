#include <windows.h>
#include <stdio.h>
//#include "stdafx.h"

HHOOK g_mouse=NULL;
HHOOK g_keyboard=NULL;
//�Զ�����Ϣ
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
	// ��Ļ���ڴ��豸������
	HBITMAP hBitmap,hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2,xScrn,yScrn;      
	// ѡ����������
	int       nWidth, nHeight;      
	// λͼ��Ⱥ͸߶�
      
	// ��Ļ�ֱ���
	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
//	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	hScrDC=GetWindowDC(::GetDesktopWindow ());
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;
	// �����Ļ�ֱ���
	xScrn = GetDeviceCaps(hScrDC, HORZRES);
	yScrn = GetDeviceCaps(hScrDC, VERTRES);
	//ȷ��ѡ�������ǿɼ���
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


	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap=CreateCompatibleBitmap(hScrDC,nWidth,nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
	

	// ����Ļ�豸�����������ڴ��豸��������
	BitBlt(hMemDC,0,0, nWidth,nHeight,hScrDC, nX, nY, SRCCOPY);
	//	�����
	HICON hico=LoadCursor (NULL,IDC_ARROW);
	::DrawIcon (hMemDC,
		px ,py ,hico);

	//�õ���Ļλͼ�ľ��
	hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	::DeleteObject (hico);
	// ����λͼ���
	return hBitmap;
}