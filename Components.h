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
using ComponentID = std::uint32_t;
static constexpr std::uint8_t COMPONENT_MAX_SIZE = 32;
}
#endif //COMPONENTS_H
