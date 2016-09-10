#include "FeatureController.h"

FeatureController::FeatureController(int port, const char* type, DeviceContext* context)
{
    this->port = port;
    this->type = type;
    this->context = context;
}

FeatureController::~FeatureController()
{
}

void FeatureController::PopulateDescription(JsonObject& featureDescription)
{
  featureDescription["type"] = type;
  featureDescription["port"] = port;
}

bool FeatureController::CanHandle(JsonObject& command)
{
  const char* commandType = command["type"].asString();
  const int commandPort = command["port"].as<int>();
  // the FeatureController can handle the command if port and feature type matches
  return port == commandPort && strcmp(type, commandType) == 0;
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
