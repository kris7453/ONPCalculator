#include "token.hpp"

namespace WSTI
{
    std::map<std::string, functionSymbol> token::functionsMap =
    {
        {"sin", functionSymbol::sin},
        {"cos", functionSymbol::cos},
        {"tan", functionSymbol::tan}
    };

    token::token()
    {
    }

    token::token( int number) 
    {
        setNumber( number );
    }

    token::token( operationSymbol _operator)
    {
        setOperator( _operator );
    }

    token::token( functionSymbol _function)
    {
        setFunction( _function );
    }

    token::token( token &e)
    {
        if (e.isElementNumber())
            this->setNumber( e.getNumber() );
        else if (e.isElementOperator())
            this->setOperator( e.getOperator() );
        else
            this->setFunction( e.getFunction() );
    }

    token::~token()
    {
    }
}
