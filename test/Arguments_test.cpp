#include "gtest/gtest.h"

#include <unistd.h>
#include "Arguments.hpp"

TEST(Arguments, parse_fileMissing_expectThrow)
{
    char *argv[] = {(char*)"PROGRAM_NAME", (char*)"--port=12345"};

    Arguments arguments;
    EXPECT_THROW(arguments.parse(2, argv), SchemaFileNotSpecifiedException);
}

TEST(Arguments, parse_portMissing_expectThrow)
{
    char *argv[] = {(char*)"PROGRAM_NAME", (char*)"--file=FILE_NAME"};

    Arguments arguments;
    EXPECT_THROW(arguments.parse(2, argv), PortNotSpecifiedException);
}

TEST(Arguments, parse_shortArguments_successful)
{
    char *argv[] = {(char*)"PROGRAM_NAME", (char*)"-f", (char*)"FILE_NAME", (char*)"-p", (char*)"12345"};

    Arguments arguments;
    EXPECT_NO_THROW(arguments.parse(5, argv));

    ASSERT_EQ("FILE_NAME", arguments.schemaFile);
    ASSERT_EQ(12345, arguments.port);
}

TEST(Arguments, parse_longArguments_successful)
{
    char *argv[] = {(char*)"PROGRAM_NAME", (char*)"--file=FILE_NAME", (char*)"--port=12345"};

    Arguments arguments;
    EXPECT_NO_THROW(arguments.parse(3, argv));

    ASSERT_EQ("FILE_NAME", arguments.schemaFile);
    ASSERT_EQ(12345, arguments.port);
}
