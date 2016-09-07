using TrainingIoT.RemoteControl.App.Domain;

namespace TrainingIoT.RemoteControl.App.Messages
{
    public class FeatureDescriptionDto
    {
        public FeatureType Type { get; set; }
        public int Port { get; set; }
    }
}