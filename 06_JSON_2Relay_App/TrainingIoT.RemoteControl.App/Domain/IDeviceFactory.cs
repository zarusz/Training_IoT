using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public interface IDeviceFactory
    {
        Device CreateFromDiscovery(DeviceDescriptionEvent e);
    }
}