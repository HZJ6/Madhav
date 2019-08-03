//
// Created by Mike on 7/30/2019.
//
#include "AIComponent.h"
#include "SDL2/SDL.h"
#include "../Actor.h"
#include "AIState.h"

AIComponent::AIComponent(Actor* owner)
        : Component(owner)
        , mCurrentState(nullptr){

}

void AIComponent::Update(float deltaTime){
    if(mCurrentState){
        mCurrentState->Update(deltaTime);
    }
}

void AIComponent::ChangeState(const std::string &name) {
    if(mCurrentState){
        mCurrentState->OnExit();
    }
    auto iter = mStateMap.find(name);
    if(iter != mStateMap.end()){
        mCurrentState = iter->second;
        mCurrentState->OnEnter();
    }
    else {
        SDL_Log("Could not find AIState %s",name.c_str());
        mCurrentState = nullptr;
    }
}

void AIComponent::RegisterState(class AIState *state) {
    mStateMap.emplace(state->GetName(),state);
}