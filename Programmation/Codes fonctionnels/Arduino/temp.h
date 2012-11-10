#include <Arduino.h>

class Temp {
public:
	Temp();
	bool init();
	bool refresh();
        void getTrame();

private:
        String  _temp;
};
