// SerialTest.cpp : Définit les comportements de classe pour l'application.
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
		// TODO : Placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO : Placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec Annuler
	}

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}
