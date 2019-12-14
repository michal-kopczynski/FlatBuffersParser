#pragma once
#include <string>
#include <functional>
#include <map>

#include <restinio/all.hpp>

class HttpRouter
{
public:
    HttpRouter() = default;
    ~HttpRouter() = default;

    void addHandler(const std::string path, std::function<std::string(std::string)> handler);
    restinio::request_handling_status_t handle(restinio::request_handle_t & req);

private:
    std::map<const std::string, std::function<std::string(std::string)>> handlers;
};
