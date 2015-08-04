#pragma once
#include "glm/glm.hpp"

class PhysicsComponent
{
public:
    PhysicsComponent(glm::vec2 position, glm::vec2 hitbox);

    void Update(const double deltaTime);

    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    glm::vec2 hitbox;
};