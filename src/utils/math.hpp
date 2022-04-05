#ifndef MATH_HPP
#define MATH_HPP

#include <stdexcept>
#include <vector>

int binomialCoefficient(int n, int k);

int monomialToIndex(int degree, int arity, std::vector<unsigned int>& values);

std::vector<unsigned int> indexToMonomial(int degree, int arity, int index);

#endif /* MATH_HPP */
