using System;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class HumiditySensorFeature : DeviceFeature
    {
        public float Humidity { get; set; }
        public DateTime Updated { get; set; }

        public HumiditySensorFeature(Device device, FeatureType type, int port) 
            : base(device, type, port)
        {
        }

        public void Measured(float humidity)
        {
            Humidity = humidity;
            Updated = DateTime.Now;
        }
    }
}