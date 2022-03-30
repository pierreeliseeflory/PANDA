#ifndef REED_MULLER_HPP
#define REED_MULLER_HPP

#include "codeword.hpp"
#include "message.hpp"

class ReedMuller
{
private:
    int q; // must be a prime power (alphabet size)
    int n; // arity
    int d; // degree (d < q -1)

public:
    ReedMuller(/* args */);
    ~ReedMuller();

    void encode();
    void decode();
};

ReedMuller::ReedMuller(/* args */)
{
}

ReedMuller::~ReedMuller()
{
}

#endif /* REED_MULLER_HPP */
