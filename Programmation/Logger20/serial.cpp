#include "serial.h"

Serial::Serial(int _port)
{
    port = _port;
    com = new LSerie();
}

bool Serial::init() {
   if( !com->open(port, SERIAL_BAUD) )
       return 0;
   else
       return 1;
}

string Serial::readData() {
    string data;
    if(com->receiveData(&data) > 0) {
        return data;
    }
}
