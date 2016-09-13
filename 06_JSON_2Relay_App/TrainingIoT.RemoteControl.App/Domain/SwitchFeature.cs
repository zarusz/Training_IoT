using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class SwitchFeature : DeviceFeature
    {
        public bool IsOn { get; protected set; }

        public SwitchFeature(Device device, FeatureType type, int port)
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

        #region Overrides of DeviceFeature

        protected override void NotifyChange()
        {
            base.NotifyChange();

            MessageBus.Current.Publish(new SwitchFeatureCommand
            {
                DeviceId = Device.DeviceId,
                Type = Type,
                Port = Port,
                On = IsOn
            });
        }

        #endregion
    }
}