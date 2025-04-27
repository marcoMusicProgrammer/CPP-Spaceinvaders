#include <raylib.h>
#include "spaceship.hpp"
#include "game.hpp"
#include "laser.hpp"
#include "obstacle.hpp"

int main() {

    Color grey = { 50, 50, 50, 255 };
    int windowWidth = 800;
    int windowHeight = 800;

    InitWindow(windowWidth,windowHeight,"Space Invaders on C++");
    SetTargetFPS(60);

    Game Game;

    while (WindowShouldClose() == false) {

        Game.HandleInput();
        Game.Update();

        BeginDrawing();
        ClearBackground(grey);

        Game.Draw();

        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}