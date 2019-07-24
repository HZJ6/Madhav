//
// Created by Mike on 7/23/2019.
//

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor *owner, int drawOrder)
        : SpriteComponent(owner, drawOrder)
        , mCurrFrame(0.0f)
        , mAnimFPS(24.0f){

}

void AnimSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);

    if(mAnimTextures.size() > 0){
        mCurrFrame += mAnimFPS * deltaTime;
        while(mCurrFrame >= mAnimTextures.size()){
            mCurrFrame -= mAnimTextures.size();
        }

        SetTexture((mAnimTextures[static_cast<int>(mCurrFrame)]));
    }
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture *> &textures) {
    mAnimTextures = textures;
    if(mAnimTextures.size() > 0){
        mCurrFrame = 0.0f;
        SetTexture(mAnimTextures[0]);
    }
}