namespace TrainingIoT.RemoteControl.App.Domain.Events
{
    public class DeviceFeatureChangedEvent
    {
        public DeviceFeature Feature { get; protected set; }

        public DeviceFeatureChangedEvent(DeviceFeature feature)
        {
            Feature = feature;
        }

    }
}