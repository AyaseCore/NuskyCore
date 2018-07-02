#ifndef SC_SCRIPTLOADER_H
#define SC_SCRIPTLOADER_H

#include "Config.h"
#include "ScriptMgr.h"
#include "DatabaseEnv.h"

class System_Censure : public PlayerScript
{
public:
	System_Censure() : PlayerScript("System_Censure") {}

	static bool CheckMessage(Player* player, std::string& msg);

	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg)
	{
		System_Censure::CheckMessage(player, msg);
	}
	
	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* receiver)
	{
		System_Censure::CheckMessage(player, msg);
	}
	
	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* group)
	{
		System_Censure::CheckMessage(player, msg);
	}
	
	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
	{
		System_Censure::CheckMessage(player, msg);
	}
	
	void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* channel)
	{
		System_Censure::CheckMessage(player, msg);
	}
};

#endif