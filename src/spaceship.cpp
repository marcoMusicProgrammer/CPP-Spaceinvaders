#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("src/Graphics/Ship_1.png");
    position.x = GetScreenWidth()/2 - image.width/2;
    position.y = GetScreenHeight() - image.height - 10;
    lastFireTime = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    DrawTexture(image, position.x,position.y, WHITE);
}

void Spaceship::moveLeft()
{
    if (position.x < 1)
    {    
        position.x = 0;
    }
    else
    {
        position.x -= 3;
    } 
}

void Spaceship::moveRight()
{
    if (position.x > GetScreenWidth() - (image.width + 1))
    {
        position.x = GetScreenWidth() - image.width;
    }
    else
    {
        position.x += 3;
    }
}

void Spaceship::fireLaser()
{
    if (GetTime() - lastFireTime >= 0.15){
        lasers.push_back(Laser({position.x + (image.width/2),position.y},-10));
        lastFireTime = GetTime();
    }
}

Rectangle Spaceship::GetRect()
{
    return {position.x,position.y,float(image.width),float(image.height)};
}