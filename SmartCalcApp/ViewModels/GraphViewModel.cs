using System.Collections.ObjectModel;
using CommunityToolkit.Mvvm.Input;
using LiveChartsCore;
using LiveChartsCore.Defaults;
using LiveChartsCore.Drawing;
using LiveChartsCore.SkiaSharpView;
using LiveChartsCore.SkiaSharpView.Painting;
using LiveChartsCore.SkiaSharpView.Painting.Effects;
using SkiaSharp;
using SmartCalcApp.Models;
using SmartCalcApp.Services;
using CommunityToolkit.Mvvm.Messaging;

namespace SmartCalcApp.ViewModels;

public partial class GraphViewModel : ViewModelBase
{
    private static readonly SKColor SGray = new(195, 195, 195);
    private static readonly SKColor SGray1 = new(160, 160, 160);
    private static readonly SKColor SGray2 = new(115, 115, 115);
    private static readonly SKColor SBackground = new(80, 94, 110);

    public LiveChartsCore.Measure.Margin Margin { get; set; } = new LiveChartsCore.Measure.Margin(24, 8, 8, 20);

    public ISeries[] SeriesCollection { get; set; }

    public GraphViewModel()
    {
        WeakReferenceMessenger.Default.Register<UpdateGraphMessage>(this, (_, message) =>
        {
            UpdateGraph(message.Value);
        });
        var calcCore = new CalcCore();
        var newData = calcCore.CalculateGraphPoints("0", -10, 10);
        SeriesCollection =
            new ISeries[]
            {
                new LineSeries<ObservablePoint>
                {
                    Values = newData,
                    Stroke = new SolidColorPaint(new SKColor(233, 193, 76), 1),
                    Fill = null,
                    EnableNullSplitting = true,
                    GeometrySize = 0
                }
            };
    }

    ~GraphViewModel()
    {
        WeakReferenceMessenger.Default.Unregister<UpdateGraphMessage>(this);
    }

    [RelayCommand]
    public void UpdateGraph(GraphParameters graphParameters)
    {
        var calcCore = new CalcCore();
        var newData =
            calcCore.CalculateGraphPoints(graphParameters.Expression, graphParameters.From, graphParameters.To);
        SeriesCollection[0].Values = new ObservableCollection<ObservablePoint>(newData);
    }

    public Axis[] XAxes { get; set; } =
    {
        new Axis
        {
            NamePadding = new Padding(0),
            NamePaint = new SolidColorPaint(SGray1),
            TextSize = 12,
            Padding = new Padding(5, 0, 5, 5),
            LabelsPaint = new SolidColorPaint(SGray),
            SeparatorsPaint =
                new SolidColorPaint
                {
                    Color = SGray, StrokeThickness = 1, PathEffect = new DashEffect(new float[] { 3, 3 })
                },
            SubseparatorsPaint = new SolidColorPaint { Color = SGray2, StrokeThickness = 0.5f },
            SubseparatorsCount = 9,
            ZeroPaint = new SolidColorPaint { Color = SGray1, StrokeThickness = 2 },
            TicksPaint = new SolidColorPaint { Color = SGray, StrokeThickness = 1.5f },
            SubticksPaint = new SolidColorPaint { Color = SGray, StrokeThickness = 1 }
        }
    };

    public Axis[] YAxes { get; set; } =
    {
        new Axis
        {
            NamePadding = new Padding(0),
            NamePaint = new SolidColorPaint(SGray1),
            TextSize = 12,
            Padding = new Padding(5, 0, 0, 5),
            LabelsPaint = new SolidColorPaint(SGray),
            SeparatorsPaint =
                new SolidColorPaint
                {
                    Color = SGray, StrokeThickness = 1, PathEffect = new DashEffect(new float[] { 3, 3 })
                },
            SubseparatorsPaint = new SolidColorPaint { Color = SGray2, StrokeThickness = 0.5f },
            SubseparatorsCount = 9,
            ZeroPaint = new SolidColorPaint { Color = SGray1, StrokeThickness = 2 },
            TicksPaint = new SolidColorPaint { Color = SGray, StrokeThickness = 1.5f },
            SubticksPaint = new SolidColorPaint { Color = SGray, StrokeThickness = 1 }
        }
    };

    public DrawMarginFrame Frame { get; set; } =
        new()
        {
            Fill = new SolidColorPaint(SBackground),
            Stroke = new SolidColorPaint { Color = SGray, StrokeThickness = 0 }
        };
}