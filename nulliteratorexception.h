#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include "exception.h"

class NullIteratorException: public TreeException
{
public:
    NullIteratorException(
        const char* msg,
        const char *locName,
        const char *date,
        const char *time,
        unsigned line,
        const char *cause = ""
    ) noexcept:
        TreeException(msg, locName, time, date, line, cause) {};
};

#endif // NULLPOINTEREXCEPTION_H
