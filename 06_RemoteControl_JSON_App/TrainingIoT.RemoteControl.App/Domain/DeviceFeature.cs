using Microsoft.Practices.ServiceLocation;
using TrainingIoT.RemoteControl.App.Messages;

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

        protected void NotifyChange(FeatureCommand command)
        {
            var q = ServiceLocator.Current.GetInstance<IFeatureCommandQueueService>();
            q.PushCommand(Device.DeviceId, command);
        }
    }
}