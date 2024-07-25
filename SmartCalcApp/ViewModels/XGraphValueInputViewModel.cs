using ReactiveUI;

namespace SmartCalcApp.ViewModels
{
    public class XGraphValueInputViewModel : ViewModelBase
    {
        private double? _xMin = -10;
        private double? _xMax = 10;

        public double XMin
        {
            get => _xMin ?? 0;
            set => this.RaiseAndSetIfChanged(ref _xMin, value);
        }

        public double XMax
        {
            get => _xMax ?? 0;
            set => this.RaiseAndSetIfChanged(ref _xMax, value);
        }
    }
}