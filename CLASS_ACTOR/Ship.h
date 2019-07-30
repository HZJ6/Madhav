//
// Created by Mike on 7/25/2019.
//

#pragma once

#include <cstdint>
#include "../Actor.h"
#include "../CLASS_COMPONENT/AnimSpriteComponent.h"
#include "../CLASS_COMPONENT/InputComponent.h"
#include "../CLASS_COMPONENT/CircleComponent.h"

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ActorInput(const uint8_t* keyState) override;
private:
    enum AnimState{
        IDLE,
        MOVE
    };
    AnimSpriteComponent* mAnimSprite;
    InputComponent* mInput;
    CircleComponent* mCircle;
    float mLaserCooldown;
    float mRespawnTime;
    bool mRespawn;
    bool isMoving;
};

