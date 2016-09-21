using System;
using System.Configuration;
using System.Linq;
using System.Text;
using log4net;
using Newtonsoft.Json;
using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Messages;
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace TrainingIoT.RemoteControl.App.Comm.Mqtt
{
    public class MqttAdapter : IBackgroundService, IDisposable, IHandles<SwitchFeatureCommand>, IHandles<IrOutFeatureCommand>
    {
        public const string TopicSensor = "sensor";
        public const string TopicRegister = "register";

        private readonly TopicSub[] _topics = {
            new TopicSub { Name = TopicSensor, QoS = MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE },
            new TopicSub { Name = TopicRegister, QoS = MqttMsgBase.QOS_LEVEL_AT_LEAST_ONCE },
        };

        private class TopicSub
        {
            public string Name { get; set; }
            public byte QoS { get; set; }

        }

        private readonly MqttClient _client;
        private readonly JsonSerializerSettings _serializerSettings = new JsonSerializerSettings();
        private bool _started;

        private static readonly ILog Log = LogManager.GetLogger(typeof(MqttAdapter));

        public MqttAdapter()
        {
            Startup.SetJsonSerializationSettings(_serializerSettings);

            var serverHost = ConfigurationManager.AppSettings["MqttBrokerHost"];
            var serverPort = int.Parse(ConfigurationManager.AppSettings["MqttBrokerPort"]);

            _client = new MqttClient(serverHost, serverPort, false, MqttSslProtocols.None, null, null);
            _client.MqttMsgPublishReceived += OnMqttMessage;
        }

        #region Implementation of IBackgroundService

        public void Start()
        {
            if (!_started)
            {
                _client.Connect("ContolApp-" + Guid.NewGuid());
                _client.Subscribe(_topics.Select(x => x.Name).ToArray(), _topics.Select(x => x.QoS).ToArray());
                _started = true;
            }
        }

        public void Stop()
        {
            if (_started)
            {
                _client.Unsubscribe(_topics.Select(x => x.Name).ToArray());
                _client.Disconnect();
                _started = false;
            }
        }

        #endregion

        #region Implementation of IDisposable

        public void Dispose()
        {
            Stop();
        }

        #endregion

        private T DeserializeMessage<T>(byte[] payload)
        {
            var json = Encoding.ASCII.GetString(payload);
            var m = JsonConvert.DeserializeObject<T>(json, _serializerSettings);
            return m;
        }

        private byte[] SerializeMessage(object msg)
        {
            var json = JsonConvert.SerializeObject(msg, _serializerSettings);
            return Encoding.ASCII.GetBytes(json);
        }

        private void OnMqttMessage(object sender, MqttMsgPublishEventArgs args)
        {
            if (args.Topic == TopicSensor)
            {
                var e = DeserializeMessage<SensorFeatureEvent>(args.Message);
                MessageBus.Current.Publish(e);
            }
            else if (args.Topic == TopicRegister)
            {
                var e = DeserializeMessage<DeviceDescriptionEvent>(args.Message);
                MessageBus.Current.Publish(e);
            }
        }

        #region Implementation of IHandles<in SwitchFeatureCommand>

        public void Handle(SwitchFeatureCommand message)
        {
            var payload = SerializeMessage(message);
            _client.Publish(message.DeviceId, payload);

        }

        #endregion

        #region Implementation of IHandles<in IrOutFeatureCommand>

        public void Handle(IrOutFeatureCommand message)
        {
            var payload = SerializeMessage(message);
            _client.Publish(message.DeviceId, payload);
        }

        #endregion
    }
}