namespace TrainingIoT.RemoteControl.App.Domain
{
    public class LedFeature : SwitchFeature
    {
        public LedFeature(Device device, FeatureType type, int port) 
            : base(device, type, port)
        {
        }
    }
}