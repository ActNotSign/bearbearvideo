// BearBearVideoDlg.h : header file
//
//{{AFX_INCLUDES()
#include "webbrowser.h"
//}}AFX_INCLUDES

#if !defined(AFX_BEARBEARVIDEODLG_H__674FB514_8F37_4E2F_AE8D_9BFEA3AB7809__INCLUDED_)
#define AFX_BEARBEARVIDEODLG_H__674FB514_8F37_4E2F_AE8D_9BFEA3AB7809__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBearBearVideoDlg dialog

#include "DarwDialog.h"
#include "DrawButton.h"
#include "vfw.h"
#include "DrawToolBar.h"
#include "DrawTab.h"
#include "MakeVideo.h"
#include "ShowWindow.h"
#include "DrawListCtrl.h"

#include "VideoShow.h"
#include "VideoEncodeDlg.h"

//线程调用的结构体
struct RWAVEPAM
{
	HWND hWnd;
	CString filename;
	CMakeVideo makevido;
	int time ;
	int smapsize;
	int freq;
	CRect rc;
	BOOL m;

};
static BOOL is=FALSE;
static RWAVEPAM lp;

#define MS_START	WM_USER+1
#define MS_STOP	WM_USER+2
#define MS_FINSH	WM_USER+3

class CBearBearVideoDlg : public CDarwDialog
{
// Construction
private :

	void CreateThread();
	//创建菜单栏
	DrawToolBar m_ToolBar;
	CImageList m_ImageList;
	//tab
	CDrawTab m_tab;
	//线程句柄；

	HANDLE  handle;

	//是否是暂停以后的开始
	BOOL m_isstop;

	//
	CVideoEncodeDlg m_vw;
public:
	CShowWindow sl;
	void CreateTab();
	BOOL m_is;
	CBearBearVideoDlg(CWnd* pParent = NULL);	// standard constructor




	// Dialog Data
	//{{AFX_DATA(CBearBearVideoDlg)
	enum { IDD = IDD_BEARBEARVIDEO_DIALOG };
	DrawButton	m_ok;
	DrawButton	m_s;
	DrawButton	m_shuzhi;
	CWebBrowser	m_Web;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBearBearVideoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBearBearVideoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnStop();
	afx_msg void OnClose();
	afx_msg LRESULT   OnFullData(WPARAM wParam,LPARAM lParam);	
	afx_msg void OnFinsh();


	afx_msg LRESULT OnMFinsh(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMStop(WPARAM wParam,LPARAM lParam);

	afx_msg LRESULT OnMStart(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void SVideoWave();
	void Makeit();
	void WhatShow();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEARBEARVIDEODLG_H__674FB514_8F37_4E2F_AE8D_9BFEA3AB7809__INCLUDED_)
