#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include "Card.hpp"

#define MAX_SIZE_DECK 6

class Person
{
private:
    /* data */
    std::vector<std::shared_ptr<Card>> cards;

public:
    Person(/* args */);
    ~Person();

    // Friend function for << overloading
    friend std::ostream &operator<<(std::ostream &os, const Person &p);

    void Add_Card(const std::shared_ptr<Card>);
    void EmptyCards();
    int Get_Number_Cards() const;
    int Get_Score() const;
};