#if !defined(AFX_INPUTSETTINGS_H__2A3F47DC_1A5C_4690_92CE_9EE8E6567EB5__INCLUDED_)
#define AFX_INPUTSETTINGS_H__2A3F47DC_1A5C_4690_92CE_9EE8E6567EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputSettings dialog

class CInputSettings : public CDialog {
// Construction
public:
	CInputSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputSettings)
	enum { IDD = IDD_SET_INPUT };
	CSliderCtrl	m_SliderClrHiR;
	CSliderCtrl	m_SliderClrHiG;
	CSliderCtrl	m_SliderClrHiB;
	CSliderCtrl	m_SliderClrLoR;
	CSliderCtrl	m_SliderClrLoG;
	CSliderCtrl	m_SliderClrLoB;
	CSliderCtrl	m_SliderBkgHiR;
	CSliderCtrl	m_SliderBkgHiG;
	CSliderCtrl	m_SliderBkgHiB;
	CSliderCtrl	m_SliderBkgLoR;
	CSliderCtrl	m_SliderBkgLoG;
	CSliderCtrl	m_SliderBkgLoB;
	CString	m_inputNo;
	CString	m_byteClrHiR;
	CString	m_byteClrHiG;
	CString	m_byteClrHiB;
	CString	m_byteClrLoR;
	CString	m_byteClrLoG;
	CString	m_byteClrLoB;
	CString	m_byteBkgHiR;
	CString	m_byteBkgHiG;
	CString	m_byteBkgHiB;
	CString	m_byteBkgLoR;
	CString	m_byteBkgLoG;
	CString	m_byteBkgLoB;
	//}}AFX_DATA
	CButton	m_btn[2];
	CString	m_Text[2];
	unsigned char m_TextColour[2][3], m_BackGround[2][3];
	CBitmap m_bmp[2];
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void PrepareBMP(int NoBMP);
	// Generated message map functions
	//{{AFX_MSG(CInputSettings)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnUpdateText_1();
	afx_msg void OnUpdateText_0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTSETTINGS_H__2A3F47DC_1A5C_4690_92CE_9EE8E6567EB5__INCLUDED_)
