using System.Collections.Generic;
using System.Linq;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class Device
    {
        public string DeviceId { get; set; }
        public IList<DeviceFeature> Features { get; set; }

        public Device(string deviceId)
        {
            DeviceId = deviceId;
            Features = new DeviceFeature[0];
        }

        public DeviceFeature GetFeatureByPort(int port) => Features.SingleOrDefault(x => x.Port == port);
    }
}