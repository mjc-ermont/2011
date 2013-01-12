#ifndef DEFINES_H
#define DEFINES_H

#include <QTime>


/*
---------------------------------------------------------------------------
                               GENERAL
---------------------------------------------------------------------------
 */
#define UPDATE_TIME 942



// A enlever quand on utilise de vraies trames.
//#define DEBUG
#undef DEBUG


/*
---------------------------------------------------------------------------
                            LIAISON SERIE
---------------------------------------------------------------------------
 */

#define BAUD B4800
#define RX_SIZE 4096 /* taille tampon d'entrée */
#define TX_SIZE 4096 /* taille tampon de sortie */
#define MAX_WAIT_READ 5000 /* temps max d'attente pour lecture (en ms) */

typedef struct Data_ {
    QTime time;
    double value;
} Data;


#endif // DEFINES_H

