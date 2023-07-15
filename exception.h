#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <exception>
#include <stdio.h>

#define MAX_LOG_LEN
#define MSG_LEN 32
#define LOC_NAME_LEN 16
#define DATE_LABEL_LEN 16
#define TIME_LABEL_LEN 16
#define CAUSE_LABEL_LEN 64

class TreeException : public std::exception
{
protected:
	char errormsg[MAX_LOG_LEN + 1];
	char msg[MSG_LEN + 1];
	char locName[LOC_NAME_LEN + 1];
	char date[DATE_LABEL_LEN + 1];
	char time[TIME_LABEL_LEN + 1];
	char cause[CAUSE_LABEL_LEN + 1];
	unsigned line;

public:
    TreeException(
        const char* msg,
        const char *locName,
        const char *date,
        const char *time,
        unsigned line,
        const char *cause = ""
    ) noexcept;

	virtual ~TreeException() = default;

	virtual const char* what() noexcept
	{
        unsigned index = 0;
        index += snprintf(
            errormsg + index,
            MAX_LOG_LEN - index + 1,
            "%s\n",
            msg
        );
        index += snprintf(
            errormsg + index,
            MAX_LOG_LEN - index + 1,
            "occured in location: %s ",
            locName
        );
        index += snprintf(
            errormsg + index,
            MAX_LOG_LEN - index + 1,
            "on line: %d\n",
            line
        );
        index += snprintf(
            errormsg + index,
            MAX_LOG_LEN - index + 1,
            "date: %s at %s\n",
            date,
            time
        );
        index += snprintf(
            errormsg + index,
            MAX_LOG_LEN - index + 1,
            "feasible cause: %s\n",
            cause
        );
        return errormsg;
    }
};

#endif // EXCEPTION_H_INCLUDED
