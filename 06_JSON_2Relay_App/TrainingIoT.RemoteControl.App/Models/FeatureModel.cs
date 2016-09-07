using TrainingIoT.RemoteControl.App.Domain;

namespace TrainingIoT.RemoteControl.App.Models
{
    public class FeatureModel
    {
        public string DeviceId { get; set; }
        public FeatureType Type { get; set; }
        public int Port { get; set; }
    }
}