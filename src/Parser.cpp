#include "Parser.hpp"
#include <iostream>

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

void Parser::loadFile(const std::string filename){
    std::ifstream fi(filename);
    bool ok;
    if (fi.is_open()) {
        std::string schemafile;
        ok = flatbuffers::LoadFile(filename.c_str(), false, &schemafile);
        if (!ok) {
            throw "Couldn't load file!";
        }
        std::string file(filename);
        const char *include_directories[] = { "", nullptr };
        if (!parser->Parse(schemafile.c_str(), include_directories)){
            throw "Error parsing file!";   
        }
    }
    else{
        throw "File not found!";
    }
}

std::string Parser::parseBuffer(const void* reqBuffer) const
{
    std::string response;
    if (!flatbuffers::GenerateText(*parser, reqBuffer, &response)) {
        std::cout <<"Couldn't serialize parsed data to JSON!" << std::endl;
    }
    return response;
}

std::string Parser::parseBuffer(std::string const& reqBuffer) const
{
    std::string response;
    if (!flatbuffers::GenerateText(*parser, reqBuffer.c_str(), &response)) {
        std::cout <<"Couldn't serialize parsed data to JSON!" << std::endl;
    }
    return response;
}