// SerialTest.h : fichier d'en-t�te principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// symboles principaux


// CSerialTestApp�:
// Consultez SerialTest.cpp pour l'impl�mentation de cette classe
//

class CSerialTestApp : public CWinApp
{
public:
	CSerialTestApp();

// Substitutions
	public:
	virtual BOOL InitInstance();

// Impl�mentation

	DECLARE_MESSAGE_MAP()
};

extern CSerialTestApp theApp;
