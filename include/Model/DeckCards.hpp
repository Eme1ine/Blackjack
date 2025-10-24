#include <vector>
#include <memory>
#include "Model/Card.hpp"

class DeckCards
{
protected:
    /* data */
    std::vector<std::shared_ptr<Card>> deck_cards;

public:
    DeckCards(/* args */);
    ~DeckCards();

    virtual std::shared_ptr<Card> Get_Random_Card();
};
