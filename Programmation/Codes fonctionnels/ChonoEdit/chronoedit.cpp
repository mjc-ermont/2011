#include "chronoedit.h"
#include "ui_chronoedit.h"

ChronoEdit::ChronoEdit(QWidget *parent) : QWidget(parent), ui(new Ui::ChronoEdit){
    ui->setupUi(this);

    ui->events->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    connect(ui->addContributeur, SIGNAL(pressed()), this, SLOT(ajouterContrib()));
    connect(ui->addContributeur, SIGNAL(pressed()), ui->setContributeur, SLOT(clear()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(ajouterLieu()));
    connect(ui->addLieu, SIGNAL(pressed()), ui->setLieu, SLOT(clear()));

    connect(this, SIGNAL(notAllSet(bool)), ui->addEvent, SLOT(setEnabled(bool)));
    connect(ui->checkContribs, SIGNAL(pressed()), this, SLOT(refreshContribLabel()));
    connect(this, SIGNAL(deletePressed()), this, SLOT(deleteEvent()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(verifyEnable()));
    connect(ui->eventTitle, SIGNAL(textEdited(QString)), this, SLOT(verifyEnable()));
    connect(ui->checkContribs, SIGNAL(pressed()), this, SLOT(verifyEnable()));
    connect(ui->addEvent, SIGNAL(pressed()), this, SLOT(ajouterEvent()));

    connect(ui->addLieu, SIGNAL(pressed()), this, SLOT(save()));
    connect(ui->addContributeur, SIGNAL(pressed()), this, SLOT(save()));
    connect(ui->addEvent, SIGNAL(pressed()), this, SLOT(save()));

    open();
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
            event.insert("debut", ui->events->item(i, 1)->text());
            event.insert("fin", ui->events->item(i, 2)->text());
            event.insert("lieu", ui->events->item(i, 3)->text());
            event.insert("contributeurs", ui->events->item(i, 4)->text());
            event.insert("description", ui->events->item(i, 5)->text());
            events.insert(i, event);
        }
        all.insert("events", events);

    QJson::Serializer serializer;
    QByteArray json = serializer.serialize(all);

    return QString(json);
}

void ChronoEdit::setContrib(QString contrib){
    ui->Contributeurs->addItem(contrib);
}

void ChronoEdit::setLieu(QString lieu){
    ui->Lieux->addItem(lieu);
    ui->eventPlace->addItem(lieu);
}

void ChronoEdit::setEvent(QString titre, QString debut, QString fin, QString lieu, QString resp, QString desc){
    int ligne = ui->events->rowCount();

    ui->events->insertRow(ligne);
    ui->events->setItem(ligne, 0, new QTableWidgetItem(titre));
    ui->events->setItem(ligne, 1, new QTableWidgetItem(debut));
    ui->events->setItem(ligne, 2, new QTableWidgetItem(fin));
    ui->events->setItem(ligne, 3, new QTableWidgetItem(lieu));
    ui->events->setItem(ligne, 4, new QTableWidgetItem(resp));
    ui->events->setItem(ligne, 5, new QTableWidgetItem(desc));
}

void ChronoEdit::ajouterContrib(){
    if(ui->Contributeurs->findItems(ui->setContributeur->text(), Qt::MatchExactly).count()   ||   ui->setContributeur->text().isEmpty())
        return;

    setContrib(ui->setContributeur->text());
}

void ChronoEdit::ajouterLieu(){
    if(ui->Lieux->findItems(ui->setLieu->text(), Qt::MatchExactly).count()   ||    ui->setLieu->text().isEmpty())
        return;

    setLieu(ui->setLieu->text());
}

void ChronoEdit::ajouterEvent(){
    setEvent(ui->eventTitle->text(), ui->debut->text(), ui->fin->text(), ui->eventPlace->itemText(ui->eventPlace->currentIndex()), ui->eventResp->text(), ui->eventDesc->toPlainText());

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

void ChronoEdit::open(){
    QFile fichier("chronologie.json");
    QString json("");
    QJson::Parser parser;

    if(fichier.open(QIODevice::ReadOnly)){
        qDebug("\nOuverture du fichier de configuration pour lecture reussie");
        json = fichier.readAll();
        fichier.flush();
        fichier.close();
    }

    QVariantMap result = parser.parse(json.toAscii()).toMap();
    foreach(QString contrib, result["contributeurs"].toStringList()){
        setContrib(contrib);
    }
    foreach(QString lieu, result["lieux"].toStringList()){
        setLieu(lieu);
    }
    QVariantList eventList(result["events"].toList());
    foreach(QVariant eventstr, eventList){
        QVariantMap event = eventstr.toMap();
        setEvent(event["titre"].toString(), event["debut"].toString(), event["fin"].toString(),event["lieu"].toString() , event["contributeurs"].toString(), event["description"].toString());
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

void ChronoEdit::deleteEvent(){
    if(ui->tabWidget->currentIndex() == 0){
        QList<int> lignes;
        lignes << -1;
        foreach(QTableWidgetItem* i, ui->events->selectedItems()){
            if(!lignes.contains(i->row())){
                int j(0);
                while(lignes[j] > i->row()){
                    j++;
                }
                lignes.insert(j, i->row());
            }
        }

        foreach(int i, lignes){
            ui->events->removeRow(i);
        }
        save();
    }
}

void ChronoEdit::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Delete){
        emit deletePressed();
    }
}
