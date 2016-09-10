using log4net;
using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Domain.Events;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm
{
    public class FeatureChangedEventHandler : IHandles<FeatureChangedEvent>
    {
        private static readonly ILog Log = LogManager.GetLogger(typeof (FeatureChangedEventHandler));
        private readonly IFeatureCommandQueueService _queue;

        public FeatureChangedEventHandler(IFeatureCommandQueueService queue)
        {
            _queue = queue;
        }

        #region Implementation of IHandles<in FeatureChangedEvent>

        public void Handle(FeatureChangedEvent message)
        {
            var switchFeature = message.Feature as SwitchFeature;
            if (switchFeature != null)
            {
                Log.InfoFormat("Switch Port:{0} On:{1}", switchFeature.Port, switchFeature.IsOn);
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