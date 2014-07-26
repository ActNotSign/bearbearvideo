// NewButton.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "NewButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewButton

CNewButton::CNewButton()
{
}

CNewButton::~CNewButton()
{
}


BEGIN_MESSAGE_MAP(CNewButton, CButton)
	//{{AFX_MSG_MAP(CNewButton)
	ON_WM_MOUSEMOVE()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewButton message handlers

void CNewButton::ButtonNormal(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_BUT_N);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	pDC->StretchBlt (0,0,winRect.Width (),winRect.Height (),
		&mDC,0,0,bitinfo.bmWidth ,bitinfo.bmHeight ,SRCCOPY);

	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(22,76,121));
	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}

void CNewButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	CButton::OnMouseMove(nFlags, point);
	CRect rc;
	GetClientRect(&rc);
	rc.InflateRect (-5,-4,-12,-7);
	point.x =point.x -rc.left ;
	point.y =point.y -rc.top ;
	if(rc.PtInRect (point))
	{
		ButtonMouse(IDB_BUT_S);
	}else
	{

		ButtonMouse(IDB_BUT_N);

	}
	
	CButton::OnMouseMove(nFlags, point);
}

void CNewButton::ButtonMouse(int IDB)
{
		CRect winRect ;
		GetClientRect(&winRect);
		
		CDC *pDC=GetWindowDC();
		CDC mDC;
		mDC.CreateCompatibleDC (pDC);
		
		CBitmap bitmap ,*pbitmap;
		BITMAP bitinfo;
		bitmap.LoadBitmap (IDB);
		bitmap.GetBitmap (&bitinfo);
		
		pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);
		
		pDC->StretchBlt (0,0,winRect.Width (),winRect.Height (),
			&mDC,0,0,bitinfo.bmWidth ,bitinfo.bmHeight ,SRCCOPY);

		
		
		mDC.SelectObject (pbitmap);
		mDC.DeleteDC ();
		pbitmap->DeleteObject ();
		bitmap.DeleteObject ();
		
		CString text;
		GetWindowText(text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor (RGB(22,76,121));
		pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		
		pDC->DeleteDC ();
}

void CNewButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

void CNewButton::ButtonPress(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_BUT_N);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);
	pDC->StretchBlt (0,0,winRect.Width (),winRect.Height (),
		&mDC,0,0,bitinfo.bmWidth ,bitinfo.bmHeight ,SRCCOPY);

	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(22,76,121));
	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}

void CNewButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
 	ButtonNormal(lpDrawItemStruct);
 
 	UINT btState = lpDrawItemStruct->itemState;

 	if(btState & ODS_DISABLED)
  	{
  	}
 
 	if(btState & ODS_SELECTED)
  	{
 		ButtonPress(lpDrawItemStruct);
  	}
	
}
