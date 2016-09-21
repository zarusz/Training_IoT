using System;

namespace TrainingIoT.RemoteControl.App.Models
{
    public class MotionSensorFeatureModel : FeatureModel
    {
        public bool Motion { get; set; }
        public DateTime Updated { get; set; }
    }
}