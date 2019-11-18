#pragma once

#include <iostream>

class Arguments {
public:
    Arguments() = default;
    void parse(int argc, char ** argv);

    int port;
    std::string schemaFile;
};
