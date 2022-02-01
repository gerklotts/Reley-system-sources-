#if !defined(AFX_IPADDRESS_H__41B17382_449F_4EE2_A2B0_81BE7424EEB9__INCLUDED_)
#define AFX_IPADDRESS_H__41B17382_449F_4EE2_A2B0_81BE7424EEB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IPAddress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIPAddress dialog

#include "resource.h"		// main symbols


class CIPAddress : public CDialog {
// Construction
public:
	CIPAddress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIPAddress)
	enum { IDD = IDD_IP_ADDRESS };
	CIPAddressCtrl	m_IP_Address;
	UINT	m_IP_Port;
	//}}AFX_DATA
	BYTE	m_Address[4];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIPAddress)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDRESS_H__41B17382_449F_4EE2_A2B0_81BE7424EEB9__INCLUDED_)
