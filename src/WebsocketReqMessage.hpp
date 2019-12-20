#pragma once


#include <iostream>

#include "utils/Base64.hpp"
#include "rapidjson/document.h"

class WebsocketReqMessage {
public:
    WebsocketReqMessage(std::string const& message);
    ~WebsocketReqMessage();
    std::string type;
    int id;
    char* decodedData;
};

WebsocketReqMessage::WebsocketReqMessage(std::string const& message){
    rapidjson::Document requestJSON;
    requestJSON.Parse(message.c_str());

    assert(requestJSON.IsObject());

    type = requestJSON["type"].GetString();
    id = requestJSON["id"].GetInt();
    rapidjson::Value& data = requestJSON["data"];
    if (type == "bin_to_json") {
        // in case base64 encoded binary - decode
        decodedData = new char[base64::decoded_size(data.GetStringLength())];
        base64::decode(decodedData, data.GetString(), data.GetStringLength());
    } else {
        // if JSON - just memcpy
        decodedData = new char[data.GetStringLength() + 1];
        decodedData[data.GetStringLength()] = 0;
        memcpy(decodedData, data.GetString(), data.GetStringLength());
    }
}

WebsocketReqMessage::~WebsocketReqMessage(){
    delete[] decodedData;
}