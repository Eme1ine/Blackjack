// qttest/test_myobject.cpp
#include <QtTest/QtTest>
#include "Controller/Game.hpp"
#include <vector>
using namespace std;
class DeckCardTest : public DeckCards
{
public:
    shared_ptr<Card> Get_Random_Card() override
    {
        return deck_cards[0];
    }
};
class TestGame : public Game
{
    Q_OBJECT
public:
    TestGame() : Game(DeckCardTest())
    {
    }

private slots:
    void testGameInit()
    {
        QCOMPARE(state, GameState::Init); // Init fini
        QCOMPARE(Get_Bank_Cards().size(), 0);
        QCOMPARE(Get_Player_Cards().size(), 0);
    }
    void testStateInit()
    {
        State_Init();
        QCOMPARE(Get_Bank_Cards().size(), 0);
        QCOMPARE(Get_Player_Cards().size(), 0);
    }

    void testStateDealingCards()
    {
        State_Init();
        State_DealingCards();
        QCOMPARE(Get_Bank_Cards().size(), 1);
        QCOMPARE(Get_Player_Cards().size(), 2);
    }

    void testStatePlayerTurn()
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

    void testStateBankTurn()
    {
        for (int i = 0; i < 1000; ++i)
        {
            State_Init();
            State_BankTurn();
            QVERIFY(Get_Score(Get_Bank_Cards()) >= 17);
        }
    }

    int Get_Score(vector<shared_ptr<Card>> cards) const
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
};
// Cette macro génère le main() pour QtTest
QTEST_MAIN(TestGame)
#include "GameTest.moc"
