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

        constexpr static float alienLaserShootInterval{0.35};
        int aliensDirection;
        float timeLastAlienFire;

        Mysteryship mysteryship;
        float lastTimeMysteryship;
        void RespawnMysteryship();
        // void MoveMysteryship();
        // void DeleteInactiveMysteryship();
};