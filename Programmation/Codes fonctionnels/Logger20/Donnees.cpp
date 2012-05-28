#include "Donnees.h"

Donnees::Donnees(){


    Line l;
    QStringList nomCapteurs = l.getCapteursNames();
    QStringList nomValeurs = l.getValueNames();

    int i=0;

    for(int c = 0; c < NB_CAPTEURS;c++) {
        tables.append(new QStandardItemModel);
        for(int v = 0; nomValeurs[c*10+v] != "-1"; v++) {
            qDebug() << "Capteur n°" << c << " : " << nomCapteurs[c] << " || Valeur n° " << v << " : " << nomValeurs[c*10+v];
            QString nom = nomValeurs[c*10+v];

            tables[c]->setHorizontalHeaderItem(v,new QStandardItem(nom));
            i++;
        }

    }
}

Donnees::~Donnees(){
   // db.close();
}

void Donnees::appendLine(Line* a){
    data.append(a);

    for(int i=0;i< NB_CAPTEURS;i++) {
        tables[i]->appendRow(a->toList(i));
    }

}


QStandardItemModel* Donnees::toTable(int numCapteur) {
    return tables[numCapteur];
}




/*
bool Donnees::appendInFile(){
    QFile fichier(QApplication::applicationDirPath() + "/save.log");

    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Append)){
        // N'a pas reussis a ouvrir
        emit msg("Erreur : n'as pas reussis a ouvrir le fichier de sauvegarde !");
        return false;
    }
    else{
        QTextStream flux(&fichier);

        for(int i = 0 ; i < colonnes() ; i++){
            flux << fenetre->item(lignes()-1, i)->text();
            flux << " ";
        }

        flux << endl;

        fichier.close();

        emit msg("[Sauvegarde] Dernier enregistrement à " + QDateTime::currentDateTime().toString("hh:mm:ss"));
    }
    return true;
}
*/

void Donnees::open(){
    QString texte("");
    QString done("");
    QList<QStandardItem *> prep;

    QFile fichier(QApplication::applicationDirPath() + "/save.log");

    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        // N'a pas reussis a ouvrir
        emit msg("[Erreur] Erreur : n'as pas reussis a ouvrir le fichier de sauvegarde !");
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

         //   fenetre->insertRow(lignes(), prep);
            prep.clear();
        }

     //   emit msg(QString("[Sauvegarde] " + QString::number(lignes()) + " lignes ont étés chargés depuis le fichier \"" + QApplication::applicationDirPath() + "/save.log\"."));

        fichier.close();
    }
}

QVector<QPair<QTime, double> > Donnees::getData(int capteur, int valeur) {
    QVector<QPair<QTime, double> > donnees;

    for(int i=0;i<data.size();i++)
        donnees.append(data[i]->getValuesWithTime()[capteur*NB_VALEURS_MAX+valeur]);


    return donnees;
}
