#include "WebSocketHandler.hpp"

#include <iostream>

#include "Parser.hpp"
#include "WebsocketReqMessage.hpp"
#include "WebsocketRespMessage.hpp"

WebSocketHandler::WebSocketHandler(Parser const& parser) :
parser(parser)
{
}

std::string const WebSocketHandler::handleMessage(std::string const& message) {
    WebsocketReqMessage reqMessage(message);
    
    std::string data;
    if (reqMessage.type == "bin_to_json"){
        data = parser.parseBinToJson((void *)reqMessage.decodedData);
    }
    else if (reqMessage.type == "json_to_bin"){
        data = parser.parseJsonToBin(reqMessage.decodedData);
    }
    else
    {
         std::cout << "Not supported type!" << std::endl;
    }
    
    WebsocketRespMessage respMessage(reqMessage.type, reqMessage.id, data);
    return std::string(respMessage.getBuffer());
}