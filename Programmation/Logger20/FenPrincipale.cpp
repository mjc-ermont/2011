#include "FenPrincipale.h"
#include "ui_FenPrincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenPrincipale)
{
    ui->setupUi(this);
}

FenPrincipale::~FenPrincipale()
{
    delete ui;
}
