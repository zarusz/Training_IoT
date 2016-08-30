using System.Net;
using System.Net.Http;
using System.Web.Http;
using TrainingIoT.RemoteControl.App.Comm;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Controllers
{
    [RoutePrefix("api/Device")]
    public class DeviceController : ApiController
    {
        private readonly IDeviceRepository _deviceRepository;
        private readonly IDeviceFactory _deviceFactory;
        private readonly IFeatureCommandQueueService _featureCommandQueueService;

        public DeviceController(IDeviceRepository deviceRepository, IDeviceFactory deviceFactory, IFeatureCommandQueueService featureCommandQueueService)
        {
            _deviceRepository = deviceRepository;
            _deviceFactory = deviceFactory;
            _featureCommandQueueService = featureCommandQueueService;
        }

        [HttpPost]
        [Route("Register")]
        public HttpResponseMessage Register(DeviceDescriptionEvent e)
        {
            // for simplicity remove previous state for that device
            var device = _deviceRepository.FindById(e.DeviceId);
            if (device != null)
            {
                _deviceRepository.Remove(device);
            }

            // create
            _deviceFactory.CreateFromDiscovery(e);

            return Request.CreateResponse(HttpStatusCode.OK);

        }

        [HttpGet]
        [Route("{deviceId}")]
        public HttpResponseMessage PopCommand(string deviceId)
        {
            var command = _featureCommandQueueService.PopCommand(deviceId);
            if (command == null)
            {
                // OK, but no payload in response
                return Request.CreateResponse(HttpStatusCode.OK);
            }
            return Request.CreateResponse(HttpStatusCode.OK, command);
        }
    }
}
