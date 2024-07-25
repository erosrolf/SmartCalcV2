using System;
using SmartCalcApp.Models;
using SmartCalcApp.Services;

namespace SmartCalcApp.ViewModels
{
    public class InfoViewModel : ViewModelBase
    {
        private readonly InstructionModel? _instructions;

        public InfoViewModel()
        {
            var instructionService = new InstructionService();
            _instructions = instructionService.GetInstructions();
            if (_instructions is null)
            {
                throw new Exception("Instructions is empty after serialization");
            }
        }

        public string InstructionsOperationText =>
            _instructions?.OperationsText == null
                ? String.Empty
                : String.Join(Environment.NewLine, _instructions.OperationsText);

        public string InstructionsFunctionsText =>
            _instructions?.FunctionsText == null
                ? String.Empty
                : String.Join(Environment.NewLine, _instructions.FunctionsText);

        public string InstructionsOperationExamples =>
            _instructions?.OperationsExamples == null
                ? String.Empty
                : string.Join(Environment.NewLine, _instructions.OperationsExamples);

        public string InstructionsFunctionsExamples =>
            _instructions?.FunctionsExamples == null
                ? String.Empty
                : String.Join(Environment.NewLine, _instructions.FunctionsExamples);
    }
}