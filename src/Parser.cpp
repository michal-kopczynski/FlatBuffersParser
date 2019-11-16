#include "Parser.hpp"
#include <iostream>

Parser::Parser()
{
    flatbuffers::IDLOptions opts;

    opts.strict_json = true;
    opts.output_default_scalars_in_json = true;
    parser = std::make_unique<flatbuffers::Parser>(opts);
}

void Parser::LoadFile(const char* filename){
    std::ifstream fi(filename);
    bool ok;
    if (fi.is_open()) {
        std::string schemafile;
        ok = flatbuffers::LoadFile(filename, false, &schemafile);
        if (!ok) {
            printf("couldn't load files!\n");
            return;
        }
        std::string file(filename);
        const char *include_directories[] = { "", nullptr };
        ok = parser->Parse(schemafile.c_str(), include_directories);
        assert(ok);
    }
    else
        std::cout << "file not found" << std::endl;
}

std::size_t Parser::ParseBuffer(const char * reqBuffer, char * respBuffer)
{
    std::string jsongen;
    if (!GenerateText(*parser, reqBuffer, &jsongen)) {
        std::cout <<"Couldn't serialize parsed data to JSON!" << std::endl;
        return 0;
    }
    jsongen.copy(respBuffer, jsongen.length());
    return jsongen.length();
}