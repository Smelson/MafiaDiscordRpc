#include "main.hpp"
#define DEBUG

Discord discordClient;
Mafia mafiaClient;
int GAME_VERSION;
std::map<std::string, MissionPresenceInfo> presenceMap;

void StartRpc()
{
	GameLoop(discordClient, mafiaClient, presenceMap);

    Helpers::Log("OnGameInit Hooked!");

	ExitThread(0);
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

__declspec(naked) void OnGameExit()
{
    _asm add esp, 3ECh
	discordClient.Shutdown();
	_asm retn 10h
}

__declspec(naked) void OnGameLoading()
{
    Helpers::Log("OnGameLoading Hooked!");

    static DWORD back10 = 0x005FB1D9;
    static DWORD back12 = 0x005BFDE1;
	static const char state[] = "Loading Game...";
	_asm
	{
        cmp GAME_VERSION, 0x180
        jz ONEZERO
        cmp GAME_VERSION, 0x18B
        jz ONETWO

        ONEZERO:
        mov [discordClient.discordPresence.state], offset state
		mov ecx, offset discordClient
		call Discord::UpdatePresence
        test eax, eax
        push 2C8h
        jmp back10

        ONETWO:
        mov [discordClient.discordPresence.state], offset state
		mov ecx, offset discordClient
		call Discord::UpdatePresence
        test eax, eax
        push 44160000h
        jmp back12
	}
}

__declspec(naked) void OnMissionLoading()
{
    Helpers::Log("OnMissionLoading Hooked!");

    static DWORD func10 = 0x6243AC;
	static DWORD func12 = 0x60FCF6;
    static DWORD back10 = 0x5E075B;
	static DWORD back12 = 0x5A4CFE;
	static const char state[] = "Loading a Mission...";

	_asm
	{
        cmp GAME_VERSION, 0x180
        jz ONEZERO
        cmp GAME_VERSION, 0x18B
        jz ONETWO

        ONEZERO:
		call func10
		mov [discordClient.discordPresence.state], offset state
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		jmp back10

        ONETWO:
        call func12
		mov [discordClient.discordPresence.state], offset state
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		jmp back12
	}
}

__declspec(naked) void OnPlayerEnterCar()
{
    static DWORD func10 = 0x5DA4B0;  
	static DWORD func12 = 0x5F2EA0;
    static DWORD back10 = 0x5D4AC2;
	static DWORD back12 = 0x5ED1B2;
	static const char state[] = "Driving a Car...";

	_asm
	{
        cmp GAME_VERSION, 0x180
        jz ONEZERO
        cmp GAME_VERSION, 0x18B
        jz ONETWO

        ONEZERO:
        test eax, eax
		call func10
		mov [discordClient.discordPresence.state], offset state
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		jmp back10

        ONETWO:
        test eax, eax
		call func12
		mov [discordClient.discordPresence.state], offset state
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		jmp back12
	}
}

__declspec(naked) void OnPlayerExitCar()
{
    static DWORD func10 = 0x5DA4B0;
	static DWORD func12 = 0x5F2EA0;
    static DWORD back10 = 0x5D4AE1;
	static DWORD back12 = 0x5ED1D1;

	_asm
	{
        cmp GAME_VERSION, 0x180
        jz ONEZERO
        cmp GAME_VERSION, 0x18B
        jz ONETWO

        ONEZERO:
		call func10
		mov [discordClient.discordPresence.state], 000000000
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		jmp back10

        ONETWO:
		call func12
		mov [discordClient.discordPresence.state], 000000000
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		jmp back12
	}
}

__declspec(naked) void OnPlayerChangeCamera()
{
    static DWORD func10 = 0x5DA4B0;
	static DWORD func12 = 0x5F2EA0;
    static DWORD back10 = 0x5D4D6B;
	static DWORD back12 = 0x5ED45B;

	static const char carState[] = "Driving a Car...";
	static const char tramState[] = "On a Train...";
	static const char cutsceneState[] = "Watching a Cutscene...";

	_asm
	{
        cmp GAME_VERSION, 0x180
        jz ONEZERO
        cmp GAME_VERSION, 0x18B
        jz ONETWO

        ONEZERO:
		call func10
        jmp UpdateState

        ONETWO:
        call func12
        jmp UpdateState

        UpdateState:
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
		mov [discordClient.discordPresence.state], 000000000
		
		jmp UpdatePresence

		SetCarState:
		mov [discordClient.discordPresence.state], offset carState
		jmp UpdatePresence

		SetTramState:
		mov [discordClient.discordPresence.state], offset tramState
		jmp UpdatePresence

		SetCutsceneState:
		mov [discordClient.discordPresence.state], offset cutsceneState
		jmp UpdatePresence

		UpdatePresence:
		mov ecx, offset discordClient
		call Discord::UpdatePresence

        cmp GAME_VERSION, 0x180
        jz ONEZEROBACK
        cmp GAME_VERSION, 0x18B
        jz ONETWOBACK

		ONEZEROBACK:
        jmp back10

        ONETWOBACK:
        jmp back12
	}
}

__declspec(naked) void OnPlayerJackCar()
{
	static DWORD back10 = 0x5DAAF8;
	static DWORD back12 = 0x5F34E8;
	static DWORD back;
	static int playerCamera4C;
	static int playerCamera;
	static int isCameraFree;

	static const char state[] = "Jacking a Car...";

	_asm
	{
		cmp GAME_VERSION, 0x180
        jz ONEZERO
        cmp GAME_VERSION, 0x18B
        jz ONETWO

		ONEZERO:
		mov playerCamera4C, ecx
		mov ecx, back10
		mov back, ecx
		mov ecx, playerCamera4C
		jmp Logic

		ONETWO:
		mov playerCamera4C, ecx
		mov ecx, back12
		mov back, ecx
		mov ecx, playerCamera4C
		jmp Logic

		Logic:
		mov [ecx+0x94], al
		mov playerCamera4C, ecx
		mov ecx, [ecx+0x94]
		mov isCameraFree, ecx
		mov ecx, playerCamera4C
		mov ecx, [ecx+0x10]
		mov playerCamera, ecx
		mov ecx, playerCamera4C

		cmp playerCamera, 0x7
		jge No
		cmp isCameraFree, 0x1
		jne SetNull
		mov [discordClient.discordPresence.state], offset state
		jmp UpdatePresence
		
		No:
		jmp UpdatePresence

		SetNull:
		mov [discordClient.discordPresence.state], 0
		jmp UpdatePresence

		UpdatePresence:
		mov ecx, offset discordClient
		call Discord::UpdatePresence
		mov ecx, playerCamera4C
		jmp back
	}
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
			Helpers::Nop(0x005DAAF7);
            Helpers::Nop(0x00623E90);
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
			Helpers::Nop(0x005F34E7);
        }
        else exit(1);

		#ifdef DEBUG
        AllocConsole();
        FILE* stream;
        freopen_s(&stream, "CONOUT$", "w", stdout);
		#endif // DEBUG
    }
    return 1;
}