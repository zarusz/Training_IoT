using TrainingIoT.RemoteControl.App.Domain;

namespace TrainingIoT.RemoteControl.App.Models
{
    public class DeviceInfoModel
    {
        public string DeviceId { get; set; }

        public DeviceInfoModel()
        {
        }

        public DeviceInfoModel(Device device)
        {
            DeviceId = device.DeviceId;
        }
    }
}