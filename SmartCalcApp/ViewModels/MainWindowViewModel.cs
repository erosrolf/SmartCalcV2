using System.Globalization;
using System.Reactive;
using CommunityToolkit.Mvvm.Messaging;
using ReactiveUI;
using SmartCalcApp.Models;
using SmartCalcApp.Services;
using SmartCalcData.DataModel;

namespace SmartCalcApp.ViewModels
{
    public class MainWindowViewModel : ViewModelBase
    {
        private readonly CalcCore _calcCore;
        private readonly CalculationHistoryViewModel _calculationHistoryViewModel;
        private readonly XValueInputViewModel _xValueInputViewModel;
        private readonly XGraphValueInputViewModel _xGraphValueInputViewModel;
        private readonly GraphViewModel _graphViewModel;

        public ReactiveCommand<Unit, Unit> EqualCommand { get; }
        public ReactiveCommand<Unit, Unit> ToggleInfoCommand { get; }
        public ReactiveCommand<Unit, Unit> ToggleGraphCommand { get; }

        private bool _isEmptyHistory;

        public bool IsEmptyHistory
        {
            get => _isEmptyHistory;
            private set => this.RaiseAndSetIfChanged(ref _isEmptyHistory, value);
        }

        private bool _isInfoPressed;

        public bool IsInfoPressed
        {
            get => _isInfoPressed;
            set => this.RaiseAndSetIfChanged(ref _isInfoPressed, value);
        }

        private bool _isGraphPressed;

        public bool IsGraphPressed
        {
            get => _isGraphPressed;
            set => this.RaiseAndSetIfChanged(ref _isGraphPressed, value);
        }

        private ViewModelBase? _currentViewModel;

        public ViewModelBase? CurrentViewModel
        {
            get => _currentViewModel;
            set => this.RaiseAndSetIfChanged(ref _currentViewModel, value);
        }

        private ViewModelBase? _currentXInputViewModel;

        public ViewModelBase? CurrentXInputViewModel
        {
            get => _currentXInputViewModel;
            set => this.RaiseAndSetIfChanged(ref _currentXInputViewModel, value);
        }

        private string? _inputExpression;

        public string? InputExpression
        {
            get => _inputExpression;
            set
            {
                this.RaiseAndSetIfChanged(ref _inputExpression, value);
                Calculate();
            }
        }

        private string? _outputResult;

        public string? OutputResult
        {
            get => _outputResult;
            set => this.RaiseAndSetIfChanged(ref _outputResult, value);
        }

        public MainWindowViewModel()
        {
            _calcCore = new CalcCore();
            _calculationHistoryViewModel = new CalculationHistoryViewModel();
            EqualCommand = ReactiveCommand.Create(Equal);
            ToggleGraphCommand = ReactiveCommand.Create(ToggleGraph);
            ToggleInfoCommand = ReactiveCommand.Create(ToggleInfo);
            CurrentViewModel = _calculationHistoryViewModel;
            _xValueInputViewModel = new XValueInputViewModel();
            _xGraphValueInputViewModel = new XGraphValueInputViewModel();
            _graphViewModel = new GraphViewModel();
            CurrentXInputViewModel = _xValueInputViewModel;
            IsEmptyHistory = _calculationHistoryViewModel.History.Count == 0;
        }

        private void ToggleInfo()
        {
            if (IsInfoPressed)
            {
                if (IsGraphPressed)
                {
                    IsGraphPressed = false;
                    CurrentXInputViewModel = _xValueInputViewModel;
                }

                CurrentViewModel = new InfoViewModel();
            }
            else
            {
                CurrentViewModel = _calculationHistoryViewModel;
            }

            this.RaisePropertyChanged(nameof(IsInfoPressed));
            this.RaisePropertyChanged(nameof(IsGraphPressed));
        }

        private void ToggleGraph()
        {
            if (IsGraphPressed)
            {
                if (IsInfoPressed)
                {
                    IsInfoPressed = false;
                }

                CurrentViewModel = _graphViewModel;
                CurrentXInputViewModel = _xGraphValueInputViewModel;
            }
            else
            {
                CurrentViewModel = _calculationHistoryViewModel;
                CurrentXInputViewModel = _xValueInputViewModel;
            }

            this.RaisePropertyChanged(nameof(IsInfoPressed));
            this.RaisePropertyChanged(nameof(IsGraphPressed));
        }

        private void Calculate()
        {
            if (_currentViewModel is GraphViewModel ||
                _currentXInputViewModel is not XValueInputViewModel xValueViewModel) return;

            var result = _calcCore.Calculate(InputExpression, xValueViewModel.XExpression);

            if (_calcCore.GetStatus() == 0)
            {
                OutputResult = result.ToString(CultureInfo.CurrentCulture);
            }
        }

        private void Equal()
        {
            if (_calcCore.GetStatus() != 0)
            {
                OutputResult = "Invalid expression";
                return;
            }

            if (CurrentViewModel is GraphViewModel)
            {
                var message = new GraphParameters(InputExpression, _xGraphValueInputViewModel.XMin,
                    _xGraphValueInputViewModel.XMax);
                WeakReferenceMessenger.Default.Send(new UpdateGraphMessage(message));
            }
            else
            {
                SaveResult();
            }
        }

        private void SaveResult()
        {
            if (_calcCore.GetStatus() != 0)
            {
                OutputResult = "Invalid expression";
                return;
            }

            var expression = _calcCore.GetExpression();
            var polish = _calcCore.GetPolish();
            if (string.IsNullOrWhiteSpace(expression))
            {
                OutputResult = "Please enter your expression";
            }
            else
            {
                var history = new History(expression, polish, OutputResult);
                _calculationHistoryViewModel.History.Add(history);
                IsEmptyHistory = false;
            }
        }

        public void ClearHistory()
        {
            IsEmptyHistory = true;
            _calculationHistoryViewModel.History.Clear();
        }
    }
}