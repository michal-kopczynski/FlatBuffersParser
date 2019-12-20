#pragma once

#include "utils/Base64.hpp"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

class WebsocketRespMessage {
public:
    WebsocketRespMessage(const std::string type, int id, std::string const& data);

    const char* getBuffer();
private:
    rapidjson::StringBuffer buffer;
};

WebsocketRespMessage::WebsocketRespMessage(const std::string type, int id, std::string const& data){
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    rapidjson::Document responseJSON;
    responseJSON.SetObject();
    rapidjson::Value typeValue;
    typeValue.SetString(type.c_str(), responseJSON.GetAllocator());
    responseJSON.AddMember("type", typeValue, responseJSON.GetAllocator());

    rapidjson::Value idValue(id);
    responseJSON.AddMember("id", idValue, responseJSON.GetAllocator());

    if (type == "bin_to_json") {
        // if response is JSON - just copy
        rapidjson::Value dataValue(rapidjson::GenericStringRef(data.c_str()));
        responseJSON.AddMember("data", dataValue, responseJSON.GetAllocator());
        responseJSON.Accept(writer);
    } else {
        // if response is binary - do base64 encode
        char encodedData[base64::encoded_size(data.size())];
        base64::encode(encodedData, data.c_str(), data.size());
        rapidjson::Value dataValue(rapidjson::GenericStringRef(encodedData, base64::encoded_size(data.size())));
        responseJSON.AddMember("data", dataValue, responseJSON.GetAllocator());
        responseJSON.Accept(writer);
    }
}

const char* WebsocketRespMessage::getBuffer(){
    return buffer.GetString();
}


