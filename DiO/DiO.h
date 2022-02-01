// DiO.h : main header file for the DiO application
//

#if !defined(AFX_DIO_H__4FB3E0A8_2C3A_435D_AF63_206D95933607__INCLUDED_)
#define AFX_DIO_H__4FB3E0A8_2C3A_435D_AF63_206D95933607__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDiOApp:
// See DiO.cpp for the implementation of this class
//

class CDiOApp : public CWinApp {
public:
	CDiOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDiOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		// DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIO_H__4FB3E0A8_2C3A_435D_AF63_206D95933607__INCLUDED_)
