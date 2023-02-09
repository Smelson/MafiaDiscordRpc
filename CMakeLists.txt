cmake_minimum_required(VERSION 3.12)

project(MafiaRpc)

set(Source
	src/main.cpp
	src/Mafia.cpp
	src/Helper.cpp
	src/GetMiseNames.cpp
	src/Discord.cpp)

set(Header
	src/main.hpp
	src/Mafia.hpp
	src/Helper.hpp
	src/GetMiseNames.hpp
	src/Discord.hpp)

set(DiscordSDK
	src/DiscordSDK/src/backoff.h
	src/DiscordSDK/src/connection.h
	src/DiscordSDK/src/connection_win.cpp
	src/DiscordSDK/src/discord_register_win.cpp
	src/DiscordSDK/src/discord_rpc.cpp
	src/DiscordSDK/src/msg_queue.h
	src/DiscordSDK/src/rpc_connection.cpp
	src/DiscordSDK/src/rpc_connection.h
	src/DiscordSDK/src/serialization.cpp
	src/DiscordSDK/src/serialization.h)

include_directories(src/DiscordSDK/include)

add_library(MafiaRpc SHARED ${Source} ${Header} ${DiscordSDK})