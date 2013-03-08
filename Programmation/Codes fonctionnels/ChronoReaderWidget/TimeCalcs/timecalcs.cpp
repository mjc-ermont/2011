#include "timecalcs.h"

QTime TimeCalcs::addition(QTime a, QTime b, int signea, int signeb){
    if(signea < 0 && signeb > 0){
        return fromMs(a.msecsTo(b));
    }
    else if(signea > 0 && signeb < 0){
        return  fromMs(b.msecsTo(a));
    }
    else{
        return fromMs(QTime().msecsTo(a) + QTime().msecsTo(b));
    }
}

int TimeCalcs::toMs(QTime a){
    return a.hour()*3600000 + a.minute()*60000 + a.second()*1000 + a.msec();
}

QTime TimeCalcs::fromMs(int a){
    int ms,s,m,h,x(a);
        h = int(x / (3600000)) % 24;  x = x % (3600000);
        m = int(x / (60000));  x = x % (60000);
        s = int(x / (1000));  x = x % (1000);
        ms= x;
    return QTime(h,m,s,ms);
}
