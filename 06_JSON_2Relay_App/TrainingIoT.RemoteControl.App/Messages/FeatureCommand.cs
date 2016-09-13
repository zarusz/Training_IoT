namespace TrainingIoT.RemoteControl.App.Messages
{
    public abstract class FeatureCommand : FeatureDescriptionDto
    {
        public string DeviceId { get; set; }
    }
}