#pragma once

#include <string>
enum Color
{
    Spade,
    Heart,
    Diamond,
    Club,
};

constexpr const char *ColorNames[] = {"Spade", "Heart", "Diamond", "Club"};

enum Number
{
    One = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
};
constexpr const char *NumberNames[] = {"Zero", "One", "Two", "Three", "Four", "Five",
                                       "Six", "Seven", "Eight", "Nine", "Ten",
                                       "Jack", "Queen", "King"};

class Card
{
private:
    /* data */
    Color color;
    Number number;
    bool taken;

public:
    Card();
    ~Card();

    void Set_Color(Color color);
    void Set_Number(Number number);
    void Set_Taken(bool taken);

    Color Get_Color();
    Number Get_Number();
    bool is_Available();

    std::string Get_Color_string() const;
    std::string Get_Number_string() const;

    // Friend function for << overloading
    friend std::ostream &operator<<(std::ostream &os, const Card &c);
};
