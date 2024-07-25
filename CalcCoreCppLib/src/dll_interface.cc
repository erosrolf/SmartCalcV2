#include "calc_graph.h"
#include "polish_calc.h"
#include "model.h"

extern "C" __attribute__ ((visibility ("default")))
void* CreateModelWrapper() {
    return static_cast<void*>(new s21::Model());
}

extern "C" __attribute__ ((visibility ("default")))
void DeleteModelWrapper(void* model) {
    delete static_cast<s21::Model*>(model);
}

extern "C" __attribute__ ((visibility ("default")))
void FreeArreyMemory(void* ptr) {
    delete[] ptr;
}

extern "C" __attribute__ ((visibility ("default")))
void CalculateWrapper(void* model, const char* expression, const char* x_value) {
    static_cast<s21::Model*>(model)->calculate(expression, x_value);
}

extern "C" __attribute__ ((visibility ("default")))
double GetResultWrapper(void* model) {
    return static_cast<s21::Model*>(model)->result();
}

extern "C" __attribute__ ((visibility ("default")))
int GetStatusWrapper(void* model) {
    return static_cast<int>(static_cast<s21::Model*>(model)->status());
}

extern "C" __attribute__ ((visibility ("default")))
const char* GetExpressionWrapper(void* model) {
    std::string expression = static_cast<s21::Model*>(model)->getExpression();
    char* c_str = new char[expression.size() + 1];
    std::strcpy(c_str, expression.c_str());
    return c_str;
} 

extern "C" __attribute__ ((visibility ("default")))
const char* GetPolishWrapper(void* model) {
    std::string polish = static_cast<s21::Model*>(model)->getReversePolish();
    char* c_str = new char[polish.size() + 1];
    std::strcpy(c_str, polish.c_str());
    return c_str;
} 

extern "C" __attribute__ ((visibility ("default")))
void ResetWrapper(void* model) {
    static_cast<s21::Model*>(model)->calcReset();
}

extern "C" __attribute__ ((visibility ("default")))
void CalculateVectorsWithPointsWrapper(void* model, const char* expression, double x_begin, double x_end) {
    static_cast<s21::Model*>(model)->calcVectorsWithPoints(expression, x_begin, x_end);
}

extern "C" __attribute__ ((visibility ("default")))
double* GetVectorXWrapper(void* model) {
    std::vector<double>& vector_x = static_cast<s21::Model*>(model)->getVectorX();
    double* result = new double[vector_x.size()];
    std::copy(vector_x.begin(), vector_x.end(), result);
    return result;
}

extern "C" __attribute__ ((visibility ("default")))
double* GetVectorYWrapper(void* model) {
    std::vector<double>& vector_y = static_cast<s21::Model*>(model)->getVectorY();
    double* result = new double[vector_y.size()];
    std::copy(vector_y.begin(), vector_y.end(), result);
    return result;
}

extern "C" __attribute__ ((visibility ("default")))
int GetVectorSizeWrapper(void* model) {
    std::vector<double>& vector_y = static_cast<s21::Model*>(model)->getVectorY();
    return vector_y.size();
}