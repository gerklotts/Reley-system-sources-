// UserName.cpp : implementation file
//

#include "stdafx.h"
#include "DiO.h"
#include "UserName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserName dialog


CUserName::CUserName(CWnd* pParent /*=NULL*/) : CDialog(CUserName::IDD, pParent) {
	//{{AFX_DATA_INIT(CUserName)
	m_UserName = "";
	//}}AFX_DATA_INIT
}


void CUserName::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserName)
	DDX_Text(pDX, IDC_USER_NAME, m_UserName);
	DDV_MaxChars(pDX, m_UserName, 20);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserName, CDialog)
	//{{AFX_MSG_MAP(CUserName)
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserName message handlers

BOOL CUserName::OnInitDialog() {
	CDialog::OnInitDialog();
	if(!strcmp(m_UserName, START_USER_NAME))
		m_UserName = "";
	UpdateData(false);
	return(true);  // return TRUE unless you set the focus to a control EXCEPTION: OCX Property Pages should return FALSE
}

void CUserName::OnCancelMode() {
	CDialog::OnCancelMode();
}
