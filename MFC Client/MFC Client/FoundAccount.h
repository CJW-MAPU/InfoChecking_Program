#pragma once


// FoundAccount 대화 상자

class FoundAccount : public CDialogEx
{
	DECLARE_DYNAMIC(FoundAccount)

public:
	FoundAccount(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~FoundAccount();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedFoundid2();
	afx_msg void OnBnClickedButton2();
	CString FNDID_Name;
	afx_msg void OnEnChangeEdit1();
	CString FNDID_PN;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit8();
	CString FNDPW_Name;
	CString FNDPW_ID;
};
