#include "Controller/Game.hpp"
#include "Model/Person/Person.hpp"
#include "Model/Person/Player.hpp"
#include "Model/Person/Bank.hpp"
#include "View/View.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

Game::Game()
{
    cout << "Game Creation" << endl;
    view.show();
    state = GameState::InitBegin;
    view.updateState(state);
    Display_Game();

    QObject::connect(&view, &View::enterPressed, this, onEnterPressed);
    QObject::connect(&view, &View::letterPressed, this, onLetterPressed);
    QObject::connect(&view, &View::turnFinished, this, onTurnFinished);
    QObject::connect(view.buttonNext, &QPushButton::released, this, onEnterPressed);
    QObject::connect(view.buttonHit, &QPushButton::released, this, onLetterPressedH);
    QObject::connect(view.buttonStand, &QPushButton::released, this, onLetterPressedS);
}

Game::~Game()
{
    cout << "Game Destroy" << endl;
}

void Game::Start_Game()
{
    bool continue_game = true;
    switch (state)
    {
    case InitBegin:
        /*Attribute random card*/
        State_Init();
        Display_Game();
        break;
    case PlayerTurn:
        State_PlayerTurn();
        break;
    case PlayerTurnFinished:
        Display_Game();
        break;
    case BankTurnBegin:
        State_BankTurn();
        Display_Game();
        break;
    case Finish:
        continue_game = State_Finish();
        break;
    default:
        break;
    }
    Next_Step();
}

void Game::Display_Game() const
{
    cout << endl;
    cout << "Game State " << StateNames[state] << endl;
    cout << "Bank" << " " << bank << " " << endl;
    cout << "Player" << " " << player << " " << endl;
    cout << endl;
}

void Game::Next_Step()
{
    if (state != Finish and player.Get_Score() > 21)
    {
        state = Finish;
    }
    else
    {
        switch (state)
        {
        case InitFinished:
            state = PlayerTurn;
            break;
        case PlayerTurnFinished:
            state = BankTurnBegin;
            break;
        case BankTurnBegin:
            state = BankTurn;
            break;
        case BankTurnFinished:
            state = Finish;
            break;
        case Finish:
            state = InitBegin;
            break;
        default:
            break;
        }
    }
    view.updateState(state);
}

void Game::State_Init()
{
    state = Init;
    bank.EmptyCards();
    player.EmptyCards();

    view.updateBank(bank);
    view.updatePlayer(player);
    bank.Add_Card(deck.Get_Random_Card());

    player.Add_Card(deck.Get_Random_Card());
    player.Add_Card(deck.Get_Random_Card());

    view.updateBank(bank);
    view.updatePlayer(player);
}
void Game::State_PlayerTurn(const char c)
{
    if (c == 's')
    {
        state = PlayerTurnFinished;
        view.updateState(state);
        Start_Game();
    }
    else
    {
        if (c == 'h')
        {
            player.Add_Card(deck.Get_Random_Card());
            view.updatePlayer(player);
        }
        if (player.Get_Score() >= 21)
        {
            state = PlayerTurnFinished;
            view.updateState(state);
            Start_Game();
        }
        else
        {
            Display_Game();
        }
        cout << "you entered ='" << c << "'" << endl;
        cout << "Hit or stand ?" << endl;
        // todo Option split a ajouter
        cout << "Press h to hit and s to stand" << endl;
    }
}
void Game::State_BankTurn()
{
    while (bank.Get_Score() < 17)
    {
        bank.Add_Card(deck.Get_Random_Card());
    }
    view.updateBank(bank);
}
bool Game::State_Finish()
{
    char reponse;
    Display_Result();
    cout << "Do you want to play again (y/n)" << endl;
    reponse = 'n';
    return (reponse == 'y');
}

void Game::Display_Result()
{
    int score_bank = bank.Get_Score();
    int score_player = player.Get_Score();
    bool youWin = false;
    if (score_bank == 21 or score_player == 21)
    {
        cout << "BLACKJACK" << endl;
    }

    if (score_player > 21)
    {
        cout << "BUSTED" << endl;
        cout << "YOU LOOOOSE" << endl;
    }
    else if (score_bank > 21)
    {
        cout << "Bank busteeed" << endl;
        cout << " YOU WIN CONGRATS ! " << endl;
        youWin = true;
    }
    else if (score_bank > score_player)
    {
        cout << "Score bank above" << endl;
        cout << "YOU LOOOOSE" << endl;
    }
    else
    {
        cout << " YOU WIN CONGRATS ! " << endl;
        youWin = true;
    }
    view.popUpWinner(youWin);
}

void Game::onEnterPressed()
{
    std::cout << "Enter pressed -> action triggered in GameController\n";
    Start_Game();
}

void Game::onLetterPressedS()
{
    onLetterPressed('s');
}

void Game::onLetterPressedH()
{
    onLetterPressed('h');
}
void Game::onLetterPressed(char value)
{
    std::cout << "letter pressed -> " << value << endl;
    if (state == PlayerTurn)
    {
        State_PlayerTurn(value);
    }
}
void Game::onTurnFinished()
{
    std::cout << "TurnFinished" << endl;
    static int init_finished_count = 0;
    if (state == BankTurn || state == BankTurnBegin)
    {
        state = BankTurnFinished;
        Start_Game();
    }
    else if (state == Init)
    {
        if (++init_finished_count == 2)
        {

            state = InitFinished;
            Start_Game();
            init_finished_count = 0;
        }
    }
}