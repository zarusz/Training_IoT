using log4net;
using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Handlers
{
    public class SensorFeatureEventHandler : IHandles<SensorFeatureEvent>
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (SensorFeatureEventHandler));

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

            var temperatureSensorFeatureEvent = e as TemperatureSensorFeatureEvent;
            if (temperatureSensorFeatureEvent != null)
            {
                var tempSensorFeature = device.GetFeatureByPort<TemperatureSensorFeature>(e.Port);
                tempSensorFeature?.Measured(temperatureSensorFeatureEvent.Temperature);
            }
            var humiditySensorFeatureEvent = e as HumiditySensorFeatureEvent;
            if (humiditySensorFeatureEvent != null)
            {
                var humidSensorFeature = device.GetFeatureByPort<HumiditySensorFeature>(e.Port);
                humidSensorFeature?.Measured(humiditySensorFeatureEvent.Humidity);
            }
            var motionSensorFeatureEvent = e as MotionSensorFeatureEvent;
            if (motionSensorFeatureEvent != null)
            {
                var motionSensorFeature = device.GetFeatureByPort<MotionSensorFeature>(e.Port);
                motionSensorFeature?.Measured(motionSensorFeatureEvent.Motion);
            }

        }

        #endregion
    }
}