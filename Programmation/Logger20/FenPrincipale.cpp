#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) : QMainWindow(parent), ui(new Ui::FenPrincipale), historique(new Donnees()){

    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));

    //------------------------------------------------------------------------------------------------------

    ui->setupUi(this);
    ui->tableWindow->setWindowTitle("Historique");
    ui->infosWindow->setWindowTitle("Tableau de bord");
    ui->consoleWindow->setWindowTitle("Console");

    ui->table->setModel(historique);

    historique->connect();

    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }

}

FenPrincipale::~FenPrincipale(){
    delete ui;
}

void FenPrincipale::append(Line *a){
    historique->appendLine(a);
}

void FenPrincipale::message(QString message){
    ui->statusBar->showMessage(message);
    ui->console->appendPlainText(message);
}
