using System;

namespace TrainingIoT.RemoteControl.App.Models
{
    public class TemperatureSensorFeatureModel : FeatureModel
    {
        public float Temperature { get; set; }
        public DateTime Updated { get; set; }
    }
}