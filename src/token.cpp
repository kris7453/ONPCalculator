#include "token.hpp"

namespace WSTI
{
    std::map<std::string, functionSymbol> token::functionsMap =
    {
        {"sin", functionSymbol::sin},
        {"cos", functionSymbol::cos},
        {"tan", functionSymbol::tan},
        {"sqrt", functionSymbol::sqrt},
        {"cbrt", functionSymbol::cbrt},
        {"log", functionSymbol::log},
        {"log2", functionSymbol::log2},
        {"log10", functionSymbol::log10},
        {"exp", functionSymbol::exp},
        {"exp2", functionSymbol::exp2},
        {"floor", functionSymbol::floor},
        {"ceil", functionSymbol::ceil},
        {"round", functionSymbol::round}
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

    std::ostream& operator<<( std::ostream& stream, const token& _token )
    {
        if ( _token.isElementNumber() )
            stream << std::fixed << std::setprecision(2) << _token.getNumber();
        else
        if ( _token.isElementOperator() )
        {
            switch ( _token.getOperator() )
            {               
                case operationSymbol::leftBracket: stream << "("; break;
                case operationSymbol::plus: stream << "+"; break;
                case operationSymbol::minus: stream << "-"; break;
                case operationSymbol::rightBracket: stream << ")"; break;
                case operationSymbol::multiple: stream << "*"; break;
                case operationSymbol::divide: stream << "/"; break;
                case operationSymbol::power: stream << "^"; break;
            }
        }
        else
        switch ( _token.getFunction() )
        {
            case functionSymbol::sin: stream << "sin"; break;
            case functionSymbol::cos: stream << "cos"; break;
            case functionSymbol::tan: stream << "tan"; break;
            case functionSymbol::sqrt: stream << "sqrt"; break;
            case functionSymbol::cbrt: stream << "cbrt"; break;
            case functionSymbol::log: stream << "log"; break;
            case functionSymbol::log2: stream << "log2"; break;
            case functionSymbol::log10: stream << "log10"; break;
            case functionSymbol::exp: stream << "exp"; break;
            case functionSymbol::exp2: stream << "exp2"; break;
            case functionSymbol::floor: stream << "floor"; break;
            case functionSymbol::ceil: stream << "ceil"; break;
            case functionSymbol::round: stream << "round"; break;
        }

        return stream;
    }
}