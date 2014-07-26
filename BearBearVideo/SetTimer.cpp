// SetTimer.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "SetTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetTimer property page

IMPLEMENT_DYNCREATE(CSetTimer, CPropertyPage)

CSetTimer::CSetTimer() : CPropertyPage(CSetTimer::IDD)
{
	//{{AFX_DATA_INIT(CSetTimer)
	//}}AFX_DATA_INIT
}

CSetTimer::~CSetTimer()
{
}

void CSetTimer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimer)
	DDX_Control(pDX, IDC_TIMER_STOP, m_stop);
	DDX_Control(pDX, IDC_TIMER_STATR, m_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER_YEARSTOP, m_yearstop);
	DDX_Control(pDX, IDC_DATETIMEPICKER_YEARS, m_years);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIMERS, m_timers);
	DDX_Control(pDX, IDC_DATETIMEPICKER_TIMERSTOP, m_timerstop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTimer, CPropertyPage)
	//{{AFX_MSG_MAP(CSetTimer)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimer message handlers

HBRUSH CSetTimer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(RGB(22,76,121));	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

LRESULT CSetTimer::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	LRESULT callBack = CDialog::DefWindowProc(message, wParam, lParam);
	if(!::IsWindow(m_hWnd))
    {
       return callBack ;
    }	
   if(message == WM_PAINT || message == WM_NCACTIVATE || message == WM_NOTIFY)
	{   
           DrawDialog();
    }	
	return callBack;
}

void CSetTimer::DrawDialog()
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
