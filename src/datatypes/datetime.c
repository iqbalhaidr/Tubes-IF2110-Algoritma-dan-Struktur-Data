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
    return (DAY(t) == NIL && MONTH(t) == NIL && YEAR(t) == NIL &&
            HOUR(t) == NIL && MINUTE(t) == NIL && SECOND(t) == NIL &&
            EPOCH(t) == NIL);
}

/* *** MENCATAT WAKTU TERKINI *** */
void getDatetime(Datetime *t) {
    time_t now = time(NULL);
    // time_t time(time_t *x)
    // both assign to *x and return, seconds since Unix Epoch
    if (now == (time_t)(-1)) {
        return;
    }

    // tm* localtime(time_t *x) convert seconds to readable-format
    struct tm *tm_info = localtime(&now);
    if (tm_info == NULL) {
        return;
    }

    t->day = tm_info->tm_mday;
    t->month = tm_info->tm_mon + 1;     // tm_mon ranges 0 to 11
    t->year = tm_info->tm_year + 1900;  // tm_year years since 1900
    t->hour = tm_info->tm_hour;
    t->minute = tm_info->tm_min;
    t->second = tm_info->tm_sec;
    t->epoch = (int)now;  // epoch adalah jumlah detik sejak UNIX EPOCH
}

/* *** KONVERSI *** */
int isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    int daysMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeap(year)) {
        return 29;
    }
    return daysMonth[month - 1];
}

int parseInt(const char *str, int start, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = result * 10 + (str[start + i] - '0');
    }
    return result;
}

int toEpoch(const char *timestamp) {
    int year = parseInt(timestamp, 0, 4);
    int month = parseInt(timestamp, 5, 2);
    int day = parseInt(timestamp, 8, 2);
    int hour = parseInt(timestamp, 11, 2);
    int minute = parseInt(timestamp, 14, 2);
    int second = parseInt(timestamp, 17, 2);
    int epochYear = 1970;
    int days = 0;

    for (int y = epochYear; y < year; y++) {
        days += isLeap(y) ? 366 : 365;
    }

    for (int m = 1; m < month; m++) {
        days += daysInMonth(year, m);
    }

    days += (day - 1);

    int seconds = days * 86400;
    seconds += hour * 3600;
    seconds += minute * 60;
    seconds += second;

    return seconds;
}

/* *** DISPLAY *** */
void displayDatetime(Datetime t) {
    printf("%02d-%02d-%d @ %02d.%02d", DAY(t), MONTH(t), YEAR(t), HOUR(t),
           MINUTE(t));
}
