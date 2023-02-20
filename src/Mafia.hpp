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
    DWORD BASE_ADDRESS_MISSION;

public:
	void SetBaseAddressMission(DWORD baseAddressMission);
	void SetGameVersion(int gameVersion);

	DWORD GetBaseAddressMission();
	int GetGameVersion();

	void Initialize(Discord& discord, DWORD baseAddressMission, int gameVersion, const char* smallImageText);
};

void GameLoop(Discord& discord, Mafia& mafia, std::map<std::string, MissionPresenceInfo> presenceMap);