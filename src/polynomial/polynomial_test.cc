#include <gtest/gtest.h>

#include "polynomial.hpp"

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
