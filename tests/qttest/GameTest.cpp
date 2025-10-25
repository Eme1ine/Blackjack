// qttest/test_myobject.cpp
#include <QtTest/QtTest>
#include "Controller/Game.hpp"
#include "GameTest.hpp"
#include <vector>
using namespace std;

shared_ptr<Card> DeckCardTest::Get_Random_Card()
{
    return deck_cards[GameTest::nb_to_generate - 1];
}

int GameTest::nb_to_generate = 1;
void GameTest::testGameInit()
{
    Game game;
    QCOMPARE(game.state, GameState::DealingCards); // Init fini
    QCOMPARE(game.Get_Bank_Cards().size(), 0);
    QCOMPARE(game.Get_Player_Cards().size(), 0);
}
void GameTest::testStateInit()
{
    State_Init();
    QCOMPARE(Get_Bank_Cards().size(), 0);
    QCOMPARE(Get_Player_Cards().size(), 0);
}

void GameTest::testStateDealingCards()
{
    State_Init();
    State_DealingCards();
    QCOMPARE(Get_Bank_Cards().size(), 1);
    QCOMPARE(Get_Player_Cards().size(), 2);
}

void GameTest::testStatePlayerTurn()
{
    State_Init();
    state = GameState::PlayerTurn;
    State_PlayerTurn();
    QCOMPARE(Get_Bank_Cards().size(), 0);
    QCOMPARE(Get_Player_Cards().size(), 0);

    State_PlayerTurn('h');
    QCOMPARE(Get_Player_Cards().size(), 1);
    QCOMPARE(state, GameState::PlayerTurn);

    State_PlayerTurn('s');
    QCOMPARE(Get_Player_Cards().size(), 1);
    QCOMPARE(state, GameState::BankTurn);

    for (int i = 0; i < 20; i++)
    {
        State_PlayerTurn('h');
    }
    QCOMPARE(Get_Player_Cards().size(), 21);
    QCOMPARE(state, GameState::Finish);
}

void GameTest::testStateBankTurn()
{
    for (int i = 1; i <= 13; ++i)
    {
        State_Init();
        nb_to_generate = i;
        State_BankTurn();
        QVERIFY(Get_Score(Get_Bank_Cards()) >= 17);
    }
}

void GameTest::testStateFinish()
{
    State_Init();
    QCOMPARE(State_Finish(), false);
}

void GameTest::testDisplayResult()
{
    // --------- Premier test
    State_Init();
    // Crée un spy sur le signal
    QSignalSpy spy(&(*this), &Game::gameFinished);
    Display_Result();

    // Vérifie la valeur du signal
    QList<QVariant> arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toInt(), true);

    // --------- Deuxieme test : score_player > 21
    State_Init();
    nb_to_generate = 8;
    // Generation de 3 cartes pour le player de valeurs 8
    for (int i = 0; i < 3; ++i)
    {
        State_PlayerTurn('h');
    }
    Display_Result();

    // Vérifie la valeur du signal
    arguments = spy.takeFirst();
    Display_Game();
    QCOMPARE(arguments.at(0).toInt(), false);

    // --------- Troisieme test : bank_player > 21
    State_Init();
    nb_to_generate = 8;
    State_BankTurn(); // Genere 3 cartes de valeurs 8
    Display_Result();

    // Vérifie la valeur du signal
    arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toInt(), true);

    // --------- Quatrieme test : score_bank > score_player
    State_Init();
    nb_to_generate = 6;
    State_BankTurn();      // Genere 3 cartes de valeurs 6
    State_PlayerTurn('h'); // Genere 1 carte de valeur 6
    Display_Result();

    // Vérifie la valeur du signal
    arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toInt(), false);

    // --------- Cinquieme test : score_bank < score_player
    State_Init();
    nb_to_generate = 6;
    State_BankTurn(); // Genere 3 cartes de valeurs 6
    nb_to_generate = 7;
    for (int i = 0; i < 3; ++i) // Genere 3 cartes de valeurs 7
    {
        State_PlayerTurn('h');
    }
    Display_Result();

    // Vérifie la valeur du signal
    arguments = spy.takeFirst();
    QCOMPARE(arguments.at(0).toInt(), true);
}

void GameTest::testNextStep()
{
    State_Init();
    state = GameState::Init;
    Next_Step();
    QCOMPARE(state, GameState::DealingCards);

    Next_Step();
    QCOMPARE(state, GameState::PlayerTurn);

    Next_Step();
    QCOMPARE(state, GameState::PlayerTurn);

    state = GameState::PlayerTurnFinished;
    Next_Step();
    QCOMPARE(state, GameState::BankTurn);

    Next_Step();
    QCOMPARE(state, GameState::Finish);

    Next_Step();
    QCOMPARE(state, GameState::Init);
}

void GameTest::testStartGame()
{
    State_Init();
    state = GameState::Init;
    Start_Game();
    QCOMPARE(state, GameState::DealingCards);

    Start_Game();
    QCOMPARE(state, GameState::PlayerTurn);

    Start_Game();
    QCOMPARE(state, GameState::PlayerTurn);

    state = GameState::PlayerTurnFinished;
    Start_Game();
    QCOMPARE(state, GameState::BankTurn);

    Start_Game();
    QCOMPARE(state, GameState::Finish);

    Start_Game();
    QCOMPARE(state, GameState::Init);
}

int GameTest::Get_Score(vector<shared_ptr<Card>> cards) const
{
    int sum = 0;
    int nb_ace = 0;
    for (shared_ptr<Card> c : cards)
    {
        sum += c->Get_Value();
        if (c->Get_Number() == 1)
        {
            ++nb_ace;
        }
    }
    while (nb_ace > 0 and sum > 21)
    {
        sum -= 10; // Value of ace go from 11 to 1
        --nb_ace;
    }
    return sum;
}
