
#include "View/View.hpp"
#include "Model/Person/Bank.hpp"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>

#include <iostream>

using namespace std;

View::View(QWidget *parent)
    : QWidget(parent),
      bank_cards(std::make_unique<QHBoxLayout>()),
      player_cards(std::make_unique<QHBoxLayout>())
{
    bank_cards->setAlignment(Qt::AlignCenter);
    player_cards->setAlignment(Qt::AlignCenter);

    layout = make_unique<QVBoxLayout>(this);
    layout->addLayout(bank_cards.get());
    layout->addLayout(player_cards.get());

    // resize(300, 100);
    setWindowTitle("MyWindow Example");
    setFocusPolicy(Qt::StrongFocus);
}

View::~View()
{
    cout << "View Destroy" << endl;
}

void View::updateBank(const Bank &bank)
{
    // bank_cards->setText(QString::number(bank.Get_Score()));
    //  1) vider l’ancien contenu
    QLayoutItem *item;
    while ((item = bank_cards->takeAt(0)) != nullptr)
    {
        delete item->widget(); // détruit le widget
        delete item;           // détruit le layoutItem
    }

    // 2) ajouter les nouvelles cartes
    for (auto card_ptr : bank.Get_Cards())
    {
        QLabel *cardLabel = new QLabel(QString::fromStdString(string(card_ptr->Get_Number_string())));
        cardLabel->setAlignment(Qt::AlignCenter);
        cardLabel->setStyleSheet("border: 1px solid gray; padding: 5px;");
        bank_cards->addWidget(cardLabel);
    }
}

void View::updatePlayer(const Player &player)
{

    //  1) vider l’ancien contenu
    QLayoutItem *item;
    while ((item = player_cards->takeAt(0)) != nullptr)
    {
        delete item->widget(); // détruit le widget
        delete item;           // détruit le layoutItem
    }

    // 2) ajouter les nouvelles cartes
    for (auto card_ptr : player.Get_Cards())
    {
        QLabel *cardLabel = new QLabel(QString::fromStdString(string(card_ptr->Get_Number_string())));
        cardLabel->setAlignment(Qt::AlignCenter);
        cardLabel->setStyleSheet("border: 1px solid gray; padding: 5px;");
        player_cards->addWidget(cardLabel);
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