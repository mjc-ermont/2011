// SerialTestDlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "LSerie.h"
#include <string>
#include <iostream>
#include <fstream>



// boîte de dialogue CSerialTestDlg
class CSerialTestDlg : public CDialog
{
// Construction
public:
	CSerialTestDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de la boîte de dialogue
	enum { IDD = IDD_SERIALTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	// Liste des ports série disponible
	CComboBox m_cListePort;
	afx_msg void OnBnClickedOk();

	LSerie* com;

	int noPoint;
    int port;
	int etat;



	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedRadio13();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CScrollBar m_Scroll;
	CButton m_BStart;
	CString sComSpeed;
	CString sComReceive;
	afx_msg void OnBnClickedBSetSpeed();
	afx_msg void OnBnClickedBSendText();
	CEdit ctl_ComSpeed;
	CEdit ctl_SendText;
	CEdit ctlReceiveText;
	CString sSendText;
	CString sReceiveText;
	afx_msg void OnBnClickedBtClear();
};
