/*
Field * field = resultvip->Fetch();				
uint32 menu_id = field[0].GetUInt32();
std::string text = field[1].GetString();

if (!sConfigMgr->GetBoolDefault("Unell.Top.Enable", true))

double Roll1 = rand_chance();
double Roll2 = rand_norm();
handler->PSendSysMessage("|cffff0000# |cff00ff00rand_chance: %d", Roll1);
handler->PSendSysMessage("|cffff0000# |cff00ff00rand_norm: %d", Roll2);

*/

#include "Unell_Script.h"

class Unell_commandscript : public CommandScript
{
  public:
	Unell_commandscript() : CommandScript("Unell_commandscript") {}

	std::vector<ChatCommand> GetCommands() const override
    {
		static std::vector<ChatCommand> unellCommandDeveloperNPCVendorTable = // .udev npc vendor
        {
            { "clear",         SEC_DEVELOPER,  		true, &HandleUnellOwnNPCVendorClear,			"" },
			{ "cost",          SEC_DEVELOPER,  		true, &HandleUnellOwnNPCVendorCost,				"" },
			{ "free",          SEC_DEVELOPER,  		true, &HandleUnellOwnNPCVendorFree,				"" },
			{ "addmoreitem",   SEC_DEVELOPER,  		true, &HandleUnellOwnNPCVendorAddMoreItem,		"" },
			{ "delmoreitem",   SEC_DEVELOPER,  		true, &HandleUnellOwnNPCVendorDelMoreItem,		"" }
        };
		
		static std::vector<ChatCommand> unellCommandDeveloperNPCTable = // .udev npc
        {
            { "display",       SEC_DEVELOPER,  		true, &HandleUnellOwnNPCDisplay,				"" },
			{ "vendor",		   SEC_DEVELOPER, 		true, nullptr, 									"", unellCommandDeveloperNPCVendorTable }
        };
		
		static std::vector<ChatCommand> unellCommandDeveloperTable = // .udev
        {
            { "npc",		   SEC_DEVELOPER, 		true, nullptr,									"", unellCommandDeveloperNPCTable },
			{ "displayid",     SEC_DEVELOPER, 		true, &HandleUnellDisplayID,					"" },
			{ "alldisplayid",  SEC_DEVELOPER, 		true, &HandleUnellDisplayIDAll,					"" },
			{ "moredisplay",   SEC_DEVELOPER, 		true, &HandleUnellDisplayIDMoreItem,			"" },
			{ "token",         SEC_DEVELOPER, 		true, &HandleUnellToken, 						"" },
			{ "addtokenchar",  SEC_DEVELOPER, 		true, &HandleUnellTokenAddChar, 				"" },
			{ "addtokenacc",   SEC_DEVELOPER, 		true, &HandleUnellTokenAddAcc, 					"" },			
			{ "test",          SEC_DEVELOPER, 		true, &HandleUnellTest,							"" },
			{ "info",          SEC_DEVELOPER, 		true, &HandleUnellDeveloperInfo,				"" },
			{ "online",	   	   SEC_DEVELOPER,  		true, &HandleUnellOnline, 						"" }
        };
		
		static std::vector<ChatCommand> unellCommandTable = // .upl
        {
            { "ilvl",          SEC_PLAYER,  		true, &HandleUnellItemLevel,					"" },
			{ "buff",          SEC_DEVELOPER,  		true, &HandleBuffCommand,						"" },
			{ "buffvor",       SEC_DEVELOPER,  		true, &HandleBuffCommandVor,					"" },
			{ "home",          SEC_DEVELOPER,  		true, &HandleUnellHome,							"" },			
			{ "info",          SEC_PLAYER,  		true, &HandleUnellInfo,							"" },
			{ "heal",          SEC_DEVELOPER,  		true, &HandleUnellHeal, 						"" },
			{ "timeap",		   SEC_PLAYER,  		true, &HandleUnellTimeAP, 						"" },
			{ "viptime",	   SEC_PLAYER,  		true, &HandleUnellTimeVIP, 						"" },
			// { "loot",		   SEC_DEVELOPER,  		true, &HandleUnellNpcLoot, 						"" }, // Нужно доделать под азерот
			{ "toptime",	   SEC_DEVELOPER,  		true, &HandleUnellTopTime, 						"" }
        };
		
		static std::vector<ChatCommand> unellCommandGMTable = // .ugm
        {
			{ "add",           SEC_GAMEMASTER,  	true, &HandleUnellAdd, 							"" }
        };

		static std::vector<ChatCommand> unellCommandInfoTable = // .uinfo
		{
			{ "player",         SEC_MODERATOR,  	true, &HandleUnellInfoPlayer, 					"" },
			{ "account",        SEC_MODERATOR,  	true, &HandleUnellInfoAccount, 					"" },
			{ "guild",          SEC_MODERATOR,  	true, &HandleUnellInfoGuild, 					"" }
		};

		static std::vector<ChatCommand> unellCommandLookUPTable = // .ulook
		{
			{ "guild",          SEC_MODERATOR,      true,  &HandleLookupGuildCommand,				"" }
		};

        static std::vector<ChatCommand> commandTable = // Команды с нуля
        {
			{ "uplayer",		SEC_PLAYER,       	true, nullptr,             	    				"", unellCommandTable },
			{ "uinfo",			SEC_MODERATOR,     	true, nullptr,             	    				"", unellCommandInfoTable },
			{ "ulook",			SEC_MODERATOR,     	true, nullptr,             	    				"", unellCommandLookUPTable },
			{ "ugm",			SEC_GAMEMASTER,    	true, nullptr,             	   					"", unellCommandGMTable },
			{ "udev",			SEC_DEVELOPER, 		true, nullptr,             	   					"", unellCommandDeveloperTable }	
        };
		
        return commandTable;
    }

	static bool HandleUnellTest(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();
		return true;
	}

	static bool HandleLookupGuildCommand(ChatHandler *handler, char const *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00Укажите значение поиска в ковычках");
			handler->SetSentErrorMessage(true);
			return false;
		}

		char *guildStr = handler->extractQuotedArg((char *)args);
		if (!guildStr)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00Неверно указано значение поиска");
			handler->SetSentErrorMessage(true);
			return false;
		}

		std::string guildName = guildStr;
		uint32 step = 1;
		uint32 maxResults = sWorld->getIntConfig(CONFIG_MAX_RESULTS_LOOKUP_COMMANDS);

		QueryResult result_info_guild = CharacterDatabase.PQuery("SELECT guildid, name FROM `guild` WHERE `name` LIKE '%%%s%%'", guildName.c_str());
		if (!result_info_guild)
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00По запросу|r %s |cff00ff00ничего не найдено", guildName.c_str());
		else
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00Найденная информация по запросу %s", guildName.c_str());
			do
			{
				if (step == maxResults)
				{
					handler->PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
					return true;
				}

				Field *fields = result_info_guild->Fetch();
				uint32 id_guild = fields[0].GetUInt32();
				std::string name_guild = fields[1].GetString();

				handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00%u|r |cff6C8CD5- Номер:|r %u|cff6C8CD5. Название:|r %s ", step, id_guild, name_guild.c_str());
				++step;
			} while (result_info_guild->NextRow());

			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00По запросу|r %s |cff00ff00найдено:|r %u |cff00ff00гильдий", guildName.c_str(), step - 1);
		}

		return true;
	}

	static bool HandleUnellInfoGuild(ChatHandler *handler, const char *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00Укажите номер гильдии");
			handler->SetSentErrorMessage(true);
			return false;
		}

		Player *player = handler->GetSession()->GetPlayer();
		uint32 guildid = (uint32)atoi((char *)args);
		uint32 accid = player->GetSession()->GetAccountId();
		std::string os = Unell_Script::Unell_InfoOS(accid);

		std::string name, info, motd, createdate, leagername;
		uint32 level_guild;
		uint64 leaderguid, BankMoney;

		QueryResult result_unell_info_guild = CharacterDatabase.PQuery("SELECT name, leaderguid, info, motd, FROM_UNIXTIME(createdate), BankMoney FROM `guild` WHERE guildid = %u;", guildid);
		if (!result_unell_info_guild)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Гильдии с таким номером не существует");
			handler->SetSentErrorMessage(true);
			return false;
		}
		else
		{
			Field *fields = result_unell_info_guild->Fetch();
			name = fields[0].GetString();
			leaderguid = fields[1].GetUInt64();
			info = fields[2].GetString();
			motd = fields[3].GetString();
			createdate = fields[4].GetString();
			BankMoney = fields[5].GetUInt64();
		}

		QueryResult result_guild_level = CharacterDatabase.PQuery("SELECT level FROM `guild_level` WHERE guild = %u", guildid);
		if (!result_guild_level)
			level_guild = 1;
		else
			level_guild = result_guild_level->Fetch()->GetUInt32();

		leagername = Unell_Script::UnellCharNameByGuid(leaderguid);

		uint32 gold = BankMoney / GOLD;
		uint32 silv = (BankMoney % GOLD) / SILVER;
		uint32 copp = (BankMoney % GOLD) % SILVER;

		if (info.empty())
			info = "-";

		if (motd.empty())
			motd = "-";

		// Вывод информации
		// Название и номер
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Информация о гильдии|r %s |cff6C8CD5(Номер гильдии:|r |cff14ECCF%u|r|cff6C8CD5)|r", name.c_str(), guildid);

		// Название и номер
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Уровень гильдии:|r %u|r", level_guild);

		// Лидер
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Лидер гильдии:|r %s|r", leagername.c_str());

		// Информация
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Информация:|r %s|r", info.c_str());

		// Сообщение дня гильдии
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Сообщение дня:|r %s|r", motd.c_str());

		// Дата создания
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Дата создания:|r %s|r", createdate.c_str());

		// Информация о золоте
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Золото:|r %u|TInterface\\MoneyFrame\\UI-GoldIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-SilverIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-CopperIcon:0:0:2:0|t", gold, silv, copp);

		QueryResult result_top_donat_exp = CharacterDatabase.PQuery("SELECT name, exp_point FROM guild_level_invested WHERE exp_point > 0 AND guild = %u ORDER BY exp_point DESC LIMIT 15", guildid);
		if (!result_top_donat_exp)
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Ещё никто не вкладывал опыт в эту гильдию");
		else
		{
			uint8 step = 1;
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Топ вложивших опыта в гильдию");

			do
			{
				Field *fields = result_top_donat_exp->Fetch();
				std::string name_char = fields[0].GetString();
				uint32 exp_point = fields[1].GetUInt32();

				handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00%u.|r %s |cff6C8CD5вложил|r %u |cff6C8CD5очков опыта|r", step, name_char.c_str(), exp_point);
				++step;
			} while (result_top_donat_exp->NextRow());
		}

		return true;
	}

	static bool HandleUnellInfoAccount(ChatHandler *handler, const char *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00Укажите название аккаунта");
			handler->SetSentErrorMessage(true);
			return false;
		}

		char *account = strtok((char *)args, " ");
		if (!account)
			return false;

		std::string accountName = account;
		if (!AccountMgr::normalizeString(accountName))
		{
			handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 accId = AccountMgr::GetId(accountName);
		if (!accId)
		{
			handler->PSendSysMessage(LANG_ACCOUNT_NOT_EXIST, accountName.c_str());
			handler->SetSentErrorMessage(true);
			return false;
		}

		Player *player = handler->GetSession()->GetPlayer();

		// Переменные
		uint32 security = 0;
		std::string localhost = "127.0.0.1";
		std::string last_ip, last_attempt_ip, joindate, last_login, username, email, gmlvlstr, Realmname, Realmname_1, Realmname_2, Realmname_3;
		uint32 online;

		QueryResult result_unell_info_acc = LoginDatabase.PQuery("SELECT username, last_ip, last_attempt_ip, joindate, last_login, online, email FROM `account` WHERE id = %u", accId);
		if (!result_unell_info_acc)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00Невозможно найти информацию об аккаунте:|r %s", accountName.c_str());
			handler->SetSentErrorMessage(true);
			return false;
		}
		else
		{

			Field *fields = result_unell_info_acc->Fetch();
			username = fields[0].GetString();
			last_ip = fields[1].GetString();
			last_attempt_ip = fields[2].GetString();
			joindate = fields[3].GetString();
			last_login = fields[4].GetString();
			online = fields[5].GetUInt32();
			email = fields[6].GetString();
		}

		if (email.empty())
			email = "-";

		QueryResult result_acc_security = LoginDatabase.PQuery("SELECT gmlevel FROM `account_access` WHERE id = %u", accId);
		if (!result_acc_security)
			security = 0;
		else
			security = result_acc_security->Fetch()->GetUInt32();

		switch (security)
		{
		case 0:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_0);
			break;
		case 1:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_1);
			break;
		case 2:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_2);
			break;
		case 3:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_3);
			break;
		case 4:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_4);
			break;
		case 5:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_5);
			break;
		case 6:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_6);
			break;
		}

		QueryResult result_realm_1 = LoginDatabase.PQuery("SELECT name FROM realmlist WHERE id = 1");
		if (!result_realm_1)
			Realmname_1 = "Неизвестный мир";
		else
			Realmname_1 = result_realm_1->Fetch()->GetString();

		QueryResult result_realm_2 = LoginDatabase.PQuery("SELECT name FROM realmlist WHERE id = 2");
		if (!result_realm_2)
			Realmname_2 = "Неизвестный мир";
		else
			Realmname_2 = result_realm_2->Fetch()->GetString();

		QueryResult result_realm_3 = LoginDatabase.PQuery("SELECT name FROM realmlist WHERE id = 3");
		if (!result_realm_3)
			Realmname_3 = "Неизвестный мир";
		else
			Realmname_3 = result_realm_3->Fetch()->GetString();

		switch (online)
		{
		case 1:
			Realmname = Realmname_1;
			break;
		case 2:
			Realmname = Realmname_2;
			break;
		case 4:
			Realmname = Realmname_3;
			break;
		}

		// Полнвый вывод всего
		// Вывод инфы об аккаунте
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Информация об аккаунте|r %s |cff6C8CD5(Номер аккаунта:|r |cff14ECCF%u|r|cff6C8CD5)|r", username.c_str(), accId);

		// Инфо о мыле
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Email:|r %s", email.c_str());

		// Инфо о доступе
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Уровень доступа:|r %u |cff6C8CD5-|r %s", security, gmlvlstr.c_str());

		// Инфо о ласт айпи
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Последний айпи:|r %s", last_ip.c_str());

		// Инфо о пред ласт айпи
		if (last_attempt_ip != localhost)
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Предпоследний айпи:|r %s", last_attempt_ip.c_str());

		// Инфо о ласт айпи
		if (online == 0)
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Последний вход:|r %s", last_login.c_str());

		// Регистрация аккаунта
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Аккаунт создан:|r %s", joindate.c_str());

		// Онлайн на игровом мире
		if (online > 0)
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Онлайн на игровом мире:|r %s", Realmname.c_str());

		// Информация о VIP акке
		QueryResult result_vip = LoginDatabase.PQuery("SELECT unsetdate FROM account_premium WHERE id = %u", accId);
		if (!result_vip)
		{
			handler->PSendSysMessage("|cffff0000# |cff6C8CD5Статус VIP аккаунта:|r |cff14ECCFНе имеет VIP");
		}
		else
		{
			handler->PSendSysMessage("|cffff0000# |cff6C8CD5Статус VIP аккаунта:|r |cff14ECCFИмеет VIP");
			Field *field = result_vip->Fetch();
			uint32 unsetdate = field[0].GetUInt32();
			std::string timeStr = secsToTimeString(unsetdate - time(NULL), false, false);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Премиум аккаунт закончится через: |cff14ECCF%s", timeStr.c_str());
		}

		return true;
	}

	static bool HandleUnellInfoPlayer(ChatHandler *handler, const char *args)
	{
		Player *target;
		uint64 targetGuid;
		std::string targetName;

		Player *player = handler->GetSession()->GetPlayer();

		uint32 parseGUID = MAKE_NEW_GUID(atol((char *)args), 0, HIGHGUID_PLAYER);

		if (sObjectMgr->GetPlayerNameByGUID(parseGUID, targetName))
		{
			target = ObjectAccessor::FindPlayerInOrOutOfWorld(MAKE_NEW_GUID(parseGUID, 0, HIGHGUID_PLAYER));
			targetGuid = parseGUID;
		}
		else if (!handler->extractPlayerTarget((char *)args, &target, &targetGuid, &targetName))
			return false;

		uint32 accId = 0;
		uint32 money = 0;
		uint32 totalPlayerTime = 0;
		uint8 level = 0;
		uint32 latency = 0;
		uint8 race;
		uint8 Class;
		int64 muteTime = 0;
		int64 banTime = -1;
		uint32 mapId;
		uint32 areaId;
		uint32 phase = 0;

		std::string guildName = "";
		bool guildIsLeader = false;
		uint64 guildMoney = 0;
		uint32 guildMemberCount = 0;
		uint32 guildID = 0;
		if (const GlobalPlayerData *gpd = sWorld->GetGlobalPlayerData(targetGuid))
			if (gpd->guildId)
				if (Guild *targetGuild = sGuildMgr->GetGuildById(gpd->guildId))
				{
					guildName = targetGuild->GetName();
					guildID = targetGuild->GetId();
					guildMoney = targetGuild->GetTotalBankMoney();
					guildMemberCount = targetGuild->GetMemberCount();
					if (targetGuild->GetLeaderGUID() == targetGuid)
						guildIsLeader = true;
				}

		// get additional information from Player object
		if (target)
		{
			accId = target->GetSession()->GetAccountId();
			money = target->GetMoney();
			totalPlayerTime = target->GetTotalPlayedTime();
			level = target->getLevel();
			latency = target->GetSession()->GetLatency();
			race = target->getRace();
			Class = target->getClass();
			muteTime = target->GetSession()->m_muteTime;
			mapId = target->GetMapId();
			areaId = target->GetAreaId();
			phase = target->GetPhaseMask();
		}
		else
		{
			PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PINFO);
			stmt->setUInt32(0, GUID_LOPART(targetGuid));
			PreparedQueryResult result = CharacterDatabase.Query(stmt);

			if (!result)
				return false;

			Field *fields = result->Fetch();
			totalPlayerTime = fields[0].GetUInt32();
			level = fields[1].GetUInt8();
			money = fields[2].GetUInt32();
			accId = fields[3].GetUInt32();
			race = fields[4].GetUInt8();
			Class = fields[5].GetUInt8();
			mapId = fields[6].GetUInt16();
			areaId = fields[7].GetUInt16();
		}

		std::string userName = handler->GetTrinityString(LANG_ERROR);
		std::string eMail = handler->GetTrinityString(LANG_ERROR);
		std::string muteReason = "";
		std::string muteBy = "";
		std::string lastIp = handler->GetTrinityString(LANG_ERROR);
		uint32 security = 0;
		std::string lastLogin = handler->GetTrinityString(LANG_ERROR);

		PreparedStatement *stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_PINFO);
		stmt->setInt32(0, int32(realmID));
		stmt->setUInt32(1, accId);
		PreparedQueryResult result = LoginDatabase.Query(stmt);

		if (result)
		{
			Field *fields = result->Fetch();
			userName = fields[0].GetString();
			security = fields[1].GetUInt8();
			eMail = fields[2].GetString();
			muteTime = fields[5].GetUInt64();
			muteReason = fields[6].GetString();
			muteBy = fields[7].GetString();

			if (eMail.empty())
				eMail = "-";

			if (!handler->GetSession() || handler->GetSession()->GetSecurity() >= AccountTypes(security))
			{
				lastIp = fields[3].GetString();
				lastLogin = fields[4].GetString();

				uint32 ip = inet_addr(lastIp.c_str());

				PreparedStatement *stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_IP2NATION_COUNTRY);

				stmt->setUInt32(0, ip);

				PreparedQueryResult result2 = LoginDatabase.Query(stmt);

				if (result2)
				{
					Field *fields2 = result2->Fetch();
					lastIp.append(" (");
					lastIp.append(fields2[0].GetString());
					lastIp.append(")");
				}
			}
			else
			{
				lastIp = "-";
				lastLogin = "-";
			}
		}

		std::string nameLink = handler->playerLink(targetName);
		std::string gmlvlstr;

		switch (security)
		{
		case 0:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_0);
			break;
		case 1:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_1);
			break;
		case 2:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_2);
			break;
		case 3:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_3);
			break;
		case 4:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_4);
			break;
		case 5:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_5);
			break;
		case 6:
			gmlvlstr = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_6);
			break;
		}

		std::string bannedby = "Консоль";
		std::string banreason = "";

		stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_PINFO_BANS);
		stmt->setUInt32(0, accId);
		PreparedQueryResult result2 = LoginDatabase.Query(stmt);
		if (!result2)
		{
			stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_PINFO_BANS);
			stmt->setUInt32(0, GUID_LOPART(targetGuid));
			result2 = CharacterDatabase.Query(stmt);
		}

		if (result2)
		{
			Field *fields = result2->Fetch();
			banTime = int64(fields[1].GetUInt64() ? 0 : fields[0].GetUInt32());
			bannedby = fields[2].GetString();
			banreason = fields[3].GetString();
		}

		std::string raceStr, ClassStr;
		switch (race)
		{
		case RACE_HUMAN:
			raceStr = "Человек";
			break;
		case RACE_ORC:
			raceStr = "Орк";
			break;
		case RACE_DWARF:
			raceStr = "Дворф";
			break;
		case RACE_NIGHTELF:
			raceStr = "Ночной эльф";
			break;
		case RACE_UNDEAD_PLAYER:
			raceStr = "Нежить";
			break;
		case RACE_TAUREN:
			raceStr = "Таурен";
			break;
		case RACE_GNOME:
			raceStr = "Гном";
			break;
		case RACE_TROLL:
			raceStr = "Тролль";
			break;
		case RACE_BLOODELF:
			raceStr = "Эльф крови";
			break;
		case RACE_DRAENEI:
			raceStr = "Дреней";
			break;
		}

		switch (Class)
		{
		case CLASS_WARRIOR:
			ClassStr = "Воин";
			break;
		case CLASS_PALADIN:
			ClassStr = "Паладин";
			break;
		case CLASS_HUNTER:
			ClassStr = "Охотник";
			break;
		case CLASS_ROGUE:
			ClassStr = "Разбойник";
			break;
		case CLASS_PRIEST:
			ClassStr = "Жрец";
			break;
		case CLASS_DEATH_KNIGHT:
			ClassStr = "Рыцарь Смерти";
			break;
		case CLASS_SHAMAN:
			ClassStr = "Шаман";
			break;
		case CLASS_MAGE:
			ClassStr = "Маг";
			break;
		case CLASS_WARLOCK:
			ClassStr = "Чернокнижник";
			break;
		case CLASS_DRUID:
			ClassStr = "Друид";
			break;
		}

		std::string timeStr = secsToTimeString(totalPlayerTime, false, false);
		uint32 gold = money / GOLD;
		uint32 silv = (money % GOLD) / SILVER;
		uint32 copp = (money % GOLD) % SILVER;

		// Add map, zone, subzone and phase to output
		int locale = handler->GetSessionDbcLocale();
		std::string areaName = "<неизвестно>";
		std::string zoneName = "";

		MapEntry const *map = sMapStore.LookupEntry(mapId);

		AreaTableEntry const *area = sAreaTableStore.LookupEntry(areaId);
		if (area)
		{
			areaName = area->area_name[locale];

			AreaTableEntry const *zone = sAreaTableStore.LookupEntry(area->zone);
			if (zone)
				zoneName = zone->area_name[locale];
		}

		uint32 itemid = 120000;
		std::string item_cron = Unell_Script::GetItemLink(player, itemid);

		uint32 accId_self = player->GetSession()->GetAccountId();
		std::string OS_Self = Unell_Script::Unell_InfoOS(accId_self);

		// Полнвый вывод всего
		// Вывод информации о игроке
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Информация о|r%s %s |cff6C8CD5(Номер игрока:|r |cff14ECCF%u|r|cff6C8CD5)|r", (target ? "" : handler->GetTrinityString(LANG_OFFLINE)), nameLink.c_str(), GUID_LOPART(targetGuid));

		// Инфо о акке
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Аккаунт:|r %s |cff6C8CD5(Номер аккаунта:|r |cff14ECCF%u|r|cff6C8CD5)|r", userName.c_str(), accId);

		// Инфо о муте
		if (muteTime > 0 && muteTime > time(nullptr))
			handler->PSendSysMessage(LANG_PINFO_MUTE, secsToTimeString(muteTime - time(nullptr), true).c_str(), muteBy.c_str(), muteReason.c_str());

		// Инфо о бане
		if (banTime >= 0)
			handler->PSendSysMessage(LANG_PINFO_BAN, banTime > 0 ? secsToTimeString(banTime - time(nullptr), true).c_str() : "навсегда", bannedby.c_str(), banreason.c_str());

		// Инфо о мыле
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Email:|r %s", eMail.c_str());

		// Инфо о доступе
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Уровень доступа:|r %u |cff6C8CD5-|r %s", security, gmlvlstr.c_str());

		// Инфо о ласт айпи
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Последний айпи:|r %s", lastIp.c_str());

		// Инфо о ласт входе (если не онлайн)
		if (!target)
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Последний вход в игру:|r %s", lastLogin.c_str());

		// Инфо о рассе и классе
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Расса:|r %s|cff6C8CD5, Класс:|r %s", raceStr.c_str(), ClassStr.c_str());

		// Информация о игровом времени
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Игровое время:|r %s", timeStr.c_str());

		// Информация о уровне
		handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Уровень:|r %u", level);

		// Информация о золоте
		if (OS_Self == "OSX")
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Деньги:|r %uг %uс %uм", gold, silv, copp);
		else
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Деньги:|r %u|TInterface\\MoneyFrame\\UI-GoldIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-SilverIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-CopperIcon:0:0:2:0|t", gold, silv, copp);

		// Инфо о местонахождении
		if (target)
		{
			if (!zoneName.empty())
				handler->PSendSysMessage(LANG_PINFO_MAP_ONLINE, map->name[locale], zoneName.c_str(), areaName.c_str(), phase);
			else
				handler->PSendSysMessage(LANG_PINFO_MAP_ONLINE, map->name[locale], areaName.c_str(), "<неизвестно>", phase);
		}
		else
			handler->PSendSysMessage(LANG_PINFO_MAP_OFFLINE, map->name[locale], areaName.c_str());

		// Инфо о задерке, если онлайн
		if (target)
			handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Задержка:|r %u", latency);

		// Информация о VIP акке
		QueryResult result_vip = LoginDatabase.PQuery("SELECT unsetdate FROM account_premium WHERE id = %u", accId);
		if (!result_vip)
		{
			handler->PSendSysMessage("|cffff0000# |cff6C8CD5Статус VIP:|r |cff14ECCFНе имеет VIP");
		}
		else
		{
			handler->PSendSysMessage("|cffff0000# |cff6C8CD5Статус VIP:|r |cff14ECCFИмеет VIP");
			Field *field = result_vip->Fetch();
			uint32 unsetdate = field[0].GetUInt32();
			std::string timeStr = secsToTimeString(unsetdate - time(NULL), false, false);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Премиум аккаунт закончится через: |cff14ECCF%s", timeStr.c_str());
		}

		// Информация о кронах
		QueryResult result_cron = CharacterDatabase.PQuery("SELECT count FROM `item_instance` WHERE `itemEntry` = '120000' AND owner_guid = %u LIMIT 0, 10", GUID_LOPART(targetGuid));
		if (!result_cron)
			handler->PSendSysMessage("|cFFFF0000#|r %s |cff6C8CD5-|r 0", item_cron.c_str());
		else
		{
			uint32 full_count = 0;
			uint32 count_cron_db;

			do
			{
				count_cron_db = result_cron->Fetch()->GetUInt32();
				full_count += count_cron_db;
			} while (result_cron->NextRow());

			handler->PSendSysMessage("|cFFFF0000#|r %s |cff6C8CD5-|r %u", item_cron.c_str(), full_count);
		}

		// Инфо о гильдии
		if (!guildName.empty())
		{
			uint32 gold_guild = guildMoney / GOLD;
			uint32 silv_guild = (guildMoney % GOLD) / SILVER;
			uint32 copp_guild = (guildMoney % GOLD) % SILVER;
			if (OS_Self == "OSX")
				handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Гильдия:|r %s |cff6C8CD5(Номер гильдии:|r |cff14ECCF%u|r|cff6C8CD5)|r|cff6C8CD5, Участников:|r %u|cff6C8CD5, Деньги гильдии:|r %uг %uс %uм|cff6C8CD5, Ги лидер:|r %s", guildName.c_str(), guildID, guildMemberCount, gold_guild, silv_guild, copp_guild, guildIsLeader ? "да" : "нет");
			else
				handler->PSendSysMessage("|cFFFF0000#|r |cff6C8CD5Гильдия:|r %s |cff6C8CD5(Номер гильдии:|r |cff14ECCF%u|r|cff6C8CD5)|r|cff6C8CD5, Участников:|r %u|cff6C8CD5, Деньги гильдии:|r %u|TInterface\\MoneyFrame\\UI-GoldIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-SilverIcon:0:0:2:0|t %u|TInterface\\MoneyFrame\\UI-CopperIcon:0:0:2:0|t|cff6C8CD5, Ги лидер:|r %s", guildName.c_str(), guildID, guildMemberCount, gold_guild, silv_guild, copp_guild, guildIsLeader ? "да" : "нет");
		}

		return true;
	}

	static bool HandleUnellOnline(ChatHandler *handler, const char * /*args*/)
	{
		Player *player = handler->GetSession()->GetPlayer(); // ORDER BY count DESC LIMIT 50
		uint32 accid = player->GetSession()->GetAccountId();
		std::string name, raceStr, ClassStr, Realmname;
		uint32 race, Class_uint, level, flag_online_race, flag_online_class, flag_online_level, playeronline, realmID, maxonline;
		uint8 step = 1;
		maxonline = sConfigMgr->GetIntDefault("Unell.Online.Max", 20);

		playeronline = sWorld->GetPlayerCount();
		realmID = sConfigMgr->GetIntDefault("RealmID", 0);

		QueryResult result_realm = LoginDatabase.PQuery("SELECT name FROM realmlist WHERE id = '%u'", realmID);
		if (!result_realm)
			Realmname = "...";
		else
			Realmname = result_realm->Fetch()->GetString();

		QueryResult result = CharacterDatabase.PQuery("SELECT name, race, class, level FROM characters WHERE online > 0 ORDER BY name DESC LIMIT %u", maxonline);
		if (!result)
		{
			handler->PSendSysMessage("|cFFFF0000#|r |cff00ff00На игровом мире:|r %s |cff00ff00нет персонажей онлайн.|r", Realmname.c_str());
			handler->SetSentErrorMessage(true);
			return false;
		}
		else
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Игровой мир:|r %s|cff00ff00,|r %u |cff00ff00персонажей онлайн", Realmname.c_str(), playeronline);
			QueryResult resflags = LoginDatabase.PQuery("SELECT flag_online_race, flag_online_class, flag_online_level FROM unell_account_setting WHERE id = %u", accid);
			if (resflags)
			{
				Field *fields = resflags->Fetch();
				flag_online_race = fields[0].GetUInt32();
				flag_online_class = fields[1].GetUInt32();
				flag_online_level = fields[2].GetUInt32();
			}
			else
			{
				flag_online_race = 1;
				flag_online_class = 1;
				flag_online_level = 1;
			}

			do
			{
				Field *field = result->Fetch();
				name = field[0].GetString();
				race = field[1].GetUInt32();
				Class_uint = field[2].GetUInt32();
				level = field[3].GetUInt32();

				switch (race)
				{
				case RACE_HUMAN:
					if (flag_online_race == 1)
						raceStr = "Человек";
					else
						raceStr = "";
					break;
				case RACE_ORC:
					if (flag_online_race == 1)
						raceStr = "Орк";
					else
						raceStr = "";
					break;
				case RACE_DWARF:
					if (flag_online_race == 1)
						raceStr = "Дворф";
					else
						raceStr = "";
					break;
				case RACE_NIGHTELF:
					if (flag_online_race == 1)
						raceStr = "Ночной эльф";
					else
						raceStr = "";
					break;
				case RACE_UNDEAD_PLAYER:
					if (flag_online_race == 1)
						raceStr = "Нежить";
					else
						raceStr = "";
					break;
				case RACE_TAUREN:
					if (flag_online_race == 1)
						raceStr = "Таурен";
					else
						raceStr = "";
					break;
				case RACE_GNOME:
					if (flag_online_race == 1)
						raceStr = "Гном";
					else
						raceStr = "";
					break;
				case RACE_TROLL:
					if (flag_online_race == 1)
						raceStr = "Тролль";
					else
						raceStr = "";
					break;
				case RACE_BLOODELF:
					if (flag_online_race == 1)
						raceStr = "Эльф крови";
					else
						raceStr = "";
					break;
				case RACE_DRAENEI:
					if (flag_online_race == 1)
						raceStr = "Дреней";
					else
						raceStr = "";
					break;
				}

				switch (Class_uint)
				{
				case CLASS_WARRIOR:
					if (flag_online_class == 1)
						ClassStr = "Воин";
					else
						ClassStr = "";
					break;
				case CLASS_PALADIN:
					if (flag_online_class == 1)
						ClassStr = "Паладин";
					else
						ClassStr = "";
					break;
				case CLASS_HUNTER:
					if (flag_online_class == 1)
						ClassStr = "Охотник";
					else
						ClassStr = "";
					break;
				case CLASS_ROGUE:
					if (flag_online_class == 1)
						ClassStr = "Разбойник";
					else
						ClassStr = "";
					break;
				case CLASS_PRIEST:
					if (flag_online_class == 1)
						ClassStr = "Жрец";
					else
						ClassStr = "";
					break;
				case CLASS_DEATH_KNIGHT:
					if (flag_online_class == 1)
						ClassStr = "Рыцарь смерти";
					else
						ClassStr = "";
					break;
				case CLASS_SHAMAN:
					if (flag_online_class == 1)
						ClassStr = "Шаман";
					else
						ClassStr = "";
					break;
				case CLASS_MAGE:
					if (flag_online_class == 1)
						ClassStr = "Маг";
					else
						ClassStr = "";
					break;
				case CLASS_WARLOCK:
					if (flag_online_class == 1)
						ClassStr = "Чернокнижник";
					else
						ClassStr = "";
					break;
				case CLASS_DRUID:
					if (flag_online_class == 1)
						ClassStr = "Друид";
					else
						ClassStr = "";
					break;
				}

				if (flag_online_level == 1)
					handler->PSendSysMessage("|cffff0000#|r |cff00ff00%u.|r %s, %s %s %u-го уровня", step, name.c_str(), raceStr.c_str(), ClassStr.c_str(), level);
				else
					handler->PSendSysMessage("|cffff0000#|r |cff00ff00%u.|r %s, %s %s", step, name.c_str(), raceStr.c_str(), ClassStr.c_str());

				++step;
			} while (result->NextRow());
		}

		return true;
	}

	static bool HandleUnellDeveloperInfo(ChatHandler *handler, const char *args)
	{
		Player *player;
		uint64 playerGuid;
		std::string playerName, raceStr, ClassStr, nameLink;
		uint32 guid;
		uint8 race, Class, level;

		uint32 parseGUID = MAKE_NEW_GUID(atol((char *)args), 0, HIGHGUID_PLAYER);

		if (sObjectMgr->GetPlayerNameByGUID(parseGUID, playerName))
		{
			player = ObjectAccessor::FindPlayerInOrOutOfWorld(MAKE_NEW_GUID(parseGUID, 0, HIGHGUID_PLAYER));
			playerGuid = parseGUID;
		}
		else if (!handler->extractPlayerTarget((char *)args, &player, &playerGuid, &playerName))
			return false;

		guid = GUID_LOPART(playerGuid);

		PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHAR_PINFO);
		stmt->setUInt32(0, guid);
		PreparedQueryResult result_char = CharacterDatabase.Query(stmt);

		if (!result_char)
			return false;

		Field *fields = result_char->Fetch();
		level = fields[1].GetUInt8();
		race = fields[4].GetUInt8();
		Class = fields[5].GetUInt8();

		switch (race)
		{
		case RACE_HUMAN:
			raceStr = "Человек";
			break;
		case RACE_ORC:
			raceStr = "Орк";
			break;
		case RACE_DWARF:
			raceStr = "Дворф";
			break;
		case RACE_NIGHTELF:
			raceStr = "Ночной эльф";
			break;
		case RACE_UNDEAD_PLAYER:
			raceStr = "Нежить";
			break;
		case RACE_TAUREN:
			raceStr = "Таурен";
			break;
		case RACE_GNOME:
			raceStr = "Гном";
			break;
		case RACE_TROLL:
			raceStr = "Тролль";
			break;
		case RACE_BLOODELF:
			raceStr = "Эльф крови";
			break;
		case RACE_DRAENEI:
			raceStr = "Дреней";
			break;
		}

		uint32 maxhealth, maxpower1, maxpower2, maxpower3, maxpower4, maxpower5, maxpower6, maxpower7, strength, agility, stamina, intellect, spirit, armor, resHoly, resFire, resNature, resFrost, resShadow, resArcane;
		float blockPct, dodgePct, parryPct, critPct, rangedCritPct, spellCritPct, min_damage, max_damage, min_r_damage, max_r_damage;
		uint32 attackPower, rangedAttackPower, spellPower, resilience, base_attack_time, base_attack_time_r;
		uint32 Power, curr_min_damage, curr_max_damage, curr_min_damage_range, curr_max_damage_range;
		std::string PowerStr;

		nameLink = handler->playerLink(playerName);

		// 															0		  1          2			3		   4          5          6         7         8          9        10        11       12      13      14       15        16        17         18         19        20        21        22        23         24     	     25            26             27              28          29          30		  31            32            33             34                 35
		QueryResult result2 = CharacterDatabase.PQuery("SELECT maxhealth, maxpower1, maxpower2, maxpower3, maxpower4, maxpower5, maxpower6, maxpower7, strength, agility, stamina, intellect, spirit, armor, resHoly, resFire, resNature, resFrost, resShadow, resArcane, blockPct, dodgePct, parryPct, critPct, rangedCritPct, spellCritPct, attackPower, rangedAttackPower, spellPower, resilience, min_damage, max_damage, min_r_damage, max_r_damage, base_attack_time, base_attack_time_r FROM `character_stats` WHERE `guid` = '%u'", guid);
		if (!result2)
		{
			handler->PSendSysMessage("|cFFFF0000#|r Характеристики для персонажа %s ещё не сохранены.", nameLink.c_str());
			handler->SetSentErrorMessage(true);
			return false;
		}
		else
		{
			Field *field = result2->Fetch();
			maxhealth = field[0].GetUInt32();
			maxpower1 = field[1].GetUInt32();
			maxpower2 = field[2].GetUInt32();
			maxpower3 = field[3].GetUInt32();
			maxpower4 = field[4].GetUInt32();
			maxpower5 = field[5].GetUInt32();
			maxpower6 = field[6].GetUInt32();
			maxpower7 = field[7].GetUInt32();
			strength = field[8].GetUInt32();
			agility = field[9].GetUInt32();
			stamina = field[10].GetUInt32();
			intellect = field[11].GetUInt32();
			spirit = field[12].GetUInt32();
			armor = field[13].GetUInt32();
			resHoly = field[14].GetUInt32();
			resFire = field[15].GetUInt32();
			resNature = field[16].GetUInt32();
			resFrost = field[17].GetUInt32();
			resShadow = field[18].GetUInt32();
			resArcane = field[19].GetUInt32();
			blockPct = field[20].GetFloat();
			dodgePct = field[21].GetFloat();
			parryPct = field[22].GetFloat();
			critPct = field[23].GetFloat();
			rangedCritPct = field[24].GetFloat();
			spellCritPct = field[25].GetFloat();
			attackPower = field[26].GetUInt32();
			rangedAttackPower = field[27].GetUInt32();
			spellPower = field[28].GetUInt32();
			resilience = field[29].GetUInt32();
			min_damage = field[30].GetFloat();
			max_damage = field[31].GetFloat();
			min_r_damage = field[32].GetFloat();
			max_r_damage = field[33].GetFloat();
			base_attack_time = field[34].GetUInt32();
			base_attack_time_r = field[35].GetUInt32();
		}

		switch (Class)
		{
		case CLASS_WARRIOR:
			ClassStr = "Воин";
			PowerStr = "Ярость";
			Power = maxpower4;
			break;
		case CLASS_PALADIN:
			ClassStr = "Паладин";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		case CLASS_HUNTER:
			ClassStr = "Охотник";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		case CLASS_ROGUE:
			ClassStr = "Разбойник";
			PowerStr = "Энергия";
			Power = maxpower4;
			break;
		case CLASS_PRIEST:
			ClassStr = "Жрец";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		case CLASS_DEATH_KNIGHT:
			ClassStr = "Рыцарь Смерти";
			Power = maxpower7 / 10;
			PowerStr = "Сила рун";
			break;
		case CLASS_SHAMAN:
			ClassStr = "Шаман";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		case CLASS_MAGE:
			ClassStr = "Маг";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		case CLASS_WARLOCK:
			ClassStr = "Чернокнижник";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		case CLASS_DRUID:
			ClassStr = "Друид";
			PowerStr = "Мана";
			Power = maxpower1;
			break;
		}

		curr_min_damage = min_damage;
		curr_max_damage = max_damage;
		curr_min_damage_range = min_r_damage;
		curr_max_damage_range = max_r_damage;

		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Персонаж|r %s %s %s %u-го |cff00ff00уровня|r", nameLink.c_str(), raceStr.c_str(), ClassStr.c_str(), level);
		handler->PSendSysMessage("|cFFFF0000# ======================|r");
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Здоровье:|r %u|cff00ff00, %s:|r %u", maxhealth, PowerStr.c_str(), Power);
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Сила:|r %u|cff00ff00, Ловкость:|r %u|cff00ff00, Выносливость:|r %u|cff00ff00, Интеллект:|r %u|cff00ff00, Дух:|r %u", strength, agility, stamina, intellect, spirit);
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Броня:|r %u", armor);
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Устойчивость:|r %u", resilience);
		handler->PSendSysMessage("|cFFFF0000# ======================|r");
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Тайная:|r %u|cff00ff00, Огонь:|r %u|cff00ff00, Природа:|r %u|cff00ff00, Лёд:|r %u|cff00ff00, Тёмная:|r %u", resArcane, resFire, resNature, resFrost, resShadow);
		handler->PSendSysMessage("|cFFFF0000# ======================|r");
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Блок:|r %.2f", blockPct);
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Уклонение:|r %.2f", dodgePct);
		handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Паррирование:|r %.2f", parryPct);
		handler->PSendSysMessage("|cFFFF0000# ======================|r");

		if (Class == CLASS_WARRIOR || Class == CLASS_PALADIN || Class == CLASS_ROGUE || Class == CLASS_DEATH_KNIGHT || Class == CLASS_SHAMAN || Class == CLASS_DRUID)
		{
			handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Урон ближний бой:|r %u - %u", curr_min_damage, curr_max_damage);
			// handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Сила атаки ближнего боя:|r %u", attackPower);
			handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Крит ближнего боя:|r %.2f", critPct);
			// handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Скорость атаки ближнего боя:|r %u", base_attack_time);
		}
		if (Class == CLASS_HUNTER)
		{
			handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Урон дальнего боя:|r %u - %u", curr_min_damage_range, curr_max_damage_range);
			// handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Сила атаки дальнего боя:|r %u", rangedAttackPower);
			// handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Скорость атаки дальнего боя:|r %u", base_attack_time_r);
			handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Крит дальний бой:|r %.2f", rangedCritPct);
		}

		if (Class == CLASS_PALADIN || Class == CLASS_PRIEST || Class == CLASS_SHAMAN || Class == CLASS_MAGE || Class == CLASS_WARLOCK || Class == CLASS_DRUID)
		{
			handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Сила заклинаний:|r %u", spellPower);
			// handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Спелл крит:|r %.2f", spellCritPct);
		}

		handler->PSendSysMessage("|cFFFF0000# ======================|r");

		return true;
	}

	static bool HandleUnellTopTime(ChatHandler *handler, const char * /*args*/)
	{
		Player *player = handler->GetSession()->GetPlayer();

		if (!sConfigMgr->GetBoolDefault("Unell.Top.Enable", true))
		{
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Система топов сервера была отключена");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (sConfigMgr->GetBoolDefault("Unell.Top.TotalTime.Enable", true))
		{
			QueryResult totaltimeres = CharacterDatabase.PQuery("SELECT value FROM `worldstates` WHERE `entry` = '40000'");
			uint32 totaltime = totaltimeres->Fetch()->GetUInt32();
			std::string timeStr = secsToTimeString(totaltime - time(NULL), false, false);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Топ: |cFFFF0000Игровое время|cff6C8CD5. Окончание через |cff14ECCF%s", timeStr.c_str());
		}

		if (sConfigMgr->GetBoolDefault("Unell.Top.TotalKill.Enable", true))
		{
			QueryResult totalkillres = CharacterDatabase.PQuery("SELECT value FROM `worldstates` WHERE `entry` = '40001'");
			uint32 totalkill = totalkillres->Fetch()->GetUInt32();
			std::string killStr = secsToTimeString(totalkill - time(NULL), false, false);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Топ: |cFFFF0000PvP убийства|cff6C8CD5. Окончание через |cff14ECCF%s", killStr.c_str());
		}

		return true;
	}

	static bool HandleUnellOwnNPCVendorAddMoreItem(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();
		Creature *creature = handler->getSelectedCreature();

		if (!creature || creature->IsPet())
		{
			handler->SendSysMessage("|cffff0000#|r Да выбери ты нпц нормального, ну чего за дела!");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!creature->IsVendor())
		{
			handler->SendSysMessage("|cffff0000#|r Ты всерьёз думаешь, что это вендор?");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 Entry = creature->GetEntry();
		CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const *crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		char *Item_start = strtok((char *)args, "-");
		if (!Item_start)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Неверно введён начальный предмет");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 Itemstart = (uint32)atoi(Item_start);

		char *Item_end = strtok(NULL, " ");
		if (!Item_end)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Неверно введён конечный предмет");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 Itemend = (uint32)atoi(Item_end);

		char *vcost = strtok(NULL, " ");
		uint32 extendedcost = vcost ? atol(vcost) : 0;

		uint32 maxcount = 0;
		uint32 incrtime = 0;
		uint32 vendor_entry = Entry;
		uint32 step = 1;

		handler->PSendSysMessage("|cFFFF0000# |cff00ff00Заливка вещей в нпц-вендора: |cffff0000%s|cff00ff00 с ценой |cffff0000%u|cff00ff00.", crename, extendedcost);

		for (uint32 i = Itemstart; i < Itemend + 1; i++)
		{
			ItemTemplate const *itemTemplate = sObjectMgr->GetItemTemplate(i);
			ItemLocale const *itemLocale = sObjectMgr->GetItemLocale(i);
			char const *name = NULL;
			if (itemLocale)
				name = itemLocale->Name[handler->GetSessionDbcLocale()].c_str();
			if ((!name || !*name) && itemTemplate)
				name = itemTemplate->Name1.c_str();
			if (!name)
				name = "Unknown item";

			if (!sObjectMgr->IsVendorItemValid(vendor_entry, i, maxcount, incrtime, extendedcost, handler->GetSession()->GetPlayer()))
			{
				handler->SetSentErrorMessage(true);
				continue;
			}

			sObjectMgr->AddVendorItem(vendor_entry, i, maxcount, incrtime, extendedcost);
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00%u.|r Заливка итема |c%08x|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r",
									 step, ItemQualityColors[itemTemplate ? itemTemplate->Quality : ITEM_QUALITY_POOR], i, name);

			++step;
		}

		handler->PSendSysMessage("|cFFFF0000# |cff00ff00Готово. Залито |cFFFF0000%u |cff00ff00итемов.", step - 1);
		return true;
	}

	static bool HandleUnellOwnNPCVendorDelMoreItem(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();
		Creature *creature = handler->getSelectedCreature();

		if (!creature || creature->IsPet())
		{
			handler->SendSysMessage("|cffff0000#|r Да выбери ты нпц нормального, ну чего за дела!");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!creature->IsVendor())
		{
			handler->SendSysMessage("|cffff0000#|r Ты всерьёз думаешь, что это вендор?");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 Entry = creature->GetEntry();
		CreatureTemplate const *cInfo = creature->GetCreatureTemplate();
		CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const *crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		char *Item_start = strtok((char *)args, "-");
		if (!Item_start)
			return false;

		char *Item_end = strtok(NULL, " ");
		if (!Item_end)
			return false;

		uint32 Itemstart = (uint32)atoi(Item_start);
		uint32 Itemend = (uint32)atoi(Item_end);

		uint32 vendor_entry = Entry;
		uint32 step = 1;

		handler->PSendSysMessage("|cFFFF0000# |cff00ff00Чистка вещей у нпц-вендора: |cffff0000%s|cff00ff00.", crename);

		for (uint32 i = Itemstart; i < Itemend + 1; i++)
		{
			ItemTemplate const *itemTemplate = sObjectMgr->GetItemTemplate(i);
			ItemLocale const *itemLocale = sObjectMgr->GetItemLocale(i);
			char const *name = NULL;
			if (itemLocale)
				name = itemLocale->Name[handler->GetSessionDbcLocale()].c_str();
			if ((!name || !*name) && itemTemplate)
				name = itemTemplate->Name1.c_str();
			if (!name)
				name = "Unknown item";

			if (!sObjectMgr->RemoveVendorItem(Entry, i))
			{
				handler->PSendSysMessage(LANG_ITEM_NOT_IN_LIST, i);
				handler->SetSentErrorMessage(true);
				continue;
			}

			handler->PSendSysMessage("|cFFFF0000# |cff00ff00%u.|r Удаление итема |c%08x|Hitem:%u:0:0:0:0:0:0:0:0|h[%s]|h|r",
									 step, ItemQualityColors[itemTemplate ? itemTemplate->Quality : ITEM_QUALITY_POOR], i, name);

			++step;
		}

		handler->PSendSysMessage("|cFFFF0000# |cff00ff00Готово. Удалено |cFFFF0000%u |cff00ff00итемов.", step - 1);

		return true;
	}

	static bool HandleUnellOwnNPCVendorClear(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();
		Creature *creature = handler->getSelectedCreature();

		if (!creature || creature->IsPet())
		{
			handler->SendSysMessage("|cffff0000#|r Да выбери ты нпц, ну чего за дела!");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!creature->IsVendor())
		{
			handler->SendSysMessage("|cffff0000#|r Ты всерьёз думаешь, что это вендор?");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 Entry = creature->GetEntry();
		CreatureTemplate const *cInfo = creature->GetCreatureTemplate();
		CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const *crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		QueryResult result = WorldDatabase.PQuery("SELECT item FROM npc_vendor WHERE entry = '%u'", Entry);
		if (result)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Удалены все предметы у нпц-вендора: |cffff0000%s|cff00ff00.", crename);
			do
			{
				Field *fields = result->Fetch();
				uint32 itemId = fields[0].GetUInt32();

				sObjectMgr->RemoveVendorItem(Entry, itemId);
			} while (result->NextRow());
		}
		if (!result)
			handler->PSendSysMessage("|cffff0000# |cff00ff00Предметов у нпц-вендора: |cffff0000%s|cff00ff00, не обнаружено.", crename);

		return true;
	}

	static bool HandleUnellOwnNPCVendorCost(ChatHandler *handler, const char *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Нужно указать айди цены.");
			handler->SetSentErrorMessage(true);
			return false;
		}

		Player *player = handler->GetSession()->GetPlayer();
		Creature *creature = handler->getSelectedCreature();

		if (!creature || creature->IsPet())
		{
			handler->SendSysMessage("|cffff0000#|r Да выбери ты нпц, ну чего за дела!");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!creature->IsVendor())
		{
			handler->SendSysMessage("|cffff0000#|r Ты всерьёз думаешь, что это вендор?");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 costid = (uint32)atoi((char *)args);
		uint32 Entry = creature->GetEntry();
		CreatureTemplate const *cInfo = creature->GetCreatureTemplate();
		CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const *crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		WorldDatabase.PExecute("UPDATE `npc_vendor` SET `ExtendedCost`='%u' WHERE (`entry`='%u')", costid, Entry);
		sObjectMgr->LoadVendors();
		handler->PSendSysMessage("|cffff0000# |cff00ff00Смена цены на все предметы у нпц-вендора: |cffff0000%s|cff00ff00. Новая цена |cffff0000%u|cff00ff00.", crename, costid);

		return true;
	}

	static bool HandleUnellOwnNPCVendorFree(ChatHandler *handler, const char *args)
	{

		Player *player = handler->GetSession()->GetPlayer();
		Creature *creature = handler->getSelectedCreature();

		if (!creature || creature->IsPet())
		{
			handler->SendSysMessage("|cffff0000#|r Да выбери ты нпц, ну чего за дела!");
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!creature->IsVendor())
		{
			handler->SendSysMessage("|cffff0000#|r Ты всерьёз думаешь, что это вендор?");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 Entry = creature->GetEntry();
		CreatureTemplate const *cInfo = creature->GetCreatureTemplate();
		CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const *crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		WorldDatabase.PExecute("UPDATE `npc_vendor` SET `ExtendedCost`='0' WHERE (`entry`='%u')", Entry);
		sObjectMgr->LoadVendors();
		handler->PSendSysMessage("|cffff0000# |cff00ff00Теперь все предметы у нпц-вендора: |cffff0000%s|cff00ff00. Бесплатные.", crename);

		return true;
	}

	static bool HandleUnellOwnNPCDisplay(ChatHandler *handler, const char *args)
	{
		if (!*args)
			return false;

		uint32 displayId = (uint32)atoi((char *)args);
		Creature *creature = handler->getSelectedCreature();
		Player *player = handler->GetSession()->GetPlayer();

		if (!creature || creature->IsPet())
		{
			handler->SendSysMessage("|cffff0000#|r Да выбери ты нпц уже, ну чего за дела!");
			handler->SetSentErrorMessage(true);
			return false;
		}

		creature->SetDisplayId(displayId);
		creature->SetNativeDisplayId(displayId);
		creature->SaveToDB();

		uint32 Entry = creature->GetEntry();
		CreatureTemplate const *cInfo = creature->GetCreatureTemplate();
		CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const *crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		QueryResult resultmodel = WorldDatabase.PQuery("SELECT modelid1 FROM creature_template WHERE entry = '%u'", Entry);

		if (!resultmodel)
			handler->PSendSysMessage("|cffff0000# |cff00ff00Не обнаружена модель.");

		uint32 modelid = resultmodel->Fetch()->GetUInt32();

		WorldDatabase.PExecute("UPDATE `creature_template` SET `modelid1`='%u' WHERE (`entry`='%u')", displayId, Entry);

		handler->PSendSysMessage("|cffff0000# |cff00ff00Для нпц: |cffff0000%s|cff00ff00, произведена смена модели с |cffff0000%u |cff00ff00на |cffff0000%u|cff00ff00.", crename, modelid, displayId);
		return true;
	}

	static bool HandleUnellItemLevel(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();
		uint32 avgILvl = player->GetAverageItemLevel();
		handler->PSendSysMessage("|cffff0000# |cff00ff00Средний уровень ваших предметов:|r %u", avgILvl);
		return true;
	}

	static bool HandleUnellDisplayIDAll(ChatHandler *handler, const char *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Нужно ввести название предметов на анг. либо на русском языке");
			handler->SetSentErrorMessage(true);
			return false;
		}

		std::string argstr = (char *)args;
		handler->PSendSysMessage("|cffff0000# |cff00ff00Запрос на дисплей айди преметов по названию:|r %s", argstr.c_str());

		Player *player = handler->GetSession()->GetPlayer();
		std::string namepart = args;
		std::wstring wnamepart;

		// converting string that we try to find to lower case
		if (!Utf8toWStr(namepart, wnamepart))
			return false;

		wstrToLower(wnamepart);

		bool found = false;
		uint32 count = 0;
		uint32 maxResults = sWorld->getIntConfig(CONFIG_MAX_RESULTS_LOOKUP_COMMANDS);

		// Search in `item_template`
		ItemTemplateContainer const *its = sObjectMgr->GetItemTemplateStore();
		for (ItemTemplateContainer::const_iterator itr = its->begin(); itr != its->end(); ++itr)
		{
			int loc_idx = player->GetSession()->GetSessionDbLocaleIndex();
			if (loc_idx >= 0)
			{
				uint8 uloc_idx = uint8(loc_idx);
				if (ItemLocale const *il = sObjectMgr->GetItemLocale(itr->second.ItemId))
				{
					if (il->Name.size() > uloc_idx && !il->Name[uloc_idx].empty())
					{
						std::string name = il->Name[uloc_idx];

						if (Utf8FitTo(name, wnamepart))
						{
							if (maxResults && count++ == maxResults)
							{
								handler->PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
								return true;
							}

							QueryResult resultdisplay = WorldDatabase.PQuery("SELECT displayid FROM item_template WHERE entry = '%u'", itr->second.ItemId);
							uint32 displayid = resultdisplay->Fetch()->GetUInt32();

							if (player->GetSession())
								handler->PSendSysMessage("|cffff0000# |cff00ff00Дисплей айди|r %u |cff00ff00-|r |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r ", displayid, itr->second.ItemId, name.c_str());
							else
								handler->PSendSysMessage("%d - %s", itr->second.ItemId, name.c_str());

							if (!found)
								found = true;

							continue;
						}
					}
				}
			}

			std::string name = itr->second.Name1;
			if (name.empty())
				continue;

			if (Utf8FitTo(name, wnamepart))
			{
				if (maxResults && count++ == maxResults)
				{
					handler->PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
					return true;
				}

				QueryResult resultdisplay = WorldDatabase.PQuery("SELECT displayid FROM item_template WHERE entry = '%u'", itr->second.ItemId);
				uint32 displayid = resultdisplay->Fetch()->GetUInt32();

				if (player->GetSession())
					handler->PSendSysMessage("|cffff0000# |cff00ff00Дисплей айди|r %u |cff00ff00-|r |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r ", displayid, itr->second.ItemId, name.c_str());
				else
					handler->PSendSysMessage("%d - %s", itr->second.ItemId, name.c_str());

				if (!found)
					found = true;
			}
		}

		if (!found)
			handler->PSendSysMessage("|cffff0000# |cff00ff00Не найдено предметов по запросу:|r %s", argstr.c_str());

		return true;
	}

	static bool HandleUnellDisplayID(ChatHandler *handler, const char *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Нужно ввести айди итема, либо линкануть его");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 itemId = 0;

		if (args[0] == '[') // [name] manual form
		{
			char *citemName = strtok((char *)args, "]");

			if (citemName && citemName[0])
			{
				std::string itemName = citemName + 1;
				WorldDatabase.EscapeString(itemName);

				PreparedStatement *stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_ITEM_TEMPLATE_BY_NAME);
				stmt->setString(0, itemName);
				PreparedQueryResult result = WorldDatabase.Query(stmt);

				if (!result)
				{
					handler->PSendSysMessage(LANG_COMMAND_COULDNOTFIND, citemName + 1);
					handler->SetSentErrorMessage(true);
					return false;
				}
				itemId = result->Fetch()->GetUInt16();
			}
			else
				return false;
		}
		else // item_id or [name] Shift-click form |cffffffff|Hitem:item_id:0:0:0|h[name]|h|r
		{
			char *cId = handler->extractKeyFromLink((char *)args, "Hitem");
			if (!cId)
				return false;
			itemId = atol(cId);
		}

		ItemTemplate const *pProto = sObjectMgr->GetItemTemplate(itemId);
		if (!pProto)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Невозможно найти дисплей айди, верноятно предмета:|r %u |cff00ff00нет в базе", itemId);
			handler->SetSentErrorMessage(true);
			return false;
		}

		QueryResult resultdisplay = WorldDatabase.PQuery("SELECT displayid FROM item_template WHERE entry = '%u'", itemId);
		uint32 displayid = resultdisplay->Fetch()->GetUInt32();

		ItemTemplate const *itemTemplate = sObjectMgr->GetItemTemplate(itemId);
		ItemLocale const *itemLocale = sObjectMgr->GetItemLocale(itemId);
		char const *name = NULL;
		if (itemLocale)
			name = itemLocale->Name[handler->GetSessionDbcLocale()].c_str();
		if ((!name || !*name) && itemTemplate)
			name = itemTemplate->Name1.c_str();
		if (!name)
			name = "Unknown item"; // |cffff0000# |cff00ff00Дисплей айди|r %u |cff00ff00-|r

		handler->PSendSysMessage("|cffff0000# |cff00ff00Дисплей айди|r %u |cff00ff00-|r |c%08x|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r",
								 displayid, ItemQualityColors[itemTemplate ? itemTemplate->Quality : ITEM_QUALITY_POOR], itemId, name);
		return true;
	}

	static bool HandleUnellDisplayIDMoreItem(ChatHandler *handler, const char *args)
	{
		if (!*args)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Нужно ввести диапазон предметов");
			handler->SetSentErrorMessage(true);
			return false;
		}

		char *Item_start = strtok((char *)args, "-");
		if (!Item_start)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Неверно введён начальный предмет");
			return false;
		}

		uint32 Itemstart = (uint32)atoi(Item_start);

		char *Item_end = strtok(NULL, " ");
		if (!Item_end)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Неверно введён конечный предмет");
			return false;
		}

		uint32 Itemend = (uint32)atoi(Item_end);

		for (uint32 i = Itemstart; i < Itemend + 1; i++)
		{
			uint32 itemId = i;

			ItemTemplate const *pProto = sObjectMgr->GetItemTemplate(itemId);
			if (!pProto)
			{
				handler->PSendSysMessage("|cffff0000# |cff00ff00Невозможно найти дисплей айди, верноятно предмета:|r %u |cff00ff00нет в базе", itemId);
				handler->SetSentErrorMessage(true);
				continue;
			}

			QueryResult resultdisplay = WorldDatabase.PQuery("SELECT displayid FROM item_template WHERE entry = '%u'", itemId);
			uint32 displayid = resultdisplay->Fetch()->GetUInt32();

			ItemTemplate const *itemTemplate = sObjectMgr->GetItemTemplate(itemId);
			ItemLocale const *itemLocale = sObjectMgr->GetItemLocale(itemId);
			char const *name = NULL;
			if (itemLocale)
				name = itemLocale->Name[handler->GetSessionDbcLocale()].c_str();
			if ((!name || !*name) && itemTemplate)
				name = itemTemplate->Name1.c_str();
			if (!name)
				name = "Unknown item"; // |cffff0000# |cff00ff00Дисплей айди|r %u |cff00ff00-|r

			handler->PSendSysMessage("|cffff0000# |cff00ff00Айди|r %u |cff00ff00Дисплей|r %u |cff00ff00-|r |c%08x|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r",
									 itemId, displayid, ItemQualityColors[itemTemplate ? itemTemplate->Quality : ITEM_QUALITY_POOR], itemId, name);
		}

		return true;
	}

	// static bool HandleUnellNpcLoot(ChatHandler * handler, const char* /*args*/)
	/*{
        Player* player = handler->GetSession()->GetPlayer();
		Creature* target = handler->getSelectedCreature();		
		
        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }		
		
		uint32 Entry = target->GetEntry();
		CreatureTemplate const* cInfo = target->GetCreatureTemplate();
		uint32 Entryloot = cInfo->lootid;		
		CreatureTemplate const* CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const* CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const* crename = NULL;
			if (CreatureLocale)
				crename = CreatureLocale->Name[handler->GetSessionDbcLocale()].c_str();
			if ((!crename || !*crename) && CreatureTemplate)
				crename = CreatureTemplate->Name.c_str();
			if (!crename)
				crename = "Unknown creature";				
		
		
		if (Entryloot > 0)
			{
				QueryResult resultloot = WorldDatabase.PQuery("SELECT Item, MinCount, MaxCount FROM creature_loot_template WHERE entry = '%u'", Entryloot);
				if(resultloot)
				{
					handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Информация о луте существа: |cffff0000%s", crename);
					do
					{
						Field * fields = resultloot->Fetch();
						uint32 itemid = fields[0].GetUInt32();
						int32 mincount = fields[1].GetInt32();	
						uint32 maxcount = fields[2].GetUInt32();

						ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemid);
						ItemLocale const* itemLocale = sObjectMgr->GetItemLocale(itemid);
						char const* name = NULL;
						if (itemLocale)
							name = itemLocale->Name[handler->GetSessionDbcLocale()].c_str();
						if ((!name || !*name) && itemTemplate)
							name = itemTemplate->Name1.c_str();
						if (!name)
							name = "Unknown item";
						
						if (mincount == maxcount)
							{
								handler->PSendSysMessage("|cFFFF0000 - |c%08x|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r",
								ItemQualityColors[itemTemplate ? itemTemplate->Quality : ITEM_QUALITY_POOR], itemid, name);
							}
						else
						{
							handler->PSendSysMessage("|cFFFF0000 - От |cff14ECCF%u |cFFFF0000до |cff14ECCF%u |c%08x|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r",
								mincount, maxcount, ItemQualityColors[itemTemplate ? itemTemplate->Quality : ITEM_QUALITY_POOR], itemid, name);
						}	
					}
					while(resultloot->NextRow());
				}
				
				if(!resultloot)
				{
					handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Существо: |cffff0000%s|cff6C8CD5, не имеет лута.", crename);
				}
			}
			else
				handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Существо: |cffff0000%s|cff6C8CD5, не имеет лута.", crename);
		
				
		return true;			
    }*/

	static bool HandleBuffCommand(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();

		if (player->duel || player->GetMap()->IsBattleArena() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead(), player->IsInCombat() || player->IsInFlight())
		{
			handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
			handler->SetSentErrorMessage(true);
			return false;
		}

		player->RemoveAurasByType(SPELL_AURA_MOUNTED);
		uint32 auras[] = {57623, 25898, 48470, 48162, 48074, 61316};
		static const size_t sizeaura = sizeof(auras) / sizeof(*auras);

		for (int i = 0; i < sizeaura; i++)
			player->CastSpell(player, auras[i], true);

		handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вы получили обычные баффы.");
		return true;
	}

	static bool HandleBuffCommandVor(ChatHandler *handler, const char *args)
	{
		Player *player = handler->GetSession()->GetPlayer();

		if (!player->GetSession()->IsPremium())
		{
			handler->SendSysMessage("Вы не являетсь VIP игроком");

			handler->SetSentErrorMessage(true);
			return false;
		}
		else
		{
			if (player->duel || player->GetMap()->IsBattleArena() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
			{
				handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
				handler->SetSentErrorMessage(true);
				return false;
			}

			player->RemoveAurasByType(SPELL_AURA_MOUNTED);
			uint32 auras[] = {23735, 23736, 23737, 23738, 23766, 23767, 23768, 23769};
			static const size_t sizeaura = sizeof(auras) / sizeof(*auras);
			for (int i = 0; i < sizeaura; i++)
				player->CastSpell(player, auras[i], true);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вы получили баффы Воржея.");
			return true;
		}
		return false;
	}

	static bool HandleUnellHome(ChatHandler *handler, const char * /*args*/)
	{
		Player *chr = handler->GetSession()->GetPlayer();

		if (chr->IsInCombat() || chr->IsInFlight() || chr->GetMap()->IsBattlegroundOrArena() || chr->HasStealthAura() || chr->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || chr->isDead())
		{
			handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
			handler->SetSentErrorMessage(true);
			return false;
		}

		handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Сейчас вы будете дома :)");
		chr->RemoveSpellCooldown(8690, true);
		chr->CastSpell(chr, 8690, false);
		chr->RemoveSpellCooldown(8690, true);
		return true;
	}

	static bool HandleUnellHeal(ChatHandler *handler, const char * /*args*/)
	{
		Player *chr = handler->GetSession()->GetPlayer();
		uint32 PvPZoneID = sConfigMgr->GetIntDefault("Unell.PvP.Announce.Kill.ZoneID", 17);

		if (chr->GetZoneId() == PvPZoneID || chr->IsInCombat() || chr->duel || chr->IsInFlight() || chr->GetMap()->IsBattlegroundOrArena() || chr->HasStealthAura() || chr->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || chr->isDead())
		{
			handler->SendSysMessage(LANG_PREMIUM_CANT_DO);
			handler->SetSentErrorMessage(true);
			return false;
		}

		chr->RemoveAurasByType(SPELL_AURA_MOUNTED);
		chr->CastSpell(chr, 23965, false);
		return true;
	}

	static bool HandleUnellInfo(ChatHandler *handler, const char *args)
	{
		Player *target = handler->getSelectedPlayer();

		if (!target)
		{
			handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 accid = target->GetSession()->GetAccountId();
		std::string os = Unell_Script::Unell_InfoOS(accid);
		std::string gmlvl;
		std::string tNameLink = handler->GetNameLink(target);
		int64 muteTime = target->GetSession()->m_muteTime;
		int64 totaltime = target->GetTotalPlayedTime();
		std::string timeStr = secsToTimeString(totaltime, false, false);
		uint32 latency = target->GetSession()->GetLatency();

		switch (target->GetSession()->GetSecurity())
		{
		case 0:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_0);
			break;
		case 1:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_1);
			break;
		case 2:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_2);
			break;
		case 3:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_3);
			break;
		case 4:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_4);
			break;
		case 5:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_5);
			break;
		case 6:
			gmlvl = handler->GetTrinityString(UNELL_LANG_GM_LEVEL_6);
			break;
		}

		handler->PSendSysMessage("|cffff0000# |cff00ff00Информация о игроке %s", tNameLink.c_str());
		handler->PSendSysMessage("|cffff0000# |cff00ff00Уровень доступа:|r |cff14ECCF%s", gmlvl.c_str());

		if (target->GetSession()->IsPremium())
		{
			QueryResult result = LoginDatabase.PQuery("SELECT unsetdate FROM account_premium WHERE id = %u", accid);
			if (result)
			{
				Field *field = result->Fetch();
				uint32 unsetdate = field[0].GetUInt32();
				std::string timeStr = secsToTimeString(unsetdate - time(NULL), false, false);
				handler->PSendSysMessage("|cffff0000#|cff00ff00 Статус VIP аккаунта:|r |cff14ECCFИмеет VIP");
				handler->PSendSysMessage("|cFFFF0000#|cff00ff00 Премиум аккаунт закончится через: |cff14ECCF%s", timeStr.c_str());
			}
		}
		else
			handler->PSendSysMessage("|cffff0000# |cff00ff00Статус VIP аккаунта:|r |cff14ECCFНе имеет VIP");

		if (!target->CanSpeak())
		{
			if (muteTime > 0)
				handler->PSendSysMessage("|cffff0000# |cff00ff00Оставшееся время мута: |cff14ECCF%s", secsToTimeString(muteTime - time(NULL), false, false).c_str());
		}

		handler->PSendSysMessage("|cffff0000# |cff00ff00Игровое время: |cff14ECCF%s", timeStr.c_str());

		if (latency == 0)
			handler->PSendSysMessage("|cffff0000# |cff00ff00Задержка: |cff14ECCFНеопределенно");
		else
			handler->PSendSysMessage("|cffff0000# |cff00ff00Задержка: |cff14ECCF%u мс", latency);

		if (os == "OSX")
			handler->PSendSysMessage("|cffff0000# |cff00ff00В игре со смартфона, ух какой!");

		return true;
	}

	static bool HandleUnellUnixTime(ChatHandler *handler, const char * /*args*/)
	{
		time_t curTime = time(NULL);
		uint32 dtime = uint32(curTime + 86400);
		uint32 wtime = uint32(curTime + 604800);
		uint32 mtime = uint32(curTime + 2592000);
		Player *player = handler->GetSession()->GetPlayer();
		handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Сейчас время |cFFFF0000%u", uint32(curTime));
		handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Время через 7 дней |cFFFF0000%u", dtime);
		handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Время через 30 дней |cFFFF0000%u", mtime);
		return true;
	}

	static bool HandleUnellAdd(ChatHandler *handler, const char *args)
	{
		if (!sConfigMgr->GetBoolDefault("Unell.Command.Add", true))
		{
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Эта команда была отключена");
			handler->SetSentErrorMessage(true);
			return false;
		}

		Player *target = handler->getSelectedPlayer();

		if (!target)
		{
			handler->SendSysMessage(LANG_NO_CHAR_SELECTED);
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint32 itemId = sConfigMgr->GetIntDefault("Unell.Command.Add.itemId", 0);
		Player *playerses = handler->GetSession()->GetPlayer();
		Player *plTarget = handler->getSelectedPlayer();

		char *px = strtok((char *)args, " ");
		if (!px)
			return false;

		int32 count = (uint32)atoi(px);

		if (count == 0)
			count = 1;

		if (!plTarget)
			plTarget = playerses;

		sLog->outDetail(handler->GetSession()->GetTrinityString(LANG_ADDITEM), itemId, count);

		//Subtract
		if (count < 0)
		{
			plTarget->DestroyItemCount(itemId, -count, true, false);
			handler->PSendSysMessage(LANG_REMOVEITEM, itemId, -count, handler->GetNameLink(plTarget).c_str());
			return true;
		}

		//Adding items
		uint32 noSpaceForCount = 0;

		// check space and find places
		ItemPosCountVec dest;
		InventoryResult msg = plTarget->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
		if (msg != EQUIP_ERR_OK) // convert to possible store amount
			count -= noSpaceForCount;

		if (count == 0 || dest.empty()) // can't add any
		{
			handler->PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);
			handler->SetSentErrorMessage(true);
			return false;
		}

		Item *item = plTarget->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

		// remove binding (let GM give it to another player later)
		if (playerses == plTarget)
			for (ItemPosCountVec::const_iterator itr = dest.begin(); itr != dest.end(); ++itr)
				if (Item *item1 = playerses->GetItemByPos(itr->pos))
					item1->SetBinding(false);

		if (count > 0 && item)
		{
			playerses->SendNewItem(item, count, false, true);
			if (playerses != plTarget)
				plTarget->SendNewItem(item, count, true, false);
		}

		if (noSpaceForCount > 0)
			handler->PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itemId, noSpaceForCount);

		std::string gmname = playerses->GetName();
		std::string targetname = target->GetName();
		uint32 gmaccid = playerses->GetSession()->GetAccountId();
		uint32 targetaccid = target->GetSession()->GetAccountId();
		time_t curTime = time(NULL);
		uint32 localtime = curTime;

		CharacterDatabase.PExecute("INSERT INTO `logs_add` (`gmplayer`, `gmaccount`, `count`, `time`, `targetname`, `targetacc`) VALUES ('%s', '%u', '%u', '%u', '%s', '%u')", gmname.c_str(), gmaccid, count, localtime, targetname.c_str(), targetaccid);

		return true;
	}

	static bool HandleUnellTimeAP(ChatHandler *handler, const char * /*args*/)
	{
		QueryResult result1 = CharacterDatabase.PQuery("SELECT value FROM worldstates WHERE entry = 20001");

		if (result1)
		{
			Field *fields = NULL;
			fields = result1->Fetch();
			uint32 value = fields[0].GetUInt32();
			std::string timeStr = secsToTimeString(value - time(NULL), false, false);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Начисление очков арены через |cff14ECCF%s", timeStr.c_str());
		}
		return true;
	}

	static bool HandleUnellTimeVIP(ChatHandler *handler, const char * /*args*/)
	{
		Player *player = handler->GetSession()->GetPlayer();
		uint32 accid = player->GetSession()->GetAccountId();
		QueryResult result = LoginDatabase.PQuery("SELECT unsetdate FROM account_premium WHERE id = %u", accid);
		if (result)
		{
			Field *field = result->Fetch();
			uint32 unsetdate = field[0].GetUInt32();
			std::string timeStr = secsToTimeString(unsetdate - time(NULL), false, false);
			handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Премиум аккаунт закончится через |cff14ECCF%s", timeStr.c_str());
		}
		return true;
	}

	static bool HandleUnellToken(ChatHandler *handler, const char * /*args*/)
	{
		Player *player = handler->GetSession()->GetPlayer();
		uint32 accid = player->GetSession()->GetAccountId();
		handler->PSendSysMessage("|cFFFF0000#|cff6C8CD5 Проверка донат валюты у игроков");
		QueryResult result = CharacterDatabase.PQuery("SELECT owner_guid, count FROM item_instance WHERE `itemEntry` = '120000' AND `count` > '500' ORDER BY count DESC LIMIT 10");
		if (result)
		{
			do
			{
				Field *fields = result->Fetch();
				uint32 owner_guid = fields[0].GetUInt32();
				uint32 count = fields[1].GetUInt32();
				QueryResult namechar = CharacterDatabase.PQuery("SELECT guid, name FROM characters WHERE guid = %u", owner_guid);
				if (namechar)
				{
					Field *fields = namechar->Fetch();
					uint32 guid = fields[0].GetUInt32();
					std::string name = fields[1].GetString();
					handler->PSendSysMessage("|cffff0000# |cff14ECCFНик: |cffff0000%s|cff14ECCF, Количество валюты: |cffff0000%u", name.c_str(), count);
				}
			} while (result->NextRow());
		}
		return true;
	}

	static bool HandleUnellTokenAddChar(ChatHandler *handler, const char *args)
	{
		char *nameStr;
		char *tokenStr;
		handler->extractOptFirstArg((char *)args, &nameStr, &tokenStr);

		if (!tokenStr)
			return false;

		Player *target;
		uint64 target_guid;
		std::string target_name;
		if (!handler->extractPlayerTarget(nameStr, &target, &target_guid, &target_name))
			return false;

		uint32 accountId = target ? target->GetSession()->GetAccountId() : sObjectMgr->GetPlayerAccountIdByGUID(target_guid);
		if (!target)
			if (WorldSession *session = sWorld->FindSession(accountId))
				target = session->GetPlayer();

		uint32 token = uint32(atoi(tokenStr));
		QueryResult result = LoginDatabase.PQuery("SELECT id, username FROM account WHERE id = %u", accountId);

		if (result)
		{
			Field *fields = result->Fetch();
			uint32 id = fields[0].GetUInt32();
			std::string username = fields[1].GetString();

			if (Unell_Script::Unell_acctoken(accountId))
			{
				LoginDatabase.PExecute("UPDATE `account_token` SET `token`=`token`+%u WHERE (`id`='%u')", token, accountId);
				LoginDatabase.PExecute("UPDATE `token_full` SET `count` = `count`+%u WHERE `accid` = %u", token, accountId);
			}
			else
			{
				LoginDatabase.PExecute("INSERT INTO `account_token` (`id`, `token`, `refereraccid`) VALUES ('%u', '%u', '0')", accountId, token);
				LoginDatabase.PExecute("INSERT INTO `token_full`(`accid`, `accname`, `count`) VALUES (%u, '%s', %u)", accountId, username.c_str(), token);
			}

			QueryResult res = LoginDatabase.PQuery("SELECT token FROM account_token WHERE id = %u", accountId);

			if (res)
			{
				Field *field = res->Fetch();
				uint32 balance = field[0].GetUInt32();
				handler->PSendSysMessage("|cffff0000# |cff14ECCFВыдача на аккаунт: |cffff0000%s|cff14ECCF количеством: |cffff0000%u |cff14ECCFтокенов.", username.c_str(), token);
			}
			else
			{
				handler->PSendSysMessage("|cffff0000# |cff14ECCFНа данный аккаунт первый раз выдаётся донат. Он занесён в базу донатов.");
				handler->PSendSysMessage("|cffff0000# |cff14ECCFВыдача на аккаунт: |cffff0000%s|cff14ECCF количеством: |cffff0000%u |cff14ECCFтокенов.", username.c_str(), token);
			}
		}

		return true;
	}

	static bool HandleUnellTokenAddAcc(ChatHandler *handler, const char *args)
	{
		char *nameStr;
		char *tokenStr;
		handler->extractOptFirstArg((char *)args, &nameStr, &tokenStr);

		if (!tokenStr)
			return false;

		std::string p_username = strtok((char *)args, " ");

		QueryResult accname = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s';", p_username.c_str());

		if (accname)
		{

			Field *fields = accname->Fetch();
			uint32 accountId = fields[0].GetUInt32();
			uint32 token = uint32(atoi(tokenStr));

			if (Unell_Script::Unell_acctoken(accountId))
			{
				LoginDatabase.PExecute("UPDATE `account_token` SET `token`=`token`+%u WHERE (`id`='%u');", token, accountId);
				LoginDatabase.PExecute("UPDATE `token_full` SET `count` = `count`+%u WHERE `accid` = %u", token, accountId);
			}
			else
			{
				LoginDatabase.PExecute("INSERT INTO `account_token` (`id`, `token`, `refereraccid`) VALUES ('%u', '%u', '0')", accountId, token);
				LoginDatabase.PExecute("INSERT INTO `token_full`(`accid`, `accname`, `count`) VALUES (%u, '%s', %u)", accountId, p_username.c_str(), token);
			}

			QueryResult res = LoginDatabase.PQuery("SELECT token FROM account_token WHERE id = %u;", accountId);

			if (res)
			{
				Field *field = res->Fetch();
				uint32 balance = field[0].GetUInt32();
				handler->PSendSysMessage("|cffff0000# |cff14ECCFВыдача на аккаунт: |cffff0000%s|cff14ECCF количеством: |cffff0000%u |cff14ECCFтокенов.", p_username.c_str(), token);
			}
			else
			{
				handler->PSendSysMessage("|cffff0000# |cff14ECCFНа данный аккаунт первый раз выдаётся донат. Он занесён в базу донатов.");
				handler->PSendSysMessage("|cffff0000# |cff14ECCFВыдача на аккаунт: |cffff0000%s|cff14ECCF количеством: |cffff0000%u |cff14ECCFтокенов.", p_username.c_str(), token);
			}
		}
		return true;
	}
};

class NPC_Unell_CH : public CreatureScript
{
  public:
	NPC_Unell_CH() : CreatureScript("NPC_Unell_CH") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		AccountTypes gmLevel = player->GetSession()->GetSecurity();
		uint32 acclevel = uint32(gmLevel);
		uint32 accid = player->GetSession()->GetAccountId();
		player->PlayerTalkClass->ClearMenus();

		// Анонс при входе в мир
		QueryResult resflaglogin = LoginDatabase.PQuery("SELECT flag_login FROM unell_account_setting WHERE id = %u", accid);
		if (!resflaglogin)
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Оповещение о входе в мир", GOSSIP_SENDER_MAIN, 2);
		else
		{
			uint32 flaglog = resflaglogin->Fetch()->GetUInt32();

			if (flaglog == 1)
				player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Оповещение о входе в мир", GOSSIP_SENDER_MAIN, 2);

			if (flaglog == 0)
				player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Оповещение о входе в мир", GOSSIP_SENDER_MAIN, 1);
		}

		// Сообщение при входе в мир
		QueryResult resflaghello = LoginDatabase.PQuery("SELECT flag_hello FROM unell_account_setting WHERE id = %u", accid);
		if (!resflaghello)
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Приветственное сообщение при входе в мир", GOSSIP_SENDER_MAIN, 4);
		else
		{
			uint32 flaghel = resflaghello->Fetch()->GetUInt32();

			if (flaghel == 1)
				player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Приветственное сообщение при входе в мир", GOSSIP_SENDER_MAIN, 4);

			if (flaghel == 0)
				player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Приветственное сообщение при входе в мир", GOSSIP_SENDER_MAIN, 3);
		}

		// Вывод рассы при просмотре онлайна через топ команду :D
		QueryResult flag_online_race = LoginDatabase.PQuery("SELECT flag_online_race FROM unell_account_setting WHERE id = %u", accid);
		if (!flag_online_race)
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Вывод рассы при просмотре онлайна", GOSSIP_SENDER_MAIN, 6);
		else
		{
			uint32 unell_flag_online_race = flag_online_race->Fetch()->GetUInt32();

			if (unell_flag_online_race == 1)
				player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Вывод рассы при просмотре онлайна", GOSSIP_SENDER_MAIN, 6);

			if (unell_flag_online_race == 0)
				player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Вывод рассы при просмотре онлайна", GOSSIP_SENDER_MAIN, 5);
		}

		// Вывод класса при просмотре онлайна через топ команду :D
		QueryResult flag_online_class = LoginDatabase.PQuery("SELECT flag_online_class FROM unell_account_setting WHERE id = %u", accid);
		if (!flag_online_class)
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Вывод класса при просмотре онлайна", GOSSIP_SENDER_MAIN, 8);
		else
		{
			uint32 unell_flag_online_class = flag_online_class->Fetch()->GetUInt32();

			if (unell_flag_online_class == 1)
				player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Вывод класса при просмотре онлайна", GOSSIP_SENDER_MAIN, 8);

			if (unell_flag_online_class == 0)
				player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Вывод класса при просмотре онлайна", GOSSIP_SENDER_MAIN, 7);
		}

		// Вывод уровня при просмотре онлайна через топ команду :D
		QueryResult flag_online_level = LoginDatabase.PQuery("SELECT flag_online_level FROM unell_account_setting WHERE id = %u", accid);
		if (!flag_online_level)
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Вывод левела при просмотре онлайна", GOSSIP_SENDER_MAIN, 10);
		else
		{
			uint32 unell_flag_online_level = flag_online_level->Fetch()->GetUInt32();

			if (unell_flag_online_level == 1)
				player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Вывод левела при просмотре онлайна", GOSSIP_SENDER_MAIN, 10);

			if (unell_flag_online_level == 0)
				player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Вывод левела при просмотре онлайна", GOSSIP_SENDER_MAIN, 9);
		}

		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
	{
		uint32 accid = player->GetSession()->GetAccountId();
		player->PlayerTalkClass->ClearMenus();
		AccountTypes gmLevel = player->GetSession()->GetSecurity();
		uint32 acclevel = uint32(gmLevel);

		switch (action)
		{
		case 100:
			OnGossipHello(player, creature);
			break;

		case 1: // Включить оповещение
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_login FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_login`='1' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFоповещение о входе в мир");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_login`) VALUES ('%u', '1')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFоповещение о входе в мир");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 2: // Выключить оповещение

		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_login FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_login`='0' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFоповещение о входе в мир");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_login`) VALUES ('%u', '0')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFоповещение о входе в мир");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 3: // Включить оповещение unell_account_setting
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_hello FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_hello`='1' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFсообщение при входе в мир");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_hello`) VALUES ('%u', '1')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFсообщение при входе в мир");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 4: // Выключить оповещение
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_hello FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_hello`='0' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFсообщение при входе в мир");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_hello`) VALUES ('%u', '0')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFсообщение при входе в мир");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 5: // Включить вывод рассы unell_account_setting
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_online_race FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_online_race`='1' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFвывод рассы при просмотре онлайна");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_online_race`) VALUES ('%u', '1')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFвывод рассы при просмотре онлайна");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 6: // Выключить вывод рассы
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_online_race FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_online_race`='0' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFвывод рассы при просмотре онлайна");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_online_race`) VALUES ('%u', '0')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFвывод рассы при просмотре онлайна");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 7: // Включить вывод класса unell_account_setting
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_online_class FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_online_class`='1' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFвывод класса при просмотре онлайна");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_online_class`) VALUES ('%u', '1')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFвывод класса при просмотре онлайна");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 8: // Выключить вывод класса
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_online_class FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_online_class`='0' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFвывод класса при просмотре онлайна");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_online_class`) VALUES ('%u', '0')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFвывод класса при просмотре онлайна");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 9: // Включить вывод левела unell_account_setting
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_online_level FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_online_level`='1' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFвывод левела при просмотре онлайна");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_online_level`) VALUES ('%u', '1')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000включили |cff14ECCFвывод левела при просмотре онлайна");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

		case 10: // Выключить левела класса
		{
			QueryResult res = LoginDatabase.PQuery("SELECT flag_online_level FROM unell_account_setting WHERE id = %u", accid);

			if (res)
			{
				LoginDatabase.PExecute("UPDATE `unell_account_setting` SET `flag_online_level`='0' WHERE (`id`='%u')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFвывод левела при просмотре онлайна");
			}

			if (!res)
			{
				LoginDatabase.PExecute("INSERT INTO `unell_account_setting` (`id`, `flag_online_level`) VALUES ('%u', '0')", accid);
				ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000# |cff14ECCFВы |cffff0000выключили |cff14ECCFвывод левела при просмотре онлайна");
			}
		}
			player->CLOSE_GOSSIP_MENU();
			break;

			return true;
		}

		return true;
	}
};

class Unell_Visual_NPC : public CreatureScript
{
  public:
	Unell_Visual_NPC() : CreatureScript("Unell_Visual_NPC") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		player->ADD_GOSSIP_ITEM(10, "Удаление всех аур", GOSSIP_SENDER_MAIN, 100);

		if (player->HasAura(72523)) // ШМ
		{
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Тёмная Скорбь", GOSSIP_SENDER_MAIN, 1);
		}
		else
			player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Тёмная Скорбь", GOSSIP_SENDER_MAIN, 2);

		if (player->HasAura(47503)) // Сифон
		{
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Сифон жизнь", GOSSIP_SENDER_MAIN, 3);
		}
		else
			player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Сифон жизнь", GOSSIP_SENDER_MAIN, 4);

		if (player->HasAura(52619)) // Свечение
		{
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Свечение", GOSSIP_SENDER_MAIN, 5);
		}
		else
			player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Свечение", GOSSIP_SENDER_MAIN, 6);

		if (player->HasAura(22578)) // Сияние
		{
			player->ADD_GOSSIP_ITEM(10, "|cff008000[Включено]|r Сияние (чёрное)", GOSSIP_SENDER_MAIN, 7);
		}
		else
			player->ADD_GOSSIP_ITEM(10, "|cffff0000[Выключено]|r Сияние (чёрное)", GOSSIP_SENDER_MAIN, 8);

		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
	{
		ChatHandler handler(player->GetSession());

		player->PlayerTalkClass->ClearMenus();
		if (sender != GOSSIP_SENDER_MAIN)
			return true;

		switch (action)
		{

		case 100:
			player->CLOSE_GOSSIP_MENU(); // UN AURA
			player->RemoveAurasDueToSpell(72523);
			player->RemoveAurasDueToSpell(47503);
			player->RemoveAurasDueToSpell(52619);
			player->RemoveAurasDueToSpell(22578);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 С вас сняты все эффекты");
			break;

		case 1:
			player->CLOSE_GOSSIP_MENU(); // ШМ
			player->RemoveAurasDueToSpell(72523);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 С вас снят эффект |cFFFF0000Аура Тёмной Скорби");
			break;

		case 2:
			player->CLOSE_GOSSIP_MENU(); // ШМ
			player->AddAura(72523, player);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 На вас наложен эффект |cFFFF0000Аура Тёмной Скорби");
			break;

		case 3:
			player->CLOSE_GOSSIP_MENU(); // Сифон
			player->RemoveAurasDueToSpell(47503);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 С вас снят эффект |cFFFF0000Сифон жизнь");
			break;

		case 4:
			player->CLOSE_GOSSIP_MENU(); // Сифон
			player->AddAura(47503, player);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 На вас наложен эффект |cFFFF0000Сифон жизнь");
			break;

		case 5:
			player->CLOSE_GOSSIP_MENU(); // Свечение
			player->RemoveAurasDueToSpell(52619);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 С вас снят эффект |cFFFF0000Свечение");
			break;

		case 6:
			player->CLOSE_GOSSIP_MENU(); // Свечение
			player->AddAura(52619, player);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 На вас наложен эффект |cFFFF0000Свечение");
			break;

		case 7:
			player->CLOSE_GOSSIP_MENU(); // Сияние
			player->RemoveAurasDueToSpell(22578);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 С вас снят эффект |cFFFF0000Сияние");
			break;

		case 8:
			player->CLOSE_GOSSIP_MENU(); // Сияние
			player->AddAura(22578, player);
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 На вас наложен эффект |cFFFF0000Сияние");
			break;

			break;

			return true; // invalid class, something fishy
		}

		return true;
	}
};

class Unell_GM_Setting_NPC : public CreatureScript
{
  public:
	Unell_GM_Setting_NPC() : CreatureScript("Unell_GM_Setting_NPC") {}

	bool OnGossipHello(Player *player, Creature *creature)
	{
		if (player->GetSession()->GetSecurity() < 1)
		{
			player->CLOSE_GOSSIP_MENU();
			creature->MonsterWhisper("Вы не ГМ, я не могу вам помочь...", player, false);
			return true;
		}

		player->ADD_GOSSIP_ITEM(10, "Полная очистка от всех предметов", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "Одеть одеяние Гейм-мастера", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(10, "Стандартные настройки для начинающего Гейм-мастера", GOSSIP_SENDER_MAIN, 3);

		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player *player, Creature *creature, uint32 sender, uint32 action)
	{
		ChatHandler handler(player->GetSession());

		player->PlayerTalkClass->ClearMenus();

		if (sender != GOSSIP_SENDER_MAIN)
			return true;

		switch (action)
		{
		case 100:
			OnGossipHello(player, creature);
			break;

		// Полная очистка предметов
		case 1:
			player->CLOSE_GOSSIP_MENU();
			{
				for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
				for (uint8 slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
				for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
				for (uint8 slot = BANK_SLOT_ITEM_START; slot < BANK_SLOT_ITEM_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
				for (uint8 slot = BANK_SLOT_BAG_START; slot < BANK_SLOT_BAG_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
				for (uint8 slot = BUYBACK_SLOT_START; slot < BUYBACK_SLOT_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
			}
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 У вас были удалены все предметы");
			break;

		// Одеяние ГМ
		case 2:
			player->CLOSE_GOSSIP_MENU();
			{
				player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 2586, true);
				player->EquipNewItem(EQUIPMENT_SLOT_FEET, 11508, true);
				player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 12064, true);
			}
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вы были одеты в одеяние Гейм-мастера");
			break;

		// Дефолт ГМ
		case 3:
			player->CLOSE_GOSSIP_MENU();
			{
				handler.GetSession()->GetPlayer()->SetGMChat(true);
				player->SetGMVisible(true);
				player->SetGameMaster(true);
				player->UpdateTriggerVisibility();

				for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
					player->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);

				player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 2586, true);
				player->EquipNewItem(EQUIPMENT_SLOT_FEET, 11508, true);
				player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 12064, true);
			}
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вы выглядите как Гейм-мастер.");
			handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вам включен ГМ чат, включена невидимость для игроков, включен ГМ мод.");
			break;

			return true; // invalid class, something fishy
		}
		return true;
	}
};

class Unell_Item_Oplot_TP : public ItemScript
{
  public:
	Unell_Item_Oplot_TP() : ItemScript("Unell_Item_Oplot_TP") {}

	bool OnUse(Player *player, Item *item, SpellCastTargets const & /*targets*/) // Any hook here
	{
		ChatHandler handler(player->GetSession());

		if (player->IsInCombat() || player->duel || player->IsInFlight() || player->GetMap()->IsBattlegroundOrArena() || player->HasStealthAura() || player->HasFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH) || player->isDead())
		{
			handler.SendSysMessage(LANG_PREMIUM_CANT_DO);
			handler.SetSentErrorMessage(true);
			return false;
		}

		switch (player->getClass())
		{
		case CLASS_DEATH_KNIGHT:
			// oldclass = 6;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 6");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_DRUID:
			// oldclass = 11;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 11");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_HUNTER:
			// oldclass = 3;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 3");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_MAGE:
			// oldclass = 8;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 8");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_PALADIN:
			// oldclass = 2;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 2");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_PRIEST:
			// oldclass = 5;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 5");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_ROGUE:
			// oldclass = 4;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 4");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_SHAMAN:
			// oldclass = 7;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 7");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_WARLOCK:
			// oldclass = 9;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 9");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;
		case CLASS_WARRIOR:
			// oldclass = 1;
			{
				QueryResult result = WorldDatabase.PQuery("SELECT x, y, z, o, map FROM unell_tp_oplot WHERE id = 1");
				if (result)
				{
					float x, y, z, o;
					uint32 map;

					Field *fields = result->Fetch();
					x = fields[0].GetFloat();
					y = fields[1].GetFloat();
					z = fields[2].GetFloat();
					o = fields[3].GetFloat();
					map = fields[4].GetUInt32();

					player->TeleportTo(map, x, y, z, o);
					player->SetPhaseMask(1, true);
				}
				else
				{
					handler.PSendSysMessage("|cFFFF0000#|r Невозможно телепортироваться в оплот вашего класса!");
				}
			}
			break;

			return true;
		}

		return true;
	}
};

class Unell_Item_EasyStart : public ItemScript
{
  public:
	Unell_Item_EasyStart() : ItemScript("Unell_Item_EasyStart") {}

	bool OnUse(Player *player, Item *item, SpellCastTargets const & /*targets*/) // Any hook here
	{
		ChatHandler handler(player->GetSession());

		if (sConfigMgr->GetBoolDefault("Unell.EasyStart.Enable", false))
		{
			uint32 itemid_conf = sConfigMgr->GetIntDefault("Unell.EasyStart.ItemID", 312001);
			uint32 gold_conf = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.Gold", 1000);
			uint32 arena_conf = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.ArenaPoint", 1000);
			uint32 honor_conf = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.HonorPoint", 1000);

			uint32 spellid_100 = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.100.Mount.SpellID", 1000);
			uint32 spellid_280 = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.280.Mount.SpellID", 1000);

			uint32 Gold_done = gold_conf * 10000;

			if (sConfigMgr->GetBoolDefault("Unell.EasyStart.Reward.Start.Set", true))
			{
				uint32 space_count = Unell_Script::Unell_Space_Count(player);

				switch (player->getClass())
				{
				case CLASS_DEATH_KNIGHT:
				{
					if (space_count >= 10)
					{
						player->AddItem(39617, 1);
						player->AddItem(39618, 1);
						player->AddItem(39619, 1);
						player->AddItem(39620, 1);
						player->AddItem(39621, 1);

						player->AddItem(39623, 1);
						player->AddItem(39625, 1);
						player->AddItem(39626, 1);
						player->AddItem(39627, 1);
						player->AddItem(39624, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 10 - space_count);
						return false;
					}
				}
				break;
				case CLASS_DRUID:
				{
					if (space_count >= 15)
					{
						player->AddItem(39557, 1);
						player->AddItem(39553, 1);
						player->AddItem(39555, 1);
						player->AddItem(39554, 1);
						player->AddItem(39556, 1);

						player->AddItem(39545, 1);
						player->AddItem(39544, 1);
						player->AddItem(39548, 1);
						player->AddItem(39546, 1);
						player->AddItem(39547, 1);

						player->AddItem(39543, 1);
						player->AddItem(39531, 1);
						player->AddItem(39539, 1);
						player->AddItem(39542, 1);
						player->AddItem(39538, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 15 - space_count);
						return false;
					}
				}
				break;
				case CLASS_HUNTER:
				{
					if (space_count >= 5)
					{
						player->AddItem(39582, 1);
						player->AddItem(39578, 1);
						player->AddItem(39580, 1);
						player->AddItem(39581, 1);
						player->AddItem(39579, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 5 - space_count);
						return false;
					}
				}
				break;
				case CLASS_MAGE:
				{
					if (space_count >= 5)
					{
						player->AddItem(39491, 1);
						player->AddItem(39495, 1);
						player->AddItem(39493, 1);
						player->AddItem(39492, 1);
						player->AddItem(39494, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 5 - space_count);
						return false;
					}
				}
				break;
				case CLASS_PALADIN:
				{
					if (space_count >= 15)
					{
						player->AddItem(39633, 1);
						player->AddItem(39634, 1);
						player->AddItem(39635, 1);
						player->AddItem(39636, 1);
						player->AddItem(39637, 1);

						player->AddItem(39638, 1);
						player->AddItem(39639, 1);
						player->AddItem(39640, 1);
						player->AddItem(39641, 1);
						player->AddItem(39642, 1);

						player->AddItem(39632, 1);
						player->AddItem(39630, 1);
						player->AddItem(39628, 1);
						player->AddItem(39631, 1);
						player->AddItem(39629, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 15 - space_count);
						return false;
					}
				}
				break;
				case CLASS_PRIEST:
				{
					if (space_count >= 10)
					{
						player->AddItem(39521, 1);
						player->AddItem(39530, 1);
						player->AddItem(39529, 1);
						player->AddItem(39528, 1);
						player->AddItem(39523, 1);

						player->AddItem(39514, 1);
						player->AddItem(39519, 1);
						player->AddItem(39517, 1);
						player->AddItem(39515, 1);
						player->AddItem(39518, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 10 - space_count);
						return false;
					}
				}
				break;
				case CLASS_ROGUE:
				{
					if (space_count >= 5)
					{
						player->AddItem(39558, 1);
						player->AddItem(39560, 1);
						player->AddItem(39561, 1);
						player->AddItem(39564, 1);
						player->AddItem(39565, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 5 - space_count);
						return false;
					}
				}
				break;
				case CLASS_SHAMAN:
				{
					if (space_count >= 15)
					{
						player->AddItem(39597, 1);
						player->AddItem(39602, 1);
						player->AddItem(39601, 1);
						player->AddItem(39604, 1);
						player->AddItem(39603, 1);

						player->AddItem(39593, 1);
						player->AddItem(39592, 1);
						player->AddItem(39594, 1);
						player->AddItem(39595, 1);
						player->AddItem(39596, 1);

						player->AddItem(39591, 1);
						player->AddItem(39583, 1);
						player->AddItem(39589, 1);
						player->AddItem(39590, 1);
						player->AddItem(39588, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 15 - space_count);
						return false;
					}
				}
				break;
				case CLASS_WARLOCK:
				{
					if (space_count >= 5)
					{
						player->AddItem(39496, 1);
						player->AddItem(39500, 1);
						player->AddItem(39498, 1);
						player->AddItem(39497, 1);
						player->AddItem(39499, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 5 - space_count);
						return false;
					}
				}
				break;
				case CLASS_WARRIOR:
				{
					if (space_count >= 10)
					{
						player->AddItem(39606, 1);
						player->AddItem(39605, 1);
						player->AddItem(39607, 1);
						player->AddItem(39609, 1);
						player->AddItem(39608, 1);

						player->AddItem(39611, 1);
						player->AddItem(39610, 1);
						player->AddItem(39622, 1);
						player->AddItem(39612, 1);
						player->AddItem(39613, 1);
					}
					else
					{
						handler.PSendSysMessage("|cFFFF0000#|r Вам не хватает %u свободных слотов в сумках", 10 - space_count);
						return false;
					}
				}
				break;
				}
				handler.PSendSysMessage("|cFFFF0000#|r Вы получили начальный сет");
			}

			if (Gold_done > 0)
			{
				player->ModifyMoney(Gold_done);
				handler.PSendSysMessage("|cFFFF0000#|r Вы получили|r %u |cFFFF0000золота", gold_conf);
			}

			if (arena_conf > 0)
			{
				player->ModifyArenaPoints(arena_conf);
				handler.PSendSysMessage("|cFFFF0000#|r Вы получили|r %u |cFFFF0000очков арены", arena_conf);
			}

			if (honor_conf > 0)
			{
				player->ModifyHonorPoints(honor_conf);
				handler.PSendSysMessage("|cFFFF0000#|r Вы получили|r %u |cFFFF0000очков чести", honor_conf);
			}

			if (sConfigMgr->GetBoolDefault("Unell.EasyStart.Reward.GiveLevel.Enable", false))
			{
				uint32 level_conf = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.GiveLevel.NewLevel", 80);
				player->GiveLevel(level_conf);
			}

			if (sConfigMgr->GetBoolDefault("Unell.EasyStart.Reward.GiveLevel.Enable", false))
			{
				uint32 level_conf = sConfigMgr->GetIntDefault("Unell.EasyStart.Reward.GiveLevel.NewLevel", 80);
				player->GiveLevel(level_conf);
			}

			if (sConfigMgr->GetBoolDefault("Unell.EasyStart.Reward.100.Mount.Enable", false))
				player->learnSpell(spellid_100);

			if (sConfigMgr->GetBoolDefault("Unell.EasyStart.Reward.280.Mount.Enable", false))
				player->learnSpell(spellid_280);

			player->DestroyItemCount(itemid_conf, 1, true);
		}
		else
			handler.PSendSysMessage("|cFFFF0000#|r Быстрый старт вылючен!");

		return true;
	}
};

void AddSC_Unell_Custom()
{
	new Unell_commandscript();
	new NPC_Unell_CH();
	new Unell_Visual_NPC();
	new Unell_Item_Oplot_TP();
	new Unell_GM_Setting_NPC();
	new Unell_Item_EasyStart();
}