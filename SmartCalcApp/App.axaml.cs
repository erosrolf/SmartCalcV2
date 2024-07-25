using System;
using System.IO;
using System.Text.Json;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using SmartCalcApp.Models;
using SmartCalcApp.ViewModels;
using SmartCalcApp.Views;

namespace SmartCalcApp
{
    public partial class App : Application
    {
        public static AppSettings? Settings { get; private set; }

        public override void Initialize()
        {
            string directory = AppDomain.CurrentDomain.BaseDirectory;
            string filePath = Path.Combine(directory, "AppSettings.json");

            if (File.Exists(filePath))
            {
                var json = File.ReadAllText(filePath);
                Settings = JsonSerializer.Deserialize<AppSettings>(json);
            }
            else
            {
                Console.WriteLine($"File {filePath} not found!");
            }

            AvaloniaXamlLoader.Load(this);
        }

        public override void OnFrameworkInitializationCompleted()
        {
            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                desktop.MainWindow = new MainWindow
                {
                    DataContext = new MainWindowViewModel(),
                };
            }

            base.OnFrameworkInitializationCompleted();
        }
    }
}
 
