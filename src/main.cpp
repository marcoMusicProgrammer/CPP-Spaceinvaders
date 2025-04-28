#include <raylib.h>
#include "spaceship.hpp"
#include "game.hpp"
#include "laser.hpp"
#include "obstacle.hpp"

std::string FormattingWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros,'0') + numberText;
}

int main() {

    Color grey  = { 50, 50, 50, 255 };
    //Color green = { 243, 216, 63, 255 };
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
            // Inner Rectangle
            DrawRectangleRoundedLinesEx({10,10,780,780},0.18f,20,2,YELLOW);
            // Level Text
            DrawTextEx(font,"LEVEL 01",{570,740}, 34, 2, YELLOW);
            // Score text
            DrawTextEx(font, "SCORE", {60,20}, 34, 2, YELLOW);
            std::string scoreText = FormattingWithLeadingZeros(Game.score,5);
            DrawTextEx(font,scoreText.c_str(),{60,50},34,2,YELLOW);
            // Highscore text
            DrawTextEx(font, "HIGHSCORE", {float(windowWidth+offset)-210,20}, 34, 2, YELLOW);
            std::string highscoreText = FormattingWithLeadingZeros(Game.highscore,5);
            DrawTextEx(font,highscoreText.c_str(),{float(windowWidth+offset)-145,50},34,2,YELLOW);
        } else {
            DrawLineEx({20,float(windowHeight)+20},{float(windowWidth)+offset - 20,float(windowHeight)+20},3.0f,RED);
            // Inner Rectangle`
            DrawRectangleRoundedLinesEx({10,10,780,780},0.18f,20,2,RED);
            // Level Text
            DrawTextEx(font,"GAME OVER",{560,740}, 34, 2, RED);
            // Score text
            DrawTextEx(font, "SCORE", {60,20}, 34, 2, RED);
            std::string scoreText = FormattingWithLeadingZeros(Game.score,5);
            DrawTextEx(font,scoreText.c_str(),{60,50},34,2,RED);
            // Highscore text
            DrawTextEx(font, "HIGHSCORE", {float(windowWidth+offset)-210,20}, 34, 2, RED);
            std::string highscoreText = FormattingWithLeadingZeros(Game.highscore,5);
            DrawTextEx(font,highscoreText.c_str(),{float(windowWidth+offset)-145,50},34,2,RED);
        }

        for(int i = 0; i < Game.lives;i++)
        {
            DrawTextureV(heart,{float(60 + (i*60)),735},WHITE);
        }

        Game.Draw();

        EndDrawing();
    } 
    
    CloseWindow();
    return 0;
}