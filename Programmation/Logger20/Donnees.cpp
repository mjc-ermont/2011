#include "Donnees.h"

Donnees::Donnees() : db(QSqlDatabase::addDatabase("QMYSQL")){
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

        db.setHostName("127.0.0.1");
        db.setUserName("root");
        db.setPassword("");
        db.setDatabaseName("logger");
}

Donnees::~Donnees(){
    db.close();
}

void Donnees::appendLine(Line* a){
    appendRow(a->toList());

    appendInFile();
    appendInDB(a);
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

        for(int i = 0 ; i < columnCount() ; i++){
            flux << item(rowCount()-1, i)->text();
            flux << " ";
        }

        flux << endl;

        fichier.close();

        emit msg("[Sauvegarde] Dernier enregistrement � " + QDateTime::currentDateTime().toString("hh:mm:ss"));
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

            insertRow(rowCount(), prep);
            prep.clear();
        }

        emit msg(QString("[Sauvegarde] " + QString::number(rowCount()) + " lignes ont �t�s charg�s depuis le fichier \"" + QApplication::applicationDirPath() + "/save.log\"."));

        fichier.close();
    }
}

void Donnees::connect(){
    db.close();

    if(db.open())
    {
        emit msg("[MySQL] Vous �tes maintenant connect� � " + db.hostName());
        db.close();
    }
    else
    {
        emit msg("[MySQL] La connexion � la base de donn�es � �chou�e, d�sol� : " + db.lastError().text());
    }
}

bool Donnees::appendInDB(Line* a){
    /*QSqlQuery q;

    q.prepare("INSERT INTO logger VALUES('', '', ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    for(int i = 2 ; i < a->toList().size() ; i++){
        q.addBindValue(a->toList().toVector()[i]->text().toDouble());
    }

    if (q.execBatch()){
        emit msg("�a marche ! :)");
    }
    else{
        emit msg("�a marche pas ! :(");
    }*/
    db.open();
    QSqlQuery query(db);
    query.prepare("INSERT INTO logger (altitude, vith, vitv, tempout, tempin, temphyg, hyg, pressout, pressin, gpsx, gpsy, gpsaltitude, CH4, CO2, GyrX, GyrY, GyrZ) "
                  "VALUES (:altitude, :vith, :vitv, :tempout, :tempin, :temphyg, :hyg, :pressout, :pressin, :gpsx, :gpsy, :gpsaltitude, :CH4, :CO2, :GyrX, :GyrY, :GyrZ)");
    query.bindValue(":altitude", a->altitude);
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
    query.exec();
}
