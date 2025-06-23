//
// Created by 13662 on 19/06/2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <queue>
#include <bitset>
#include <cassert>

#include "Signature.h"
#include "Entity.h"

namespace ECS
{

class EntityManager
{
	public:
	EntityManager()
	{
		for (EntityID entity = 0; entity < MAX_ENTITY_SIZE; ++entity)
		{
			availableEntities_.push(entity);
		}
	}
	EntityID CreateEntity()
	{
		assert(livingEntityCount_ < MAX_ENTITY_SIZE && "Too many Entities exist");

		const EntityID entity = availableEntities_.front();
		availableEntities_.pop();
		++livingEntityCount_;

		return entity;
	}

	void DestroyEntity(EntityID entity)
	{
		assert(entity < MAX_ENTITY_SIZE && "Entity ID out of range");

		signatures_[entity].reset();

		availableEntities_.push(entity);
		--livingEntityCount_;
	}

	void SetSignature(EntityID entity, Signature signature)
	{
		assert(entity < MAX_ENTITY_SIZE && "Entity ID out of range");
		signatures_[entity] = signature;
	}


	private:
	// Available Entity IDs, can support thread security in the future
	std::queue<EntityID> availableEntities_{};

	// Signature Map Entity.ID - Component ID bit map
	std::array<Signature, MAX_ENTITY_SIZE> signatures_{};

	EntityID livingEntityCount_ {0};
};
}
#endif //ENTITYMANAGER_H
