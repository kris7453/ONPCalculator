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
        try
        {
            tokenizeExpression();
        }
        catch( const expressionException &e)
        {
            switch ( e )
            {
            case expressionException::bracketsParity:
                cout << "Wrong expression, brackets parity is incorrect!" << endl;
                break;
            }
        }
        
    }

    void ONPExpression::tokenizeExpression()
    {
        short bracketsParity = 0; // variable to check brackets parity, brackets parity have to be equal 0 at the function end
        stack<token> tempStack;
        string::const_iterator expressionEnd = this->inFixExpression.end();

        for ( string::const_iterator i = inFixExpression.begin(); i < expressionEnd; i++)
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
                case '(': tempStack.push( token(operationSymbol::leftBracket) ); bracketsParity++; break;
                case '+': tempStack.push( token(operationSymbol::plus) ); break;
                case '-': tempStack.push( token(operationSymbol::minus) ); break;
                case ')': tempStack.push( token(operationSymbol::rightBracket) ); bracketsParity--; break;
                case '*': tempStack.push( token(operationSymbol::multiple) ); break;
                case '/': tempStack.push( token(operationSymbol::divide) ); break;
                case '^': tempStack.push( token(operationSymbol::power) ); break;
            
                default:
                
                    break;
            }
        }

        if ( bracketsParity ) // bracketsParity <> 0
            throw expressionException::bracketsParity;


        while( !tempStack.empty() )
        {
            inFixStack.push( tempStack.top() );
            tempStack.pop();
        }
    }
}