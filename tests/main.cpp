#include <iostream>
#include "Chm.hpp"

int main() {
    NMphf::Chm chm;
    const char* A[] = {"10","20"};
    std::cout << chm.generate(A, 2) <<std::endl;
}