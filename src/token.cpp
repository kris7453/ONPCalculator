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

    token::token( double number) 
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

    token::token( std::string _function)
    {
        auto funIterator = functionsMap.find( _function );
        
        if( funIterator != functionsMap.end())
            this->setFunction( funIterator->second );
        else
            throw std::invalid_argument("Unrecognized symbol " + _function );
    }

    token::token( const token &e)
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

    bool token::isOperatorBracket() const
    {
        if ( isElementOperator() )
            return ( ( _operator == operationSymbol:: leftBracket || _operator == operationSymbol::rightBracket )
            ?   true
            :   false);
    }

    short token::getPriority() const
    {
        if ( this->isElementFunction() )
            return 3;

        if ( this->isElementOperator() )
        {
            switch ( this->_operator )
            {
                case operationSymbol::plus:
                case operationSymbol::minus:

                    return 1;

                case operationSymbol::multiple:
                case operationSymbol::divide:

                    return 2;

                case operationSymbol::power:

                    return 3;
            }
        }

        //For number
        return 0;
    }

    associativity token::getAssociativity() const
    {
        if ( this->isElementOperator() )
        {
            switch ( this->_operator )
            {
                case operationSymbol::plus:
                case operationSymbol::minus:
                case operationSymbol::multiple:
                case operationSymbol::divide:
                
                    return associativity::left;
                
                case operationSymbol::power:

                    return associativity::right;
            }
        }

        return associativity::none;
    }

}
