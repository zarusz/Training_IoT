using System.Collections.Generic;
using System.Linq;
using SlimMessageBus;
using TrainingIoT.RemoteControl.App.Messages;

namespace TrainingIoT.RemoteControl.App.Domain
{
    public class IrCode
    {
        public uint Data { get; set; }
        public uint Bits { get; set; }
    }

    public class IrOutFeature : DeviceFeature
    {
        public IrOutFeature(Device device, int port)
            : base(device, FeatureType.IrOut, port)
        {
        }

        public void Send(string codeType, IEnumerable<IrCode> codes)
        {
            MessageBus.Current.Publish(new IrOutFeatureCommand
            {
                DeviceId = Device.DeviceId,
                Type = Type,
                Port = Port,
                CodeType = codeType,
                CodeData = codes.Select(x => new IrOutFeatureCommand.CodeDataDto {Bits = x.Bits, Data = x.Data }).ToList()
            });
        }

    }
}