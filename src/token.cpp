#include "token.hpp"

namespace WSTI
{
    token::token()
    {
    }

    token::token( token &e)
    {
        if (e.isElementNumber())
            this->setNumber( e.getNumber() );
        else if (e.isElementNumber())
            this->setOperator( e.getOperator() );
        else
            this->setOperator( e.getOperator() );
    }

    token::~token()
    {
    }
}
