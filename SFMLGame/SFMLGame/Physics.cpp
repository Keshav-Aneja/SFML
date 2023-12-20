#include "Physics.h"

bool Physics::isCollided(std::shared_ptr<Entity> entityA, std::shared_ptr<Entity> entityB)
{
	Vec2 posA = { entityA->cTransform->pos.x,entityA->cTransform->pos.y };
	Vec2 posB = { entityB->cTransform->pos.x,entityB->cTransform->pos.y };
	float distance = posA.dist(posB);
	if (entityA->cCollision && entityB->cCollision && distance < entityA->cCollision->radius + entityB->cCollision->radius)
	{
		return true;
	}
	return false;
}