#pragma once

#define FLATBUFFERSPARSER_VERSION_MAJOR 1
#define FLATBUFFERSPARSER_VERSION_MINOR 0
#define FLATBUFFERSPARSER_VERSION_PATCH 0

#define AUX_STR_EXP(__A)  #__A
#define AUX_STR(__A)      AUX_STR_EXP(__A)

#define FLATBUFFERSPARSER_VERSION AUX_STR(FLATBUFFERSPARSER_VERSION_MAJOR) "." AUX_STR(FLATBUFFERSPARSER_VERSION_MINOR) "." AUX_STR(FLATBUFFERSPARSER_VERSION_PATCH)