#include "mysteryship.hpp"
#include <iostream>


Mysteryship::Mysteryship()
{
    image = LoadTexture("src/Graphics/mystery.png");
    state = false;
}

Mysteryship::~Mysteryship()
{

}

void Mysteryship::Draw()
{   
    if(state)
    {
        DrawTextureV(image,position,WHITE);
    }
}

void Mysteryship::Spawn()
{
    
    position.y = 90;
    int randomDirection = GetRandomValue(0,1);
    int randomSpeed = GetRandomValue(4,8);

    if(randomDirection == 1) {
        position.x = 25;
        speed = randomSpeed;
    } else {
        position.x = GetScreenWidth() - 105;
        speed = -randomSpeed;
    }

    state = true;
}

void Mysteryship::Update()
{
    if(state)
    {
        position.x += speed;
    
        if(position.x < 25 || position.x > GetScreenWidth() - 105)
        {
            state = false;
        }
    }
}

void Mysteryship::UnloadImage()
{
    UnloadTexture(image);
}

Rectangle Mysteryship::GetRect()
{
    if(state)
    {
        return {
            position.x,
            position.y,
            float(image.width),
            float(image.height),
        };
    } else {
        return {
            position.x,
            position.y,
            0,
            0
        };
    }
}