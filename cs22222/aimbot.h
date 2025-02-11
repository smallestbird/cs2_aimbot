#pragma once


#include "client_dll.hpp"
#include "offsets.hpp"
#include "vector.h"
#include "memoryy.h"
#include <Windows.h>

namespace aimbot {

	inline uintptr_t module_base;
	inline uintptr_t PID;

	float distance(vec3 p1, vec3 p2);
	void frame();


}
