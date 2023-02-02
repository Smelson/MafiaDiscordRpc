#include "Discord.hpp"
#include <map>
#include <string>

struct MissionPresenceInfo
{
	const char* details;
	const char* largeImageKey;
};

std::map<std::string, MissionPresenceInfo> SetMap();
void GetMafiaMissionsNames(Discord* discord, std::map<std::string, MissionPresenceInfo> presenceMap, const char* mission);