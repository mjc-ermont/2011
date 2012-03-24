// stdafx.h : fichier Include pour les fichiers Include  syst�me standard,
// ou pour les fichiers Include sp�cifiques au projet qui sont fr�quemment utilis�s,
// mais rarement modifi�s

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclut les informations rarement utilis�es des en-t�tes Windows
#endif

// Modifiez les valeurs suivantes si votre plate-forme cible est ant�rieure aux plates-formes sp�cifi�es ci-apr�s.
// Consultez la documentation MSDN pour obtenir des informations r�centes sur les valeurs respectives des diff�rentes plates-formes.
#ifndef WINVER				// Permet l'utilisation de fonctionnalit�s sp�cifiques � Windows�95 et � Windows�NT�4 ou version ult�rieure.
#define WINVER 0x0400		// La valeur appropri�e doit �tre utilis�e pour des applications cibles Windows 98 et Windows 2000 ou version ult�rieure.
#endif

#ifndef _WIN32_WINNT		// Permet l'utilisation de fonctionnalit�s sp�cifiques � Windows�NT�4 ou version ult�rieure.
#define _WIN32_WINNT 0x0400		// La valeur appropri�e doit �tre utilis�e pour des applications cibles Windows 98 et Windows 2000 ou version ult�rieure.
#endif						

#ifndef _WIN32_WINDOWS		// Permet l'utilisation de fonctionnalit�s sp�cifiques � Windows�98 ou version ult�rieure.
#define _WIN32_WINDOWS 0x0410 // La valeur appropri�e doit �tre utilis�e pour des applications cibles Windows Me ou version ult�rieure.
#endif

#ifndef _WIN32_IE			// Permet l'utilisation de fonctionnalit�s sp�cifiques � Internet Explorer�4.0 ou version ult�rieure.
#define _WIN32_IE 0x0400	// La valeur appropri�e doit �tre utilis�e pour des applications cibles Internet Explorer 5.0 ou version ult�rieure.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// certains constructeurs CString seront explicites

// d�sactive le masquage MFC de certains messages d'avertissement courants et par ailleurs souvent ignor�s
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // composants MFC principaux et standard
#include <afxext.h>         // extensions MFC
#include <afxdisp.h>        // classes Automation MFC

#include <afxdtctl.h>		// Prise en charge MFC des contr�les communs Internet Explorer�4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Prise en charge MFC des contr�les communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

