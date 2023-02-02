#include "Mafia.hpp"
#include "GetMiseNames.hpp"
#include <chrono>

#define SLEEPTIME 1000

void Mafia::SetBaseAddressPlayer(DWORD baseAddressPlayer)
{
	BASE_ADDRESS_PLAYER = baseAddressPlayer;
}

void Mafia::SetBaseAddressMission(DWORD baseAddressMission)
{
	BASE_ADDRESS_MISSION = baseAddressMission;
}

void Mafia::SetGameVersion(int gameVersion)
{
	GAME_VERSION = gameVersion;
}

DWORD Mafia::GetBaseAddressPlayer()
{
	return BASE_ADDRESS_PLAYER;
}

DWORD Mafia::GetBaseAddressMission()
{
	return BASE_ADDRESS_MISSION;
}

int Mafia::GetGameVersion()
{
	return GAME_VERSION;
}

void Mafia::Initialize(Discord* discord, DWORD baseAddressPlayer, DWORD baseAddressMission, int gameVersion, const char* smallImageText)
{
	SetBaseAddressPlayer(baseAddressPlayer);
	SetBaseAddressMission(baseAddressMission);
	SetGameVersion(gameVersion);

	discord->discordPresence.smallImageText = smallImageText;
	discord->discordPresence.startTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	discord->discordPresence.smallImageKey = "mafia_new";
}

//////////////////////////////////////////////////////////////

int MafiaSDK::GetGameVersion()
{
	if (*(DWORD*)0x005F99FE == 384)
		return 384;
	if (*(DWORD*)0x005BE48E == 393)
		return 393;
	if (*(DWORD*)0x005BEC2E == 395)
		return 395;
	return 0;
}

/////////////////////////////////////////////////////////////

void GameLoop(Discord* discord, Mafia* mafia)
{
	discord->Initialize();

	std::map<std::string, MissionPresenceInfo> presenceMap = SetMap();
	DWORD BASE_ADDRESS_PLAYER = mafia->GetBaseAddressPlayer();
	DWORD BASE_ADDRESS_MISSION = mafia->GetBaseAddressMission();

	const char* mission;
	int isLoaded;
	int playerCamera;
	int playerRotateCamera;
	int isInCar;

	std::string missionString = "00menu";

	while (true)
	{
		mission = (const char*)GetPointerAddress(BASE_ADDRESS_MISSION, { 0x68, 0x0 });
		isLoaded = *(int*)GetPointerAddress(BASE_ADDRESS_PLAYER, { 0x40 });
		playerCamera = *(int*)GetPointerAddress(BASE_ADDRESS_PLAYER, { 0x5c });
		playerRotateCamera = *(int*)GetPointerAddress(BASE_ADDRESS_PLAYER, { 0xE0 });	

		if (playerCamera > 6 && playerCamera < 16)
			isInCar = 1;
		else
			isInCar = 0;

		missionString = mission;

		discord->discordPresence.details = mission;
		GetMafiaMissionsNames(discord, presenceMap, mission);

		if (isLoaded == 0)
			discord->discordPresence.state = "Loading...";
		else if (isLoaded == 1 && playerCamera == 22)
			discord->discordPresence.state = "Watching a cutscene...";
		else if (isLoaded == 1 && playerCamera == 17)
			discord->discordPresence.state = "On a Tram...";
		else if (isLoaded == 1 && playerRotateCamera == 1 && isInCar == 0)
			discord->discordPresence.state = "Trying to get in a car...";
		else if (isLoaded == 1 && isInCar == 1 && playerCamera != 17 && playerCamera != 22 && playerCamera != 24 && missionString != "00menu")
			discord->discordPresence.state = "Driving a car...";
		else if (isLoaded == 1 && isInCar == 0 && playerCamera != 17 && playerCamera != 22 && playerCamera != 24 && missionString != "00menu")
			discord->discordPresence.state = "Walking around...";
		else
			discord->discordPresence.state = NULL;

		discord->UpdatePresence();

		Sleep(SLEEPTIME);
	}
}

