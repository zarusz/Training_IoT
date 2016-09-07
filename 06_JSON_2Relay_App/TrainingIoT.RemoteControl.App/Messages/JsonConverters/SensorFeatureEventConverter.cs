using System;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace TrainingIoT.RemoteControl.App.Messages.JsonConverters
{
    public class SensorFeatureEventConverter : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            return typeof(SensorFeatureEvent).IsAssignableFrom(objectType);
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var item = JObject.Load(reader);
            var discriminator = item["type"].Value<string>();
            object target = null;
            switch (discriminator)
            {
                case "temperatureSensor":
                    target = new TemperatureSensorFeatureEvent();
                    break;

                case "humiditySensor":
                    target = new HumiditySensorFeatureEvent();
                    break;

                default:
                    throw new ArgumentException("Invalid source type");
            }

            serializer.Populate(item.CreateReader(), target);

            return target;
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            serializer.Serialize(writer, value);
        }
    }
}