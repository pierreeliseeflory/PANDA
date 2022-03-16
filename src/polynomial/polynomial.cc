#include "polynomial.hpp"

#include <sstream>
#include <stdexcept>

void MultiVariatePolynomial::print()
{
    for (auto element : this->coefficients)
        std::cout << element << " ";

    std::cout << std::endl;
}

std::string MultiVariatePolynomial::to_string()
{
    std::vector<NTL::ZZ_p> param(this->getArity());

    std::stringstream ss;

    for (int i = 0; i < this->getMaxNbElements(); i++)
    {
        if (this->coefficients.at(i) != 0)
        {
            for (int k = 0; k < this->getArity(); k++)
            {
                ss << i % (k * order) << " ";
            }
            ss << this->coefficients.at(i);
        }
    }
    return ss.str();
}

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