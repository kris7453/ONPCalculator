#pragma once
#include <map>

namespace WSTI
{
    enum operationSymbol
    {
        leftBracket,
        plus,
        minus,
        rightBracket,
        multiple,
        divide,
        power
    };

    enum functionSymbol
    {
        sin,
        cos,
        tan
    };

    enum associativity
    {
        left,
        right,
        none
    };
        
    class token
    {
        public:

            explicit token();
            token( double number);
            token( operationSymbol _operator);
            token( functionSymbol _function);
            token( std::string _function);
            token( const token &e );
            ~token();


            void setNumber( double number){ this->number = number; whichElement = 0;}
            double getNumber() const { return number; }

            void setOperator( operationSymbol _operator){ this->_operator = _operator; whichElement = 1;}
            operationSymbol getOperator() const { return _operator; }

            void setFunction( functionSymbol _function){ this->_function = _function; whichElement = 2;}
            functionSymbol getFunction() const { return _function; }
            
            bool isElementNumber() const { return (whichElement == 0);}
            bool isElementOperator() const { return (whichElement == 1);}
            bool isOperatorBracket() const;
            bool isElementFunction() const { return (whichElement == 2);}

            short getPriority() const;
            associativity getAssociativity() const;


        private:

            unsigned short whichElement; // 0 - number, 1 - operator, 2 - function

            union
            {
                double             number;
                operationSymbol _operator;
                functionSymbol  _function;
            };
            
            static std::map<std::string, functionSymbol> functionsMap;
        
    };
}