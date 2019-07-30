//
// Created by Mike on 7/23/2019.
//

#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <unordered_map>

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 100);

    void Update(float deltaTime);

    void SetAnimTextures(int animState, const std::vector<SDL_Texture*>& textures);

    float getAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }
    void SetCurrAnim(int currAnim);
    void SetAnimOnce() { mAnimOnce = true; }

private:
    std::unordered_map<int,std::vector<SDL_Texture*>> mAnimTextures;
    int mCurrAnim;
    float mCurrFrame;
    float mAnimFPS;
    bool mAnimOnce;
};