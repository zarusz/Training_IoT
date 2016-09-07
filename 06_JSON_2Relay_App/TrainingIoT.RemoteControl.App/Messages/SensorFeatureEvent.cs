namespace TrainingIoT.RemoteControl.App.Messages
{
    public abstract class SensorFeatureEvent
    {
        public string DeviceId { get; set; }
        public string Type { get; set; }
        public int Port { get; set; }
    }
}