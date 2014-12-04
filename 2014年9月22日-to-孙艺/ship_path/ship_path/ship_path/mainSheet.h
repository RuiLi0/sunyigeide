#pragma once
#include "Ship1.h"
#include "Ship2.h"
#include "Ship3.h"


// mainSheet

class mainSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(mainSheet)

public:
	mainSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	mainSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~mainSheet();

protected:
	DECLARE_MESSAGE_MAP()

private:
	Ship1 ship1;
	Ship2 ship2;
	Ship3 ship3;
};


