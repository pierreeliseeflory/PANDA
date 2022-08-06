#ifndef REED_MULLER_HPP
#define REED_MULLER_HPP

#include <algorithm>

// #include "codeword.hpp"
// #include "message.hpp"
#include "src/polynomial/polynomial.hpp"
#include "src/utils/math.hpp"

typedef std::vector<NTL::ZZ_p> message;

// struct message

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

namespace ReedMuller
{
    std::vector<NTL::ZZ_p> encode(message &message, int q, int n, int d)
    {
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

    NTL::ZZ_p decode(std::vector<NTL::ZZ_p> &codeword, int q, int n, int d, std::vector<NTL::ZZ_p> &desired_point)
    {
        NTL::ZZ_p::init((NTL::ZZ)q);

        unsigned int sampling_number = d + 1;
        std::vector<NTL::ZZ_p> random_point; // generate a random point over (F_q)^n
        while (random_point.size() != sampling_number)
            random_point.push_back(NTL::random_ZZ_p());
        std::vector<NTL::ZZ_p> arguments; // generate random distincts coefficient
        while (arguments.size() != sampling_number)
        {
            NTL::ZZ_p candidate = NTL::random_ZZ_p();
            if (std::find(arguments.begin(), arguments.end(), candidate) == arguments.end())
                arguments.push_back(candidate);
        }

        std::vector<std::vector<NTL::ZZ_p>> samples;
        for (int i = 0; i < sampling_number; i++)
        {
            std::vector<NTL::ZZ_p> image;
            for (int variable = 0; variable < n; variable++)
            {
                image.push_back(desired_point.at(variable) + arguments.at(i) * random_point.at(variable));
            }
            samples.push_back(image);
        }

        // recover the unique univariate polynomial h, deg h ≤ d, such that h(arguments[i]) = samples[i]
        // and evaluate it at 0

        NTL::ZZ_p res(0);

        for (int j = 0; j < sampling_number; ++j)
        {
            int index = 0;
            for (int variable = 0; variable < n; variable++)
                index += NTL::conv<int>(samples.at(j).at(variable)) * squareAndMultiply(q, variable);

            NTL::ZZ_p temp_res(codeword.at(index));

            for (int i = 0; i < sampling_number; ++i)
            {
                if (i != j)
                {
                    std::cout << " j " << j << " i " << i << " " << arguments.at(j) - arguments.at(i) << std::endl;
                    temp_res *= (-arguments.at(i)) / (arguments.at(j) - arguments.at(i));
                }
            }
            res += temp_res;
        }

        return res; // return h(0)
    }
}

#endif /* REED_MULLER_HPP */
