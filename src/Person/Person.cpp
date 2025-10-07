#include "Person/Person.hpp"

#include <iostream>
#include <memory>

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
    for (shared_ptr<Card> c : p.cards)
    {
        Number number = c->Get_Number();
        Color color = c->Get_Color();
        os << NumberNames[number] << ColorNames[color] << " ";
    }

    return os;
}

void Person::Add_Card(shared_ptr<Card> card)
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
    int nb_ace = 0;
    for (shared_ptr<Card> c : cards)
    {
        sum += c->Get_Value();
        if (c->Get_Number() == 1)
        {
            ++nb_ace;
        }
    }
    while (nb_ace > 0 and sum > 21)
    {
        sum -= 10; // Value of ace go from 11 to 1
        --nb_ace;
    }
    return sum;
}

void Person::EmptyCards()
{
    cards.clear();
}