using System;
using System.IO;

namespace SmartCalcApp.Models
{
    public class AppSettings
    {
        public string InstructionFilePath { get; init; }
        public string CombinedInstructionFilePath() => Path.Combine(BaseDirectory, InstructionFilePath);
        private string BaseDirectory => AppDomain.CurrentDomain.BaseDirectory;
        public AppSettings(string instructionFilePath)
        {
            InstructionFilePath = instructionFilePath;
        }
    }
}