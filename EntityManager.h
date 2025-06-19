//
// Created by 13662 on 19/06/2025.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <queue>
#include <bitset>

#include "Components.h"
#include "Entity.h"

namespace ECS
{
#define ASSERTMSG(cond, msg) assert((msg, cond));

	template<typename E, typename C>
	class EntityManager
	{
		using Signature = std::bitset<Component<C>::MAX_COMPONENTS>;
		using Entity_t = Entity<E>;
		using Component_t = Component<C>;

		constexpr static E MaxEntity_v = Entity_t::MAX_ENTITY;
		constexpr static C MaxComponent_v = Component<C>::MAX_COMPONENTS;

		public:
		EntityManager()
		{
			for (E entity = 0; entity < MaxEntity_v; ++entity)
			{
				mAvailableEntities_.emplace(entity);
			}
		}
		Entity_t CreateEntity()
		{
			ASSERTMSG(mLivingEntityCount_ < MaxComponent_v, "Too many Entities exist")

			Entity_t entity = mAvailableEntities_.front();
			mAvailableEntities_.pop();
			++mLivingEntityCount_;

			return entity;
		}

		void DestroyEntity(Entity_t entity)
		{
			ASSERTMSG(entity.ID < MaxEntity_v, "Entity ID out of range")

			mSignatures_[entity.ID].reset();

			mAvailableEntities_.push(entity);
			--mLivingEntityCount_;
		}

		void SetSignature(Entity_t entity, Signature signature)
		{
			ASSERTMSG(entity.ID < MaxEntity_v, "Entity ID out of range")
			mSignatures_[entity.ID] = signature;
		}


		private:
		// Available Entity IDs, can support thread security in the future
		std::queue<Entity_t> mAvailableEntities_{};

		// Signature Map Entity.ID - Component ID bit map
		std::array<Signature, MaxEntity_v> mSignatures_{};

		E mLivingEntityCount_ {};
	};
}
#endif //ENTITYMANAGER_H
