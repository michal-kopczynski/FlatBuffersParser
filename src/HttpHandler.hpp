#pragma once

#include <memory>
#include <thread>
#include <string>
#include <tuple>

class Parser;

class HttpHandler {
public:
    HttpHandler(Parser const& parser);

    std::tuple<std::string, std::string> handleBinToJsonRequest(std::string const& reqBuffer) const;

private:
    Parser const& parser;
};

