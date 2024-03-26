#ifndef MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H
#define MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H

#include <logger.h>
#include <array>
#include <unordered_map>
#include <list>
#include <fstream>

class client_logger_builder;

class client_logger final:
    public logger
{
private:


    static std::unordered_map<std::string, std::pair<size_t, std::ofstream>> _global_streams;

    friend client_logger_builder;

    class refcounted_stream final
    {
        std::pair<std::string, std::ofstream*> _stream;

    public:

        explicit refcounted_stream(std::string& path);

        refcounted_stream(const refcounted_stream& oth);

        refcounted_stream& operator=(const refcounted_stream& oth);

        refcounted_stream(refcounted_stream&& oth) noexcept;

        refcounted_stream& operator=(refcounted_stream&& oth) noexcept;

        ~refcounted_stream();
    };

    std::unordered_map<logger::severity ,std::pair<std::list<refcounted_stream>, bool>> _output_streams;

    std::string _format;

private:

    client_logger(std::unordered_map<logger::severity ,std::pair<std::list<refcounted_stream>, bool>>& streams, std::string& format);

    std::string make_format(const std::string& message);

public:

    client_logger(
        client_logger const &other);

    client_logger &operator=(
        client_logger const &other);

    client_logger(
        client_logger &&other) noexcept;

    client_logger &operator=(
        client_logger &&other) noexcept;

    ~client_logger() noexcept final;

public:

    [[nodiscard]] logger const *log(
        const std::string &message,
        logger::severity severity) const noexcept override;

};

#endif //MATH_PRACTICE_AND_OPERATING_SYSTEMS_CLIENT_LOGGER_H