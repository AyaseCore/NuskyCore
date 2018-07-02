# Copyright (C) 2013-2018 NuskyCore <http://www.nuskycore.org/
# Copyright (C) 2008-2018 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  World/achievement_scripts.cpp
  World/areatrigger_scripts.cpp
  World/boss_emerald_dragons.cpp
  World/chat_log.cpp
  world/duel_reset.cpp
  World/go_scripts.cpp
  World/guards.cpp
  World/item_scripts.cpp
  World/mob_generic_creature.cpp
  World/npc_innkeeper.cpp
  World/npc_professions.cpp
  World/npc_taxi.cpp
  World/npcs_special.cpp
)

message("  -> Prepared: World")
