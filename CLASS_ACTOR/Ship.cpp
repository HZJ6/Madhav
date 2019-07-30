//
// Created by Mike on 7/25/2019.
//

#include "Ship.h"
#include "../CLASS_COMPONENT/SpriteComponent.h"
#include "../CLASS_COMPONENT/InputComponent.h"
#include "../Game.h"
#include "../CLASS_ACTOR/Laser.h"

Ship::Ship(Game* game)
    :Actor(game)
    ,mRespawnTime(1.5f)
    ,mRespawn(false)
    ,isMoving(false){
    mAnimSprite = new AnimSpriteComponent(this);
    std::vector<SDL_Texture*> idle = {game->getTexture("Assets/Ship.png")};
    std::vector<SDL_Texture*> move = {game->getTexture("Assets/ShipWithThrust.png")};
    mAnimSprite->SetAnimTextures(IDLE,idle);
    mAnimSprite->SetAnimTextures(MOVE,move);
    mInput = new InputComponent(this);
    mInput->SetAngularSpeed(0.0f);
    mInput->setAcceleration(300.0f);
    mInput->SetMass(1.0f);
    mInput->setMaxAngularSpeed(5.0f);
    mInput->setForwardKey(SDL_SCANCODE_W);
    mInput->setBackKey(SDL_SCANCODE_S);
    mInput->setClockWiseKwy(SDL_SCANCODE_D);
    mInput->setCounterClockwiseKey(SDL_SCANCODE_A);
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);
    if(!mRespawn) {
        for (auto ast : getGame()->GetAsteroids()) {
            if (Intersect(*mCircle, *(ast->GetCircle()))) {
                setScale(0.0f);
                mRespawn = true;
            }
        }
        if (isMoving) {
            mAnimSprite->SetCurrAnim(MOVE);
        } else {
            mAnimSprite->SetCurrAnim(IDLE);
        }
    }
    else{
        mRespawnTime -= deltaTime;
        if(mRespawnTime <= 0) {
            setScale(1.0f);
            mInput->SetVelocity(Vector2::Zero);
            setPosition(Vector2(1024.0f / 2.0f, 768.0f / 2.0f));
            setRotation(0.0f);
            mRespawnTime = 1.5f;
            mRespawn = false;
        }
    }
    mLaserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t *keyState) {
    if(keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0 && !mRespawn){
        new Laser(getGame(),getPosition(),getRotation());
        mLaserCooldown = 0.5f;
    }
    if(keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_D]){
        isMoving = true;
    }
    else{
        isMoving = false;
    }
}

