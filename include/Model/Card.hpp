#pragma once

#include <string>
enum Color
{
    Spade,
    Heart,
    Diamond,
    Club,
};

constexpr const std::string_view ColorNames[] = {"spades", "hearts", "diamonds", "clubs"};

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
constexpr const std::string_view NumberNames[] = {"Zero", "ace", "2", "3", "4", "5",
                                                  "6", "7", "8", "9", "10",
                                                  "jack", "queen", "king"};

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

    std::string Get_Color_string() const;
    std::string Get_Number_string() const;
    std::string Get_Name() const;

    // Friend function for << overloading
    friend std::ostream &operator<<(std::ostream &os, const Card &c);
};
