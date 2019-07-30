//
// Created by Mike on 7/29/2019.
//

#pragma once
#include "../Actor.h"
#include "../CLASS_COMPONENT/CircleComponent.h"
#include "../CLASS_COMPONENT/MoveComponent.h"

class Asteroid : public Actor {
public:
    Asteroid(class Game* game);
    ~Asteroid();
    CircleComponent* GetCircle() { return mCircle; }
private:
    CircleComponent* mCircle;
};