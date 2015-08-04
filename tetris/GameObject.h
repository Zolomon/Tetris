#pragma once
#include <memory>
#include "RenderComponent.h"

class BackgroundGameObject
{
public:
    std::shared_ptr<RenderComponent> renderComponent;
};