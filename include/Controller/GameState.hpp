#pragma once
enum GameState
{
    Init,
    DealingCards,
    PlayerTurn,
    PlayerTurnFinished,
    BankTurn,
    Finish,
};

constexpr const char *StateNames[] = {"Init", "DealingCards", "PlayerTurn", "PlayerTurnFinished", "BankTurn", "Finish"};
