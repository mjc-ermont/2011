#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

/*  ------- DEBUG -------  */

#define SERIAL_DEBUG    0    // Activation du mode debug

/*  ------- TRASMISSION -------  */

#define DELAY_SEND      1000
#define DELAY_REFRESH   800

#define SERIAL_BAUDRATE 4800 // baudrate de la liaison série avec le kiwi
#define NB_REPET        3    // Nombre de répéition de la trame
#define SIZE_VALUE      7    // Longueur maxi de la valeur dans la trame
#define ID_CAPT_GPS     0   // ID dans la trame du GPS
#define ID_CAPT_ACCEL   1    // ID dans la trame de l'accéléromètre
#define ID_CAPT_HUM     2    // ID dans la trame du capeur d'humidité
#define ID_CAPT_PRESS   3    // ID dans la trame du capeur de pression
#define ID_CAPT_TEMP    4    // ID dans la trame du capeur de temperature
// GPS
#define GPS_BAUDRATE    4800 // baudrate de la liaison série avec le GPS
#define NB_VAL_GPS      7    // Nombre de valeurs du capteur GPS
#define ID_VAL_LAT_DEG  0    // No de la valeur "Degres latitude" dans la trame
#define ID_VAL_LAT_MIN  1    // No de la valeur "Minutes latitude" dans la trame
#define ID_VAL_LON_DEG  2    // No de la valeur "Degres longitude" dans la trame
#define ID_VAL_LON_MIN  3    // No de la valeur "Minutes longitude" dans la trame
#define ID_VAL_VIT      4    // No de la valeur "Vitesse" dans la trame
#define ID_VAL_UTIME    5    // No de la valeur "temps UTC" dans la trame
#define ID_VAL_ALT      6    // No de la valeur "temps UTC" dans la trame


/*  ------- CAPTEUR HUMIDITE -------  */

#define HYT371_ADDR     0x28 // Adresse I2C Capteur Humidité

/*  ------- CAPTEUR PRESSION -------  */

#define PIN_PRESS       2

/*  ------- CAPTEUR TEMPERATURE -------  */

#define PIN_TEMP        3

/*  ------- CAPTEUR TEMPERATURE -------  */

#define SD_CS_PIN       9

#endif
