using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Comm.Http
{
    public interface IFeatureCommandQueue
    {
        FeatureCommand PopCommand(string deviceId);
        void PushCommand(string deviceId, FeatureCommand command);
    }
}