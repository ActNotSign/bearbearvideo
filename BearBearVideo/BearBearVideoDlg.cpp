// BearBearVideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "BearBearVideoDlg.h"
#include <windowsx.h>
#include ".\bearbearvideodlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

__declspec(dllexport) void SetHook(HWND hWnd);
__declspec(dllexport) void UnHook();
__declspec(dllexport) POINT GetPoint();
__declspec(dllexport) HBITMAP CatchScreen(LPRECT lpRect);

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
const CString PICNAME="C:\\tv.lbxx";
LONG CALLBACK WaveIOProc(LPMMIOINFO lpmmioInfo, UINT uMsg, 
                         LPARAM lParam1, LPARAM lParam2);
DWORD WINAPI ThreadProc();

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBearBearVideoDlg dialog

CBearBearVideoDlg::CBearBearVideoDlg(CWnd* pParent /*=NULL*/)
	: CDarwDialog(CBearBearVideoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBearBearVideoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_is=FALSE;
	handle=NULL;
	m_isstop=FALSE;
}

void CBearBearVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBearBearVideoDlg)
	DDX_Control(pDX, IDC_OK, m_ok);
	DDX_Control(pDX, IDC_STOP, m_s);
	DDX_Control(pDX, IDOK, m_shuzhi);
	DDX_Control(pDX, IDC_EXPLORER, m_Web);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBearBearVideoDlg, CDarwDialog)
	//{{AFX_MSG_MAP(CBearBearVideoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_CLOSE()
	ON_MESSAGE(MM_WIM_DATA,OnFullData)
	ON_BN_CLICKED(IDC_OK, OnFinsh)
	//自定义消息
	ON_MESSAGE(MS_START,OnMStart)
	ON_MESSAGE(MS_STOP,OnMStop)
	ON_MESSAGE(MS_FINSH,OnMFinsh)

	//}}AFX_MSG_MAP
//	ON_WM_ACTIVATEAPP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBearBearVideoDlg message handlers


BOOL CBearBearVideoDlg::OnInitDialog()
{


	CDarwDialog::OnInitDialog();

	//ad
	m_Web.Navigate ("9454.pqpq.net//ad.htm",NULL,NULL,NULL,NULL);
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);
	// Set small icon
//	CreateToolBar();
	// TODO: Add extra initialization here
//set hook
	SetHook(this->m_hWnd);

	CreateTab();
	m_s.EnableWindow (FALSE);
	m_ok.EnableWindow (FALSE);

	lp.makevido .InitWave ((LPMMIOPROC)WaveIOProc);



	::SetWindowPos (this->m_hWnd ,HWND_TOPMOST,0,0,0,0,SWP_NOSIZE |SWP_NOMOVE);

	//设置程序标题
	SetWindowText("熊熊软件-0.1<版>视频录像专家");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBearBearVideoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBearBearVideoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDarwDialog::OnPaint();
	}
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	CoInitialize(NULL);
	while(TRUE)
	{

		if(is)
		{	

			HBITMAP bit;

			if(lp.m)
			{
				//有鼠标
				bit=CatchScreen(&(lp.rc) );
			}else
			{
				//没鼠标

				bit=lp.makevido.CatchBitmap (&(lp.rc) );

			}
			lp.makevido .SavePicture(bit,PICNAME);
			::DeleteObject (bit);
			
			lp.makevido.MakeAvi(lp.filename ,lp.time ,PICNAME ,TRUE );
			
			lp.makevido .RecordWave (lp.smapsize ,lp.freq,lp.hWnd  );
			is=FALSE;
		}
		else
		{

			HBITMAP bit;

			if(lp.m)
			{
				//有鼠标
				bit=CatchScreen(&(lp.rc) );
			}else
			{
				//没鼠标

				bit=lp.makevido.CatchBitmap (&(lp.rc) );

			}

			lp.makevido .SavePicture(bit,PICNAME);
			::DeleteObject (bit);
			lp.makevido.MakeAvi(lp.filename ,lp.time ,PICNAME ,FALSE);
			
		}
		Sleep(340);
	}
	return TRUE;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBearBearVideoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBearBearVideoDlg::OnOK() 
{
   // TODO: Add your control notification handler code here
	if(m_tab.m_dset .m_vset .path !="" & m_tab.m_dset .m_vset .filename !="" )
	{
		if(!m_isstop)
		{
			CreateThread();
		}else
		{
			if(handle!=NULL)
			{						
				::ResumeThread (handle);
				//判断是否暂停视频录制
				if(m_tab.m_dset .m_video  )
				{
					m_vw.m_Captured =TRUE;
				}	
			}
			else
			{
				//判断是否暂停视频录制
				m_vw.m_Captured =TRUE;
			}
			//控制窗口状态
			m_tab.m_dlz .m_hide .str ="录制中";
			m_tab.m_dlz .m_hide .is =TRUE;
			m_s.EnableWindow ();
			m_shuzhi.EnableWindow (FALSE);
			m_ok.EnableWindow ();
			//	m_isstop=FALSE;
		}

	}else
	{
		MessageBox("请选择保存路径和文件名");

	}

}





void CBearBearVideoDlg::CreateTab()
{
	m_tab.Create (IDD_TAB);
	CRect rc;
	m_tab.GetWindowRect (&rc);
	m_tab.MoveWindow (0,0,rc.Width (),rc.Height ());
	m_tab.ShowWindow (SW_SHOW);
	//初始化音频窗口句柄.
	m_tab.m_dwav .m_hWnd =m_hWnd;
}



void CBearBearVideoDlg::OnStop() 
{
	CString s;
	m_s.GetWindowText (s);
	::SuspendThread (handle);
	m_s.EnableWindow (FALSE);
	m_shuzhi.EnableWindow ();

	m_isstop=TRUE;

	if(	m_vw.m_Captured)
		m_vw.m_Captured =FALSE;
}

void CBearBearVideoDlg::OnClose() 
{
	
	UnHook();
	if(handle!=NULL)
	{	

		DWORD d;
		::GetExitCodeThread (handle,&d);
		::TerminateThread (handle,d);	
		lp.makevido.Stop(m_tab.m_dset .m_vset .filename,m_tab.m_dset .m_vset .path,
			PICNAME);
		
	}

	if(::IsWindow (m_vw.m_hWnd))
		m_vw.OnCancel ();


	lp.makevido.StopWave ();

	CDarwDialog::OnClose();
}

LRESULT  CBearBearVideoDlg::OnFullData(WPARAM wParam,LPARAM lParam)
{


	lp.makevido .StopWave ();

	is=TRUE;
	return 0;
}


LONG CALLBACK WaveIOProc(LPMMIOINFO lpmmioInfo, UINT uMsg, 
                         LPARAM lParam1, LPARAM lParam2)
{
	static int  file = 0;
           int  nStatus;
           LONG lStatus;
	switch(uMsg)
    {
		case MMIO_CREATE:
			file=_lcreat((LPSTR)lParam1, 0);
			if(file==-1)
				return(MMIOERR_CANNOTOPEN);
			return(0);
		case MMIOM_OPEN:
			file=_lopen((LPSTR)lParam1, MMIO_WRITE);
			if(file==-1)
			{
				file=_lcreat((LPSTR)lParam1, 0);
			}
			if(file == -1)
				return(MMIOERR_CANNOTOPEN);
			else
			{
				lpmmioInfo->lDiskOffset = 0;
				return(0);
			}

       case MMIOM_CLOSE:
              return(_lclose(file));
       case MMIOM_READ:
              nStatus=_lread(file, (LPSTR)lParam1, (int)lParam2);
              lpmmioInfo->lDiskOffset += (int)lParam2;
              return((LONG)nStatus);
       case MMIOM_WRITEFLUSH:
		   {
              nStatus=_lwrite(file, (LPSTR)lParam1, (int)lParam2);
              lpmmioInfo->lDiskOffset += (int)lParam2;
              return((LONG)nStatus);
		   }
       case MMIOM_SEEK:
              lStatus=_llseek(file, (LONG)lParam1, (int)lParam2);
              lpmmioInfo->lDiskOffset=lStatus;
              return(lStatus);
    }
	return(0);
}





//void CBearBearVideoDlg::OnActivateApp(BOOL bActive, DWORD dwThreadID)
//{
//	CDarwDialog::OnActivateApp(bActive, dwThreadID);
//
//	// TODO: 在此处添加消息处理程序代码
//}

void CBearBearVideoDlg::WhatShow()
{
	//处理录制时程序的现实方式
	m_tab.m_dlz.SetWindowShow (this->m_hWnd );
}


//创建多线程
void CBearBearVideoDlg::CreateThread()
{


	if(m_tab.m_dlz .MakeWhat ())
	{
		
		if(!m_tab.m_dlz.m_video )
		{		
			//是否同时录制视频
			if(m_tab.m_dset .m_video  )
			{
				SVideoWave();
			}	
			
			lp.rc =m_tab.m_dlz .MakeWhat ();	
			lp.hWnd =this->m_hWnd ;
			lp.makevido .nFrames =0;
			lp.filename =m_tab.m_dset .m_vset .filename;
			lp.time =m_tab.m_dset .m_vset .time ;
			lp.freq =m_tab.m_dwav .GetFreq ();
			lp.smapsize =m_tab.m_dwav.GetSampsize () ;
			lp.m =m_tab.m_dset.m_mouse;
			//创建线程并立即运行
			handle= ::CreateThread (NULL,0,ThreadProc,(LPVOID)&lp ,0,NULL);
			//窗口的显示
			
			//判断是否带录音
			if(m_tab.m_dset .m_hasWave )
			{
				lp.makevido .RecordWave (lp.smapsize ,lp.freq ,this->m_hWnd );
			}
			
			m_s.EnableWindow ();
			m_shuzhi.EnableWindow (FALSE);
			m_ok.EnableWindow ();
			m_isstop=TRUE;
			WhatShow();
			
		}else
		{
			SVideoWave();

			m_s.EnableWindow ();
			m_shuzhi.EnableWindow (FALSE);
			m_ok.EnableWindow ();
		}
	}else
	{
		MessageBox("你没有选择录制的窗口");
	}
}

void CBearBearVideoDlg::Makeit()
{
}

void CBearBearVideoDlg::OnFinsh() 
{
	if(handle!=NULL)
	{	

		DWORD d;
		::GetExitCodeThread (handle,&d);
		if(!::TerminateThread (handle,d))
		{
			MessageBox("线程关闭失败");
		}
		handle=NULL;
		
		m_s.EnableWindow (FALSE);
		m_shuzhi.EnableWindow (TRUE);
		m_ok.EnableWindow (FALSE);
		
		lp.makevido .Stop(m_tab.m_dset .m_vset .filename,
			m_tab.m_dset .m_vset .path,
			PICNAME);


		m_isstop=FALSE;		
	}
	if(::IsWindow (m_vw.m_hWnd ))
	{
		m_vw.OnCancel ();
		m_s.EnableWindow (FALSE);
		m_shuzhi.EnableWindow (TRUE);
		m_ok.EnableWindow (FALSE);
	}
}
//自定义消息处理
LRESULT CBearBearVideoDlg::OnMStart(WPARAM wParam,LPARAM lParam) 
{

	OnOK() ;	
	return 0;
}

LRESULT CBearBearVideoDlg::OnMFinsh(WPARAM wParam,LPARAM lParam) 
{

	OnFinsh() ;
	AfxGetMainWnd ()->ShowWindow (SW_SHOW);
	m_tab.m_dlz .m_hide .SendMessage (WM_CLOSE);


	return 0;
}

LRESULT CBearBearVideoDlg::OnMStop(WPARAM wParam,LPARAM lParam) 
{
	OnStop() ;
	m_tab.m_dlz .m_hide .is =TRUE;
	m_tab.m_dlz .m_hide .str ="暂停中";


	return 0;
	
}


void CBearBearVideoDlg::SVideoWave()
{


	m_vw.Create (IDD_DIALOG_ViDEOSHOW);
	m_vw.ShowWindow (SW_SHOW);
	//处理当同时录制摄像头时候的名字
	CString filename;
	if(m_tab.m_dset .m_video  )
	{
		filename="摄像头_"+m_tab.m_dset .m_vset .filename;
	}else
	{
		filename=m_tab.m_dset .m_vset .filename;
	}
	m_vw.Start(filename);
}
