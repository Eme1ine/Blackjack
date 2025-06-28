#include "Person/Person.hpp"

#include <iostream>

using namespace std;
Person::Person(/* args */)
{
    cout << "Person create" << endl;
    card1 = 0;
    card2 = 0;
}

Person::~Person()
{
    cout << "Person destroy" << endl;
}

void Person::SetCard1(int numero)
{
    card1 = numero;
}
int Person::GetCard1()
{
    return card1;
}

void Person::SetCard2(int numero)
{
    card2 = numero;
}

int Person::GetCard2()
{
    return card2;
}