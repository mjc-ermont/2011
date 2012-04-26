#ifndef SERIAL_H
#define SERIAL_H

#include <string>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <QThread>

#define BAUD 9600
#define RX_SIZE 4096 /* taille tampon d'entrée */
#define TX_SIZE 4096 /* taille tampon de sortie */
#define MAX_WAIT_READ 5000 /* temps max d'attente pour lecture (en ms) */

class Serial : public QThread
{
    Q_OBJECT

public:
    Serial(int _port=1);
    ~Serial();


protected:
    bool OpenCOM (int nId);
    bool CloseCOM ();
    bool ReadCOM (void* buffer, int nBytesToRead, int* pBytesRead);
    bool WriteCOM (void* buffer, int nBytesToWrite, int* pBytesWritten);


public slots:
    void run();
    bool init();

    void readData();

signals:
    void dataRead(std::string);

private:
    int port;

    HANDLE g_hCOM;
    COMMTIMEOUTS g_cto;
        /* Configuration du port COM */
    DCB g_dcb;

};

#endif // SERIAL_H
