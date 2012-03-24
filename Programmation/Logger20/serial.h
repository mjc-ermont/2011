#ifndef SERIAL_H
#define SERIAL_H

#include "LSerie/LSerie.h"

#define SERIAL_BAUD 9600

class Serial
{
public:
    Serial(int _port=1);
    bool init();

    string readData();


private:
    LSerie* com;
    int port;
};

#endif // SERIAL_H
