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
    DeckCards *deck;

public:
    GameState state;

protected:
    void State_Init();
    void State_DealingCards();
    void State_BankTurn();
    bool State_Finish();

    void Display_Game() const;

    void Next_Step();

    void Display_Result();

public:
    explicit Game();
    Game(DeckCards *deck);
    ~Game();

    void Start_Game();
    void State_PlayerTurn(const char c = ' ');

    std::vector<std::shared_ptr<Card>> Get_Bank_Cards() const;
    std::vector<std::shared_ptr<Card>> Get_Player_Cards() const;

signals:
    void gameFinished(bool youWin);
};
