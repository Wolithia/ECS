//
// Created by 13662 on 20/06/2025.
//

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <memory>
#include <typeindex>
#include <unordered_map>

#include "Components.h"
#include "IComponentArray.h"

namespace ECS
{
class ComponentManager
{
public:
	ComponentManager() = default;
	~ComponentManager() = default;
	template <typename T>
	void RegisterComponent()
	{
		const char * typeName = typeid(T).name();
		componentTypes_.insert(std::make_pair(typeName, componentTypeCounts_++));
		componentArrays_.insert(std::make_pair(typeName, std::make_shared<ComponentArray<T>>()));
	}

	template <typename T>
	const char * GetComponentType()
	{
		return componentTypes_[typeid(T).name()];
	}

	template <typename T>
	void AddComponent(Entity entity, T Component)
	{
		GetComponentArray<T>()->InsertData(entity, Component);
	}

	template <typename T>
	void RemoveComponent(Entity entity)
	{
		GetComponentArray<T>()->RemoveData(entity);
	}

	template <typename T>
	T& GetComponent(Entity entity)
	{
		return GetComponentArray<T>()->GetData(entity);
	}

	void EntityDestroy(Entity entity)
	{
		for (auto const& pair : componentArrays_)
		{
			auto const& component = pair.second;
			component->EntityDestroy(entity);
		}
	}

private:
	std::unordered_map<const char *, ComponentType> componentTypes_ {};
	std::unordered_map<const char *, std::shared_ptr<IComponentArray>> componentArrays_ {};
	ComponentType componentTypeCounts_ {};

	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[typeid(T).name()]);
	}
};
}

#endif //COMPONENTMANAGER_H
