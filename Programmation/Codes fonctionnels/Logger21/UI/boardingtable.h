#ifndef BOARDINGTABLE_H
#define BOARDINGTABLE_H

#include <QGridLayout>
#include <QLCDNumber>
#include <QGroupBox>
#include <QLabel>
#include "../InPut/sensormanager.h"
#include "defines.h"

class SensorManager;

class BoardingTable
{
public:
    BoardingTable(QGridLayout *container, SensorManager *mgr);
    ~BoardingTable();

    void init(SensorManager* );
    void update(SensorValue *sv);

private:
    QGridLayout *m_container;
    QVector<QGridLayout *> capteurs_layouts;
    QVector<QLCDNumber *> valeurs;
};

#endif // BOARDINGTABLE_H
