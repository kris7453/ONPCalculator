#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>
#include <stack>
#include <string>
#include <math.h>

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
            bool isExpressionValid(){ return validExpression;}
            string getPostFixExpression(){ return postFixExpression;}
            void printONPCalculate();

        private:
 
            string inFixExpression;
            string postFixExpression;

            bool validExpression;
            
            queue<token>    ONPQueue;
            deque<token>    inFixDeque;

            enum expressionException
            {
                bracketsParity
            };

            void tokenizeExpression();
            void convertInFixToPostFix();

            string parseTokenQueueToString( const queue<token> &input);
            string parseTokenStackToString( const stack<token> &input);

    };
}