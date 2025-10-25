#include "Controller/Game.hpp"
#include "Model/Person/Person.hpp"
#include "Model/Person/Player.hpp"
#include "Model/Person/Bank.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;
Game::Game(DeckCards *deck) : deck(deck)
{
    state = GameState::Init;
}

Game::Game()
{
    cout << "Game Creation" << endl;
    state = GameState::Init;
    Display_Game();
    Start_Game();
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
    case Init:
        /*Attribute random card*/
        State_Init();
        Display_Game();
        break;
    case DealingCards:
        /*Attribute random card*/
        State_DealingCards();
        Display_Game();
        break;
    case PlayerTurn:
        State_PlayerTurn();
        Display_Game();
        break;
    case BankTurn:
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
    switch (state)
    {
    case Init:
        state = DealingCards;
        break;
    case DealingCards:
        state = PlayerTurn;
        break;
    case PlayerTurnFinished:
        state = BankTurn;
        break;
    case BankTurn:
        state = Finish;
        break;
    case Finish:
        state = Init;
        break;
    default:
        break;
    }
}

void Game::State_Init()
{
    bank.EmptyCards();
    player.EmptyCards();
}

void Game::State_DealingCards()
{
    bank.Add_Card(deck->Get_Random_Card());

    player.Add_Card(deck->Get_Random_Card());
    player.Add_Card(deck->Get_Random_Card());
}

void Game::State_PlayerTurn(const char c)
{
    if (c == 's')
    {
        state = PlayerTurnFinished;
        Next_Step();
    }
    else
    {
        if (c == 'h')
        {
            player.Add_Card(deck->Get_Random_Card());
        }
        if (player.Get_Score() >= 21)
        {
            state = Finish;
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
        bank.Add_Card(deck->Get_Random_Card());
    }
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
    emit gameFinished(youWin);
}

std::vector<std::shared_ptr<Card>> Game::Get_Bank_Cards() const
{
    return bank.Get_Cards();
}

std::vector<std::shared_ptr<Card>> Game::Get_Player_Cards() const
{
    return player.Get_Cards();
}