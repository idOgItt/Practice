#include <not_implemented.h>
#include <string>

#include "../include/client_logger.h"

client_logger::client_logger(
    client_logger const &other)
{
    throw not_implemented("client_logger::client_logger(client_logger const &other)", "your code should be here...");
}

client_logger &client_logger::operator=(
    client_logger const &other)
{
    throw not_implemented("client_logger &client_logger::operator=(client_logger const &other)", "your code should be here...");
}

client_logger::client_logger(
    client_logger &&other) noexcept
{
    throw not_implemented("client_logger::client_logger(client_logger &&other) noexcept", "your code should be here...");
}

client_logger &client_logger::operator=(
    client_logger &&other) noexcept
{
    throw not_implemented("client_logger &client_logger::operator=(client_logger &&other) noexcept", "your code should be here...");
}

client_logger::~client_logger() noexcept
{
    throw not_implemented("client_logger::~client_logger() noexcept", "your code should be here...");
}

logger const *client_logger::log(
    const std::string &text,
    logger::severity severity) const noexcept
{
    throw not_implemented("logger const *client_logger::log(const std::string &text, logger::severity severity) const noexcept", "your code should be here...");
}

client_logger::client_logger(
        std::unordered_map<logger::severity ,std::pair<std::list<refcounted_stream>, bool>> &streams,
        std::string& format)
{

}

std::string client_logger::make_format(const std::string &message)
{
    return std::string();
}

client_logger::refcounted_stream::refcounted_stream(std::string &path) : _stream(std::make_pair(path, nullptr)) {}

client_logger::refcounted_stream::refcounted_stream(const client_logger::refcounted_stream &oth) : _stream(std::make_pair(oth._stream.first,
                                                                                                                          nullptr))
{
    auto it = _global_streams.find(oth._stream.first);

    if (it != _global_streams.end())
    {
        ++it->second.first;
        _stream.second = &it->second.second;
    } else
    {
        auto inserted = _global_streams.emplace(_stream.first, std::make_pair<size_t>(1, std::ofstream(oth._stream.first)));

        if (!inserted.second || !inserted.first->second.second.is_open())
        {
            if (inserted.second)
            {
                _global_streams.erase(inserted.first);
            }
            throw std::runtime_error("File " + oth._stream.first + " could not be opened");
        }

        _stream.second = &inserted.first->second.second;
    }
}

client_logger::refcounted_stream &
client_logger::refcounted_stream::operator=(const client_logger::refcounted_stream &oth)
{
    if (this == &oth)
        return *this;

    if (_stream.second != nullptr)
    {
        auto it = _global_streams.find(_stream.first);

        if (it != _global_streams.end())
        {
            --it->second.first;

            if (it->second.first == 0)
            {
                it->second.second.close();
                _global_streams.erase(it);
            }
        }
    }

    _stream.first = oth._stream.first;
    _stream.second = oth._stream.second;

    if (_stream.second != nullptr)
    {
        auto it = _global_streams.find(_stream.first);
        ++it->second.first;
    }

    return *this;
}

client_logger::refcounted_stream::refcounted_stream(client_logger::refcounted_stream &&oth) noexcept
{
    std::swap(_stream.first, oth._stream.first);
    _stream.second = std::exchange(oth._stream.second, nullptr);
}

client_logger::refcounted_stream &client_logger::refcounted_stream::operator=(client_logger::refcounted_stream &&oth) noexcept
{
    if (this == &oth)
        return *this;

    std::swap(_stream.first, oth._stream.first);
    std::swap(_stream.second, oth._stream.second);

    return *this;
}

client_logger::refcounted_stream::~refcounted_stream()
{
    if (_stream.second != NULL)
    {
        auto it = _global_streams.find(_stream.first);

        if (it != _global_streams.end())
        {
            --it->second.first;

            if (it->second.first == 0)
            {
                it->second.second.close();
                _global_streams.erase(it);
            }
        }
    }
}
