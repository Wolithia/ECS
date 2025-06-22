//
// Created by 13662 on 19/06/2025.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <array>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>

namespace ECS
{
	using EntityID = std::uint32_t;
	static constexpr EntityID MAX_ENTITY_SIZE = std::numeric_limits<EntityID>::max() - 1;
}


#endif //ENTITY_H
