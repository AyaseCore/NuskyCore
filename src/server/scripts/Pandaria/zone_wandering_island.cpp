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
#include "ScriptedEscortAI.h"

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

        bool IsInCombat;
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
            IsInCombat = false;
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
                IsInCombat = false;
                me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                Talk(urand(0, 7));
                me->GetMotionMaster()->MovePoint(0, 1446.322876f, 3389.027588f, 173.782471f);
        	}
        }

        void EnterCombat(Unit* unit)
        {
        	IsInCombat = true;
        }

        void JustRespawned()
        {
        	Reset();
        }

        void UpdateAI(const uint32 diff)
        {
            if (IsInCombat)
            {
            	DoMeleeAttackIfReady();
                return;
            }
            else
            {
            	if (punch1 <= diff)
                {
                	me->HandleEmoteCommand(35);
                    punch1 = 7500;
                }
                else
                   	punch1 -= diff;

                if (punch2 <= diff)
                {
                    me->HandleEmoteCommand(36);
                    punch2 = 7500;
                }
                else
                    punch2 -= diff;

               	if (punch3 <= diff)
                {
                    me->HandleEmoteCommand(37);
                    punch3 = 7500;
                }
                else
                    punch3 -= diff;
            }

			if (me->GetPositionX() == 1446.322876f && me->GetPositionY() == 3389.027588f && me->GetPositionZ() == 173.782471f)
			{
				//me->ForcedDespawn(1000);
			}
    	}
    };

    CreatureAI* GetAI(Creature* creature) const
    {
    	return new npc_tushui_trainee_AI(creature);
    }
};

class npc_huojin_trainee : public CreatureScript
{
    public:
        npc_huojin_trainee() : CreatureScript("npc_huojin_trainee") { }

    struct npc_huojin_traineeAI : public ScriptedAI
    {
        npc_huojin_traineeAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 punch;
        bool IsInCombat;

        void Reset()
        {
            punch = urand(500, 3000);
            me->SetReactState(REACT_DEFENSIVE);
            me->SetFullHealth();
            me->setFaction(7);
        	IsInCombat = false;
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPctDamaged(16.67f, damage))
            {
            	damage = 0;
                if (attacker && attacker->GetTypeId() == TYPEID_PLAYER)
                    attacker->ToPlayer()->KilledMonsterCredit(54586, 0);
                    
                me->CombatStop();
                me->setFaction(35);
                IsInCombat = false;
                me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
               	Talk(urand(0, 7));
                me->GetMotionMaster()->MovePoint(0, 1446.322876f, 3389.027588f, 173.782471f);
            }
        }

        void EnterCombat(Unit* unit)
        {
        	IsInCombat = true;
        }

        void JustRespawned()
        {
        	Reset();
        }

        void UpdateAI(const uint32 diff)
        {
        	if (IsInCombat)
            {
            	DoMeleeAttackIfReady();
                return;
            }
            else
            {
            	if (punch <= diff)
                {
                    me->HandleEmoteCommand(35);
                    punch = urand(500, 3000);
                }
                else
                	punch -= diff;
            }

			if (me->GetPositionX() == 1446.322876f && me->GetPositionY() == 3389.027588f && me->GetPositionZ() == 173.782471f)
			{
				//me->ForcedDespawn(1000);
			}
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
    	return new npc_huojin_traineeAI(creature);
    }
};

class npc_jaomin_ro : public CreatureScript
{
public:
    npc_jaomin_ro() : CreatureScript("npc_jaomin_ro") { }

    bool OnGossipHello(Player*player , Creature*creature)
    {
    	if (Creature* vehicle = player->SummonCreature(55685, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation()))
        {
        	creature->GetAI()->Reset();
        }

        return true;
    }
};

class boss_jaomin_ro : public CreatureScript
{
public:
    boss_jaomin_ro() : CreatureScript("boss_jaomin_ro") { }
    
    struct boss_jaomin_roAI : public ScriptedAI
    {
        boss_jaomin_roAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_DEFENSIVE);
            me->SetDisplayId(39755);
            me->setFaction(14); //mechant!
        }

        enum eEvents
        {
            EVENT_JAOMIN_JUMP   = 1,
            EVENT_HIT_CIRCLE    = 2,
            EVENT_FALCON        = 3,
            EVENT_RESET         = 4,
            EVENT_CHECK_AREA    = 5,
        };
        
        EventMap events;
        bool isInFalcon;

        void EnterCombat(Unit* unit)
        {
            Talk(0);
            events.ScheduleEvent(EVENT_JAOMIN_JUMP, 1000);
            events.ScheduleEvent(EVENT_HIT_CIRCLE, 2000);
            events.ScheduleEvent(EVENT_CHECK_AREA, 2500);
        }
        
        void Reset()
        {
            isInFalcon = false;
            me->SetReactState(REACT_DEFENSIVE);
            me->SetDisplayId(39755);
            me->setFaction(2357); //mechant!
            me->CombatStop(true);

            me->GetMotionMaster()->MovePoint(1, 1380.35f, 3170.68f, 136.93f);
        }
        
        void DamageTaken(Unit* attacker, uint32& damage)
        {
            if (me->HealthBelowPctDamaged(30, damage) && !isInFalcon)
            {
                isInFalcon = true;
                me->SetDisplayId(39796); //faucon
                events.ScheduleEvent(EVENT_FALCON, 1000);
                events.CancelEvent(EVENT_JAOMIN_JUMP);
                events.CancelEvent(EVENT_HIT_CIRCLE);
            }

            if (me->HealthBelowPctDamaged(5, damage))
            {
                me->SetDisplayId(39755);

                std::list<Player*> playerList;
                GetPlayerListInGrid(playerList, me, 10.0f);
                for (auto player: playerList)
                    player->KilledMonsterCredit(me->GetEntry(), 0);

                me->CombatStop();
                me->setFaction(35);
                me->SetFullHealth();
                me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                events.Reset();
                events.ScheduleEvent(EVENT_RESET, 5000);
                damage = 0;
            }

            if (damage > me->GetHealth())
                damage = 0;
        }
        
        void UpdateAI(const uint32 diff)
        {            
            events.Update(diff);
            
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_JAOMIN_JUMP: //on monte
                        if (me->GetVictim())
                            me->CastSpell(me->GetVictim(), 108938, true);
                        events.ScheduleEvent(EVENT_JAOMIN_JUMP, 30000);
                        break;
                    case EVENT_HIT_CIRCLE: //baffe
                        if (me->GetVictim())
                            me->CastSpell(me->GetVictim(), 119301, true);

                        events.ScheduleEvent(EVENT_HIT_CIRCLE, 3000);
                        break;
                    case EVENT_FALCON: //attaque du faucon
                        if (me->GetVictim())
                            me->CastSpell(me->GetVictim(), 108935, true);

                        events.ScheduleEvent(EVENT_FALCON, 4000);
                        break;
                    case EVENT_RESET: //remechant
                        Reset();
                    	break;
                    case EVENT_CHECK_AREA:
                        if (me->GetAreaId() != 5843) // Grotte Paisible
                            Reset();
                        break;
                }
            }
            
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_jaomin_roAI(creature);
    }
};

class npc_aysa_lake_escort : public CreatureScript
{
public:
    npc_aysa_lake_escort() : CreatureScript("npc_aysa_lake_escort") { }

    struct npc_aysa_lake_escortAI : public npc_escortAI
    {        
        npc_aysa_lake_escortAI(Creature* creature) : npc_escortAI(creature) { }

        uint32 IntroTimer;

        void Reset()
        {
            IntroTimer = 2500;
        }

        void MovementInform(uint32 uiType, uint32 uiId)
        {
            npc_escortAI::MovementInform(uiType, uiId);

            if (uiType != POINT_MOTION_TYPE && uiType != EFFECT_MOTION_TYPE)
                return;

            switch (uiId)
            {
                case 10:
                    me->GetMotionMaster()->MoveJump(1227.11f, 3489.73f, 100.37f, 10, 20, 11);
                    break;
                case 11:
                    me->GetMotionMaster()->MoveJump(1236.68f, 3456.68f, 102.58f, 10, 20, 12);
                    break;
                case 12:
                    Start(false, true);
                    break;
                default:
                    break;
            }
        }

        void WaypointReached(uint32 waypointId)
        {
            if (waypointId == 4)
                me->DespawnOrUnsummon(500);
        }

        void UpdateAI(const uint32 diff)
        {
            if (IntroTimer)
            {
                if (IntroTimer <= diff)
                {
                    //me->MonsterYell("Follow me!", LANG_UNIVERSAL, 0);
                    IntroTimer = 0;
                    me->GetMotionMaster()->MoveJump(1216.78f, 3499.44f, 91.15f, 10, 20, 10);
                }
                else
                    IntroTimer -= diff;
            }

            npc_escortAI::UpdateAI(diff);
        }
    };
    
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aysa_lake_escortAI(creature);
    }
    
};

#define ACTION_TALK_1 2

class npc_aysa : public CreatureScript
{
public:
    npc_aysa() : CreatureScript("npc_aysa") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == 29414) // La voie des tushui
            if (Creature* tempSummon = creature->SummonCreature(56661, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, player->GetGUID()))
                tempSummon->SetPhaseMask(1, true);

        return true;
    }
    
    struct npc_aysaAI : public ScriptedAI
    {
    	EventMap events;
        std::list<Player*> playersInvolved;
        uint64 lifeiGUID;
        bool inCombat;
        uint64 timer;
        bool hasSaidIntro;
        
        npc_aysaAI(Creature* creature) : ScriptedAI(creature)
        {
            events.ScheduleEvent(1, 600); //Begin script
            inCombat = false;
            hasSaidIntro = false;
            timer = 0;
            lifeiGUID = 0;
            me->SetReactState(REACT_DEFENSIVE);
            me->setFaction(2263);
        }

        enum eEvents
        {
            EVENT_START         = 1,
            EVENT_SPAWN_MOBS    = 2,
            EVENT_PROGRESS      = 3,
            EVENT_END           = 4,
        };
        
        void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
        {
            if(me->HealthBelowPctDamaged(5, uiDamage))
            {
                if(lifeiGUID)
                {
                    if (Creature* lifei = me->GetCreature(*me, lifeiGUID))
                        if (TempSummon* summon = lifei->ToTempSummon())
                            summon->UnSummon();
                    lifeiGUID = 0;
                }
                
                uiDamage = 0;
                me->MonsterSay("I can't meditate!", LANG_UNIVERSAL, 0);
                me->SetFullHealth();
                me->SetReactState(REACT_DEFENSIVE);
                
                std::list<Creature*> unitlist;
                GetCreatureListWithEntryInGrid(unitlist, me, 59637, 50.0f);
                for (auto creature: unitlist)
                    me->Kill(creature);
                	
                events.ScheduleEvent(EVENT_START, 20000);
                events.CancelEvent(EVENT_SPAWN_MOBS);
                events.CancelEvent(EVENT_PROGRESS);
                events.CancelEvent(EVENT_END);
            }
        }
        
        void updatePlayerList()
        {
            playersInvolved.clear();
            
            std::list<Player*> PlayerList;
            GetPlayerListInGrid(PlayerList, me, 20.0f);

            for (auto player: PlayerList)
            {
                if (player->GetQuestStatus(29414) == QUEST_STATUS_INCOMPLETE)
                    playersInvolved.push_back(player);

                if (player->GetQuestStatus(29419) == QUEST_STATUS_COMPLETE && player->GetQuestStatus(29424) == QUEST_STATUS_COMPLETE 
                    && me->GetPositionX() == 1206.310059f && me->GetPositionY() == 3507.459961f)
                {
                    DoAction(ACTION_TALK_1);
                }
                else if (player->GetQuestStatus(29410) != QUEST_STATUS_INCOMPLETE)
                    me->SetReactState(REACT_PASSIVE);
            }
        }

        void DoAction(int32 action)
        {
            switch (action)
            {
				case ACTION_TALK_1:
					if (!hasSaidIntro)
					{
						Talk(0);
						hasSaidIntro = true;
					}
					break;
            }
        }
        
        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_START: //Begin script if playersInvolved is not empty
                    {
                    	updatePlayerList();
                        if(playersInvolved.empty())
                            events.ScheduleEvent(1, 600);
                        else
                        {
                            me->MonsterSay("Keep those creatures at bay while I meditate. We'll soon have the answers we seek...", LANG_UNIVERSAL, 0);
                            me->SetReactState(REACT_PASSIVE);
                            timer = 0;
                            events.ScheduleEvent(EVENT_SPAWN_MOBS, 5000); //spawn mobs
                            events.ScheduleEvent(EVENT_PROGRESS, 1000); //update time
                            events.ScheduleEvent(EVENT_END, 90000); //end quest
                        }
                        break;
                    }
                    case EVENT_SPAWN_MOBS: //Spawn 3 mobs
                    {
                        updatePlayerList();
                        for(int i = 0; i < std::max((int)playersInvolved.size()*3,3); i++)
                        {
                            if(TempSummon* temp = me->SummonCreature(59637, 1144.55f, 3435.65f, 104.97f, 3.3f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                            {
                                if (temp->AI())
                                    temp->AI()->AttackStart(me);

			                    temp->AddThreat(me, 250.0f);
                                temp->GetMotionMaster()->Clear();
                                temp->GetMotionMaster()->MoveChase(me);
                            }
                        }
                        events.ScheduleEvent(EVENT_SPAWN_MOBS, 20000); //spawn mobs
                        break;
                    }
                    case EVENT_PROGRESS: //update energy
                    {
                        timer++;

                        TempSummon* lifei = NULL;
                        if (Creature* c = me->GetCreature(*me, lifeiGUID))
                            if (TempSummon* summon = c->ToTempSummon())
                                lifei = summon;

                        if(timer == 25 && !lifeiGUID)
                        {
                            if (lifei = me->SummonCreature(54856, 1130.162231f, 3435.905518f, 105.496597f, 0.0f,TEMPSUMMON_MANUAL_DESPAWN))
                            {
                                lifeiGUID = lifei->GetGUID();
                                lifei->MonsterSay("The way of the Tushui... enlightenment through patience and mediation... the principled life", LANG_UNIVERSAL, 0);
                            }
                        }
                        
                        if(timer == 30)
                            if (lifei)
                                lifei->MonsterSay("It is good to see you again, Aysa. You've come with respect, and so I shall give you the answers you seek.", LANG_UNIVERSAL, 0);
                        
                        if(timer == 42)
                            if (lifei)
                                lifei->MonsterSay("Huo, the spirit of fire, is known for his hunger. He wants for tinder to eat. He needs the caress of the wind to rouse him.", LANG_UNIVERSAL, 0);
                        
                        if(timer == 54)
                            if (lifei)
                                lifei->MonsterSay("If you find these things and bring them to his cave, on the far side of Wu-Song Village, you will face a challenge within.", LANG_UNIVERSAL, 0);
                        
                        if(timer == 66)
                            if (lifei)
                                lifei->MonsterSay("Overcome that challenge, and you shall be graced by Huo's presence. Rekindle his flame, and if your spirit is pure, he shall follow you.", LANG_UNIVERSAL, 0);
                        
                        if(timer == 78)
                            if (lifei)
                                lifei->MonsterSay("Go, children. We shall meet again very soon.", LANG_UNIVERSAL, 0);
                        
                        if(timer == 85)
                        {
                            if (lifei)
                                lifei->UnSummon();

                            lifei = NULL;
                            lifeiGUID = 0;
                        }
                        
                        updatePlayerList();
                        for (auto player: playersInvolved)
                        {
                            if(!player->HasAura(116421))
                                player->CastSpell(player, 116421);

                            player->ModifyPower(POWER_ALTERNATE_POWER, timer/25);
                            player->SetMaxPower(POWER_ALTERNATE_POWER, 90);
                        }

                        events.ScheduleEvent(EVENT_PROGRESS, 1000);
                        break;
                    }
                    case EVENT_END: //script end
                    {
                        TempSummon* lifei = NULL;

                        if (Creature* c = me->GetCreature(*me, lifeiGUID))
                            if (TempSummon* summon = c->ToTempSummon())
                                lifei = summon;

                        if(lifei)
                        {
                            lifei->UnSummon();
                            lifei = NULL;
                            lifeiGUID = 0;
                        }

                        events.ScheduleEvent(EVENT_START, 10000);
                        events.CancelEvent(EVENT_SPAWN_MOBS);
                        events.CancelEvent(EVENT_PROGRESS);
                        me->MonsterSay("And so our path lays before us. Speak to Master Shang Xi, he will tell you what comes next.", LANG_UNIVERSAL, 0);
                        updatePlayerList();
                        me->SetReactState(REACT_DEFENSIVE);
                        for(auto player: playersInvolved)
                        {
                            player->KilledMonsterCredit(54856, 0);
                            player->RemoveAura(116421);
                        }
                        break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aysaAI(creature);
    }
};

void AddSC_zone_wandering_island()
{
    new npc_master_shang_xi();
	new go_wandering_weapon_rack();
    new npc_training_target();
    new npc_tushui_trainee();
    new npc_huojin_trainee();
    new npc_jaomin_ro();
    new boss_jaomin_ro();
    new npc_aysa_lake_escort();
    new npc_aysa();
}
