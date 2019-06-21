#include "ONPExpression.hpp"

namespace WSTI
{
    ONPExpression::ONPExpression() : validExpression( false )
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
        queue<token> inFixQueue;
        string::const_iterator expressionEnd = this->inFixExpression.end();

        for ( string::const_iterator i = inFixExpression.begin(); i < expressionEnd; i++)
        {
            if( *i == ' ')  continue;

            if ( *i >= '0' && *i <= '9' )
            {
                string number = "";

                for (; (( *i >= '0' && *i <= '9' ) || *i == '.') && i < expressionEnd; i++)
                {
                    number += *i;
                }

                inFixQueue.push( token(stod(number)) );
                i--;
                continue;
            }

            switch ( *i )
            {
                case '(': inFixQueue.push( token(operationSymbol::leftBracket) ); bracketsParity++; break;
                case '+': inFixQueue.push( token(operationSymbol::plus) ); break;
                case '-': inFixQueue.push( token(operationSymbol::minus) ); break;
                case ')': inFixQueue.push( token(operationSymbol::rightBracket) ); bracketsParity--; break;
                case '*': inFixQueue.push( token(operationSymbol::multiple) ); break;
                case '/': inFixQueue.push( token(operationSymbol::divide) ); break;
                case '^': inFixQueue.push( token(operationSymbol::power) ); break;
            
                default:
                {
                    string funct = "";

                    for (; *i != '(' && i < expressionEnd; i++)
                        funct += *i;
                    
                    i--;

                    try
                    {
                        inFixQueue.push( token( funct ));
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                        validExpression = false;
                        return;
                    }
                }
                    break;
            }
        }

        if ( bracketsParity ) // bracketsParity <> 0
            throw expressionException::bracketsParity;

        validExpression = true;
    }

    bool ONPExpression::isExpressionValid()
    {
        return  validExpression;
    }

    void ONPExpression::convertInFixToPostFix()
    {
        queue<token> input( inFixQueue );
        queue<token> output;
        stack<operationSymbol>  operationStack;

        while( !input.empty() )
        {
            token t = input.front();
            input.pop();

            if( t.isElementNumber() )
            {
                output.push( t );
                continue;
            }

            if( t.isElementOperator() )
            {
                
            }
        }

    }

}