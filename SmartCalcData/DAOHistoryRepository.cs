using SmartCalcData.DataModel;

namespace SmartCalcData
{
    public interface DAOHistoryRepository
    {
        public void AddHistory(History history);
        public List<History> GetHistory();
    }
}