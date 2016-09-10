using TrainingIoT.RemoteControl.App.Domain;

namespace TrainingIoT.RemoteControl.App.Messages
{
    public abstract class SensorFeatureEvent
    {
        public string DeviceId { get; set; }
        public FeatureType Type { get; set; }
        public int Port { get; set; }
    }
}