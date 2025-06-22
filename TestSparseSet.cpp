//
// Created by 13662 on 22/06/2025.
//

#include "SparseSet.h"
#include <cassert>
#include <cstdint>
#include <iostream>

int main() {
	SparseSet<uint32_t, uint8_t> set;

	set.Add(10);
	set.Add(20);
	assert(set.Find(10) != std::numeric_limits<uint8_t>::max());
	set.Remove(10);
	assert(set.Find(10) == std::numeric_limits<uint8_t>::max());

	std::cout << "All tests passed!\n";
	return 0;
}
