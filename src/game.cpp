#include "game.hpp"
#include <iostream>
#include <vector>

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

    DeleteInactiveLaser();

    //std::cout << "Number of laser hit: " << spaceship.lasers.size() << std::endl;
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }

    for(auto& obstacle: this -> obstacles) {
        obstacle.Draw();
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
    }

    if (IsKeyDown(KEY_SPACE))
    {
        spaceship.fireLaser();
    } 
}

void Game::DeleteInactiveLaser()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it -> active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++ it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    for(int i = 1; i < 5; i++) {

        obstacles.push_back(Obstacle({,10}));
    }
}