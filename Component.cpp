//
// Created by Mike on 7/19/2019.
//

#include "Component.h"
#include "Actor.h"

Component::Component(class Actor *owner, int updateOrder)
        : mOwner(owner)
        , mUpdateOrder(updateOrder){
    mOwner->AddComponent(this);
}

Component::~Component(){
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {
    // Override for specific behaviour in derived class
}
