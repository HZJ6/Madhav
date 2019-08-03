//
// Created by Mike on 7/30/2019.
//

#pragma once
#include "../Component.h"
#include <string>
#include <unordered_map>

class AIComponent : public Component {
public:
    AIComponent(class Actor* owner);

    void Update(float deltaTime) override;
    void ChangeState(const std::string& name);

    void RegisterState(class AIState* state);
private:
    std::unordered_map<std::string,class AIState*> mStateMap;
    class AIState* mCurrentState;
};
