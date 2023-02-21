#include "Mafia.hpp"
#include "GetMiseNames.hpp"
#include <chrono>

void Mafia::SetBaseAddressMission(DWORD baseAddressMission)
{
	BASE_ADDRESS_MISSION = baseAddressMission;
}	

void Mafia::SetBaseAddressPlayer(DWORD baseAddressPlayer)
{
	BASE_ADDRESS_PLAYER = baseAddressPlayer;
}

void Mafia::SetGameVersion(int gameVersion)
{
	GAME_VERSION = gameVersion;
}

DWORD Mafia::GetBaseAddressMission()
{
	return BASE_ADDRESS_MISSION;
}

DWORD Mafia::GetBaseAddressPlayer()
{
	return BASE_ADDRESS_PLAYER;
}

int Mafia::GetGameVersion()
{
	if (*(DWORD*)0x005F99FE == 384)
		return 384;
	if (*(DWORD*)0x005BE48E == 393)
		return 393;
	if (*(DWORD*)0x005BEC2E == 395)
		return 395;
	return 0;
}

void Mafia::Initialize(Discord& discord, DWORD baseAddressMission, DWORD baseAddressPlayer, int gameVersion, const char* smallImageText)
{
	SetBaseAddressMission(baseAddressMission);
	SetBaseAddressPlayer(baseAddressPlayer);
	SetGameVersion(gameVersion);

	discord.discordPresence.smallImageText = smallImageText;
	discord.discordPresence.smallImageKey = "mafia_new";
}

void GameLoop(Discord& discord, Mafia& mafia, std::map<std::string, MissionPresenceInfo> presenceMap, bool IS_DEBUG)
{
	DWORD BASE_ADDRESS_MISSION = mafia.GetBaseAddressMission();
	DWORD BASE_ADDRESS_PLAYER = mafia.GetBaseAddressPlayer();
	const char* mission;

	std::string missionString = "00menu";

	mission = (const char*)Helpers::GetPointerAddress(BASE_ADDRESS_MISSION, { 0x68, 0x0 });
	missionString = mission;

	GetMafiaMissionsNames(discord, presenceMap, mission, IS_DEBUG);

	discord.discordPresence.startTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	discord.discordPresence.state = NULL;

	discord.UpdatePresence();
}
