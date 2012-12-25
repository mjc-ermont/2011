#include <Arduino.h>

class GPS {
public:
	GPS();
	bool init();
	bool refresh();
        void getTrame();

private:
        String _lat_deg; // Degres de latitude
        String _lat_min; // Minutes de latitude
        String _lon_deg; // Degres de longitude
        String _lon_min; // Minutes de longitude
        String _vit;     // Vitesse
        String _utime;   // Temps UTC
};
