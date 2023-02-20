#pragma once
#include <Windows.h>
#include "Discord.hpp"
#include "Helpers.hpp"
#include <map>
#include <string>
#include "GetMiseNames.hpp"

class Mafia
{
private:
    int GAME_VERSION;
	DWORD BASE_ADDRESS_PLAYER;
    DWORD BASE_ADDRESS_MISSION;

public:
	void SetBaseAddressMission(DWORD baseAddressMission);
	void SetBaseAddressPlayer(DWORD baseAddressPlayer);
	void SetGameVersion(int gameVersion);

	DWORD GetBaseAddressMission();
	DWORD GetBaseAddressPlayer();
	int GetGameVersion();

	void Mafia::Initialize(Discord& discord, DWORD baseAddressMission, DWORD baseAddressPlayer, int gameVersion, const char* smallImageText);
};

void GameLoop(Discord& discord, Mafia& mafia, std::map<std::string, MissionPresenceInfo> presenceMap);