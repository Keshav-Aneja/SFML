	#include "EntityManager.h"
#include <iostream>
	EntityManager::EntityManager() {

	}

	void EntityManager::update()
	{
		//TODO: add the entities from m_entitiesToAdd the proper location(s)
		// - add them to the vector of all entities
		// - add them to the vector inside the map, with the tag as the key
		for (auto& e : m_entitiesToAdd)
		{
			m_entities.push_back(e);
			m_entityMap[e->tag()].push_back(e);
		}
		m_entitiesToAdd.clear();
		//remove the dead entities from the vector of all entities
		removeDeadEntities(m_entities);

		//remove dead entities from each vector in the entity map
		//C++17 way of iterating through [key,value] pairs in a map
		for (auto& pair : m_entityMap)
		{
			std::string tag = pair.first;
			EntityVec entityVec = pair.second;
			removeDeadEntities(entityVec);
		}
	}

	void EntityManager::removeDeadEntities(EntityVec & vec)
	{
		//TODO: remove all dead entities from the input vector
		// this is called by the update function
		/*for (auto e : vec)
		{
			if (!e->isActive())
			{
				//remove from vec
				//check out std::remove_if
			}
		}*/
		auto removeIter = std::remove_if(vec.begin(), vec.end(), [](auto& e) {
			return !e->isActive();
			});
		vec.erase(removeIter, vec.end());
		//vec.erase(std::remove_if(vec.begin(), vec.end(), [](auto& e) { return !e->isActive(); }), vec.end());
	}

	std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
	{	
		auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));
		m_entitiesToAdd.push_back(entity);
		return entity;
	}

	const EntityVec& EntityManager::getEntities()
	{
		return m_entities;
	}

	const EntityVec& EntityManager::getEntities(const std::string& tag)
	{
		return m_entityMap[tag];
	}