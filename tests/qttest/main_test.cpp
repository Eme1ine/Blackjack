#include <QApplication>
#include <QtTest/QtTest>

#include "ServicesViewTest.hpp"
#include "GameTest.hpp"

int main(int argc, char **argv)
{
    // Choisis QApplication seulement si tu utilises QWidget/QLabel/animations etc.
    QApplication app(argc, argv);

    int totalReturn = 0;

    {
        ServicesViewTest servicesTest;
        totalReturn |= QTest::qExec(&servicesTest, argc, argv);
    }

    {
        GameTest gameTest;
        totalReturn |= QTest::qExec(&gameTest, argc, argv);
    }

    // Si tu veux exécuter plus de tests, répète la même chose
    return totalReturn;
}
