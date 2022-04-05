#include <gtest/gtest.h>

#include "src/reed-muller/reed-muller.hpp"

TEST(EncodingTest, SimpleMessage)
{
    unsigned int arity = 1;
    unsigned int degree = 2;
    unsigned int order = 7;
    NTL::ZZ_p::init((NTL::ZZ)order);
    std::vector<NTL::ZZ_p> message = { NTL::ZZ_p(6), NTL::ZZ_p(0), NTL::ZZ_p(2) };
    std::vector<NTL::ZZ_p> codeword = { NTL::ZZ_p(6), NTL::ZZ_p(1), NTL::ZZ_p(0), NTL::ZZ_p(3), NTL::ZZ_p(3), NTL::ZZ_p(0), NTL::ZZ_p(1) };
    EXPECT_EQ(ReedMuller::encode(message, order, arity, degree), codeword);
}
