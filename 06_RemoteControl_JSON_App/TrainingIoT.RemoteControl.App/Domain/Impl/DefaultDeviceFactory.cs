using System;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Domain.Impl
{
    public class DefaultDeviceFactory : IDeviceFactory
    {
        private readonly IDeviceRepository _deviceRepository;

        public DefaultDeviceFactory(IDeviceRepository deviceRepository)
        {
            _deviceRepository = deviceRepository;
        }

        #region Implementation of IDeviceFactory

        public Device CreateFromDiscovery(DeviceDescriptionEvent e)
        {
            var device = new Device(e.DeviceId);
            e.Features.ForEach(f => device.Features.Add(CreateFeature(device, f)));
            _deviceRepository.Save(device);
            return device;
        }

        private DeviceFeature CreateFeature(Device device, FeatureDescriptionDto f)
        {
            switch (f.Type)
            {
                case FeatureType.Switch:
                    return new SwitchFeature(device, f.Type, f.Port);

                case FeatureType.Led:
                    return new LedFeature(device, f.Type, f.Port);

                case FeatureType.TemperatureSensor:
                    return new TemperatureSensorFeature(device, f.Type, f.Port);

                case FeatureType.HumiditySensor:
                    return new HumiditySensorFeature(device, f.Type, f.Port);
            }

            throw new NotSupportedException($"The feature type {f.Type} is not supported.");
        }

        #endregion
    }
}