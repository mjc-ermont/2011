#include "Line.h"

Line::Line(QObject *parent) : QObject(parent){


    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            QPair<QString, double> value;
            value.first = "-1";
            value.second = -1;

            switch(c) {
            case 0: // GPS
                names.push_back("GPS");
                switch(v) {
                case 0: // Altitude
                    value.first = "Altitude";
                    break;
                case 1: // Pos X
                    value.first = "Position - X";
                    break;
                case 2: // Pos Y
                    value.first = "Position - Y";
                    break;
                case 3:
                    value.first = "Vitesse Horizontale";
                    break;
                case 4:
                    value.first = "Vitesse verticale";
                    break;

                }

                break;

            case 1: // Temperatures
                names.push_back("Température");
                switch(v) {
                case 0: // Exterieur
                    value.first = "Extérieure";
                    break;
                case 1: // Interieur
                    value.first = "Intérieure";
                    break;

                }
                break;

            case 2: // Gyroscope
                names.push_back("Gyroscope");
                switch(v) {
                case 0: // X
                    value.first = "X";
                    break;
                case 1: // Y
                    value.first = "Y";
                    break;
                case 2: // Z
                    value.first = "Z";
                    break;

                }
                break;

            case 3: // Gaz
                names.push_back("Gaz");
                switch(v) {
                case 0: // CH4
                    value.first = "CH4";
                    break;
                case 1: // CO2
                    value.first = "CO2";
                    break;

                }
                break;

            case 4: // Pressions
                names.push_back("Pression");
                switch(v) {
                case 0: // Exterieur
                    value.first = "Extérieur";
                    break;
                case 1: // Interieur
                    value.first = "Intérieur";
                    break;

                }
                break;
            case 5:
                names.push_back("Hygrométrie");
                switch(v) {
                case 0: // Exterieur
                    value.first = "Hygromètre";
                    break;

                }
            }

            content.push_back(value);
        }
    }
}

QStringList Line::getValueNames() {
    QStringList names;

    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            names.append(content[c*10+v].first);
        }
    }
    return names;
}

QList<QStandardItem *> Line::toList() const{
    QList<QStandardItem *> prep;

    heure.currentDateTime();
    prep << new QStandardItem(heure.toString("dd/MM/yyyy-hh:mm:ss"));

    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            if(content[c*10+v].first != "-1") {
                prep << new QStandardItem(QString::number(content[c*10+v].second));
            }
        }
    }

    return prep;
}

QString Line::addData(QString trame) {
    QString erreur = "OK";


    return erreur;
}

bool Line::checkComplete() {


    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            if((content[c*10+v].first != "-1") && content[c*10+v].second == -1)
                return false;
        }
    }

    return true;
}

void Line::clear(){
    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            content[c*10 + v].second = -1;
        }
    }
}
