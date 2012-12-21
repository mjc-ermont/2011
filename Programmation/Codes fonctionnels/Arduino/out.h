#include <Arduino.h>

class Out {
public:
	Out();
	bool init();
        void addTrame(const char *trame);
        virtual void writeQueue();
private:

};
