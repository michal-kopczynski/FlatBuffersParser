#pragma once

#include "utils/Base64.hpp"
#include "rapidjson/document.h"

class WebsocketReqMessage {
public:
    WebsocketReqMessage(const void * message);
    WebsocketReqMessage(std::string const& message);
    ~WebsocketReqMessage();
    std::string type;
    int id;
    char* decodedData;
};

WebsocketReqMessage::WebsocketReqMessage(const void * message){
    rapidjson::Document requestJSON;
    requestJSON.Parse(static_cast<const char*>(message));

    assert(requestJSON.IsObject());

    type = requestJSON["type"].GetString();
    id = requestJSON["id"].GetInt();
    rapidjson::Value& data = requestJSON["data"];

    decodedData = new char[base64::decoded_size(data.GetStringLength())];
    base64::decode(decodedData, data.GetString(), data.GetStringLength());
}

WebsocketReqMessage::WebsocketReqMessage(std::string const& message){
    rapidjson::Document requestJSON;
    requestJSON.Parse(message.c_str());

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