#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) : QMainWindow(parent), ui(new Ui::FenPrincipale){
    ui->setupUi(this);

    ui->tableWindow->setWindowTitle("Historique");
    ui->infosWindow->setWindowTitle("Tableau de bord");

    historique = new Donnees();
    ui->table->setModel(historique);

    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));

    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }

    /*Line* n = new Line();

        n->altitude = 2.2;
        n->CH4 = 3;
        n->CO2 = 89;
        n->gpsaltitude = 6;
        n->gpsx = 4;
        n->gpsy = 121;
        n->GyrX = 89;
        n->GyrY = 90;
        n->GyrZ = 91;
        n->hyg = 88989;
        n->pressin = 100;
        n->pressout = 200;
        n->temphyg = 67;
        n->tempin = 28;
        n->tempout = 27;
        n->vith = 100;
        n->vitv = 101;

   historique->appendLine(n);*/


}

FenPrincipale::~FenPrincipale(){
    delete ui;
}

void FenPrincipale::message(QString message){
    ui->statusBar->showMessage(message);
}
