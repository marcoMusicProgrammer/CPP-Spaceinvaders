#pragma once
#include "spaceship.hpp"
#include "mysteryship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include <vector>

class Game
{
    public:
        Game();
        ~Game();
        void Update();
        void HandleInput();
        void Draw();
        void DeleteInactiveLaser();

        bool run;
        int lives;
        int score;
        int highscore;
      
    private:
        Spaceship spaceship;
        std::vector <Obstacle> obstacles;
        std::vector <Alien> aliens;  
        std::vector <Obstacle> CreateObstacles();
        std::vector <Alien> CreateAliens();
        std::vector <Laser> alienLasers;

        void MoveAliens();
        void MoveDownAliens(int distance);
        void AliensFireLaser();
        void CheckForHighscore();

        constexpr static float alienLaserShootInterval{0.35};
        int aliensDirection;
        float timeLastAlienFire;

        Mysteryship mysteryship;
        float lastTimeMysteryship;
        int mysteryShipSpawnInterval;

        void CheckForCollisions();

        void GameOver();
        void Reset();
        void InitGame();

        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreToFile();
};