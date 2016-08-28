using System.Collections.Generic;

namespace TrainingIoT.RemoteControl.App.Services
{
    public interface IDeviceRepository
    {
        ICollection<Device> FindAll(); 
        Device FindById(string deviceId);
        void Save(Device device);
    }
}