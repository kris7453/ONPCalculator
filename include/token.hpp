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
        
    class token
    {
        public:

            token();
            token( int number);
            token( operationSymbol _operator);
            token( functionSymbol _function);
            token( token &e );
            ~token();

            void setNumber( int number){ this->number = number; whichElement = 0;}
            int getNumber(){ return number; }

            void setOperator( operationSymbol _operator){ this->_operator = _operator; whichElement = 1;}
            operationSymbol getOperator(){ return _operator; }

            void setFunction( functionSymbol _function){ this->_function = _function; whichElement = 2;}
            functionSymbol getFunction(){ return _function; }
            
            bool isElementNumber(){ return (whichElement == 0);}
            bool isElementOperator(){ return (whichElement == 1);}
            bool isElementFunction(){ return (whichElement == 2);}

        private:

            unsigned short whichElement; // 0 - number, 1 - operator, 2 - function

            union
            {
                int             number;
                operationSymbol _operator;
                functionSymbol  _function;
            };
            
            static std::map<std::string, functionSymbol> functionsMap;
        
    };
}