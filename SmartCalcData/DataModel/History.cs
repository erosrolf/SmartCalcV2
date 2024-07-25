using System.ComponentModel.DataAnnotations;

namespace SmartCalcData.DataModel
{
    public class History
    {
        [Key] public int Id { get; set; }

        public string Expression { get; set; }
        public string PolishExpression { get; set; }
        public string Result { get; set; }

        public History(string expression, string polishExpression, string result)
        {
            Expression = expression;
            PolishExpression = polishExpression;
            Result = result;
        }
    }
}