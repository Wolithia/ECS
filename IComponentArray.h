//
// Created by 13662 on 19/06/2025.
//

#ifndef ICOMPONENTARRAY_H
#define ICOMPONENTARRAY_H
#include <array>
#include <cstddef>
#include <unordered_map>

#include "Components.h"
#include "Entity.h"

namespace ECS
{

class IComponentArray
{
public:
	virtual ~IComponentArray() = 0;
	virtual void EntityDestroy(Entity entity) = 0;
};

template<typename T, typename... Args>
class ComponentArray : public IComponentArray
{
	using E2CMapType = typename std::unordered_map<Entity, std::size_t>;
	using C2EMapType = typename std::unordered_map<std::size_t, Entity>;

public:
	void InsertEntity(Entity entity, Args... args)
	{
		componentArray_[currentSize_] = T(std::forward<Args>(args)...);
		componentToEntityMap_[currentSize_] = entity;
		entityToComponentMap_[entity] = currentSize_;
		++currentSize_;
	}

	void EntityDestroy(Entity entity) override
	{
		if (auto itr = entityToComponentMap_.find(entity); itr != entityToComponentMap_.end())
		{
			RemoveData(itr);
		}
	}

	T& GetData(Entity entity)
	{
		return componentArray_[entityToComponentMap_[entity]];
	}

private:
	void RemoveData(E2CMapType::iterator itr)
	{
		Component attachedComponent = itr->second;
		Component lastIndex = currentSize_ - 1;

		// Swap the last component with the component to removed
		componentArray_[attachedComponent] = componentArray_[lastIndex];

		Entity entityOfTheLastComponent = componentToEntityMap_[lastIndex];
		componentToEntityMap_[attachedComponent] = entityOfTheLastComponent;
		entityToComponentMap_[entityOfTheLastComponent] = attachedComponent;

		--currentSize_;
	}

private:

	// Component Data Array
	std::array<Comp, MAX_COMPONENTS> componentArray_ {};

	//TODO: Sparse Set
	std::unordered_map<Entity, std::size_t> entityToComponentMap_ {};
	std::unordered_map<std::size_t, Entity> componentToEntityMap_ {};
	std::uint8_t currentSize_ {0};
};
}
#endif //ICOMPONENTARRAY_H
