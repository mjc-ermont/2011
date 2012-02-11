#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QMainWindow>

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
};

#endif // FENPRINCIPALE_H
