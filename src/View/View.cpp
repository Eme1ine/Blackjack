
#include "View/View.hpp"
#include "Model/Person/Bank.hpp"
#include <QVBoxLayout>
#include <QKeyEvent>

#include <memory>
#include <iostream>

using namespace std;

View::View(QWidget *parent)
    : QWidget(parent),
      bank_cards(),
      player_cards(),
      background("img/0_background.jpg")
{
    resize(500, 500);
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    // ----- Section du haut (banque) -----
    QWidget *bankSection = new QWidget(this);
    bankSection->setMinimumHeight(200);
    bankSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    bank_cards = new QHBoxLayout(bankSection);
    bank_cards->setSpacing(8);
    bank_cards->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(bankSection, 1);

    // ----- Section du bas (joueur) -----
    QWidget *playerSection = new QWidget(this);
    playerSection->setMinimumHeight(200);
    playerSection->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    player_cards = new QHBoxLayout(playerSection);
    player_cards->setSpacing(8);
    player_cards->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(playerSection, 1);

    setWindowTitle("MyWindow Example");
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
