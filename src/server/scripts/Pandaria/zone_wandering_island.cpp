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

/* ScriptData
SDName: wandering island (part 1)
SD%Complete: 0
SDComment: Placeholder
SDCategory: wandering_island
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"

#define ACTION_TALK 1

class npc_master_shang_xi : public CreatureScript
{
    enum master_shang
    {

        SPELL_MASTERS_FLAME = 114610,
        SPELL_CREATE_MASTERS_FLAME = 114611,
        SPELL_SNATCH_MASTERS_FLAME = 114746,

        ITEM_MASTERS_FLAME = 80212,

        QUEST_LESSONS_OF_BURNING_SCROLL = 29408,
    };

public:
    npc_master_shang_xi() : CreatureScript("npc_master_shang_xi") { }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_LESSONS_OF_BURNING_SCROLL) // The Lesson of the Burning Scroll
        {
            creature->AddAura(SPELL_MASTERS_FLAME, creature);
            creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
        }

        return true;
    }

    struct npc_master_shang_xi_AI : public ScriptedAI
    {
        npc_master_shang_xi_AI(Creature* creature) : ScriptedAI(creature)
        {
            resetTimer = 10000;
        }

        uint32 resetTimer;

        void SpellHit(Unit* caster, const SpellInfo* pSpell)
        {
            if (pSpell->Id == SPELL_SNATCH_MASTERS_FLAME) // Snatch Master's Flame
            {
                if (caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (caster->ToPlayer()->GetQuestStatus(QUEST_LESSONS_OF_BURNING_SCROLL) == QUEST_STATUS_INCOMPLETE)
                    {
                        me->CastSpell(caster, SPELL_CREATE_MASTERS_FLAME, true);
                        me->RemoveAurasDueToSpell(SPELL_MASTERS_FLAME);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                        Talk(0);
                    }
                }
            }
        }

        void MoveInLineOfSight(Unit * who)
        {
            Player * const player = who->ToPlayer();
            if (!player)
                return;

            if (player->GetQuestStatus(QUEST_LESSONS_OF_BURNING_SCROLL) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(ITEM_MASTERS_FLAME) && !me->HasAura(SPELL_MASTERS_FLAME))
                me->AddAura(SPELL_MASTERS_FLAME, me);
        }

        void UpdateAI(uint32 const diff)
        {
            // In case noone used spellclick - reset questgiver flag in periodic way
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
                return;

            if (resetTimer <= diff)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
                resetTimer = 10000;
            }
            else
                resetTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_master_shang_xi_AI(creature);
    }
};

class go_wandering_weapon_rack : public GameObjectScript
{
public:
    go_wandering_weapon_rack() : GameObjectScript("go_wandering_weapon_rack") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(30027) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(73209))
        {
            player->AddItem(73209, 1);
        }
        else if (player->GetQuestStatus(30033) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(76392) || !player->HasItemCount(76390)))
        {
            player->AddItem(76392, 1);
            player->AddItem(76390, 1);
        }
        else if (player->GetQuestStatus(30034) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(73211))
        {
            player->AddItem(73211, 1);
        }
        else if (player->GetQuestStatus(30035) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(76393) || !player->HasItemCount(73207)))
        {
            player->AddItem(76393, 1);
            player->AddItem(73207, 1);
        }
        else if (player->GetQuestStatus(30036) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(73212) || !player->HasItemCount(73208)))
        {
            player->AddItem(73212, 1);
            player->AddItem(73208, 1);
        }
        else if (player->GetQuestStatus(30037) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(73213) || !player->HasItemCount(76391)))
        {
            player->AddItem(73213, 1);
            player->AddItem(76391, 1);
        }
        else if (player->GetQuestStatus(30038) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(73210))
        {
            player->AddItem(73210, 1);
        }

        return true;
    }
};

class npc_training_target : public CreatureScript
{
public:
    npc_training_target() : CreatureScript("npc_training_target") { }

    struct npc_training_targetAI : public ScriptedAI
    {
        npc_training_targetAI(Creature* creature) : ScriptedAI(creature) {}
        
        void Reset() override
        {
            me->SetReactState(REACT_PASSIVE);
        }

		void EnterCombat(Unit * unit) override
        {
            return;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_training_targetAI(creature);
    }
};

class npc_tushui_trainee : public CreatureScript
{
public:
    npc_tushui_trainee() : CreatureScript("npc_tushui_trainee") { }

    struct npc_tushui_trainee_AI : public ScriptedAI
    {
        npc_tushui_trainee_AI(Creature* creature) : ScriptedAI(creature) {}

        bool isInCombat;
        uint64 playerGUID;
        uint32 punch1;
        uint32 punch2;
       	uint32 punch3;

        void Reset()
        {
            punch1 = 1000;
            punch2 = 3500;
            punch3 = 6000;
            playerGUID = 0;
            isInCombat = false;
           	me->SetReactState(REACT_DEFENSIVE);
            me->setFaction(7);
            me->SetFullHealth();
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPctDamaged(16.67f, damage))
            {
                me->setFaction(35);

                if (attacker && attacker->GetTypeId() == TYPEID_PLAYER)
                    attacker->ToPlayer()->KilledMonsterCredit(54586, 0);

                damage = 0;
                me->CombatStop();
                isInCombat = false;
                me->HandleEmote(EMOTE_ONESHOT_SALUTE);
                Talk(urand(0, 7));
                me->GetMotionMaster()->MovePoint(0, 1446.322876f, 3389.027588f, 173.782471f);
        	}
        }

        void EnterCombat(Unit* unit)
        {
        	isInCombat = true;
        }

        void JustRespawned()
        {
        	Reset();
        }

        void UpdateAI(const uint32 diff)
        {
            if (isInCombat)
            {
            	DoMeleeAttackIfReady();
                return;
            }
            else
            {
            	if (punch1 <= diff)
                {
                	me->HandleEmote(35);
                    punch1 = 7500;
                }
                else
                   	punch1 -= diff;

                if (punch2 <= diff)
                {
                    me->HandleEmote(36);
                    punch2 = 7500;
                }
                else
                    punch2 -= diff;

               	if (punch3 <= diff)
                {
                    me->HandleEmote(37);
                    punch3 = 7500;
                }
                else
                    punch3 -= diff;
            }

            if (me->GetPositionX() == 1446.322876f && me->GetPositionY() == 3389.027588f && me->GetPositionZ() == 173.782471f)
                me->ForcedDespawn(1000);
    	}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
    	return new npc_tushui_trainee_AI(creature);
    }
};

void AddSC_zone_wandering_island()
{
    new npc_master_shang_xi();
	new go_wandering_weapon_rack();
    new npc_training_target();
    new npc_tushui_trainee();
}
