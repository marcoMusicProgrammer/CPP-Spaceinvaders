#include "game.hpp"
#include <iostream>

Game::Game()
{
}

Game::~Game()
{
}

void Game::Update()
{
    for (auto& laser: spaceship.lasers)
    {
        laser.Update();
    }
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }
    
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.moveLeft();

    } else if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.moveRight();

    } else if (IsKeyDown(KEY_SPACE))
    {
        spaceship.fireLaser();
    }
}