#include "DeckCards.hpp"
#include <random>
#include <memory>
#include <iostream>
using namespace std;
DeckCards::DeckCards(/* args */)
{
    for (int color = Spade; color < 4; color++)
    {
        for (int number = One; number < 14; number++)
        {
            shared_ptr<Card> card = make_shared<Card>();
            card->Set_Color(Color(color));
            card->Set_Number(Number(number));
            deck_cards.push_back(card);
        }
    }
}

DeckCards::~DeckCards()
{
}

shared_ptr<Card> DeckCards::Get_Random_Card()
{
    // Choisir un index aléatoire
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, deck_cards.size() - 1);
    shared_ptr<Card> selected = deck_cards[dist(gen)];
    return selected;
}