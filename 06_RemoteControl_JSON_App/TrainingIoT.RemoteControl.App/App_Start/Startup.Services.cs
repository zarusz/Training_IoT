using Autofac;
using TrainingIoT.RemoteControl.App.Domain.Impl;

namespace TrainingIoT.RemoteControl.App
{
    public partial class Startup
    {
        public static void RegisterServices(ContainerBuilder builder)
        {
            builder.RegisterType<MemoryDeviceRepository>()
                .AsImplementedInterfaces()
                .SingleInstance();

            builder.RegisterType<DefaultDeviceFactory>()
                .AsImplementedInterfaces();

            builder.RegisterType<MemoryFeatureCommandQueueService>()
                .AsImplementedInterfaces()
                .SingleInstance();

        }
    }
}