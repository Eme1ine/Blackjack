#include "DeckCards.hpp"
#include <random>
#include <iostream>
using namespace std;
DeckCards::DeckCards(/* args */) : deck_cards(56)
{
    for (int color = Spade; color < 4; color++)
    {
        for (int number = One; number < 14; number++)
        {
            Card &card = deck_cards[color * 14 + number];
            card.Set_Color(Color(color));
            card.Set_Number(Number(number));
        }
    }
}

DeckCards::~DeckCards()
{
}

Card *DeckCards::Get_Random_Available_Card()
{
    // Filtrer les cartes disponibles
    vector<Card *> available;

    for (Card &c : deck_cards)
    {
        if (c.is_Available())
        {
            available.push_back(&c);
        }
    }

    if (available.empty())
    {
        return nullptr; // Plus de cartes disponibles
    }

    // Choisir un index aléatoire
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, available.size() - 1);

    Card *selected = available[dist(gen)];
    selected->Set_Taken(true);
    return selected;
}