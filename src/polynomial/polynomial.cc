#include "polynomial.hpp"

#include <sstream>
#include <stdexcept>

void MultiVariatePolynomial::print() const
{
    for (auto element : this->coefficients)
        std::cout << element << " ";

    std::cout << std::endl;
}

std::string MultiVariatePolynomial::to_string() const
{
    std::vector<NTL::ZZ_p> param(this->getArity());

    std::stringstream ss;

    for (int i = 0; i < this->getMaxNbElements(); i++)
    {
        if (this->coefficients.at(i) != 0)
        {
            int temp = i;
            ss << this->coefficients.at(i) << " (";
            for (int variable = this->getArity() - 1; variable >= 0; variable--)
            {

                int factor = binomialCoefficient(this->degree + variable, this->degree);
                ss << "x_" << variable << "^" << temp / factor << " ";
                temp %= factor;
            }
            ss << ") ";
        }
    }

    if (ss.rdbuf()->in_avail() == 0)
        ss << "0";
    return ss.str();
}

void MultiVariatePolynomial::setElement(int index, NTL::ZZ_p value)
{
    if (index > getMaxNbElements())
        throw std::invalid_argument("The sum of powers must be lower than that of the whole polynomial");
    coefficients.at(index) = value;
};

void MultiVariatePolynomial::setElement(std::vector<int> monomial, NTL::ZZ_p value)
{
    if (monomial.size() != this->arity)
    {
        throw std::invalid_argument("The monomial set must have the same arity as th epolynomial");
    }
    int index = 0;
    for (int variable = 0; variable < monomial.size(); ++variable)
    {
        if (monomial.at(variable) > this->degree)
            throw std::invalid_argument("Individual variable powers must be lower than that of the polynomial");
        index += monomial.at(variable) * binomialCoefficient(this->degree + variable, this->degree);
    }
    setElement(index, value);
};

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

NTL::ZZ_p MultiVariatePolynomial::getElement(int index) const
{
    if (index >= maxNbElements || index < 0)
        throw std::invalid_argument("Incorrect index");
    return coefficients.at(index);
}

MultiVariatePolynomial MultiVariatePolynomial::add(const MultiVariatePolynomial &other) const
{
    if (arity != other.getArity())
        throw std::invalid_argument("Can't add polynomial with different arity");
    if (degree != other.getDegree())
        throw std::invalid_argument("Can't add polynomial with different degree");
    if (order != other.getOrder())
        throw std::invalid_argument("Can't add polynomial with different order");

    std::vector<NTL::ZZ_p> new_values;

    for (int index = 0; index < this->getMaxNbElements(); index++)
        new_values.push_back(getElement(index) + other.getElement(index));
    return MultiVariatePolynomial(arity, degree, order, new_values);
}

MultiVariatePolynomial MultiVariatePolynomial::operator+(const MultiVariatePolynomial &other) const
{
    return this->add(other);
}

MultiVariatePolynomial MultiVariatePolynomial::sub(const MultiVariatePolynomial &other) const
{
    if (arity != other.getArity())
        throw std::invalid_argument("Can't substract polynomial with different arity");
    if (degree != other.getDegree())
        throw std::invalid_argument("Can't substract polynomial with different degree");
    if (order != other.getOrder())
        throw std::invalid_argument("Can't substract polynomial with different order");

    std::vector<NTL::ZZ_p> new_values;

    for (int index = 0; index < this->getMaxNbElements(); index++)
        new_values.push_back(getElement(index) - other.getElement(index));
    return MultiVariatePolynomial(arity, degree, order, new_values);
}

MultiVariatePolynomial MultiVariatePolynomial::operator-(const MultiVariatePolynomial &other) const
{
    return this->sub(other);
}

NTL::ZZ_p MultiVariatePolynomial::evaluate(std::vector<NTL::ZZ_p> point) const
{
    if (point.size() != this->arity)
        throw std::invalid_argument("Can't evaluate polynomial on vector of incorrect size");

    NTL::ZZ_p result;

    for (int monomial = 0; monomial < this->getMaxNbElements(); monomial++)
    {
        if (this->coefficients.at(monomial) != 0)
        {
            int temp = monomial;
            NTL::ZZ_p temp_result(this->coefficients.at(monomial));
            for (int variable = this->getArity() - 1; variable >= 0; variable--)
            {
                NTL::ZZ_p temp_temp_result;
                int factor = binomialCoefficient(this->degree + variable, this->degree);
                NTL::power(temp_temp_result, point.at(variable), (temp / factor));
                temp_result *= temp_temp_result;
                temp %= factor;
            }
            result += temp_result;
        }
    }
    return result;
}