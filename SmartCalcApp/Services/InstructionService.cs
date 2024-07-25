using System;
using System.IO;
using System.Text.Json;
using SmartCalcApp.Models;

namespace SmartCalcApp.Services;

public class InstructionService
{
    public InstructionModel? GetInstructions()
    {
        if (App.Settings is null)
        {
            throw new Exception("App.Settings are not initialized!");
        }

        if (!File.Exists(App.Settings.InstructionFilePath))
        {
            throw new Exception("File with instructions not found");
        }

        var json = File.ReadAllText(App.Settings.InstructionFilePath);
        return JsonSerializer.Deserialize<InstructionModel>(json);
    }
}