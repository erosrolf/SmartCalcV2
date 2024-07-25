using CommunityToolkit.Mvvm.Messaging.Messages;

namespace SmartCalcApp.Services;

public struct GraphParameters
{
    public string Expression { get; set; }
    public double From { get; set; }
    public double To { get; set; }

    public GraphParameters(string expression, double from, double to)
    {
        Expression = expression;
        From = from;
        To = to;
    }
}

public class UpdateGraphMessage : ValueChangedMessage<GraphParameters>
{
    public UpdateGraphMessage(GraphParameters value) : base(value) { }
}