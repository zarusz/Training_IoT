using System;

namespace TrainingIoT.RemoteControl.App.Models
{
    public class HumiditySensorFeatureModel : FeatureModel
    {
        public float Humidity { get; set; }
        public DateTime Updated { get; set; }
    }
}