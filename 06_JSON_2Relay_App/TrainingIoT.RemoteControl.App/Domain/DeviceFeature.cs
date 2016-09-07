using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Domain.Events;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class DeviceFeature
    {
        public Device Device { get; protected set; }
        public FeatureType Type { get; protected set; }
        public int Port { get; protected set; }
        public string DisplayName { get; set; }

        public DeviceFeature(Device device, FeatureType type, int port)
        {
            Device = device;
            Type = type;
            Port = port;
        }

        protected void NotifyChange()
        {
            MessageBus.Current.Publish(new FeatureChangedEvent(this));
        }
    }
}