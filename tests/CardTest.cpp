#include "Model/Card.hpp"
#include <gtest/gtest.h>
#include <iostream>

Card card;
TEST(CardTest, ColorTest)
{
    card.Set_Color(Spade);

    EXPECT_EQ(card.Get_Color(), 0);
}

TEST(CardTest, NumberTest)
{
    card.Set_Number(One);
    EXPECT_EQ(card.Get_Number(), 1);
}

TEST(CardTest, NumberValueTest)
{
    std::vector<int> value_expected = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    for (int i = 0; i < value_expected.size(); ++i)
    {
        Number n = static_cast<Number>(i + 1);
        card.Set_Number(n);
        EXPECT_EQ(card.Get_Value(), value_expected.at(i));
    }
}