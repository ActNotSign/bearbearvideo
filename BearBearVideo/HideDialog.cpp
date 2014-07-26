// HideDialog.cpp : implementation file
//

#include "stdafx.h"
#include "bearbearvideo.h"
#include "HideDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHideDialog dialog


CHideDialog::CHideDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHideDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHideDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	r=0;
	g=255;
	b=0;
	str="录制中";
	is=FALSE;
}


void CHideDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHideDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHideDialog, CDialog)
	//{{AFX_MSG_MAP(CHideDialog)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHideDialog message handlers

BOOL CHideDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL"); 
	if(hInst) 
	{            
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);          
		MYFUNC fun = NULL;
		//取得SetLayeredWindowAttributes函数指针     
		fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if(fun)fun(this->GetSafeHwnd(),0,150,2);     
		FreeLibrary(hInst); 
	}
	CRect wr;
	::GetWindowRect (::GetDesktopWindow (),&wr);
	CRect r;
	GetWindowRect(&r);
	MoveWindow (wr.Width ()-r.Width ()-10,10,r.Width (),r.Height ());

	SetTimer(1,300,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHideDialog::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	::AfxGetMainWnd ()->ShowWindow (SW_SHOW);
	SendMessage(WM_CLOSE);
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CHideDialog::OnTimer(UINT nIDEvent) 
{
	CDC *pDC=GetWindowDC ();

	if(r==255)
	{
		if(g==0)
		{

			if(b==255)
			{
				b=0;
				r=0;
				g=255;
			}else
			{
				b+=5;
			}
		}
		else
		{
			g-=25;
		}
	}else
	{
		r+=15;
	}
	CFont font;
	font.CreatePointFont (100,"宋体");
	pDC->SelectObject (&font);
	pDC->SetTextColor (RGB(r,g,b));
	pDC->SetBkMode(TRANSPARENT);
	CRect winRect;
	GetWindowRect(&winRect);

	if(is)
	{
		Invalidate ();
		is=FALSE;
	}
	pDC->TextOut (13,9,str);
	font.DeleteObject ();

	CFont f;
	f.CreatePointFont (116,"宋体");
	pDC->SelectObject (&f);
	pDC->SetTextColor (RGB(0,0,255));
	pDC->TextOut (5,29,"双击返回");
	f.DeleteObject ();

	pDC->DeleteDC ();

	CDialog::OnTimer(nIDEvent);
}

void CHideDialog::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SendMessage (WM_NCLBUTTONDOWN,HTCAPTION);
	CDialog::OnLButtonDown(nFlags, point);
}
