//
// Created by 13662 on 22/06/2025.
//

#ifndef SIGNATURE_H
#define SIGNATURE_H
#include <bitset>

#include "Components.h"

namespace ECS
{
	using Signature = std::bitset<COMPONENT_MAX_SIZE>;
}
#endif //SIGNATURE_H
