#pragma once
#include <raylib.h>

class Mysteryship {
    public:
        Mysteryship();
        ~Mysteryship();

        void Update();
        void Draw();
        void Spawn();
        void UnloadImage();

        bool state;
        Texture2D image;
        Vector2 position;
        int speed;

        
    private:
};