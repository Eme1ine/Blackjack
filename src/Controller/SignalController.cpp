#include "Controller/SignalController.hpp"
#include "View/View.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

SignalController::SignalController()
{
    cout << "SignalController Creation" << endl;
    // Ajout des connection entre signal et slot
    QObject::connect(&view, &View::enterPressed, this, onEnterPressed);
    QObject::connect(&view, &View::letterPressed, this, onLetterPressed);
    QObject::connect(&view, &View::turnFinished, this, onTurnFinished);
    QObject::connect(view.buttonNext, &QPushButton::released, this, onEnterPressed);
    QObject::connect(view.buttonHit, &QPushButton::released, this, onLetterPressedH);
    QObject::connect(view.buttonStand, &QPushButton::released, this, onLetterPressedS);
    QObject::connect(&game, &Game::gameFinished, this, onGameFinished);

    view.show();
    countUpdateFinished = 2;
    updateView();
}

SignalController::~SignalController()
{
    cout << "SignalController Destroy" << endl;
}

void SignalController::onEnterPressed()
{
    cout << countUpdateFinished << endl;
    if (countUpdateFinished == 2)
    {
        std::cout << "Enter pressed -> action triggered in GameController\n";
        game.Start_Game();
        updateView();
    }
}

void SignalController::onLetterPressedS()
{
    onLetterPressed('s');
    // view.updateState(game.state);
    // view.updatePlayer(game.Get_Player_Cards());
}

void SignalController::onLetterPressedH()
{
    // view.updateState(game.state);
    // view.updatePlayer(game.Get_Player_Cards());
    onLetterPressed('h');
}
void SignalController::onLetterPressed(char value)
{
    if (countUpdateFinished == 2)
    {
        std::cout << "letter pressed -> " << value << endl;
        if (game.state == PlayerTurn)
        {
            game.State_PlayerTurn(value);
        }
        updateView();
    }
}
void SignalController::onTurnFinished()
{
    ++countUpdateFinished;
}

void SignalController::updateView()
{
    if (countUpdateFinished == 2)
    {
        countUpdateFinished = 0;
        view.updateState(game.state);
        view.updateBank(game.Get_Bank_Cards());
        view.updatePlayer(game.Get_Player_Cards());
    }
}
void SignalController::onGameFinished(bool youWin)
{
    view.popUpWinner(youWin);
}