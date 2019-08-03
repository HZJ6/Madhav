// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "../Game.h"
#include "../CLASS_COMPONENT/SpriteComponent.h"
#include "../CLASS_COMPONENT/NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "../CLASS_COMPONENT/CircleComponent.h"
#include <algorithm>

Enemy::Enemy(class Game* game)
        :Actor(game)
{
    // Add to enemy vector
    game->GetEnemies().emplace_back(this);

    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->getTexture("Assets/Airplane.png"));
    // Set position at start tile
    setPosition(getGame()->GetGrid()->GetStartTile()->getPosition());
    // Setup a nav component at the start tile
    NavComponent* nc = new NavComponent(this);
    nc->SetForwardSpeed(150.0f);
    nc->StartPath(getGame()->GetGrid()->GetStartTile());
    // Setup a circle for collision
    mCircle = new CircleComponent(this);
    mCircle->SetRadius(25.0f);
}

Enemy::~Enemy()
{
    // Remove from enemy vector
    auto iter = std::find(getGame()->GetEnemies().begin(),
                          getGame()->GetEnemies().end(),
                          this);
    getGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    // Am I near the end tile?
    Vector2 diff = getPosition() - getGame()->GetGrid()->GetEndTile()->getPosition();
    if (Math::NearZero(diff.Length(), 10.0f))
    {
        setState(EDead);
    }
}