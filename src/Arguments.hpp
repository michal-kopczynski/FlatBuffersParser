#pragma once

#include <iostream>

class SchemaFileNotSpecifiedException : std::exception {};
class PortNotSpecifiedException : std::exception {};

class Arguments {
public:
    Arguments() = default;
    void parse(int argc, char ** argv);

    int port;
    std::string schemaFile;
};
