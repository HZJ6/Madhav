//
// Created by Mike on 7/19/2019.
//

#pragma once
#include <vector>
#include "Math.h"

class Actor{
public:
    // Used to track state of actor
    enum State{
        EActive,
        EPaused,
        EDead
    };

    // Constructor / destructor
    Actor(class Game* game);
    virtual ~Actor();

    // Update function called from Game (not overridable)
    void Update(float deltaTime);
    // Updates all the components attached to the actor (not overrideable)
    void UpdateComponents(float deltaTime);
    // Any actor-specific update code (overrideable)
    virtual void UpdateActor(float deltaTime);

    // Getters
    State getState() const { return mState;}
    Vector2 getPosition() const { return mPosition; }
    float getScale() const { return mScale; }
    float getRotation() const { return mRotation; }
    class Game* getGame() const { return mGame; }

    // Setters
    void setState(const State state) { mState = state; }
    void setPosition(const Vector2 position) { mPosition = position; }
    void setScale(const float scale) { mScale = scale; }
    void setRotation(const float rotation) { mRotation = rotation; }

    // Add / remove components
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
private:
    // Actor's state
    State mState;
    // Transform
    Vector2 mPosition; // Center position of actor
    float mScale;      // Uniforms scale of actor (1.0f for 100%)
    float mRotation;   // Rotation angle (in radians)
    // Components held by this actor
    std::vector<class Component*> mComponents;
    class Game* mGame;
};

