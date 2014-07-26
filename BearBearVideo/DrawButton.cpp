// DrawButton.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "DrawButton.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DrawButton

DrawButton::DrawButton()
{
}

DrawButton::~DrawButton()
{
}


BEGIN_MESSAGE_MAP(DrawButton, CButton)
	//{{AFX_MSG_MAP(DrawButton)
	ON_WM_MOUSEMOVE()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DrawButton message handlers









void DrawButton::ButtonPress(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_PRESSBUTTON2);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
		mDC.m_hDC ,0,0,bitinfo.bmWidth ,28,RGB(21,74,118));

	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(255,255,255));
	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}

void DrawButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	
	CButton::PreSubclassWindow();
}

void DrawButton::ButtonNormal(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_PRESSBUTTON2);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
		mDC.m_hDC ,0,56,bitinfo.bmWidth ,28,RGB(0,0,0));

	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(255,255,255));
	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}









void DrawButton::ButtonMouse()
{



	CRect winRect ;
	GetClientRect(&winRect);

	CDC *pDC=GetWindowDC();
	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_PRESSBUTTON2);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
		mDC.m_hDC ,0,28,bitinfo.bmWidth ,28,RGB(0,0,0));


	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(255,255,255));
	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}

void DrawButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CButton::OnMouseMove(nFlags, point);
	CRect rc;
	GetClientRect(&rc);
	rc.InflateRect (-5,-4,-12,-7);
	point.x =point.x -rc.left ;
	point.y =point.y -rc.top ;
	if(rc.PtInRect (point))
	{
		ButtonMouse();
	}else
	{

		CRect winRect ;
		GetClientRect(&winRect);
		
		CDC *pDC=GetWindowDC();
		CDC mDC;
		mDC.CreateCompatibleDC (pDC);
		
		CBitmap bitmap ,*pbitmap;
		BITMAP bitinfo;
		bitmap.LoadBitmap (IDB_PRESSBUTTON2);
		bitmap.GetBitmap (&bitinfo);
		
		pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);
		
		TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
			mDC.m_hDC ,0,56,bitinfo.bmWidth ,28,RGB(0,0,0));
		
		
		mDC.SelectObject (pbitmap);
		mDC.DeleteDC ();
		pbitmap->DeleteObject ();
		bitmap.DeleteObject ();
		
		CString text;
		GetWindowText(text);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor (RGB(255,255,255));
		pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		
		pDC->DeleteDC ();
	}



}

void DrawButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
 	ButtonNormal(lpDrawItemStruct);
 
 	UINT btState = lpDrawItemStruct->itemState;

 	if(btState & ODS_DISABLED)
  	{
		ButtonDeath(lpDrawItemStruct);
  	}
 
 	if(btState & ODS_SELECTED)
  	{
 		ButtonPress(lpDrawItemStruct);
  	}
}



void DrawButton::ButtonDeath(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_PRESSBUTTON2);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
		mDC.m_hDC ,0,56,bitinfo.bmWidth ,28,RGB(0,0,0));

	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(212,208,200));
	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}
