using System.Collections.Generic;

namespace TrainingIoT.RemoteControl.App.Models
{
    public class DeviceDetailModel : DeviceInfoModel
    {
        public IList<FeatureModel> Features { get; set; }
        
    }
}