#include "Unell_Script.h"

static const char* checks[] = {
    "sytes", 
	"instant", 
	"dyndns",
    "no-ip",
    "http:",
    ".com",
    ".net",
    ".org",
    ".eu",
    ".fr",
    ".bg",
    ".info",
    ".br",
    "https:",
    "wow",
    "www.",
    "no-ip",
    ".zapto",
    ".biz",
    ".servegame",
    "trevonwow",
    "megawow",
    "fatalwow",
    "uniforgiven-wow",
    "wow-autolouco",
    "heaven-wow",
    "fireballwow",
    "wowbrasilpa",
    "fatalitywow",
    "demonic-wow",
    "revenge-wow",
    "heavenwow",
    "undead-wow",
    "linebr",
    "azralon",
    "black-wow",
	"w-o-w",
	"(w)(o)(w)",
};

static const size_t checksize = sizeof(checks) / sizeof(*checks);

class System_Censure : public PlayerScript
{
public:
    System_Censure() : PlayerScript("System_Censure") { }

    void CheckMessage(Player* player, std::string& msg, uint32 lang)
    {
        //if (player->isGameMaster() || lang == LANG_ADDON)
           // return;

        // remove all space characters and transform to lowercase for simpler checking
        if (sConfigMgr->GetBoolDefault("Unell.AntiAD.Enable", true))
		{
			std::string checkmsg = msg;
			checkmsg.erase(remove_if(checkmsg.begin(), checkmsg.end(), ::isspace), checkmsg.end());
			std::transform(checkmsg.begin(), checkmsg.end(), checkmsg.begin(), ::tolower);
			
			for (size_t i = 0; i < checksize; ++i)
			{
				if (checkmsg.find(checks[i]) != std::string::npos)
				{
					msg = "";				
					std::string NameLink = ChatHandler(player->GetSession()).GetNameLink(player);
					char msg[250];
					snprintf(msg, 250, "|cFFFF0000[Антиреклама]:|cff6C8CD5 Игрок %s |cff6C8CD5сказал запрещённое слово:|r %s", NameLink.c_str(), checkmsg.c_str());
					sWorld->SendGMText(LANG_GM_BROADCAST, msg);
					
					if (sConfigMgr->GetBoolDefault("Unell.AntiAD.Enable.Mute", true))
					{	
						uint32 guid = sObjectMgr->GetPlayerGUIDByName(player->GetName());
						
						if (!sConfigMgr->GetBoolDefault("Unell.AntiAD.Mute.GM", true))
						{
							if (!Unell_Script::Unell_isgm(guid))
							{
								uint32 confmute = sConfigMgr->GetIntDefault("Unell.AntiAD.Mutetime", 5);
								int64 muteTime = time(NULL) + confmute * MINUTE;
								player->GetSession()->m_muteTime = muteTime;
								ChatHandler(player->GetSession()).PSendSysMessage("|cFFFF0000[Антиреклама]:|cff6C8CD5 Ваш чат заблокирован на|r %u |cff6C8CD5минут.", confmute);
							}
						}
						
						if (sConfigMgr->GetBoolDefault("Unell.AntiAD.Mute.GM", true))
						{
							uint32 confmute = sConfigMgr->GetIntDefault("Unell.AntiAD.Mutetime", 5);
							int64 muteTime = time(NULL) + confmute * MINUTE;
							player->GetSession()->m_muteTime = muteTime;
							ChatHandler(player->GetSession()).PSendSysMessage("|cFFFF0000[Антиреклама]:|cff6C8CD5 Ваш чат заблокирован на|r %u |cff6C8CD5минут.", confmute);
						}
					}
				}
			}		
		}
    };

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg) 
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Player* /*receiver*/) 
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Group* /*group*/) 
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* /*guild*/) 
    {
        CheckMessage(player, msg, lang);
    }

    void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Channel* /*channel*/) 
    {
        CheckMessage(player, msg, lang);
    }
};

std::string GetNameLink(Player* player)
{
	std::string name = player->GetName();
	std::string color;
	switch(player->getClass()) 
	{
	case CLASS_DEATH_KNIGHT:
		color = "|cFFFF0000";
		break;
	case CLASS_DRUID:
		color = "|cFFFF0000";
		break;
	case CLASS_HUNTER:
		color = "|cFFFF0000";
		break;
	case CLASS_MAGE:
		color = "|cFFFF0000";
		break;
	case CLASS_PALADIN:
		color = "|cFFFF0000";
		break;
	case CLASS_PRIEST:
		color = "|cFFFF0000";
		break;
	case CLASS_ROGUE:
		color = "|cFFFF0000";
		break;
	case CLASS_SHAMAN:
		color = "|cFFFF0000";
		break;
	case CLASS_WARLOCK:
		color = "|cFFFF0000";
		break;
	case CLASS_WARRIOR:
		color = "|cFFFF0000";
		break;
	}
	return "|Hplayer:"+name+"|h"+color+name+"|cff6C8CD5]:|h|r";
}

class cs_world_chat : public CommandScript
{
	public:
		cs_world_chat() : CommandScript("cs_world_chat"){}

	
	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> WorldChatCommandTable =
		{
			{ "w", SEC_MODERATOR, false, &HandleWorldChatCommand, "" },
		};

		return WorldChatCommandTable;
	}

	static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
	{
		if (!handler->GetSession()->GetPlayer()->CanSpeak())
			return false;
		std::string temp = args;

		if (!args || temp.find_first_not_of(' ') == std::string::npos)
			return false;

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();

		switch(player->GetSession()->GetSecurity())
		{
			// Moderator/trial 
			case SEC_MODERATOR:
				msg += "|cff6C8CD5[Модератор ";
				msg += GetNameLink(player);
				msg += " |cff14ECCF";
				break;
			// GM
			case SEC_EVENTER:
				msg += "|cff6C8CD5[Ивент-мастер";
				msg += GetNameLink(player);
				msg += " |cff14ECCF";
				break;
			// Admin
			case SEC_GAMEMASTER:
				msg += "|cff6C8CD5[Гейм-мастер ";
				msg += GetNameLink(player);
				msg += " |cff14ECCF";
				break;
				// GM
			case SEC_ADMINISTRATOR:
				msg += "|cff6C8CD5[Администратор ";
				msg += GetNameLink(player);
				msg += " |cff14ECCF";
				break;
				// Admin
			case SEC_DEVELOPER:
				msg += "|cff6C8CD5[Разработчик ";
				msg += GetNameLink(player);
				msg += " |cff14ECCF"; 
				break;
				// Admin
			case SEC_CONSOLE:
				msg += "|cff6C8CD5[Куратор ";
				msg += GetNameLink(player);
				msg += " |cff14ECCF";
				break;
				// Игрок
			case SEC_PLAYER:
				msg += "|cff6C8CD5[Игрок ";
				msg += GetNameLink(player);
				msg += " |cff14ECCF";
				break;
		}
			
		msg += args;
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);	

		return true;
	}
};

void AddSC_Unell_Chat_System()
{
    new System_Censure();
	new cs_world_chat();
}

