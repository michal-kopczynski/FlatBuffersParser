#pragma once

#include <cstddef>
#include <string>
#include <memory>

namespace flatbuffers{
    class Parser;
}

class Parser {
public:
    Parser();
    ~Parser();
    void loadFile(const std::string filename);
    std::size_t parseBuffer(const char * reqBuffer, char * respBuffer);
    std::shared_ptr<std::string> parseBuffer(const void* reqBuffer);

private:
    std::unique_ptr <flatbuffers::Parser> parser;
};
