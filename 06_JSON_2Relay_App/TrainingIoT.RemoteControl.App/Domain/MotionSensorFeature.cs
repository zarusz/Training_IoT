using System;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class MotionSensorFeature : DeviceFeature
    {
        public bool Motion { get; set; }
        public DateTime Updated { get; set; }

        public MotionSensorFeature(Device device, FeatureType type, int port)
            : base(device, type, port)
        {
        }

        public void Measured(bool motion)
        {
            Motion = motion;
            Updated = DateTime.Now;
        }
    }
}