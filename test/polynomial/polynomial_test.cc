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
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.to_string(), std::string("6 * (x_1^0 ) + 2 * (x_1^2 ) "));
}

TEST(ToStringTest, ComplexPolynomial)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.to_string(), std::string("1 * (x_1^0 x_2^0 x_3^0 ) + 1 * (x_1^1 x_2^0 x_3^0 ) + 1 * (x_1^2 x_2^0 x_3^0 ) + 1 * (x_1^3 x_2^0 x_3^0 ) + 1 * (x_1^0 x_2^1 x_3^0 ) + 1 * (x_1^1 x_2^1 x_3^0 ) + 1 * (x_1^2 x_2^1 x_3^0 ) + 1 * (x_1^0 x_2^2 x_3^0 ) + 1 * (x_1^1 x_2^2 x_3^0 ) + 1 * (x_1^0 x_2^3 x_3^0 ) + 1 * (x_1^0 x_2^0 x_3^1 ) + 1 * (x_1^1 x_2^0 x_3^1 ) + 1 * (x_1^2 x_2^0 x_3^1 ) + 1 * (x_1^0 x_2^1 x_3^1 ) + 1 * (x_1^1 x_2^1 x_3^1 ) + 1 * (x_1^0 x_2^2 x_3^1 ) + 1 * (x_1^0 x_2^0 x_3^2 ) + 1 * (x_1^1 x_2^0 x_3^2 ) + 1 * (x_1^0 x_2^1 x_3^2 ) + 1 * (x_1^0 x_2^0 x_3^3 ) "));
}

TEST(GetElementTest, BasicAssertions)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.getElement(2), NTL::ZZ_p(2));
    std::vector<unsigned int> monomial = {0};
    EXPECT_EQ(poly.getElement(monomial), NTL::ZZ_p(6));
}

TEST(GetElementTest, IncorrectValuesAssertions)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_THROW(poly.getElement(10), std::invalid_argument);
    EXPECT_THROW(poly.getElement(-1), std::invalid_argument);
    std::vector<unsigned int> monomial = {0, 1};
    EXPECT_THROW(poly.getElement(monomial), std::invalid_argument);
}

TEST(SetElementTest, BasicAssertions)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 2;
    MultiVariatePolynomial poly(arity, degree, order);
    poly.setElement(9, NTL::ZZ_p(1));
    EXPECT_EQ(poly.getElement(9), NTL::ZZ_p(1));
    std::vector<unsigned int> monomial = {1, 1, 1};
    poly.setElement(monomial, NTL::ZZ_p(1));
    EXPECT_EQ(poly.getElement(monomial), NTL::ZZ_p(1));
}

TEST(SetElementTest, IncorrectValuesAssertions)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    NTL::ZZ_p value = NTL::ZZ_p(1);
    MultiVariatePolynomial poly(arity, degree, order);
    EXPECT_THROW(poly.setElement(10, value), std::invalid_argument);
    EXPECT_THROW(poly.setElement(-1, value), std::invalid_argument);
    std::vector<unsigned int> monomial1 = {0, 1};
    EXPECT_THROW(poly.setElement(monomial1, value), std::invalid_argument);
    std::vector<unsigned int> monomial2 = {2, 0, 4};
    EXPECT_THROW(poly.setElement(monomial2, value), std::invalid_argument);
}

TEST(AddTest, BasicAssertions)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 3;
    NTL::ZZ_p::init((NTL::ZZ)order);
    MultiVariatePolynomial poly1(arity, degree, order);
    MultiVariatePolynomial poly2(arity, degree, order);
    std::vector<unsigned int> monomial1 = {0, 0, 0};
    std::vector<unsigned int> monomial2 = {1, 1, 1};
    std::vector<unsigned int> monomial3 = {0, 0, 3};
    poly1.setElement(monomial1, NTL::ZZ_p(1));
    poly1.setElement(monomial2, NTL::ZZ_p(2));
    poly1.setElement(monomial3, NTL::ZZ_p(1));
    poly2.setElement(monomial2, NTL::ZZ_p(1));
    poly2.setElement(monomial3, NTL::ZZ_p(1));
    EXPECT_EQ((poly1.add(poly2)).to_string(), "1 * (x_1^0 x_2^0 x_3^0 ) + 2 * (x_1^0 x_2^0 x_3^3 ) ");
    EXPECT_EQ((poly1 + poly2).to_string(), "1 * (x_1^0 x_2^0 x_3^0 ) + 2 * (x_1^0 x_2^0 x_3^3 ) ");
}

TEST(AddTest, IncorrectValuesAssertions)
{
    unsigned int arity1 = 1;
    unsigned int arity2 = 3;
    unsigned int degree1 = 2;
    unsigned int degree2 = 3;
    unsigned int order1 = 2;
    unsigned int order2 = 7;
    MultiVariatePolynomial poly(arity1, degree1, order1);
    MultiVariatePolynomial poly1(arity2, degree1, order1);
    MultiVariatePolynomial poly2(arity1, degree2, order1);
    MultiVariatePolynomial poly3(arity1, degree1, order2);
    EXPECT_THROW(poly.add(poly1), std::invalid_argument);
    EXPECT_THROW(poly.add(poly2), std::invalid_argument);
    EXPECT_THROW(poly.add(poly3), std::invalid_argument);
    EXPECT_THROW(poly + poly1, std::invalid_argument);
    EXPECT_THROW(poly + poly2, std::invalid_argument);
    EXPECT_THROW(poly + poly3, std::invalid_argument);
}

TEST(SubTest, BasicAssertions)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 3;
    NTL::ZZ_p::init((NTL::ZZ)order);
    MultiVariatePolynomial poly1(arity, degree, order);
    MultiVariatePolynomial poly2(arity, degree, order);
    std::vector<unsigned int> monomial1 = {0, 0, 0};
    std::vector<unsigned int> monomial2 = {1, 1, 1};
    std::vector<unsigned int> monomial3 = {0, 0, 3};
    poly1.setElement(monomial1, NTL::ZZ_p(1));
    poly1.setElement(monomial2, NTL::ZZ_p(2));
    poly1.setElement(monomial3, NTL::ZZ_p(1));
    poly2.setElement(monomial2, NTL::ZZ_p(1));
    poly2.setElement(monomial3, NTL::ZZ_p(1));
    EXPECT_EQ((poly1.sub(poly2)).to_string(), "1 * (x_1^0 x_2^0 x_3^0 ) + 1 * (x_1^1 x_2^1 x_3^1 ) ");
    EXPECT_EQ((poly1 - poly2).to_string(), "1 * (x_1^0 x_2^0 x_3^0 ) + 1 * (x_1^1 x_2^1 x_3^1 ) ");
}

TEST(SubTest, IncorrectValuesAssertions)
{
    unsigned int arity1 = 1;
    unsigned int arity2 = 3;
    unsigned int degree1 = 2;
    unsigned int degree2 = 3;
    unsigned int order1 = 2;
    unsigned int order2 = 7;
    MultiVariatePolynomial poly(arity1, degree1, order1);
    MultiVariatePolynomial poly1(arity2, degree1, order1);
    MultiVariatePolynomial poly2(arity1, degree2, order1);
    MultiVariatePolynomial poly3(arity1, degree1, order2);
    EXPECT_THROW(poly.sub(poly1), std::invalid_argument);
    EXPECT_THROW(poly.sub(poly2), std::invalid_argument);
    EXPECT_THROW(poly.sub(poly3), std::invalid_argument);
    EXPECT_THROW(poly - poly1, std::invalid_argument);
    EXPECT_THROW(poly - poly2, std::invalid_argument);
    EXPECT_THROW(poly - poly3, std::invalid_argument);
}

TEST(EvaluationTest, BasicAssertions)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> point1 = {NTL::ZZ_p(0)};
    std::vector<NTL::ZZ_p> point2 = {NTL::ZZ_p(7)};
    std::vector<NTL::ZZ_p> point3 = {NTL::ZZ_p(5)};
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order, values);
    EXPECT_EQ(poly.evaluate(point1), NTL::ZZ_p(6));
    EXPECT_EQ(poly.evaluate(point2), NTL::ZZ_p(6));
    EXPECT_EQ(poly.evaluate(point3), NTL::ZZ_p(0));
}

TEST(EvaluationTest, AdvancedAssertions)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 3;
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> point1 = {NTL::ZZ_p(0), NTL::ZZ_p(0), NTL::ZZ_p(0)};
    std::vector<NTL::ZZ_p> point2 = {NTL::ZZ_p(7), NTL::ZZ_p(0), NTL::ZZ_p(0)};
    std::vector<NTL::ZZ_p> point3 = {NTL::ZZ_p(0), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    std::vector<NTL::ZZ_p> point4 = {NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(1)};
    std::vector<NTL::ZZ_p> values = {NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2)};
    MultiVariatePolynomial poly(arity, degree, order);
    std::vector<unsigned int> monomial1 = {0, 0, 0};
    std::vector<unsigned int> monomial2 = {1, 1, 1};
    std::vector<unsigned int> monomial3 = {0, 0, 3};
    poly.setElement(monomial1, NTL::ZZ_p(1));
    poly.setElement(monomial2, NTL::ZZ_p(2));
    poly.setElement(monomial3, NTL::ZZ_p(1));
    EXPECT_EQ(poly.evaluate(point1), NTL::ZZ_p(1));
    EXPECT_EQ(poly.evaluate(point2), NTL::ZZ_p(1));
    EXPECT_EQ(poly.evaluate(point3), NTL::ZZ_p(0));
    EXPECT_EQ(poly.evaluate(point4), NTL::ZZ_p(1));
}

TEST(EvaluationTest, IncorrectValuesAssertions)
{
    unsigned int arity = 3;
    unsigned int degree = 3;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> point1 = {NTL::ZZ_p(0), NTL::ZZ_p(0)};
    std::vector<NTL::ZZ_p> point2 = {NTL::ZZ_p(7), NTL::ZZ_p(0), NTL::ZZ_p(0), NTL::ZZ_p(0)};
    MultiVariatePolynomial poly(arity, degree, order);
    EXPECT_THROW(poly.evaluate(point1), std::invalid_argument);
    EXPECT_THROW(poly.evaluate(point2), std::invalid_argument);
}
