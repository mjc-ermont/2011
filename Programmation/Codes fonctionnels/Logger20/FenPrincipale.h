#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#define DEBUG // A activer si on n'utilise pas des vraies trames

#include <QtGui>
#include "ui_FenPrincipale.h"
#include "Donnees.h"
#include "Line.h"
#include "serial.h"
#include "boardingtable.h"
#include "graphicview.h"
#include "mapsview.h"
#include "defines.h"



class GraphicView;
class MapsView;

class FenPrincipale : public QMainWindow, public Ui::FenPrincipale
{
    Q_OBJECT

    public:
        explicit FenPrincipale(Serial *com);
        ~FenPrincipale();

        void append(Line *a);

        QTime getDepart() { return h_depart;}


protected:
        void reinit_b();

    private:
        Donnees* historique;
        Serial* com;
        QTimer *timerAct;
        QTimer *actTemps;
        Line curLine;
        BoardingTable* tableauBord;
        MapsView* carte;

        QVector<QTableView*> tableauxHist;
        QVector<GraphicView*> graphiques;

        QTime h_depart;


    public slots:
        void message(QString message);
        void requestAct();
        void informationsReceived(QStringList);
        void syncTime();

        void on_b_param_clicked();
        void on_b_table_clicked();
        void on_b_tb_clicked();
        void on_b_console_clicked();
        void on_actionQuitter_triggered();

private slots:
        void on_b_carte_clicked();
        void on_b_graph_clicked();
        void on_sel_capteur_currentIndexChanged(int index);
        void on_add_graph_clicked();

        void graphClosed();
};

#endif // FENPRINCIPALE_H

