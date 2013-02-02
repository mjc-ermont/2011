#include "timecalcs.h"

TimeCalcs::TimeCalcs(){

}

QTime TimeCalcs::addition(QTime a, QTime b, int signea, int signeb){
    return QTime(a.hour()*signea + (b.hour()*signeb), a.minute()*signea + (b.minute()*signeb), a.second()*signea + (b.second()*signeb), a.msec()*signea + (b.msec()*signeb));
}

int TimeCalcs::toMs(QTime a){
    return a.hour()*3600000 + a.minute()*60000 + a.second()*1000 + a.msec();
}
