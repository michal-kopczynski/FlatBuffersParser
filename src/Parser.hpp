#pragma once

#include <cstddef>
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

class Parser {
public:
    Parser();
    void loadFile(const std::string filename);
    std::size_t parseBuffer(const char * reqBuffer, char * respBuffer);

private:
    std::unique_ptr <flatbuffers::Parser> parser;
};
