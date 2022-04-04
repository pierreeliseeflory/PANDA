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
    NTL::ZZ_p::init((NTL::ZZ)7);
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.to_string(), std::string("6 * (x_1^0 ) + 2 * (x_1^2 ) "));
}

TEST(ToStringTest, ComplexPolynomial)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)7);
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.to_string(), std::string("1 * (x_1^0 x_2^0 x_3^0 ) + 1 * (x_1^1 x_2^0 x_3^0 ) + 1 * (x_1^2 x_2^0 x_3^0 ) + 1 * (x_1^3 x_2^0 x_3^0 ) + 1 * (x_1^0 x_2^1 x_3^0 ) + 1 * (x_1^1 x_2^1 x_3^0 ) + 1 * (x_1^2 x_2^1 x_3^0 ) + 1 * (x_1^0 x_2^2 x_3^0 ) + 1 * (x_1^1 x_2^2 x_3^0 ) + 1 * (x_1^0 x_2^3 x_3^0 ) + 1 * (x_1^0 x_2^0 x_3^1 ) + 1 * (x_1^1 x_2^0 x_3^1 ) + 1 * (x_1^2 x_2^0 x_3^1 ) + 1 * (x_1^0 x_2^1 x_3^1 ) + 1 * (x_1^1 x_2^1 x_3^1 ) + 1 * (x_1^0 x_2^2 x_3^1 ) + 1 * (x_1^0 x_2^0 x_3^2 ) + 1 * (x_1^1 x_2^0 x_3^2 ) + 1 * (x_1^0 x_2^1 x_3^2 ) + 1 * (x_1^0 x_2^0 x_3^3 ) "));
}

TEST(GetElementTest, BasicAssertions)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)7);
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    NTL::ZZ_p res;
    poly.getElement(2, res);
    EXPECT_EQ(res, NTL::ZZ_p(2));
    std::vector<unsigned int> monomial = {0};
    poly.getElement(monomial, res);
    EXPECT_EQ(res, NTL::ZZ_p(6));
}

// TEST(GetElementTest, IncorrectValuesAssertions)
// {
//     unsigned int arity = 1;
//     unsigned int degree = 2;
//     unsigned int order = 7;
//     std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
//     MultiVariatePolynomial poly(arity, degree, order, values);
//     EXPECT_THROW(poly.getElement(10), std::invalid_argument);
//     EXPECT_THROW(poly.getElement(-1), std::invalid_argument);
//     std::vector<unsigned int> monomial = {0, 1};
//     EXPECT_THROW(poly.getElement(monomial), std::invalid_argument);
// }

// TEST(SetElementTest, BasicAssertions)
// {
//     unsigned int arity = 3;
//     unsigned int degree = 3;
//     unsigned int order = 2;
//     MultiVariatePolynomial poly(arity, degree, order);
//     poly.setElement(9, NTL::ZZ_p(1));
//     EXPECT_EQ(poly.getElement(9), NTL::ZZ_p(1));
//     std::vector<unsigned int> monomial = {1, 1, 1};
//     poly.setElement(monomial, NTL::ZZ_p(1));
//     EXPECT_EQ(poly.getElement(monomial), NTL::ZZ_p(1));
// }

// TEST(SetElementTest, IncorrectValuesAssertions)
// {
//     unsigned int arity = 1;
//     unsigned int degree = 2;
//     unsigned int order = 7;
//     NTL::ZZ_p value = NTL::ZZ_p(1);
//     MultiVariatePolynomial poly(arity, degree, order);
//     EXPECT_THROW(poly.setElement(10, value), std::invalid_argument);
//     EXPECT_THROW(poly.setElement(-1, value), std::invalid_argument);
//     std::vector<unsigned int> monomial1 = {0, 1};
//     EXPECT_THROW(poly.setElement(monomial1, value), std::invalid_argument);
//     std::vector<unsigned int> monomial2 = {2, 0, 4};
//     EXPECT_THROW(poly.setElement(monomial2, value), std::invalid_argument);
// }

// field (wrapping)
// out of bounds

/*
- tostring
- setElement (index, vector)
- getElement
- add +
- sub -
- evaluate
*/