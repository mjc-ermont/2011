#include "eventbox.h"
#include "ui_eventbox.h"

EventBox::EventBox(QString name, QString contributeurs, int time, QString lieu, QString description) : m_time(time), ui(new Ui::EventBox){
    ui->setupUi(this);
        ui->name->setTitle(name);
        ui->contribs->setText(contributeurs);
        ui->lieu->setText(lieu);
        this->setToolTip(description);

        ui->time->setText(QString::number(time) + " minutes");
        ui->progression->setValue(0);
        ui->progression->hide();
}

EventBox::~EventBox(){
    delete ui;
}

void EventBox::setTime(QTime heure){
    debut = QTime::currentTime();

    moment = heure.addSecs(m_time*60);
    ui->time->setText(moment.toString("hh:mm"));

    ui->progression->show();
    reload();
}

void EventBox::reload(){
    int avancement =     (QTime::currentTime().hour()*3600 + QTime::currentTime().minute()*60 + QTime::currentTime().second()) - (debut.hour()*3600 + debut.minute()*60 + debut.second());
    int differenceTime = (moment.hour()*3600 + moment.minute()*60 + moment.second()) - (debut.hour()*3600 + debut.minute()*60 + debut.second());
    if(avancement > 0 && differenceTime > 0)
        ui->progression->setValue(int(avancement*100/differenceTime));
    else
        ui->progression->setValue(100);
    qDebug() << avancement << differenceTime;
}
