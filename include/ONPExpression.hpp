#pragma once

#include <iostream>
#include <stack>

#include "../include/token.hpp"

    using namespace std;

namespace WSTI
{
    class ONPExpression
    {
        public:
        
            ONPExpression();
            ~ONPExpression();

            void setInFixExpression( string expression);

        private:
 
            string inFixExpression;
            
            stack<token>    outputStack;
            stack<operationSymbol>      operationStack;
    };
}