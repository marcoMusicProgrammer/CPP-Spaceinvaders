#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
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
        
        std::vector<Obstacle> CreateObstacles();

};