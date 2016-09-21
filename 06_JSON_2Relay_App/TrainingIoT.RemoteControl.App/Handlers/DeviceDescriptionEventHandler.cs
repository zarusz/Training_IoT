using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Handlers
{
    public class DeviceDescriptionEventHandler : IHandles<DeviceDescriptionEvent>
    {
        private readonly IDeviceRepository _deviceRepository;
        private readonly IDeviceFactory _deviceFactory;

        public DeviceDescriptionEventHandler(IDeviceRepository deviceRepository, IDeviceFactory deviceFactory)
        {
            _deviceRepository = deviceRepository;
            _deviceFactory = deviceFactory;
        }

        #region Implementation of IHandles<in DeviceDescriptionEvent>

        public void Handle(DeviceDescriptionEvent e)
        {
            // for simplicity remove previous state for that device
            var device = _deviceRepository.FindById(e.DeviceId);
            if (device != null)
            {
                _deviceRepository.Remove(device);
            }

            // create
            _deviceFactory.CreateFromDiscovery(e);
        }

        #endregion
    }
}