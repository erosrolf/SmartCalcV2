using Microsoft.EntityFrameworkCore;
using SmartCalcData.DataModel;

namespace SmartCalcData
{
    public class HistoryDbContext : DbContext
    {
        public DbSet<History> History => Set<History>();

        public HistoryDbContext()
        {
            Database.Migrate();
        }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            optionsBuilder.UseSqlite("Filename=CalculationHistory.db");
        }
    }
}