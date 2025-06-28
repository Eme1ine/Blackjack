#pragma once

class Person
{
private:
    /* data */
    int card1;
    int card2;

public:
    Person(/* args */);
    ~Person();

    void SetCard1(int numero);
    int GetCard1();
    void SetCard2(int numero);
    int GetCard2();
};