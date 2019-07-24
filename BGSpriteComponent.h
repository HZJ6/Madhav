//
// Created by Mike on 7/23/2019.
//

#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

class BGSpriteComponent : public SpriteComponent{
public:
    BGSpriteComponent(class Actor* owner, int drawOrder = 10);

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetBGTexture(const std::vector<SDL_Texture*>& textures);

    void SetScreenSize(const Vector2& size) { mScreenSize = size; }
    void SetScrollSpeed(float speed) { mScrollSpeed = speed; }

    float getScrollSpeed() const { return mScrollSpeed; }

private:
    struct BGTexture{
        SDL_Texture* mTexture;
        Vector2 mOffset;
    };
    std::vector<BGTexture> mBGTextures;
    Vector2 mScreenSize;
    float mScrollSpeed;
};