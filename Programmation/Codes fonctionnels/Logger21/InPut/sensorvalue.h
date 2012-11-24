#ifndef VALUE_H
#define VALUE_H

#include <QString>
#include <QVector>
#include <defines.h>


class SensorValue
{
public:
    SensorValue(QString i_name, QString i_unit, QString i_id);
    void addData(double d);
    QVector<Data> getData() {return datalist;}

private:
    QString name;
    QString unit;
    int id;
    QVector<Data> datalist;
};

#endif // VALUE_H
