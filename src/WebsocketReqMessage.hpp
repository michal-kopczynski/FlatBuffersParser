#pragma once

#include <boost/beast/core/detail/base64.hpp>
#include "rapidjson/document.h"

namespace base64 = boost::beast::detail::base64;

class WebsocketReqMessage {
public:
    WebsocketReqMessage(const void * message);
    ~WebsocketReqMessage();
    std::string type;
    int id;
    char* decodedData;
};

WebsocketReqMessage::WebsocketReqMessage(const void * message){
    rapidjson::Document requestJSON;
    // std::cout << (const char *)message << std::endl;
    // std::cout << "size: "<< strlen((const char *)message) << std::endl;
    requestJSON.Parse(static_cast<const char*>(message));

    assert(requestJSON.IsObject());

    type = requestJSON["type"].GetString();
    id = requestJSON["id"].GetInt();
    rapidjson::Value& data = requestJSON["data"];

    decodedData = new char[base64::decoded_size(data.GetStringLength())];
    base64::decode(decodedData, data.GetString(), data.GetStringLength());
}

WebsocketReqMessage::~WebsocketReqMessage(){
    delete[] decodedData;
}