#ifndef SERIAL_H
#define SERIAL_H

#include "defines.h"
#include <QThread>
#include <QStringList>
#include <string>
//#include <windows.h>
#include <cstdio>
#include <cstdlib>
//#include <conio.h>
#include <QDebug>

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <iostream>
#include <pthread.h>


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
/*
    HANDLE g_hCOM;
    COMMTIMEOUTS g_cto;

    DCB g_dcb;
*/

    QString skipped_buf;

    void setspeed(speed_t vitesse)
    {
      cfsetospeed(&tio, vitesse);
      cfsetispeed(&tio, vitesse);
      tcsetattr(tty_fd,TCSANOW,&tio);
    }

    int nb_read;
    unsigned char buffer[1024];
    struct termios tio;
    int tty_fd;

};

#endif // SERIAL_H
