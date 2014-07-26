// VideoEncodeDlg.h : header file
//

#if !defined(AFX_VIDEOENCODEDLG_H__F80B0570_069F_478A_A476_15CC382360A2__INCLUDED_)
#define AFX_VIDEOENCODEDLG_H__F80B0570_069F_478A_A476_15CC382360A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CVideoEncodeDlg dialog
//#include "Afxmt.h"

#include "vfw.h"
#include "DarwDialog.h"




class CVideoEncodeDlg : public CDarwDialog
{
// Construction
public:
	CVideoEncodeDlg(CWnd* pParent = NULL); // standard constructor
	
	DWORD          m_Frame;            //��¼֡��
	COMPVARS       m_Com;              //ѹ������
	BITMAPINFO     m_InInfo,m_OutInfo; //λͼ��ʽ
	PAVIFILE       m_pFile;            //AVI�ļ�
	AVISTREAMINFO  strhdr;             //AVI����Ϣ
	PAVISTREAM     ps;                 //AVI��ָ��
	BOOL           m_Captured;         //�Ƿ�ʼ��׽
	CRect wndRC;
// Dialog Data
	//{{AFX_DATA(CVideoEncodeDlg)
	enum { IDD = IDD_DIALOG_ViDEOSHOW };
	CStatic	m_Panel;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoEncodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void   InitCompress();
	HICON  m_hIcon;
	HWND   m_hWndVideo; //��Ƶ��ʾ����
	void	Start(CString filename);
	// Generated message map functions
	//{{AFX_MSG(CVideoEncodeDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

struct PMP{
	HWND hwnd;
	int   NAME;


};
static PMP ph;


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOENCODEDLG_H__F80B0570_069F_478A_A476_15CC382360A2__INCLUDED_)
