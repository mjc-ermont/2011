#ifndef CHRONOREADERWIDGET_H
#define CHRONOREADERWIDGET_H

#include <QtGui>
#include <qjson/parser.h>
#include <qjson/serializer.h>

#include "eventbox.h"
#include "TimeCalcs/timecalcs.h"

namespace Ui {
class ChronoReaderWidget;
}

/****************************************************************
**              Comment utilliser ChronoReaderWidget ?          *
*****************************************************************
** Méthodes :
**  Pour lancer le compteur et definir l'heure de lancement : laucherCounter( heure de lancement du ballon : "QTime" )
**  Si tu veut recharger le fichier :                         open()
**
** Signaux :
**  Pour quand y a un compteur qui commence :                 eventBegan(event)
**  Pour quand y a un compteur qui fini :                     eventFinished(event)
**/

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
