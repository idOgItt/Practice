#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_LOGGER_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_LOGGER_H

#include <iostream>

class logger
{

public:

    enum class severity
    {
        trace,
        debug,
        information,
        warning,
        error,
        critical
    };

public:

    virtual ~logger() noexcept = default;

public:

    virtual const logger& log(
        std::string const &message,
        logger::severity severity) const & = 0;

public:

    const logger& trace(
        std::string const &message) const &;

    const logger& debug(
        std::string const &message) const &;

    const logger& information(
        std::string const &message) const &;

    const logger& warning(
        std::string const &message) const &;

    const logger& error(
        std::string const &message) const &;

    const logger& critical(
        std::string const &message) const &;

protected:

    static std::string severity_to_string(
        logger::severity severity);

    static std::string current_datetime_to_string();

    static std::string current_date_to_string();

    static std::string current_time_to_string();

};


#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_LOGGER_H