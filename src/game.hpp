#pragma once
#include "spaceship.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void Update();
        void HandleInput();
        void Draw();
    private:
        Spaceship spaceship;

};