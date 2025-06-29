#include "Game.hpp"
#include "Person/Person.hpp"
#include <iostream>

using namespace std;

Game::Game(/* args */)
{
    cout << "Game Creation" << endl;
    state = GameState::Init;
    Display_Game();
}

Game::~Game()
{
    cout << "Game Destroy" << endl;
}

void Game::Start_Game()
{
    bool continue_game = true;
    while (continue_game)
    {
        switch (state)
        {
        case Init:
            /*Attribute random card*/
            State_Init();
            break;
        case PlayerTurn:
            State_PlayerTurn();
            break;
        case BankTurn:
            State_BankTurn();
            break;
        case Finish:
            continue_game = State_Finish();
            break;
        default:
            break;
        }
        Display_Game();
        Next_Step();
    }
}

void Game::Display_Game()
{
    cout << endl;
    cout << "Game State " << state << endl;
    cout << "Card Bank" << " " << bank << " " << endl;
    cout << "Card Player" << " " << player << " " << endl;
    cout << endl;
}

void Game::Next_Step()
{
    switch (state)
    {
    case Init:
        state = PlayerTurn;
        break;
    case PlayerTurn:
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
    bank.Add_Card(deck.Get_Random_Available_Card());

    player.Add_Card(deck.Get_Random_Available_Card());
    player.Add_Card(deck.Get_Random_Available_Card());
}
void Game::State_PlayerTurn()
{
}
void Game::State_BankTurn()
{
}
bool Game::State_Finish()
{
    char reponse;
    cout << "Do you want to play again (y/n)" << endl;
    cin >> reponse;
    if (reponse == 'y')
    {
        return true;
    }
    else
    {
        return false;
    }
}