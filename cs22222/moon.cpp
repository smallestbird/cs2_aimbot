#include "aimbot.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow) {

	aimbot::PID = memory::GetProcID(L"cs2.exe");
	aimbot::module_base = memory::GetModuleBaseAddress(aimbot::PID, L"client.dll");

	while (true) {
		if (GetAsyncKeyState(VK_LSHIFT)) {
			aimbot::frame();
		}
	}
	return 0;


}




