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

    public slots:
        void message(QString message);

private slots:
    void on_pushButton_clicked();
};

#endif // FENPRINCIPALE_H
