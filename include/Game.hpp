#pragma once

#include "Person/Bank.hpp"
#include "Person/Player.hpp"
#include "DeckCards.hpp"

enum GameState
{
    Init,
    PlayerTurn,
    BankTurn,
    Finish,
};

class Game
{
private:
    /* data */
    Bank bank;
    Player player;
    GameState state;
    DeckCards deck;

public:
    Game(/* args */);
    ~Game();

    void Display_Game();

    void Start_Game();

    void Next_Step();

    void State_Init();
    void State_PlayerTurn();
    void State_BankTurn();
    bool State_Finish();
};
