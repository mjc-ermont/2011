#include <Arduino.h>

class GPS {
public:
	GPS();
	bool init();
	bool refresh();
        void getTrame();

private:
        String _lat_deg;
        String _lat_min;
        String _lon_deg;
        String _lon_min;
};
