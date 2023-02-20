cmake_minimum_required(VERSION 3.12)

project(MafiaRpc)

set(CMAKE_CXX_STANDARD 14)

set(Source
	src/main.cpp
	src/Discord.cpp
	src/Helpers.cpp
	src/Mafia.cpp
	src/GetMiseNames.cpp
	)

set(Header 
	src/main.hpp
	src/Discord.hpp
	src/Helpers.hpp
	src/Mafia.hpp
	src/GetMiseNames.hpp
	)

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
	src/DiscordSDK/src/serialization.h
	)

include_directories(src/DiscordSDK/include)

add_library(MafiaRpc SHARED ${Source} ${Header} ${DiscordSDK})