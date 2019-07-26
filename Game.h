//
// Created by Mike on 7/18/2019.
//

#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

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
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 768;

    std::unordered_map<std::string, SDL_Texture*> mTextures;
    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;
    std::vector<class PlayerComponent*> mPlayers;
    std::vector<class SpriteComponent*> mSprites;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mUpdatingActors;
    Uint32 mTicksCount;
    bool mIsRunning;

    class Ship* mShip; // Demos player object
};

