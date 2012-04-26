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

    timerAct->setInterval(1000);
    connect(timerAct,SIGNAL(timeout()),this,SLOT(requestAct()));
    connect(com,SIGNAL(dataRead(std::string)),this,SLOT(informationsReceived(std::string)));
}

FenPrincipale::~FenPrincipale(){
    delete ui;
}

void FenPrincipale::requestAct() {
    //com->readData();
}

void FenPrincipale::informationsReceived(std::string _data) {
   /* QString data = QString::fromStdString(_data);
    if(data != "")
        message(data);*/
}

void FenPrincipale::append(Line *a){
    historique->appendLine(a);
}

void FenPrincipale::message(QString message){
    ui->statusBar->showMessage(message);
    ui->console->appendPlainText(message);
}

