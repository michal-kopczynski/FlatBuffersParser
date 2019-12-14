#include "HttpHandler.hpp"

#include <iostream>

#include "Parser.hpp"

HttpHandler::HttpHandler(Parser const& parser) :
parser(parser)
{
}

std::string HttpHandler::handleBinToJsonRequest(std::string const& reqBuffer) const
{
    std::cout << "HttpHandler::handleBinToJsonRequest" << std::endl;
    return parser.parseBuffer(reqBuffer);
}
