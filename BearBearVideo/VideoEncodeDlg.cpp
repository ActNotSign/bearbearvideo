// VideoEncodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BearBearVideo.h"
#include "VideoEncodeDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


/////////////////////////////////////////////////////////////////////////////
// CVideoEncodeDlg dialog


CVideoEncodeDlg::CVideoEncodeDlg(CWnd* pParent /*=NULL*/)
	: CDarwDialog(CVideoEncodeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoEncodeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	m_Captured = FALSE;

}

void CVideoEncodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoEncodeDlg)
	DDX_Control(pDX, IDC_PANEL, m_Panel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVideoEncodeDlg, CDarwDialog)
	//{{AFX_MSG_MAP(CVideoEncodeDlg)
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoEncodeDlg message handlers
CVideoEncodeDlg* pDlg;

LRESULT WINAPI EncodeCallback(HWND hWnd, LPVIDEOHDR lpVHdr)
{
//	CVideoEncodeDlg* pDlg = (CVideoEncodeDlg*)(CWnd::FromHandle(ph.hwnd));

	if ((pDlg->m_Captured) && (lpVHdr->dwFlags&VHDR_DONE))
	{
/**/	char* buffer = new char [lpVHdr->dwBytesUsed+1];
		memset(buffer,0,lpVHdr->dwBytesUsed+1);
		DWORD dwCkID         ; 
		DWORD dwCompFlags    ; 
		DWORD dwQuality = 6000; 	
		//视频压缩
		if (ICCompress(pDlg->m_Com.hic, 0, &pDlg->m_OutInfo.bmiHeader, buffer, &pDlg->m_InInfo.bmiHeader, 
			(unsigned char *)lpVHdr->lpData, &dwCkID, &dwCompFlags, pDlg->m_Frame++,0, dwQuality, NULL, NULL) == ICERR_OK)
		{		
			AVIStreamSetFormat(pDlg->ps ,pDlg->m_Frame,&pDlg->m_OutInfo,sizeof(pDlg->m_OutInfo));
			AVIStreamWrite(pDlg->ps,pDlg->m_Frame ,1, (LPBYTE) buffer,pDlg->m_OutInfo.bmiHeader.biSizeImage ,AVIIF_KEYFRAME,
				NULL,NULL);
		}

		delete[]buffer;
	}

 	return 1;
}

BOOL CVideoEncodeDlg::OnInitDialog()
{

	CDarwDialog::OnInitDialog();

	pDlg =this;
	ph.NAME =IDD_DIALOG_ViDEOSHOW;
	//Add "About..." menu item to system menu.
	//IDM_ABOUTBOX must be in the system command range.

	m_hWndVideo = capCreateCaptureWindow(NULL,WS_POPUP,1,1,10,10,m_hWnd,0);


	//连接驱动程序
	if (capDriverConnect(m_hWndVideo,0))
	{	
		::SetParent(m_hWndVideo,*this);
		::SetWindowLong(m_hWndVideo,GWL_STYLE,WS_CHILD);

		
		m_Panel.GetClientRect(wndRC);
		m_Panel.MapWindowPoints(this,wndRC);
		wndRC.DeflateRect(1,1,1,1);

		::SetWindowPos(m_hWndVideo,NULL,wndRC.left,wndRC.top,wndRC.Width(),wndRC.Height(),SWP_NOZORDER);
		::ShowWindow(m_hWndVideo,SW_SHOW);

		CAPDRIVERCAPS caps;
		capDriverGetCaps(m_hWndVideo,sizeof(caps),&caps);

		if (caps.fHasOverlay)
			capOverlay(m_hWndVideo,TRUE);

		CAPTUREPARMS params;
		capCaptureGetSetup(m_hWndVideo,&params,sizeof(params));

		params.fYield           = TRUE;
		params.fAbortLeftMouse  = FALSE;
		params.fAbortRightMouse = FALSE;
		params.fLimitEnabled    = FALSE;
		params.vKeyAbort        = FALSE;
		params.fCaptureAudio    = FALSE;
		
		capCaptureSetSetup(m_hWndVideo,&params,sizeof(params));
		capSetCallbackOnVideoStream(m_hWndVideo,EncodeCallback);

		capPreviewRate(m_hWndVideo,30);
		capPreview(m_hWndVideo,TRUE);


	}else
	{
		MessageBox("没有发现视频");
	}
	return TRUE; 
}



// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.



// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.


void CVideoEncodeDlg::OnCancel() 
{
	//终止回调函数
	capSetCallbackOnVideoStream(m_hWndVideo,NULL);
	//结束数据压缩
	ICCompressEnd(m_Com.hic);
	//关闭压缩句柄
	ICClose(m_Com.hic);
	if (m_Captured)
	{
		//关闭AVI文件流
		AVIStreamClose(ps);
		if(m_pFile != NULL)
			AVIFileRelease(m_pFile);
		AVIFileExit();	
		m_Captured=FALSE;
	}
	//停止捕捉
	capCaptureStop(m_hWndVideo);
	//断开驱动程序连接
	capDriverDisconnect(m_hWndVideo);

	CDarwDialog::OnCancel();
}

void CVideoEncodeDlg::OnOK() 
{
}

void CVideoEncodeDlg::InitCompress()
{
	capGetVideoFormat(m_hWndVideo,&m_InInfo ,sizeof(BITMAPINFO));
	capGetVideoFormat(m_hWndVideo,&m_OutInfo,sizeof(BITMAPINFO));
	memset(&m_Com,0,sizeof(COMPVARS));  
	m_Com.cbSize=sizeof(m_Com); 

	//利用代码选择压缩器
	m_Com.dwFlags=ICMF_COMPVARS_VALID;  

	m_Com.fccHandler=mmioFOURCC('M', 'S', 'V', 'C');
	m_Com.fccType=ICTYPE_VIDEO;   
	m_Com.lFrame=0;   
	m_Com.lKey=15;   
	m_Com.lKeyCount=0;  
	m_Com.lDataRate = 780;
	m_Com.lpbiOut=(BITMAPINFO*)&m_OutInfo; 	
	m_Com.hic= ICOpen(ICTYPE_VIDEO,mmioFOURCC('M', 'S', 'V', 'C'),ICMODE_COMPRESS);
	m_Com.cbState = 1180;

	//利用对话框选择压缩器
//	ICCompressorChoose(NULL,ICMF_CHOOSE_ALLCOMPRESSORS ,(LPVOID)&m_InInfo,NULL,&m_Com,"选择压缩类型");
	ICCompressGetFormat(m_Com.hic,&m_InInfo.bmiHeader,&m_OutInfo.bmiHeader);
	//开始压缩
	int ret = ICCompressBegin(m_Com.hic,(BITMAPINFO*)&m_InInfo,(BITMAPINFO*)&m_OutInfo);
	if (ret!=ICERR_OK )
		MessageBox("压缩失败");
}

void CVideoEncodeDlg::Start(CString filename)
{
	capGetVideoFormat(m_hWndVideo,&m_InInfo,sizeof(m_InInfo));
	m_Frame = 0 ;
	//AVI文件初始化
	AVIFileInit() ;
	//设置压缩参数
	InitCompress();

	//打开文件
	AVIFileOpen(&m_pFile,filename,OF_WRITE | OF_CREATE,NULL);
	memset(&strhdr, 0, sizeof(strhdr)) ;
	strhdr.fccType    = streamtypeVIDEO; 
	strhdr.fccHandler = 0  ;
	strhdr.dwScale    = 1  ;
	strhdr.dwRate     = 15; 
	strhdr.dwSuggestedBufferSize = m_InInfo.bmiHeader.biSizeImage;
	SetRect(&strhdr.rcFrame, 0, 0, m_InInfo.bmiHeader.biWidth, m_InInfo.bmiHeader.biHeight);
	ps = NULL;
	//文件文件流
	AVIFileCreateStream(m_pFile,&ps,&strhdr); 
	m_Captured = TRUE;

	//开始捕捉

	capCaptureSequenceNoFile(m_hWndVideo);
}

int CVideoEncodeDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	DWORD dwStyle   =  GetWindowLong(m_hWnd,GWL_STYLE);   
	SetWindowLong(m_hWnd,GWL_STYLE,dwStyle|WS_THICKFRAME );   
	
	if (CDarwDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CVideoEncodeDlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	lpncsp->rgrc ->left -=2;
	lpncsp->rgrc ->right +=1;
		
	CDarwDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}
