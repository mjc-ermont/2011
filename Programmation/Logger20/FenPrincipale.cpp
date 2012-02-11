#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) : QMainWindow(parent), ui(new Ui::FenPrincipale){
    ui->setupUi(this);

    ui->tableWindow->setWindowTitle("Historique");
    ui->infosWindow->setWindowTitle("Tableau de bord");

    historique = new Donnees();
    ui->table->setModel(historique);
}

FenPrincipale::~FenPrincipale(){
    delete ui;
}
