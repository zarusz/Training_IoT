using System;
using System.Collections.Generic;
using System.Linq;
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

            var feature = device.GetFeatureByPort<SwitchFeature>(port);
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

        public ActionResult SendIr(string id, int port, string codeType, string data)
        {
            var codes = new List<IrCode>();
            foreach (var code in data.Split('|').Select(x => x.Split(':')).ToList())
            {
                var d = Convert.ToUInt32(code[0], 16);
                var b = uint.Parse(code[1]);
                var irCode = new IrCode {Bits = b, Data = d};
                codes.Add(irCode);
            }


            var device = _deviceRepository.FindById(id);
            if (device == null)
            {
                return HttpNotFound($"The device with {id} does not exist.");
            }

            var feature = device.GetFeatureByPort<IrOutFeature>(port);
            feature.Send(codeType, codes);

            return RedirectToAction("Device", new { id });
        }
    }
}