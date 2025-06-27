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
