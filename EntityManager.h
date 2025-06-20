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
			mAvailableEntities_.push(entity);
		}
	}
	Entity CreateEntity()
	{
		ASSERTMSG(mLivingEntityCount_ < MAX_ENTITIES, "Too many Entities exist")

		Entity entity = mAvailableEntities_.front();
		mAvailableEntities_.pop();
		++mLivingEntityCount_;

		return entity;
	}

	void DestroyEntity(Entity entity)
	{
		ASSERTMSG(entity < MAX_ENTITIES, "Entity ID out of range")

		mSignatures_[entity].reset();

		mAvailableEntities_.push(entity);
		--mLivingEntityCount_;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		ASSERTMSG(entity < MAX_ENTITIES, "Entity ID out of range")
		mSignatures_[entity] = signature;
	}


	private:
	// Available Entity IDs, can support thread security in the future
	std::queue<Entity> mAvailableEntities_{};

	// Signature Map Entity.ID - Component ID bit map
	std::array<Signature, MAX_ENTITIES> mSignatures_{};

	Entity mLivingEntityCount_ {};
};
}
#endif //ENTITYMANAGER_H
