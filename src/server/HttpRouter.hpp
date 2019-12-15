#pragma once
#include "iostream"
#include <string>
#include <functional>
#include <map>

#include <restinio/all.hpp>

class PathAlreadyAddedException : std::exception {};

using handler_t = std::function<std::tuple<std::string, std::string>(std::string)>;

class HttpRouter
{
public:
    HttpRouter() = default;
    ~HttpRouter() = default;

    void addHandler(const std::string path, handler_t handler);
    restinio::request_handling_status_t handle(restinio::request_handle_t & req);

private:
    std::map<const std::string, handler_t> handlers;
};
