
#include "Stat.h"
#include <cmath>
#include "Vector.h"
#include <iomanip>


float mean(const Vector<float>& value, int n)
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        sum += value[i];
    }

    return sum / n;
}

float sqSum(const Vector<float>& value, int n, float mean)
{
    float sqSum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        sqSum += (value[i] - mean) * (value[i]- mean);
    }

    return sqSum;
}

float standardDV(float sqSum, int n)
{
    return sqrt(sqSum / (n-1));
}

float total(const Vector<float>& value, int n)
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        sum += value[i];
    }

    return sum;
}

float sPCC(const Vector<float> & x, const Vector<float> & y)
{
    int n = x.Size();
    float xSum = 0.0;
    float ySum = 0.0;
    float xySum = 0.0;
    float x2Sum = 0.0;
    float y2Sum = 0.0;

    for (int i = 0; i<n; i++)
    {
        xSum += x[i];
        ySum += y[i];
        xySum += x[i]*y[i];
        x2Sum += x[i]*x[i];
        y2Sum += y[i]*y[i];
    }

    float nominator = n*xySum - (xSum*ySum);
    float denominator = std::sqrt((n*x2Sum-xSum*xSum)*(n*y2Sum-ySum*ySum));

    if (denominator == 0)
        return 0;

    return nominator / denominator;
}

float mad(const Vector<float>& value, int n, float mean)
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        float diff = value[i] - mean;
        if (diff < 0)
            diff = -diff;          // absolute value
        sum += diff;
    }
    return sum / n;
}
