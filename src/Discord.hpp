#pragma once
#include "DiscordSDK/src/discord_register.h"
#include "DiscordSDK/src/discord_rpc.h"
#include <vcruntime_string.h>

#define MAFIA_APPLICATION_ID "747679968389234783"

class Discord
{
public:
    DiscordEventHandlers handler;
    DiscordRichPresence discordPresence;

    void Initialize();
    void UpdatePresence();
    void Shutdown();
};