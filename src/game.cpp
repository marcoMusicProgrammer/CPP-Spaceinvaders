#include "game.hpp"
#include <iostream>
#include <vector>
#include <fstream>

Game::Game()
{
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
    mysteryship.UnloadImage();
}


void Game::Update()
{
    if(run)
    {
        float currentTime = GetTime();
        if(currentTime - lastTimeMysteryship >= mysteryShipSpawnInterval) {
            mysteryship.Spawn();
            lastTimeMysteryship = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10,20);
        }
    
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
        
        CheckForCollisions();
    } else {
        if(IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }
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
    if(run)
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
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;

    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 11; column++) {
            float x = 75    + column    * 55;
            float y = 180   + row       * 55;

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
        if(alien.position.x + alien.images[alien.type -1].width > GetScreenWidth() - 25) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }

        if(alien.position.x < 25) {
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
    if(currentTime - timeLastAlienFire >= alienLaserShootInterval && !aliens.empty())
    {
        int randomValue = GetRandomValue(0, aliens.size() -1);
        Alien& alien = aliens[randomValue];
        alienLasers.push_back(Laser({alien.position.x + (alien.images[alien.type -1].width / 2), alien.position.y + alien.images[alien.type -1].height},4));
        timeLastAlienFire = GetTime();
    }
}

void Game::CheckForCollisions() {
    
    // Spaceship lasers collision
    for(auto& laser: spaceship.lasers)
    {
        // Collision against aliens
        auto it = aliens.begin();
        while(it != aliens.end())
        {
            if(CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
            {
                it = aliens.erase(it);
                laser.active = false;
                if(it -> type == 1) {
                    score += 10;
                } else if (it -> type == 2) {
                    score += 30;
                } else {
                    score += 50;
                }

                CheckForHighscore();

            } else {
                ++it;
            }
        }

        // Collision against shields
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        // Collision against mysteryship
        if(CheckCollisionRecs(mysteryship.GetRect(), laser.GetRect()))
        {
            mysteryship.state = false;
            laser.active = false;

            score += 100;

            CheckForHighscore();
        }
    }

    for(auto& laser: alienLasers)
    {
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it -> GetRect(),laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(spaceship.GetRect(),laser.GetRect()))
        {
            lives --;
            laser.active = false;

            if(lives == 0)
            {
                GameOver();
            }

        }
    }

    for(auto& alien: aliens)
    {
        for(auto& obstacle: obstacles)
        {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end())
            {
                if(CheckCollisionRecs(it -> GetRect(),alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(spaceship.GetRect(),alien.GetRect()))
        {
            GameOver();
        }
    }
}

void Game::CheckForHighscore()
{
    if(score > highscore)
    {
        highscore = score;
        SaveHighscoreToFile(highscore);
    }
}

void Game::SaveHighscoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Error occured opening highscore.txt file" << std::endl;
    }
}

int Game::LoadHighscoreToFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Error occured opening highscore.txt file" << std::endl;
    }

    return loadedHighscore;
}

void Game::GameOver()
{
    std::cout << "Game Over" << std::endl;
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFire = 0.0;
    lastTimeMysteryship = 0.0;
    lives = 3;
    run = true;
    score = 0;
    highscore = LoadHighscoreToFile();

    mysteryShipSpawnInterval = GetRandomValue(10,20);
}