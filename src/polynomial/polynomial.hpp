#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <iostream>
#include <vector>
#include <math.h>
#include <NTL/ZZ_p.h>

#include "src/utils/math.hpp"

// TODO : REFACTOR -> use recursive polynomials
// TODO : Templatize the class

class MultiVariatePolynomial
{
public:
    MultiVariatePolynomial(unsigned int arity, unsigned int degree, unsigned int order) : arity(arity), degree(degree), order(order), maxNbElements(binomialCoefficient(degree + arity, degree)), coefficients(maxNbElements)
    {
        NTL::ZZ p((long)order);
        NTL::ZZ_p::init(p);
    }
    MultiVariatePolynomial(unsigned int arity, unsigned int degree, unsigned int order, std::vector<NTL::ZZ_p> values) : MultiVariatePolynomial(arity, degree, order)
    {
        if (values.size() != this->getMaxNbElements())
            throw std::invalid_argument("Incorrect number of values provided");
        coefficients = values;
    }
    MultiVariatePolynomial() = delete;

    unsigned int getArity() const
    {
        return this->arity;
    };
    void setArity(unsigned int arity)
    {
        this->arity = arity;
    };
    unsigned int getDegree() const
    {
        return this->degree;
    };
    void setDegree(unsigned int degree)
    {
        this->degree = degree;
    };
    unsigned int getOrder() const
    {
        return this->order;
    };
    void setOrder(unsigned int order)
    {
        this->order = order;
    };

    unsigned int getMaxNbElements() const
    {
        return this->maxNbElements;
    };

    void setElement(std::vector<unsigned int> monomial, NTL::ZZ_p value);

    void setElement(unsigned int index, NTL::ZZ_p value);

    NTL::ZZ_p getElement(std::vector<unsigned int> monomial) const;

    NTL::ZZ_p getElement(unsigned int index) const;

    void print() const;

    std::string to_string() const;

    MultiVariatePolynomial add(const MultiVariatePolynomial &other) const;
    MultiVariatePolynomial operator+(const MultiVariatePolynomial &other) const;

    MultiVariatePolynomial sub(const MultiVariatePolynomial &other) const;
    MultiVariatePolynomial operator-(const MultiVariatePolynomial &other) const;

    NTL::ZZ_p evaluate(std::vector<NTL::ZZ_p> point) const;

private:
    unsigned int arity;
    unsigned int degree;
    unsigned int order;
    unsigned int maxNbElements;
    std::vector<NTL::ZZ_p> coefficients;
};

#endif // __POLYNOMIAL_H__