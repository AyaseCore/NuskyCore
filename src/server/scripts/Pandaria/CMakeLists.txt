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

  # Dungeons

  # Raids
  Pandaria/Raids/SiegeOfOrgrimmar/boss_Immerseus.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_Galakras.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_GeneralNazgrim.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_KorKron.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_IronJuggernaut.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_Norushen.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_Malkorok.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_ParagonsOfTheKlaxxi.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_ShaOfPride.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_SiegecrafterBlackfuse.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_SpoilsOfPandaria.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_TheFallenProtectors.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_Thok.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/boss_GarroshHellscream.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/instance_SiegeOfOrgrimmar.cpp
  Pandaria/Raids/SiegeOfOrgrimmar/SiegeOfOrgrimmar.h

  # WorldBosses

  # Zones

  Pandaria/boss_ordos.cpp
  Pandaria/zone_dread_wastes.cpp
  Pandaria/zone_isle_of_giants.cpp
  Pandaria/zone_isle_of_thunder.cpp
  Pandaria/zone_krasarang_wilds.cpp
  Pandaria/zone_kun_lai_summit.cpp
  Pandaria/zone_the_jade_forest.cpp
  Pandaria/zone_the_situation_in_dalaran.cpp
  Pandaria/zone_the_veiled_stair.cpp
  Pandaria/zone_timeless_isle.cpp
  Pandaria/zone_townlong_steppes.cpp
  Pandaria/zone_vale_of_eternal_blossoms.cpp
  Pandaria/zone_valley_of_the_four_winds.cpp
  Pandaria/zone_wandering_island.cpp
)

message("  -> Prepared: Pandaria")
