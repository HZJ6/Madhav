//
// Created by Mike on 7/29/2019.
//
#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent {
public:
    InputComponent(class Actor* owner);
    void ProcessInput(const uint8_t* keyState) override;

    float getAcceleration() const { return mAcceleration; }
    void setAcceleration(float acceleration) { mAcceleration = acceleration; }
    float getMaxAngularSpeed() const { return mMaxAngularSpeed; }
    void setMaxAngularSpeed(float mMaxAngularSpeed) { InputComponent::mMaxAngularSpeed = mMaxAngularSpeed; }
    int getForwardKey() const { return mForwardKey; }
    void setForwardKey(int mForwardKey) { InputComponent::mForwardKey = mForwardKey; }
    int getBackKey() const { return mBackKey; }
    void setBackKey(int mBackKey) { InputComponent::mBackKey = mBackKey; }
    int getClockWiseKwy() const { return mClockWiseKwy; }
    void setClockWiseKwy(int mClockWiseKwy) { InputComponent::mClockWiseKwy = mClockWiseKwy; }
    int getCounterClockwiseKey() const { return mCounterClockwiseKey; }
    void setCounterClockwiseKey(int mCounterClockwiseKey) { InputComponent::mCounterClockwiseKey = mCounterClockwiseKey; }
private:
    float mAcceleration;
    float mMaxAngularSpeed;
    int mForwardKey;
    int mBackKey;
    int mClockWiseKwy;
    int mCounterClockwiseKey;
};
