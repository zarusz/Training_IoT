//
//
//

#include "MainApp.h"
#include <stdio.h>

#include "Utils/TimeUtil.h"
#include "Feature/FeatureController.h"
#include "Feature/SwitchFeatureController.h"
//#include "FeatureControllers/TempFeatureController.h"
//#include "FeatureControllers/IRTransceiverFeatureController.h"
//#include "FeatureControllers/IRReceiverFeatureController.h"

// update with a unique id
#define DEVICE_UNIQUE_ID	"my_device_id"

// update with you network SSID and password
#define NETWORK_NAME			"IoT_Network"
#define NETWORK_PASSWORD	"IoT_Password"

//#define TOPIC_DEVICE_EVENTS "device/events"
//#define TOPIC_DEVICE_DESCRIPTION "device/description"

// update with the host for the 06_RemoteControl_App ASP.NET Web App
#define SERVER_HOST				"http://iot-remotecontrol-2.azurewebsites.net/api/device/"

#define TOPIC_REGISTER		"register"

MainApp::MainApp()
	: //pubSubClient(espClient),
		_deviceConfig(DEVICE_UNIQUE_ID, NETWORK_NAME, NETWORK_PASSWORD),
		_serializationProvider(),
		_messageBus(SERVER_HOST, &_serializationProvider, this)
{
	// sub to topic of the device's unique id
	_messageBus.Subscribe(_deviceConfig.uniqueId);

	// define all the features
	_features.push_back(new SwitchFeatureController(4, this, 4, false));
	_features.push_back(new SwitchFeatureController(5, this, 5, false));

/*
	features.push_back(new SwitchFeatureController(10, this, 20, false));
	features.push_back(new SwitchFeatureController(11, this, 21, false));
	features.push_back(new SwitchFeatureController(12, this, 22, false));
	features.push_back(new SwitchFeatureController(13, this, 23, false));
	features.push_back(new SwitchFeatureController(14, this, 24, false));
	features.push_back(new SwitchFeatureController(15, this, 25, false));
	features.push_back(new SwitchFeatureController(16, this, 26, false));
	features.push_back(new SwitchFeatureController(17, this, 27, false));

	features.push_back(new TempFeatureController(30, 31, this, 2));
	features.push_back(new IRReceiverFeatureController(41, this, 4));
	features.push_back(new IRTransceiverFeatureController(40, this, 16));
	features.push_back(new IRTransceiverFeatureController(50, this, 5));
*/

	//deviceInTopic = String("device/") + deviceConfig.uniqueId;
	//pubSubClient.setServer(deviceConfig.mqttBroker, 1883);
	//pubSubClient.setCallback(callback);
}

MainApp::~MainApp()
{
	// destroy all the features
	for (auto featureIt = _features.begin(); featureIt != _features.end(); ++featureIt)
		delete *featureIt;
}

void MainApp::Init()
{
	// Initialize the BUILTIN_LED pin as an output
	pinMode(BUILTIN_LED, OUTPUT);
	Serial.begin(115200);

	SetupWifi();
	OnStart();
}

void MainApp::Loop()
{
/*
	if (!pubSubClient.connected()) {
		ReconnectPubSub();
	}
	pubSubClient.loop();
*/
	_messageBus.Loop();
	OnLoop();
}

void MainApp::SetupWifi()
{
	Serial.printf("\nConnecting to %s\n", _deviceConfig.networkName);

  // Connect to a WiFi network
  WiFi.begin(_deviceConfig.networkName, _deviceConfig.networkPassword);
  // Wait until the connection is established
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected\n");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void MainApp::Handle(const char* topic, JsonObject& message)
{
	// if topic is same as device id
	if (strcmp(_deviceConfig.uniqueId, topic) == 0)
	{
		OnCommand(message);
	}
}

void MainApp::OnStart() {
	Serial.println("Starting...");

	SendDeviceDescription();

	/*
	Serial.println("Sending DeviceConnectedEvent");
	// Once connected, publish an announcement...
	DeviceEvents deviceEvents = DeviceEvents_init_zero;
	deviceEvents.has_deviceConnectedEvent = true;
	strcpy(deviceEvents.deviceConnectedEvent.device_id, deviceConfig.uniqueId);
	PublishMessage(TOPIC_DEVICE_EVENTS, DeviceEvents_fields, &deviceEvents);
	*/

	/*
	Serial.println("Sending DeviceDescription");
	deviceDescription = (DeviceDescription) DeviceDescription_init_zero;
	strcpy(deviceDescription.device_id, deviceConfig.uniqueId);
	deviceDescription.ports[0] = (DevicePort) DevicePort_init_default;
	deviceDescription.ports[0].port = 1;
	deviceDescription.ports[0].feature = DevicePortFeature::DevicePortFeature_SWITCH;
	deviceDescription.ports[1] = (DevicePort) DevicePort_init_default;
	deviceDescription.ports[1].port = 2;
	deviceDescription.ports[1].feature = DevicePortFeature::DevicePortFeature_SWITCH;
	PublishMessage(TOPIC_DEVICE_DESCRIPTION, DeviceDescription_fields, &deviceDescription);
	*/

	Serial.println("Started.");
}

void MainApp::OnStop() {
	Serial.println("Stopping...");

	/*
	Serial.println("Sending DeviceDisconnectedEvent");
	// Once connected, publish an announcement...
	DeviceEvents deviceEvents = DeviceEvents_init_zero;
	deviceEvents.has_deviceDisconnectedEvent = true;
	strcpy(deviceEvents.deviceDisconnectedEvent.device_id, deviceConfig.uniqueId);
	PublishMessage(TOPIC_DEVICE_EVENTS, DeviceEvents_fields, &deviceEvents);
	*/

	Serial.println("Stopped.");
}

void MainApp::OnLoop()
{
	if (TimeUtil::IntervalPassed(lastMsg, 10000))
	{
		++value;
		Serial.printf("Publish DeviceHearbeatEvent %d.\n", value);

		/*
		DeviceEvents deviceEvents = DeviceEvents_init_zero;
		deviceEvents.has_deviceHearbeatEvent = true;
		strcpy(deviceEvents.deviceHearbeatEvent.device_id, deviceConfig.uniqueId);
		deviceEvents.deviceHearbeatEvent.sequence_id = value;
		PublishMessage(TOPIC_DEVICE_EVENTS, DeviceEvents_fields, &deviceEvents);
		*/
	}

	// run loop on each feature instance
	for (auto featureIt = _features.begin(); featureIt != _features.end(); ++featureIt)
		(*featureIt)->Loop();
}

void MainApp::SendDeviceDescription()
{
		Serial.println("Sending DeviceDescription...");

		JsonObject& descriptionEvent = _serializationProvider.CreateMessage();
		descriptionEvent["deviceId"] = _deviceConfig.uniqueId;
		JsonArray& featureDescriptions = descriptionEvent.createNestedArray("features");

		for(auto featureIt = _features.begin(); featureIt != _features.end(); ++featureIt)
		{
			JsonObject& featureDescription = _serializationProvider.CreateObject();
			(*featureIt)->PopulateDescription(featureDescription);
			featureDescriptions.add(featureDescription);
		}

		_messageBus.Publish(TOPIC_REGISTER, descriptionEvent);
}

void MainApp::OnCommand(JsonObject& command)
{
	Serial.println("HandleCommand (start)");

	for(auto it = _features.begin(); it != _features.end(); ++it)
		(*it)->TryHandle(command);

	Serial.println("HandleCommand (finish)");
}


/*
void MainApp::ReconnectPubSub()
{
	// Loop until we're reconnected
	while (!pubSubClient.connected())
	{
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (pubSubClient.connect(deviceConfig.uniqueId))
		{
			Serial.println("Connected to MQTT broker.");
			// ... and resubscribe
			pubSubClient.subscribe(deviceInTopic.c_str());
			OnStart();
		}
		else
		{
			Serial.print("failed, rc=");
			Serial.print(pubSubClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void MainApp::Callback(char* topic, byte* payload, unsigned int length)
{
	if (deviceInTopic == topic) {
		// Allocate space for the decoded message.
		DeviceMessage message = DeviceMessage_init_zero;
		bool status = DecodeMessage(payload, length, DeviceMessage_fields, &message);
		if (status)
		{
			HandleDeviceMessage(message);
		}
		return;
	}

	DebugRetrievedMessage(topic, payload, length);
}

bool MainApp::DecodeMessage(byte* payload, unsigned int length, const pb_field_t* msg_fields, void* msg) const
{
	// Create a stream that reads from the buffer.
	pb_istream_t stream = pb_istream_from_buffer(payload, length);
	// Now we are ready to decode the message.
	bool status = pb_decode(&stream, msg_fields, msg);

	// Check for errors...
	if (!status)
	{
			Serial.print("Decoding failed:");
			Serial.println(PB_GET_ERROR(&stream));
	}
	return status;
}

bool MainApp::EncodeMessage(byte* payload, unsigned int maxLength, unsigned int& length, const pb_field_t* msg_fields, const void* msg) const
{
	// Create a stream that will write to our buffer.
	pb_ostream_t stream = pb_ostream_from_buffer(payload, maxLength);
	// Now we are ready to encode the message!
  bool status = pb_encode(&stream, msg_fields, msg);
  length = stream.bytes_written;

	// Then just check for any errors..
	if (!status)
	{
			Serial.print("Encoding failed: ");
			Serial.println(PB_GET_ERROR(&stream));
	}

	return status;
}

bool MainApp::PublishMessage(const char* topic, const pb_field_t* msg_fields, const void* msg)
{
	byte buffer[512];
	unsigned int length;

	if (!EncodeMessage(buffer, sizeof(buffer), length, msg_fields, msg))
	{
			return false;
	}

	pubSubClient.publish(topic, buffer, length);
	return true;
}

void MainApp::DebugRetrievedMessage(const char* topic, byte* payload, unsigned int length)
{
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++)
	{
		Serial.print((char)payload[i]);
	}
	Serial.println();

	// Switch on the LED if an 1 was received as first character
	if ((char)payload[0] == '1')
	{
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
										  // but actually the LED is on; this is because
										  // it is acive low on the ESP-01)
	}
	else
	{
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
	}
}
*/
