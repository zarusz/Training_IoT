using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm.Http
{
    public class HttpAdapter : IHandles<SwitchFeatureCommand>
    {
        private readonly IFeatureCommandQueue _queue;

        public HttpAdapter(IFeatureCommandQueue queue)
        {
            _queue = queue;
        }

        #region Implementation of IHandles<in SwitchFeatureCommand>

        public void Handle(SwitchFeatureCommand command)
        {
            _queue.PushCommand(command.DeviceId, command);
        }

        #endregion
    }
}