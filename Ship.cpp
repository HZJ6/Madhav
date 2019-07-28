//
// Created by Mike on 7/25/2019.
//

#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Ship::Ship(Game* game)
    :Actor(game)
    ,mRightSpeed(0.0f)
    ,mDownSpeed(0.0f){
    AnimSpriteComponent* asc = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> idle = {
            game->getTexture("Assets/Character06.png")
    };

    std::vector<SDL_Texture*> walk = {
            game->getTexture("Assets/Character01.png"),
            game->getTexture("Assets/Character02.png"),
            game->getTexture("Assets/Character03.png"),
            game->getTexture("Assets/Character04.png"),
            game->getTexture("Assets/Character05.png"),
            game->getTexture("Assets/Character06.png")
    };

    std::vector<SDL_Texture*> jump = {
            game->getTexture("Assets/Character07.png"),
            game->getTexture("Assets/Character08.png"),
            game->getTexture("Assets/Character09.png"),
            game->getTexture("Assets/Character10.png"),
            game->getTexture("Assets/Character11.png"),
            game->getTexture("Assets/Character12.png"),
            game->getTexture("Assets/Character13.png"),
            game->getTexture("Assets/Character14.png"),
            game->getTexture("Assets/Character15.png")
    };

    std::vector<SDL_Texture*> punch = {
            game->getTexture("Assets/Character16.png"),
            game->getTexture("Assets/Character17.png"),
            game->getTexture("Assets/Character18.png")
    };

    asc->SetAnimTextures(IDLE, idle);
    asc->SetAnimTextures(WALK, walk);
    asc->SetAnimTextures(JUMP, jump);
    asc->SetAnimTextures(PUNCH, punch);

    mAnim = asc;
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    // Update position based on speeds and delta time
    Vector2 pos = getPosition();
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;
    // Restrict position to left half of screen
    if(pos.x < 25.0f){
        pos.x = 25.0f;
    }
    else if(pos.x > 1024.0f){
        pos.x = 1024.0f;
    }
    if(pos.y < 25.0f){
        pos.y = 25.0f;
    }
    else if(pos.y > 743.0f){
        pos.y = 743.0f;
    }
    setPosition(pos);
}

void Ship::ProcessKeyboard(const uint8_t *state) {
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;
    bool continueAnim = false;
    if(state[SDL_SCANCODE_D]){
        mRightSpeed += 250.0f;
        mAnim->SetCurrAnim(WALK);
        continueAnim = true;
    }
    if(state[SDL_SCANCODE_A]){
        mRightSpeed -= 250.0f;
        mAnim->SetCurrAnim(WALK);
        continueAnim = true;
    }
    if(state[SDL_SCANCODE_S]){
        mDownSpeed += 300.0f;
        mAnim->SetCurrAnim(WALK);
        continueAnim = true;
    }
    if(state[SDL_SCANCODE_W]){
        mDownSpeed -= 300.0f;
        mAnim->SetCurrAnim(WALK);
        continueAnim = true;
    }
    if(state[SDL_SCANCODE_SPACE]){
        mAnim->SetCurrAnim(JUMP);
        mAnim->SetAnimOnce();
        continueAnim = true;
    }
    if(state[SDL_SCANCODE_F]){
        mAnim->SetCurrAnim(PUNCH);
        mAnim->SetAnimOnce();
        continueAnim = true;
    }
    if(!continueAnim) {
        mAnim->SetCurrAnim(IDLE);
    }
}
