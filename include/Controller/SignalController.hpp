#pragma once

#include "Controller/Game.hpp"
#include "View/View.hpp"

class SignalController : public QObject
{
    Q_OBJECT
private:
    Game game;
    View view;
    int countUpdateFinished;

public:
    SignalController();
    ~SignalController();

    void updateView();

public slots:
    void onEnterPressed();
    void onLetterPressed(char value);
    void onLetterPressedH();
    void onLetterPressedS();
    void onTurnFinished();
    void onGameFinished(bool youWin);
};
