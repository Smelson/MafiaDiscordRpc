#include "main.hpp"

Discord discord;
Mafia mafia;
std::map<std::string, MissionPresenceInfo> presenceMap = SetMap();
int gameVersion;

void GameLoop(Discord& discord, Mafia& mafia, std::map<std::string, MissionPresenceInfo> presenceMap);

void StartRpc()
{
	GameLoop(discord, mafia, presenceMap);
	ExitThread(0);
}

void InitRpc()
{
	mafia.Initialize(discord, 0x00647E1C, 0x0063788C, 393, "Mafia 1.2");
	discord.Initialize();
	presenceMap = SetMap();
}

void OnGameInit()
{
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartRpc), nullptr, 0, nullptr);
}

__declspec(naked) void OnGameLoading()
{
	static DWORD func = 0x60FCF6;
	static DWORD back = 0x5A4CFE;
	static const char state[] = "Loading...";

	_asm
	{
		call func
		mov [discord.discordPresence.state], offset state
		mov ecx, offset discord
		call Discord::UpdatePresence
		jmp back
	}
}

__declspec(naked) void OnPlayerEnterCar()
{
	static DWORD func = 0x5F2EA0;
	static DWORD back = 0x5ED1B2;
	static const char state[] = "Driving a car...";

	_asm
	{
		call func
		mov [discord.discordPresence.state], offset state
		mov ecx, offset discord
		call Discord::UpdatePresence
		jmp back
	}
}

__declspec(naked) void OnPlayerExitCar()
{
	static DWORD func = 0x5F2EA0;
	static DWORD back = 0x5ED1D1;

	_asm
	{
		call func
		mov [discord.discordPresence.state], 000000000
		mov ecx, offset discord
		call Discord::UpdatePresence
		jmp back
	}
}

__declspec(naked) void OnPlayerChangeCamera()
{
	static DWORD func = 0x5F2EA0;
	static DWORD back = 0x5ED45B;
	static const char carState[] = "Driving a car...";
	static const char tramState[] = "On Tram...";
	static const char cutsceneState[] = "Watching a cutscene...";

	_asm
	{
		call func

		cmp [edi+0x10], 0x7
		jz SetCarState
		cmp [edi+0x10], 0x8
		jz SetCarState
		cmp [edi+0x10], 0x9
		jz SetCarState
		cmp [edi+0x10], 0xC
		jz SetCarState
		cmp [edi+0x10], 0xD
		jz SetCarState
		cmp [edi+0x10], 0xE
		jz SetCarState
		cmp [edi+0x10], 0x11
		jz SetTramState
		cmp [edi+0x10], 0x16
		jz SetCutsceneState
		mov [discord.discordPresence.state], 000000000
		
		jmp UpdatePresence

		SetCarState:
		mov [discord.discordPresence.state], offset carState
		jmp UpdatePresence

		SetTramState:
		mov [discord.discordPresence.state], offset tramState
		jmp UpdatePresence

		SetCutsceneState:
		mov [discord.discordPresence.state], offset cutsceneState
		jmp UpdatePresence

		UpdatePresence:
		mov ecx, offset discord
		call Discord::UpdatePresence
		jmp back
	}
}

int __stdcall DllMain(HMODULE hModule, DWORD reason_for_call, LPVOID lpReserved)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		gameVersion = MafiaSDK::GetGameVersion();
		if (gameVersion == 384)
			exit(1);
		else if (gameVersion == 393)
			exit(1);
		else if (gameVersion == 395)
		{
			Helpers::InstallJmpHook(0x005A395B, (DWORD)OnGameInit);
			Helpers::InstallJmpHook(0x005A4CF9, (DWORD)OnGameLoading);
			Helpers::InstallJmpHook(0x005ED1AD, (DWORD)OnPlayerEnterCar);
			Helpers::InstallJmpHook(0x005ED1CC, (DWORD)OnPlayerExitCar);
			Helpers::InstallJmpHook(0x005ED456, (DWORD)OnPlayerChangeCamera);
		}
		else exit(1);

		InitRpc();
	}
	return 1;
}