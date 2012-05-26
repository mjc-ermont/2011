#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtGui>
#include "Donnees.h"
#include "Line.h"
#include "serial.h"
#include "boardingtable.h"

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
        Line curLine;
        BoardingTable* tableauBord;

    public slots:
        void message(QString message);
        void requestAct();
        void informationsReceived(QStringList);

private slots:
    void on_b_param_clicked();
    void on_b_table_clicked();
    void on_b_tb_clicked();
    void on_b_console_clicked();
    void on_actionQuitter_triggered();
};

#endif // FENPRINCIPALE_H
