#include "Model/DeckCards.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <numeric>

TEST(DeckCardsTest, InitTest)
{
    DeckCards deck;
    std::vector<int> random_deck;
    for (int i = 0; i < 10000; ++i)
    {
        std::shared_ptr<Card> c = deck.Get_Random_Card();
        random_deck.push_back(c->Get_Value());
    }

    // expected frequency per card
    double expected = 7.307;
    double mean = std::accumulate(random_deck.begin(), random_deck.end(), 0.0) / random_deck.size();
    EXPECT_NEAR(mean, expected, 0.1);
}