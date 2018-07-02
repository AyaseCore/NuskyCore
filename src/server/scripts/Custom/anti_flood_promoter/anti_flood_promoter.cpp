/*
<--------------------------------------------------------------------------->
- Developer(s): NuskyDev
- Complete: 100%
- Atualizado: 12/05/2018
<--------------------------------------------------------------------------->
*/

#include "anti_flood_promoter.h"

bool MUTE__PLAYER;
int    TEMPO_MUTE;

std::vector<std::string> Rules;

bool System_Censure::CheckMessage(Player* player, std::string& msg)
{
	std::string lower = msg;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
	for (std::vector<std::string>::iterator it = Rules.begin(); it != Rules.end(); ++it) {
		if (lower.find(*it) != std::string::npos)
		{
			msg = "";
			ChatHandler(player->GetSession()).PSendSysMessage("|cffFFF000[ |cffFFFFFF! |cffFFF000] |cffFF4040Cuidado: Você pode ser banido, impossível enviar texto com links.|r");

			if (MUTE__PLAYER == 1)
			{
				player->GetSession()->m_muteTime = time(0) + TEMPO_MUTE;
				ChatHandler(player->GetSession()).PSendSysMessage("|cffe84118Você recebeu uma punição pela sua conduta.|r duração de |cfff5f6fa%u segundo(s)|r", TEMPO_MUTE);
			}

			std::string str = "";
			SessionMap ss = sWorld->GetAllSessions();
			for (SessionMap::const_iterator itr = ss.begin(); itr != ss.end(); ++itr)
				if (itr->second->GetSecurity() > 0)
					str = "|cfff5f6fa" + ChatHandler(player->GetSession()).GetNameLink() + "|r |cFFe84118Player usando chat ilegal!!|r";
			WorldPacket data(SMSG_NOTIFICATION, (str.size() + 1));
			data << str;
			sWorld->SendGlobalGMMessage(&data);
			return false;
		}
	}
	return true;
}

class SystemCensureWorld : public WorldScript
{
public:
	SystemCensureWorld() : WorldScript("SystemCensureWorld") { }

	void OnConfigLoad(bool /*reload*/)
	{
		MUTE__PLAYER        = sConfigMgr->GetBoolDefault("AntiSpam_MutePlayer", true);
		TEMPO_MUTE          = sConfigMgr->GetIntDefault("AntiSpam_TimeMute", 10);
		
		QueryResult Result = WorldDatabase.Query("SELECT text FROM chat_filter");
		if (!Result){
			return;	
		}			
		Rules.clear();
		do
		{
			Field* Fields = Result->Fetch();
			std::string moton = Fields[0].GetString();
			Rules.push_back(moton);
		}
		while (Result->NextRow());
	}
};

void AddSC_System_Censure()
{
	new System_Censure();
	new SystemCensureWorld();
}
