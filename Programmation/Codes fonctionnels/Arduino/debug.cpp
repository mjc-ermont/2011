#include <Arduino.h>
#include "defines.h"

void debug (const char *string){
#if SERIAL_DEBUG
    Serial.println(string);
    Serial.flush();
#endif
}
