#if !defined(AFX_SET_H__6BA703E8_2EA5_4A0F_9E51_3ABFD00C6F6E__INCLUDED_)
#define AFX_SET_H__6BA703E8_2EA5_4A0F_9E51_3ABFD00C6F6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Set.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSet dialog
#include "DrawEdit.h"
#include "NewButton.h"
class CSet : public CPropertyPage
{
	DECLARE_DYNCREATE(CSet)

// Construction
public:
	void DrawDialog();
	CSet();
	~CSet();

	struct vset
	{
		CString filename;
		CString path;
		int time;
	};
	 vset m_vset;
// Dialog Data
	//{{AFX_DATA(CSet)
	enum { IDD = IDD_OLE_PROPPAGE_SET };
	CNewButton	m_selete;
	CDrawEdit	m_filepathe;
	CDrawEdit	m_filenamee;
	CDrawEdit	m_avitime;
	UINT	m_atime;
	BOOL	m_video;
	BOOL	m_mouse;
	CString	m_space;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSet)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSelete();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAvitime();
	afx_msg void OnCheckVideo();
	afx_msg void OnCheckMouse();
	afx_msg void OnChangeFilenamee();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void initEdit();
	// 判读是否录制声音
	BOOL m_hasWave;
	afx_msg void OnBnClickedCheckWave();
	// 判断是否生成文
	BOOL m_checkMake;
	// 判断是否生成avi
	BOOL m_suerAVI;
	afx_msg void OnBnClickedCheckMake();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SET_H__6BA703E8_2EA5_4A0F_9E51_3ABFD00C6F6E__INCLUDED_)
