//
// Created by Mike on 7/27/2019.
//

#pragma once
#include "SpriteComponent.h"
#include "Actor.h"
#include <string>
#include <vector>
#include "Math.h"

class TileMapComponent : public SpriteComponent {
public:
    TileMapComponent(class Actor* owner, int drawOrder = 10);

    void Draw(SDL_Renderer* renderer) override;
    void SetTexture(SDL_Texture* texture) override { mTileMapTexture = texture; }

    void LoadTileMap_CSV(std::string fileName);
    void SetScreenSize(Vector2 &size) { mScreenSize = size; }

private:
    SDL_Texture* mTileMapTexture;
    std::vector<std::vector<int>> csvMap;
    Vector2 mScreenSize;
};

