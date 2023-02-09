#include "Discord.hpp"

void Discord::Initialize()
{
    memset(&handler, 0, sizeof(handler));
    Discord_Initialize(MAFIA_APPLICATION_ID, &handler, 1, NULL);
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
}

void Discord::UpdatePresence()
{
    Discord_UpdatePresence(&discordPresence);
}

void Discord::Shutdown()
{
    Discord_Shutdown();
}