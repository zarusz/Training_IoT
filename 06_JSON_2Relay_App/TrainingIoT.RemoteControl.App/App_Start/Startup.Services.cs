using System.Configuration;
using Autofac;
using SlimMessageBus;
using SlimMessageBus.Core.Config;
using SlimMessageBus.ServiceLocator.Config;
using TrainingIoT.RemoteControl.App.Comm;
using TrainingIoT.RemoteControl.App.Comm.Http;
using TrainingIoT.RemoteControl.App.Comm.Mqtt;
using TrainingIoT.RemoteControl.App.Domain.Impl;
using TrainingIoT.RemoteControl.App.ErrorLogging;
using TrainingIoT.RemoteControl.App.Handlers;

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


            builder.RegisterType<DeviceDescriptionEventHandler>()
                .AsImplementedInterfaces();

            builder.RegisterType<SensorFeatureEventHandler>()
                .AsImplementedInterfaces();


            var messageBus = new MessageBusBuilder()
                .ResolveHandlersFromServiceLocator()
                .Build();

            MessageBus.SetProvider(() => messageBus);
            builder.RegisterInstance(messageBus);

            var mqttTransport = ConfigurationManager.AppSettings["TransportMode"] == "MQTT";
            if (mqttTransport)
                TransportMqtt(builder);
            else
                TransportHttp(builder);
        }

        private static void TransportMqtt(ContainerBuilder builder)
        {
            builder.RegisterType<MqttAdapter>()
                .AsSelf()
                .AsImplementedInterfaces()
                .SingleInstance()
                .AutoActivate();
        }

        private static void TransportHttp(ContainerBuilder builder)
        {
            builder.RegisterType<MemoryFeatureCommandQueue>()
                .AsImplementedInterfaces()
                .SingleInstance();

            builder.RegisterType<HttpAdapter>()
                .AsImplementedInterfaces();
        }
    }
}