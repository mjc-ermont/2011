#include "chronoedit.h"
#include "ui_chronoedit.h"

ChronoEdit::ChronoEdit(QWidget *parent) : QWidget(parent), ui(new Ui::ChronoEdit){
    ui->setupUi(this);

    connect(ui->addContributeur, SIGNAL(pressed()), this, SLOT(ajouterContrib()));
    connect(ui->addContributeur, SIGNAL(pressed()), ui->setContributeur, SLOT(clear()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(ajouterLieu()));
    connect(ui->addLieu, SIGNAL(pressed()), ui->setLieu, SLOT(clear()));
}

ChronoEdit::~ChronoEdit(){
    delete ui;
}

void ChronoEdit::ajouterContrib(){
    if( ! ui->Contributeurs->findItems(ui->setContributeur->text(), Qt::MatchExactly).count()  && ! ui->setContributeur->text().isEmpty()){
        ui->Contributeurs->addItem(ui->setContributeur->text());
        ui->actionnaireCombo->addItem(ui->setContributeur->text());
    }
}

void ChronoEdit::ajouterLieu(){
    if( ! ui->Lieux->findItems(ui->setLieu->text(), Qt::MatchExactly).count()  && ! ui->setLieu->text().isEmpty()){
        ui->Lieux->addItem(ui->setLieu->text());
        ui->lieuCombo->addItem(ui->setLieu->text());
    }
}
