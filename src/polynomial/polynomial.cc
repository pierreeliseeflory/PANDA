#include "polynomial.hpp"

#include <sstream>
#include <stdexcept>

void MultiVariatePolynomial::print() const
{
    for (auto element : this->coefficients)
        std::cout << element << " ";

    std::cout << std::endl;
}

int MultiVariatePolynomial::getPowers(int index)
{
    std::stringstream ss;
    for (unsigned int var = 0; var < this->getArity(); var++)
    {
    }
    return 1;
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
            for (unsigned int variable = 0; variable < this->arity; variable++)
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

void MultiVariatePolynomial::setElement(std::vector<unsigned int> &monomial, NTL::ZZ_p value)
{
    setElement(monomialToIndex(this->degree, this->arity, monomial), value);
};

NTL::ZZ_p MultiVariatePolynomial::getElement(unsigned int index) const
{
    if (index >= maxNbElements || index < 0)
        throw std::invalid_argument("Incorrect index");
    return coefficients.at(index);
}

NTL::ZZ_p MultiVariatePolynomial::getElement(std::vector<unsigned int> &monomial) const
{
    return getElement(monomialToIndex(this->degree, this->arity, monomial));
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

NTL::ZZ_p MultiVariatePolynomial::evaluate(std::vector<NTL::ZZ_p> &point) const
{
    if (point.size() != this->arity)
        throw std::invalid_argument("Can't evaluate polynomial on vector of incorrect size");

    NTL::ZZ_p result;

    for (unsigned int index = 0; index < this->getMaxNbElements(); index++)
    {
        if (this->coefficients.at(index) != 0)
        {
            NTL::ZZ_p temp(this->coefficients.at(index));
            std::vector<unsigned int> monomial = indexToMonomial(this->degree, this->arity, index);
            for (int variable = 0; variable < this->getArity(); variable++)
            {
                temp *= NTL::power(point.at(variable), monomial.at(variable));
            }
            result += temp;
        }
    }
    return result;
}
