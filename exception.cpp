#include "exception.h"
#include <cstring>
#include <string>

TreeException::TreeException(
    const char* msg,
    const char *locName,
    const char *date,
    const char *time,
    unsigned line,
    const char *cause
) noexcept {
    strncpy(this->msg, msg, MSG_LEN);
    this->msg[MSG_LEN] = 0;

    strncpy(this->locName, locName, LOC_NAME_LEN);
    this->locName[LOC_NAME_LEN] = 0;

    strncpy(this->date, date, DATE_LABEL_LEN);
    this->date[DATE_LABEL_LEN] = 0;

    strncpy(this->time, time, TIME_LABEL_LEN);
    this->time[TIME_LABEL_LEN] = 0;

    this->line = line;

    strncpy(this->cause, cause, CAUSE_LABEL_LEN);
    this->cause[CAUSE_LABEL_LEN] = 0;
}
