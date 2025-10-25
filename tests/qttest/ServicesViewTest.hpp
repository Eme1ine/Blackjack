#pragma once
#include <QtTest/QtTest>
#include <QObject>
#include "Model/Card.hpp"

class TestView : public QWidget
{
    Q_OBJECT
public:
    explicit TestView(QWidget *parent = nullptr) : QWidget(parent) {}
signals:
    void turnFinished();
};

class ServicesViewTest : public QObject
{
    Q_OBJECT
private slots:
    std::shared_ptr<Card> generateCard(int i);
    void test_updatePerson_empty_clears_layout_and_emits();
    void test_updatePerson_adds_cards_and_emits_after_animations();
};
