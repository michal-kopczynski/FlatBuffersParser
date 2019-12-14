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
    std::string parseBuffer(const void* reqBuffer) const;
    std::string parseBuffer(std::string const& reqBuffer) const;

private:
    std::unique_ptr <flatbuffers::Parser> parser;
};
