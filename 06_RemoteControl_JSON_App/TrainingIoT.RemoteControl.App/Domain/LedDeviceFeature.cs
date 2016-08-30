namespace TrainingIoT.RemoteControl.App.Domain
{
    public class LedDeviceFeature : SwitchDeviceFeature
    {
        public LedDeviceFeature(Device device, FeatureType type, int port) 
            : base(device, type, port)
        {
        }
    }
}