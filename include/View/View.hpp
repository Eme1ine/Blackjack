#pragma once
#include <QWidget>
#include <QLabel>
#include <memory>
#include <iostream>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QParallelAnimationGroup>
#include "Model/Person/Bank.hpp"
#include "Model/Person/Player.hpp"

class View : public QWidget
{
    Q_OBJECT
private:
    QHBoxLayout *bank_cards;
    QHBoxLayout *player_cards;
    QVBoxLayout *mainLayout;
    QPixmap background;

public:
    explicit View(QWidget *parent = nullptr);
    ~View();
    void updateBank(const Bank &bank);
    void updatePlayer(const Player &player);
    void updatePerson(const Person &person, QHBoxLayout *layout_person);
    QPixmap renderSvg(const std::string name, const QSize &outSize);

signals:
    void enterPressed(); // signal envoye quand on appuie sur Entree
    void letterPressed(char value);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.drawPixmap(rect(), background); // scale to fill
    }
    QParallelAnimationGroup *addCardFromRight(QHBoxLayout *targetLayout, const QPixmap &pix);
    void dealBankSequential(QHBoxLayout *layout, const QVector<QPixmap> &pix, int idx);
};