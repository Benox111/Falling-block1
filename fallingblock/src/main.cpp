#include "raylib.h"
#include <iostream>
#include <string>
using namespace std;

class Player
{
    public:
        int positionX = 300;
        int positionY = 400;
        float speed = 10;    
        float friction; 
        Vector2 velocity = {0, 0};
};
class Block{
    public: 
        int positionX = 300;
        int positionY = 0;
};
int main()
{
   
    int counter = 0;
    Player player;
    Block block;
    int screenHeight = 800;
    int screenWidth = 500;
    InitWindow(screenHeight, screenWidth, "Falling Blocks");
    InitAudioDevice();
    SetTargetFPS(60);
    Texture2D playerTextur = LoadTexture("./Graphics/bucket.png"); 
    Texture2D blockTextur = LoadTexture("./Graphics/drop.png"); 
    Texture2D background = LoadTexture("Graphics/background.png");

    Sound soundEffect = LoadSound("Graphics/drop.mp3");
    Music music = LoadMusicStream("Graphics/music.mp3");
    PlayMusicStream(music);
    SetMusicVolume(music , 1.0f);
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        
        UpdateMusicStream(music);
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        block.positionY += 5;
        if (block.positionY > GetScreenHeight())
        {
            block.positionY = 0;
            counter = 0;
        }
        
        if (IsKeyDown(KEY_LEFT)) player.positionX -= player.speed;
        if (IsKeyDown(KEY_RIGHT)) player.positionX += player.speed;
        player.velocity.x *= player.friction;
        player.positionX += player.velocity.x * GetFrameTime();
                // Define rectangles for collision detection
        Rectangle playerRect = { (float)player.positionX, (float)player.positionY, 100, 30 }; // Player's rectangle
        Rectangle blockRect = { (float)block.positionX, (float)block.positionY, 25, 25 };   // Block's rectangle
        if (CheckCollisionRecs(playerRect, blockRect) == true)
        {
            block.positionY = 0;
            PlaySound(soundEffect);
            block.positionX = GetRandomValue(20, 650);  
            counter++;
        }
    // For the left side of the screen
    if (player.positionX <= -playerTextur.width)
    {
        player.positionX = 800 - playerTextur.width;  // Wrap around to the right side
    }

    // For the right side of the screen
    if (player.positionX >= 800)
    {
        player.positionX = 0;  // Wrap around to the left side
    }


        DrawTexture(playerTextur,(float)player.positionX, (float)player.positionY, WHITE); 
        DrawTextureEx(blockTextur,Vector2{(float)block.positionX, (float)block.positionY},0.0f, 0.4f ,WHITE);
        DrawText(TextFormat("%d",counter), 100, 100, 40, BLACK);
        EndDrawing();
    }
    CloseAudioDevice();
    UnloadTexture(playerTextur);
    UnloadTexture(background);
    UnloadTexture(blockTextur);
    CloseWindow();
    
}