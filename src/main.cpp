#include <iostream>
#include "../include/ONPExpression.hpp"
#include <queue>

int main()
{
    WSTI::ONPExpression express;
    std::string strExpress = "sin(2)+34.38+4*2/(512-495)^2";

    express.setInFixExpression( strExpress );


    std::cout << "Hello Easy C++ project!" << std::endl;

    return 0;
}