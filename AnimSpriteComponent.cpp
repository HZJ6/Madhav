//
// Created by Mike on 7/23/2019.
//

#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(class Actor *owner, int drawOrder)
        : SpriteComponent(owner, drawOrder)
        , mCurrFrame(0.0f)
        , mAnimFPS(4.0f)
        , mCurrAnim(0){

}

void AnimSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);

    if(mAnimTextures[mCurrAnim].size() > 0){
        mCurrFrame += mAnimFPS * deltaTime;
        while(mCurrFrame >= mAnimTextures[mCurrAnim].size()){
            mCurrFrame -= mAnimTextures[mCurrAnim].size();
            mAnimOnce = false;
        }

        SetTexture((mAnimTextures[mCurrAnim][static_cast<int>(mCurrFrame)]));
    }
}

void AnimSpriteComponent::SetCurrAnim(int currAnim){
    if(!mAnimOnce || (mCurrFrame >= mAnimTextures[mCurrAnim].size())){
        mCurrAnim = currAnim;
    }
}

void AnimSpriteComponent::SetAnimTextures(int animState, const std::vector<SDL_Texture *> &textures) {
    mAnimTextures.emplace(animState,textures);
    if(mAnimTextures.size() > 0){
        mCurrFrame = 0.0f;
    }
}