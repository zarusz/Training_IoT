using System.Collections.Generic;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public interface IDeviceRepository
    {
        ICollection<Device> FindAll(); 
        Device FindById(string deviceId);
        void Save(Device device);
        void Remove(Device device);
    }
}