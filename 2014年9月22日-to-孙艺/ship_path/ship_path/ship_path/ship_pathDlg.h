
// ship_pathDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// Cship_pathDlg �Ի���
class Cship_pathDlg : public CDialogEx
{
// ����
public:
	Cship_pathDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SHIP_PATH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit pathName;
	CButton choosePath;
	afx_msg void OnBnClickedChoose();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
