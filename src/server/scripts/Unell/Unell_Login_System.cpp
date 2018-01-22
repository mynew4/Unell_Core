#include "Unell_Script.h"

/*
bool firstLogin = player->HasAtLoginFlag(AT_LOGIN_FIRST);
*/

class Unell_Login : public PlayerScript
{
public:
	Unell_Login() : PlayerScript("Unell_Login") { }	

	void OnLogin(Player* player)
	{
		ChatHandler handler(player->GetSession());
		uint32 accId, refid, playeronline, tickets, flag;
		std::string NameLink, username, os, name, uptime, player_ip, gmlvl;
		
		accId = player->GetSession()->GetAccountId();
		NameLink = ChatHandler(player->GetSession()).GetNameLink(player);
		refid = Unell_Script::Unell_refid(accId);
		username = Unell_Script::Unell_accuser(refid);
		os = Unell_Script::Unell_InfoOS(accId);
		name = player->GetName();
		playeronline = sWorld->GetPlayerCount();
		uptime = secsToTimeString(sWorld->GetUptime());
		player_ip = player->GetSession()->GetRemoteAddress();
		tickets = Unell_Script::Unell_Ticket_Open();
	    
		switch (player->GetSession()->GetSecurity())
		{
		case 0:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_0);
			break;
		case 1:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_1);
			break;
		case 2:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_2);
			break;
		case 3:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_3);
			break;
		case 4:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_4);
			break;
		case 5:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_5);
			break;
		case 6:
			gmlvl = handler.GetTrinityString(UNELL_LANG_GM_LEVEL_6);
			break;
		}
		
		QueryResult result = LoginDatabase.PQuery("SELECT flag_hello FROM unell_account_setting WHERE id = %u", accId);
		if (result)
			flag = result->Fetch()->GetUInt32();
		
		if (!result || (flag == 1))
		{
			handler.PSendSysMessage("|cffff0000##############################|r");
			handler.PSendSysMessage("|cffff0000# |cff00ff00Привет,|r %s", name.c_str());
			
			if (player->GetSession()->GetSecurity() >= SEC_MODERATOR)
				handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш уровень доступа:|r %s", gmlvl.c_str());
		
			handler.PSendSysMessage("|cffff0000# |cff00ff00Ваш IP:|r %s", player_ip.c_str());
			handler.PSendSysMessage("|cffff0000# |cff00ff00Сейчас|r %u |cff00ff00игроков онлайн|r", playeronline);
			
			if (player->GetSession()->GetSecurity() < SEC_MODERATOR)
				handler.PSendSysMessage("|cffff0000# |cff00ff00Время работы сервера:|r %s", uptime.c_str());
			
			if (player->GetSession()->GetSecurity() >= SEC_MODERATOR)
				handler.PSendSysMessage("|cffff0000# |cff00ff00Открытые тикеты:|r %u", tickets);
			
			if (os == "OSX")
				handler.PSendSysMessage("|cffff0000# |cff00ff00Сейчас вы в игре с телефона");
			
			if (sConfigMgr->GetBoolDefault("Unell.Referer.System.Enable", true))
			{
				if (refid != 1)
				{
					if (username == "Неизвестно")
						handler.PSendSysMessage("|cffff0000#|r Пожалуйста, укажите кто вас пригласил");
					else
						handler.PSendSysMessage("|cffff0000# |cff00ff00Вас пригласил|r %s", username.c_str());
				}
			}
			
			if (player->GetSession()->IsPremium())
			{
				handler.PSendSysMessage("|cffff0000#|cff00ff00 Статус премиум аккаунта:|r |cff14ECCFИмеет премиум доступ");
				QueryResult result = LoginDatabase.PQuery("SELECT unsetdate FROM account_premium WHERE id = %u", accId);
				if (result)
				{
					Field * field = result->Fetch();
					uint32 unsetdate = field[0].GetUInt32();
					std::string timeStr  = secsToTimeString(unsetdate - time(NULL), false, false);
					handler.PSendSysMessage("|cFFFF0000# |cff00ff00Премиум аккаунт закончится через|r %s", timeStr.c_str());
				}
			}
			else
				handler.PSendSysMessage("|cffff0000#|cff00ff00 Статус премиум аккаунта:|r |cff14ECCFНе имеет премиум доступа");
			
			handler.PSendSysMessage("|cffff0000# |cff00ff00Удачи и приятной игры|r");
			handler.PSendSysMessage("|cffff0000##############################|r");
		}
	}	
};

class Unell_Login_Token : public PlayerScript
{
public:
	Unell_Login_Token() : PlayerScript("Unell_Login_Token") { }	

	void OnLogin(Player* player)
	{		
		if (sConfigMgr->GetBoolDefault("Unell.Donat.Token.OnLogin", true))
		{
			if (player->GetSession()->GetSecurity() >= SEC_MODERATOR)
			{
				ChatHandler handler(player->GetSession());
				uint32 itemId = sConfigMgr->GetIntDefault("Unell.Donat.Token.OnLogin.TokenID", 0);
				uint32 countconf = sConfigMgr->GetIntDefault("Unell.Donat.Token.OnLogin.Value", 0);
				
				QueryResult result = CharacterDatabase.PQuery("SELECT owner_guid, count FROM item_instance WHERE `itemEntry` = '%u' AND `count` > '%u' ORDER BY count DESC LIMIT 100", itemId, countconf);
				if(result)
				{
					handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Проверка донат валюты у игроков");
					do
					{
						Field * fields = result->Fetch();
						uint32 owner_guid = fields[0].GetUInt32();
						uint32 count = fields[1].GetUInt32();
						QueryResult namechar = CharacterDatabase.PQuery("SELECT guid, name FROM characters WHERE guid = %u", owner_guid);
						if(namechar)
						{
							Field * fields = namechar->Fetch();
							uint32 guid = fields[0].GetUInt32();
							std::string name = fields[1].GetString();
							
							if (sConfigMgr->GetBoolDefault("Unell.Donat.Token.OnLogin.NoGM", true))
							{
								if (!Unell_Script::Unell_isgm(owner_guid))								
								handler.PSendSysMessage("|cffff0000# |cff14ECCFНик: |cffff0000%s|cff14ECCF, Количество валюты: |cffff0000%u", name.c_str(), count);
							}
							
							if (!sConfigMgr->GetBoolDefault("Unell.Donat.Token.OnLogin.NoGM", true))
								handler.PSendSysMessage("|cffff0000# |cff14ECCFНик: |cffff0000%s|cff14ECCF, Количество валюты: |cffff0000%u", name.c_str(), count);
						}					
					} 
					while(result->NextRow());
				}
				return;
			}
		
		}		
	}
};

class Unell_Login_CommandAdd : public PlayerScript
{
public:
	Unell_Login_CommandAdd() : PlayerScript("Unell_Login_CommandAdd") { }	

	void OnLogin(Player* player)
	{		
		if (sConfigMgr->GetBoolDefault("Unell.Command.Add.LoginLogs", false))
		{
			if (player->GetSession()->GetSecurity() == SEC_CONSOLE)
			{
				ChatHandler handler(player->GetSession());
				QueryResult result = CharacterDatabase.PQuery("SELECT gmplayer, count, FROM_UNIXTIME(time), targetname FROM logs_add WHERE (UNIX_TIMESTAMP() - time) < 86400 ORDER BY time DESC LIMIT 20");
				if(result) 
				{
					handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 История выдачи ивент марок за последние 24 часа.");
					do
					{
						Field * fields = result->Fetch();
						std::string gmname = fields[0].GetString();
						uint32 count = fields[1].GetUInt32();
						std::string time = fields[2].GetCString();
						std::string targetname = fields[3].GetString();
						
						handler.PSendSysMessage("|cffff0000# |cff14ECCFГМ: |cffff0000%s|cff14ECCF, Количество: |cffff0000%u|cff14ECCF, Дата: |cffff0000%s|cff14ECCF, Игроку: |cffff0000%s|cff14ECCF.", gmname.c_str(), count, time.c_str(), targetname.c_str());
					} 
					while(result->NextRow());
				}
				
				if(!result)
					handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Выдача марок за последние 24 часа не производилась.");
			}
		}		
	}
};

class Unell_Login_GM : public PlayerScript
{
public:
	Unell_Login_GM() : PlayerScript("Unell_Login_GM") {}

	void OnLogin(Player* player)
	{
		if (sConfigMgr->GetBoolDefault("Unell.Start.GM.Island", true))
		{
			if (player->GetSession()->GetSecurity() > 0 && player->GetTotalPlayedTime() < 1)
				player->TeleportTo(1,  16226.2f,  16257.0f,  13.2022f,  1.65007f); // ГМ остров
		}
	}
};

class Unell_Account_Mounts : public PlayerScript
{
    static const bool limitrace = true; // This set to true will only learn mounts from chars on the same team, do what you want.
public:
	Unell_Account_Mounts() : PlayerScript("Unell_Account_Mounts") { }

    void OnLogin(Player* player)
    {
        std::vector<uint32> Guids;
        uint32 playerGUID = player->GetGUID();
        QueryResult result1 = CharacterDatabase.PQuery("SELECT guid, race FROM characters WHERE account = %u", playerGUID);
        
		if (!result1)
            return;

        do
        {
            Field* fields = result1->Fetch();

            uint32 guid = fields[0].GetUInt32();
            uint32 race = fields[1].GetUInt8();

            if ((Player::TeamIdForRace(race) == Player::TeamIdForRace(player->getRace())) || !limitrace)
                Guids.push_back(result1->Fetch()[0].GetUInt32());

        } 
		while (result1->NextRow());

        std::vector<uint32> Spells;

        for (auto& i : Guids)
        {
            QueryResult result2 = CharacterDatabase.PQuery("SELECT spell FROM character_spell WHERE guid = %u", i);
            
			if (!result2)
                continue;

            do
            {
                Spells.push_back(result2->Fetch()[0].GetUInt32());
            } 
			while (result2->NextRow());
        }

        for (auto& i : Spells)
        {
            auto sSpell = sSpellStore.LookupEntry(i);
            if (sSpell->Effect[0] == SPELL_EFFECT_APPLY_AURA && sSpell->EffectApplyAuraName[0] == SPELL_AURA_MOUNTED)
                player->learnSpell(sSpell->Id);
        }
    }
};

void AddSC_Unell_Login_System()
{
	new Unell_Login();
	new Unell_Login_Token();
	new Unell_Login_CommandAdd();
	new Unell_Login_GM();
	new Unell_Account_Mounts();
}