#include <vector>
#include "Card.hpp"

class DeckCards
{
private:
    /* data */
    std::vector<Card> deck_cards;

public:
    DeckCards(/* args */);
    ~DeckCards();

    Card *Get_Random_Available_Card();
};
