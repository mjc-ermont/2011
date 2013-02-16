#include "chronoreaderwidget.h"
#include "ui_chronoreaderwidget.h"

ChronoReaderWidget::ChronoReaderWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ChronoReaderWidget), finished(0), runing(0){
    ui->setupUi(this);

    open();
    foreach(event i, evenements){
        boxes << new EventBox(i.titre, i.contribs, i.debut, i.moment, i.fin, i.lieu, i.description);
        ui->layout->addWidget(boxes[boxes.size()-1]);
        connect(boxes[boxes.size()-1], SIGNAL(begin()), this, SLOT(hasBegun()));
        connect(boxes[boxes.size()-1], SIGNAL(finished()), this, SLOT(hasFinished()));
    }

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
            entree.moment = (curentevent["avant"].toString() == "avant")*(-1);
            entree.titre = curentevent["titre"].toString();
            entree.description = curentevent["description"].toString();
            entree.contribs = curentevent["contributeurs"].toString();
            entree.debut = QTime::fromString(curentevent["debut"].toString(), "hh:mm");
            entree.fin = QTime::fromString(curentevent["fin"].toString(), "hh:mm");
            entree.lieu = curentevent["lieu"].toString();

            while(i < evenements.size() && TimeCalcs::toMs(evenements[i].debut)*evenements[i].moment + TimeCalcs::toMs(evenements[i].fin) < TimeCalcs::toMs(entree.debut)*entree.moment + TimeCalcs::toMs(entree.fin)){
                i++;
        }
        evenements.insert(i, entree);
    }
}

void ChronoReaderWidget::laucherCounter(QTime m_heure){
    heure = m_heure;

    foreach(EventBox *i, boxes){
        i->setTime(m_heure);
    }
}

void ChronoReaderWidget::refresh(){
    foreach(EventBox *i, boxes){
        i->reload();
    }
}

void ChronoReaderWidget::hasBegun(){
    runing++;
    emit eventBegan(evenements[runing-1]);
    qDebug() << evenements[runing-1].titre << " a commence";
}

void ChronoReaderWidget::hasFinished(){
    finished++;
    emit eventFinished(evenements[finished-1]);
    qDebug() << evenements[finished-1].titre << " s'est termine";
    ui->scrollArea->horizontalScrollBar()->move(100, 0);
}
