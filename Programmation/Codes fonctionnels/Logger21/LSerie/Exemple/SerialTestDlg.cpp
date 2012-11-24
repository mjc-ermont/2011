// SerialTestDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"
#include ".\serialtestdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;


//*****************************************************************************************************
//*****************************************************************************************************
//** CAboutDlg
//*  Cette classe gére la fenêtre "About".
//*****************************************************************************************************

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Données de la boîte de dialogue
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // prise en charge de DDX/DDV
	DECLARE_MESSAGE_MAP()
};

//******************************************************************
//* Fonctions associés à la classe CAboutDlg.
	CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
	{
	}

	void CAboutDlg::DoDataExchange(CDataExchange* pDX)
	{
		CDialog::DoDataExchange(pDX);
	}

	BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	END_MESSAGE_MAP()









//*****************************************************************************************************
//*****************************************************************************************************
//** CSerialTestDlg
//*  Cette classe gére la fenêtre principale de l'apllication.
//*****************************************************************************************************

CSerialTestDlg::CSerialTestDlg(CWnd* pParent) : CDialog(CSerialTestDlg::IDD, pParent)
	, sComSpeed(_T(""))
	, sComReceive(_T(""))
	, sSendText(_T(""))
	, sReceiveText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cListePort);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_Scroll);
	DDX_Text(pDX, IDC_COM_SPEED, sComSpeed);
	DDX_Control(pDX, IDC_COM_SPEED, ctl_ComSpeed);
	DDX_Control(pDX, IDC_RE_TEXT, ctlReceiveText);
	DDX_Text(pDX, IDC_EDIT5, sSendText);
	DDX_Text(pDX, IDC_RE_TEXT, sReceiveText);
}

BEGIN_MESSAGE_MAP(CSerialTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO13, OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, OnBnClickedRadio14)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_B_SET_SPEED, OnBnClickedBSetSpeed)
	ON_BN_CLICKED(IDC_B_SEND_TEXT, OnBnClickedBSendText)
	ON_BN_CLICKED(IDC_BT_CLEAR, OnBnClickedBtClear)
END_MESSAGE_MAP()





void CSerialTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}




void CSerialTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO : ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels

 // Get the minimum and maximum scroll-bar positions.
   int pos, minPos, maxPos;

   if( pScrollBar )
   {
	   pos = pScrollBar->GetScrollPos();	
	   pScrollBar->GetScrollRange(&minPos, &maxPos); 

	   if(nSBCode==SB_LINELEFT)	
		   pos -=10;
	   if(nSBCode==SB_LINERIGHT)	
		   pos +=10;
	   if(nSBCode==SB_PAGELEFT)	
		   pos -=100;
	   if(nSBCode==SB_PAGERIGHT)	
		   pos +=100;
	   if(nSBCode==SB_THUMBPOSITION)
		   pos = nPos;

	    if(pos<minPos) pos=minPos;
		if(pos>maxPos) pos=maxPos;
		pScrollBar->SetScrollPos(pos);	
   }

    
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);


}





// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône. Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CSerialTestDlg::OnPaint() 
{	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
	}
	else
	{
		CDialog::OnPaint();
	}

}


// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CSerialTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



// gestionnaires de messages pour CSerialTestDlg

BOOL CSerialTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO : ajoutez ici une initialisation supplémentaire

	//**************** Initialisation de l'interface ***************
	m_cListePort.AddString("Com 1");
	m_cListePort.AddString("Com 2");
	m_cListePort.AddString("Com 3");
	m_cListePort.AddString("Com 4");
	m_cListePort.AddString("Com 5");
	m_cListePort.AddString("Com 6");
	m_cListePort.AddString("Com 7");
	m_cListePort.AddString("Com 8");
	ctl_ComSpeed.SetWindowText("9600");

	//**************** Initialisation des variables ***************
	com=0;
	
	return TRUE;  // retourner TRUE, sauf si vous avez défini le focus sur un contrôle
}




//*****************************************************************************************************
//** OnCbnSelchangeCombo1
//*  Cette fonction ouvre le port série sélectionné par la ComboBox.
//*****************************************************************************************************

void CSerialTestDlg::OnCbnSelchangeCombo1()
{int err=0;
 int speed = 0;

		//--- Récupération du N° du port choisi par l'utilisateur.
		port = m_cListePort.GetCurSel();
		// Lecture de la valeure rentrée par l'utilisateur, et convertion en int.
		UpdateData(true);
		speed = atol(this->sComSpeed);

		if(port!=CB_ERR)
		{
			port++;	// chg de numérotation (0 à 7  ->  COM1 à COM8) 
			// Si l'objet com à déja été instancié, on le ferme.
			if(com)
			{
				KillTimer(1);
				com->closeCom();
				delete com;
				com=0;
			}
			// Ouverture du port demandé.
			com = new LSerie();
			err = com->open(port, speed);
			if(!err)
			{
				MessageBox("Port Com indisponible", "SerialTest : Erreur!");
				return;
			}
			SetTimer(1, 1000, 0);
		}

}








//*****************************************************************************************************
//** OnBnClickedRadiox
//*  Ces fonctions active ou pas les lignes de commande du port série.
//*****************************************************************************************************


void CSerialTestDlg::OnBnClickedRadio1()
{
	//---------- RTS ON -------------
	if(com)
		com->setRts(1);

	
}

void CSerialTestDlg::OnBnClickedRadio2()
{
	//---------- RTS OFF -------------
	if(com)
		com->setRts(0);

}

void CSerialTestDlg::OnBnClickedRadio3()
{
	//---------- DTR ON -------------
	if(com)
		com->setDtr(1);
}

void CSerialTestDlg::OnBnClickedRadio4()
{
	//---------- DTR OFF -------------
	if(com)
		com->setDtr(0);
}


void CSerialTestDlg::OnBnClickedRadio13()
{
	//---------- RTS ON -------------
	if(com)
		com->setTxd(1);
}

void CSerialTestDlg::OnBnClickedRadio14()
{
	//---------- RTS OFF -------------
	if(com)
		com->setTxd(0);
}





//*****************************************************************************************************
//** OnTimer
//*  Lecture périodique de l'état des lignes de commande du port série et du buffer d'entrée.
//*****************************************************************************************************
void CSerialTestDlg::OnTimer(UINT nIDEvent)
{
	// TODO : ajoutez ici le code de votre gestionnaire de messages et/ou les paramètres par défaut des appels
	string sTrame = "";

	CDialog::OnTimer(nIDEvent);

	if(nIDEvent == 1 && com)
	{
		if( com->receiveData(&sTrame) > 0)
		{
			CString strCString(sTrame.c_str());
			this->sReceiveText += strCString + "\r\n";
			UpdateData(false);
		}
		

		if( com->getCts() )
		{
			this->CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO5);
		}
		else
		{
			this->CheckRadioButton(IDC_RADIO5, IDC_RADIO6, IDC_RADIO6);
		}

		if( com->getDtr() )
			this->CheckRadioButton(IDC_RADIO7, IDC_RADIO8, IDC_RADIO7);
		else
			this->CheckRadioButton(IDC_RADIO7, IDC_RADIO8, IDC_RADIO8);

		if( com->getCd() )
			this->CheckRadioButton(IDC_RADIO9, IDC_RADIO10, IDC_RADIO9);
		else
			this->CheckRadioButton(IDC_RADIO9, IDC_RADIO10, IDC_RADIO10);

		if( com->getRi() )
			this->CheckRadioButton(IDC_RADIO11, IDC_RADIO12, IDC_RADIO11);
		else
			this->CheckRadioButton(IDC_RADIO11, IDC_RADIO12, IDC_RADIO12);


	}
}






//*****************************************************************************************************
//** OnBnClickedBSetSpeed
//*  Configure la vitesse de communication du port série.
//*****************************************************************************************************

void CSerialTestDlg::OnBnClickedBSetSpeed()
{	long speed = 0;

	// Lecture de la valeure rentrée par l'utilisateur, et convertion en int.
	UpdateData(true);
	speed = atol(this->sComSpeed);
	if(com)
	{	
		if(com->setSpeed(speed))
			MessageBox("Speed is set to " + this->sComSpeed + "bauds"); 
		else
		{
			string msgErreur = "ERROR : This speed is not valid for this serial port ! - ";
			msgErreur += com->getErrorMsg();
			MessageBox((LPCSTR)msgErreur.data()); 
		}


	}
}


void CSerialTestDlg::OnBnClickedBSendText()
{
	// Lecture de la valeur rentrée par l'utilisateur, et convertion en int.
	UpdateData(true);
	
	if(com)
	{	
		//trame = this->sSendText.GetBuffer();
		//com->SendData(sizeof(trame), (LPBYTE)trame);
		std::string stdString((LPCTSTR)this->sSendText);
		com->sendData(&stdString);
		this->sReceiveText += "#Send >" + this->sSendText + "\r\n";
		UpdateData(false);
	}
}


void CSerialTestDlg::OnBnClickedBtClear()
{
	this->sReceiveText = "";
	UpdateData(false);
}
