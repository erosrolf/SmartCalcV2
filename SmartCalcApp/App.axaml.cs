using System.IO;
using System.Text.Json;
using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using SmartCalcApp.Models;
using SmartCalcApp.ViewModels;
using SmartCalcApp.Views;

namespace SmartCalcApp;

public partial class App : Application
{
    public static AppSettings? Settings { get; private set; }
    
    public override void Initialize()
    {
        var json = File.ReadAllText("AppSettings.json");
        Settings = JsonSerializer.Deserialize<AppSettings>(json);
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