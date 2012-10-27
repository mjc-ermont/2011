#include "Line.h"


Line::Line(QObject *parent) : QObject(parent){


    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
            h_reception.push_back(QTime(0,0));

            QPair<QString, double> value;
            value.first = "-1";
            value.second = -1;

            switch(c) {
            case 0: // GPS
                capteurNames.push_back("GPS");
                switch(v) {
                case 0: // Pos X
                    value.first = "Latitude - Degrés";
                    break;
                case 1: // Pos Y
                    value.first = "Latitude - Minute";
                    break;
                case 2:
                    value.first = "Longitude - Degrés";
                    break;
                case 3:
                    value.first = "Longitude - Minute";
                    break;
                case 4:
                    value.first = "Vitesse (Knots)";
                    break;
                case 5:
                    value.first = "Heure UTC";
                    break;
                case 6: // Altitude
                    value.first = "Altitude (m)";
                    break;

                }

                break;
            case 1: // ACCELEROMETRE
                capteurNames.push_back("Accéléromètre");
                switch(v) {
                case 0:
                    value.first = "Valeur moyenne";
                    break;
                }
                break;
            case 2: // HUMIDITE
                capteurNames.push_back("Humidité");
                switch(v) {
                case 0:
                    value.first = "Humidité";
                    break;
                case 1:
                    value.first = "Température";
                    break;
                }
                break;
            }

            content.push_back(value);
        }
    }

    capteurNames.removeDuplicates();

    qDebug() << h_reception.size();
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

QList<QStandardItem *> Line::toList(int numCapteur) const{
    QList<QStandardItem *> prep;

    for(int v=0;v < 10;v++) {
        if(content[numCapteur*10+v].first != "-1") {
            prep << new QStandardItem(QString::number(content[numCapteur*10+v].second));
        }
    }

    return prep;
}

QString Line::get_checksum(QString trame) {

    char XOR = 0;
    for (int i = 0; i < trame.length() ; i++)
    {
       XOR = XOR ^ trame.toStdString()[i];
    }

    qDebug() << XOR;

    return QString::number(XOR);
}

QString Line::addData(QString trame) {
    QString erreur = "OK";

    qDebug() << "La trame: " << trame;

DEFINES_H
    QStringList elements = trame.split("$");
/*    for(int i=0;i < elements.size();i++) {
        qDebug() << "[" << i << "] " << elements[i];
    }*/

    if(elements.size() < 5)
        return "Ya un bug lol.";

    QString firstPart = elements[0] + "$" + elements[1] + "$" + elements[2] + "$" + elements[3] + "$";
    QString checkSum = get_checksum(firstPart);
    qDebug() << "CS: "<< QString(checkSum).toInt(NULL, 10) << " | "  << elements[4].toInt(NULL, 16) ;
    if(QString(checkSum).toInt(NULL, 10) == elements[4].toInt(NULL, 16) ) {
        int numCapteur = elements[1].toInt();
        double valeur = elements[3].toDouble();
        int numValeur = elements[2].toInt();

        if(numCapteur == 2) // LE PUTAIN DE CAPTEUR D'ARTHUR QU'IL FAUT DIVISER PAR 100
            valeur = valeur / 100;

        qDebug() << "VALEUR BORDEL DE MERDE ("<<numCapteur<<";"<<numValeur<< ")"<<valeur;

        content[numCapteur*NB_VALEURS_MAX+numValeur].second = valeur;
        h_reception[numCapteur*NB_VALEURS_MAX + numValeur] = QTime::currentTime();
    } else {
        erreur = "Mauvais checksum.";
    }

    return erreur;
}

double Line::getValue(int c, int v) {
    return content[c*NB_VALEURS_MAX+v].second;
}

bool Line::checkComplete() {
    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < NB_VALEURS_MAX;v++) {
            if((content[c*NB_VALEURS_MAX+v].first != "-1") && content[c*NB_VALEURS_MAX+v].second == -1)
                return false;
        }
    }

    return true;
}

void Line::clear(){
    for(int c=0;c<NB_CAPTEURS;c++) {
        for(int v=0;v < NB_VALEURS_MAX;v++) {
            content[c*NB_VALEURS_MAX + v].second = -1;
            h_reception[c*NB_VALEURS_MAX + v] = QTime(0,0);
        }
    }
}

QVector<double> Line::getRawValues() {
    QVector<double> values;

    for(int c=0;c < NB_CAPTEURS;c++) {
        for(int v=0;v < NB_VALEURS_MAX;v++) {
            if(content[c*NB_VALEURS_MAX+v].first != "-1") {
                values.append(content[c*NB_VALEURS_MAX+v].second);
            }
        }
    }

    return values;
}


QVector<QPair<QTime,double> > Line::getValuesWithTime() {
    QVector<QPair<QTime,double> > values;


    for(int c=0;c < NB_CAPTEURS;c++) {
        for(int v=0;v < 10;v++) {
             QPair<QTime,double> tmp;
             tmp.first = h_reception[c*NB_VALEURS_MAX+v];
             tmp.second = content[c*NB_VALEURS_MAX+v].second;

             values.append(tmp);
        }
    }

    return values;
}

void Line::randUpdate(Line *befL) {
    for(int c=0;c < NB_CAPTEURS;c++) {
        for(int v=0;v < NB_VALEURS_MAX;v++) {
            if(content[c*NB_VALEURS_MAX+v].first != "-1") {
                 if(befL == 0) {
                     qDebug() <<  "KOUKOU ";
                     content[c*NB_VALEURS_MAX+v].second = (rand()%((rand()%1000)+1))/10.0;
                     h_reception[c*NB_VALEURS_MAX + v] = QTime::currentTime();
                } else {
                     qDebug() <<  "TU VEUX VOUAR MA BEAT ";
                     content[c*NB_VALEURS_MAX+v].second = befL->getValue(c,v) + (rand()%4)-2;
                     h_reception[c*NB_VALEURS_MAX + v] = QTime::currentTime();
                }
            }
        }
    }


    qDebug() << "Content: " << content.size();
    qDebug() << "H reception: " << h_reception.size();
}
