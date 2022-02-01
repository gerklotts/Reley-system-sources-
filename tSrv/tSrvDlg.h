// tSrvDlg.h : header file
//

#if !defined(AFX_TSRVDLG_H__4ABF31FB_2CEC_4795_8A44_30AC425A812F__INCLUDED_)
#define AFX_TSRVDLG_H__4ABF31FB_2CEC_4795_8A44_30AC425A812F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"		// main symbols
#include "ListeningSocket.h"	// Added by ClassView
#include "ServSocket.h"	// Added by ClassView

#define NUMB_CLIENTS 8

/////////////////////////////////////////////////////////////////////////////
// CTSrvDlg dialog

class CTSrvDlg : public CDialog {
// Construction
public:
	CTSrvDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTSrvDlg)
	enum { IDD = IDD_TSRV_DIALOG };
	CButton	m_btnServPort;
	CString	m_ServerIP;
	//}}AFX_DATA
	CButton	m_btnInputs[32];
	CButton	m_btnRelays[16];
	CButton	m_btnOutputs[16];

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTSrvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	DWORD m_InputsDWORD;
	WORD  m_RelaysWORD, m_OutputsWORD;
	CBitmap m_bmpOn, m_bmpOnGrey, m_bmpOff, m_bmpOffGrey;
	unsigned char bIP[4];
	class CListeningSocket m_ListeningSocket;
	class CServSocket m_ServSocket[NUMB_CLIENTS+1];

// Implementation
public:
	void OnAccept();
	void Receive(char *);

protected:
	HICON m_hIcon;

	void SaveINI();
	void FPrintfSaveRx(char *);
	void Set_btnHiLo(void);
	void OnIn(int);
	void SendToAll(void);

	// Generated message map functions
	//{{AFX_MSG(CTSrvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnServIpPort();
	afx_msg void OnIn00();
	afx_msg void OnIn01();
	afx_msg void OnIn02();
	afx_msg void OnIn03();
	afx_msg void OnIn04();
	afx_msg void OnIn05();
	afx_msg void OnIn06();
	afx_msg void OnIn07();
	afx_msg void OnIn08();
	afx_msg void OnIn09();
	afx_msg void OnIn10();
	afx_msg void OnIn11();
	afx_msg void OnIn12();
	afx_msg void OnIn13();
	afx_msg void OnIn14();
	afx_msg void OnIn15();
	afx_msg void OnIn16();
	afx_msg void OnIn17();
	afx_msg void OnIn18();
	afx_msg void OnIn19();
	afx_msg void OnIn20();
	afx_msg void OnIn21();
	afx_msg void OnIn22();
	afx_msg void OnIn23();
	afx_msg void OnIn24();
	afx_msg void OnIn25();
	afx_msg void OnIn26();
	afx_msg void OnIn27();
	afx_msg void OnIn28();
	afx_msg void OnIn29();
	afx_msg void OnIn30();
	afx_msg void OnIn31();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSRVDLG_H__4ABF31FB_2CEC_4795_8A44_30AC425A812F__INCLUDED_)
