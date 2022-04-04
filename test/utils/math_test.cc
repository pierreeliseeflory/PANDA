#include <gtest/gtest.h>

#include "src/utils/math.hpp"

TEST(BinomialTest, BasicAssertions)
{
    EXPECT_EQ(binomialCoefficient(4, 2), 6);
    EXPECT_EQ(binomialCoefficient(10, 5), 252);
}

TEST(BinomialTest, EdgeValuesAssertions)
{
    EXPECT_EQ(binomialCoefficient(5, 0), 1);
    EXPECT_EQ(binomialCoefficient(7, 7), 1);
}

TEST(BinomialTest, IncorrectValuesAssertions)
{
    EXPECT_THROW(binomialCoefficient(3, 7), std::invalid_argument);
    EXPECT_THROW(binomialCoefficient(-1, 3), std::invalid_argument);
    EXPECT_THROW(binomialCoefficient(3, -1), std::invalid_argument);
}

TEST(MonomialToIndexTest, BasicAssertions)
{
    std::vector<unsigned int> monomial1 = {0, 3, 0};
    EXPECT_EQ(monomialToIndex(3, 3, monomial1), 9);
    std::vector<unsigned int> monomial2 = {1, 1, 1};
    EXPECT_EQ(monomialToIndex(3, 3, monomial2), 14);
    std::vector<unsigned int> monomial3 = {1, 0, 0, 0, 1};
    EXPECT_EQ(monomialToIndex(3, 5, monomial3), 36);
    std::vector<unsigned int> monomial4 = {0, 0, 3};
    EXPECT_EQ(monomialToIndex(3, 3, monomial4), 19);
}

TEST(MonomialToIndexTest, EdgeValuesAssertions)
{
    std::vector<unsigned int> monomial1 = {0, 0, 0};
    EXPECT_EQ(monomialToIndex(3, 3, monomial1), 0);
    std::vector<unsigned int> monomial2 = {0, 0, 3};
    EXPECT_EQ(monomialToIndex(3, 3, monomial2), 19);
    std::vector<unsigned int> monomial3 = {0};
    EXPECT_EQ(monomialToIndex(3, 1, monomial3), 0);
}

TEST(MonomialToIndexTest, IncorrectValuesAssertions)
{
    std::vector<unsigned int> monomial1 = {0, 0, 0};
    EXPECT_THROW(monomialToIndex(3, 2, monomial1), std::invalid_argument);
    EXPECT_THROW(monomialToIndex(3, 5, monomial1), std::invalid_argument);
    std::vector<unsigned int> monomial2 = {1, 0, 3};
    EXPECT_THROW(monomialToIndex(3, 3, monomial2), std::invalid_argument);
}

TEST(IndexToMonomialTest, BasicAssertions)
{
    std::vector<unsigned int> monomial1 = {0, 3, 0};
    EXPECT_EQ(indexToMonomial(3, 3, 9), monomial1);
    std::vector<unsigned int> monomial2 = {1, 1, 1};
    EXPECT_EQ(indexToMonomial(3, 3, 14), monomial2);
    std::vector<unsigned int> monomial3 = {1, 0, 0, 0, 1};
    EXPECT_EQ(indexToMonomial(3, 5, 36), monomial3);
    std::vector<unsigned int> monomial4 = {0, 0, 3};
    EXPECT_EQ(indexToMonomial(3, 3, 19), monomial4);
}

TEST(IndexToMonomialTest, EdgeValuesAssertions)
{
    std::vector<unsigned int> monomial1 = {0, 0, 0};
    EXPECT_EQ(indexToMonomial(3, 3, 0), monomial1);
    std::vector<unsigned int> monomial2 = {0, 0, 3};
    EXPECT_EQ(indexToMonomial(3, 3, 19), monomial2);
}

TEST(IndexToMonomialTest, IncorrectValuesAssertions)
{
    EXPECT_THROW(indexToMonomial(3, 2, -1), std::invalid_argument);
    EXPECT_THROW(indexToMonomial(3, 5, 128), std::invalid_argument);
}