using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.Extension.Json.JsonConverters;

namespace TrainingIoT.RemoteControl.App.Messages
{
    [JsonDiscriminatorField("type")]
    [JsonSubclass(typeof(TemperatureSensorFeatureEvent), "temperatureSensor")]
    [JsonSubclass(typeof(HumiditySensorFeatureEvent), "humiditySensor")]
    [JsonSubclass(typeof(MotionSensorFeatureEvent), "motionSensor")]
    public abstract class SensorFeatureEvent
    {
        public string DeviceId { get; set; }
        public FeatureType Type { get; set; }
        public int Port { get; set; }
    }
}