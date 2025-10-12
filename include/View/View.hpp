#pragma once
#include <QWidget>
#include <QLabel>
#include <memory>
#include <iostream>
#include <QVBoxLayout>
#include "Model/Person/Bank.hpp"
#include "Model/Person/Player.hpp"

class View : public QWidget
{
    Q_OBJECT
private:
    std::unique_ptr<QHBoxLayout> bank_cards;
    std::unique_ptr<QHBoxLayout> player_cards;
    std::unique_ptr<QVBoxLayout> layout;

public:
    explicit View(QWidget *parent = nullptr);
    ~View();
    void updateBank(const Bank &bank);
    void updatePlayer(const Player &player);
    QPixmap renderSvg(const std::string name, const QSize &outSize);

signals:
    void enterPressed(); // signal envoyé quand on appuie sur Entrée
    void letterPressed(char value);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};