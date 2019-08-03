// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Tower.h"
#include "../CLASS_COMPONENT/SpriteComponent.h"
#include "../CLASS_COMPONENT/MoveComponent.h"
#include "../Game.h"
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(class Game* game)
        :Actor(game)
{
    SpriteComponent* sc = new SpriteComponent(this, 200);
    sc->SetTexture(game->getTexture("Assets/Tower.png"));

    mMove = new MoveComponent(this);
    //mMove->SetAngularSpeed(Math::Pi);

    mNextAttack = AttackTime;
}

void Tower::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    mNextAttack -= deltaTime;
    if (mNextAttack <= 0.0f)
    {
        Enemy* e = getGame()->GetNearestEnemy(getPosition());
        if (e != nullptr)
        {
            // Vector from me to enemy
            Vector2 dir = e->getPosition() - getPosition();
            float dist = dir.Length();
            if (dist < AttackRange)
            {
                // Rotate to face enemy
                setRotation(Math::Atan2(-dir.y, dir.x));
                // Spawn bullet at tower position facing enemy
                Bullet* b = new Bullet(getGame());
                b->setPosition(getPosition());
                b->setRotation(getRotation());
            }
        }
        mNextAttack += AttackTime;
    }
}