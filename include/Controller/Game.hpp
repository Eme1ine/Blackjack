#pragma once

#include "Controller/GameState.hpp"
#include "Model/Person/Bank.hpp"
#include "Model/Person/Player.hpp"
#include "Model/DeckCards.hpp"
#include "View/View.hpp"

class Game : public QObject
{
    Q_OBJECT
private:
    /* data */
    Bank bank;
    Player player;
    DeckCards deck;

public:
    GameState state;

public:
    explicit Game();
    ~Game();

    void Display_Game() const;

    void Start_Game();

    void Next_Step();

    void State_Init();
    void State_DealingCards();
    void State_PlayerTurn(const char c = ' ');
    void State_BankTurn();
    bool State_Finish();

    void Display_Result();

    std::vector<std::shared_ptr<Card>> Get_Bank_Cards() const { return bank.Get_Cards(); };
    std::vector<std::shared_ptr<Card>> Get_Player_Cards() const { return player.Get_Cards(); };

signals:
    void gameFinished(bool youWin);
};
