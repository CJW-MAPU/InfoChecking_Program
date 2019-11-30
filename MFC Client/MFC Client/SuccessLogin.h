#pragma once
#include "struct.h"

// SuccessLogin 대화 상자

class SuccessLogin : public CDialogEx
{
	DECLARE_DYNAMIC(SuccessLogin)

public:
	SuccessLogin(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SuccessLogin();
	CString Login_id;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	Player_Data Player__;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
};
