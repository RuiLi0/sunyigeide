#pragma once
#include "afxwin.h"


// Ship1 �Ի���

class Ship1 : public CPropertyPage
{
	DECLARE_DYNAMIC(Ship1)

public:
	Ship1();
	virtual ~Ship1();

// �Ի�������
	enum { IDD = IDD_SHIP1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic image1;
	CStatic shipName1;
	CStatic type1;
	CStatic loadStatus1;
	CStatic LOA1;
	CStatic breadth1;
	CStatic draft1;

	CString pathname1;
	CStatic DISP_V1;
	afx_msg void OnPaint();
	CStatic hint;
};
