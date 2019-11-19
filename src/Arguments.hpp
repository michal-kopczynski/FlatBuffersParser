#pragma once

#include <iostream>
#include <vector>

class SchemaFileNotSpecifiedException : std::exception {};
class PortNotSpecifiedException : std::exception {};

class Arguments {
public:
    Arguments() = default;
    void parse(int argc, char ** argv);

    int port;
    std::vector<std::string> schemaFiles;
};
