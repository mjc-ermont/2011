#ifndef CHRONOREADERWIDGET_H
#define CHRONOREADERWIDGET_H

#include <QtGui>
#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "eventbox.h"
#include "timecalcs.h"

namespace Ui {
class ChronoReaderWidget;
}

class ChronoReaderWidget : public QWidget
{
    Q_OBJECT

    struct event{
        int moment;
        QTime debut;
        QTime fin;
        QString titre;
        QString lieu;
        QString contribs;
        QString description;
    };

    public:
        explicit ChronoReaderWidget(QWidget *parent = 0);
        ~ChronoReaderWidget();

    public slots:
        void open();
        void laucherCounter(QTime m_heure);

    private slots:
        void refresh();

        void hasFinished();
        void hasBegun();

    signals:
        void eventBegan(event e);
        void eventFinished(event e);

    private:
        Ui::ChronoReaderWidget *ui;

    private:
        QList<event> evenements;
        QList<EventBox*> boxes;
        QTime heure;

        QTimer *timer;
        int finished, runing;
};

#endif // CHRONOREADERWIDGET_H
