#include "Person/Person.hpp"

#include <iostream>

using namespace std;
Person::Person() : number_cards(0), cards(6)
{
    cout << "Person create" << endl;
}

Person::~Person()
{
    cout << "Person destroy" << endl;
}

std::ostream &operator<<(std::ostream &os, const Person &p)
{

    int n = p.number_cards;
    os << "\n Person has " << n << " cards :";
    os << "\n";
    for (size_t i = 0; i < n; i++)
    {
        Number number = p.cards.at(i)->Get_Number();
        Color color = p.cards.at(i)->Get_Color();
        os << NumberNames[number] << ColorNames[color] << " ";
    }

    return os;
}

void Person::Add_Card(Card *card)
{
    if (number_cards == MAX_SIZE_DECK)
    {
        cout << "ca va pas du tout la deck trop grand" << endl;
        // do exception
    }
    else
    {
        cards[number_cards] = card;
        number_cards += 1;
        // cout << number_cards << " " << cards.at(number_cards - 1) << "c'est ajoute" << endl;
    }
}
int Person::Get_Number_Cards()
{
    return number_cards;
}