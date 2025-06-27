#include "Person/Player.hpp"

#include <iostream>

using namespace std;

Player::Player(/* args */)
{
    cout << "Player create" << endl;
}

Player::~Player()
{
    cout << "Player destroy" << endl;
}
