using Microsoft.EntityFrameworkCore;
using SmartCalcData.DataModel;

namespace SmartCalcData;

public class HistoryRepository : DAOHistoryRepository
{
    private readonly HistoryDbContext _db;

    public HistoryRepository(HistoryDbContext db)
    {
        _db = db;
    }

    public void AddHistory(History history)
    {
        _db.Add(history);
        _db.SaveChanges();
    }

    public void TruncateHistory()
    {
        _db.Database.ExecuteSqlRaw("DELETE FROM History;");
        _db.Database.ExecuteSqlRaw("DELETE FROM sqlite_sequence WHERE name = 'History'");
        _db.SaveChanges();
    }

    public List<History> GetHistory()
    {
        return _db.History.ToList();
    }
}