#include <not_implemented.h>
#include <httplib.h>

#include "../include/server_logger.h"

server_logger::~server_logger() noexcept
{
    httplib::Params par;
    par.emplace("pid", std::to_string(server_logger::_getpid()));
    _client.Post("/destroy", par);
}

logger const *server_logger::log(
    const std::string &text,
    logger::severity severity) const noexcept
{
    httplib::Params par;
    par.emplace("pid", std::to_string(server_logger::_getpid()));
    par.emplace("sev", severity_to_string(severity));
    par.emplace("message", text);

    _client.Post("/log", par);
    return this;
}

server_logger::server_logger(const std::string& dest,
                             const std::unordered_map<logger::severity, std::pair<std::string, bool>> &streams)
                             : _client(dest)
{
    for (auto& pair : streams)
    {
        httplib::Params par;
        par.emplace("pid", std::to_string(server_logger::_getpid()));
        par.emplace("sev", severity_to_string(pair.first));
        par.emplace("path", pair.second.first);
        par.emplace("console", pair.second.second ? "1" : "0");
        _client.Post("/init", par);
    }
}

int server_logger::_getpid()
{
    return 1;
}
