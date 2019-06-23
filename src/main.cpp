#include <iostream>
#include "../include/ONPExpression.hpp"
#include <queue>

int main()
{
    WSTI::ONPExpression express;
    std::string strExpress;

    std::cout << " Enter in-fix expression:" << std::endl;
    getline( std::cin, strExpress);

    while ( strExpress != "q" )
    {
        express.setInFixExpression( strExpress );
        std::cout << std::endl << "ONP: " << express.getPostFixExpression() << std::endl << std::endl;
        express.printONPCalculate();
        cin.ignore();
        getchar();
        system("clear");
        std::cout << " Enter in-fix expression:" << std::endl;
        getline( std::cin, strExpress);
    } 

    return 0;
}