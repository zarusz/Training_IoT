using System.Collections.Generic;

namespace TrainingIoT.RemoteControl.App.Messages
{
    public class IrOutFeatureCommand : FeatureCommand
    {
        public string CodeType { get; set; }
        public IList<CodeDataDto> CodeData { get; set; }

        public class CodeDataDto
        {
            public uint Bits { get; set; }
            public uint Data { get; set; }
        }
    }
}