#include "Model/Card.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(CardTest, ColorTest)
{
    Card card;
    card.Set_Color(Spade);

    EXPECT_EQ(card.Get_Color(), 0);
}

TEST(CardTest, NumberTest)
{
    Card card;
    card.Set_Number(One);
    EXPECT_EQ(card.Get_Number(), 1);
}

TEST(CardTest, NumberValueTest)
{
    Card card;
    std::vector<int> value_expected = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    for (int i = 0; i < value_expected.size(); ++i)
    {
        Number n = static_cast<Number>(i + 1);
        card.Set_Number(n);
        EXPECT_EQ(card.Get_Value(), value_expected.at(i));
    }
}

TEST(CardTest, OutputFormatIsCorrect)
{
    Card card;
    card.Set_Number(Two);
    card.Set_Color(Heart);
    std::ostringstream oss;

    // Act
    oss << card;

    // Assert
    EXPECT_EQ(card.Get_Color_string(), "hearts");
    EXPECT_EQ(card.Get_Number_string(), "2");
    EXPECT_EQ(card.Get_Name(), "2_of_hearts");
    EXPECT_EQ(oss.str(), "2hearts");

    Card card2;
    card2.Set_Number(King);
    card2.Set_Color(Diamond);
    std::ostringstream oss2;

    // Act
    oss2 << card2;

    // Assert
    EXPECT_EQ(card2.Get_Color_string(), "diamonds");
    EXPECT_EQ(card2.Get_Number_string(), "king");
    EXPECT_EQ(card2.Get_Name(), "king_of_diamonds");
    EXPECT_EQ(oss2.str(), "kingdiamonds");
}