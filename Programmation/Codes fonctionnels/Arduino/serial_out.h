#ifndef SERIALOUT_INCLUDED
#define SERIALOUT_INCLUDED
#include <Arduino.h>
#include "queue.h"
#include "out.h"


class SerialOut : public Out {
public:
	SerialOut();
	virtual bool init();
        virtual void writeQueue();
};

#endif // SERIALOUT_INCLUDED
