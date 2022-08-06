#include <iostream>
#include <iterator>

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

int monomialToIndex(int degree, unsigned int arity, std::vector<unsigned int> &monomial)
{
    if (monomial.size() != arity)
        throw std::invalid_argument("The monomial must have the same arity as the polynomial");
    int total_degree = 0;
    for (std::vector<unsigned int>::iterator it = monomial.begin(); it != monomial.end(); ++it)
        total_degree += *it;

    if (total_degree > degree)
        throw std::invalid_argument("The monomial has incorrect degree");
    int index = 0;
    for (int var = arity - 1; var >= 0; var--)
    {
        for (unsigned int i = 0; i < monomial.at(var); i++)
            index += binomialCoefficient(degree + var - i, degree - i);
        degree -= monomial.at(var);
    }
    return index;
}

std::vector<unsigned int> indexToMonomial(int degree, int arity, int index)
{
    std::vector<unsigned int> monomial(arity);
    if (index < 0 || index >= binomialCoefficient(degree + arity, degree))
        throw std::invalid_argument("Invalid index");
    for (int variable = arity - 1; variable >= 0; variable--)
    {
        int variable_effect = 0;
        int power = 0;
        for (power = 0; power <= degree; power++)
        {
            int temp = binomialCoefficient(degree + variable - power, degree - power);
            if (index / (variable_effect + temp) > 0)
                variable_effect += temp;
            else
                break;
        }
        index -= variable_effect;
        degree -= power;
        monomial.at(variable) = power;
    }
    return monomial;
}
