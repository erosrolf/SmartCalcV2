using System;
using System.Text.RegularExpressions;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Interactivity;

namespace SmartCalcApp.Views
{
    public partial class XValueInputView : UserControl
    {
        public XValueInputView()
        {
            InitializeComponent();
            this.FindControl<TextBox>("XExpressionInputTextBox")
                ?.AddHandler(TextInputEvent, TextBox_XInputValidationRegexKeyDown, RoutingStrategies.Tunnel);
        }
        
        private void TextBox_XInputValidationRegexKeyDown(object? sender, TextInputEventArgs e)
        {
            string pattern = @"^[1234567890.sincostagleqr+\-*/^%()]*$";
            if (!Regex.IsMatch(e.Text ?? String.Empty, pattern))
            {
                e.Handled = true;
            } 
        }
    }
}
