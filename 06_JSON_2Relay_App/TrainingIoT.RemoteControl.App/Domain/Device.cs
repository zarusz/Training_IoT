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
            Features = new List<DeviceFeature>();
        }

        public IEnumerable<DeviceFeature> GetFeaturesByPort(int port) => Features.Where(x => x.Port == port);
        public T GetFeatureByPort<T>(int port) where T : DeviceFeature => GetFeaturesByPort(port).OfType<T>().SingleOrDefault();
    }
}