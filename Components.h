//
// Created by 13662 on 19/06/2025.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <limits>
#include <cstdint>

namespace ECS
{
using Component = std::uint8_t;
constexpr Component MAX_COMPONENTS = std::numeric_limits<Component>::max();
}
#endif //COMPONENTS_H
