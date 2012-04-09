#include <windows.h>
#include <stdio.h>
#include <stdafx.h>
#include "LSerie.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/// <summary> Constructeur de la classe par d�faut.</summary> 
/// <remarks> Il param�tre une communication s�rie sur COM1 � 9600 Bauds, 8 bit et pas de part�.</remarks>   
LSerie::LSerie()
{
	hcom = NULL;	//Fichier de sortie sur le port COM		| The file stream use for acces to the serial port.
	bufferSize = 8192;	// Buffer d'entr�e sortie.
}
LSerie::~LSerie()
{
	if(hcom != NULL)
		closeCom();
}



bool LSerie::open(int numPort, long speedInBaud)
{
	return open(numPort, speedInBaud, 8, 0, 1);
}


/************************************************************************************
**** Fonction: Open
**** Derni�re modif: 21/05/2005
**** D�veloppeur: Alexandre Fonton
**** R�le: Ouvre le port RS232 choisi. 
**** Recoit: 
**** Renvoie: Faux si l'ouverture du port a �chou�, sinon Vrai.
*************************************************************************************/

bool LSerie::open(int numPort, long speedInBaud, int nbBit, int parity, float nbStopBit)
{	char buf[] = "COM1";

	//--- V�rification des param�tres pass�s � la fonction:
	if(numPort<1 || numPort>9)		// V�rification que le num�ro de port est compri entre 1 et 9.
		return false;

	if(speedInBaud<1)		// V�rification de la vitesse de communication
		return false;

	if(nbBit<5 || nbBit > 9)
		return false;

	if(parity<0 || parity > 2)
		return false;

	if(nbStopBit<1 || nbStopBit > 2)
		return false;


	//--- Cr�ation d'une chaine de caract�re contenant le nom du port s�rie, ex : COM1.
	itoa(numPort, &buf[3], 10); 

	//--- Ouverture du port s�rie en lecture / �criture.
	hcom=CreateFile(buf, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING , 0, 0);
	if (hcom==0 || hcom==INVALID_HANDLE_VALUE)
		return false;

	//--- D�finit la dur�e du TimeOut pour la reception.
	setTimeOut(100);

	//--- Dimensionne les buffers d'entr�e et sortie.
	if ( !SetupComm(hcom, bufferSize, bufferSize) )     
	    return false;

	//--- R�cup�re l'objet de configuration du format des bytes.
    if ( !GetCommState(hcom, &dcb))
		return false;

	//Nombre de bit par byte:
	dcb.ByteSize = nbBit;
	
	//Nombre de bit de stop: 1, 1.5 ou 2
	if(nbStopBit == 1)
		dcb.StopBits = ONESTOPBIT;
	if(nbStopBit == 1.5)
		dcb.StopBits = ONE5STOPBITS;
	if(nbStopBit == 2)
		dcb.StopBits = TWOSTOPBITS;
	
	//V�rification de la parit�: 0 pas de v�rif, 1 pair, 2 impaire.
	if(parity == 0)
		dcb.Parity = NOPARITY;
	if(parity == 1)
		dcb.Parity = ODDPARITY;
	if(parity == 2)
		dcb.Parity = EVENPARITY;

	//--- Stocke l'objet de configuration du format des bytes.
	  if (!SetCommState(hcom, &dcb))
		return false;
	  else
		return true;

}







/************************************************************************************
**** Fonction: CloseCom
**** Derni�re mofif: 01/07/2004
**** D�veloppeur: Alexandre Fonton
**** R�le: Ferme le port RS232 actuellement ouvert.
**** Recoit: Rien
**** Renvoie: Rien
*************************************************************************************/

void LSerie::closeCom()
{
	CloseHandle(hcom);
	hcom = NULL;
}



/************************************************************************************
**** Fonction: SetTimeout
**** Derni�re mofif: 01/07/2004
**** D�veloppeur: Alexandre Fonton
**** R�le: D�finit la dur�e maximum d'attente d'une information (TimeOut).
**** Recoit: Temps d'attente en ms.
**** Renvoie: Faux si l'op�ration a �chou�, sinon Vrai.
*************************************************************************************/

bool LSerie::setTimeOut(DWORD ms)
{
	//--- V�rification des param�tres pass�s � la fonction:
	if( ms<0)
		return false;

	ct.ReadIntervalTimeout = 0;
	ct.ReadTotalTimeoutMultiplier = 0;	// pas de multipicateur de timeout en fonction du nombre de caract�res demand�s.
	ct.ReadTotalTimeoutConstant = ms;
	ct.WriteTotalTimeoutMultiplier = 0;
	ct.WriteTotalTimeoutConstant = ms;
	if ( !SetCommTimeouts(hcom, &ct) )      //Configuration du Time Out
		return false;

	return false;
	//MSDN: The SetCommTimeouts function sets the time-out parameters for all read and write operations on a specified communications device.
}




/**********************************************************************
**** Fonction: SetBaud
**** Derni�re mofif: 01/07/2004
**** D�veloppeur: Alexandre Fonton
**** R�le: D�finit la vitesse de communication (ex:9600 baud).
**** Recoit: Vitesse de communication en baud.
**** Renvoie: Faux si l'op�ration a �chou�, sinon Vrai.
***********************************************************************/

bool LSerie::setSpeed(DWORD baudrate)
{
	//--- V�rification des param�tres pass�s � la fonction:
	if( baudrate<1)
		return false;


	if (!GetCommState(hcom, &dcb))
		return FALSE;

	dcb.BaudRate = baudrate;

	if (!SetCommState(hcom, &dcb))
		return FALSE;
	else 
		return TRUE;


	

	//MSDN: The SetCommState function configures a communications device according to the specifications in a device-control block (a DCB structure). The function reinitializes all hardware and control settings, but it does not empty output or input queues.
}



/**********************************************************************
**** Fonction: SendData(string)
**** Derni�re mofif: 22/05/2005
**** D�veloppeur: Alexandre Fonton
**** R�le: Envoie une chaine de caract�res contenu dans un type "string" sur le port RS232 actuellement ouvert.
**** Recoit: Un pointeur sur une chaine de caract�res.
**** Renvoie: -1 si l'op�ration a �chou�, sinon le nombre de caract�res envoy�s.
***********************************************************************/

int  LSerie::sendData(string* data)
{
	//--- V�rification des param�tres pass�s � la fonction:
	if( data == NULL )
		return false;

	return sendData((DWORD)data->size(), (LPBYTE)data->data());
}



/**********************************************************************
**** Fonction: SendData(DWORD lg, LPBYTE data)
**** Derni�re mofif: 01/07/2004
**** D�veloppeur: Alexandre Fonton
**** R�le: Envoie une s�rie d'octets sur le port RS232 actuellement ouvert.
**** Recoit: Un pointeur sur une chaine de caract�res (data) et sa taille (lg).
**** Renvoie: -1 si l'op�ration a �chou�, sinon le nombre de caract�res envoy�s.
***********************************************************************/
int LSerie::sendData(DWORD lg, LPBYTE data)
{
	DWORD result=0;

	//--- V�rification des param�tres pass�s � la fonction:
	if( lg<0 || data==NULL)
		return false;


	if ( !WriteFile(hcom, data, lg, &result, 0) )
		return -1;
	else
		return (int)result;

	//MSDN:  The WriteFile function writes data to a file and is designed for both synchronous
	//		and asynchronous operation. The function starts writing data to the file at the 
	//		position indicated by the file pointer. After the write operation has been completed
	//		, the file pointer is adjusted by the number of bytes actually written, except when
	//		the file is opened with FILE_FLAG_OVERLAPPED. If the file handle was created for 
	//		overlapped input and output (I/O), the application must adjust the position of the
	//		file pointer after the write operation is finished.
    //       This function is designed for both synchronous and asynchronous operation. 
	//		The WriteFileEx function is designed solely for asynchronous operation. 
	//		It lets an application perform other processing during a file write operation.

}







/**********************************************************************
**** Fonction: ReceiveData(string* data)
**** Derni�re mofif: 22/05/2005
**** D�veloppeur: Alexandre Fonton
**** R�le: Lecture du buffer de reception du port RS232 actuellement ouvert.
**** Recoit: Un pointeur sur une string.
**** Renvoie: -1 si l'op�ration a �chou�, sinon le nombre de caract�res recu.
***********************************************************************/
int LSerie::receiveData(string* data)
{	char buffer[1025];
	int nbChar=0;

	//--- V�rification des param�tres pass�s � la fonction:
	if( data==NULL)
		return false;

	nbChar = receiveData(1024, (LPBYTE)buffer);
	buffer[nbChar] = 0; // caract�re de fin de chaine.
	data->assign(buffer);
	return nbChar;
}


/**********************************************************************
**** Fonction: ReceiveData
**** Derni�re mofif: 01/07/2004
**** D�veloppeur: Alexandre Fonton
**** R�le: Lecture du buffer de reception du port RS232 actuellement ouvert.
**** Recoit: Un pointeur sur une chaine de caract�res (data) et sa taille maximale possible (lg).
**** Renvoie: -1 si l'op�ration a �chou�, sinon le nombre de caract�res recu.
***********************************************************************/
int LSerie::receiveData(DWORD lg, LPBYTE data)
{
	DWORD result=0;

	//--- V�rification des param�tres pass�s � la fonction:
	if( lg<0 || data==NULL)
		return false;

	if (!ReadFile(hcom, data, lg, &result, 0))
		return -1;
	else
		return (int)result;

	//MSDN:   The ReadFile function reads data from a file, starting at the position indicated 
	//		 by the file pointer. After the read operation has been completed, the file pointer
	//		 is adjusted by the number of bytes actually read, unless the file handle is 
	//		 created with the overlapped attribute. If the file handle is created for 
	//		 overlapped input and output (I/O), the application must adjust the position of 
	//		 the file pointer after the read operation.
	//        This function is designed for both synchronous and asynchronous operation. 
	//		 The ReadFileEx function is designed solely for asynchronous operation. It lets 
	//		 an application perform other processing during a file read operation.

}


/**************************** SetRts(val) **************************************************
**** Positionne RTS au niveau val (0 ou 1)   */
bool LSerie::setRts(bool val)				
{ 
	if(val)
	  { 
		  if(EscapeCommFunction(hcom, SETRTS) == TRUE )
			  return true;
	  }
	else
	  { 
		  if(EscapeCommFunction(hcom, CLRRTS) == TRUE )
			  return true;
	  }

   return false;
}


/**************************** SetTxd(val) **************************************************
**** Positionne Txd au niveau val (0 ou 1)   */
bool LSerie::setTxd(bool val)				
{ 
	if(val)
	  { 
		  if( EscapeCommFunction(hcom, SETBREAK) == TRUE )
			  return true;
	  }
	else
	  { 
		  if( EscapeCommFunction(hcom, CLRBREAK) == TRUE )
			  return true;
	  }
   return false;
}


	
/**************************** SetDtr(val) **************************************************
**** Positionne DTR au niveau val (0 ou 1)   */
bool LSerie::setDtr(bool val)						
{ 
	if(val)
	  {
		  if( EscapeCommFunction(hcom, SETDTR) == TRUE )
			  return true;
	  }
	else
	  { 
		  if( EscapeCommFunction(hcom, CLRDTR) == TRUE )
			  return false;
	  }
    return false;
}



/********************** GetCts() ***********************/
bool LSerie::getCts()						
{ 
	DWORD result;
		GetCommModemStatus(hcom, &result);
		if(result & MS_CTS_ON)
			return true;
		else
			return false;
}

/********************** GetDtr() ***********************/
bool LSerie::getDtr()						
{ 
  DWORD result;
		GetCommModemStatus(hcom, &result);
		if(result & MS_DSR_ON)
			return true;
		else
			return false;
}

/********************** GetRi() ***********************/
bool LSerie::getRi()						
{ 
  DWORD result;
		GetCommModemStatus(hcom, &result);
		if(result & MS_RING_ON)
			return true;
		else
			return false;
}


/********************** GetCd() ***********************/
bool LSerie::getCd()						
{ int err=0;
  DWORD result;
		err = GetCommModemStatus(hcom, &result);
		if(result & MS_RLSD_ON)
			return true;
		else
			return false;
}




string LSerie::getErrorMsg()
{
	LPVOID lpMsgBuf;
	string sErreur = "";

	if ( FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
							NULL, GetLastError(),
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
							(LPTSTR) &lpMsgBuf, 0, NULL ))
	{
		sErreur.assign((LPCTSTR)lpMsgBuf);
	}

	return sErreur;
}



