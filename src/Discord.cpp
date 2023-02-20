#include "Discord.hpp"

void Discord::Initialize()
{
    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(MAFIA_APPLICATION_ID, &handlers, 1, NULL);
}

void Discord::UpdatePresence()
{
    Discord_UpdatePresence(&discordPresence);
}

void Discord::Shutdown()
{
    Discord_Shutdown();
}