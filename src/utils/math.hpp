#ifndef MATH_HPP
#define MATH_HPP

#include <stdexcept>
#include <vector>

int binomialCoefficient(int n, int k);

int monomialToIndex(int degree, int arity, std::vector<unsigned int>& values);

std::vector<unsigned int> indexToMonomial(int degree, int arity, int index);

template<typename T>
T squareAndMultiply(T base, unsigned int exponent) {
    T res = 1;
    while (exponent > 0) {
        if (exponent & 1)
            res *= base;
        else
            res *= res;
        exponent >>= 1;
    }
    return res;
}

#endif /* MATH_HPP */
