#include <Arduino.h>

class Press {
public:
	Press();
	bool init();
	bool refresh();
        void getTrame();

private:
        String  _press;
};
