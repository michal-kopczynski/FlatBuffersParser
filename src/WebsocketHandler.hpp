#pragma once

#include <memory>
#include <thread>

class Parser;

class WebsocketHandler {
public:
    WebsocketHandler(std::shared_ptr<Parser> parser);

    std::shared_ptr<std::string const> handleMessage(std::shared_ptr<std::string const> const& ss);
    std::shared_ptr<std::string const> handleMessage(const void* data);
private:
    std::shared_ptr<Parser> parser;
};

