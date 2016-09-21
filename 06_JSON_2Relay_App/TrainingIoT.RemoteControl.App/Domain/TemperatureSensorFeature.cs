using System;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class TemperatureSensorFeature : DeviceFeature
    {
        public float Temperature { get; set; }
        public DateTime Updated { get; set; }

        public TemperatureSensorFeature(Device device, int port) 
            : base(device, FeatureType.TemperatureSensor, port)
        {
        }

        public void Measured(float temperature)
        {
            Temperature = temperature;
            Updated = DateTime.Now;            
        }
    }
}