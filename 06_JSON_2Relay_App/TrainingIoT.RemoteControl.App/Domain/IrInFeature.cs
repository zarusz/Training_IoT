namespace TrainingIoT.RemoteControl.App.Domain
{
    public class IrInFeature : DeviceFeature
    {
        public IrInFeature(Device device, int port)
            : base(device, FeatureType.IrIn, port)
        {
        }

    }
}