
// ship_path.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cship_pathApp: 
// �йش����ʵ�֣������ ship_path.cpp
//

class Cship_pathApp : public CWinApp
{
public:
	Cship_pathApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cship_pathApp theApp;