#pragma once
#include "Main.h"

// ResultPWFND 대화 상자

class ResultPWFND : public CDialogEx
{
	DECLARE_DYNAMIC(ResultPWFND)

public:
	ResultPWFND(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ResultPWFND();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	Player_Data Player;
	CString New_PW;
	CString Check_PW;
};
