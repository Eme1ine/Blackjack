#include "Person/Bank.hpp"

#include <iostream>

using namespace std;
Bank::Bank(/* args */)
{
    cout << "Bank create" << endl;
}

Bank::~Bank()
{
    cout << "Bank Destroy" << endl;
}
