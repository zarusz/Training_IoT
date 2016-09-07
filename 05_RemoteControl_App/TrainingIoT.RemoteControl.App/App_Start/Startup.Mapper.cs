using AutoMapper;
using TrainingIoT.RemoteControl.App.Models;
using TrainingIoT.RemoteControl.App.Services;

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
	    }

	}
}