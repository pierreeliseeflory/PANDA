#ifndef REED_MULLER_HPP
#define REED_MULLER_HPP

// #include "codeword.hpp"
// #include "message.hpp"
#include "src/polynomial/polynomial.hpp"
#include "src/utils/math.hpp"

typedef std::vector<NTL::ZZ_p> message;

// should probably turn that into a namespace instead
// class ReedMuller
// {
// private:
//     int q; // must be a prime power (alphabet size)
//     int n; // arity
//     int d; // degree (d < q -1)

// public:
//     ReedMuller(message& message, int q, int n, int d);
//     ~ReedMuller();

//     vostd::vector<NTL::ZZ_p>id encode(MultiVariatePolynomial& poly);
//     void decode();
// };

// ReedMuller::ReedMuller(message& message, int q, int n, int d) : q(q), n(n), d(d)
// {
//     // potentially include padding to allow any size of message
//     MultiVariatePolynomial poly(n, d, q, message);
//     encode(poly);
// }

// ReedMuller::~ReedMuller()
// {
// }

namespace ReedMuller {
    std::vector<NTL::ZZ_p> encode(message& message, int q, int n, int d) {
        MultiVariatePolynomial poly(n, d, q, message);
        std::vector<NTL::ZZ_p> points;
        std::vector<long> exponents;
        for (int i = 0; i < n; i++)
        {
            exponents.push_back(squareAndMultiply((long)q, i));
        }
        for (int index = 0; index < squareAndMultiply((long)q, n); index++)
        {
            std::vector<NTL::ZZ_p> point;
            for (int i = 0; i < n; i++)
            {
                point.push_back((NTL::ZZ_p)((index / exponents.at(i)) % q));
            }
            points.push_back(poly.evaluate(point));
        }
        return points;
    }
}


#endif /* REED_MULLER_HPP */
