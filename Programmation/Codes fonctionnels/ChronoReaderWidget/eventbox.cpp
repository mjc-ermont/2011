#include "eventbox.h"
#include "ui_eventbox.h"

EventBox::EventBox(QString name, QString contributeurs, QTime m_debut, int m_signe, QTime m_fin, QString lieu, QString description) : debut(m_debut), signe(m_signe), fin(m_fin), began(false), finish(false), ui(new Ui::EventBox){
    ui->setupUi(this);
        ui->name->setTitle(name);
        ui->contribs->setText(contributeurs);
        ui->lieu->setText(lieu);
        this->setToolTip(description);

        if(signe == -1 && TimeCalcs::toMs(debut) > TimeCalcs::toMs(fin)){
            ui->time->setText("-"+debut.toString());
            ui->fin->setText("-" + TimeCalcs::addition(debut, fin, 1, -1).toString());
        }
        else if(signe == -1 && TimeCalcs::toMs(debut) == TimeCalcs::toMs(fin)){
            ui->time->setText("-"+debut.toString());
            ui->fin->setText(TimeCalcs::addition(debut, fin, 1, -1).toString());
        }
        else{
            ui->time->setText(debut.toString());
            ui->fin->setText(TimeCalcs::addition(fin, debut, 1, signe).toString());
        }
        ui->progression->setValue(0);
        ui->progression->hide();
}

EventBox::~EventBox(){
    delete ui;
}

void EventBox::setTime(QTime m_time){
    time = m_time;
    ui->time->setText(TimeCalcs::addition(debut, time, signe).toString());
    ui->fin->setText(TimeCalcs::addition(TimeCalcs::addition(debut, time, signe), fin).toString());

    reload();
}

void EventBox::reload(){
    if(TimeCalcs::toMs(QTime::currentTime()) > TimeCalcs::toMs(TimeCalcs::addition(debut, time, signe))){
        if(!began){
            began = true;
            emit begin();
            ui->progression->show();
        }
        int avance = TimeCalcs::toMs(QTime::currentTime()) - TimeCalcs::toMs(TimeCalcs::addition(debut, time, signe));
        if(avance > TimeCalcs::toMs(fin)){
            ui->progression->setValue(100);
            if(!finish){
                finish=true;
                emit finished();
            }
        }
        else
            ui->progression->setValue((avance*100)/TimeCalcs::toMs(fin));
    }
}

void EventBox::mousePressEvent(QMouseEvent *a){
    if(finish)
        hide();
}
