//
// Created by 13662 on 19/06/2025.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <limits>
#include <type_traits>
#include <cstdint>

namespace ECS
{
template<typename T>
struct Component
{
	static_assert(std::is_integral_v<T>, "T must be an integral type");
	T ID;
	static constexpr T MAX_ID = std::numeric_limits<T>::max();
	static constexpr T MAX_COUNT = 32;
};
using ComponentType = std::uint8_t;
constexpr ComponentType MAX_COMPONENTS = 32;
}
#endif //COMPONENTS_H
