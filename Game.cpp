//
// Created by Mike on 7/18/2019.
//
#include "Game.h"


// --- Constructors / Destructors ---
Game::Game() : mWindow(nullptr), mIsRunning(true){

}

// --- Public Methods ---
bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if(sdlResult != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 1)", // Window Title
            100,  // Top left x-coordinate of window
            100,  // Top left y-coordinate of window
            1024, // Width of window
            768,  // Height of window
            0     // Flags (0=none set)
    );

    if(!mWindow){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
            mWindow, // Window for the renderer to draw on
            -1,      // Usually -1 : For determining which graphics driver to use
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(!mRenderer){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    mPaddlePos.x = thickness;
    mPaddlePos.y = 768 / 2.0f;

    mBallPos.x = 1028 / 2.0f;
    mBallPos.y = 768 / 2.0f;

    mBallVel.x = -200.0f;
    mBallVel.y = 235.0f;

    mTicksCount = 0;

    return true;
}

void Game::RunLoop() {
    while(mIsRunning){
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown(){
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

// --- Private Methods ---
void Game::ProcessInput() {
    SDL_Event event;
    const Uint8* state = SDL_GetKeyboardState(nullptr);

    // While there are still events in the queue...
    while(SDL_PollEvent(&event)){
        switch(event.type){
            // If event is SDL_QUIT exit.
            case SDL_QUIT :
                mIsRunning = false;
                break;
            default:
                break;
        }
    }

    mPaddleDir = 0;
    if(state[SDL_SCANCODE_W]){
        mPaddleDir -= 1;
    }
    if(state[SDL_SCANCODE_S]){
        mPaddleDir += 1;
    }
    // Check state of keyboard for ESC press, which exits.
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }
}

void Game::UpdateGame() {
    // Wait until 16ms has elapsed since last frame
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    // Delta time is the difference in ticks from last frame
    // (converted to seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Clamp maximum delta time value
    if(deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }

    // Update tick counts (for next frame)
    mTicksCount = SDL_GetTicks();

    // Based on input processed, move paddle up or down
    if(mPaddleDir != 0){
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        // Wall collision
        if(mPaddlePos.y < (paddleH)/2.0f + thickness){
            mPaddlePos.y = (paddleH)/2.0f + thickness;
        }
        else if(mPaddlePos.y > ( 768.0f - (paddleH)/2.0f - thickness)){
            mPaddlePos.y = ( 768.0f - (paddleH)/2.0f - thickness);
        }
    }

    // Update the balls velocity depending on surface contact
    if(mBallPos.y - thickness/2.0f <= thickness && mBallVel.y < 0.0f)
    {
        mBallVel.y *= -1;
    }
    if(mBallPos.y + thickness/2.0f >= (768 - thickness) && mBallVel.y > 0.0f){
        mBallVel.y *= -1;
    }
    if(mBallPos.x + thickness/2.0f >= (1028 - thickness) && mBallVel.x > 0.0f){
        mBallVel.x *= -1;
    }
    int diff = abs(static_cast<int>(mBallPos.y) - static_cast<int>(mPaddlePos.y));
    if(diff <= paddleH/2.0f
            && mBallPos.x <= mPaddlePos.x + thickness
            && mBallPos.x - thickness/2.0f > mPaddlePos.x
            && mBallVel.x < 0.0f){
        mBallVel.x *= -1.0f;
    }

    // Move balls position
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(
            mRenderer,
            0,   // R
            0,   // G
            255, // B
            255  // A
    );

    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(
            mRenderer,
            255,   // R
            255,   // G
            255,   // B
            255    // A
    );

    SDL_Rect topWall{
            0,        // x
            0,        // y
            1024,     // Width
            thickness // Height
    };

    SDL_Rect rightWall{
            1024 - thickness, // x
            0,                // y
            thickness,        // Width
            1024              // Height
    };

    SDL_Rect botWall{
            0,                // x
            768 - thickness,  // y
            1024,             // Width
            thickness         // Height
    };

    SDL_Rect ball{
            static_cast<int>(mBallPos.x - thickness / 2.0f),  // x
            static_cast<int>(mBallPos.y - thickness / 2.0f),  // y
            thickness,                                        // Width
            thickness                                         // Height
    };

    SDL_Rect paddle{
            static_cast<int>(mPaddlePos.x),                     // x
            static_cast<int>(mPaddlePos.y - paddleH / 2.0f),  // y
            thickness,                                          // Width
            paddleH                                       // Height
    };

    SDL_RenderFillRect(mRenderer, &topWall);
    SDL_RenderFillRect(mRenderer, &rightWall);
    SDL_RenderFillRect(mRenderer, &botWall);
    SDL_RenderFillRect(mRenderer, &ball);
    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_RenderPresent(mRenderer);
}
