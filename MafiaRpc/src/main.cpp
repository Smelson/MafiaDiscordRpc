#include "main.hpp"
#define DEBUG

Discord discord;
Mafia mafia;
std::map<std::string, MissionPresenceInfo> presenceMap = SetMap();
int gameVersion;

void GameLoop(Discord* discord, Mafia* mafia, std::map<std::string, MissionPresenceInfo> presenceMap);

void StartRpc(HMODULE hModule)
{
	GameLoop(&discord, &mafia, presenceMap);
	ExitThread(0);
}

void InitRpc()
{
	if (gameVersion == 384)
		mafia.Initialize(&discord, 0x006F9464, 0x0065115C, 384, "Mafia 1.0");
	else if (gameVersion == 395)
		mafia.Initialize(&discord, 0x00647E1C, 0x0063788C, 393, "Mafia 1.2");
	else exit(1);

	discord.Initialize();
	presenceMap = SetMap();
}

void OnGameInit(HMODULE hModule)
{
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartRpc), hModule, 0, nullptr);
}

int __stdcall DllMain(HMODULE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		gameVersion = MafiaSDK::GetGameVersion();
		if (gameVersion == 384)
			Helpers::InstallJmpHook(0x005DF209, (DWORD)OnGameInit);
		else if (gameVersion == 393)
			exit(1);
		else if (gameVersion == 395)
			Helpers::InstallJmpHook(0x005A395B, (DWORD)OnGameInit);
		else exit(1);

		InitRpc();
	}

	return 1;
}