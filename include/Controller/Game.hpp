#pragma once

#include "Model/Person/Bank.hpp"
#include "Model/Person/Player.hpp"
#include "Model/DeckCards.hpp"

enum GameState
{
    Init,
    PlayerTurn,
    BankTurn,
    Finish,
};

constexpr const char *StateNames[] = {"Init", "PlayerTurn", "BankTurn", "Finish"};

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

    void Display_Game() const;

    void Start_Game();

    void Next_Step();

    void State_Init();
    void State_PlayerTurn();
    void State_BankTurn();
    bool State_Finish() const;

    void Display_Result() const;
};
