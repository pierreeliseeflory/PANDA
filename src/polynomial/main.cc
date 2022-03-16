#include <iostream>

#include <NTL/ZZ_p.h>

#include "polynomial.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    NTL::ZZ p((long)17);
    NTL::ZZ_p::init(p);
    NTL::ZZ_p k((long)6);

    std::cout << k << std::endl;
    std::cout << k * 2 << std::endl;
    std::cout << k * 3 << std::endl;
    std::cout << k * 4 << std::endl;

    int arity = 3;
    int degree = 5;
    int order = 2;

    MultiVariatePolynomial poly(arity, degree, order);

    poly.print();

    std::cout << poly.to_string() << std::endl;

    std::cout << poly.getMaxNbElements() << std::endl;

    return 0;
}