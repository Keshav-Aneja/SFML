#pragma once
#include "Entity.h"
class Physics
{
public:
static bool isCollided(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB);
};