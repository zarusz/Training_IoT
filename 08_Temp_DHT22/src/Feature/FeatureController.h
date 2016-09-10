#ifndef _FeatureController_h
#define _FeatureController_h

#include <ArduinoJson.h>
#include "../DeviceContext.h"

class FeatureController
{
protected:
  int port;
  const char* type;
  DeviceContext* context;

public:
  FeatureController(int port, const char* type, DeviceContext* context);
  virtual ~FeatureController();

  // Fills the feature description for the discovery message
  virtual void PopulateDescription(JsonObject& featureDescription);
  // The feature can do some processing if needed.
  virtual void Loop() = 0;
  // Attempts to match the command to this feature and handle.
  virtual bool TryHandle(JsonObject& command);

protected:
  // Checks if the feature is able to handle the command (port/type match).
  virtual bool CanHandle(JsonObject& command);
  // The feature has a message to handle.
  virtual void Handle(JsonObject& command) = 0;
};


#endif
