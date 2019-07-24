//
// Created by Mike on 7/19/2019.
//

#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(class Game *game)
        : mState(EActive)
        , mPosition(Vector2::Zero)
        , mScale(1.0f)
        , mRotation(0.0f)
        ,mGame(game) {
        mGame->AddActor(this);
}

Actor::~Actor() {
    mGame->RemoveActor(this);
    // Need to delete components
    // Because ~Components calls RemoveComponent, need a different style loop
    while(!mComponents.empty()){
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime) {
    if(mState ==  EActive){
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for(auto comp: mComponents){
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {
    // Override for specific behaviour in derived class
}

void Actor::AddComponent(class Component *component) {
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for(; iter != mComponents.end(); ++iter){
        if(myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    // Insert element before position of iterator
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(class Component *component) {
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if(iter != mComponents.end()){
        mComponents.erase(iter);
    }
}


