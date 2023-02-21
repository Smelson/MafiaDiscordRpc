#pragma once
#include <discord_register.h>
#include <discord_rpc.h>
#include <vcruntime_string.h>

#define MAFIA_APPLICATION_ID "747679968389234783"

class Discord
{
public:
    DiscordRichPresence discordPresence;
    DiscordEventHandlers handlers;

    void Initialize();
    void UpdatePresence();
    void ClearPresence();
    void Shutdown();
};
