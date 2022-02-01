// IPAddress.cpp : implementation file
//

#include "stdafx.h"
#include "IPAddress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIPAddress dialog


CIPAddress::CIPAddress(CWnd* pParent /*=NULL*/) : CDialog(CIPAddress::IDD, pParent) {
	//{{AFX_DATA_INIT(CIPAddress)
	m_IP_Port = 5000;
	//}}AFX_DATA_INIT
}


void CIPAddress::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPAddress)
	DDX_Control(pDX, IDC_IP_ADDRESS, m_IP_Address);
	DDX_Text(pDX, IDC_IP_PORT, m_IP_Port);
	DDV_MinMaxUInt(pDX, m_IP_Port, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIPAddress, CDialog)
	//{{AFX_MSG_MAP(CIPAddress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPAddress message handlers

BOOL CIPAddress::OnInitDialog() {
	CDialog::OnInitDialog();
	m_IP_Address.SetAddress(m_Address[0], m_Address[1], m_Address[2], m_Address[3]);
	return(true);  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIPAddress::OnOK() {
	m_IP_Address.GetAddress(m_Address[0], m_Address[1], m_Address[2], m_Address[3]);
	CDialog::OnOK();
}
