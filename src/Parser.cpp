#include "Parser.hpp"
#include <iostream>
#include <fstream>

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

Parser::Parser()
{
    flatbuffers::IDLOptions opts;

    opts.strict_json = true;
    opts.output_default_scalars_in_json = true;
    parser = std::make_unique<flatbuffers::Parser>(opts);
}

Parser::~Parser() = default;


std::string Parser::loadFile(const std::string& fileName) const {
    std::string schemaFile;
    std::ifstream fi(fileName);

    if (fi.is_open()) {
        if (!flatbuffers::LoadFile(fileName.c_str(), false, &schemaFile)) {
            throw "Couldn't load file!";
        }
    }
    else{
        throw "File not found!";
    }
    return schemaFile;
}

void Parser::parseFile(const std::string& schemaFile){
    const char *include_directories[] = { "", nullptr };
    if (!parser->Parse(schemaFile.c_str(), include_directories)){
        throw "Error parsing file!";   
    }
}

std::string Parser::parseBinToJson(const void* bin) const
{
    std::string response;
    if (!flatbuffers::GenerateText(*parser, bin, &response)) {
        std::cout <<"Couldn't serialize parsed data to JSON!" << std::endl;
        throw ParsingFailedException();
    }
    return response;
}

std::string Parser::parseJsonToBin(const void* json) const
{
    const char *include_directories[] = { "", nullptr };
    if (!parser->Parse(static_cast<const char*>(json), include_directories)){
        std::cout << "Error parsing JSON file!" << std::endl;  
        throw ParsingFailedException();
    }
    else{
        return std::string( reinterpret_cast<char *>(parser->builder_.GetBufferPointer()),
                            static_cast<size_t>(parser->builder_.GetSize()) );
    }
}
