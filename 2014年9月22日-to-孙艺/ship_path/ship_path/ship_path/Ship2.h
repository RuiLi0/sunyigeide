#pragma once
#include "afxwin.h"


// Ship2 对话框

class Ship2 : public CPropertyPage
{
	DECLARE_DYNAMIC(Ship2)

public:
	Ship2();
	virtual ~Ship2();

// 对话框数据
	enum { IDD = IDD_SHIP2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic shipName2;
	CStatic type2;
	CStatic loadStatus2;
	CStatic LOA2;
	CStatic breadth2;
	CStatic draft2;
	CStatic DISP_V2;
	CStatic image2;

	CString pathname2;
	afx_msg void OnPaint();
};
