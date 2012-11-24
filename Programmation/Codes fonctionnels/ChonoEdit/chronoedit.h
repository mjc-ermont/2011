#ifndef CHRONOEDIT_H
#define CHRONOEDIT_H

#include <QWidget>

namespace Ui {
class ChronoEdit;
}

class ChronoEdit : public QWidget
{
    Q_OBJECT
    
    public:
        explicit ChronoEdit(QWidget *parent = 0);
        ~ChronoEdit();

    private:
        Ui::ChronoEdit *ui;

    private slots:
        void ajouterContrib();
        void ajouterLieu();

    public slots:
};

#endif // CHRONOEDIT_H
