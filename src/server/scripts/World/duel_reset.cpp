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

#include "ScriptMgr.h"
#include "World.h"

class DuelResetScript : public PlayerScript
{
public:
	DuelResetScript() : PlayerScript("DuelResetScript") { }

	void OnDuelStart(Player* player1, Player* player2) override
    {
    	// Cooldowns reset
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWNS))
        {
            player1->RemoveArenaSpellCooldowns();
            player2->RemoveArenaSpellCooldowns();
        }

        // Health and mana reset
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_HEALTH_MANA))
        {
        	player1->SaveHealthBeforeDuel();
            player1->SetHealth(player1->GetMaxHealth());

            player2->SaveHealthBeforeDuel();
            player2->SetHealth(player2->GetMaxHealth());

            // check if player1 class uses mana
            if (player1->getPowerType() == POWER_MANA || player1->getClass() == CLASS_DRUID)
            {
                player1->SaveManaBeforeDuel();
                player1->SetPower(POWER_MANA, player1->GetMaxPower(POWER_MANA));
            }

            // check if player2 class uses mana
            if (player2->getPowerType() == POWER_MANA || player2->getClass() == CLASS_DRUID)
            {
                player2->SaveManaBeforeDuel();
                player2->SetPower(POWER_MANA, player2->GetMaxPower(POWER_MANA));
            }
        }
    }
    
	void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
	{
		if (type == DUEL_WON)
        {
        	pWinner->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
        	
        	if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWNS))
            {
                pWinner->RemoveArenaSpellCooldowns();
                pLoser->RemoveArenaSpellCooldowns();
            }

            if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_HEALTH_MANA))
            {
                pWinner->RestoreHealthAfterDuel();
                pLoser->RestoreHealthAfterDuel();

                // check if player1 class uses mana
                if (pWinner->getPowerType() == POWER_MANA || pWinner->getClass() == CLASS_DRUID)
                    pWinner->RestoreManaAfterDuel();

                // check if player2 class uses mana
                if (pLoser->getPowerType() == POWER_MANA || pLoser->getClass() == CLASS_DRUID)
                    pLoser->RestoreManaAfterDuel();
            }
       	}
	}
};

void AddSC_duel_reset()
{
    new DuelResetScript();
}