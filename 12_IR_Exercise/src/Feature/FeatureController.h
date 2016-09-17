#ifndef _FeatureController_h
#define _FeatureController_h

#include <ArduinoJson.h>
#include "../DeviceContext.h"

class FeatureController
{
protected:
  int _port;
  const char* _type;
  DeviceContext* _context;

public:
  FeatureController(int port, const char* type, DeviceContext* context);
  virtual ~FeatureController();

  // Fills the feature description for the discovery message
  virtual void PopulateDescriptions(JsonArray& featureDescriptions);

  // The feature can do some processing if needed.
  virtual void Loop();
  // Attempts to match the command to this feature and handle.
  virtual bool TryHandle(JsonObject& command);
  // Attempt to handle the incomming message (on the specified topic).
  virtual bool TryHandle(JsonObject& message, const char* topic);

protected:
  virtual void PopulateDescription(JsonArray& featureDescriptions, const char* type);
  // Checks if the feature is able to handle the command (port/type match).
  virtual bool CanHandle(JsonObject& command);
  // The feature has a message to handle.
  virtual void Handle(JsonObject& command);
};


#endif
