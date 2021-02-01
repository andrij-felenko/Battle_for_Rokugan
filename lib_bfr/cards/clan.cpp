#include "token.h"

Token::Token()
{

}

Type Token::type() const
{
    return m_type;
}

void Token::setType(const Type &type)
{
    m_type = type;
}
