#pragma once


// Register 대화 상자

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Register();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CString Register_ID;
	CString Register_PW;
	CString Register_PW2;
	CString Register_Name;
	CString Register_Email;
	CString Register_Cellnum;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox EmailCombo;
};
