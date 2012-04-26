#include "serial.h"

Serial::Serial(int _port)
{
    port = _port;

    g_hCOM = NULL;
    COMMTIMEOUTS _g_cto = {
       MAX_WAIT_READ, /* ReadIntervalTimeOut */
       0, /* ReadTotalTimeOutMultiplier */
       MAX_WAIT_READ, /* ReadTotalTimeOutConstant */
       0, /* WriteTotalTimeOutMultiplier */
       0 /* WriteTotalTimeOutConstant */
   };

   DCB _g_dcb = {
       sizeof(DCB), /* DCBlength */
       BAUD, /* BaudRate */
       TRUE, /* fBinary */
       FALSE, /* fParity */
       FALSE, /* fOutxCtsFlow */
       FALSE, /* fOutxDsrFlow */
       DTR_CONTROL_ENABLE, /* fDtrControl */
       FALSE, /* fDsrSensitivity */
       FALSE, /* fTXContinueOnXoff */
       FALSE, /* fOutX */
       FALSE, /* fInX */
       FALSE, /* fErrorChar */
       FALSE, /* fNull */
       RTS_CONTROL_ENABLE, /* fRtsControl */
       FALSE, /* fAbortOnError */
       0, /* fDummy2 */
       0, /* wReserved */
       0x100, /* XonLim */
       0x100, /* XoffLim */
       8, /* ByteSize */
       NOPARITY, /* Parity */
       ONESTOPBIT, /* StopBits */
       0x11, /* XonChar */
       0x13, /* XoffChar */
       '?', /* ErrorChar */
       0x1A, /* EofChar */
       0x10 /* EvtChar */
   };

   g_cto = _g_cto;
   g_dcb = _g_dcb;
}

Serial::~Serial() {
    CloseCOM();
}

bool Serial::init() {
   if( !OpenCOM(port) )
       return 0;
   else
       return 1;
}

std::string Serial::readData() {
    std::string data;
    int size;

    char buf[50];

    ReadCOM(buf,49,&size);

    buf[size]='\0';
    data = std::string(buf);

    if(size > 0) {
        return data;
    }
    else {
        return "Rien du tout lol";
    }
}


bool Serial::OpenCOM(int nId)
{
    /* variables locales */
    char szCOM[16];
    /* construction du nom du port, tentative d'ouverture */
    sprintf(szCOM, "COM%d", nId);
    g_hCOM = CreateFileA(szCOM, GENERIC_READ|GENERIC_WRITE, 0, NULL,
    OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
    if(g_hCOM == INVALID_HANDLE_VALUE)
    {
        printf("Erreur lors de l'ouverture du port COM%d", nId);
        return FALSE;
    }
    /* affectation taille des tampons d'émission et de réception */
    SetupComm(g_hCOM, RX_SIZE, TX_SIZE);
    /* configuration du port COM */
    if(!SetCommTimeouts(g_hCOM, &g_cto) || !SetCommState(g_hCOM, &g_dcb))
    {
        printf("Erreur lors de la configuration du port COM%d", nId);
        CloseHandle(g_hCOM);
        return false;
    }
    /* on vide les tampons d'émission et de réception, mise à 1 DTR */
    PurgeComm(g_hCOM, PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);
    EscapeCommFunction(g_hCOM, SETDTR);
    return true;
}


/******************************************************************************
CloseCOM : fermeture du port COM.
retour : vrai si l'opération a réussi, faux sinon.
******************************************************************************/
bool Serial::CloseCOM()
{
    /* fermeture du port COM */
    CloseHandle(g_hCOM);
    return true;
}


/******************************************************************************
ReadCOM : lecture de données sur le port COM.
entrée : buffer : buffer où mettre les données lues.
nBytesToRead : nombre max d'octets à lire.
pBytesRead : variable qui va recevoir le nombre d'octets lus.
retour : vrai si l'opération a réussi, faux sinon.
-------------------------------------------------------------------------------
Remarques : - la constante MAX_WAIT_READ utilisée dans la structure
COMMTIMEOUTS permet de limiter le temps d'attente si aucun
caractères n'est présent dans le tampon d'entrée.
- la fonction peut donc retourner vrai sans avoir lu de données.
******************************************************************************/
bool Serial::ReadCOM(void* buffer, int nBytesToRead, int* pBytesRead)
{
    return ReadFile(g_hCOM, buffer, nBytesToRead, (DWORD*)pBytesRead, NULL);
}
/******************************************************************************
WriteCOM : envoi de données sur le port COM.
entrée : buffer : buffer avec les données à envoyer.
nBytesToWrite : nombre d'octets à envoyer.
pBytesWritten : variable qui va recevoir le nombre d'octets
envoyés.
retour : vrai si l'opération a réussi, faux sinon.
******************************************************************************/
bool Serial::WriteCOM(void* buffer, int nBytesToWrite, int* pBytesWritten)
{
    /* écriture sur le port */
    return WriteFile(g_hCOM, buffer, nBytesToWrite, (DWORD*)pBytesWritten, NULL);
}
