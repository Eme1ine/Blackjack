// qttest/test_myobject.cpp
#include <QtTest/QtTest>
#include "Controller/Game.hpp"

class TestGame : public Game
{
    Q_OBJECT

private slots:
    void testStateInit()
    {
        QCOMPARE(state, GameState::DealingCards); // Init fini
        QCOMPARE(Get_Bank_Cards().size(), 0);
        QCOMPARE(Get_Player_Cards().size(), 0);
    }
};

// Cette macro génère le main() pour QtTest
QTEST_MAIN(TestGame)
#include "GameTest.moc"
