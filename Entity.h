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

template <typename T=std::uint32_t>
struct Entity
{
	static_assert(std::is_integral<T>::value, "Entity type must be integral");
	T ID;
	static constexpr T INVALID_ID = std::numeric_limits<T>::max();
};

}


#endif //ENTITY_H
