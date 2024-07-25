using System.Collections.Generic;
using SmartCalcData.DataModel;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using SmartCalcData;

namespace SmartCalcApp.ViewModels
{
    public class CalculationHistoryViewModel : ViewModelBase
    {
        public ObservableCollection<History> History { get; set; }

        public CalculationHistoryViewModel()
        {
            History = new ObservableCollection<History>(LoadHistory());
            History.CollectionChanged += OnHistoryCollectionChanged;
        }

        private IEnumerable<History> LoadHistory()
        {
            using var db = new HistoryDbContext();
            var repository = new HistoryRepository(db);
            return repository.GetHistory();
        }

        private void OnHistoryCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            using var db = new HistoryDbContext();
            var repository = new HistoryRepository(db);

            switch (e.Action)
            {
                case NotifyCollectionChangedAction.Add:
                    if (e.NewItems != null)
                        foreach (History item in e.NewItems)
                        {
                            repository.AddHistory(item);
                        }

                    break;

                case NotifyCollectionChangedAction.Reset:
                    repository.TruncateHistory();

                    break;
            }
        }
    }
}