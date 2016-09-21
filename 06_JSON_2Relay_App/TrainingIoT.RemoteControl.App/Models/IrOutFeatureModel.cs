namespace TrainingIoT.RemoteControl.App.Models
{
    public class IrOutFeatureModel : FeatureModel
    {
        public string CodeType { get; set; }
        public IrCodeModel[] Codes { get; set; }

        public class IrCodeModel 
        {
            public int Date { get; set; }
            public int Bits { get; set; }
        }
    }
}