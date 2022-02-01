// DiODlg.h : header file
//

#if !defined(AFX_DIODLG_H__711C3AD2_0179_42EB_87D0_54A44EC50CD1__INCLUDED_)
#define AFX_DIODLG_H__711C3AD2_0179_42EB_87D0_54A44EC50CD1__INCLUDED_

#include "IPAddress.h"	// Added by ClassView
#include "MySocket.h"
#include "InputSettings.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDiODlg dialog

class CDiODlg : public CDialog {
// Construction
public:
	CDiODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDiODlg)
	enum { IDD = IDD_DIO_DLG };
	CStatic	m_Answer;
	CStatic	m_SocketStatus;
	CButton	m_btnRelease;
	CButton	m_btnRequest;
	CButton	m_btnOpen;
	CButton	m_btnSetIP;
	CButton	m_btnUserName;
	CButton	m_checkSaveRX;
	CString	m_UserName;
	CIPAddressCtrl	m_IP_Address;
	CString	m_Inputs;
	//}}AFX_DATA
	CButton	m_btnInputs[32];
//	CButton	m_btnRelaysOn[16];
//	CButton	m_btnRelaysOff[16];
	CButton	m_btnOutputs[16];
	unsigned char m_InTextColour[2][32][3];
	unsigned char m_InBackGround[2][32][3];
	char m_InText[2][32][30];
	int m_flgSaveRX;
	int m_ConnectTimer;
	int m_SocketOnTimer;

	DWORD m_InputsDWORD;
	WORD m_RelaysWORD, m_OutputsWORD;

	class CIPAddress m_SetIP;
	class CMySocket  m_MySocket;
	class CInputSettings m_InputSettings;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetInBMP(int HiLo, int No);
	void ReadINI();
	CBitmap m_bmpHi, m_bmpLo, m_bmpX, m_bmpIn[2][32];
	void Receive(char *pBuffer);
	void ServerOnConnect();
	void ServerOnClose();
protected:
	HICON m_hIcon;
	void CalckTimes(int No);
	void Set_btnSetIP();
	void SaveINI();
	void Set_btnHiLo(void);
	void FPrintfSaveRx(char * String);
	void FPrintfConect();

	void OnOutput(unsigned int No);
	void OnRelayOn(unsigned int No);
	void OnRelayOff(unsigned int No);
	void OnIn(unsigned int No);
	// Generated message map functions
	//{{AFX_MSG(CDiODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSaveRx();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnSetIP();
	afx_msg void OnOutput00();
	afx_msg void OnOutput01();
	afx_msg void OnOutput02();
	afx_msg void OnOutput03();
	afx_msg void OnOutput04();
	afx_msg void OnOutput05();
	afx_msg void OnOutput06();
	afx_msg void OnOutput07();
	afx_msg void OnOutput08();
	afx_msg void OnOutput09();
	afx_msg void OnOutput10();
	afx_msg void OnOutput11();
	afx_msg void OnOutput12();
	afx_msg void OnOutput13();
	afx_msg void OnOutput14();
	afx_msg void OnOutput15();

	afx_msg void OnRelayOn00();
	afx_msg void OnRelayOn01();
	afx_msg void OnRelayOn02();
	afx_msg void OnRelayOn03();
	afx_msg void OnRelayOn04();
	afx_msg void OnRelayOn05();
	afx_msg void OnRelayOn06();
	afx_msg void OnRelayOn07();
	afx_msg void OnRelayOn08();
	afx_msg void OnRelayOn09();
	afx_msg void OnRelayOn10();
	afx_msg void OnRelayOn11();
	afx_msg void OnRelayOn12();
	afx_msg void OnRelayOn13();
	afx_msg void OnRelayOn14();
	afx_msg void OnRelayOn15();

	afx_msg void OnRelayOff00();
	afx_msg void OnRelayOff01();
	afx_msg void OnRelayOff02();
	afx_msg void OnRelayOff03();
	afx_msg void OnRelayOff04();
	afx_msg void OnRelayOff05();
	afx_msg void OnRelayOff06();
	afx_msg void OnRelayOff07();
	afx_msg void OnRelayOff08();
	afx_msg void OnRelayOff09();
	afx_msg void OnRelayOff10();
	afx_msg void OnRelayOff11();
	afx_msg void OnRelayOff12();
	afx_msg void OnRelayOff13();
	afx_msg void OnRelayOff14();
	afx_msg void OnRelayOff15();

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

#endif // !defined(AFX_DIODLG_H__711C3AD2_0179_42EB_87D0_54A44EC50CD1__INCLUDED_)
