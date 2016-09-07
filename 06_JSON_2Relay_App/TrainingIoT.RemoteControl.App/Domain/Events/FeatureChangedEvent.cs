namespace TrainingIoT.RemoteControl.App.Domain.Events
{
    public class FeatureChangedEvent
    {
        public DeviceFeature Feature { get; protected set; }

        public FeatureChangedEvent(DeviceFeature feature)
        {
            Feature = feature;
        }

    }
}