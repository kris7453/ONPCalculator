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

    void ONPExpression::printONPCalculate()
    {
        
    }

    void ONPExpression::tokenizeExpression()
    {
        short bracketsParity = 0; // variable to check brackets parity, brackets parity have to be equal 0 at the function end
        
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

                inFixDeque.push_back( token(stod(number)) );
                i--;
                continue;
            }

            switch ( *i )
            {
                case '(': inFixDeque.push_back( token(operationSymbol::leftBracket) ); bracketsParity++; break;
                case '+': inFixDeque.push_back( token(operationSymbol::plus) ); break;
                case '-': inFixDeque.push_back( token(operationSymbol::minus) ); break;
                case ')': inFixDeque.push_back( token(operationSymbol::rightBracket) ); bracketsParity--; break;
                case '*': inFixDeque.push_back( token(operationSymbol::multiple) ); break;
                case '/': inFixDeque.push_back( token(operationSymbol::divide) ); break;
                case '^': inFixDeque.push_back( token(operationSymbol::power) ); break;
            
                default:
                {
                    string funct = "";

                    for (; *i != '(' && *i != ' ' && i < expressionEnd; i++)
                        funct += *i ;
                    
                    i--;

                    try
                    {
                        inFixDeque.push_back( token( funct ));
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
        convertInFixToPostFix();
    }

    bool ONPExpression::isExpressionValid()
    {
        return  validExpression;
    }

    void ONPExpression::convertInFixToPostFix()
    {
        queue<token> input( inFixDeque );
        stack<token>  operationStack;

        while( !input.empty() )
        {
            token t = input.front();
            input.pop();

            if( t.isElementNumber() )
            {
                ONPQueue.push( t );
                continue;
            }

            // For tokens which are opeartors

            token operationStackTop;

            if ( t.isOperatorBracket() )
            {
                if ( t.getOperator() == operationSymbol::leftBracket )
                {
                    operationStack.push( t );
                    continue;
                }

                operationStackTop = operationStack.top();

                if ( t.getOperator() == operationSymbol::rightBracket )
                {
                    while ( operationStackTop.getOperator() != operationSymbol::leftBracket )
                    {
                        ONPQueue.push( operationStackTop );
                        operationStack.pop();

                        if ( !operationStack.empty() )
                            operationStackTop = operationStack.top();
                        else
                            throw std::invalid_argument("Mismatched argument!");
                    }
                    operationStack.pop(); // Pop the left bracket

                    if ( !operationStack.empty() )
                    {
                        operationStackTop = operationStack.top();
                        
                        if ( operationStackTop.isElementFunction() )
                        {
                            ONPQueue.push( operationStackTop );
                            operationStack.pop();
                        }
                    }
                    continue;
                }
            }

            if ( !operationStack.empty() )
            {
                bool getNext = false;
                operationStackTop = operationStack.top();

                do
                {
                    if (operationStackTop.isElementOperator()
                        && ((operationStackTop.getPriority() > t.getPriority())
                            ||  (operationStackTop.getPriority() == t.getPriority() 
                            && operationStackTop.getAssociativity() == associativity::left)))
                    {
                        ONPQueue.push( operationStackTop );
                        operationStack.pop();

                        if ( !operationStack.empty() )
                        {
                            operationStackTop = operationStack.top();
                            getNext = true;
                            continue;
                        }
                    }
                    
                    getNext = false;
                } while ( getNext );
            }

            operationStack.push( t );
            continue;
        }

        while ( !operationStack.empty() )
        {
            ONPQueue.push( operationStack.top() );
            operationStack.pop();
        }

        postFixToString();
    }

    void ONPExpression::postFixToString()
    {
        queue<token> input( ONPQueue );
        std::stringstream postFixStream;

        do
        {
            auto t = input.front();
            input.pop();

            if ( t.isElementNumber() )
            {
                postFixStream << std::fixed << setprecision(2) << t.getNumber() << " ";
                continue;
            }

            if ( t.isElementOperator() )
            {
                switch ( t.getOperator() )
                {               
                    case operationSymbol::leftBracket: postFixStream << "( "; break;
                    case operationSymbol::plus: postFixStream << "+ "; break;
                    case operationSymbol::minus: postFixStream << "- "; break;
                    case operationSymbol::rightBracket: postFixStream << ") "; break;
                    case operationSymbol::multiple: postFixStream << "* "; break;
                    case operationSymbol::divide: postFixStream << "/ "; break;
                    case operationSymbol::power: postFixStream << "^ "; break;
                }
                continue;
            }

            switch ( t.getFunction() )
            {
                case functionSymbol::sin: postFixStream << "sin "; break;
                case functionSymbol::cos: postFixStream << "cos "; break;
                case functionSymbol::tan: postFixStream << "tan "; break;
            }
        } while ( !input.empty() );

        postFixExpression = postFixStream.str();
    }

    void ONPExpression::calculateONP()
    {

    }

}