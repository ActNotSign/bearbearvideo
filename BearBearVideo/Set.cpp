// Set.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "Set.h"
#include ".\set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSet property page

IMPLEMENT_DYNCREATE(CSet, CPropertyPage)

CSet::CSet() : CPropertyPage(CSet::IDD)
, m_hasWave(FALSE)
, m_checkMake(FALSE)
, m_suerAVI(FALSE)
{
	//{{AFX_DATA_INIT(CSet)
	m_atime = 3;
	m_video = FALSE;
	m_mouse = FALSE;
	m_space = _T("");
	//}}AFX_DATA_INIT
	m_vset.filename ="";
	m_vset.path ="";
	m_vset.time =0;
}

CSet::~CSet()
{
}

void CSet::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSet)
	DDX_Control(pDX, IDC_SELETE, m_selete);
	DDX_Control(pDX, IDC_FILEPATHE, m_filepathe);
	DDX_Control(pDX, IDC_FILENAMEE, m_filenamee);
	DDX_Control(pDX, IDC_AVITIME, m_avitime);
	DDX_Text(pDX, IDC_AVITIME, m_atime);
	DDX_Check(pDX, IDC_CHECK_VIDEO, m_video);
	DDX_Check(pDX, IDC_CHECK_MOUSE, m_mouse);
	DDX_Text(pDX, IDC_STATIC_SPACE, m_space);
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_WAVE, m_hasWave);
	DDX_Check(pDX, IDC_CHECK_MAKE, m_checkMake);
	DDX_Radio(pDX, IDC_SUERAVI_AVI, m_suerAVI);
}


BEGIN_MESSAGE_MAP(CSet, CPropertyPage)
	//{{AFX_MSG_MAP(CSet)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_SELETE, OnSelete)
	ON_EN_CHANGE(IDC_AVITIME, OnChangeAvitime)
	ON_BN_CLICKED(IDC_CHECK_VIDEO, OnCheckVideo)
	ON_BN_CLICKED(IDC_CHECK_MOUSE, OnCheckMouse)
	ON_EN_CHANGE(IDC_FILENAMEE, OnChangeFilenamee)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_WAVE, OnBnClickedCheckWave)
	ON_BN_CLICKED(IDC_CHECK_MAKE, OnBnClickedCheckMake)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSet message handlers

HBRUSH CSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = ::CreateSolidBrush (RGB(243,245,247));
	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor(RGB(22,76,121));	
	// TODO: Return a different brush if the default is not desired
	return hbr;

}







void CSet::DrawDialog()
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

LRESULT CSet::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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

void CSet::OnSelete() 
{
	UpdateData ();

	CFileDialog f(FALSE ,"avi","视频");
	f.m_ofn.lpstrFilter ="avi\0*.avi";
	if(IDOK==f.DoModal ())
	{
		m_vset.filename = f.GetFileName ();

		m_vset.path = f.GetPathName ();
		(m_vset.path).TrimRight (f.GetPathName ());

		CString s=f.GetPathName ();
		s.TrimRight (f.GetPathName ()); 
	
		m_filenamee.SetWindowText (f.GetFileName ());
		m_filepathe.SetWindowText (s);
/*
		unsigned long  free,a,b;
		if(GetDiskFreeSpace("E:\\",&a,&b,&free,NULL)==0)
		{
			MessageBox("失败");
		}
		CString s;
		s.Format ("%dGB",(free*a*b)/1024/1024/1024);

		((CStatic *)GetDlgItem(IDC_STATIC_SPACE))->SetWindowText(s);
*/
	}
}

BOOL CSet::OnInitDialog() 
{

	//初始化配置


//	m_suerAVI=TRUE;

	CPropertyPage::OnInitDialog();

	UpdateData();
	//录制声音
	m_hasWave=TRUE;
//	m_video=TRUE;
	m_mouse=TRUE;
	//生成
	m_checkMake=TRUE;

	UpdateData(FALSE);
	m_vset.time=m_atime;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSet::OnChangeAvitime() 
{
	UpdateData ();

	m_vset.time =m_atime;	
}



void CSet::OnBnClickedCheckWave()
{
	//更新变量	
	UpdateData();
}

void CSet::OnBnClickedCheckMake()
{
	//更新变量
	UpdateData();

	if(m_checkMake)
	{
		(CButton*)GetDlgItem(IDC_SUERAVI_AVI)->EnableWindow (1);
	}else
	{
		(CButton*)GetDlgItem(IDC_SUERAVI_AVI)->EnableWindow (0);

	}
}

void CSet::OnCheckVideo() 
{
	UpdateData();	
}

void CSet::initEdit()
{
	
}

void CSet::OnCheckMouse() 
{
	UpdateData();		
}

void CSet::OnChangeFilenamee() 
{
	m_filenamee.GetWindowText (m_vset.filename);
	m_vset.path =m_vset.path + "\\"+m_vset.filename ;
//	MessageBox(m_vset.path);
}
