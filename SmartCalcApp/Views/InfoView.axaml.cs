using Avalonia.Controls;
using SmartCalcApp.ViewModels;

namespace SmartCalcApp.Views
{
    public partial class InfoView : UserControl
    {
        public InfoView()
        {
            InitializeComponent();
            var viewModel = new InfoViewModel();
            DataContext = viewModel;
        }
    }
}