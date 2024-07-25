using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using LiveChartsCore.Defaults;

namespace SmartCalcApp.Models
{
    public class CalcCore
    {
        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr CreateModelWrapper();

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern void DeleteModelWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern void CalculateWrapper(IntPtr model, string expression, string xValue);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetResultWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern void CalculateVectorsWithPointsWrapper(IntPtr model, string expression, double xBegin,
            double xEnd);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetVectorXWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetVectorYWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetVectorSizeWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetExpressionWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetPolishWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetStatusWrapper(IntPtr model);

        [DllImport("CoreLibs/libCalcCore.dylib", CallingConvention = CallingConvention.Cdecl)]
        private static extern void FreeArreyMemory(IntPtr ptr);

        private readonly IntPtr _calcModel;

        public CalcCore()
        {
            _calcModel = CreateModelWrapper();
        }

        ~CalcCore()
        {
            DeleteModelWrapper(_calcModel);
        }

        public double Calculate(string? expression, string? xValue)
        {
            if (String.IsNullOrWhiteSpace(expression))
            {
                expression = "0";
            }

            if (String.IsNullOrWhiteSpace(xValue))
            {
                xValue = "0";
            }

            CalculateWrapper(_calcModel, expression, xValue);
            return GetResultWrapper(_calcModel);
        }

        public string GetExpression()
        {
            IntPtr ptr = GetExpressionWrapper(_calcModel);
            string result = Marshal.PtrToStringAnsi(ptr);
            FreeArreyMemory(ptr);
            return result;
        }

        public string GetPolish()
        {
            IntPtr ptr = GetPolishWrapper(_calcModel);
            string result = Marshal.PtrToStringAnsi(ptr);
            FreeArreyMemory(ptr);
            return result;
        }

        private List<double> GetVector(IntPtr model, Func<IntPtr, IntPtr> getVectorWrapper)
        {
            var size = GetVectorSizeWrapper(_calcModel);
            var vectorPtr = getVectorWrapper(_calcModel);
            var vector = new double[size];
            Marshal.Copy(vectorPtr, vector, 0, size);
            FreeArreyMemory(vectorPtr);
            return new List<double>(vector);
        }

        public List<ObservablePoint> CalculateGraphPoints(string? expression, double xBegin, double xEnd)
        {
            if (String.IsNullOrWhiteSpace(expression))
            {
                expression = "0";
            }

            CalculateVectorsWithPointsWrapper(_calcModel, expression, xBegin, xEnd);
            List<double> x = GetVector(_calcModel, GetVectorXWrapper);
            List<double> y = GetVector(_calcModel, GetVectorYWrapper);
            var points = new List<ObservablePoint>();

            for (int i = 0; i < Math.Min(x.Count, y.Count); i++)
            {
                points.Add(new ObservablePoint(x[i], y[i]));
            }

            return points;
        }

        public int GetStatus() => GetStatusWrapper(_calcModel);
    }
}