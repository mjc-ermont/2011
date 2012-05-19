#include "Line.h"

Line::Line(QObject *parent) : QObject(parent){


    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            QPair<QString, double> value;
            value.first = "-1";
            value.second = -1;

            switch(c) {
            case 0: // GPS
                capteurNames.push_back("GPS");
                switch(v) {
                case 0: // Pos X
                    value.first = "Latitude - Angle";
                    break;
                case 1: // Pos Y
                    value.first = "Latitude - Minute";
                    break;
                case 2:
                    value.first = "Longitude - Angle";
                    break;
                case 3:
                    value.first = "Longitude - Minute";
                    break;
                case 4:
                    value.first = "Vitesse (Knots)";
                    break;
                case 5:
                    value.first = "Heure";
                    break;
                case 6: // Altitude
                    value.first = "Altitude (m)";
                    break;

                }

                break;

            case 1: // Temperatures
                capteurNames.push_back("Température");
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
                capteurNames.push_back("Gyroscope");
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
                capteurNames.push_back("Gaz");
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
                capteurNames.push_back("Pression");
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
                capteurNames.push_back("Hygrométrie");
                switch(v) {
                case 0: // Exterieur
                    value.first = "Hygromètre";
                    break;

                }
            }

            content.push_back(value);
        }
    }

    capteurNames.removeDuplicates();
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

QString Line::get_checksum(const char *trame) {
    unsigned int check, i;
    int c;
    char buffer[17];

    for (i = 0 ; i < strlen(trame) ; i++){
            c = (unsigned char)trame[i];
            if (c != '$' && c!='#') check ^= c;
    }

    itoa(check, buffer, 10);
    return QString(buffer);
}

QString Line::addData(QString trame) {
    QString erreur = "OK";

    qDebug() << "La trame: " << trame;


    QStringList elements = trame.split("$");

    for(int i=0;i < elements.size();i++) {
        qDebug() << "[" << i << "] " << elements[i];
    }

    if(elements.size() != 5)
        return "Ya un bug lol.";

    QString firstPart = elements[0] + "$" + elements[1] + "$" + elements[2] + "$" + elements[3] + "$";
    QString checkSum = get_checksum(firstPart.toStdString().c_str());
    qDebug() << "CS: " << checkSum;
    if(checkSum == elements[4]) {
        int numCapteur = elements[1].toInt();
        double valeur = elements[3].toDouble();
        int numValeur = elements[2].toInt();

        content[numCapteur*10+numValeur].second = valeur;
    } else {
        erreur = "Mauvais checksum.";
    }

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
