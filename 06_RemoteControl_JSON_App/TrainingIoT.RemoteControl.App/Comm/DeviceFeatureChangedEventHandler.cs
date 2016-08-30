using NLog;
using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Domain.Events;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm
{
    public class DeviceFeatureChangedEventHandler : IHandles<DeviceFeatureChangedEvent>
    {
        private static readonly ILogger Logger = LogManager.GetCurrentClassLogger();
        private readonly IFeatureCommandQueueService _queue;

        public DeviceFeatureChangedEventHandler(IFeatureCommandQueueService queue)
        {
            _queue = queue;
        }

        #region Implementation of IHandles<in DeviceFeatureChangedEvent>

        public void Handle(DeviceFeatureChangedEvent message)
        {
            var switchFeature = message.Feature as SwitchDeviceFeature;
            if (switchFeature != null)
            {
                Logger.Info("Switch Port:{0} On:{1}", switchFeature.Port, switchFeature.IsOn);
                _queue.PushCommand(switchFeature.Device.DeviceId, new SwitchFeatureCommand
                {
                    Type = switchFeature.Type,
                    Port = switchFeature.Port,
                    On = switchFeature.IsOn
                });
            }
        }

        #endregion
    }
}