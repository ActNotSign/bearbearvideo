// Spy.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "Spy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpy dialog


CSpy::CSpy(CWnd* pParent /*=NULL*/)
	: CDarwDialog(CSpy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpy)
	m_hide = FALSE;
	m_savepic = FALSE;
	//}}AFX_DATA_INIT
	m_move=FALSE;
	m_rc=NULL;
	m_C=FALSE;
}


void CSpy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpy)
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Check(pDX, IDC_CHECK, m_hide);
	DDX_Check(pDX, IDC_SAVEPIC, m_savepic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpy, CDarwDialog)
	//{{AFX_MSG_MAP(CSpy)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_BN_CLICKED(IDC_SAVEPIC, OnSavepic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpy message handlers

void CSpy::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CRect rc;
	GetClientRect(&rc);

	point.x =point.x -rc.left ;
	point.y =point.y -rc.top ;
	CRect r(80,20,120,50);
	
	if(r.PtInRect (point))
	{
		::SetCapture (this->m_hWnd );
		m_Static.SetIcon( ::AfxGetApp ()->LoadIcon(IDI_ICON1) );
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));  
		m_move=TRUE;
		if(::IsWindow (m_showPic.m_hWnd ))
			m_showPic.DestroyWindow ();

	}
	
	
	CDarwDialog::OnLButtonDown(nFlags, point);
}

BOOL CSpy::OnInitDialog() 
{
	CDarwDialog::OnInitDialog();

	m_Static.Create(_T("ico"), 
		WS_CHILD|WS_VISIBLE|SS_ICON|SS_CENTERIMAGE, CRect(80,20,120,50),
		this );
	m_Static.SetIcon( ::AfxGetApp ()->LoadIcon(IDI_ICON2) );
	

	::SetWindowPos (this->m_hWnd ,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE |SWP_NOMOVE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSpy::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_move)
	{
		ReleaseCapture();		
		m_Static.SetIcon( ::AfxGetApp ()->LoadIcon(IDI_ICON2) );
		SetCursor(AfxGetApp()->LoadCursor (IDC_ARROW));
		
		::RedrawWindow(m_hwndCapture,
			NULL, NULL, 
			RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_ERASENOW | 
			RDW_UPDATENOW | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
		m_move=FALSE;
		m_C=TRUE;
		::GetWindowRect (m_hwndCapture,&m_rc);

		//矩形区域的显示图片
		CRect r;
		::GetWindowRect (m_hwndCapture,&r);
		r.top  = r.top  -25;
		r.right =r.right +10;
		r.bottom =r.bottom +10;

		if(!::IsWindow (m_showPic.m_hWnd ))
		{

			if(m_savepic)
			{
				m_pic.SavePicture (m_pic.CatchBitmap (m_rc),m_strl);
			}
			m_showPic.Create (IDD_SWINDOW);
			m_showPic.DrawPic (m_pic.CatchBitmap (m_rc));
			m_showPic.MoveWindow (&r);	
			m_showPic.ShowWindow (SW_SHOW);

		}
	}
	
		
	CDarwDialog::OnLButtonUp(nFlags, point);
}

void CSpy::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_move)
	{
		SetCapture();
		//获取鼠标经过的窗口句柄
		ClientToScreen(&point); 
		m_hwndCapture=(HWND)::WindowFromPoint(point);    	//获得鼠标所在处的窗口句柄 	
		SetWindowMes();
		DrawRect(m_hwndCapture);
	}
	
	CDarwDialog::OnMouseMove(nFlags, point);
}

void CSpy::OnOK() 
{
	
	CDarwDialog::OnOK();
}

void CSpy::OnCancel() 
{

	UpdateData();
	if(m_hide==TRUE)
	{
		::AfxGetMainWnd ()->ShowWindow (SW_SHOW);
	}
	if(::IsWindow (m_showPic.m_hWnd ))
			m_showPic.DestroyWindow ();

	CDarwDialog::OnCancel();
}



HBRUSH CSpy::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{

//	HBRUSH hbr = CDarwDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(RGB(22,76,121));
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CSpy::OnCheck() 
{
	UpdateData();
	if(m_hide==TRUE)
	{
		::AfxGetMainWnd ()->ShowWindow (SW_HIDE);

	}else
	{
		::AfxGetMainWnd ()->ShowWindow (SW_SHOW);
	}

}

void CSpy::DrawRect(HWND hWnd)
{
	::GetWindowRect(hWnd,&m_rc);
	if(m_rc!=m_r)
	{
		CDC		DC,*pDC;	
		CPen    pen(PS_SOLID, 10, RGB(255,0,0));
		CPen	*pOldPen = NULL;
		HDC		hDC = NULL;
		hDC = ::GetWindowDC(hWnd);
		
		pDC=DC.FromHandle (hDC);
		
		pOldPen = pDC->SelectObject(&pen);
		
		pDC->MoveTo(0, 0);
		pDC->LineTo(m_rc.Width(), 0);
		pDC->LineTo(m_rc.Width(), m_rc.Height());
		pDC->LineTo(0, m_rc.Height());
		pDC->LineTo(0, 0);
		
		pDC->SelectObject(pOldPen);

		pOldPen->DeleteObject ();
		::DeleteObject (hDC);
		pDC->DeleteDC ();
		::ReleaseDC(m_hWnd,hDC);


		m_r=m_rc;
		m_h1=m_h;


		if(m_h1!=hWnd)
		{		
			::RedrawWindow(m_h1,
				NULL, NULL, 
				RDW_INTERNALPAINT | RDW_INVALIDATE | RDW_ERASENOW | 
				RDW_UPDATENOW | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
		}
		m_h=hWnd;


	}

}

void CSpy::SetWindowMes()
{
	//句柄值
	CString s;
	s.Format ("%d",m_hwndCapture);
	((CStatic *)GetDlgItem(IDC_STATIC_HANDLE))->SetWindowText(s);

	//类名
	char classname[255];
	::GetClassName(m_hwndCapture,classname,255);
	s.Format ("%s",classname);
	((CStatic *)GetDlgItem(IDC_STATIC_CLASSNAME))->SetWindowText(s);
	//
	//标题
	char cap[255];
	::GetWindowText (m_hwndCapture,cap,255);
	s.Format ("%s",cap);

	((CStatic *)GetDlgItem(IDC_STATIC_CAP))->SetWindowText(s);
	//矩形大小
	CRect rcc;
	::GetWindowRect (m_hwndCapture,&rcc);
	s.Format ("%d,%d,%d,%d",rcc.left ,rcc.right ,rcc.top ,rcc.bottom );
	((CStatic *)GetDlgItem(IDC_STATIC_RECT))->SetWindowText(s);

}

void CSpy::OnSavepic() 
{
	UpdateData();

	CFileDialog f(FALSE ,"bmp","未命名");
	f.m_ofn.lpstrFilter ="bmp\0*.bmp";
	if(IDOK==f.DoModal ())
	{

		m_strl=f.GetPathName ();

	}
}
