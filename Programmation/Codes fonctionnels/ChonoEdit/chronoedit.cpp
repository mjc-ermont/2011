#include "chronoedit.h"
#include "ui_chronoedit.h"

ChronoEdit::ChronoEdit(QWidget *parent) : QWidget(parent), ui(new Ui::ChronoEdit){
    ui->setupUi(this);

    connect(ui->addContributeur, SIGNAL(pressed()), this, SLOT(ajouterContrib()));
    connect(ui->addContributeur, SIGNAL(pressed()), ui->setContributeur, SLOT(clear()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(ajouterLieu()));
    connect(ui->addLieu, SIGNAL(pressed()), ui->setLieu, SLOT(clear()));

    connect(this, SIGNAL(notAllSet(bool)), ui->addEvent, SLOT(setEnabled(bool)));
    connect(ui->checkContribs, SIGNAL(pressed()), this, SLOT(refreshContribLabel()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(verifyEnable()));
    connect(ui->eventTitle, SIGNAL(textEdited(QString)), this, SLOT(verifyEnable()));
    connect(ui->checkContribs, SIGNAL(pressed()), this, SLOT(verifyEnable()));
    connect(ui->addEvent, SIGNAL(pressed()), this, SLOT(ajouterEvent()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(save()));
    connect(ui->addContributeur, SIGNAL(pressed()), this, SLOT(save()));
    connect(ui->addEvent, SIGNAL(pressed()), this, SLOT(save()));
}

ChronoEdit::~ChronoEdit(){
    delete ui;
}

QString ChronoEdit::json(){
    QVariantMap all;

        QVariantList contributeurs;
        for(int i = 0 ; i < ui->Contributeurs->count() ; i++){
            contributeurs << ui->Contributeurs->item(i)->text();
        }
        all.insert("contributeurs", contributeurs);

        QVariantList lieux;
        for(int i = 0 ; i < ui->Lieux->count() ; i ++){
            lieux << ui->Lieux->item(i)->text();
        }
        all.insert("lieux", lieux);

        QVariantList events;
        for(int i = 0 ; i < ui->events->rowCount() ; i ++){
            QVariantMap event;
            event.insert("titre", ui->events->item(i, 0)->text());
            event.insert("time", ui->events->item(i, 1)->text());
            event.insert("lieu", ui->events->item(i, 2)->text());
            event.insert("contributeurs", ui->events->item(i, 3)->text());
            event.insert("description", ui->events->item(i, 4)->text());
            events.insert(i, event);
        }
        all.insert("events", events);

    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(all);

    return QString(json);
}

void ChronoEdit::ajouterContrib(){
    if(ui->Contributeurs->findItems(ui->setContributeur->text(), Qt::MatchExactly).count()   ||   ui->setContributeur->text().isEmpty())
        return;

    ui->Contributeurs->addItem(ui->setContributeur->text());
}

void ChronoEdit::ajouterLieu(){
    if(ui->Lieux->findItems(ui->setLieu->text(), Qt::MatchExactly).count()   ||    ui->setLieu->text().isEmpty())
        return;

    ui->Lieux->addItem(ui->setLieu->text());
    ui->eventPlace->addItem(ui->setLieu->text());
}

void ChronoEdit::ajouterEvent(){
    int ligne = ui->events->rowCount();

    ui->events->insertRow(ligne);
    ui->events->setItem(ligne, 0, new QTableWidgetItem(ui->eventTitle->text()));
    ui->events->setItem(ligne, 1, new QTableWidgetItem(ui->eventTime->text()));
    ui->events->setItem(ligne, 2, new QTableWidgetItem(ui->eventPlace->itemText(ui->eventPlace->currentIndex())));
    ui->events->setItem(ligne, 3, new QTableWidgetItem(ui->eventResp->text()));
    ui->events->setItem(ligne, 4, new QTableWidgetItem(ui->eventDesc->toPlainText()));

    ui->eventTitle->clear();
    ui->eventDesc->clear();
}

void ChronoEdit::save(){
    QFile fichier("chronologie.json");
    QString config(json());

    if(fichier.open(QIODevice::WriteOnly))
    {
        qDebug("Ouverture du fichier de configuration pour ecriture reussie");
        fichier.write(config.toAscii());

        fichier.flush();
        fichier.close();
    }
}

void ChronoEdit::refreshContribLabel(){
    QList<QListWidgetItem *> liste( ui->Contributeurs->selectedItems() );
    QString text("");

    foreach( QListWidgetItem *i , liste){
        text += i->text() + ", ";
    }
    text.resize(text.size() - 2);
    if( liste.size() == 0 ){
        text = "Aucun - selectionnez dans l'onglet \"Contributeurs\"";
    }

    ui->eventResp->setText(text);
}

void ChronoEdit::verifyEnable(){
    bool checker (true);

    if(ui->eventTitle->text().isEmpty())
        checker = false;
    if(ui->Lieux->count() == 0)
        checker = false;
    if(ui->eventResp->text() == "Aucun - selectionnez dans l'onglet \"Contributeurs\"")
        checker = false;

    emit notAllSet(checker);
}
