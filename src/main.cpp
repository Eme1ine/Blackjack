#include "Controller/Game.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <QApplication>
#include <QFile>
#include <QLatin1String>
#include <QString>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World" << endl;

    // Demarrage de la vue QT
    QApplication app(argc, argv);
    QFile styleFile("styles/blackjack.qss");
    if (styleFile.open(QFile::ReadOnly))
    {
        QString style = QLatin1String(styleFile.readAll());
        app.setStyleSheet(style);
    }

    // Demarrage du jeu
    Game game = Game();
    //  game.Start_Game();
    return app.exec();
}