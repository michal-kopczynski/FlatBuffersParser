#include "Arguments.hpp"

#include <iostream>
#include "cxxopts.hpp"

void Arguments::parse(int argc, char ** argv){
    cxxopts::Options options("FlatBuffersParser", "FlatBuffers Parser is socket based tool for parsing binary FlatBuffers data to JSON format.");

    options.add_options()
        ("p,port", "Port to listen", cxxopts::value<int>())
        ("f,file", "Schema files", cxxopts::value<std::string>())
        ;

    auto result = options.parse(argc, argv);

    if (result.count("file")) {
        schemaFile = result["file"].as<std::string>();
    }
    else {
        throw SchemaFileNotSpecifiedException();
    }

    if (result.count("port")) {
        port = result["port"].as<int>();
    }
    else {
        throw PortNotSpecifiedException();
    }
}
