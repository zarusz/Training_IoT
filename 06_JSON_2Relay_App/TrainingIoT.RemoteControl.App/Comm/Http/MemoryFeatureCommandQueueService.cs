using System.Collections.Concurrent;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm.Http
{
    public class MemoryFeatureCommandQueue : IFeatureCommandQueue
    {
        private readonly ConcurrentDictionary<string, ConcurrentQueue<FeatureCommand>> _commandsByDevice = new ConcurrentDictionary<string, ConcurrentQueue<FeatureCommand>>();

        #region Implementation of IFeatureCommandQueueService

        public FeatureCommand PopCommand(string deviceId)
        {
            ConcurrentQueue<FeatureCommand> commands;
            if (_commandsByDevice.TryGetValue(deviceId, out commands))
            {
                FeatureCommand command;
                if (commands.TryDequeue(out command))
                {
                    return command;
                }
            }

            return null;
        }

        public void PushCommand(string deviceId, FeatureCommand command)
        {
            ConcurrentQueue<FeatureCommand> commands;
            if (!_commandsByDevice.TryGetValue(deviceId, out commands))
            {
                commands = new ConcurrentQueue<FeatureCommand>();
                _commandsByDevice[deviceId] = commands;
            }

            commands.Enqueue(command);
        }

        #endregion
    }
}