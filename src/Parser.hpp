#ifndef FLATBUFFERSPARSER_PARSER_HPP
#define FLATBUFFERSPARSER_PARSER_HPP

#include <cstddef>
#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

class Parser {
public:
    Parser();
    void LoadFile(const char* filename);
    std::size_t ParseBuffer(const char * reqBuffer, char * respBuffer);

private:
    std::unique_ptr <flatbuffers::Parser> parser;
};


#endif //FLATBUFFERSPARSER_PARSER_HPP