#include <raylib.h>
#include "spaceship.hpp"
#include "game.hpp"
#include "laser.hpp"
#include "obstacle.hpp"

int main() {

    Color grey  = { 50, 50, 50, 255 };
    Color green = { 243, 216, 63, 255 };
    int offset  = 50;
    int windowWidth  = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset,windowHeight + (offset * 2),"Space Invaders on C++");
    Font font = LoadFont("src/Font/PixelifySans-Regular.ttf");
    Texture2D heart = LoadTexture("src/Graphics/heart2.png");
    SetTargetFPS(60);

    Game Game;

    while (WindowShouldClose() == false) {

        Game.HandleInput();
        Game.Update();

        BeginDrawing();
        ClearBackground(grey);

        if(Game.run)
        {
            DrawLineEx({20,float(windowHeight)+20},{float(windowWidth)+offset - 20,float(windowHeight)+20},3.0f,YELLOW);
            DrawRectangleRoundedLinesEx({10,10,780,780},0.18f,20,2,YELLOW);
            DrawTextEx(font,"LEVEL 01",{570,740}, 34, 2, YELLOW);
        } else {
            DrawLineEx({20,float(windowHeight)+20},{float(windowWidth)+offset - 20,float(windowHeight)+20},3.0f,RED);
            DrawRectangleRoundedLinesEx({10,10,780,780},0.18f,20,2,RED);
            DrawTextEx(font,"GAME OVER",{560,740}, 34, 2, RED);

        }

        for(int i = 0; i < Game.lives;i++)
        {
            DrawTextureV(heart,{float(60+i*60),735},WHITE);
        }

        Game.Draw();

        EndDrawing();
    } 
    
    CloseWindow();
    return 0;
}