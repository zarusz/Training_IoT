using System.Net;
using System.Net.Http;
using System.Text;
using System.Web.Http;
using TrainingIoT.RemoteControl.App.Services;

namespace TrainingIoT.RemoteControl.App.Controllers
{
    [RoutePrefix("api/Device")]
    public class DeviceController : ApiController
    {
        private readonly IDeviceRepository _deviceRepository;
        private readonly DeviceStateSerializer _deviceStateSerializer;

        public DeviceController(IDeviceRepository deviceRepository, DeviceStateSerializer deviceStateSerializer)
        {
            _deviceRepository = deviceRepository;
            _deviceStateSerializer = deviceStateSerializer;
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
