//
// Created by 13662 on 22/06/2025.
//

#ifndef SYSTEM_H
#define SYSTEM_H
#include <set>

#include "Entity.h"

namespace ECS
{
class System
{
private:
	std::set<EntityID> entities_;

friend class SystemManager;
};
}
#endif //SYSTEM_H
