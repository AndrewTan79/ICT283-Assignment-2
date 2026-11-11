#ifndef STAT_H_INCLUDED
#define STAT_H_INCLUDED

#include "Vector.h"

/**
 * @brief Calculates the arithmetic mean of a set of values.
 *
 * @param value Vector containing the numbers.
 * @param n     Number of values to use. Must be greater than 0.
 * @return The sum of the values divided by n.
 */
float mean(const Vector<float>& value, int n);

/**
 * @brief Calculates the sum of squared differences from the mean.
 *
 * Used as an intermediate step when calculating standard deviation.
 *
 * @param value Vector containing the numbers.
 * @param n     Number of values to use.
 * @param mean  The mean that has already been calculated.
 * @return The sum of (value[i] - mean) squared.
 */
float sqSum(const Vector<float>& value, int n, float mean);

/**
 * @brief Calculates the sample standard deviation.
 *
 * @param sqSum Sum of squared differences (from the sqSum function).
 * @param n     Number of values. Must be greater than 1.
 * @return The square root of sqSum / (n - 1).
 */
float standardDV(float sqSum, int n);

/**
 * @brief Calculates the sum of a set of values.
 *
 * @param value Vector containing the numbers.
 * @param n     Number of values to use.
 * @return The total of the values.
 */
float total(const Vector<float>& value, int n);

/**
 * @brief Calculates the sample Pearson Correlation Coefficient.
 *
 * Measures the linear relationship between two sets of values.
 * Returns 0 if the denominator is zero (no variation in the data).
 *
 * @param x First set of values.
 * @param y Second set of values. Must be the same length as x.
 * @return The sample Pearson correlation coefficient.
 */
float sPCC(const Vector<float>& x, const Vector<float>& y);

/**
 * @brief Calculates the Mean Absolute Deviation (MAD).
 *
 * @param value Vector containing the numbers.
 * @param n     Number of values to use. Must be greater than 0.
 * @param mean  The mean that has already been calculated.
 * @return The average of the absolute differences from the mean.
 */
float mad(const Vector<float>& value, int n, float mean);

#endif // STAT_H_INCLUDED
