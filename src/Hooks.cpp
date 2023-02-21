#include "Hooks.hpp"

extern Discord discordClient;
extern int GAME_VERSION;

__declspec(naked) void OnGameExit()
{
    _asm add esp, 3ECh
	discordClient.ClearPresence();
	discordClient.Shutdown();
	_asm retn 10h
}

__declspec(naked) void OnGameLoading()
{
    static unsigned long back10 = 0x005FB1D9;
    static unsigned long back12 = 0x005BFDE1;
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
    static unsigned long func10 = 0x6243AC;
	static unsigned long func12 = 0x60FCF6;
    static unsigned long back10 = 0x5E075B;
	static unsigned long back12 = 0x5A4CFE;
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
    static unsigned long func10 = 0x5DA4B0;  
	static unsigned long func12 = 0x5F2EA0;
    static unsigned long back10 = 0x5D4AC2;
	static unsigned long back12 = 0x5ED1B2;
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
    static unsigned long func10 = 0x5DA4B0;
	static unsigned long func12 = 0x5F2EA0;
    static unsigned long back10 = 0x5D4AE1;
	static unsigned long back12 = 0x5ED1D1;

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
    static unsigned long func10 = 0x5DA4B0;
	static unsigned long func12 = 0x5F2EA0;
    static unsigned long back10 = 0x5D4D6B;
	static unsigned long back12 = 0x5ED45B;

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
	static unsigned long back10 = 0x5DAAF8;
	static unsigned long back12 = 0x5F34E8;
	static unsigned long back;
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