cmake_minimum_required(VERSION 3.15)
project(MafiaRpc)

set(CMAKE_CXX_STANDARD 14)

set(SRC
        src/main.cpp
        src/Mafia.cpp
        src/Helper.cpp
        src/GetMiseNames.cpp
        src/Discord.cpp)

set (HEADER
        src/main.hpp
        src/Mafia.hpp
        src/Helper.hpp
        src/GetMiseNames.hpp
        src/Discord.hpp)

set (DISCORDSDK
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
        src/DiscordSDK/src/discord_register.h
        src/DiscordSDK/src/discord_rpc.h)

add_library(MafiaRpc SHARED ${SRC} ${HEADER} ${DISCORDSDK})
