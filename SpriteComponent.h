//
// Created by Mike on 7/23/2019.
//

#pragma once
#include "Component.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component {
public:
    SpriteComponent(class Actor* owner, int drawOrder = 100);
    ~SpriteComponent();

    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int getDrawOrder() const { return mDrawOrder; }
    int getTexHeight() const { return mTexHeight; }
    int getTexWidth() const { return mTexWidth; }

protected:
    SDL_Texture * mTexture;
    int mDrawOrder;
    int mTexWidth;
    int mTexHeight;

};
