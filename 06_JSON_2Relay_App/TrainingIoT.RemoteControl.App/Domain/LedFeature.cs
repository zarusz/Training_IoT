namespace TrainingIoT.RemoteControl.App.Domain
{
    public class LedFeature : SwitchFeature
    {
        public LedFeature(Device device, int port)
            : base(device, FeatureType.Switch, port)
        {
        }
    }
}