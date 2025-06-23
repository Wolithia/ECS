//
// Created by 13662 on 22/06/2025.
//

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H
#include <cassert>
#include <memory>
#include <unordered_map>

#include "Signature.h"
#include "System.h"

namespace ECS
{
class SystemManager
{
public:
	SystemManager();

	// Add a system to the manager
	template <typename SystemType>
	std::shared_ptr<SystemType> RegisterSystem()
	{
		const char* name = typeid(SystemType).name();
		assert(!systems_.contains(name) && "System already registered");
		systems_.emplace(name, std::make_shared<SystemType>());
		return systems_[name];
	}

	// Set a system's component signature
	template <typename SystemType>
	void SetSignature(Signature signature)
	{
		const char* name = typeid(SystemType).name();
		if (!signatures_.contains(name))
			signatures_.emplace(name, signature);
		else
			signatures_[name] = signature;
	}

	void EntityDestroy(EntityID entity)
	{
		for (auto it = systems_.begin(); it != systems_.end(); ++it)
		{
			auto& system = it->second;
			system->entities_.erase(entity);
		}
	}

	void EntitySignatureChanged(EntityID entity_id, Signature entity_signature)
	{
		for (auto it = systems_.begin(); it != systems_.end(); ++it)
		{
			auto& system_t = it->first;
			auto& system = it->second;
			auto& system_signature = signatures_[system_t];
			if (entity_signature == system_signature)
			{
				system->entities_.insert(entity_id);
			}
			else
			{
				system->entities_.erase(entity_id);
			}
		}
	}

private:
	std::unordered_map<const char *, Signature> signatures_;
	std::unordered_map<const char *, std::shared_ptr<System>> systems_;
};
}
#endif //SYSTEMMANAGER_H
