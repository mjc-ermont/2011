// SerialTest.cpp : D�finit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialTestApp

BEGIN_MESSAGE_MAP(CSerialTestApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// construction de CSerialTestApp

CSerialTestApp::CSerialTestApp()
{
	// TODO : ajoutez ici le code de la construction.
	// Placez toutes les initialisations dans InitInstance
}


// Le seul et unique objet CSerialTestApp

CSerialTestApp theApp;


// initialisation de CSerialTestApp

BOOL CSerialTestApp::InitInstance()
{
	CWinApp::InitInstance();

	AfxEnableControlContainer();


	CSerialTestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO : Placez ici le code d�finissant le comportement lorsque la bo�te de dialogue est
		//  ferm�e avec OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO : Placez ici le code d�finissant le comportement lorsque la bo�te de dialogue est
		//  ferm�e avec Annuler
	}

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}
