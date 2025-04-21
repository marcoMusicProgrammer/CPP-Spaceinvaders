#include <raylib.h>
#include "spaceship.hpp"
#include "game.hpp"
#include "laser.hpp"

int main() {

    Color grey = { 50, 50, 50, 255 };
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth,windowHeight,"Space Invaders on C++");
    SetTargetFPS(60);

    Game Game;
    Laser laser = Laser({100,0},10);

    while (WindowShouldClose() == false) {

        Game.HandleInput();
        laser.Update();
        Game.Update();

        BeginDrawing();
        ClearBackground(grey);

        Game.Draw();
        laser.Draw();

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}