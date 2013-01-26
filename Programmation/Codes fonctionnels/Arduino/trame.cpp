#include <string.h>
#include <Arduino.h>

byte get_checksum(char *string) // fonction de génération du checksum
{
  byte XOR = 0;	// checksum, byte pour avoir une longueur de 2 chiffres hexa
  for (int i = 0; i < strlen(string) ; i++) 
  {
    XOR = XOR ^ string[i]; // xor entre le checksum et chaque caractère de la trame 
  }
  return XOR;
}

