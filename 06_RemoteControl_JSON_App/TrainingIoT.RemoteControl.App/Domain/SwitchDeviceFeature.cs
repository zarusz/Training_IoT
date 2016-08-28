using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class SwitchDeviceFeature : DeviceFeature
    {
        public bool IsOn { get; protected set; }

        public SwitchDeviceFeature(Device device, FeatureType type, int port)
            : base(device, type, port)
        {
            Off();
        }

        public void Off()
        {
            IsOn = false;
            NotifyChange();
        }

        public void On()
        {
            IsOn = true;
            NotifyChange();
        }

        protected void NotifyChange()
        {
            NotifyChange(new SwitchFeatureCommand { On = IsOn, Port = Port, Type = Type });
        }
    }
}