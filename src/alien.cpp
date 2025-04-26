#include "alien.hpp"

Texture2D Alien::images [3] = {};

Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;
    this->lastFireTime = 0.0;
    
    if(images[type -1].id == 0) {
        switch (type) {
            case 1:
                images[0] = LoadTexture("src/Graphics/alien_1.png");
                break;        
            case 2:
                images[1] = LoadTexture("src/Graphics/alien_2.png");
                break;
            case 3:
                images[2] = LoadTexture("src/Graphics/alien_3.png");
                break;
            default:
                images[0] = LoadTexture("src/Graphics/alien_1.png");
                break;
            }
    }
}

void Alien::Draw()
{   
    //FireLasers();
    DrawTextureV(images[type -1],position,WHITE);
}

int Alien::GetType() 
{
    return this->type;
}

void Alien::UnloadImages()
{
    std::cout << "Elimino le texture" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        UnloadTexture(images[i]);
    }
}

void Alien::Update(int direction)
{
    position.x += direction;
}

Rectangle Alien::GetRect()
{
    return {position.x,position.y,float(images[type -1].width),float(images[type -1].height)};
}