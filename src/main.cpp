#include <iostream>
#include "../include/ONPExpression.hpp"

int main() {
   WSTI::ONPExpression express;

   express.setInFixExpression("34+4*2/(512-495)^2");

    std::cout << "Hello Easy C++ project!" << std::endl;

    return 0;
}