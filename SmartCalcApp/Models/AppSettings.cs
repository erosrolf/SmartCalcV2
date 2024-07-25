namespace SmartCalcApp.Models
{
    public class AppSettings
    {
        public AppSettings(string instructionFilePath)
        {
            InstructionFilePath = instructionFilePath;
        }

        public string InstructionFilePath { get; set; }
        public string CalcCoreLibPath { get; set; }
    }
}