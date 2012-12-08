#ifndef CHRONOEDIT_H
#define CHRONOEDIT_H

#include <QtGui>
#include <qjson/parser.h>
#include <qjson/serializer.h>

namespace Ui {
class ChronoEdit;
}

class ChronoEdit : public QWidget
{
    Q_OBJECT
    
    public:
        explicit ChronoEdit(QWidget *parent = 0);
        ~ChronoEdit();

        QString json();

    private:
        Ui::ChronoEdit *ui;

    private slots:
        void ajouterContrib();
        void ajouterLieu();
        void ajouterEvent();

        void verifyEnable();
        void refreshContribLabel();

    public slots:
        void save();

    signals:
        void notAllSet(bool a = false);
};

#endif // CHRONOEDIT_H
