using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;

namespace TrainingIoT.RemoteControl.Extension.Json.JsonConverters
{
    public class JsonInheritanceMeta : IHasDiscriminatorValue
    {
        private readonly Type _baseType;
        public string DiscriminatorField { get; protected set; }
        public object DiscriminatorValue { get; protected set; }
        private readonly IDictionary<object, Func<object>> _objectFactoryByDiscriminatorValue;

        public JsonInheritanceMeta(Type baseType, JsonDiscriminatorFieldAttribute discriminatorFieldAttribute)
        {
            _baseType = baseType;
            DiscriminatorField = discriminatorFieldAttribute.DiscriminatorField;
            DiscriminatorValue = discriminatorFieldAttribute.DiscriminatorValue;
            _objectFactoryByDiscriminatorValue = ScanKnownTypes();

        }

        private IDictionary<object, Func<object>> ScanKnownTypes()
        {
            var objectFactory = new Dictionary<object, Func<object>>();

            var jsonSubclassAttribs = _baseType
                .GetCustomAttributes<JsonSubclassAttribute>()
                .ToList();

            foreach (var jsonSubclassAttrib in jsonSubclassAttribs)
            {
                AddObjectFactoryForType(jsonSubclassAttrib.Type, jsonSubclassAttrib.DiscriminatorValue, objectFactory);
            }

            // if the discriminator is provided and the base class is not abstract, register the object factory for it too
            if (DiscriminatorValue != null && !_baseType.IsAbstract)
            {
                AddObjectFactoryForType(_baseType, DiscriminatorValue, objectFactory);
            }

            return objectFactory;
        }

        private static void AddObjectFactoryForType(Type type, object discriminatorValue, Dictionary<object, Func<object>> objectFactory)
        {
            var typeConstructor = type.GetConstructor(Type.EmptyTypes);
            if (typeConstructor == null)
            {
                var msg = $"The class of type {type} needs a public no-arg constructor.";
                throw new InvalidOperationException(msg);
            }
            Func<object> typeFactory = () => typeConstructor.Invoke(null);
            objectFactory.Add(discriminatorValue, typeFactory);
        }

        public Func<object> GetObjectFactory(object discriminatorValue)
        {
            Func<object> objectFactory;
            return _objectFactoryByDiscriminatorValue.TryGetValue(discriminatorValue, out objectFactory) ? objectFactory : null;
        } 
    }
}