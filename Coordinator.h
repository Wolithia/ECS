//
// Created by 13662 on 23/06/2025.
//

#ifndef COORDINATOR_H
#define COORDINATOR_H
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace ECS
{
class Coordinator
{
public:
	void Init()
	{
		entityManager_ = std::make_unique<EntityManager>();
		systemManager_ = std::make_unique<SystemManager>();
		componentManager_ = std::make_unique<ComponentManager>();
	}

	EntityID CreateEntity()
	{
		return entityManager_->CreateEntity();
	}

	void DestroyEntity(EntityID entity)
	{
		entityManager_->DestroyEntity(entity);
		systemManager_->EntityDestroy(entity);
		componentManager_->EntityDestroy(entity);
	}

	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		componentManager_->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(EntityID entity, T component)
	{
		componentManager_->AddComponent<T>(entity, component);

		auto signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(), true);
		entityManager_->SetSignature(entity, signature);

		systemManager_->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(EntityID entity)
	{
		componentManager_->RemoveComponent<T>(entity);

		auto signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(), false);
		entityManager_->SetSignature(entity, signature);

		systemManager_->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(EntityID entity)
	{
		return componentManager_->GetComponent<T>(entity);
	}

	template<typename T>
	const char * GetComponentType()
	{
		return componentManager_->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return systemManager_->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		systemManager_->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<EntityManager> entityManager_;
	std::unique_ptr<ComponentManager> componentManager_;
	std::unique_ptr<SystemManager> systemManager_;
};
}

#endif //COORDINATOR_H
