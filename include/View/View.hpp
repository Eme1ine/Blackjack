#pragma once
#include <QWidget>
#include <QLabel>
#include <memory>
#include <iostream>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>

#include "Controller/GameState.hpp"
#include "Model/Person/Bank.hpp"
#include "Model/Person/Player.hpp"
#include "View/BlackJackButton.hpp"
#include "View/ServicesView.hpp"

class View : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *bank_cards;
    QHBoxLayout *player_cards;
    QPixmap background;
    ServicesView services;

public:
    BlackjackButton *buttonNext;
    BlackjackButton *buttonHit;
    BlackjackButton *buttonStand;

public:
    explicit View(QWidget *parent = nullptr);
    ~View();
    void updateBank(std::vector<std::shared_ptr<Card>> cards);
    void updatePlayer(std::vector<std::shared_ptr<Card>> cards);
    void updateState(const GameState state);
    void popUpWinner(bool youWin);

signals:
    void enterPressed(); // signal envoye quand on appuie sur Entree
    void letterPressed(char value);
    void turnFinished();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};