#include <vector>
#include <memory>
#include "Model/Card.hpp"

class DeckCards
{
private:
    /* data */
    std::vector<std::shared_ptr<Card>> deck_cards;

public:
    DeckCards(/* args */);
    ~DeckCards();

    std::shared_ptr<Card> Get_Random_Card();
};
