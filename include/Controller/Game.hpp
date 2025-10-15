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
    GameState state;
    DeckCards deck;
    View view;

public:
    explicit Game();
    ~Game();

    void Display_Game() const;

    void Start_Game();

    void Next_Step();

    void State_Init();
    void State_PlayerTurn(const char c = ' ');
    void State_BankTurn();
    bool State_Finish() const;

    void Display_Result() const;

public slots:
    void onEnterPressed();
    void onLetterPressed(char value);
    void onLetterPressedH();
    void onLetterPressedS();
    void onTurnFinished();
};
