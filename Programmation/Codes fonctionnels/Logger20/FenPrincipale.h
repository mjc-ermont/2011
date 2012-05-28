#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#define DEBUG // A activer si on n'utilise pas des vraies trames

#include <QtGui>
#include "Donnees.h"
#include "Line.h"
#include "serial.h"
#include "boardingtable.h"
#include "graphicview.h"
#include "defines.h"


namespace Ui {
    class FenPrincipale;
}

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        explicit FenPrincipale(Serial *com);
        ~FenPrincipale();

        void append(Line *a);

protected:
        void reinit_b();

    private:
        Ui::FenPrincipale *ui;
        Donnees* historique;
        Serial* com;
        QTimer *timerAct;
        QTimer *actTemps;
        Line curLine;
        BoardingTable* tableauBord;

        QVector<QTableView*> tableauxHist;
        QVector<GraphicView*> graphiques;


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
        void on_b_graph_clicked();
        void on_sel_capteur_currentIndexChanged(int index);
        void on_add_graph_clicked();
};

#endif // FENPRINCIPALE_H
