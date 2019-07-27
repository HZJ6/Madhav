//
// Created by Mike on 7/25/2019.
//

#pragma once

#include <cstdint>
#include "Actor.h"
#include "AnimSpriteComponent.h"

class Ship : public Actor {
public:
    Ship(class Game* game);
    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard(const uint8_t* state);
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }
private:
    enum animState{
        IDLE,
        WALK,
        JUMP,
        PUNCH
    };

    float mRightSpeed;
    float mDownSpeed;
    AnimSpriteComponent* mAnim;
    animState mCurrAnimState;
};

