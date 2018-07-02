#include "ScriptMgr.h"

class AntiFarmSystem : public PlayerScript
{
public:
	AntiFarmSystem() : PlayerScript("AntiFarmSystem") {}
 
	void OnPVPKill(Player * killer, Player * killed)
	{
		if (killer->GetGUID() == killed->GetGUID())
			return;

		if (killer->GetSession()->GetRemoteAddress() == killed->GetSession()->GetRemoteAddress() || killed->GetMaxHealth() < 10000) // about 1/4 of the maximum hp a character can have on your server to make this fully functional.
		{
			std::string str = "";
           	SessionMap ss = sWorld->GetAllSessions();
            for (SessionMap::const_iterator itr = ss.begin(); itr != ss.end(); ++itr)
                if (itr->second->GetSecurity() > 0)
                str = "|cffFFFC00[Anti-Farm System]|cff00FFFF[|cff60FF00" + std::string(killer->GetName()) + "|cff00FFFF] Possivel Farmer |cffEE0000 [ATENÇÃO GMS!]";
            WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
            data << str;
            sWorld->SendGlobalGMMessage(&data);
		}
		else
			return;
	}
};

void AddSC_AntiFarmSystem()
{
   new AntiFarmSystem();
}