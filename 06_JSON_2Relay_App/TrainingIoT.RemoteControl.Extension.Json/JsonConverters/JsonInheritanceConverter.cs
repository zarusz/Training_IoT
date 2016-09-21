using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace TrainingIoT.RemoteControl.Extension.Json.JsonConverters
{
    public class JsonInheritanceConverter : JsonConverter
    {
        private readonly ConcurrentBag<Type> _notSupportedTypesCache = new ConcurrentBag<Type>();
        private readonly ConcurrentDictionary<Type, JsonInheritanceMeta> _metaByType = new ConcurrentDictionary<Type, JsonInheritanceMeta>();

        private static JsonDiscriminatorFieldAttribute TryGetDiscriminatorFieldAttrib(Type baseType)
        {
            var jsonDiscriminatorFieldAttrib = baseType.GetCustomAttribute<JsonDiscriminatorFieldAttribute>();
            return jsonDiscriminatorFieldAttrib;
        }

        public override bool CanConvert(Type objectType)
        {
            if (_notSupportedTypesCache.Contains(objectType))
            {
                // reject immediately
                return false;
            }

            if (_metaByType.ContainsKey(objectType))
            {
                return true;
            }

            var discriminatorFieldAttrib = TryGetDiscriminatorFieldAttrib(objectType);
            if (discriminatorFieldAttrib != null)
            {
                _metaByType[objectType] = new JsonInheritanceMeta(objectType, discriminatorFieldAttrib);
                return true;
            }

            // remember this type is not handled by this converter
            _notSupportedTypesCache.Add(objectType);
            return false;
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var meta = _metaByType[objectType];

            var item = JObject.Load(reader);
            var discriminator = item[meta.DiscriminatorField].Value<string>();

            var objectFactory = meta.GetObjectFactory(discriminator);
            if (objectFactory == null)
            {
                throw new ArgumentException($"Unknown discriminator value '{discriminator}'.");
            }

            var target = objectFactory();
            serializer.Populate(item.CreateReader(), target);

            return target;
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            serializer.Serialize(writer, value);
        }
    }
}