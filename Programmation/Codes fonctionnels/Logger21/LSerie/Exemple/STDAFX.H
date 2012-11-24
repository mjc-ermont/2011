// stdafx.h : fichier Include pour les fichiers Include  système standard,
// ou pour les fichiers Include spécifiques au projet qui sont fréquemment utilisés,
// mais rarement modifiés

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclut les informations rarement utilisées des en-têtes Windows
#endif

// Modifiez les valeurs suivantes si votre plate-forme cible est antérieure aux plates-formes spécifiées ci-après.
// Consultez la documentation MSDN pour obtenir des informations récentes sur les valeurs respectives des différentes plates-formes.
#ifndef WINVER				// Permet l'utilisation de fonctionnalités spécifiques à Windows 95 et à Windows NT 4 ou version ultérieure.
#define WINVER 0x0400		// La valeur appropriée doit être utilisée pour des applications cibles Windows 98 et Windows 2000 ou version ultérieure.
#endif

#ifndef _WIN32_WINNT		// Permet l'utilisation de fonctionnalités spécifiques à Windows NT 4 ou version ultérieure.
#define _WIN32_WINNT 0x0400		// La valeur appropriée doit être utilisée pour des applications cibles Windows 98 et Windows 2000 ou version ultérieure.
#endif						

#ifndef _WIN32_WINDOWS		// Permet l'utilisation de fonctionnalités spécifiques à Windows 98 ou version ultérieure.
#define _WIN32_WINDOWS 0x0410 // La valeur appropriée doit être utilisée pour des applications cibles Windows Me ou version ultérieure.
#endif

#ifndef _WIN32_IE			// Permet l'utilisation de fonctionnalités spécifiques à Internet Explorer 4.0 ou version ultérieure.
#define _WIN32_IE 0x0400	// La valeur appropriée doit être utilisée pour des applications cibles Internet Explorer 5.0 ou version ultérieure.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// certains constructeurs CString seront explicites

// désactive le masquage MFC de certains messages d'avertissement courants et par ailleurs souvent ignorés
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // composants MFC principaux et standard
#include <afxext.h>         // extensions MFC
#include <afxdisp.h>        // classes Automation MFC

#include <afxdtctl.h>		// Prise en charge MFC des contrôles communs Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Prise en charge MFC des contrôles communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

