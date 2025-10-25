// qttest/test_myobject.cpp
#include <QtTest/QtTest>
#include "Controller/Game.hpp"
#include <vector>
using namespace std;

class GameTest;

class DeckCardTest : public DeckCards
{
public:
    shared_ptr<Card> Get_Random_Card() override;
};

class GameTest : public Game
{
    Q_OBJECT
public:
    static int nb_to_generate;
    GameTest() : Game(new DeckCardTest())
    {
    }

private slots:
    void testGameInit();
    void testStateInit();

    void testStateDealingCards();

    void testStatePlayerTurn();

    void testStateBankTurn();

    void testStateFinish();

    void testDisplayResult();

    void testNextStep();

    void testStartGame();

    int Get_Score(vector<shared_ptr<Card>> cards) const;
};
