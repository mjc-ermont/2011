#include "chronoreaderwidget.h"
#include "ui_chronoreaderwidget.h"

ChronoReaderWidget::ChronoReaderWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ChronoReaderWidget){
    ui->setupUi(this);

    open();
    foreach(event i, evenements){
        boxes << new EventBox(i.titre, i.contribs, i.moment, i.lieu, i.description);
        ui->layout->addWidget(boxes[boxes.size()-1]);
    }

    laucherCounter(QTime(17,40));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer->start(500);
}

ChronoReaderWidget::~ChronoReaderWidget(){
    delete ui;
}

void ChronoReaderWidget::open(){
    QFile fichier("chronologie.json");
    QString json("");
    QJson::Parser parser;

    if(fichier.open(QIODevice::ReadOnly)){
        json = fichier.readAll();
        fichier.flush();
        fichier.close();
    }

    QVariantMap result = parser.parse(json.toAscii()).toMap();
    QVariantList eventList(result["events"].toList());

    foreach(QVariant eventstr, eventList){
        QVariantMap curentevent = eventstr.toMap();
        event entree;
        int i(0);
            entree.titre = curentevent["titre"].toString();
            entree.description = curentevent["description"].toString();
            entree.contribs = curentevent["contributeurs"].toString();
            entree.moment = curentevent["time"].toInt();
            entree.lieu = curentevent["lieu"].toString();
        while(i < evenements.size() && evenements[i].moment < entree.moment){
            i++;
        }
        evenements.insert(i, entree);
    }
}

void ChronoReaderWidget::laucherCounter(QTime m_heure){
    heure = m_heure;

    foreach(EventBox *i, boxes){
        i->setTime(heure);
    }
}

void ChronoReaderWidget::refresh(){
    foreach(EventBox *i, boxes){
        i->reload();
    }
}
