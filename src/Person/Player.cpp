#include "Person/Player.hpp"

#include <iostream>

using namespace std;

Player::Player(/* args */)
{
    cout << "Player create" << endl;
    SetCard1(8);
    SetCard2(5);
}

Player::~Player()
{
    cout << "Player destroy" << endl;
}
