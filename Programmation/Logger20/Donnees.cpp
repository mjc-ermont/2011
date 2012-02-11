#include "Donnees.h"

Donnees::Donnees(){
        setHorizontalHeaderItem(0, new QStandardItem("Date / heure"));
        setHorizontalHeaderItem(1, new QStandardItem("Altitude"));
        setHorizontalHeaderItem(2, new QStandardItem("Vitesse Horizontale"));
        setHorizontalHeaderItem(3, new QStandardItem("Vitesse Verticale"));
        setHorizontalHeaderItem(4, new QStandardItem("Temperature exterieure"));
        setHorizontalHeaderItem(5, new QStandardItem("Temperature interieure"));
        setHorizontalHeaderItem(6, new QStandardItem("Temperature hygrometre"));
        setHorizontalHeaderItem(7, new QStandardItem("Hygrometrie"));
        setHorizontalHeaderItem(8, new QStandardItem("Pression exterieur"));
        setHorizontalHeaderItem(9, new QStandardItem("Pression interieure"));
        setHorizontalHeaderItem(10, new QStandardItem("GPS - X"));
        setHorizontalHeaderItem(11, new QStandardItem("GPS - Y"));
        setHorizontalHeaderItem(12, new QStandardItem("GPS - Altitude"));
        setHorizontalHeaderItem(13, new QStandardItem("CH4"));
        setHorizontalHeaderItem(14, new QStandardItem("CO2"));
        setHorizontalHeaderItem(15, new QStandardItem("Gyroscope - X"));
        setHorizontalHeaderItem(16, new QStandardItem("Gyroscope - Y"));
        setHorizontalHeaderItem(17, new QStandardItem("Gyroscope - Z"));
}

void Donnees::appendLine(Line* a){
    appendRow(a->toList());

    appendInFile(a);
}

bool Donnees::appendInFile(Line *a){
    QFile fichier(QApplication::applicationDirPath() + "/save.log");

    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Append)){
        // N'a pas reussis a ouvrir
        emit msg("Erreur : n'as pas reussis a ouvrir le fichier de sauvegarde !");
        return false;
    }
    else{
        QTextStream flux(&fichier);

        for(int i = 0 ; i < columnCount() ; i++){
            flux << item(rowCount()-1, i)->text();
            flux << " ";
        }

        flux << endl;

        fichier.close();

        emit msg("Dernier enregistrement à " + QDateTime::currentDateTime().toString("hh:mm:ss"));
    }
    return true;
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

        emit msg(QString(QString::number(rowCount()) + " lignes ont étés chargés depuis le fichier \"" + QApplication::applicationDirPath() + "/save.log\"."));

        fichier.close();
    }
}
