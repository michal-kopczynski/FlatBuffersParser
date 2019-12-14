#pragma once

#include <memory>
#include <thread>
#include <string>

class Parser;

class HttpHandler {
public:
    HttpHandler(Parser const& parser);

    std::string handleBinToJsonRequest(std::string const& reqBuffer) const;

private:
    Parser const& parser;
};

