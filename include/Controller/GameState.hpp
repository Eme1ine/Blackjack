#pragma once
enum GameState
{
    InitBegin,
    Init,
    InitFinished,
    PlayerTurn,
    PlayerTurnFinished,
    BankTurnBegin,
    BankTurn,
    BankTurnFinished,
    Finish,
};

constexpr const char *StateNames[] = {"InitBegin", "Init", "InitFinished", "PlayerTurn", "PlayerTurnFinished", "BankTurnBegin", "BankTurn", "BankTurnFinished", "Finish"};
