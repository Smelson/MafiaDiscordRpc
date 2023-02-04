#include <Windows.h>
#include "Discord.hpp"
#include "Helper.hpp"

class Mafia
{
private:
	DWORD BASE_ADDRESS_PLAYER;
	DWORD BASE_ADDRESS_MISSION;
	int GAME_VERSION;

public:
	void SetBaseAddressPlayer(DWORD baseAddressPlayer);
	void SetBaseAddressMission(DWORD baseAddressMission);
	void SetGameVersion(int gameVersion);

	DWORD GetBaseAddressPlayer();
	DWORD GetBaseAddressMission();
	int GetGameVersion();

	void Initialize(Discord* discord, DWORD baseAddressPlayer, DWORD baseAddressMission, int gameVersion, const char* smallImageText);
};

class MafiaSDK
{
public:
	static int GetGameVersion();
};