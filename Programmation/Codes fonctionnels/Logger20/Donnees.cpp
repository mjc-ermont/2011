#include "Donnees.h"

Donnees::Donnees() : db(QSqlDatabase::addDatabase("QMYSQL")), capteurs(QApplication::applicationDirPath() + "/Config/Capteurs.ini", QSettings::IniFormat){
    fenetre = new QStandardItemModel;

    Line l;
    QStringList nomCapteurs = l.getCapteursNames();
    QStringList nomValeurs = l.getValueNames();

    int i=0;

    for(int c = 0; c < NB_CAPTEURS;c++) {
        for(int v = 0; nomValeurs[c*10+v] != "-1"; v++) {
            qDebug() << "Capteur n°" << c << " : " << nomCapteurs[c] << " || Valeur n° " << v << " : " << nomValeurs[c*10+v];
            QString nom = nomCapteurs[c] + " - " + nomValeurs[c*10+v];

            fenetre->setHorizontalHeaderItem(i, new QStandardItem(nom));
            i++;
        }

    }

    //------------------------------------------------------------------

    /*db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("logger");*/
}

Donnees::~Donnees(){
    db.close();
}

void Donnees::appendLine(Line* a){
    fenetre->appendRow(a->toList());

 //   appendInFile();
  //  appendInDB(a);
}

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

            fenetre->insertRow(lignes(), prep);
            prep.clear();
        }

        emit msg(QString("[Sauvegarde] " + QString::number(lignes()) + " lignes ont étés chargés depuis le fichier \"" + QApplication::applicationDirPath() + "/save.log\"."));

        fichier.close();
    }
}

void Donnees::connect(){
    db.close();

    if(db.open())
    {
        emit msg("[MySQL] Vous êtes maintenant connecté à " + db.hostName());
        db.close();
    }
    else
    {
        emit msg("[MySQL] La connexion à la base de données à échouée, désolé : " + db.lastError().text());
    }
}

/**
 *
 *  @todo Réparer le fonction suivante.
 *
 *
 */


bool Donnees::appendInDB(Line* a){
    /*QSqlQuery q;

    q.prepare("INSERT INTO logger VALUES('', '', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    for(int i = 2 ; i < a->toList().size() ; i++){
        q.addBindValue(a->toList().toVector()[i]->text().toDouble());
    }

    if (q.execBatch()){
        emit msg("Ça marche ! :)");
    }
    else{
        emit msg("Ça marche pas ! :(");
    }*/

    db.open();
    QSqlQuery query(db);
   // query.prepare("INSERT INTO logger (altitude, vith, vitv, tempout, tempin, temphyg, hyg, pressout, pressin, gpsx, gpsy, gpsaltitude, CH4, CO2, GyrX, GyrY, GyrZ) "
   //               "VALUES (:altitude, :vith, :vitv, :tempout, :tempin, :temphyg, :hyg, :pressout, :pressin, :gpsx, :gpsy, :gpsaltitude, :CH4, :CO2, :GyrX, :GyrY, :GyrZ)");
   /* query.bindValue(":altitude", a->altitude);
    query.bindValue(":vith", a->vith);
    query.bindValue(":vitv", a->vitv);
    query.bindValue(":tempout", a->tempout);
    query.bindValue(":tempin", a->tempin);
    query.bindValue(":temphyg", a->temphyg);
    query.bindValue(":hyg", a->hyg);
    query.bindValue(":pressout", a->pressout);
    query.bindValue(":pressin", a->pressin);
    query.bindValue(":gpsx", a->gpsx);
    query.bindValue(":gpsy", a->gpsy);
    query.bindValue(":gpsaltitude", a->gpsaltitude);
    query.bindValue(":CH4", a->CH4);
    query.bindValue(":CO2", a->CO2);
    query.bindValue(":GyrX", a->GyrX);
    query.bindValue(":GyrY", a->GyrY);
    query.bindValue(":GyrZ", a->GyrZ);
    query.exec();*/

    return true;
}

QStandardItemModel *Donnees::toFen(){
    return fenetre;
}

//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------

/**
* @return Nombre de colonnes
* @author Remi
*/
int Donnees::colonnes() const{
    return fenetre->columnCount();
}

/**
* @return Nombre de colonnes
* @author Remi
*/
int Donnees::lignes() const{
    return fenetre->rowCount();
}

//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------

/**
* @return Nombre de capteurs enregistres
* @author Remi
*/
int Donnees::nbCapteurs() const{
    return capteurs.childGroups().size();
}

/**
* @return Liste des noms des capteurs
* @author Remi
*/
QStringList Donnees::listCapteurs() const{
    return capteurs.childGroups();
}

/**
* @return Une valeure du capteur
* @arg    Nom du capteur
* @arg    Type de valeure
* @author Remi
*/
QVariant Donnees::capteurInfo(QString capteur, QString type){
    capteurs.beginGroup(capteur);
    QVariant retourne = capteurs.value(type);
    capteurs.endGroup();

    return retourne;
}
