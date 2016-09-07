using System.Collections.Generic;

namespace TrainingIoT.RemoteControl.App.Messages
{
    public class DeviceDescriptionEvent
    {
        public string DeviceId { get; set; }
        public List<FeatureDescriptionDto> Features;
    }
}