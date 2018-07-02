/*
 * Copyright (C) 2013-2018 NuskyCore <http://www.nuskycore.org/>
 * Copyright (C) 2008-2018 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2018 MaNGOS <https://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

// Core configuration options

#ifndef Nusky_SYSTEMCONFIG_H
#define Nusky_SYSTEMCONFIG_H

#include "Define.h"
#include "revision.h"

#define _PACKAGENAME "NuskyCore 5.4.8 18414"

// Format is YYYYMMDDRR where RR is the change in the conf file
// for that day.
#ifndef NUSKYWORLD_CONFIG_VERSION
# define NUSKYWORLD_CONFIG_VERSION 2017091000
#endif
#ifndef NuskyAUTH_CONFIG_VERSION
# define NuskyAUTH_CONFIG_VERSION 2017021900
#endif

#if NUSKY_ENDIAN == NUSKY_BIGENDIAN
# define _ENDIAN_STRING "big-endian"
#else
# define _ENDIAN_STRING "little-endian"
#endif

#if PLATFORM == PLATFORM_WINDOWS
# ifdef _WIN64
#  define _FULLVERSION _PACKAGENAME " rev. " VER_PRODUCTVERSION_STR " (Win64, " _BUILD_DIRECTIVE ")"
# else
#  define _FULLVERSION _PACKAGENAME " rev. " VER_PRODUCTVERSION_STR " (Win32, " _BUILD_DIRECTIVE ")"
# endif
#else
#  define _FULLVERSION _PACKAGENAME " rev. " VER_PRODUCTVERSION_STR " (Unix, " _BUILD_DIRECTIVE ")"
#endif
#endif
