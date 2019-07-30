//
// Created by Mike on 7/29/2019.
//

#include "Laser.h"
#include "../Game.h"
#include "../CLASS_COMPONENT/MoveComponent.h"
#include "../CLASS_COMPONENT/SpriteComponent.h"
#include "../CLASS_COMPONENT/CircleComponent.h"

Laser::Laser(Game *game,Vector2 position, float rotation)
        : Actor(game){
    setPosition(position);
    setRotation(rotation);
    MoveComponent* mc = new MoveComponent(this);
    mc->SetVelocity(Vector2(Math::Cos(rotation),-Math::Sin(rotation))*600.0f);
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(getGame()->getTexture("Assets/Laser.png"));
    mLifeLength = 1.0f;
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(5.0f);
}

void Laser::UpdateActor(float deltaTime) {
    mLifeLength -= deltaTime;
    if(mLifeLength <= 0){
        setState(EDead);
    }
    else {
        for (auto ast : getGame()->GetAsteroids()) {
            if (Intersect(*mCircle, *(ast->GetCircle()))) {
                setState(EDead);
                ast->setState(EDead);
                break;
            }
        }
    }
}