// Soft.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "Soft.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoft dialog


CSoft::CSoft(CWnd* pParent /*=NULL*/)
	: CDialog(CSoft::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoft)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSoft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoft)
	DDX_Control(pDX, IDC_SPY, m_spy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSoft, CDialog)
	//{{AFX_MSG_MAP(CSoft)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SPY, OnSpy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoft message handlers

void CSoft::DrawDialog()
{
	CDC *pDC=GetWindowDC();
	CBrush brush;
	CRect winRect;
	GetWindowRect(&winRect);
	CRect rect;	
	brush.CreateSolidBrush (RGB(94,179,227));
//底线
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =winRect.Height ()-1;
	rect.bottom =winRect.Height ();


	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();
//上线
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =0;
	rect.bottom =1;

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();


//left线
	rect.left =0;
	rect.right =1;
	rect.top =0;
	rect.bottom =winRect.Height ();

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();

//right线
	rect.left =winRect.Width ()-1;
	rect.right =winRect.Width(),
	rect.top =0;
	rect.bottom =winRect.Height ();

	pDC->FillRect (&rect,&brush);
	pDC->DeleteDC ();

	brush.DeleteObject ();	
}



LRESULT CSoft::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT callBack = CDialog::DefWindowProc(message, wParam, lParam);
	if(!::IsWindow(m_hWnd))
    {
       return callBack ;
    }	
   if(message == WM_PAINT || message == WM_NCACTIVATE || message == WM_NOTIFY)
	{   
           DrawDialog();
    }	
   return CDialog::DefWindowProc(message, wParam, lParam);
}

HBRUSH CSoft::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(RGB(22,76,121));	
	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSoft::OnSpy() 
{
	m_Spy.DoModal ();
}
