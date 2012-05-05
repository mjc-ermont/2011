#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtGui>
#include "Donnees.h"
#include "Line.h"
#include "serial.h"

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

    private:
        Ui::FenPrincipale *ui;
        Donnees* historique;
        Serial* com;
        QTimer *timerAct;

    public slots:
        void message(QString message);
        void requestAct();
        void informationsReceived(QStringList);
};

#endif // FENPRINCIPALE_H
