using System;

namespace TrainingIoT.RemoteControl.Extension.Json.JsonConverters
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Struct)]
    public class JsonDiscriminatorFieldAttribute : Attribute, IHasDiscriminatorValue
    {
        public string DiscriminatorField { get; protected set; }
        public object DiscriminatorValue { get; protected set; }

        public JsonDiscriminatorFieldAttribute(string discriminatorField, object discriminatorValue = null)
        {
            DiscriminatorField = discriminatorField;
            DiscriminatorValue = discriminatorValue;
        }
    }
}