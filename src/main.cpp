#include "Controller/Game.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <QApplication>
#include <QLabel>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "Hello World" << endl;

    // Demarrage de la vue QT
    QApplication app(argc, argv);

    // Demarrage du jeu
    Game game = Game();
    //  game.Start_Game();
    return app.exec();
}