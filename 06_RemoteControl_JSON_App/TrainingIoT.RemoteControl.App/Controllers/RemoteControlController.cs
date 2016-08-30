using System.Collections.Generic;
using System.Web.Mvc;
using AutoMapper;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Models;

namespace TrainingIoT.RemoteControl.App.Controllers
{

    public class RemoteControlController : Controller
    {
        private readonly IDeviceRepository _deviceRepository;

        public RemoteControlController(IDeviceRepository deviceRepository)
        {
            _deviceRepository = deviceRepository;
        }

        public ActionResult Index()
        {
            var devices = _deviceRepository.FindAll();
            var devicesModels = Mapper.Map<IList<DeviceInfoModel>>(devices);
            return View(devicesModels);
        }


        public ActionResult Device(string id)
        {
            var device = _deviceRepository.FindById(id);
            if (device == null)
            {
                return HttpNotFound($"The device with {id} does not exist.");
            }

            var deviceModel = Mapper.Map<DeviceDetailModel>(device);
            return View(deviceModel);
        }


        public ActionResult ChangeSwitch(string id, int port, bool on)
        {
            var device = _deviceRepository.FindById(id);
            if (device == null)
            {
                return HttpNotFound($"The device with {id} does not exist.");
            }

            var feature = (SwitchDeviceFeature) device.GetFeatureByPort(port);
            if (on)
                feature.On();
            else 
                feature.Off();           

            return RedirectToAction("Device", new { id });
        }

        public ActionResult ChangeLed(string id, int port, bool on)
        {
            return ChangeSwitch(id, port, on);
        }
    }
}