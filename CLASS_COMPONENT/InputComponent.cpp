//
// Created by Mike on 7/29/2019.
//
#include "InputComponent.h"
#include "../Actor.h"
#include "../Game.h"

InputComponent::InputComponent(Actor *owner)
        :MoveComponent(owner){

}

void InputComponent::ProcessInput(const uint8_t *keyState) {
    Vector2 acceleration = Vector2::Zero;
    if(keyState[mForwardKey]){
        acceleration += Vector2(Math::Cos(mOwner->getRotation()),-Math::Sin(mOwner->getRotation())) * mAcceleration;
    }
    if(keyState[mBackKey]){
        acceleration -= Vector2(Math::Cos(mOwner->getRotation()),-Math::Sin(mOwner->getRotation())) * mAcceleration;
    }
    AddForce(acceleration);

    float angularSpeed = 0.0f;
    if(keyState[mClockWiseKwy]){
        angularSpeed -= mMaxAngularSpeed;
    }
    if(keyState[mCounterClockwiseKey]){
        angularSpeed += mMaxAngularSpeed;
    }
    SetAngularSpeed(angularSpeed);

}