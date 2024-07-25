using System;
using System.Text.RegularExpressions;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;
using SmartCalcApp.ViewModels;

namespace SmartCalcApp.Views;

public partial class MainWindow : Window
{
    public MainWindow()
    {
        InitializeComponent();
        DataContext = new MainWindowViewModel();

        this.FindControl<TextBox>("ExpressionInputTextBox")
            ?.AddHandler(TextInputEvent, TextBox_InputValidationRegexKeyDown, RoutingStrategies.Tunnel);
    }
    
    private void TextBox_InputValidationRegexKeyDown(object? sender, TextInputEventArgs e)
    {
        string pattern = @"^[1234567890.sincostaglxeqr+\-*/^%()]*$";
        if (!Regex.IsMatch(e.Text ?? String.Empty, pattern))
        {
            e.Handled = true;
        } 
    }
}