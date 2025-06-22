//
// Created by 13662 on 19/06/2025.
//

#ifndef ICOMPONENTARRAY_H
#define ICOMPONENTARRAY_H
#include <cassert>
#include <vector>
#include <cstddef>
#include <unordered_map>

#include "SparseSet.h"
#include "Entity.h"

namespace ECS
{

class IComponentArray
{
public:
	virtual ~IComponentArray() = 0;
	virtual void EntityDestroy(EntityID entity) = 0;
};

template<typename Component>
class ComponentArray : public IComponentArray
{
public:
	ComponentArray()
	{
		components_.reserve(256);
	}

	template <typename ... Args>
	void InsertEntity(const EntityID entity_id, Args... args)
	{
		components_.emplace_back(std::forward<Args>(args)...);
		indexMap_.Add(entity_id);
		++currentSize_;
	}

	void InsertEntity(const EntityID entity_id)
	{
		components_.emplace_back();
		indexMap_.Add(entity_id);
		++currentSize_;
	}

	void EntityDestroy(EntityID entity_id) override
	{
		if (indexMap_.Has(entity_id))
			indexMap_.Remove(entity_id);
		else
			assert(false && "Entity does not exist");

		--currentSize_;
	}

	Component& GetData(EntityID entity_id)
	{
		ComponentID component_id = indexMap_.Find(entity_id);
		return components_[component_id];
	}

private:
	// Component Data Array
	std::vector<Component> components_ {};

	SparseSet<std::uint32_t, std::uint8_t> indexMap_ {};
	std::uint8_t currentSize_ {0};
};
}
#endif //ICOMPONENTARRAY_H
