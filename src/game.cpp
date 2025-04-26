#include "game.hpp"
#include <iostream>
#include <vector>

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    mysteryship.Spawn();
    aliensDirection = 1;
    timeLastAlienFire = 0.0;
    lastTimeMysteryship = 0.0;
}

Game::~Game()
{
    Alien::UnloadImages();
    mysteryship.UnloadImage();
}


void Game::Update()
{
    for (auto& laser: spaceship.lasers)
    {
        laser.Update();
    }

    AliensFireLaser();

    for (auto& laser : alienLasers) {
        laser.Update();
    }

    DeleteInactiveLaser();
    MoveAliens();

    mysteryship.Update();
    
    //std::cout << "Number of alien laser hit: " << alienLasers.size() << std::endl;
    RespawnMysteryship();
    
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }

    for (auto& obstacle: obstacles) {
        obstacle.Draw();
    }

    for (auto& alien: aliens) {
        alien.Draw();
    }

    for (auto& laser : alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
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
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it -> active)
        {
            it = spaceship.lasers.erase(it);
        } else {
            ++ it;
        }
    }

    for(auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if(!it -> active)
        {
            it = alienLasers.erase(it);
        } else {
            ++ it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    int paddingSpace = (GetScreenWidth() - (obstacleWidth * 4)) / 5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * paddingSpace + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;

    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {
            float x = 75    + column    * 55;
            float y = 110   + row       * 55;

            if(row == 0) {
                aliens.push_back(Alien(3, {x, y}));
            } else if (row == 2 || row == 3) {
                aliens.push_back(Alien(2, {x, y}));
            } else {
                aliens.push_back(Alien(1, {x, y}));
            }
        }
    }

    return aliens;
}

void Game::MoveAliens()
{
    for(auto& alien : aliens) {
        if(alien.position.x + alien.images[alien.type -1].width > GetScreenWidth()) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }

        if(alien.position.x < 0) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }

        alien.Update(aliensDirection);
    } 
}

void Game::MoveDownAliens(int distance)
{
    for(auto& alien: aliens){
        alien.position.y += distance;
    }
}

void Game::AliensFireLaser()
{

    double currentTime = GetTime();
    if(currentTime - timeLastAlienFire >= alienLaserShootInterval)
    {
        int randomValue = GetRandomValue(0, aliens.size() -1);
        Alien& alien = aliens[randomValue];
        alienLasers.push_back(Laser({alien.position.x + (alien.images[alien.type -1].width / 2), alien.position.y + alien.images[alien.type -1].height},4));
        timeLastAlienFire = GetTime();
    }
}

void Game::RespawnMysteryship()
{
    float currentTime = GetTime();
    if(currentTime - lastTimeMysteryship >= 10 && mysteryship.state == false) {
        mysteryship.Spawn();
        lastTimeMysteryship = GetTime();
    }
}

// void Game::MoveMysteryship()
// {

//     if(mysteryship.size() > 0)
//     {
//         if(myst)
//         mysteryship[0].Update(2);
//     }
// }

// void Game::DeleteInactiveMysteryship()
// {
//     for(auto it = mysteryship.begin(); it != mysteryship.end();) {
//         if(!it -> state) {
//             std::cout << "Sto eliminando mysteryshi " << std::endl;
//             mysteryship.erase(it);
//         } else {
//             it++;
//         }
//     }
// }