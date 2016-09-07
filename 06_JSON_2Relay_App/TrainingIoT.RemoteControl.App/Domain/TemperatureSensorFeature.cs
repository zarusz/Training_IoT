using System;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class TemperatureSensorFeature : DeviceFeature
    {
        public float Temperature { get; set; }
        public DateTime Updated { get; set; }

        public TemperatureSensorFeature(Device device, FeatureType type, int port) 
            : base(device, type, port)
        {
        }

        public void Measured(float temperature)
        {
            Temperature = temperature;
            Updated = DateTime.Now;            
        }
    }
}