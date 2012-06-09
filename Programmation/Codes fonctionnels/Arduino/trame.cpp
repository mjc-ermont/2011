#include <string.h>
#include <Arduino.h>
#include <string.h>

uint8_t get_checksum(char *string)
{
  uint8_t XOR = 0;	
  for (int i = 0; i < strlen(string); i++) 
  {
    XOR = XOR ^ string[i];
  }
  return XOR;
}

