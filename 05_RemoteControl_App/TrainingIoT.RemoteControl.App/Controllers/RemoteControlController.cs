using System.Collections.Generic;
using System.Web.Mvc;
using AutoMapper;
using TrainingIoT.RemoteControl.App.Models;
using TrainingIoT.RemoteControl.App.Services;

namespace TrainingIoT.RemoteControl.App.Controllers
{

    public class RemoteControlController : Controller
    {
        private readonly IDeviceRepository _deviceRepository;
        private readonly DeviceStateSerializer _deviceStateSerializer;

        public RemoteControlController(IDeviceRepository deviceRepository, DeviceStateSerializer deviceStateSerializer)
        {
            _deviceRepository = deviceRepository;
            _deviceStateSerializer = deviceStateSerializer;
        }

        public ActionResult Index()
        {
            var devices = _deviceRepository.FindAll();
            var devicesModels = Mapper.Map<IList<DeviceInfoModel>>(devices);
            return View(devicesModels);
        }


        public ActionResult Device(string id, string state = null)
        {
            var device = _deviceRepository.FindById(id);
            if (device == null)
            {
                return HttpNotFound($"The device with {id} does not exist.");
            }

            if (state != null)
            {
                device.State = _deviceStateSerializer.Deserialize(state);
                _deviceRepository.Save(device);
            }

            var deviceModel = Mapper.Map<DeviceDetailModel>(device);
            return View(deviceModel);
        }
    }
}