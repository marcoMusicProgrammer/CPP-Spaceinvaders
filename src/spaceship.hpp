#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Spaceship {
    public:
        Spaceship();
        ~Spaceship();

        void Draw();
        void moveLeft();
        void moveRight();
        void fireLaser();
        Rectangle GetRect();

        std::vector<Laser> lasers;


    private:
        Texture2D image;
        Vector2 position;
        double lastFireTime;
};