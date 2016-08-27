using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Data.Odbc;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Web.Http;

namespace TrainingIoT.RemoteControl.App.Controllers
{
    public class DeviceState
    {
        public bool LedOn { get; set; }
    }

    public class Device
    {
        public string DeviceId { get; set; }
        public DeviceState State { get; set; }
    }

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

    public interface IDeviceRepository
    {
        ICollection<Device> FindAll(); 
        Device FindById(string deviceId);
        void Save(Device device);
    }

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

        #endregion

        public static readonly MemoryDeviceRepository Instance = new MemoryDeviceRepository();
    }


    [RoutePrefix("api/Device")]
    public class DeviceController : ApiController
    {
        private readonly IDeviceRepository _deviceRepository;
        private readonly DeviceStateSerializer _deviceStateSerializer;

        public DeviceController()
        {
            _deviceRepository = MemoryDeviceRepository.Instance;
            _deviceStateSerializer = new DeviceStateSerializer();
        }

        [HttpGet]
        [Route("{deviceId}/State")]
        public HttpResponseMessage GetDeviceState(string deviceId)
        {
            var device = _deviceRepository.FindById(deviceId);
            if (device == null)
            {
                // add the new device, so we can display it on the UI
                device = new Device
                {
                    DeviceId = deviceId,
                    State = new DeviceState()
                };
                _deviceRepository.Save(device);
            }

            var state = _deviceStateSerializer.Serialize(device.State);

            // respond the string as plain text in ASCII
            var response = Request.CreateResponse(HttpStatusCode.OK);
            response.Content = new StringContent(state, Encoding.ASCII, "text/plain");
            return response;
        }

        [HttpGet]
        [Route("{deviceId}")]
        public HttpResponseMessage SetDeviceState(string deviceId, string state = null)
        {
            var device = _deviceRepository.FindById(deviceId);
            if (device == null)
            {
                return Request.CreateErrorResponse(HttpStatusCode.NotFound, $"The device with id '{deviceId}' does not exist.");
            }

            device.State = _deviceStateSerializer.Deserialize(state);
            return Request.CreateResponse(HttpStatusCode.OK);
        }
    }
}
