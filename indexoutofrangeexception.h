#ifndef INDEXOUTOFRANGEEXCEPTION_H
#define INDEXOUTOFRANGEEXCEPTION_H

#include "exception.h"

class IndexOutOfRangeException: public TreeException
{
public:
    IndexOutOfRangeException(
        const char* msg,
        const char *locName,
        const char *date,
        const char *time,
        unsigned line,
        const char *cause = ""
    ) noexcept:
        TreeException(msg, locName, time, date, line, cause) {};
};

#endif // INDEXOUTOFRANGEEXCEPTION_H
