// DarwDialog.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "DarwDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDarwDialog dialog


CDarwDialog::CDarwDialog(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CDarwDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CDarwDialog::CDarwDialog(UINT id, CWnd * parent /* = NULL */)
      : CDialog(id, parent) , m_IsHasMaxButton(false) , 
	  m_IsHasCloseButton(true) , m_IsHasMinButton(false)
{
}


void CDarwDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDarwDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDarwDialog, CDialog)
	//{{AFX_MSG_MAP(CDarwDialog)
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDarwDialog message handlers

void CDarwDialog::Draw()
{
	if(!IsWindow (m_hWnd))
	{
		return;
	}

	CRect rc ,r;
	GetWindowRect(&rc);
	GetClientRect(&r);

	CDC *pDC=GetWindowDC(); 
	CDC mermoyDC;
	mermoyDC.CreateCompatibleDC (pDC);

	CBitmap bitmap ,*pbitmap;
	bitmap.LoadBitmap (IDB_FARAM);
	BITMAP bitinfo;
	bitmap.GetBitmap (&bitinfo);
	pbitmap =(CBitmap*)mermoyDC.SelectObject (&bitmap);
//top
	pDC->StretchBlt (0,0,rc.Width ()-1,rc.Height () - r.Height ()-1,&mermoyDC,0,0,bitinfo.bmWidth  ,25,SRCCOPY);

//left
	pDC->StretchBlt (0,25,5,rc.Height (),&mermoyDC,0,9,5,bitinfo.bmHeight,SRCCOPY);
//right
	pDC->StretchBlt (rc.Width ()-5,25,rc.Width () -10,rc.Height (),&mermoyDC, bitinfo.bmWidth -5,9,bitinfo.bmWidth -5 ,bitinfo.bmHeight ,SRCCOPY);
//bomtton
	pDC->StretchBlt (0,rc.Height ()-6,rc.Width (),27,&mermoyDC,0,bitinfo.bmHeight-5 ,bitinfo.bmWidth ,25,SRCCOPY);

	mermoyDC.SelectObject (pbitmap);
	mermoyDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();


//button
	bitmap.LoadBitmap (IDB_BUTTON);
	bitmap.GetBitmap (&bitinfo);
	mermoyDC.CreateCompatibleDC (pDC);
	mermoyDC.SelectObject (&bitmap);
//close
	m_rcclose.left =rc.Width ()-48;
	m_rcclose.top =0;
	m_rcclose.right =rc.Width ()-10;
	m_rcclose.bottom =21;
	pDC->StretchBlt (m_rcclose.left,m_rcclose.top,m_rcclose.Width (),m_rcclose.Height (),
		&mermoyDC,0,20,40,19,SRCCOPY);
//min

	m_rcmin.left =rc.Width ()-77;
	m_rcmin.top =0;
	m_rcmin.right =rc.Width ()-48;
	m_rcmin.bottom =21;

	pDC->StretchBlt (rc.Width ()-77,0,m_rcmin.Width (),m_rcmin.Height ()
		,&mermoyDC,0,0,27 ,19,SRCCOPY);

	mermoyDC.SelectObject (pbitmap);
	mermoyDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	pDC->DeleteDC ();
}





LRESULT CDarwDialog::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT callBack = CDialog::DefWindowProc(message, wParam, lParam);
	if(!::IsWindow(m_hWnd))
    {
       return callBack ;
    }	
   if(message == WM_NCPAINT || message == WM_NCACTIVATE || message == WM_NOTIFY)
	{   
           Draw();
    }	
	return callBack;
}

void CDarwDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rctWnd;
    GetWindowRect(&rctWnd);
    HRGN hrgn1 = ::CreateRoundRectRgn(0, 0 ,rctWnd.Width()  ,rctWnd.Height(),9,9);
    SetWindowRgn(hrgn1,TRUE);
	::DeleteObject(hrgn1);
	// TODO: Add your message handler code here
	
}

void CDarwDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	// TODO: Add your message handler code here and/or call default
	 lpncsp[0].rgrc ->right -=2;
	 lpncsp[0].rgrc ->left +=2;
	 lpncsp[0].rgrc ->top +=0;	
	 lpncsp[0].rgrc ->bottom  -=2;	
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}



void CDarwDialog::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	if(!IsWindow (m_hWnd))
	{
		return;
	}


	CRect rc;
	GetWindowRect(&rc);


	point.x =point.x -rc.left ;
	point.y =point.y -rc.top ;



	CDC *pDC=GetWindowDC(); 
	CDC mermoyDC;
	CBitmap bitmap ,*pbitmap;
	BITMAP bitinfo;

	mermoyDC.CreateCompatibleDC (pDC);
	bitmap.LoadBitmap (IDB_BUTTON);
	bitmap.GetBitmap (&bitinfo);
	pbitmap=(CBitmap *)mermoyDC.SelectObject (&bitmap);

	if(m_rcclose.PtInRect (point))
	{
		pDC->StretchBlt (m_rcclose.left,m_rcclose.top,m_rcclose.Width (),m_rcclose.Height (),
			&mermoyDC,41,20,40  ,19,SRCCOPY);
	}else
	{
		pDC->StretchBlt (m_rcclose.left,m_rcclose.top,m_rcclose.Width (),m_rcclose.Height (),
			&mermoyDC,0,20,40,19,SRCCOPY);
	}

	if(m_rcmin.PtInRect (point))
	{
		pDC->StretchBlt (rc.Width ()-77,0,m_rcmin.Width (),m_rcmin.Height ()
			,&mermoyDC,27,0,27 ,19,SRCCOPY);
	}else
	{
		pDC->StretchBlt (rc.Width ()-77,0,m_rcmin.Width (),m_rcmin.Height ()
			,&mermoyDC,0,0,27 ,19,SRCCOPY);
	}
	mermoyDC.SelectObject (pbitmap);
	mermoyDC.DeleteDC ();
	pbitmap->DeleteObject ();
	bitmap.DeleteObject ();

	pDC->DeleteDC ();	
	CDialog::OnNcMouseMove(nHitTest, point);
}

void CDarwDialog::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	if(!IsWindow (m_hWnd))
	{
		return;
	}


	CRect rc;
	GetWindowRect(&rc);

	point.x =point.x -rc.left ;
	point.y =point.y -rc.top ;

	if(m_rcclose.PtInRect (point))
	{
		SendMessage(WM_CLOSE);
	}

	if(m_rcmin.PtInRect (point))
	{
		SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);  
	}
	CDialog::OnNcLButtonDown(nHitTest, point);
}

HBRUSH CDarwDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(22,76,121));
	// TODO: Return a different brush if the default is not desired
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
