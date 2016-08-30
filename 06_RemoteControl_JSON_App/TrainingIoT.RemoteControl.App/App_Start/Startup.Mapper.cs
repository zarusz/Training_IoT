using AutoMapper;
using TrainingIoT.RemoteControl.App.Domain;
using TrainingIoT.RemoteControl.App.Models;

namespace TrainingIoT.RemoteControl.App
{
	public partial class Startup
	{
		public static void ConfigureMapper()
		{
			Mapper.Initialize(CreateMap);
		}

	    private static void CreateMap(IMapperConfigurationExpression cfg)
	    {
	        cfg.CreateMap<Device, DeviceInfoModel>();
	        cfg.CreateMap<Device, DeviceDetailModel>();
	        cfg.CreateMap<DeviceFeature, FeatureModel>()
	            .ForMember(x => x.DeviceId, x => x.MapFrom(d => d.Device.DeviceId));
            cfg.CreateMap<SwitchDeviceFeature, SwitchFeatureModel>();
        }

    }
}