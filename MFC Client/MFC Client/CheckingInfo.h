#pragma once
#include "struct.h"


// CheckingInfo 대화 상자

class CheckingInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CheckingInfo)

public:
	CheckingInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CheckingInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit3();
	int Update_Count;
	CString Info_Name;
	CString Info_Email;
	CString Info_CellNum;
	Player_Data Player;
	virtual BOOL OnInitDialog();
	afx_msg void OnStnClickedInfotext();
	afx_msg void OnBnClickedButton2();
};
