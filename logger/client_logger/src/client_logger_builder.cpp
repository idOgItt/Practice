#include <filesystem>
#include <utility>
#include "../include/client_logger_builder.h"

using namespace nlohmann;

//client_logger_builder::client_logger_builder()
//{
//    throw not_implemented("client_logger_builder::client_logger_builder()", "your code should be here...");
//}
//
//client_logger_builder::client_logger_builder(
//    client_logger_builder const &other)
//{
//    throw not_implemented("client_logger_builder::client_logger_builder(client_logger_builder const &other)", "your code should be here...");
//}
//
//client_logger_builder &client_logger_builder::operator=(
//    client_logger_builder const &other)
//{
//    throw not_implemented("client_logger_builder &client_logger_builder::operator=(client_logger_builder const &other)", "your code should be here...");
//}
//
//client_logger_builder::client_logger_builder(
//    client_logger_builder &&other) noexcept
//{
//    throw not_implemented("client_logger_builder::client_logger_builder(client_logger_builder &&other) noexcept", "your code should be here...");
//}
//
//client_logger_builder &client_logger_builder::operator=(
//    client_logger_builder &&other) noexcept
//{
//    throw not_implemented("client_logger_builder &client_logger_builder::operator=(client_logger_builder &&other) noexcept", "your code should be here...");
//}
//
//client_logger_builder::~client_logger_builder() noexcept
//{
//    throw not_implemented("client_logger_builder::~client_logger_builder() noexcept", "your code should be here...");
//}

logger_builder *client_logger_builder::add_file_stream(
    std::string const &stream_file_path,
    logger::severity severity)
{
    auto it = _output_streams.find(severity);
    if (it == _output_streams.end())
    {
        auto inserted = _output_streams.emplace(severity, std::make_pair(std::forward_list<client_logger::refcounted_stream>(), false));
        it = inserted.first;
    }

    it->second.first.emplace_front(std::filesystem::weakly_canonical(stream_file_path).string());

    return this;
}

logger_builder *client_logger_builder::add_console_stream(
    logger::severity severity)
{
    auto it = _output_streams.find(severity);
    if (it == _output_streams.end())
    {
        auto inserted = _output_streams.emplace(severity, std::make_pair(std::forward_list<client_logger::refcounted_stream>(), true));
        it = inserted.first;
    }

    it->second.second = true;

    return this;
}

logger_builder* client_logger_builder::transform_with_configuration(
    std::string const &configuration_file_path,
    std::string const &configuration_path)
{
    std::ifstream file(configuration_file_path);

    if (!file.is_open())
        throw std::ios_base::failure("File " + configuration_file_path + " could not be opened");

    json data = json::parse(file);

    file.close();

    auto it = data.find(configuration_path);

    if (it == data.end() || !it->is_object())
        return this;

    parse_severity(logger::severity::trace, (*it)["trace"]);
    parse_severity(logger::severity::debug, (*it)["debug"]);
    parse_severity(logger::severity::information, (*it)["information"]);
    parse_severity(logger::severity::warning, (*it)["warning"]);
    parse_severity(logger::severity::error, (*it)["error"]);
    parse_severity(logger::severity::critical, (*it)["critical"]);

    auto format = it->find("format");

    if (format != it->end())
    {
        _format = format.value();
    }

    return this;
}

logger_builder *client_logger_builder::clear()
{
    _output_streams.clear();
    _format = "%m";

    return this;
}

logger *client_logger_builder::build() const
{
    return new client_logger(_output_streams, _format);
}

logger_builder *client_logger_builder::set_format(const std::string &format)
{
    _format = format;
    return this;
}

void client_logger_builder::parse_severity(logger::severity sev, nlohmann::json& j)
{
    if (j.empty())
        return;

    auto it = _output_streams.find(sev);

    auto data_it = j.find("paths");
    if (data_it != j.end())
    {
        json data = j["paths"];

        for (const std::string &path: data)
        {
            if (it == _output_streams.end())
            {
                it = _output_streams.emplace(sev, std::make_pair(std::forward_list<client_logger::refcounted_stream>(),
                                                                 false)).first;
            }

            it->second.first.emplace_front(std::filesystem::weakly_canonical(path).string());
        }
    }

    auto console = j.find("console");

    if (console != j.end())
    {
        if (it == _output_streams.end())
        {
            it = _output_streams.emplace(sev, std::make_pair(std::forward_list<client_logger::refcounted_stream>(), false)).first;
        }
        it->second.second = console->get<bool>();
    }
}
