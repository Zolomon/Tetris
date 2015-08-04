#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(glm::vec2 position, glm::vec2 hitbox)
    : position(position), velocity(0.0f), acceleration(0.0f), hitbox(hitbox)
{
    
}


void PhysicsComponent::Update(const double deltaTime)
{
    velocity += acceleration;
    position += velocity;
}
