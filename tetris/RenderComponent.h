#pragma once

#include "Game.h"
#include "PhysicsComponent.h"

struct GDIBitmap;
class Game; 

class RenderComponent
{
public:
    RenderComponent(Bitmap bitmap, std::shared_ptr<PhysicsComponent> physicsComponent);
    void Render(Game& game);

private:
    Bitmap bmp;
    std::shared_ptr<PhysicsComponent> physicsComponent;
};