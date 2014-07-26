// SetLZ.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "SetLZ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetLZ property page

IMPLEMENT_DYNCREATE(CSetLZ, CPropertyPage)

CSetLZ::CSetLZ() : CPropertyPage(CSetLZ::IDD)
{
	//{{AFX_DATA_INIT(CSetLZ)
	m_makeV = -1;
	m_show = -1;
	//}}AFX_DATA_INIT
	m_move=FALSE;
	m_video=FALSE;
}

CSetLZ::~CSetLZ()
{
}

void CSetLZ::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetLZ)
	DDX_Control(pDX, IDC_LOOK, m_look);
	DDX_Control(pDX, IDC_SET, m_set);
	DDX_Radio(pDX, IDC_RADIO_FULL, m_makeV);
	DDX_Radio(pDX, IDC_RADIO_SHOW, m_show);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetLZ, CPropertyPage)
	//{{AFX_MSG_MAP(CSetLZ)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SET, OnSet)
	ON_BN_CLICKED(IDC_RADIO_WIN, OnRadioWin)
	ON_BN_CLICKED(IDC_RADIO_VIDEO, OnRadioVideo)
	ON_BN_CLICKED(IDC_RADIO_FULL, OnRadioFull)
	ON_BN_CLICKED(IDC_LOOK, OnLook)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetLZ message handlers

void CSetLZ::DrawDialog()
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

LRESULT CSetLZ::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

HBRUSH CSetLZ::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(RGB(22,76,121));	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}




BOOL CSetLZ::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
//初始化东西


//
	((CButton*)GetDlgItem(IDC_RADIO_FULL))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO_HIDE))->SetCheck(1);
	// Create a child icon static control.


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}





CRect CSetLZ::MakeWhat()
{
	UpdateData ();
	CRect rc;
	switch (m_makeV)
	{
	case 0:
		m_video=FALSE;
		::GetWindowRect(::GetDesktopWindow (),&rc);
		return rc;
	case 1:
		m_video=FALSE;
		if(m_spy.m_C)
		{
			return m_rectCapture;
		}
		break;
	case 2:
		m_video=TRUE;
		return FALSE;
	}
	m_video=FALSE;
}

void CSetLZ::OnSet() 
{

}

int CSetLZ::SetWindowShow(HWND hWnd)
{
	UpdateData ();
	switch (m_show)
	{
	case 0:
		return SHOW;
	case 1:	

		::AfxGetMainWnd ()->ShowWindow (SW_HIDE);
		m_hide.Create (IDD_OLE_PROPPAGE_HIDE);
		m_hide.ShowWindow (SW_SHOW);


		return HDIE;
	case 2:
		::SendMessage(hWnd,WM_SYSCOMMAND,SC_MINIMIZE,NULL);
		return MIN;
	}
	return 1;

}

void CSetLZ::OnRadioWin() 
{
	
	if(IDCANCEL==m_spy.DoModal ())
	{
		if(m_spy.m_C)
		{
			((CStatic *)GetDlgItem(IDC_STATIC_C))->SetWindowText("已选择窗口");
			m_rectCapture=m_spy.m_rc;
		}
	}

}

void CSetLZ::OnRadioVideo() 
{
	((CStatic *)GetDlgItem(IDC_STATIC_C))->SetWindowText("未选择窗口");
	
}

void CSetLZ::OnRadioFull() 
{
	((CStatic *)GetDlgItem(IDC_STATIC_C))->SetWindowText("未选择窗口");
	
}

void CSetLZ::OnLook() 
{
	if(!::IsWindow (m_vs.m_hWnd ))
	
	{
		m_vs.Create (IDD_DIALOG_ViDEOSHOW);
		m_vs.ShowWindow (SW_SHOW);
	//	m_vs.Start ("a.avi");
	}else
	{
		m_vs.ShowWindow (SW_SHOW);
	//	m_vs.Start ("a.avi");
	}

}
