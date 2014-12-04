#pragma once
#include "afxwin.h"


// Ship3 对话框

class Ship3 : public CPropertyPage
{
	DECLARE_DYNAMIC(Ship3)

public:
	Ship3();
	virtual ~Ship3();

// 对话框数据
	enum { IDD = IDD_SHIP3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic shipName3;
	CStatic type3;
	CStatic loadStatus3;
	CStatic LOA3;
	CStatic breadth3;
	CStatic draft3;
	CStatic DISP_V3;
	CStatic image3;

	CString pathname3;
	afx_msg void OnPaint();

	CStatic distance;
};
