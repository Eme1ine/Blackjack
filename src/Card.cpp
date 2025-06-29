#include "Card.hpp"

#include <iostream>

using namespace std;

Card::Card() : color(Spade), number(One), taken(false)
{
    cout << "Creation Card" << endl;
}

Card::~Card()
{
}

void Card::Set_Color(Color color)
{
    this->color = color;
}
void Card::Set_Number(Number number)
{
    this->number = number;
}
Color Card::Get_Color()
{
    return color;
}
Number Card::Get_Number()
{
    return number;
}
string Card::Get_Color_string() const
{
    return ColorNames[color];
}
string Card::Get_Number_string() const
{
    return NumberNames[number];
}

bool Card::is_Available()
{
    return !taken;
}

void Card::Set_Taken(bool taken)
{
    this->taken = taken;
}
std::ostream &operator<<(std::ostream &os, const Card &c)
{

    os << c.Get_Number_string() << c.Get_Color_string();
    return os;
}