//
// Created by Mike on 7/18/2019.
//
#include "Game.h"
#include "SDL2/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "Ship.h"
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

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
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
    SDL_Log(IMG_GetError());
    IMG_Quit();
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

// --- Private Methods ---
void Game::ProcessInput() {
    SDL_Event event;

    // While there are still events in the queue...
    while(SDL_PollEvent(&event)){
        switch(event.type){
            // If event is SDL_QUIT exit.
            case SDL_QUIT :
                mIsRunning = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    // Check state of keyboard for ESC press, which exits.
    if(state[SDL_SCANCODE_ESCAPE]){
        mIsRunning = false;
    }

    mShip->ProcessKeyboard(state);
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
    for(auto actor : mActors){
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
}

void Game::GenerateOutput() {

    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    for(auto sprite : mSprites){
        sprite->Draw(mRenderer);
    }

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
    // Create player's ship
    mShip = new Ship(this);
    mShip->setPosition(Vector2(100.0f, 384.0f));
    mShip->setScale(1.5f);

    // Create actor for the background (this doesn't need a subclass)
    Actor* temp = new Actor(this);
    temp->setPosition(Vector2(512.0f, 384.0f));
    // Create the "far back" background
    BGSpriteComponent* bg = new BGSpriteComponent(temp);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    std::vector<SDL_Texture*> bgtexs = {
            getTexture("Assets/Farback01.png"),
            getTexture("Assets/Farback02.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-100.0f);
    // Create the closer background
    bg = new BGSpriteComponent(temp, 50);
    bg->SetScreenSize(Vector2(1024.0f, 768.0f));
    bgtexs = {
            getTexture("Assets/Stars.png"),
            getTexture("Assets/Stars.png")
    };
    bg->SetBGTextures(bgtexs);
    bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData() {
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    // Destroy textures
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}