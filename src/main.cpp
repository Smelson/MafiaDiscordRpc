#include "main.hpp"

Discord discordClient;
Mafia mafiaClient;
int GAME_VERSION;

std::map<std::string, MissionPresenceInfo> presenceMap;
bool IS_DEBUG = false;

void StartRpc()
{
	GameLoop(discordClient, mafiaClient, presenceMap, IS_DEBUG);
	ExitThread(0);
}

void ChangeMode()
{
    while(true)
    {
        if (GetAsyncKeyState(VK_INSERT))
        {   
            IS_DEBUG = !IS_DEBUG;
            CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartRpc), nullptr, 0, nullptr);
            if (IS_DEBUG == true)
                Helpers::Log("Modding Mode Activated!", 0x00FF00, GAME_VERSION);
            else
                Helpers::Log("Standard Mode Activated!", 0x00FF00, GAME_VERSION);
        }
        Sleep(1500);
    }
}

void InitRpc()
{
	discordClient.Initialize();
	presenceMap = SetMap();
}

void OnGameInit()
{
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(StartRpc), nullptr, 0, nullptr);
}

int __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);

        GAME_VERSION = mafiaClient.GetGameVersion();

        if (GAME_VERSION == 384)
        {
			InitRpc();
            mafiaClient.Initialize(discordClient, 0x65115C, 0x6F9464, 384, "Mafia 1.0");
            Helpers::InstallJmpHook(0x005DF209, (DWORD)OnGameInit);
            Helpers::InstallJmpHook(0x00623E8B, (DWORD)OnGameExit);
            Helpers::InstallJmpHook(0x005FB1D4, (DWORD)OnGameLoading);
            Helpers::InstallJmpHook(0x005E0756, (DWORD)OnMissionLoading);
            Helpers::InstallJmpHook(0x005D4ABD, (DWORD)OnPlayerEnterCar);
            Helpers::InstallJmpHook(0x005D4ADC, (DWORD)OnPlayerExitCar);
            Helpers::InstallJmpHook(0x005D4D66, (DWORD)OnPlayerChangeCamera);
			Helpers::InstallJmpHook(0x005DAAF2, (DWORD)OnPlayerJackCar);
			Helpers::Nop(0x005DAAF7, 1);
            Helpers::Nop(0x00623E90, 1);
        }
        else if (GAME_VERSION == 395)
        {
			InitRpc();
            mafiaClient.Initialize(discordClient, 0x63788C, 0x647E1C, 395, "Mafia 1.2");
            Helpers::InstallJmpHook(0x005A395B, (DWORD)OnGameInit);
            Helpers::InstallJmpHook(0x005661AB, (DWORD)OnGameExit);
            Helpers::InstallJmpHook(0x005BFDDC, (DWORD)OnGameLoading);
            Helpers::InstallJmpHook(0x005A4CF9, (DWORD)OnMissionLoading);
            Helpers::InstallJmpHook(0x005ED1AD, (DWORD)OnPlayerEnterCar);
            Helpers::InstallJmpHook(0x005ED1CC, (DWORD)OnPlayerExitCar);
            Helpers::InstallJmpHook(0x005ED456, (DWORD)OnPlayerChangeCamera);
			Helpers::InstallJmpHook(0x005F34E2, (DWORD)OnPlayerJackCar);
			Helpers::Nop(0x005F34E7, 1);
        }
        else exit(1);
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ChangeMode), nullptr, 0, nullptr);
    }
    return 1;
}