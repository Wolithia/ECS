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
using Entity = std::uint32_t;
constexpr Entity MAX_ENTITIES = std::numeric_limits<Entity>::max();

// Test components
struct Transform
{
	std::array<float, 3> position;
	std::array<float, 3> rotation;
	std::array<float, 3> scale;
};

}


#endif //ENTITY_H
