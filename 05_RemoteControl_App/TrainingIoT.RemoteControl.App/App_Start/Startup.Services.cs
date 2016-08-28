using Autofac;
using TrainingIoT.RemoteControl.App.Services;
using TrainingIoT.RemoteControl.App.Services.Impl;

namespace TrainingIoT.RemoteControl.App
{
    public partial class Startup
    {
        public static void RegisterServices(ContainerBuilder builder)
        {
            builder.RegisterType<MemoryDeviceRepository>()
                .AsImplementedInterfaces()
                .SingleInstance();

            builder.RegisterType<DeviceStateSerializer>()
                .AsSelf()
                .SingleInstance();
        }
    }
}