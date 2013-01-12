#include "serial.h"

#ifdef WIN32
Serial::Serial(int _port, QThread * parent) : QThread(parent)
{
    skipped_buf = "";

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

void Serial::run() {
    init();
}

bool Serial::init() {
   return OpenCOM(port);
}

void Serial::readData() {
    int size;

    char buf[67];
    QStringList trames;

    #ifndef DEBUG

        ReadCOM(buf,66,&size);

        buf[size]='\0';
        QString data = QString::fromStdString(skipped_buf + std::string(buf));

        trames = data.split('@');
        int nbTrames = trames.size();
        if(nbTrames >= 2) {
            if(trames.last().size() != trames[nbTrames - 2].size()) {
                skipped_buf = trames.last().toStdString();
                trames.removeLast();

            }
        }
    #endif
    emit dataRead(trames);
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


#endif

#ifdef __linux
Serial::Serial(QString _port, QThread * parent) : QThread(parent)
{
    port = _port;
}


Serial::~Serial() {
    CloseCOM();
}

void Serial::run() {
    init();
}


bool Serial::init() {
    qDebug() << "port = " << port.toStdString().c_str();

    std::string acm = port.toStdString();


    memset(&tio,0,sizeof(tio));
    tio.c_iflag=0; //IGNPAR;
    tio.c_oflag=0;
    tio.c_cflag=CS8|CREAD|CLOCAL;           // 8n1, see termios.h for more information
    tio.c_lflag=0;
    tio.c_cc[VMIN]=1;
    tio.c_cc[VTIME]=5;

    tty_fd = open( acm.c_str(), O_RDWR | O_NONBLOCK);
    if(tty_fd < 0){
        perror("open");
        printf("file => %s\n", acm.c_str());
        return false;
    }

    setspeed(BAUD);
    return true;
}


void Serial::readData() {

    QStringList trames;
    for(int i=0;i<1024;++i)
        buffer[i] = '\n';

    #ifndef DEBUG
        nb_read = read(tty_fd, buffer, 1024);
        int eol=0;

        for(int i=0;(i<1024)&&(eol==0);++i)
            if(buffer[i] == '\n')
                eol = i;


        QString s;
        for(int i=0;i<eol;i++)
            s += buffer[i];

        QString data = skipped_buf + s;

        trames = data.split('@');
        int nbTrames = trames.size();
        if(nbTrames >= 2) {
            if(trames.last().size() != trames[nbTrames - 2].size()) {
                skipped_buf = trames.last();
                trames.removeLast();
            }
        }
    #endif
    qDebug() << "Data read" << trames;
    emit dataRead(trames);
}


// ----- Protected

bool Serial::OpenCOM(int nId) {

}

bool Serial::CloseCOM()
{
    if (close(tty_fd)<0) {
       perror("close");
       return false;
    }
    return true;
}

bool Serial::ReadCOM(void* buffer, int nBytesToRead, int* pBytesRead)
{

}

bool Serial::WriteCOM(void* buffer, int nBytesToWrite, int* pBytesWritten)
{
    write(tty_fd,buffer,nBytesToWrite);
    return true;
}

#endif
