#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QtGui>
#include "Donnees.h"
#include "Line.h"

namespace Ui {
    class FenPrincipale;
}

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        explicit FenPrincipale(QWidget *parent = 0);
        ~FenPrincipale();

    private:
        Ui::FenPrincipale *ui;
        Donnees* historique;

    public slots:
        void message(QString message);
};

#endif // FENPRINCIPALE_H
