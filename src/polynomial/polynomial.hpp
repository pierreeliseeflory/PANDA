#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <iostream>
#include <vector>
#include <math.h>

#include <NTL/ZZ_p.h>

int binomialCoefficient(int n, int k);

class MultiVariatePolynomial
{
public:
    MultiVariatePolynomial(int arity, int degree, int order) : arity(arity), degree(degree), order(order), maxNbElements(binomialCoefficient(degree + arity, degree)), coefficients(maxNbElements)
    {
        NTL::ZZ p((long)order);
        NTL::ZZ_p::init(p);
    }
    MultiVariatePolynomial() = delete;

    int getArity()
    {
        return this->arity;
    };
    void setArity(int arity)
    {
        this->arity = arity;
    };
    int getDegree()
    {
        return this->degree;
    };
    void setDegree(int degree)
    {
        this->degree = degree;
    };
    int getOrder()
    {
        return this->order;
    };
    void setOrder(int order)
    {
        this->order = order;
    };

    int getMaxNbElements()
    {
        return this->maxNbElements;
    }

    void print();

    std::string to_string();

private:
    int arity;
    int degree;
    int order;
    int maxNbElements;
    std::vector<NTL::ZZ_p> coefficients;
};

#endif // __POLYNOMIAL_H__