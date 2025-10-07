#include <vector>
#include <memory>
#include "Card.hpp"

class DeckCards
{
private:
    /* data */
    std::vector<std::shared_ptr<Card>> deck_cards;

public:
    DeckCards(/* args */);
    ~DeckCards();

    std::shared_ptr<Card> Get_Random_Available_Card();
};
