#include <iostream>

#include <NTL/ZZ_p.h>

#include "polynomial.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    NTL::ZZ p((long)17);
    NTL::ZZ_p::init(p);
    NTL::ZZ_p k(6);

    std::cout << k << std::endl;
    std::cout << k * 2 << std::endl;
    std::cout << k * 3 << std::endl;
    std::cout << k * 4 << std::endl;

    unsigned int arity = 3;
    unsigned int degree = 5;
    unsigned int order = 7;

    MultiVariatePolynomial poly(arity, degree, order);

    NTL::ZZ_p value(5);
    std::vector<unsigned int> monomial = {0, 3, 1};
    poly.setElement(monomial, value);

    poly.print();

    std::cout << poly.to_string() << std::endl;
    std::cout << poly.add(poly).to_string() << std::endl;
    std::cout << (poly + poly).to_string() << std::endl;
    std::cout << (poly - poly).to_string() << std::endl;

    std::cout << poly.getMaxNbElements() << std::endl;

    std::vector<NTL::ZZ_p> point = {NTL::ZZ_p(1), NTL::ZZ_p(1), NTL::ZZ_p(4)};
    std::cout << poly.evaluate(point) << std::endl;

    return 0;
}