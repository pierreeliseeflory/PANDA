#include <iostream>

#include <NTL/ZZ_p.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    NTL::ZZ p((long)17);
    NTL::ZZ_p::init(p);
    NTL::ZZ_p k((long)19);

    std::cout << k << std::endl;

    return 0;
}