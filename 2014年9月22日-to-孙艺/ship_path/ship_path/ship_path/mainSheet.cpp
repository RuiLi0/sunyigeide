// mainSheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ship_path.h"
#include "mainSheet.h"


// mainSheet

IMPLEMENT_DYNAMIC(mainSheet, CPropertySheet)

mainSheet::mainSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	//����������ҳ�ӵ����Ա�
	AddPage(&ship1);
	AddPage(&ship2);
	AddPage(&ship3);

}

mainSheet::mainSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

	pParentWnd->GetWindowTextW(ship1.pathname1);
	pParentWnd->GetWindowTextW(ship2.pathname2);
	pParentWnd->GetWindowTextW(ship3.pathname3);
	//����������ҳ�ӵ����Ա�
	AddPage(&ship1);
	AddPage(&ship2);
	AddPage(&ship3);
}

mainSheet::~mainSheet()
{
}


BEGIN_MESSAGE_MAP(mainSheet, CPropertySheet)
END_MESSAGE_MAP()


// mainSheet ��Ϣ�������
