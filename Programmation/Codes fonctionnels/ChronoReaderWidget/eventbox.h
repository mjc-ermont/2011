#ifndef EVENTBOX_H
#define EVENTBOX_H

#include <QtGui>

namespace Ui {
class EventBox;
}

class EventBox : public QFrame
{
    Q_OBJECT
    
    public:
        void setTime(QTime heure);
        void reload();

    explicit EventBox(QString name, QString contributeurs, int time, QString lieu, QString description = "");
        ~EventBox();

    private:
        Ui::EventBox *ui;

        QTime moment;
        QTime debut;
        int m_time;
};

#endif // EVENTBOX_H
