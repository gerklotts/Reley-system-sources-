// tSrv.h : main header file for the TSRV application
//

#if !defined(AFX_TSRV_H__925B879C_593A_49D5_A203_62D6AFC84AB3__INCLUDED_)
#define AFX_TSRV_H__925B879C_593A_49D5_A203_62D6AFC84AB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTSrvApp:
// See tSrv.cpp for the implementation of this class
//

class CTSrvApp : public CWinApp {
public:
	CTSrvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTSrvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTSrvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSRV_H__925B879C_593A_49D5_A203_62D6AFC84AB3__INCLUDED_)
