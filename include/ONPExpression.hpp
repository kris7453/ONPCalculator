#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <string>

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
            bool isExpressionValid();

        private:
 
            string inFixExpression;

            bool validExpression;
            
            queue<token>    ONPQueue;
            queue<token>    inFixQueue;

            enum expressionException
            {
                bracketsParity
            };

            void tokenizeExpression();
            void convertInFixToPostFix();
    };
}