#include "Person/Bank.hpp"

#include <iostream>

using namespace std;
Bank::Bank(/* args */)
{
    cout << "Bank create" << endl;
    SetCard1(10);
    SetCard2(9);
}

Bank::~Bank()
{
    cout << "Bank Destroy" << endl;
}
