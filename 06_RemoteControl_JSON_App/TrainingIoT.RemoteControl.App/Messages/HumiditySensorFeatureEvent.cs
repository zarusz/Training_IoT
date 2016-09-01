namespace TrainingIoT.RemoteControl.App.Messages
{
    public class HumiditySensorFeatureEvent : SensorFeatureEvent
    {
        public float Humidity { get; set; }
    }
}