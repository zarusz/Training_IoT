#include "FeatureController.h"

FeatureController::FeatureController(int port, const char* type, DeviceContext* context)
{
    _port = port;
    _type = type;
    _context = context;
}

FeatureController::~FeatureController()
{
}

void FeatureController::PopulateDescriptions(JsonArray& featureDescriptions)
{
  PopulateDescription(featureDescriptions, _type);
}

void FeatureController::PopulateDescription(JsonArray& featureDescriptions, const char* type)
{
  JsonObject& featureDescription = _context->GetSerializationProvider().CreateObject();
  featureDescription["port"] = _port;
  featureDescription["type"] = type;
  featureDescriptions.add(featureDescription);
}

void FeatureController::Loop()
{
  // nothing to do - override in subclass
}

bool FeatureController::TryHandle(JsonObject& message, const char* topic)
{
  return false;
}

bool FeatureController::TryHandle(JsonObject& command)
{
  if (CanHandle(command))
  {
    Handle(command);
    return true;
  }
  return false;
}

bool FeatureController::CanHandle(JsonObject& command)
{
  const char* commandType = command["type"].asString();
  const int commandPort = command["port"].as<int>();
  // the FeatureController can handle the command if port and feature type matches
  return _port == commandPort && strcmp(_type, commandType) == 0;
}

void FeatureController::Handle(JsonObject& command)
{
  // nothing - need to override in subclass
}
