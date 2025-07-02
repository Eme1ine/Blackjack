#include "Person/Person.hpp"

#include <iostream>

using namespace std;
Person::Person() : cards(0)
{
    cout << "Person create" << endl;
}

Person::~Person()
{
    cout << "Person destroy" << endl;
}

std::ostream &operator<<(std::ostream &os, const Person &p)
{

    int n = p.Get_Number_Cards();
    os << "has " << p.Get_Score() << " points with " << n << " cards :";
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
    cards.push_back(card);
}

int Person::Get_Number_Cards() const
{
    return cards.size();
}

int Person::Get_Score() const
{
    int sum = 0;
    for (int i = 0; i < Get_Number_Cards(); i++)
    {
        sum += cards[i]->Get_Number();
    }
    return sum;
}

void Person::EmptyCards()
{
    cards.clear();
}