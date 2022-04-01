#include "math.hpp"

int binomialCoefficient(int n, int k)
{
    if (k > n)
        throw std::invalid_argument("Binomial coefficient: n must be greater than k");
    if (k < 0 || n < 0)
        throw std::invalid_argument("Binomial coefficient: n and k must be non-negatives");
    if (k == 0 || k == n)
        return 1;
    return binomialCoefficient(n - 1, k - 1) + binomialCoefficient(n - 1, k);
}