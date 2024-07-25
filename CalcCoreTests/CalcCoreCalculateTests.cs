using LiveChartsCore.Defaults;
using SmartCalcApp.Models;

namespace CalcCoreTests
{
    public class CalcCoreCalculateTests
    {
        [Fact]
        public void GivenValidInputExpressions_WhenCalculateCalled_ThenCorrectResult()
        {
            // Arrange
            var calcCore = new CalcCore();
            double expectedResult = 6.0;

            // Act
            double actualResult = calcCore.Calculate("2+x", "2*2");

            // Assert
            Assert.Equal(expectedResult, actualResult);
        }

        [Fact]
        public void GivenInvalidInputExpressions_WhenCalculateCalled_ThenIncorrectStatus()
        {
            // Arrange
            var calcCore = new CalcCore();
            int correctExpressionStatus = 0;

            // Act
            calcCore.Calculate("e2", "2*2");
            int status = calcCore.GetStatus();

            // Assert
            Assert.NotEqual(correctExpressionStatus, status);
        }

        [Fact]
        public void GivenValidInputExpression_WhenCalculateGraphPoints_ThenCorrectResult()
        {
            // Arrange
            var calcCore = new CalcCore();
            int expectedCount = 800;

            // Act
            List<ObservablePoint> actualResult = calcCore.CalculateGraphPoints("x^2", -10, 10);

            // Assert
            Assert.Equal(expectedCount, actualResult.Count);
        }
    }
}