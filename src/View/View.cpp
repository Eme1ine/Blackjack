
#include "View/View.hpp"
#include "Model/Person/Bank.hpp"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QMessageBox>
#include "View/BlackJackButton.hpp"

#include <memory>
#include <iostream>

using namespace std;

View::View(QWidget *parent)
    : QWidget(parent),
      bank_cards(),
      player_cards(),
      background("img/0_background.jpg")
{
    resize(700, 500);
    QHBoxLayout *bigLayout = new QHBoxLayout(this);
    bigLayout->setContentsMargins(0, 0, 0, 0);
    bigLayout->setSpacing(0);
    setLayout(bigLayout);

    // ----- Section gauche (jeux) -----
    QWidget *gameSection = new QWidget(this);
    gameSection->setFixedSize(500, 500);
    bigLayout->addWidget(gameSection);

    // ----- Section droite (bouton) -----
    QWidget *boutonSection = new QWidget(this);
    boutonSection->setFixedSize(200, 500);
    bigLayout->addWidget(boutonSection);

    // ----- Section droite remplissage -----
    QVBoxLayout *boutonLayout = new QVBoxLayout(boutonSection);
    boutonLayout->setContentsMargins(10, 10, 10, 10);
    boutonLayout->setSpacing(5);
    boutonLayout->setAlignment(Qt::AlignBottom | Qt::AlignHCenter);

    buttonHit = new BlackjackButton("Hit", boutonSection);
    boutonLayout->addWidget(buttonHit);
    buttonStand = new BlackjackButton("Stand", boutonSection);
    boutonLayout->addWidget(buttonStand);
    buttonNext = new BlackjackButton("Next", boutonSection);
    boutonLayout->addWidget(buttonNext);

    // ----- Section gauche remplissage -----
    gameLayout = new QVBoxLayout(gameSection);
    gameLayout->setContentsMargins(0, 0, 0, 0);
    gameLayout->setSpacing(0);

    // ----- Section du haut (banque) -----
    QWidget *bankSection = new QWidget(gameSection);
    bankSection->setMinimumHeight(200);
    bankSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    bank_cards = new QHBoxLayout(bankSection);
    bank_cards->setSpacing(8);
    bank_cards->setAlignment(Qt::AlignCenter);

    gameLayout->addWidget(bankSection, 1);

    // ----- Section du bas (joueur) -----
    QWidget *playerSection = new QWidget(gameSection);
    playerSection->setMinimumHeight(200);
    playerSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    player_cards = new QHBoxLayout(playerSection);
    player_cards->setSpacing(8);
    player_cards->setAlignment(Qt::AlignCenter);

    gameLayout->addWidget(playerSection, 1);

    setWindowTitle("BlackJack");
    setFocusPolicy(Qt::StrongFocus);
}

View::~View()
{
    cout << "View Destroy" << endl;
}

void View::updateBank(const Bank &bank)
{
    services.updatePerson(bank, bank_cards, this);
}

void View::updatePlayer(const Player &player)
{
    services.updatePerson(player, player_cards, this);
}

void View::updateState(const GameState state)
{
    if (state == PlayerTurn)
    {
        buttonNext->setVisible(false);
        buttonHit->setVisible(true);
        buttonStand->setVisible(true);
    }
    else
    {
        buttonHit->setVisible(false);
        buttonStand->setVisible(false);
        buttonNext->setVisible(true);
    }
}

void View::popUpWinner(bool youWin)
{
    if (youWin)
    {
        QMessageBox::information(this, "Blackjack", "🎉 YOU WIN!");
    }
    else
    {
        QMessageBox::information(this, "Blackjack", "LOOOOSER!");
    }
}

void View::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        emit enterPressed(); // envoie le signal
    else if (event->key() == Qt::Key_S)
    {
        emit letterPressed('s');
    }
    else if (event->key() == Qt::Key_H)
    {
        emit letterPressed('h');
    }
    else
        QWidget::keyPressEvent(event);
}
