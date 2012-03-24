// l_serie.cpp: implementation of the l_serie class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>

#include "stdafx.h"
#include "l_serie.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

l_serie::l_serie(int port)
{
	ComPort=port;
}
l_serie::l_serie()
{
	ComPort=1;
}
l_serie::~l_serie()
{

}



/************************************************************************************
**** Fonction: InitComPort
**** Derniére mofif: 01/07/2004
**** Développeur: Alexandre Fonton
**** Rôle: Initialise les variables de la classe, ouvre le port RS232 choisi 
****        lors de la création de la classe et effectue un paramétrage par 
****        défaut du port RS232. 
**** Recoit: Rien
**** Renvoie: Faux si l'ouverture du port a échoué, sinon Vrai.
*************************************************************************************/

bool l_serie::InitComPort()
{	char buf[] = "COM1";

	if (ComPort==2)   buf[3]='2'; 
	if (ComPort==3)   buf[3]='3'; 
	if (ComPort==4)   buf[3]='4'; 
	if (ComPort==5)   buf[3]='5'; 
	if (ComPort==6)   buf[3]='6'; 
	if (ComPort==7)   buf[3]='7';
	if (ComPort==8)   buf[3]='8'; 


	hcom=CreateFile(buf, GENERIC_READ | GENERIC_WRITE, 0,0,
					OPEN_EXISTING ,0,0);
	if (hcom==0 || hcom==INVALID_HANDLE_VALUE)
		return false;


	ct.ReadTotalTimeoutMultiplier = 2;
	ct.ReadTotalTimeoutConstant = 200;
	ct.WriteTotalTimeoutMultiplier = 10;
	ct.WriteTotalTimeoutConstant = 200;
	if ( !SetCommTimeouts(hcom, &ct) )      //Configuration du Time Out
		return false;

	if ( !SetupComm(hcom, 8192, 8192) )     //Dimentionne les buffers d'entrée et sortie.
	    return false;

    if ( !GetCommState(hcom, &dcb))
		return false;

	  dcb.ByteSize = 8;
	  dcb.StopBits = ONESTOPBIT;
	  dcb.Parity = NOPARITY;
	  if (!SetCommState(hcom, &dcb))
		return false;
	  else
		return true;

}




/************************************************************************************
**** Fonction: CloseCom
**** Derniére mofif: 01/07/2004
**** Développeur: Alexandre Fonton
**** Rôle: Ferme le port RS232 actuellement ouvert.
**** Recoit: Rien
**** Renvoie: Rien
*************************************************************************************/

void l_serie::CloseCom()
{
	CloseHandle(hcom);
	hcom=0;
}



/************************************************************************************
**** Fonction: SetTimeout
**** Derniére mofif: 01/07/2004
**** Développeur: Alexandre Fonton
**** Rôle: Définit la durée maximum d'attente d'une information (TimeOut).
**** Recoit: Temps d'attente en ms.
**** Renvoie: Faux si l'opération a échoué, sinon Vrai.
*************************************************************************************/

bool l_serie::SetTimeout(DWORD ms)
{
	ct.ReadTotalTimeoutConstant = ms;
	if(SetCommTimeouts(hcom, &ct) == TRUE)
		return true;

	return false;
	//MSDN: The SetCommTimeouts function sets the time-out parameters for all read and write operations on a specified communications device.
}




/**********************************************************************
**** Fonction: SetBaud
**** Derniére mofif: 01/07/2004
**** Développeur: Alexandre Fonton
**** Rôle: Définit la vitesse de communication (ex:9600 baud).
**** Recoit: Vitesse de communication en baud.
**** Renvoie: Faux si l'opération a échoué, sinon Vrai.
***********************************************************************/

bool l_serie::SetBaud(DWORD baudrate)
{
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
**** Fonction: SendData
**** Derniére mofif: 01/07/2004
**** Développeur: Alexandre Fonton
**** Rôle: Envoie une série d'octets sur le port RS232 actuellement ouvert.
**** Recoit: Un pointeur sur une chaine de caractéres (data) et sa taille (lg).
**** Renvoie: -1 si l'opération a échoué, sinon le nombre de caractères envoyés.
***********************************************************************/

int l_serie::SendData(DWORD lg, LPBYTE data)
{
	DWORD result=0;

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
**** Fonction: ReceiveData
**** Derniére mofif: 01/07/2004
**** Développeur: Alexandre Fonton
**** Rôle: Lecture du buffer de reception du port RS232 actuellement ouvert.
**** Recoit: Un pointeur sur une chaine de caractéres (data) et sa taille maximale possible (lg).
**** Renvoie: -1 si l'opération a échoué, sinon le nombre de caractères recu.
***********************************************************************/
int l_serie::ReceiveData(DWORD lg, LPBYTE data)
{
	DWORD result=0;
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
bool l_serie::SetRts(int val)				
{ 
	if(val==1)
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
bool l_serie::SetTxd(int val)				
{ 
	if(val==1)
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
bool l_serie::SetDtr(int val)						
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
bool l_serie::GetCts()						
{ 
	DWORD result;
		GetCommModemStatus(hcom, &result);
		if(result & MS_CTS_ON)
			return true;
		else
			return false;
}

/********************** GetDtr() ***********************/
bool l_serie::GetDtr()						
{ 
  DWORD result;
		GetCommModemStatus(hcom, &result);
		if(result & MS_DSR_ON)
			return true;
		else
			return false;
}

/********************** GetRi() ***********************/
bool l_serie::GetRi()						
{ 
  DWORD result;
		GetCommModemStatus(hcom, &result);
		if(result & MS_RING_ON)
			return true;
		else
			return false;
}


/********************** GetCd() ***********************/
bool l_serie::GetCd()						
{ int err=0;
  DWORD result;
		err = GetCommModemStatus(hcom, &result);
		if(result & MS_RLSD_ON)
			return true;
		else
			return false;
}






