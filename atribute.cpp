#include "atribute.h"
std::string Atribute::getName() const
{
    return name;
}

void Atribute::setName(const std::string &value)
{
    name = value;
}

std::string Atribute::getValue() const
{
    return value;
}

void Atribute::setValue(const std::string &_value)
{
    value = _value;
}

Atribute::Atribute()
    : name(""), value("")
{
}

Atribute::~Atribute()
{
}
