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

#ifndef NUSKYSERVER_ERRORS_H
#define NUSKYSERVER_ERRORS_H

#include "Define.h"

namespace Nusky
{

    DECLSPEC_NORETURN void Assert(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Fatal(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Error(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    void Warning(char const* file, int line, char const* function, char const* message);

} // namespace Nusky

#define WPAssert(cond) do { if (!(cond)) Nusky::Assert(__FILE__, __LINE__, __FUNCTION__, #cond); } while (0)
#define WPFatal(cond, msg) do { if (!(cond)) Nusky::Fatal(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPError(cond, msg) do { if (!(cond)) Nusky::Error(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPWarning(cond, msg) do { if (!(cond)) Nusky::Warning(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)

#define ASSERT WPAssert

#endif
