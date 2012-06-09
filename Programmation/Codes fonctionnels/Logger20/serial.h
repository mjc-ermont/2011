#ifndef SERIAL_H
#define SERIAL_H

#include "defines.h"
#include <QThread>
#include <QStringList>
#include <string>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <QDebug>


class Serial : public QThread
{
    Q_OBJECT

public:
    Serial(int _port=1,QThread * parent = 0);
    ~Serial();
    void run();
    bool init();


protected:
    bool OpenCOM (int nId);
    bool CloseCOM ();
    bool ReadCOM (void* buffer, int nBytesToRead, int* pBytesRead);
    bool WriteCOM (void* buffer, int nBytesToWrite, int* pBytesWritten);


public slots:

    void readData();

signals:
    void dataRead(QStringList);

private:
    int port;

    HANDLE g_hCOM;
    COMMTIMEOUTS g_cto;
        /* Configuration du port COM */
    DCB g_dcb;

    std::string skipped_buf;

};

#endif // SERIAL_H
