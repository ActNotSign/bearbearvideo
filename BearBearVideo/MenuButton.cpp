// MenuButton.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "MenuButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
CMenuButton::CMenuButton()
{
}

CMenuButton::~CMenuButton()
{
}


BEGIN_MESSAGE_MAP(CMenuButton, CButton)
	//{{AFX_MSG_MAP(CMenuButton)
	ON_WM_DRAWITEM()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuButton message handlers

void CMenuButton::TabButtonNormal(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_TABBUTTON);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
		mDC.m_hDC ,0,30,bitinfo.bmWidth ,20,RGB(255,0,255));

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

void CMenuButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	TabButtonNormal(lpDrawItemStruct);
	// TODO: Add your message handler code here and/or call default
 
 	UINT btState = lpDrawItemStruct->itemState;

 	if(btState & ODS_DISABLED)
  	{
		//Invalidate ();
		TabButtonDeath(lpDrawItemStruct);
  	}
 
}

void CMenuButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CButton::OnMouseMove(nFlags, point);

	CRect rc;
	GetClientRect(&rc);
	rc.InflateRect (-5,-5,-16,-10);
	point.x =point.x -rc.left ;
	point.y =point.y -rc.top ;
	if(rc.PtInRect (point))
	{
		CRect winRect ;
		GetClientRect(&winRect);
		
		CDC *pDC=GetWindowDC();
		CDC mDC;
		mDC.CreateCompatibleDC (pDC);
		
		CBitmap bitmap ,*pbitmap;
		BITMAP bitinfo;
		bitmap.LoadBitmap (IDB_TABBUTTON);
		bitmap.GetBitmap (&bitinfo);
		
		pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);
		
		TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
			mDC.m_hDC ,0,60,bitinfo.bmWidth ,20,RGB(255,0,255));
		
		
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
	}else
	{

		CRect winRect ;
		GetClientRect(&winRect);
		
		CDC *pDC=GetWindowDC();
		CDC mDC;
		mDC.CreateCompatibleDC (pDC);
		
		CBitmap bitmap ,*pbitmap;
		BITMAP bitinfo;
		bitmap.LoadBitmap (IDB_TABBUTTON);
		bitmap.GetBitmap (&bitinfo);
		
		pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);
		
		TransparentBlt (pDC->m_hDC ,0,0,winRect.Width (),winRect.Height (),
			mDC.m_hDC ,0,30,bitinfo.bmWidth ,20,RGB(255,0,255));
		
		
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
}

void CMenuButton::PreSubclassWindow() 
{
	ModifyStyle(0,BS_OWNERDRAW);
	
	CButton::PreSubclassWindow();
}

void CMenuButton::TabButtonDeath(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CDC *pDC=GetWindowDC();
	CRect winRect=lpDrawItemStruct->rcItem ;

	CDC mDC;
	mDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;
	bitmap.LoadBitmap (IDB_TABBUTTON);
	bitmap.GetBitmap (&bitinfo);

	pbitmap=(CBitmap *)mDC.SelectObject (&bitmap);

	TransparentBlt (pDC->m_hDC ,0,2,winRect.Width (),winRect.Height (),
		mDC.m_hDC ,0,0,bitinfo.bmWidth ,20,RGB(255,0,255));

	mDC.SelectObject (pbitmap);
	mDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	CString text;
	GetWindowText(text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor (RGB(85,133,172));

	pDC->DrawText (text,&winRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	pDC->DeleteDC ();
}
