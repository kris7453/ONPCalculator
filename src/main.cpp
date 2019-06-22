#include <iostream>
#include "../include/ONPExpression.hpp"
#include <queue>

int main()
{
    WSTI::ONPExpression express;
    std::string strExpress = "3*(sin (2) +sin( 6))^ 2";

    express.setInFixExpression( strExpress );
    std::cout << express.getPostFixExpression() << std::endl;

    return 0;
}