// AD.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "AD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAD dialog


CAD::CAD(CWnd* pParent /*=NULL*/)
	: CDialog(CAD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAD)
	DDX_Control(pDX, IDC_QQ, m_qq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAD, CDialog)
	//{{AFX_MSG_MAP(CAD)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAD message handlers

HBRUSH CAD::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);

	return hbr;
}

LRESULT CAD::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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
	return callBack;		
}

void CAD::DrawDialog()
{
	CDC *pDC=GetWindowDC();
	CBrush brush;
	CRect winRect;
	GetWindowRect(&winRect);
	CRect rect;
//底线
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =winRect.Height ()-1;
	rect.bottom =winRect.Height ();
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();
//上线
	rect.left =0;
	rect.right =winRect.Width  ();
	rect.top =0;
	rect.bottom =1;
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();


//left线
	rect.left =0;
	rect.right =1;
	rect.top =0;
	rect.bottom =winRect.Height ();
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);

	brush.DeleteObject ();

//right线
	rect.left =winRect.Width ()-1;
	rect.right =winRect.Width(),
	rect.top =0;
	rect.bottom =winRect.Height ();
	brush.CreateSolidBrush (RGB(94,179,227));

	pDC->FillRect (&rect,&brush);
	pDC->DeleteDC ();
	brush.DeleteObject ();	
}

BOOL CAD::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_qq.Dong ();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
