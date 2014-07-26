// BearBearVideo.h : main header file for the BEARBEARVIDEO application
//

#if !defined(AFX_BEARBEARVIDEO_H__31307010_9910_41C5_9C8D_504F147BFEFF__INCLUDED_)
#define AFX_BEARBEARVIDEO_H__31307010_9910_41C5_9C8D_504F147BFEFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBearBearVideoApp:
// See BearBearVideo.cpp for the implementation of this class
//

class CBearBearVideoApp : public CWinApp
{
public:
	CBearBearVideoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBearBearVideoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBearBearVideoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEARBEARVIDEO_H__31307010_9910_41C5_9C8D_504F147BFEFF__INCLUDED_)
