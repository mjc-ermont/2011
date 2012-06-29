#include <string.h>
#include <Arduino.h>

byte get_checksum(String string)
{
  byte XOR = 0;	
  for (int i = 0; i < string.length() ; i++) 
  {
    XOR = XOR ^ string[i];
  }
  return XOR;
}

