#pragma once

#include "Person/Person.hpp"
class Bank : public Person
{
private:
    /* data */
public:
    Bank(/* args */);
    ~Bank();
    // Friend function for << overloading
    friend std::ostream &operator<<(std::ostream &os, const Person &p);
};
