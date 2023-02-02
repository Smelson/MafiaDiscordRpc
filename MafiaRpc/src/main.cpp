#include "main.hpp"

Discord discord;
Mafia mafia;

void MainThread(HMODULE hModule)
{
#ifdef DEBUG
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
#endif // DEBUG

	int gameVersion = MafiaSDK::GetGameVersion();

	if (gameVersion == 384)
		mafia.Initialize(&discord, 0x006F9464, 0x0065115C, 384, "Mafia 1.0");
	else if (gameVersion == 393)
		mafia.Initialize(&discord, 0x00646D4C, 0x00646D90, 393, "Mafia 1.1");
	else if (gameVersion == 395)
		mafia.Initialize(&discord, 0x00647E1C, 0x0063788C, 393, "Mafia 1.2");
	else
		exit(1);

	GameLoop(&discord, &mafia);
}

int __stdcall DllMain(HMODULE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), hModule, 0, nullptr);
	}

	return 1;
}