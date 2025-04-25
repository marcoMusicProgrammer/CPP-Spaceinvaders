#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed; 
    this -> active = true;
}

Laser::~Laser()
{

}

void Laser::Draw() 
{
    if(active)
    {
        DrawRectangle(position.x,position.y,4,10,WHITE);
    }
}

void Laser::Update()
{
    position.y += speed;
    // std::cout << "Posizione laser: " << position.x << ", " << position.y <<  std::endl;
    if (position.y > GetScreenHeight() || position.y < 0)
    {
        active = false;
    }
}