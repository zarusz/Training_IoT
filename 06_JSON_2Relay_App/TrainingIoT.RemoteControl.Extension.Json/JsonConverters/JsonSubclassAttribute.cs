using System;

namespace TrainingIoT.RemoteControl.Extension.Json.JsonConverters
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct, AllowMultiple = true)]
    public class JsonSubclassAttribute : Attribute, IHasDiscriminatorValue
    {
        public Type Type { get; protected set; }
        public object DiscriminatorValue { get; protected set; }

        public JsonSubclassAttribute(Type type, object discriminatorValue)
        {
            Type = type;
            DiscriminatorValue = discriminatorValue;
        }
    }
}