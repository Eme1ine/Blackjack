#pragma once

#include <string>
enum Color
{
    Spade,
    Heart,
    Diamond,
    Club,
};

constexpr const std::string_view ColorNames[] = {"Spade", "Heart", "Diamond", "Club"};

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
constexpr const std::string_view NumberNames[] = {"Zero", "One", "Two", "Three", "Four", "Five",
                                                  "Six", "Seven", "Eight", "Nine", "Ten",
                                                  "Jack", "Queen", "King"};

class Card
{
private:
    /* data */
    Color color;
    Number number;

public:
    Card();
    Card(const Card &card);
    ~Card();

    void Set_Color(Color color);
    void Set_Number(Number number);

    Color Get_Color() const;
    Number Get_Number() const;
    int Get_Value() const;

    std::string_view Get_Color_string() const;
    std::string_view Get_Number_string() const;

    // Friend function for << overloading
    friend std::ostream &operator<<(std::ostream &os, const Card &c);
};
