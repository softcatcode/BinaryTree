#ifndef NULLPOINEREXCEPTION_H_INCLUDED
#define NULLPOINEREXCEPTION_H_INCLUDED

#include "exception.h"

class NullPointerException: TreeException
{
public:
    NullPointerException(
        const char* msg,
        const char *locName,
        const char *date,
        const char *time,
        unsigned line,
        const char *cause = ""
    ) noexcept:
        TreeException(msg, locName, time, date, line, cause) {};
};

#endif // NULLPOINEREXCEPTION_H_INCLUDED
