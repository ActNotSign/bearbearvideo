// DrawToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "DrawToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DrawToolBar

DrawToolBar::DrawToolBar()
{
}

DrawToolBar::~DrawToolBar()
{
}


BEGIN_MESSAGE_MAP(DrawToolBar, CToolBarCtrl)
	//{{AFX_MSG_MAP(DrawToolBar)
	ON_WM_CTLCOLOR()
	ON_WM_NCPAINT()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DrawToolBar message handlers







HBRUSH DrawToolBar::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CToolBarCtrl::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void DrawToolBar::OnNcPaint() 
{
	// TODO: Add your message handler code here
	
	// Do not call CToolBarCtrl::OnNcPaint() for painting messages
}

void DrawToolBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CToolBarCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
