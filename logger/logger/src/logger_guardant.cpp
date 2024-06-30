#include "../include/logger_guardant.h"

const logger_guardant &logger_guardant::log_with_guard(
    std::string const &message,
    logger::severity severity) const &
{
    logger *got_logger = get_logger();
    if (got_logger != nullptr)
    {
        got_logger->log(message, severity);
    }

    return *this;
}

const logger_guardant & logger_guardant::trace_with_guard(
    std::string const &message) const &
{
    return log_with_guard(message, logger::severity::trace);
}

const logger_guardant &logger_guardant::debug_with_guard(
    std::string const &message) const &
{
    return log_with_guard(message, logger::severity::debug);
}

const logger_guardant &logger_guardant::information_with_guard(
    std::string const &message) const &
{
    return log_with_guard(message, logger::severity::information);
}

const logger_guardant &logger_guardant::warning_with_guard(
    std::string const &message) const &
{
    return log_with_guard(message, logger::severity::warning);
}

const logger_guardant &logger_guardant::error_with_guard(
    std::string const &message) const &
{
    return log_with_guard(message, logger::severity::error);
}

const logger_guardant &logger_guardant::critical_with_guard(
    std::string const &message) const &
{
    return log_with_guard(message, logger::severity::critical);
}