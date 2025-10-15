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
#include "View/ServicesView.hpp"

class View : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *bank_cards;
    QHBoxLayout *player_cards;
    QVBoxLayout *gameLayout;
    QPixmap background;
    ServicesView services;

public:
    QPushButton *buttonNext;
    QPushButton *buttonHit;
    QPushButton *buttonStand;

public:
    explicit View(QWidget *parent = nullptr);
    ~View();
    void updateBank(const Bank &bank);
    void updatePlayer(const Player &player);
    void updateState(const GameState state);

signals:
    void enterPressed(); // signal envoye quand on appuie sur Entree
    void letterPressed(char value);
    void turnFinished();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.drawPixmap(rect(), background); // scale to fill
    }
};