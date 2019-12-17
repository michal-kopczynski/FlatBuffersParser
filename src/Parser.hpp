#pragma once

#include <cstddef>
#include <string>
#include <memory>

namespace flatbuffers{
    class Parser;
}

class ParsingFailedException : std::exception {};

class Parser {
public:
    Parser();
    ~Parser();

    void loadFile(const std::string& filename);
    std::string parseBinToJson(const void* bin) const;
    std::string parseJsonToBin(const void* json) const;

private:
    std::unique_ptr <flatbuffers::Parser> parser;
};
