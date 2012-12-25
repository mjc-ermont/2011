#include <Arduino.h>
#include "vector.h"
#include "out.h"

class Capteur {
public:
	Capteur();
	virtual bool init() = 0;
	virtual bool refresh() = 0;
        virtual void getTrame() = 0;
        virtual void addOut(Out &out);

protected:
        Vector<Out> _out;
};
