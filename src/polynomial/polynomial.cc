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
    bool first = true;

    for (unsigned int i = 0; i < this->getMaxNbElements(); i++)
    {
        if (this->coefficients.at(i) != 0)
        {
            if (first == true)
                first = false;
            else
                ss << "+ ";
            unsigned int temp = i;
            ss << this->coefficients.at(i) << " * (";
            std::vector<unsigned int> monomial = indexToMonomial(this->degree, this->arity, i);
            for (int variable = 0; variable < this->arity; variable++)
                ss << "x_" << variable + 1 << "^" << monomial.at(variable) << " ";
            ss << ") ";
        }
    }

    if (ss.rdbuf()->in_avail() == 0)
        ss << "0";
    return ss.str();
}

void MultiVariatePolynomial::setElement(unsigned int index, NTL::ZZ_p value)
{
    if (index > getMaxNbElements())
        throw std::invalid_argument("The sum of powers must be lower than that of the whole polynomial");
    coefficients.at(index) = value;
};

void MultiVariatePolynomial::setElement(std::vector<unsigned int> monomial, NTL::ZZ_p value)
{
    setElement(monomialToIndex(this->degree, this->arity, monomial), value);
};

NTL::ZZ_p MultiVariatePolynomial::getElement(unsigned int index) const
{
    if (index >= maxNbElements || index < 0)
        throw std::invalid_argument("Incorrect index");
    std::cout << index << std::endl;
    std::cout << coefficients.at(0) << std::endl;
    std::cout << coefficients.at(index) << std::endl;
    return coefficients.at(index);
}

NTL::ZZ_p MultiVariatePolynomial::getElement(std::vector<unsigned int> monomial) const
{
    getElement(monomialToIndex(this->degree, this->arity, monomial));
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

    for (unsigned int index = 0; index < this->getMaxNbElements(); index++)
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

    for (unsigned int index = 0; index < this->getMaxNbElements(); index++)
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

    for (unsigned int monomial = 0; monomial < this->getMaxNbElements(); monomial++)
    {
        if (this->coefficients.at(monomial) != 0)
        {
            unsigned int temp = monomial;
            NTL::ZZ_p temp_result(this->coefficients.at(monomial));
            for (int variable = this->getArity() - 1; variable >= 0; variable--)
            {
                NTL::ZZ_p temp_temp_result;
                unsigned int factor = binomialCoefficient(this->degree + variable, this->degree);
                NTL::power(temp_temp_result, point.at(variable), (temp / factor));
                temp_result *= temp_temp_result;
                temp %= factor;
            }
            result += temp_result;
        }
    }
    return result;
}