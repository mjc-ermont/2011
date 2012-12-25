void debug (const char *string){
#ifdef SERIAL_DEBUG
    Serial.println(string);
#
}
