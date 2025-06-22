//
// Created by 13662 on 22/06/2025.
//

#ifndef SPARSESET_H
#define SPARSESET_H
#include <cassert>
#include <vector>
#include <limits>


template <typename EntityID, typename ComponentID>
class SparseSet
{
	static constexpr ComponentID INVALID_COMPONENT_ID = std::numeric_limits<ComponentID>::max();
public:
	explicit SparseSet(size_t initial_dense_size=256, size_t initial_sparse_size=1024)
	{
		dense_.reserve( initial_dense_size); // dense_'s length is defined by the number of components
		sparse_.resize( initial_sparse_size, INVALID_COMPONENT_ID); // sparse_'s length is defined by the number of entities
	}

	SparseSet(const SparseSet& other) = delete;
	SparseSet& operator=(const SparseSet& other) = delete;

	SparseSet(SparseSet&& other) = default;
	SparseSet& operator=(SparseSet&& other) = default;

	~SparseSet() = default;

	inline bool Has(EntityID entity_id) const
	{
		return entity_id < sparse_.size() && sparse_[entity_id] != INVALID_COMPONENT_ID;
	}

	inline ComponentID Find(EntityID entity_id) const
	{
		assert(entity_id < sparse_.size());
		ComponentID id = sparse_[entity_id];
		return id;
	}

	inline void Remove(EntityID entity_id)
	{
		assert(size_ > 0 && entity_id < sparse_.size() && "Invalid entity ID");
		ComponentID attachedComponent = Find(entity_id);
		assert(attachedComponent != INVALID_COMPONENT_ID && "Removing non-existent entity");

		EntityID lastEntity	= dense_[size_ - 1];

		sparse_[lastEntity] = attachedComponent;
		sparse_[entity_id] = INVALID_COMPONENT_ID;

		dense_[attachedComponent] = lastEntity;
		dense_.pop_back();

		--size_;
	}

	inline ComponentID Add(EntityID entity_id)
	{
		if (entity_id < sparse_.size() && sparse_[entity_id] != INVALID_COMPONENT_ID)
			return sparse_[entity_id];

		dense_.emplace_back(entity_id);

		if (entity_id >= sparse_.size())
			sparse_.resize(entity_id + 1, INVALID_COMPONENT_ID);

		sparse_[entity_id] = size_;

		return size_++;
	}

private:
	ComponentID size_ = 0;
	std::vector<EntityID> dense_ {}; // Stores Entity IDs
	std::vector<ComponentID> sparse_ {}; // Stores component IDs
};

#endif //SPARSESET_H
