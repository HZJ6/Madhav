//
// Created by Mike on 7/18/2019.
//

#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>
#include <algorithm>
#include <string>
#include "Math.h"


// TODO: Implement SpriteComponent, AnimSpriteComponent, BGspriteComponent

class Game{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    SDL_Texture* getTexture(const std::string& fileName);
private:
    struct Ball{
        Vector2 ballPos;
        Vector2 ballVel;
    };

    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    bool mIsRunning;
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;
    bool mUpdatingActors;
    Uint32 mTicksCount;

    // Game specific setup parameters
    Uint8 ballCount = 3;

    // Containers for the actors
    std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    std::vector<class PlayerComponent*> mPlayers;
    std::vector<class SpriteComponent*> mSprites;


    //TODO: Remove container once ball object implemented
    std::vector<Ball> balls;

    //TODO: Move these values to individual objects
    const Uint8 THICKNESS = 30;
    const Uint8 PADDLE_HEIGHT = 100;
    Uint16 ballSpeed = 500;
    Uint8 paddleSpeed = 2;
    int mPaddleDir;
    Vector2 mPaddlePos;

};

