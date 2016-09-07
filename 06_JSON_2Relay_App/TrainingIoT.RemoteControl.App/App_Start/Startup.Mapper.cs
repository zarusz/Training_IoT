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


                
            cfg.CreateMap<SwitchFeature, SwitchFeatureModel>()
                .IncludeBase<DeviceFeature, FeatureModel>();

            cfg.CreateMap<LedFeature, LedFeatureModel>()
                .IncludeBase<SwitchFeature, SwitchFeatureModel>();

            cfg.CreateMap<LedFeature, LedFeatureModel>()
                .IncludeBase<DeviceFeature, FeatureModel>();

            cfg.CreateMap<TemperatureSensorFeature, TemperatureSensorFeatureModel>()
                .IncludeBase<DeviceFeature, FeatureModel>();

            cfg.CreateMap<HumiditySensorFeature, HumiditySensorFeatureModel>()
                .IncludeBase<DeviceFeature, FeatureModel>();
        }

    }
}