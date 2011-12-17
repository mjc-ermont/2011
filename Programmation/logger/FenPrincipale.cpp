#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) : QMainWindow(parent), ui(new Ui::FenPrincipale), historique(new Donnees){
    ui->setupUi(this);

    ui->tableWindow->setWindowTitle("Historique");
    ui->infosWindow->setWindowTitle("Tableau de bord");

    ui->table->setModel(historique);

    connect(historique, SIGNAL(msg(QString)), ui->statusBar, SLOT(showMessage(QString)));

    if(QFile::exists(QApplication::applicationDirPath() + "/save.log")){
        historique->open();
    }
    else{
        historique->append(42.1337, 10, -1, 40, 12.5, 21, 5, 52, 100, 898, 10, -1, 40);
        historique->append(42.1337, 10, -1, 40, 7875.057, -3 , 90909099090, 3, -2378, 283, 10, -1, 40);
        historique->append(42.1337, 10, -1, 40, 123, -300, -200, 4564.5, 53265.4, 3002.7, 10, -1, 40);
        historique->append(42.1337, 10, -1, 40, 42, 0, 0, -36, 8, 63.0, 10, -1, 40);
        historique->append(42.1337, 10, -1, 40, 1337, 1, 0, -1, 83.83, 63.7, 10, -1, 40);
        historique->append(42.1337, 10, -1, 40, 42.1337, 10, -1, 40, 9.1, 83.9, 10, -1, 40);
    }
}

FenPrincipale::~FenPrincipale(){
    delete ui;
}
