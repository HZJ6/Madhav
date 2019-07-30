//
// Created by Mike on 7/29/2019.
//

#pragma once
#include "../Actor.h"
#include "../CLASS_COMPONENT/CircleComponent.h"

class Laser : public Actor {
public:
    Laser(class Game* game,Vector2 position,float rotation);
    void UpdateActor(float deltaTime) override;
private:
    float mLifeLength;
    CircleComponent* mCircle;
};
