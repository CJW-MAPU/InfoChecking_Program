#pragma once
#include "Main.h"

// ResultIDFND 대화 상자

class ResultIDFND : public CDialogEx
{
	DECLARE_DYNAMIC(ResultIDFND)

public:
	ResultIDFND(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ResultIDFND();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	Found_IDList FND_Player;
	Player_Data Player;
	afx_msg void OnBnClickedButton2();
};
