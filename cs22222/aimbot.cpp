#include "aimbot.h"
using wow = uintptr_t;
float aimbot::distance(vec3 p1, vec3 p2) {
	return (float)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));

}
void aimbot::frame() {
	wow entityList = memory::Read<wow>(module_base + cs2_dumper::offsets::client_dll::dwEntityList);
	if (!entityList) {
		return;
	}

	wow localPlayerPawn = memory::Read<wow>(module_base + cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
	if (!localPlayerPawn) {
		return;
	}

	BYTE team = memory::Read<BYTE>(localPlayerPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum);
	vec3 localEyePos = memory::Read<vec3>(localPlayerPawn + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin)+memory::Read<vec3>(localPlayerPawn+ cs2_dumper::schemas::client_dll::C_BaseModelEntity::m_vecViewOffset);
	float closest_distance = 1;
	vec3 enemyPos;

	for (int i = 0; i < 32; i++) {
		wow listEntry = memory::Read<wow>(entityList + ((8 * (i & 0x7ff) >> 9) + 16));
		if (!listEntry) {
			continue;
		}
		wow entityController = memory::Read<wow>(listEntry + 120 * (i & 0x1ff));
		if (!entityController) {
			continue;
		}
		wow entityControllerPawn = memory::Read<wow>(entityController + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
		if (!entityControllerPawn) {
			continue;
		}
		wow entityPawn = memory::Read<wow>(listEntry + 120 * (entityControllerPawn & 0x1ff));
		if (!entityPawn) {
			continue;
		}
		if (team == memory::Read<BYTE>(entityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum)) {
			continue;
		}
		if (memory::Read<std::uint32_t>(entityPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth) <= 0) {
			continue;
		}

		vec3 entityEyePos = memory::Read<vec3>(entityPawn + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin) + memory::Read<vec3>(entityPawn + cs2_dumper::schemas::client_dll::C_BaseModelEntity::m_vecViewOffset);

		float currentDistance = distance(localEyePos, entityEyePos);
		if (closest_distance < 0 || currentDistance < closest_distance) {
			closest_distance = currentDistance;
			enemyPos = entityEyePos;
		}




	}
	vec3 relativeAngle = (enemyPos - localEyePos).RelativeAngle();
	memory::Write<vec3>(module_base + cs2_dumper::offsets::client_dll::dwViewAngles,relativeAngle);


}