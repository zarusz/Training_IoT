using System.Collections.Concurrent;
using System.Collections.Generic;

namespace TrainingIoT.RemoteControl.App.Domain.Impl
{
    public class MemoryDeviceRepository : IDeviceRepository
    {
        private readonly ConcurrentDictionary<string, Device> _deviceStateById = new ConcurrentDictionary<string, Device>();

        #region Implementation of IDeviceRepository

        public ICollection<Device> FindAll()
        {
            return new List<Device>(_deviceStateById.Values);
        }

        public Device FindById(string deviceId)
        {
            Device device;
            if (_deviceStateById.TryGetValue(deviceId, out device))
            {
                return device;
            }
            return null;
        }

        public void Save(Device device)
        {
            _deviceStateById[device.DeviceId] = device;
        }

        public void Remove(Device device)
        {
            Device d;
            _deviceStateById.TryRemove(device.DeviceId, out d);
        }

        #endregion
    }
}