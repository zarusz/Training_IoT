using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm
{
    public class SensorFeatureEventHandler : IHandles<SensorFeatureEvent>
    {
        private readonly IDeviceRepository _deviceRepository;

        public SensorFeatureEventHandler(IDeviceRepository deviceRepository)
        {
            _deviceRepository = deviceRepository;
        }

        #region Implementation of IHandles<in SensorFeatureEvent>

        public void Handle(SensorFeatureEvent e)
        {
            var device = _deviceRepository.FindById(e.DeviceId);
            if (device == null)
            {
                // no such device
                return;
            }

            var feature = device.GetFeatureByPort(e.Port);

            var temperatureSensorFeatureEvent = e as TemperatureSensorFeatureEvent;
            if (temperatureSensorFeatureEvent != null)
            {
                ((TemperatureSensorFeature)feature).Measured(temperatureSensorFeatureEvent.Temperature);
            }
            var humiditySensorFeatureEvent = e as HumiditySensorFeatureEvent;
            if (humiditySensorFeatureEvent != null)
            {
                ((HumiditySensorFeature)feature).Measured(humiditySensorFeatureEvent.Humidity);
            }

        }

        #endregion
    }
}