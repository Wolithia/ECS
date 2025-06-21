//
// Created by 13662 on 19/06/2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <queue>
#include <bitset>
#include <cassert>

#include "Components.h"
#include "Entity.h"

namespace ECS
{
#define ASSERTMSG(cond, msg) assert(((msg), cond));

class EntityManager
{
	using Signature = std::bitset<MAX_COMPONENTS>;
	public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			availableEntities_.push(entity);
		}
	}
	Entity CreateEntity()
	{
		ASSERTMSG(livingEntityCount_ < MAX_ENTITIES, "Too many Entities exist")

		Entity entity = availableEntities_.front();
		availableEntities_.pop();
		++livingEntityCount_;

		return entity;
	}

	void DestroyEntity(Entity entity)
	{
		ASSERTMSG(entity < MAX_ENTITIES, "Entity ID out of range")

		signatures_[entity].reset();

		availableEntities_.push(entity);
		--livingEntityCount_;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		ASSERTMSG(entity < MAX_ENTITIES, "Entity ID out of range")
		signatures_[entity] = signature;
	}


	private:
	// Available Entity IDs, can support thread security in the future
	std::queue<Entity> availableEntities_{};

	// Signature Map Entity.ID - Component ID bit map
	std::array<Signature, MAX_ENTITIES> signatures_{};

	Entity livingEntityCount_ {};
};
}
#endif //ENTITYMANAGER_H
