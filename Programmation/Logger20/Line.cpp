#include "Line.h"

Line::Line(QObject *parent) : QObject(parent), time(QDateTime::currentDateTime()){

}

QList<QStandardItem *> Line::toList() const{
    QList<QStandardItem *> prep;

    prep << new QStandardItem(time.toString("dd/MM/yyyy-hh:mm:ss"));
    prep << new QStandardItem(QString::number(altitude));
    prep << new QStandardItem(QString::number(vith));
    prep << new QStandardItem(QString::number(vitv));
    prep << new QStandardItem(QString::number(tempout));
    prep << new QStandardItem(QString::number(tempin));
    prep << new QStandardItem(QString::number(temphyg));
    prep << new QStandardItem(QString::number(hyg));
    prep << new QStandardItem(QString::number(pressout));
    prep << new QStandardItem(QString::number(pressin));
    prep << new QStandardItem(QString::number(gpsx));
    prep << new QStandardItem(QString::number(gpsy));
    prep << new QStandardItem(QString::number(gpsaltitude));
    prep << new QStandardItem(QString::number(CH4));
    prep << new QStandardItem(QString::number(CO2));
    prep << new QStandardItem(QString::number(GyrX));
    prep << new QStandardItem(QString::number(GyrY));
    prep << new QStandardItem(QString::number(GyrZ));

    return prep;
}
