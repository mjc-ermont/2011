#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(Serial* _com) : ui(new Ui::FenPrincipale), historique(new Donnees()){

    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));

    //------------------------------------------------------------------------------------------------------

    com = _com;


    ui->setupUi(this);
    ui->tableWindow->setWindowTitle("Historique");
    ui->infosWindow->setWindowTitle("Tableau de bord");
    ui->consoleWindow->setWindowTitle("Console");

    ui->table->setModel(historique->toFen());

    historique->connect();

    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }

    timerAct = new QTimer();
    connect(timerAct,SIGNAL(timeout()),this,SLOT(requestAct()));

    timerAct->start(5000);

    connect(com,SIGNAL(dataRead(QStringList)),this,SLOT(informationsReceived(QStringList)));
    requestAct();
}

FenPrincipale::~FenPrincipale(){
    delete ui;
}

void FenPrincipale::requestAct() {
    qDebug() << "Da goud ?";
    com->readData();

}

void FenPrincipale::informationsReceived(QStringList trames) {
    for(int i=0;i<trames.size();i++) {
        message(trames[i]);
        curLine.addData(trames[i]);

    }
}

void FenPrincipale::append(Line *a){
    historique->appendLine(a);
}

void FenPrincipale::message(QString message){
    ui->statusBar->showMessage(message);
    ui->console->appendPlainText(message);
}

