//
// Created by Mike on 7/18/2019.
//
#include "Game.h"
#include "SDL2/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"

// --- Constructors / Destructors ---
Game::Game()
    : mWindow(nullptr)
    , mRenderer(nullptr)
    , mIsRunning(true)
    , mUpdatingActors(false){

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
            SCREEN_WIDTH, // Width of window
            SCREEN_HEIGHT,  // Height of window
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

    if(IMG_Init(IMG_INIT_PNG) == 0){
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    // TODO: Move paddle starting position into Actor Paddle object
    // TODO: Add code to create paddle object and player component
    mPaddlePos.x = THICKNESS;
    mPaddlePos.y = SCREEN_HEIGHT / 2.0f;

    // TODO: Move ball creation into ball Actor objects
    // TODO: Add code to create ball objects
    Ball* ball = nullptr;
    srand(time(nullptr));
    double randomAngle;
    for(int i = 0; i < ballCount; ++i){
        randomAngle = M_PI * (((rand() % 120)-60)/180.0f);
        ball = new Ball();
        ball->ballPos.x = SCREEN_WIDTH/2.0f;
        ball->ballPos.y = SCREEN_HEIGHT/2.0f;
        ball->ballVel.x = static_cast<float>(cos(randomAngle))*ballSpeed;
        ball->ballVel.y = static_cast<float>(sin(randomAngle))*ballSpeed;
        balls.push_back(*ball);
    }
    ball = nullptr;

    // TODO: Add code to create wall objects

    LoadData();

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
    UnloadData();
    IMG_Quit();
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

    // TODO: Implement Player and Controller components
    // TODO: Add loop for processing player inputs

    mPaddleDir = 0;
    if(state[SDL_SCANCODE_W]){
        mPaddleDir -= paddleSpeed;
    }
    if(state[SDL_SCANCODE_S]){
        mPaddleDir += paddleSpeed;
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

    // Update all actors
    mUpdatingActors = true;
    for(auto &actor : mActors){
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    // Move any pending actors to mActors
    for(auto pending : mPendingActors){
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();

    // Add any dead actors to a temp vector
    std::vector<Actor*> deadActors;
    for(auto actor : mActors){
        if(actor->getState() == Actor::EDead){
            deadActors.emplace_back(actor);
        }
    }

    // Delete dead actors (which removes them from mActors)
    for(auto actor : deadActors){
        delete actor;
    }

    // TODO: Move paddle update into paddle Actor object ActorUpdate()
    // Based on input processed, move paddle up or down
    if(mPaddleDir != 0){
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

        // Wall collision
        if(mPaddlePos.y < (PADDLE_HEIGHT)/2.0f + THICKNESS){
            mPaddlePos.y = (PADDLE_HEIGHT)/2.0f + THICKNESS;
        }
        else if(mPaddlePos.y > ( 768.0f - (PADDLE_HEIGHT)/2.0f - THICKNESS)){
            mPaddlePos.y = ( 768.0f - (PADDLE_HEIGHT)/2.0f - THICKNESS);
        }
    }

    // TODO: Move ball update into ball Actor object ActorUpdate()
    // Update the balls velocity depending on surface contact
    for(auto &ball : balls){
        if(ball.ballPos.y - THICKNESS/2.0f <= THICKNESS && ball.ballVel.y < 0.0f)
        {
            ball.ballVel.y *= -1;
        }
        if(ball.ballPos.y + THICKNESS/2.0f >= (768 - THICKNESS) && ball.ballVel.y > 0.0f){
            ball.ballVel.y *= -1;
        }
        if(ball.ballPos.x + THICKNESS/2.0f >= (1028 - THICKNESS) && ball.ballVel.x > 0.0f){
            ball.ballVel.x *= -1;
        }
        int diff = abs(static_cast<int>(ball.ballPos.y) - static_cast<int>(mPaddlePos.y));
        if(diff <= PADDLE_HEIGHT/2.0f
           && ball.ballPos.x <= mPaddlePos.x + THICKNESS
           && ball.ballPos.x - THICKNESS/2.0f > mPaddlePos.x
           && ball.ballVel.x < 0.0f){
            ball.ballVel.x *= -1.0f;
        }

        // Move balls position
        ball.ballPos.x += ball.ballVel.x * deltaTime;
        ball.ballPos.y += ball.ballVel.y * deltaTime;
    }

}

void Game::GenerateOutput() {

    // TODO: Implement SpriteComponents and move all into objects
    // TODO: Implement wall Actor and move all into objects
    // TODO: Add loop for drawing all sprites owned by game

    for(auto sprite : mSprites){
        sprite->Draw(mRenderer);
    }

    SDL_SetRenderDrawColor(
            mRenderer,
            0,   // R
            0,   // G
            255, // B
            255  // A
    );

    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(
            mRenderer,  // SDL_Renderer
            0,          // R
            0,          // G
            0,          // B
            255         // A
    );

    SDL_Rect leftWall{
            0,                   // X
            THICKNESS,           // y
            3 * THICKNESS,       // width
            768 - 2 * THICKNESS  // height
    };

    SDL_RenderFillRect(mRenderer, &leftWall);

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
            THICKNESS // Height
    };

    SDL_Rect rightWall{
            1024 - THICKNESS, // x
            0,                // y
            THICKNESS,        // Width
            1024              // Height
    };

    SDL_Rect botWall{
            0,                // x
            768 - THICKNESS,  // y
            1024,             // Width
            THICKNESS         // Height
    };

    SDL_Rect* ballImage = nullptr;
    for(auto &ball : balls){
        ballImage = new SDL_Rect();
        ballImage->x = static_cast<int>(ball.ballPos.x - THICKNESS / 2.0f);  // x
        ballImage->y = static_cast<int>(ball.ballPos.y - THICKNESS / 2.0f);  // y
        ballImage->w = THICKNESS;                                            // Width
        ballImage->h = THICKNESS;                                            // Height
        SDL_RenderFillRect(mRenderer, ballImage);
    }
    ballImage = nullptr;

    SDL_Rect paddle{
            static_cast<int>(mPaddlePos.x),                   // x
            static_cast<int>(mPaddlePos.y - PADDLE_HEIGHT / 2.0f),  // y
            THICKNESS,                                        // Width
            PADDLE_HEIGHT                                           // Height
    };

    SDL_RenderFillRect(mRenderer, &topWall);
    SDL_RenderFillRect(mRenderer, &rightWall);
    SDL_RenderFillRect(mRenderer, &botWall);
    SDL_RenderFillRect(mRenderer, &paddle);

    SDL_RenderPresent(mRenderer);
}

// Implementation of game objects

void Game::AddActor(class Actor* actor){
    // If updating actors, need to add to pending
    if(mUpdatingActors){
        mPendingActors.emplace_back(actor);
    }
    else{
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(class Actor* actor){
    auto searchResult = std::find(mActors.begin(),mActors.end(),actor);
    if(searchResult != mActors.end()){
        std::iter_swap(searchResult, mActors.end() - 1);
        mActors.pop_back();
    }
    else {
        searchResult = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
        if (searchResult != mPendingActors.end()) {
            std::iter_swap(searchResult, mPendingActors.end() - 1);
            mPendingActors.pop_back();
        }
    }
}

void Game::AddSprite(class SpriteComponent* sprite){
    int myDrawOrder = sprite->getDrawOrder();
    auto iter = mSprites.begin();
    for(; iter != mSprites.end(); ++iter){
        if(myDrawOrder < (*iter)->getDrawOrder()){
            break;
        }
    }
    mSprites.insert(iter,sprite);
}

void Game::RemoveSprite(struct SpriteComponent *sprite) {
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

SDL_Texture* Game::getTexture(const std::string &fileName) {
    SDL_Texture* tex = nullptr;

    auto iter = mTextures.find(fileName);
    if(iter != mTextures.end()){
        tex = iter->second;
    }
    else{
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if(!surf){
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        tex = SDL_CreateTextureFromSurface(mRenderer, surf);
        SDL_FreeSurface(surf);
        if(!tex){
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }

        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}

void Game::LoadData() {
    // TODO: Once ball and paddle objects exist create them here
    // TODO: Implement LoadData once components are done

    // Create actor for the background
}

void Game::UnloadData() {
    // TODO: Implement UnloadData once components are done
}