#include "Model/Person/Person.hpp"
#include "Model/Card.hpp"
#include <gtest/gtest.h>
#include <iostream>

Person person;

TEST(PersonTest, InitTest)
{
    Person person1;
    EXPECT_EQ(person1.Get_Number_Cards(), 0);
}

TEST(PersonTest, AddCardTest)
{
    Card card;
    card.Set_Number(Two);
    card.Set_Color(Heart);
    person.Add_Card(std::make_shared<Card>(card));
    EXPECT_EQ(person.Get_Number_Cards(), 1);
    EXPECT_EQ(person.Get_Cards().at(0)->Get_Number(), 2);
    EXPECT_EQ(person.Get_Cards().at(0)->Get_Color(), 1);
}

TEST(PersonTest, EmptyCardTest)
{
    Card card;
    person.Add_Card(std::make_shared<Card>(card));
    EXPECT_NE(person.Get_Number_Cards(), 0);
    person.EmptyCards();
    EXPECT_EQ(person.Get_Number_Cards(), 0);
}

TEST(PersonTest, GetScoreEnorme)
{
    Person person;
    EXPECT_EQ(person.Get_Score(), 0);

    for (int i = 0; i < 13; ++i)
    {
        Number n = static_cast<Number>(i + 1);
        Card card;
        card.Set_Number(n);
        person.Add_Card(std::make_shared<Card>(card));
    }
    // L'As vaudra 1 car le score depasse 21
    EXPECT_EQ(person.Get_Score(), 85);
}

TEST(PersonTest, GetScoreSansAs)
{
    Person person;
    Card card;
    card.Set_Number(Eight);
    person.Add_Card(std::make_shared<Card>(card));
    Card card2;
    card2.Set_Number(Nine);
    person.Add_Card(std::make_shared<Card>(card2));
    EXPECT_EQ(person.Get_Score(), 17);
}
TEST(PersonTest, GetScoreAsSansDepasser)
{
    Person person;
    Card card1;
    card1.Set_Number(One);
    person.Add_Card(std::make_shared<Card>(card1));
    Card card2;
    card2.Set_Number(Nine);
    person.Add_Card(std::make_shared<Card>(card2));
    EXPECT_EQ(person.Get_Score(), 20);
}
TEST(PersonTest, GetScoreAsAvecDepassement)
{
    Person person;
    Card card;
    card.Set_Number(One);
    person.Add_Card(std::make_shared<Card>(card));
    Card card2;
    card2.Set_Number(Nine);
    person.Add_Card(std::make_shared<Card>(card2));
    Card card3;
    card3.Set_Number(Two);
    person.Add_Card(std::make_shared<Card>(card3));
    EXPECT_EQ(person.Get_Score(), 12);
}

TEST(PersonTest, OutputFormatIsCorrect)
{
    Person person;
    Card card;
    card.Set_Number(Two);
    card.Set_Color(Heart);
    person.Add_Card(std::make_shared<Card>(card));
    std::ostringstream oss;

    // Act
    oss << person;

    // Assert
    EXPECT_EQ(oss.str(), "has 2 points with 1 cards :\n2hearts ");

    Card card2;
    card2.Set_Number(Three);
    card2.Set_Color(Diamond);
    person.Add_Card(std::make_shared<Card>(card2));
    std::ostringstream oss2;

    // Act
    oss2 << person;

    // Assert
    EXPECT_EQ(oss2.str(), "has 5 points with 2 cards :\n2hearts 3diamonds ");
}