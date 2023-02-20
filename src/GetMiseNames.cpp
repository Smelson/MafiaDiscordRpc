#include "GetMiseNames.hpp"

std::map<std::string, MissionPresenceInfo> SetMap()
{
	std::map<std::string, MissionPresenceInfo> presenceMap;
	presenceMap["00menu"]					= 			MissionPresenceInfo{ "In Main Menu", "00menu" };
	presenceMap["autosalon"]				= 			MissionPresenceInfo{ "Carcyclopedia", "Carcyclopedia" };
	presenceMap["carcyclopedia"]			= 			MissionPresenceInfo{ "Carcyclopedia", "carcyklopedia" };
	presenceMap["extreme"]					= 			MissionPresenceInfo{ "Free Ride Extreme", "freeride" };
	presenceMap["freeitaly"]				= 			MissionPresenceInfo{ "Free Ride City - Small", "freeride" };
	presenceMap["freekrajina"]				= 			MissionPresenceInfo{ "Free Ride Country Side - Daytime", "freeride" };
	presenceMap["freekrajinanoc"]			= 			MissionPresenceInfo{ "Free Ride Country Side - Night", "freeride" };
	presenceMap["freeride"]					= 			MissionPresenceInfo{ "Free Ride City - Daytime", "freeride" };
	presenceMap["freeridenoc"]				= 			MissionPresenceInfo{ "Free Ride City - Night", "freeride" };
	presenceMap["intro"]					= 			MissionPresenceInfo{ "Intro", "intermezzo" };
	presenceMap["intermezzo02"]				= 			MissionPresenceInfo{ "Intermezzo-1", "intermezzo" };
	presenceMap["intermezzo03"]				= 			MissionPresenceInfo{ "Intermezzo-2", "intermezzo" };
	presenceMap["intermezzo4"]				= 			MissionPresenceInfo{ "Intermezzo-3", "intermezzo" };
	presenceMap["fmv intermezzo05"] 		= 			MissionPresenceInfo{ "Intermezzo-4", "intermezzo" };
	presenceMap["fmv konec"]				= 			MissionPresenceInfo{ "Epilogue", "intermezzo" };
	presenceMap["FMV KONEC"]				= 			MissionPresenceInfo{ "Epilogue", "intermezzo" };
	presenceMap["mise01"]					= 			MissionPresenceInfo{ "An Offer You Can't Refuse", "m01" };
	presenceMap["mise02a-taxi"]				= 			MissionPresenceInfo{ "The Running Man - Taxi Rank", "m02a" };
	presenceMap["mise02-saliery"]			= 			MissionPresenceInfo{ "The Running Man - Salieri Bar", "m02" };
	presenceMap["mise02-ulicka"]			= 			MissionPresenceInfo{ "The Running Man - Coffee Break", "m02" };
	presenceMap["mise03-morello"]			= 			MissionPresenceInfo{ "Molotov Party - City", "m03" };	
	presenceMap["mise03-saliery"]			= 			MissionPresenceInfo{ "Molotov Party - Salieri Bar", "m03" };
	presenceMap["mise03-salierykonec"] 		= 			MissionPresenceInfo{ "Molotov Party - Return To Salieri's Bar", "m03" };
	presenceMap["mise04-krajina"] 			= 			MissionPresenceInfo{ "Ordinary Routine - Get Him!", "m04" };
	presenceMap["mise04-mesto"] 			= 			MissionPresenceInfo{ "Ordinary Routine - After The Briefing", "m04" };
	presenceMap["mise04-saliery"] 			= 			MissionPresenceInfo{ "Ordinary Routine - Salieri Bar", "m04" };
	presenceMap["mise04-motorest"] 			= 			MissionPresenceInfo{ "Ordinary Routine - Clark's Motel", "m04" };
	presenceMap["mise05-mesto"] 			= 			MissionPresenceInfo{ "Fairplay - City", "m06" };
	presenceMap["mise05-saliery"] 			= 			MissionPresenceInfo{ "Fairplay - Salieri Bar", "m06" };
	presenceMap["mise06-autodrom"] 			= 			MissionPresenceInfo{ "Fairplay - Race", "m06" };
	presenceMap["mise06-mesto"] 			= 			MissionPresenceInfo{ "Fairplay - City", "m06" };
	presenceMap["mise06-oslava"] 			= 			MissionPresenceInfo{ "Fairplay - City", "m06" };
	presenceMap["mise06-saliery"] 			= 			MissionPresenceInfo{ "Fairplay - Salieri's Bar", "m06" };
	presenceMap["mise07b-chuligani"] 		= 			MissionPresenceInfo{ "Better Get Used To It - City", "m07b" };
	presenceMap["mise07b-saliery"] 			= 			MissionPresenceInfo{ "Better Get Used To It - Salieri Bar", "m07b" };
	presenceMap["mise07-saliery"] 			= 			MissionPresenceInfo{ "Sarah - Salieri Bar", "m07a" };
	presenceMap["mise07-sara"] 				= 			MissionPresenceInfo{ "Sarah - Moonlight Stroll", "m07a" };
	presenceMap["mise08-hotel"] 			= 			MissionPresenceInfo{ "The Whore - Hotel Corleone", "m08a" };
	presenceMap["mise08-kostel"] 			= 			MissionPresenceInfo{ "The Priest - Suprise", "m08a" };
	presenceMap["mise08-mesto"] 			= 			MissionPresenceInfo{ "The Whore - City", "m08a" };
	presenceMap["mise09-krajina"] 			= 			MissionPresenceInfo{ "A Trip To The Country - Return Journey", "m09" };
	presenceMap["mise09-mesto"] 			= 			MissionPresenceInfo{ "A Trip To The Country - City", "m09" };
	presenceMap["mise09-prejimka"] 			= 			MissionPresenceInfo{ "A Trip To The Country - The Farm", "m09" };
	presenceMap["mise09-saliery"] 			= 			MissionPresenceInfo{ "A Trip To The Country - Salieri Bar", "m09" };
	presenceMap["mise10-letiste"] 			= 			MissionPresenceInfo{ "Omerta - The Airport", "m10" };
	presenceMap["mise10-mesto"] 			= 			MissionPresenceInfo{ "Omerta - City", "m10" };
	presenceMap["mise10-saliery"] 			= 			MissionPresenceInfo{ "Omerta - Salieri Bar", "m10" };
	presenceMap["mise11-mesto"] 			= 			MissionPresenceInfo{ "Visiting Rich People - City", "m11" };
	presenceMap["mise11-saliery"] 			= 			MissionPresenceInfo{ "Visiting Rich People - Salieri Bar", "m11" };
	presenceMap["mise11-vila"] 				= 			MissionPresenceInfo{ "Visiting Rich People - The Villa", "m11" };
	presenceMap["mise12-garage"] 			= 			MissionPresenceInfo{ "A Great Deal! - The Parking Lot", "m12" };
	presenceMap["mise12-mesto"] 			= 			MissionPresenceInfo{ "A Great Deal! - Car Chase", "m12" };
	presenceMap["mise12-saliery"] 			= 			MissionPresenceInfo{ "A Great Deal! - Salieri Bar", "m12" };
	presenceMap["mise13-mesto"] 			= 			MissionPresenceInfo{ "Bon Appetit! - City", "m13" };
	presenceMap["mise13-mesto"] 			= 			MissionPresenceInfo{ "Bon Appetit! - After The Attack", "m13" };
	presenceMap["mise13-restaurace"] 		= 			MissionPresenceInfo{ "Bon Appetit! - Pepe's Restaurant", "m13" };
	presenceMap["mise13-zradce"] 			= 			MissionPresenceInfo{ "Bon Appetit! - Carlo", "m13" };
	presenceMap["mise14-mesto"] 			= 			MissionPresenceInfo{ "Happy Birthday! - City", "m14" };
	presenceMap["mise14-parnik"] 			= 			MissionPresenceInfo{ "Happy Birthday! - At The Party", "m14" };
	presenceMap["mise14-saliery"] 			= 			MissionPresenceInfo{ "Happy Birthday! - Vincenzo's Workshop", "m14" };
	presenceMap["mise15-mesto"] 			= 			MissionPresenceInfo{ "You Lucky Bastard! - City", "m15" };
	presenceMap["mise15-pristav"] 			= 			MissionPresenceInfo{ "You Lucky Bastard! - The Harbor", "m15" };
	presenceMap["mise15-saliery"] 			= 			MissionPresenceInfo{ "You Lucky Bastard! - Salieri Bar", "m15" };
	presenceMap["mise16-krajina"] 			= 			MissionPresenceInfo{ "Creme De La Creme - Manhunt", "m16" };
	presenceMap["mise16-letiste"] 			= 			MissionPresenceInfo{ "Creme De La Creme - The Airport", "m16" };
	presenceMap["mise16-mesto"] 			= 			MissionPresenceInfo{ "Creme De La Creme - City", "m16" };
	presenceMap["mise16-saliery"] 			= 			MissionPresenceInfo{ "Creme De La Creme - Salieri Bar", "m16" };
	presenceMap["mise17-mesto"] 			= 			MissionPresenceInfo{ "Election Campaign - City", "m17" };
	presenceMap["mise17-saliery"] 			= 			MissionPresenceInfo{ "Election Campaign - Salieri Bar", "m17" };
	presenceMap["mise17-vezeni"] 			= 			MissionPresenceInfo{ "Election Campaign - Old Prison", "m17" };
	presenceMap["mise18-mesto"] 			= 			MissionPresenceInfo{ "Just For Relaxation - City", "m18" };
	presenceMap["mise18-pristav"] 			= 			MissionPresenceInfo{ "Just For Relaxation - The Harbor", "m18" };
	presenceMap["mise18-saliery"] 			= 			MissionPresenceInfo{ "Just For Relaxation - Salieri Bar", "m18" };
	presenceMap["mise19-banka"] 			= 			MissionPresenceInfo{ "Moonlightning - The Bank", "m19" };
	presenceMap["mise19-mesto"] 			= 			MissionPresenceInfo{ "Moonlightning - City", "m19" };
	presenceMap["mise19-pauli"] 			= 			MissionPresenceInfo{ "Moonlightning - Paulie's Flat", "m19" };
	presenceMap["mise20-galery"] 			= 			MissionPresenceInfo{ "The Death Of Art - Grand Finale", "m20" };
	presenceMap["mise20-mesto"] 			= 			MissionPresenceInfo{ "The Death Of Art - City", "m20" };
	presenceMap["mise20-pauli"] 			= 			MissionPresenceInfo{ "The Death Of Art - Paulie's Flat", "m20" };
	presenceMap["tutorial"] 				= 			MissionPresenceInfo{ "Tutorial", "tutorial" };
	return presenceMap;
}

void GetMafiaMissionsNames(Discord& discord, std::map<std::string, MissionPresenceInfo> presenceMap, const char* mission)
{
	std::string missionString = mission;

	MissionPresenceInfo info = presenceMap[missionString];

	if (info.details == nullptr && info.largeImageKey == nullptr)
	{
		discord.discordPresence.details = mission;
		discord.discordPresence.largeImageKey = "";
		discord.discordPresence.largeImageText = mission;
		return;
	}

	discord.discordPresence.details = info.details;
	discord.discordPresence.largeImageKey = info.largeImageKey;
	discord.discordPresence.largeImageText = info.details;
}
