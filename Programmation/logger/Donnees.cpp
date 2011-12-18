#include "Donnees.h"

Donnees::Donnees(QObject *parent) : QStandardItemModel(parent){
    setColumnCount(4);
    setHorizontalHeaderItem(0, new QStandardItem("Date / heure"));
    setHorizontalHeaderItem(1, new QStandardItem("Altitude (GPS)"));
    setHorizontalHeaderItem(2, new QStandardItem("Vitesse Horizontale"));
    setHorizontalHeaderItem(3, new QStandardItem("Vitesse Verticale"));
    setHorizontalHeaderItem(4, new QStandardItem("Temperature exterieure"));
    setHorizontalHeaderItem(5, new QStandardItem("Temperature interieure"));
    setHorizontalHeaderItem(6, new QStandardItem("Temperature (hygromètre)"));
    setHorizontalHeaderItem(7, new QStandardItem("Pression interieure"));
    setHorizontalHeaderItem(8, new QStandardItem("Exterieur interieure"));
    setHorizontalHeaderItem(9, new QStandardItem("GPS - X"));
    setHorizontalHeaderItem(10, new QStandardItem("GPS - Y"));
    setHorizontalHeaderItem(11, new QStandardItem("CH4"));
    setHorizontalHeaderItem(12, new QStandardItem("CO2"));
    setHorizontalHeaderItem(13, new QStandardItem("Gyroscope - X"));
    setHorizontalHeaderItem(14, new QStandardItem("Gyroscope - Y"));
    setHorizontalHeaderItem(15, new QStandardItem("Gyroscope - Z"));

}

void Donnees::append(double altitude, double vith, double vitv, double tempout, double tempin, double temphyg, double pressout, double pressin, int gpsx, int gpsy, double CO2, double CH4, double gyrx, double gyry, double gyrz){
   QList<QStandardItem *> prep;

   prep << new QStandardItem(QDateTime::currentDateTime().toString("dd/MM/yyyy-hh:mm:ss"));
   prep << new QStandardItem(QString::number(altitude));
   prep << new QStandardItem(QString::number(vith));
   prep << new QStandardItem(QString::number(vitv));
   prep << new QStandardItem(QString::number(tempout));
   prep << new QStandardItem(QString::number(tempin));
   prep << new QStandardItem(QString::number(temphyg));
   prep << new QStandardItem(QString::number(pressout));
   prep << new QStandardItem(QString::number(pressin));
   prep << new QStandardItem(QString::number(gpsx));
   prep << new QStandardItem(QString::number(gpsy));
   prep << new QStandardItem(QString::number(CO2));
   prep << new QStandardItem(QString::number(CH4));
   prep << new QStandardItem(QString::number(gyrx));
   prep << new QStandardItem(QString::number(gyry));
   prep << new QStandardItem(QString::number(gyrz));

   insertRow(rowCount(), prep);

   emit msg("Dernière modification effectué le " + QDateTime::currentDateTime().toString("dd/MM/yyyy-hh:mm:ss"));

   saveAppend();
}

void Donnees::saveAppend(){
    QFile fichier(QApplication::applicationDirPath() + "/save.log");

    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Append)){
        // N'a pas reussis a ouvrir
        emit msg("Erreur : n'as pas reussis a ouvrir le fichier de sauvegarde !");
    }
    else{
        QTextStream flux(&fichier);

        for(int i = 0 ; i < columnCount() ; i++){
            flux << item(rowCount()-1, i)->text();
            flux << " ";
        }

        flux << endl;

        fichier.close();
    }
}

void Donnees::open(){
    QString texte("");
    QString done("");
    QList<QStandardItem *> prep;

    QFile fichier(QApplication::applicationDirPath() + "/save.log");

    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        // N'a pas reussis a ouvrir
        emit msg("Erreur : n'as pas reussis a ouvrir le fichier de sauvegarde !");
    }

    else{
        QTextStream flux(&fichier);

        while(!flux.atEnd()){
            texte = flux.readLine() + '\n';
            texte.resize(texte.size()-1);

            for(int i = 0 ; i < texte.size() ; i++){
                if(texte[i] == ' '){
                    prep << new QStandardItem(done);

                    done = "";
                }
                else{
                    done += texte[i];
                }
            }

            insertRow(rowCount(), prep);
            prep.clear();
        }

        emit msg(QString::number(rowCount()) + " lignes ont étés chargés depuis le fichier \"" + QApplication::applicationDirPath() + "/save.log\".");

        fichier.close();
    }
}
