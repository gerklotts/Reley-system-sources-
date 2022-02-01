// tSrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tSrv.h"
#include "tSrvDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define INI_FILE ".\\tServ.ini"
#define DiO_INI_FILE ".\\DiO.ini"

CTSrvDlg *pTSrvDlg;

/////////////////////////////////////////////////////////////////////////////
// CTSrvDlg dialog

CTSrvDlg::CTSrvDlg(CWnd* pParent /*=NULL*/) : CDialog(CTSrvDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CTSrvDlg)
	m_ServerIP = _T("xxx.xxx.xxx");
	//}}AFX_DATA_INIT
	m_InputsDWORD = 0;
	m_OutputsWORD = 0;
	m_RelaysWORD = 0;
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTSrvDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTSrvDlg)
	DDX_Control(pDX, IDC_IP_PORT, m_btnServPort);
	DDX_Text(pDX, IDC_SERV_IP, m_ServerIP);
	//}}AFX_DATA_MAP
	for(int i = 0; i < NUMB_CLIENTS; i++) {
		DDX_Text(pDX, IDC_USER_IP_1 + i, m_ServSocket[i].m_UserIP);
	}
	for(i = 0; i < 32; i++) {
		DDX_Control(pDX, IDC_IN_0 + i, m_btnInputs[i]);
	}
	for(i = 0; i < 16; i++) {
		DDX_Control(pDX, IDC_OUT_0 + i, m_btnOutputs[i]);
		DDX_Control(pDX, IDC_RELAY_0 + i, m_btnRelays[i]);
	}
}

BEGIN_MESSAGE_MAP(CTSrvDlg, CDialog)
	//{{AFX_MSG_MAP(CTSrvDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IP_PORT, OnServIpPort)

	ON_BN_CLICKED(IDC_IN_0, OnIn00)
	ON_BN_CLICKED(IDC_IN_1, OnIn01)
	ON_BN_CLICKED(IDC_IN_2, OnIn02)
	ON_BN_CLICKED(IDC_IN_3, OnIn03)
	ON_BN_CLICKED(IDC_IN_4, OnIn04)
	ON_BN_CLICKED(IDC_IN_5, OnIn05)
	ON_BN_CLICKED(IDC_IN_6, OnIn06)
	ON_BN_CLICKED(IDC_IN_7, OnIn07)
	ON_BN_CLICKED(IDC_IN_8, OnIn08)
	ON_BN_CLICKED(IDC_IN_9, OnIn09)
	ON_BN_CLICKED(IDC_IN_10, OnIn10)
	ON_BN_CLICKED(IDC_IN_11, OnIn11)
	ON_BN_CLICKED(IDC_IN_12, OnIn12)
	ON_BN_CLICKED(IDC_IN_13, OnIn13)
	ON_BN_CLICKED(IDC_IN_14, OnIn14)
	ON_BN_CLICKED(IDC_IN_15, OnIn15)
	ON_BN_CLICKED(IDC_IN_16, OnIn16)
	ON_BN_CLICKED(IDC_IN_17, OnIn17)
	ON_BN_CLICKED(IDC_IN_18, OnIn18)
	ON_BN_CLICKED(IDC_IN_19, OnIn19)
	ON_BN_CLICKED(IDC_IN_20, OnIn20)
	ON_BN_CLICKED(IDC_IN_21, OnIn21)
	ON_BN_CLICKED(IDC_IN_22, OnIn22)
	ON_BN_CLICKED(IDC_IN_23, OnIn23)
	ON_BN_CLICKED(IDC_IN_24, OnIn24)
	ON_BN_CLICKED(IDC_IN_25, OnIn25)
	ON_BN_CLICKED(IDC_IN_26, OnIn26)
	ON_BN_CLICKED(IDC_IN_27, OnIn27)
	ON_BN_CLICKED(IDC_IN_28, OnIn28)
	ON_BN_CLICKED(IDC_IN_29, OnIn29)
	ON_BN_CLICKED(IDC_IN_30, OnIn30)
	ON_BN_CLICKED(IDC_IN_31, OnIn31)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTSrvDlg message handlers

BOOL CTSrvDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, true);			// Set big icon
	SetIcon(m_hIcon, false);		// Set small icon
	pTSrvDlg = this;
	m_ListeningSocket.m_IP_Port = GetPrivateProfileInt("Server", "IP_Port",     22022, INI_FILE);
	if(m_ListeningSocket.m_IP_Port < 1024 || 0xFFFF < m_ListeningSocket.m_IP_Port)
		m_ListeningSocket.m_IP_Port = 22022;
	m_ListeningSocket.Create();
	m_ListeningSocket.Listen();
	char String[1000];
	gethostname(String, 1000);
	hostent *HostEntry = gethostbyname(String);
	m_ServerIP = inet_ntoa(*(struct in_addr *)*HostEntry->h_addr_list);
	bIP[0] = ((struct in_addr *)*HostEntry->h_addr_list)->S_un.S_un_b.s_b1;
	bIP[1] = ((struct in_addr *)*HostEntry->h_addr_list)->S_un.S_un_b.s_b2;
	bIP[2] = ((struct in_addr *)*HostEntry->h_addr_list)->S_un.S_un_b.s_b3;
	bIP[3] = ((struct in_addr *)*HostEntry->h_addr_list)->S_un.S_un_b.s_b4;
	SaveINI();
	CTime CurrTime = CTime::GetCurrentTime();
	CString s = CurrTime.Format("--------  %Y.%m.%d %H:%M:%S  ---------\n");
	sprintf(String, "%s", s);
	FPrintfSaveRx(String);
	m_bmpOn.LoadBitmap(IDB_ON);
	m_bmpOff.LoadBitmap(IDB_OFF);
	m_bmpOnGrey.LoadBitmap(IDB_ON_G);
	m_bmpOffGrey.LoadBitmap(IDB_OFF_G);
	Set_btnHiLo();
	UpdateData(false);
	return(true);  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTSrvDlg::OnPaint() {
	if(IsIconic()) {
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTSrvDlg::OnQueryDragIcon() {
	return((HCURSOR)m_hIcon);
}

void CTSrvDlg::FPrintfSaveRx(char * String) {
//	if(m_flgSaveRX) {
		FILE *fp;
		if((fp = fopen(".\\tServ.SQL", "a")) != NULL) {
			fprintf(fp, String);
			fclose(fp);
		}
//	}
}

void CTSrvDlg::OnServIpPort() {
//	for(int i = 0; !m_ServSocket[i].m_Accepted && i < NUMB_CLIENTS; i++)
//		;
//	if(i < NUMB_CLIENTS) {
//		if(MessageBox("Server work.\nStop it ???", "Delay Server", MB_OKCANCEL) != IDOK)
//			return;
//	}
	CServIP_PortDlg ServIP_PortDlg;
	ServIP_PortDlg.m_Port = m_ListeningSocket.m_IP_Port;
	if(ServIP_PortDlg.DoModal() == IDOK && m_ListeningSocket.m_IP_Port != ServIP_PortDlg.m_Port) {
/*		for(int i = 0; i < NUMB_CLIENTS; i++) {
			if(m_ServSocket[i].m_Accepted) {
				m_ServSocket[i].Close();
				m_ServSocket[i].m_Accepted = false;
				m_ServSocket[i].m_Position = -1;
				m_pServSocket[i] = &m_DumySocket;
			}
		}*/
		m_ListeningSocket.Close();
		m_ListeningSocket.m_IP_Port = ServIP_PortDlg.m_Port;
		SaveINI();
		UpdateData(false);
		m_ListeningSocket.Create();
		m_ListeningSocket.Listen();
	}
}

void CTSrvDlg::SaveINI() {
	char String[200];
	sprintf(String, "%u", m_ListeningSocket.m_IP_Port);
	WritePrivateProfileString("Server", "IP_Port", String, INI_FILE);

	sprintf(String, "%d", bIP[0]);  WritePrivateProfileString("DiO", "IP_Address1", String, DiO_INI_FILE);
	sprintf(String, "%d", bIP[1]);  WritePrivateProfileString("DiO", "IP_Address2", String, DiO_INI_FILE);
	sprintf(String, "%d", bIP[2]);  WritePrivateProfileString("DiO", "IP_Address3", String, DiO_INI_FILE);
	sprintf(String, "%d", bIP[3]);  WritePrivateProfileString("DiO", "IP_Address4", String, DiO_INI_FILE);
	sprintf(String, "%d", m_ListeningSocket.m_IP_Port); WritePrivateProfileString("DiO", "IP_Port",     String, DiO_INI_FILE);

	/*	for(int i = 0; i < 10; i++) {
		char SectName[20];
		strcpy(SectName, BoardUsers[i]);
		for(int j = 0; j < 10; j++) {
			char KeyName[20];
			sprintf(KeyName, "User%d", j+1);
			WritePrivateProfileString(SectName, KeyName, m_UserName[i][j], INI_FILE);
		}
	} */
	sprintf(String, "IP Port = %u", m_ListeningSocket.m_IP_Port);
	m_btnServPort.SetWindowText(String);
}

// ###############################################################################################################################################
//   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server
//   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server   Server
// ###############################################################################################################################################

void CTSrvDlg::OnAccept() {
	for(int AcceptNo = 0; m_ServSocket[AcceptNo].m_Accepted && AcceptNo < (NUMB_CLIENTS+1); AcceptNo++)
		;
	if(AcceptNo == (NUMB_CLIENTS+1))
		return;
	UpdateData(true);
//	if(m_Check) AcceptNo = NUMB_CLIENTS; // TEST   TEST   TEST   TEST   TEST
	if(m_ListeningSocket.Accept(m_ServSocket[AcceptNo])) {
		if(AcceptNo == NUMB_CLIENTS) {
			char String[1000];
			char *pBuffer = m_ServSocket[NUMB_CLIENTS].m_Buffer;
			strcpy(pBuffer, "! DiO server:\\nReject. Too many users:\n");
			for(int i = 0;  i < NUMB_CLIENTS; i++) {
				sprintf(String, "%u : ", i + 1);
				strcat(pBuffer, String);
				strcat(pBuffer, m_ServSocket[i].m_UserIP);
				strcat(pBuffer, "\n");
			}
			m_ServSocket[NUMB_CLIENTS].Send(pBuffer, strlen(pBuffer) + 1);
			Sleep(300);
			m_ServSocket[NUMB_CLIENTS].Close();
			m_ServSocket[NUMB_CLIENTS].m_Accepted = false;
			return;
		}
		m_ServSocket[AcceptNo].m_Accepted = true;
		UINT tmpUINT;
		m_ServSocket[AcceptNo].GetPeerName(m_ServSocket[AcceptNo].m_UserIP, tmpUINT);
		UpdateData(false);
	}
}

void CTSrvDlg::SendToAll(void) {
	char BufferToSent[1000];
	sprintf(BufferToSent, "%08X %04X %04X", m_InputsDWORD, m_OutputsWORD, m_RelaysWORD);
	for(int i = 0; i < NUMB_CLIENTS; i++) {
		if(m_ServSocket[i].m_Accepted) {
			strcpy(m_ServSocket[i].m_Buffer, BufferToSent);
			m_ServSocket[i].Send(m_ServSocket[i].m_Buffer, strlen(BufferToSent), 0);
		}

	}
}

DWORD CheckDWORD[32] = {
	0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080,
	0x00000100, 0x00000200, 0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000, 0x00008000,
	0x00010000, 0x00020000, 0x00040000, 0x00080000, 0x00100000, 0x00200000, 0x00400000, 0x00800000,
	0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000
};
void CTSrvDlg::Set_btnHiLo(void) {
	for(int i = 0; i < 32; i++) {
		if(m_InputsDWORD & CheckDWORD[i])
			m_btnInputs[i].SetBitmap(m_bmpOn);
		else
			m_btnInputs[i].SetBitmap(m_bmpOff);
	}
	for(i = 0; i < 16; i++) {
		if(m_OutputsWORD & (WORD)CheckDWORD[i])
			m_btnOutputs[i].SetBitmap(m_bmpOnGrey);
		else
			m_btnOutputs[i].SetBitmap(m_bmpOffGrey);
		if(m_RelaysWORD & (WORD)CheckDWORD[i])
			m_btnRelays[i].SetBitmap(m_bmpOnGrey);
		else
			m_btnRelays[i].SetBitmap(m_bmpOffGrey);
	}
}

void CTSrvDlg::OnIn(int No) {
	m_InputsDWORD ^= CheckDWORD[No];
	Set_btnHiLo();
	SendToAll();
}

void CTSrvDlg::OnIn00() { OnIn( 0); }
void CTSrvDlg::OnIn01() { OnIn( 1); }
void CTSrvDlg::OnIn02() { OnIn( 2); }
void CTSrvDlg::OnIn03() { OnIn( 3); }
void CTSrvDlg::OnIn04() { OnIn( 4); }
void CTSrvDlg::OnIn05() { OnIn( 5); }
void CTSrvDlg::OnIn06() { OnIn( 6); }
void CTSrvDlg::OnIn07() { OnIn( 7); }
void CTSrvDlg::OnIn08() { OnIn( 8); }
void CTSrvDlg::OnIn09() { OnIn( 9); }
void CTSrvDlg::OnIn10() { OnIn(10); }
void CTSrvDlg::OnIn11() { OnIn(11); }
void CTSrvDlg::OnIn12() { OnIn(12); }
void CTSrvDlg::OnIn13() { OnIn(13); }
void CTSrvDlg::OnIn14() { OnIn(14); }
void CTSrvDlg::OnIn15() { OnIn(15); }
void CTSrvDlg::OnIn16() { OnIn(16); }
void CTSrvDlg::OnIn17() { OnIn(17); }
void CTSrvDlg::OnIn18() { OnIn(18); }
void CTSrvDlg::OnIn19() { OnIn(19); }
void CTSrvDlg::OnIn20() { OnIn(20); }
void CTSrvDlg::OnIn21() { OnIn(21); }
void CTSrvDlg::OnIn22() { OnIn(22); }
void CTSrvDlg::OnIn23() { OnIn(23); }
void CTSrvDlg::OnIn24() { OnIn(24); }
void CTSrvDlg::OnIn25() { OnIn(25); }
void CTSrvDlg::OnIn26() { OnIn(26); }
void CTSrvDlg::OnIn27() { OnIn(27); }
void CTSrvDlg::OnIn28() { OnIn(28); }
void CTSrvDlg::OnIn29() { OnIn(29); }
void CTSrvDlg::OnIn30() { OnIn(30); }
void CTSrvDlg::OnIn31() { OnIn(31); }


void CTSrvDlg::Receive(char *Buffer) {
	char String[1000];
	int i = atoi(&Buffer[1]);
	sprintf(String, "tSrv receive : \"%s\"\n", Buffer);
	FPrintfSaveRx(String);
	if(i < 0 || 15 < i) {
		MessageBox(Buffer, "WRONG NUMBRE !", MB_OK);
	} else if(Buffer[0] == 'r') {
		m_RelaysWORD &= ~CheckDWORD[i];
		Set_btnHiLo();
	} else if(Buffer[0] == 'R') {
		m_RelaysWORD |= CheckDWORD[i];
		Set_btnHiLo();
	} else if(Buffer[0] == 'o') {
		m_OutputsWORD ^= CheckDWORD[i];
		Set_btnHiLo();
	} else {
		MessageBox(Buffer, "WRONG COMMAND !", MB_OK);
	}
	SendToAll();
}
