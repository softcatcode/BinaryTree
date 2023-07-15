#ifndef ILLEGALFUNCUSEEXCEPTION_H
#define ILLEGALFUNCUSEEXCEPTION_H

#include "exception.h"

class IllegalFuncUseException: public TreeException
{
public:
    IllegalFuncUseException(
        const char* msg,
        const char *locName,
        const char *date,
        const char *time,
        unsigned line,
        const char *cause = ""
    ) noexcept:
        TreeException(msg, locName, time, date, line, cause) {};
};

#endif // ILLEGALFUNCUSEEXCEPTION_H
