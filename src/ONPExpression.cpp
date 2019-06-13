#include "ONPExpression.hpp"

namespace WSTI
{
    ONPExpression::ONPExpression()
    {
    }

    ONPExpression::~ONPExpression()
    {
    }

    void ONPExpression::setInFixExpression( string expression)
    {
        inFixExpression = expression;
    }

    void ONPExpression::tokenizeExpression()
    {
        stack<token> tempStack;
        string::const_iterator expressionEnd = this->inFixExpression.cend();

        for ( string::const_iterator i = inFixExpression.cbegin(); i < expressionEnd; i++)
        {
            if( *i == ' ')  continue;

            if ( *i >= '0' &&*i <= '9' )
            {
                string number = "";

                for (; ( *i >= '0' && *i <= '9' ) && i < expressionEnd; i++)
                {
                    number += *i;
                }

                tempStack.push( token(stoi(number)) );
                i--;
                continue;
            }

            switch ( *i )
            {
                case '(': tempStack.push( token(operationSymbol::leftBracket) ); break;
                case '+': tempStack.push( token(operationSymbol::plus) ); break;
                case '-': tempStack.push( token(operationSymbol::minus) ); break;
                case ')': tempStack.push( token(operationSymbol::rightBracket) ); break;
                case '*': tempStack.push( token(operationSymbol::multiple) ); break;
                case '/': tempStack.push( token(operationSymbol::divide) ); break;
                case '^': tempStack.push( token(operationSymbol::power) ); break;
            
                default:
                    

                    break;
            }
        }

        while( !tempStack.empty() )
        {
            inFixStack.push( tempStack.top() );
            tempStack.pop();
        }
    }
}