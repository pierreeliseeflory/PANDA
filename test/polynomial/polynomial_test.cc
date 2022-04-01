#include <gtest/gtest.h>

#include "src/polynomial/polynomial.hpp"

TEST(ToStringTest, ZeroPolynomial)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    MultiVariatePolynomial poly(arity, degree, order);
    EXPECT_EQ(poly.to_string(), std::string("0"));
}

TEST(ToStringTest, SimplePolynomial)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.to_string(), std::string("6 * (x_0^0 ) + 2 * (x_0^2 ) "));
}

TEST(ToStringTest, ComplexPolynomial)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 7;
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.to_string(), std::string(""));
}

/*
- tostring
- setElement (index, vector)
- getElement
- add +
- sub -
- evaluate
*/