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

class View;

class ServicesView
{

    QPixmap renderSvg(const std::string name, const QSize &outSize);
    QParallelAnimationGroup *addCardFromRight(QHBoxLayout *targetLayout, const QPixmap &pix, View *window);
    void dealBankSequential(QHBoxLayout *layout, const QVector<QPixmap> &pix, int idx, View *window);

public:
    void updatePerson(const Person &person, QHBoxLayout *layout_person, View *window);
};