#include "Donnees.h"

Donnees::Donnees(){
    /*Creation des colones : eviter de modifier : risque d'incorence du programme
    **En cas de modifications, ne pas oublier de remplacer le numro de colone*/

        setHorizontalHeaderItem(0, new QStandardItem("Date / heure"));
        setHorizontalHeaderItem(1, new QStandardItem("Vitesse Horizontale"));
        setHorizontalHeaderItem(2, new QStandardItem("Vitesse Verticale"));
        setHorizontalHeaderItem(3, new QStandardItem("Temperature exterieure"));
        setHorizontalHeaderItem(4, new QStandardItem("Temperature interieure"));
        setHorizontalHeaderItem(5, new QStandardItem("Temperature hygrometre"));
        setHorizontalHeaderItem(6, new QStandardItem("Hygrometrie"));
        setHorizontalHeaderItem(7, new QStandardItem("Pression interieure"));
        setHorizontalHeaderItem(8, new QStandardItem("Pression exterieur"));
        setHorizontalHeaderItem(9, new QStandardItem("GPS - X"));
        setHorizontalHeaderItem(10, new QStandardItem("GPS - Y"));
        setHorizontalHeaderItem(11, new QStandardItem("GPS - Altitude"));
        setHorizontalHeaderItem(12, new QStandardItem("CH4"));
        setHorizontalHeaderItem(13, new QStandardItem("CO2"));
        setHorizontalHeaderItem(14, new QStandardItem("Gyroscope - X"));
        setHorizontalHeaderItem(15, new QStandardItem("Gyroscope - Y"));
        setHorizontalHeaderItem(16, new QStandardItem("Gyroscope - Z"));
}
