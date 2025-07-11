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
        cout << "Press Enter to continue" << endl;
        cin.get();
        Next_Step();
    }
}

void Game::Display_Game()
{
    cout << endl;
    cout << "Game State " << StateNames[state] << endl;
    cout << "Bank" << " " << bank << " " << endl;
    cout << "Player" << " " << player << " " << endl;
    cout << endl;
}

void Game::Next_Step()
{
    if (state != Finish and player.Get_Score() >= 21)
    {
        state = Finish;
    }
    else
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
}

void Game::State_Init()
{
    bank.EmptyCards();
    bank.Add_Card(deck.Get_Random_Available_Card());

    player.EmptyCards();
    player.Add_Card(deck.Get_Random_Available_Card());
    player.Add_Card(deck.Get_Random_Available_Card());
}
void Game::State_PlayerTurn()
{
    char c;
    bool continue_player_turn = true;
    while (continue_player_turn)
    {
        cout << "Hit or stand ?" << endl;
        cout << "Press h to hit and s to stand" << endl;
        cin >> c;
        if (c == 'h')
        {
            player.Add_Card(deck.Get_Random_Available_Card());
            Display_Game();
        }
        else
        {
            continue_player_turn = false;
        }

        if (player.Get_Score() >= 21)
        {
            continue_player_turn = false;
        }
    }
}
void Game::State_BankTurn()
{
    while (bank.Get_Score() < 17)
    {
        bank.Add_Card(deck.Get_Random_Available_Card());
    }
}
bool Game::State_Finish()
{
    char reponse;
    Display_Result();
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

void Game::Display_Result()
{
    int score_bank = bank.Get_Score();
    int score_player = player.Get_Score();
    if (score_player > 21)
    {
        cout << "Score above 21" << endl;
        cout << "YOU LOOOOSE" << endl;
    }
    else if (score_bank > score_player)
    {
        cout << "Score above 21" << endl;
        cout << "YOU LOOOOSE" << endl;
    }
    else
    {
        cout << " YOU WIN CONGRATS ! " << endl;
    }
}