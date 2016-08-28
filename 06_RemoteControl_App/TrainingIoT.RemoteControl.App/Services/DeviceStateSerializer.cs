using TrainingIoT.RemoteControl.App.Controllers;

namespace TrainingIoT.RemoteControl.App.Services
{
    public class DeviceStateSerializer
    {
        public string Serialize(DeviceState deviceState)
        {
            return deviceState.LedOn ? "1" : "0";
        }

        public DeviceState Deserialize(string serial)
        {
            var ds = new DeviceState {LedOn = serial == "1"};
            return ds;
        }
    }
}