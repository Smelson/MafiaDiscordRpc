#include "Mafia.hpp"
#include "GetMiseNames.hpp"
#include <chrono>

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

void Mafia::Initialize(Discord& discord, DWORD baseAddressPlayer, DWORD baseAddressMission, int gameVersion, const char* smallImageText)
{
    SetBaseAddressPlayer(baseAddressPlayer);
    SetBaseAddressMission(baseAddressMission);
    SetGameVersion(gameVersion);

    discord.discordPresence.smallImageText = smallImageText;
    discord.discordPresence.smallImageKey = "mafia_new";
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

void GameLoop(Discord& discord, Mafia& mafia, std::map<std::string, MissionPresenceInfo> presenceMap)
{
    DWORD BASE_ADDRESS_MISSION = mafia.GetBaseAddressMission();

    const char* mission;

    std::string missionString = "00menu";

    mission = (const char*)Helpers::GetPointerAddress(BASE_ADDRESS_MISSION, { 0x68, 0x0 });
    missionString = mission;

    GetMafiaMissionsNames(discord, presenceMap, mission);
    discord.discordPresence.state = nullptr;
    discord.discordPresence.startTimestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    discord.UpdatePresence();
}
