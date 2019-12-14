#pragma once

#include <memory>
#include <thread>

class Parser;

class WebSocketHandler {
public:
    WebSocketHandler(Parser const& parser);

    std::string const handleMessage(std::string const& message);

private:
    Parser const& parser;
};

