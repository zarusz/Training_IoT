#include "JsonSerializationProvider.h"

void JsonSerializationProvider::ResetBuffer()
{
  jsonBuffer = StaticJsonBuffer<JSON_BUFFER_SIZE>();
}

JsonObject& JsonSerializationProvider::CreateMessage()
{
  ResetBuffer();
  return CreateObject();
}

JsonObject& JsonSerializationProvider::CreateObject()
{
  return jsonBuffer.createObject();
}

JsonObject& JsonSerializationProvider::Deserialize(String& payload)
{
  ResetBuffer();
  return jsonBuffer.parseObject(payload.c_str());
}

String JsonSerializationProvider::Serialize(JsonObject& m)
{
  char buffer[JSON_BUFFER_SIZE];
  m.printTo(buffer, sizeof(buffer));
  return String(buffer);
}
