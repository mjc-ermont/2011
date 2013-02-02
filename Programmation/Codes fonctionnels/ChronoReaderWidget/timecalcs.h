#ifndef TIMECALCS_H
#define TIMECALCS_H

#include <QtGui>

class TimeCalcs
{
    public:
        TimeCalcs();
        static QTime addition(QTime a, QTime b, int signea = 1, int signeb = 1);
        static int toMs(QTime a);
};

#endif // TIMECALCS_H
