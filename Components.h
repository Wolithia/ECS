//
// Created by 13662 on 19/06/2025.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <limits>
#include <cstdint>

namespace ECS
{
	template<typename T>
	struct Component
	{
		using ComponentType = typename T;
		constexpr ComponentType MAX_COMPONENTS = std::numeric_limits<ComponentType>::max();
		ComponentType ID;
	};
}
#endif //COMPONENTS_H
