//
// Created by Mike on 7/18/2019.
//

#ifndef MADHAV_GAME_H
#define MADHAV_GAME_H
#include <SDL2/SDL.h>
#include <cstdlib>

class Game{
public:
    Game();
    // Initialize the game
    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shutdown the game
    void Shutdown();
private:
    struct Vector2{
        float x;
        float y;
    };

    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Window created by SDL
    SDL_Window* mWindow;
    // Renderer created by SDL
    SDL_Renderer* mRenderer;
    // Game should continue to run while...
    bool mIsRunning;
    // Parameter for wall thickness
    const Uint8 thickness = 30;
    // Parameter for paddle height;
    const Uint8 paddleH = 100;
    // The paddle
    Vector2 mPaddlePos;
    // The ball
    Vector2 mBallPos;
    // The balls velocity (speed and direction)
    Vector2 mBallVel;
    // Track the number of ticks
    Uint32 mTicksCount;
    // Track paddle movement
    int mPaddleDir;
};

#endif //MADHAV_GAME_H
