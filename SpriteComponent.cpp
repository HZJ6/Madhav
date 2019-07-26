//
// Created by Mike on 7/23/2019.
//
#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(class Actor *owner, int drawOrder)
        : Component(owner)
        ,mTexture(nullptr)
        ,mDrawOrder(drawOrder)
        ,mTexWidth(0)
        ,mTexHeight(0){
    mOwner->getGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    mOwner->getGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer){
    if(mTexture){
        SDL_Rect r;
        // Scale the width/height by owner's scale
        r.w = static_cast<int>(mTexWidth * mOwner->getScale());
        r.h = static_cast<int>(mTexHeight * mOwner->getScale());
        // Center the rectangle around the position of the owner
        r.x = static_cast<int>(mOwner->getPosition().x - r.w / 2);
        r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2);

        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
        SDL_RenderCopyEx(renderer,
                mTexture,
                nullptr,
                &r,
                -Math::ToDegrees(mOwner->getRotation())
                ,nullptr,
                SDL_FLIP_NONE);
    }
}

void SpriteComponent::SetTexture(SDL_Texture *texture) {
    mTexture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

