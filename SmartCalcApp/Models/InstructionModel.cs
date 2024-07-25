using System.Collections.Generic;

namespace SmartCalcApp.Models
{
    public class InstructionModel
    {
        public List<string>? OperationsText { get; set; }
        public List<string>? FunctionsText { get; set; }
        public List<string>? OperationsExamples { get; set; }
        public List<string>? FunctionsExamples { get; set; }
    }
}