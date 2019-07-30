//
// Created by Mike on 7/29/2019.
//

#include "../Game.h"
#include "Asteroid.h"
#include "../Random.h"
#include "../CLASS_COMPONENT/SpriteComponent.h"
#include "../CLASS_COMPONENT/MoveComponent.h"

Asteroid::Asteroid(Game* game)
        : Actor(game) {
    Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f,768.0f));
    setPosition(randPos);
    setRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->getTexture("Assets/Asteroid.png"));

    MoveComponent* mc = new MoveComponent(this);
    mc->SetMass(1.0f);
    mc->SetVelocity(Vector2(Math::Cos(getRotation()),Math::Sin(getRotation())) * 100);

    mCircle = new CircleComponent(this);
    mCircle->SetRadius(40.0f);

    game->AddAsteroid(this);
}

Asteroid::~Asteroid(){
    getGame()->RemoveAsteroid(this);
}
