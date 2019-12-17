#include "HttpHandler.hpp"

#include <iostream>

#include "Parser.hpp"

HttpHandler::HttpHandler(Parser const& parser) :
parser(parser)
{
}

std::tuple<std::string, std::string> HttpHandler::handleBinToJsonRequest(std::string const& reqBuffer) const
{
    return { parser.parseBinToJson(reqBuffer.c_str()), "application/json"};
}

std::tuple<std::string, std::string> HttpHandler::handleJsonToBinRequest(std::string const& reqBuffer) const
{
    return { parser.parseJsonToBin(reqBuffer.c_str()), "application/octet-stream"};
}

