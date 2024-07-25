using ReactiveUI;

namespace SmartCalcApp.ViewModels
{
    public class XValueInputViewModel : ViewModelBase
    {
        private string _xExpression;

        public string XExpression
        {
            get => _xExpression;
            set => this.RaiseAndSetIfChanged(ref _xExpression, value);
        }
    }
}