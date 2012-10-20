#ifndef DEFINES_H
#define DEFINES_H



/*
---------------------------------------------------------------------------
                               GENERAL
---------------------------------------------------------------------------
 */

#define NB_CAPTEURS 6
#define NB_VALEURS_MAX 10

#define UPDATE_TIME 3000


// A enlever quand on utilise de vraies trames.
//#define DEBUG
#undef DEBUG



/*
---------------------------------------------------------------------------
                            LIAISON SERIE
---------------------------------------------------------------------------
 */

#define BAUD 9600
#define RX_SIZE 4096 /* taille tampon d'entrée */
#define TX_SIZE 4096 /* taille tampon de sortie */
#define MAX_WAIT_READ 5000 /* temps max d'attente pour lecture (en ms) */

#endif // DEFINES_H
