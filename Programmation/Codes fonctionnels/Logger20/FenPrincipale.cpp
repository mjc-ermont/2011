#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(Serial* _com) : ui(new Ui::FenPrincipale), historique(new Donnees()){

    connect(historique, SIGNAL(msg(QString)), this, SLOT(message(QString)));

    //------------------------------------------------------------------------------------------------------



    com = _com;


    ui->setupUi(this);
    ui->table->setModel(historique->toFen());

    historique->connect();

    tableauBord = new BoardingTable(ui->container);

    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }

    ui->stack->setCurrentIndex(0);

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

    if(ui->get_infos->isChecked())
        com->readData();

}

void FenPrincipale::informationsReceived(QStringList trames) {
    if(trames.size() > 0) {
        for(int i=0;i<trames.size();i++) {
            message(trames[i]);
            curLine.addData(trames[i]);
        }



        historique->appendLine(&curLine);
        curLine.clear();
    }
}

void FenPrincipale::append(Line *a){
    historique->appendLine(a);
}

void FenPrincipale::message(QString message){
    ui->statusBar->showMessage(message);
    ui->console->appendPlainText(message);
}


void FenPrincipale::on_actionQuitter_triggered()
{
    qApp->quit();
}

void FenPrincipale::on_b_console_clicked()
{
    reinit_b();
    ui->b_console->setDefault(true);

    ui->stack->setCurrentIndex(1);
}

void FenPrincipale::on_b_tb_clicked()
{
    reinit_b();
    ui->b_tb->setDefault(true);

    ui->stack->setCurrentIndex(0);
}

void FenPrincipale::on_b_table_clicked()
{
    reinit_b();
    ui->b_table->setDefault(true);

    ui->stack->setCurrentIndex(2);
}

void FenPrincipale::on_b_param_clicked()
{
    reinit_b();
    ui->b_param->setDefault(true);

    ui->stack->setCurrentIndex(3);
}

void FenPrincipale::reinit_b(){
    ui->b_tb->setDefault(false);
    ui->b_table->setDefault(false);
    ui->b_console->setDefault(false);
    ui->b_param->setDefault(false);
}
