using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm
{
    public interface IFeatureCommandQueueService
    {
        FeatureCommand PopCommand(string deviceId);
        void PushCommand(string deviceId, FeatureCommand command);
    }
}