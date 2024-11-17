#include "../modules/datetime.h"

/* *** KONSTRUKTOR *** */
void CreateDatetime(Datetime *t) {
    DAY(*t) = NIL;
    MONTH(*t) = NIL;
    YEAR(*t) = NIL;
    HOUR(*t) = NIL;
    MINUTE(*t) = NIL;
    SECOND(*t) = NIL;
    EPOCH(*t) = NIL;
}

/* *** TES KOSONG *** */
boolean isEmptyDatetime(Datetime t) {
    return (DAY(t) == NIL && MONTH(t) == NIL 
            && YEAR(t) == NIL && HOUR(t) == NIL 
            && MINUTE(t) == NIL && SECOND(t) == NIL 
            && EPOCH(t) == NIL);
}

/* *** MENCATAT WAKTU TERKINI *** */
void getDatetime(Datetime *t) {
    time_t now = time(NULL);
    //time_t time(time_t *x) 
    //both assign to *x and return, seconds since Unix Epoch
    if (now == (time_t)(-1)) {
        return;
    }

    //tm* localtime(time_t *x) convert seconds to readable-format
    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        return;
    }

    t->day = tm_info->tm_mday;
    t->month = tm_info->tm_mon + 1;      // tm_mon ranges 0 to 11
    t->year = tm_info->tm_year + 1900;   // tm_year years since 1900
    t->hour = tm_info->tm_hour;
    t->minute = tm_info->tm_min;
    t->second = tm_info->tm_sec;
    t->epoch = (int)now;                 // epoch adalah jumlah detik sejak UNIX EPOCH
}

/* *** KONVERSI *** */
int toSecond(Datetime t) {
    return EPOCH(t);
}

/* *** DISPLAY *** */
void displayDatetime(Datetime t) {
    printf("%02d-%02d-%d @ %02d.%02d", DAY(t), MONTH(t), YEAR(t)
                                    , HOUR(t), MINUTE(t));
}

