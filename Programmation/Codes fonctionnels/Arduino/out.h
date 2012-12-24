#ifndef OUT_INCLUDED
#define OUT_INCLUDED

#include <Arduino.h>
#include "queue.h"



class Out {
public:
	Out();
	virtual bool init() = 0;
        void addTrame(String trame);
        virtual void writeQueue() = 0;
protected:
        QueueArray<String> queue;
};

#endif
