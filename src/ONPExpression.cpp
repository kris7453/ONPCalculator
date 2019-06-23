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
        int step = 0;
        auto input = queue<token>(ONPQueue);
        stack<token> output;

        cout << std::setw(5) << std::internal << "step" << std::setw(10) << "token" << std::setw(20) << "output" << std::endl << std::endl;
        
        while( !input.empty())
        {
            try
            {
                token t = input.front();
                input.pop();

                cout << std::setw(5) << std::right << step << std::setw(10) << std::internal << t << "   " << std::setw(20) << std::left << parseTokenStackToString(output) << std::endl;

                if ( !output.empty())
                {
                    if ( t.isElementNumber() )
                        output.push( t );
                    else
                    {
                        if ( t.isElementOperator() )
                        {
                            double first, second;

                            if ( !output.empty() )
                            {
                                if ( output.top().isElementNumber())
                                {
                                    second = output.top().getNumber();
                                    output.pop();
                                }
                                else
                                    throw std::invalid_argument("Wrong argument to operator. Invalid ONP expression!");
                            }
                            else
                                throw std::invalid_argument("Too few arguments in expression!");
                            
                            if ( !output.empty() )
                            {
                                if ( output.top().isElementNumber())
                                {
                                    first = output.top().getNumber();
                                    output.pop();
                                }
                                else
                                    throw std::invalid_argument("Wrong argument to operator. Invalid ONP expression!");
                            }
                            else
                                throw std::invalid_argument("Too few arguments in expression!");

                            token newToken;

                            switch ( t.getOperator() )
                            {               
                                case operationSymbol::plus:     newToken.setNumber( first + second ); break;
                                case operationSymbol::minus:    newToken.setNumber( first - second ); break;
                                case operationSymbol::multiple: newToken.setNumber( first * second ); break;
                                case operationSymbol::divide:   newToken.setNumber( first / second ); break;
                                case operationSymbol::power:    newToken.setNumber( pow( first, second) ); break;
                            }

                            output.push( newToken );
                        }
                        else // Element is function
                        {
                            double first;

                            if ( !output.empty() )
                            {
                                if ( output.top().isElementNumber())
                                {
                                    first = output.top().getNumber();
                                    output.pop();
                                }
                                else
                                    throw std::invalid_argument("Wrong argument to operator. Invalid ONP expression!");
                            }
                            else
                                throw std::invalid_argument("Too few arguments in expression!");

                            token newToken;

                            switch ( t.getFunction() )
                            {
                                case functionSymbol::sin: newToken.setNumber( std::sin( first / 180.0 * M_PI ) ); break;
                                case functionSymbol::cos: newToken.setNumber( std::cos( first / 180.0 * M_PI ) ); break;
                                case functionSymbol::tan: newToken.setNumber( std::tan( first / 180.0 * M_PI ) ); break;
                                case functionSymbol::sqrt: newToken.setNumber( std::sqrt( first ) ); break;
                                case functionSymbol::cbrt: newToken.setNumber( std::cbrt( first ) ); break;
                                case functionSymbol::log: newToken.setNumber( std::log( first ) ); break;
                                case functionSymbol::log2: newToken.setNumber( std::log2( first ) ); break;
                                case functionSymbol::log10: newToken.setNumber( std::log10( first ) ); break;
                                case functionSymbol::exp: newToken.setNumber( std::exp( first ) ); break;
                                case functionSymbol::exp2: newToken.setNumber( std::exp2( first ) ); break;
                                case functionSymbol::floor: newToken.setNumber( std::floor( first ) ); break;
                                case functionSymbol::ceil: newToken.setNumber( std::ceil( first ) ); break;
                                case functionSymbol::round: newToken.setNumber( std::round( first ) ); break;
                            }

                            output.push( newToken );
                        }
                    }
                }
                else
                    output.push( t );
                
                step++;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        cout << std::setw(5) << std::right << step << std::setw(10) << std::internal << "=" << "   " << std::setw(20) << std::left << parseTokenStackToString(output) << std::endl;
    }

    void ONPExpression::tokenizeExpression()
    {
        short bracketsParity = 0; // variable to check brackets parity, brackets parity have to be equal 0 at the function end
        string::const_iterator expressionEnd = this->inFixExpression.end();
        inFixDeque.clear();
        while ( !ONPQueue.empty() )
            ONPQueue.pop();

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

        postFixExpression = parseTokenQueueToString( ONPQueue );
    }

    string ONPExpression::parseTokenQueueToString( const queue<token> &input)
    {
        auto _input( input );
        std::stringstream postFixStream;

        do
        {
            auto t = _input.front();
            _input.pop();
            postFixStream << t << " ";
        } while ( !_input.empty() );

        return postFixStream.str();
    }

    string ONPExpression::parseTokenStackToString( const stack<token> &input)
    {
        auto _input( input );
        stack<token> reverseInput;
        std::stringstream postFixStream;

        while ( !_input.empty() )
        {
            reverseInput.push( _input.top() );
            _input.pop();
        }

        while ( !reverseInput.empty() )
        {
            postFixStream << reverseInput.top() << " ";
            reverseInput.pop();
        }

        return postFixStream.str();
    }
}