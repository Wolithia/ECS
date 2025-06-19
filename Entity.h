//
// Created by 13662 on 19/06/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <array>
#include <cstdint>
#include <limits>
#include <bitset>

namespace ECS
{
	template<typename T=uint32_t>
	struct Entity
	{
		using EntityIDType = typename T;
		constexpr EntityIDType MAX_ENTITIES = std::numeric_limits<EntityIDType>::max();
		EntityIDType ID;

		explicit Entity(T id) : ID(id) {}
	};


	// Test components
	struct Transform
	{
		std::array<float, 3> position;
		std::array<float, 3> rotation;
		std::array<float, 3> scale;
	};

}


#endif //ENTITY_H
