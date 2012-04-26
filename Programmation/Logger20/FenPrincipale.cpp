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

void FenPrincipale::on_pushButton_clicked()
{
    QString data = QString::fromStdString(com->readData());
    if(data != "")
        message(data);
}
