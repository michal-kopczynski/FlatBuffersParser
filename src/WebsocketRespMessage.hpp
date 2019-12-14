#pragma once

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
    rapidjson::Document responseJSON;
    responseJSON.SetObject();
    rapidjson::Value typeValue;
    typeValue.SetString(type.c_str(), responseJSON.GetAllocator());
    responseJSON.AddMember("type", typeValue, responseJSON.GetAllocator());

    rapidjson::Value idValue(id);
    responseJSON.AddMember("id", idValue, responseJSON.GetAllocator());
    
    rapidjson::Value dataValue(rapidjson::GenericStringRef(data.c_str()));
    responseJSON.AddMember("data", dataValue, responseJSON.GetAllocator());

    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    responseJSON.Accept(writer);
}

const char* WebsocketRespMessage::getBuffer(){
    return buffer.GetString();
}


