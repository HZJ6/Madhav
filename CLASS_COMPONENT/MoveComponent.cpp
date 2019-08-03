// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "MoveComponent.h"
#include "../Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
        :Component(owner, updateOrder)
        ,mAngularSpeed(0.0f)
        ,mForwardSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
    if (!Math::NearZero(mAngularSpeed))
    {
        float rot = mOwner->getRotation();
        rot += mAngularSpeed * deltaTime;
        mOwner->setRotation(rot);
    }

    if (!Math::NearZero(mForwardSpeed))
    {
        Vector2 pos = mOwner->getPosition();
        pos += mOwner->getForward() * mForwardSpeed * deltaTime;
        mOwner->setPosition(pos);
    }
}