using Autofac;
using SlimMessageBus;
using SlimMessageBus.Core.Config;
using SlimMessageBus.ServiceLocator.Config;
using TrainingIoT.RemoteControl.App.Comm;
using TrainingIoT.RemoteControl.App.Domain.Impl;
using TrainingIoT.RemoteControl.App.ErrorLogging;

namespace TrainingIoT.RemoteControl.App
{
    public partial class Startup
    {
        public static void RegisterServices(ContainerBuilder builder)
        {
            builder.RegisterType<ErrorLoggingMiddleware>();

            builder.RegisterType<MemoryDeviceRepository>()
                .AsImplementedInterfaces()
                .SingleInstance();

            builder.RegisterType<DefaultDeviceFactory>()
                .AsImplementedInterfaces();

            builder.RegisterType<MemoryFeatureCommandQueueService>()
                .AsImplementedInterfaces()
                .SingleInstance();


            var messageBus = new MessageBusBuilder()
                .ResolveHandlersFromServiceLocator()
                .Build();

            MessageBus.SetProvider(() => messageBus);
            builder.RegisterInstance(messageBus);

            builder.RegisterType<FeatureChangedEventHandler>()
                .AsImplementedInterfaces();

            builder.RegisterType<SensorFeatureEventHandler>()
                .AsImplementedInterfaces();
        }
    }
}