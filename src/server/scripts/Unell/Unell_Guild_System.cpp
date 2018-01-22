#include "Unell_Script.h"

void static UpdateLevel(Player* player)
{
	char msg[2048];
	uint32 guild = player->GetGuildId();
	QueryResult result = CharacterDatabase.PQuery("SELECT level, xp FROM guild_level WHERE guild = %u", guild);
	if (result)
	{
		Field *fields = result->Fetch();
		uint16 level = fields[0].GetUInt16();
		uint32 xp = fields[1].GetUInt32();

		QueryResult maxlevel = CharacterDatabase.PQuery("SELECT max(level) FROM guild_xp_table");
		uint32 maxlvl = maxlevel->Fetch()->GetUInt32();
		QueryResult maxexp = CharacterDatabase.PQuery("SELECT xp FROM guild_xp_table WHERE level = %u", maxlvl);
		uint32 maxxp = maxexp->Fetch()->GetUInt32();

		QueryResult knowLevel = CharacterDatabase.PQuery("SELECT level FROM guild_xp_table WHERE xp > %u", xp);
		if (knowLevel)
		{
			Field *fs = knowLevel->Fetch();
			uint16 gLevel = fs[0].GetUInt16();

			if (level < gLevel)
			{
				if (gLevel == maxlvl)
				{
					snprintf(msg, 250, "|cffff0000[Новый уровень гильдии]:|r |cff6C8CD5Гильдия достигла максимального уровня.");
					sWorld->SendGuildText(guild, msg);
				}
				else
				{
					snprintf(msg, 250, "|cffff0000[Новый уровень гильдии]:|r |cff6C8CD5Гильдия достигла %u-го уровня.", gLevel);
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 2)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Передвижение в форме духа 150%%");
					sWorld->SendGuildText(guild, msg);
				}
				
				if (gLevel == 3)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Получаемый опыт +5%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 4)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Получаемые очки чести +5%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 5)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Передвижение в форме духа 200%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 6)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Получаемый опыт +10%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 7)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Получаемые очки чести +10%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 8)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Передвижение в форме духа 250%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 9)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Получаемый опыт +20%%");
					sWorld->SendGuildText(guild, msg);
				}

				if (gLevel == 10)
				{
					snprintf(msg, 250, "|cffff0000 - Открыто:|r |cff6C8CD5Получаемые очки чести +15%%");
					sWorld->SendGuildText(guild, msg);
				}
			}
			CharacterDatabase.PQuery("UPDATE guild_level SET level = %u WHERE guild = %u", gLevel, guild);
		}

		if (xp > maxxp)
			CharacterDatabase.PQuery("UPDATE `guild_level` SET `xp`='%u' WHERE (`guild`='%u')", maxxp, guild);
		else
			CharacterDatabase.PQuery("UPDATE `guild_level` SET `xp`='%u' WHERE (`guild`='%u')", xp, guild);
	}

	//sGuildMgr->LoadGuilds();
}

void static ReplaceColorList(Player* player, Creature* creature) 
{
	player->PlayerTalkClass->ClearMenus();
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет на Красный", GOSSIP_SENDER_MAIN, 3);
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет на Синий", GOSSIP_SENDER_MAIN, 4);
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет на Чёрный", GOSSIP_SENDER_MAIN, 5);
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет на Белый", GOSSIP_SENDER_MAIN, 6);
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет на Зелёный", GOSSIP_SENDER_MAIN, 7);
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет на Желтый", GOSSIP_SENDER_MAIN, 8);
	player->SEND_GOSSIP_MENU(1, creature->GetGUID());
}

void static ReplaceColor(Player* player, Creature* creature, uint32 color)
{
	char msg[2048];
	uint32 guild = player->GetGuildId();

	switch(color)
	{
		case 1:
			CharacterDatabase.PExecute("UPDATE guild_level SET color = '|cffFF0000' WHERE guild = %u", player->GetGuildId());
			{
				snprintf(msg, 250, "|cffff0000[Смена цвета гильдии]:|r |cff6C8CD5Смена названия цвета гильдии на|r |cffFF0000Красный");
				sWorld->SendGuildText(guild, msg);
			}
			break;
		case 2:
			CharacterDatabase.PExecute("UPDATE guild_level SET color = '|cff0000FF' WHERE guild = %u", player->GetGuildId());
			{
				snprintf(msg, 250, "|cffff0000[Смена цвета гильдии]:|r |cff6C8CD5Смена названия цвета гильдии на|r |cff0000FFСиний");
				sWorld->SendGuildText(guild, msg);
			}
			break;
		case 3:
			CharacterDatabase.PExecute("UPDATE guild_level SET color = '|cff000000' WHERE guild = %u", player->GetGuildId());
			{
				snprintf(msg, 250, "|cffff0000[Смена цвета гильдии]:|r |cff6C8CD5Смена названия цвета гильдии на|r |cff000000Чёрный");
				sWorld->SendGuildText(guild, msg);
			}
			break;
		case 4:
			CharacterDatabase.PExecute("UPDATE guild_level SET color = '|cffFFFFFF' WHERE guild = %u", player->GetGuildId());
			{
				snprintf(msg, 250, "|cffff0000[Смена цвета гильдии]:|r |cff6C8CD5Смена названия цвета гильдии на|r |cffFFFFFFБелый");
				sWorld->SendGuildText(guild, msg);
			}
			break;
		case 5:
			CharacterDatabase.PExecute("UPDATE guild_level SET color = '|cff00FF00' WHERE guild = %u", player->GetGuildId());
			{
				snprintf(msg, 250, "|cffff0000[Смена цвета гильдии]:|r |cff6C8CD5Смена названия цвета гильдии на|r |cff00FF00Зелёный");
				sWorld->SendGuildText(guild, msg);
			}
			break;
		case 6:
			CharacterDatabase.PExecute("UPDATE guild_level SET color = '|cffFFFF00' WHERE guild = %u", player->GetGuildId());
			{
				snprintf(msg, 250, "|cffff0000[Смена цвета гильдии]:|r |cff6C8CD5Смена названия цвета гильдии на|r |cffFFFF00Желтый");
				sWorld->SendGuildText(guild, msg);
			}
			break;
	}
	player->CLOSE_GOSSIP_MENU();
}

void static Selection_Invested(Player* player, Creature* creature, char const* code)
{
	ChatHandler handler(player->GetSession());
	std::string NameLink = ChatHandler(player->GetSession()).playerLink(player->GetName());
	std::string name = player->GetName();
	uint32 guild = player->GetGuildId();
	char msg[2048];

	if (!guild)
	{
		player->GetSession()->SendNotification("Вы не состоите в гильдии!");
		player->CLOSE_GOSSIP_MENU();
		return;
	}

	int32 exp_point = atoi(code);
	uint32 coutitem = player->GetItemCount(120001);
	char const* item_name = Unell_Script::Unell_Item_Locale(player, 120001);
	uint32 iditem = 120001;

	if (!player->HasItemCount(120001, exp_point))
	{
		uint32 lacks_item = exp_point - coutitem;
		handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Вам не хватает|r %u |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", lacks_item, iditem, item_name);
		player->CLOSE_GOSSIP_MENU();
	}
	else
	{
		player->DestroyItemCount(120001, exp_point, true);
		CharacterDatabase.PQuery("UPDATE guild_level SET xp = xp+%u WHERE guild = %u", exp_point, guild);

		QueryResult result = CharacterDatabase.PQuery("SELECT name FROM guild_level_invested WHERE guild = %u AND name = '%s'", guild, name.c_str());
		if (result)
			CharacterDatabase.PExecute("UPDATE `guild_level_invested` SET `exp_point`= exp_point + %u WHERE (`guild`='%u') AND (`name`='%s')", exp_point, guild, name.c_str());
		else
			CharacterDatabase.PExecute("INSERT INTO `guild_level_invested` (`guild`, `name`, `exp_point`) VALUES ('%u', '%s', '%u')", guild, name.c_str(), exp_point);

		snprintf(msg, 2048, "|cffff0000[Повышение опыта]:|r |cff14ECCF%s|r |cff6C8CD5добавил|r |cff14ECCF%u|r |cff6C8CD5очков опыта|r", NameLink.c_str(), exp_point);
		sWorld->SendGuildText(guild, msg);		
		player->CLOSE_GOSSIP_MENU();
	}
	UpdateLevel(player);
}

void static Full_Invested(Player* player, Creature* creature)
{
	ChatHandler handler(player->GetSession());
	std::string NameLink = ChatHandler(player->GetSession()).playerLink(player->GetName());
	std::string name = player->GetName();
	uint32 guild = player->GetGuildId();
	char const* item_name = Unell_Script::Unell_Item_Locale(player, 120001);
	uint32 iditem = 120001;
	uint32 coutitem = player->GetItemCount(120001);
	char msg[2048];

	if (!guild)
	{
		player->GetSession()->SendNotification("Вы не состоите в гильдии!");
		player->CLOSE_GOSSIP_MENU();
		return;
	}

	if (coutitem == 0)
	{
		handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 У вас нет |r |cffffffff|Hitem:%d:0:0:0:0:0:0:0:0|h[%s]|h|r", iditem, item_name);
		return;
	}

	player->DestroyItemCount(120001, coutitem, true);
	CharacterDatabase.PQuery("UPDATE guild_level SET xp = xp+%u WHERE guild = %u", coutitem, guild);

	QueryResult result = CharacterDatabase.PQuery("SELECT name FROM guild_level_invested WHERE guild = %u AND name = '%s'", guild, name.c_str());
	if (result)
		CharacterDatabase.PExecute("UPDATE `guild_level_invested` SET `exp_point`= exp_point + %u WHERE (`guild`='%u') AND (`name`='%s')", coutitem, guild, name.c_str());
	else
		CharacterDatabase.PExecute("INSERT INTO `guild_level_invested` (`guild`, `name`, `exp_point`) VALUES ('%u', '%s', '%u')", guild, name.c_str(), coutitem);

	snprintf(msg, 2048, "|cffff0000[Повышение опыта]:|r |cff14ECCF%s|r |cff6C8CD5добавил|r |cff14ECCF%u|r |cff6C8CD5очков опыта|r", NameLink.c_str(), coutitem);
	sWorld->SendGuildText(guild, msg);
	player->CLOSE_GOSSIP_MENU();
	UpdateLevel(player);
}

void static GuildInfo(Player* player) 
{
	if (!player->GetGuildId()) 
	{
		player->GetSession()->SendNotification("Вы не состоите в гильдии!");
		player->CLOSE_GOSSIP_MENU();
		return;
	}
	UpdateLevel(player);	
	ChatHandler handler(player->GetSession());	
	uint32 guild = player->GetGuildId();
	QueryResult result = CharacterDatabase.PQuery("SELECT level, xp FROM guild_level WHERE guild = %u", guild);
	
	if (result) 
	{
		Field *fields = result->Fetch();
		uint16 level = fields[0].GetUInt16();
		uint32 xp = fields[1].GetUInt32();
		
		ChatHandler(player->GetSession()).PSendSysMessage("|cFFFF0000# |cfff4b25eУровень вашей гильдии:|r |cfffcedbb%u|r", level);
		ChatHandler(player->GetSession()).PSendSysMessage("|cFFFF0000# |cfff4b25eПрогресс уровня вашей гильдии:|r |cfffcedbb%u очков опыта|r", xp);

		QueryResult result1 = CharacterDatabase.PQuery("SELECT xp FROM guild_xp_table WHERE level = %u", level);
		if (result1) 
		{
			Field *fields = result1->Fetch();
			uint32 reqXp = fields[0].GetUInt32();
			uint32 ReqXp = reqXp-xp;
		
			if (level < 10)
				handler.PSendSysMessage("|cFFFF0000# |cfff4b25eДо %u-го уровня гильдии осталось накопить:|r |cfffcedbb%u очков опыта|r", level+1, ReqXp);
			else 
				handler.PSendSysMessage("|cFFFF0000# |cfff4b25eВаша гильдия имеет максимальный уровень!|r");
		}
	}
		
	player->CLOSE_GOSSIP_MENU();
}

void static GuildInfo_Reward(Player* player)
{
	if (!player->GetGuildId())
	{
		player->GetSession()->SendNotification("Вы не состоите в гильдии!");
		player->CLOSE_GOSSIP_MENU();
		return;
	}
	ChatHandler handler(player->GetSession());
	uint32 guild = player->GetGuildId();
	QueryResult result = CharacterDatabase.PQuery("SELECT level, xp FROM guild_level WHERE guild = %u", guild);

	if (result)
	{
		Field *fields = result->Fetch();
		uint16 level = fields[0].GetUInt16();

		handler.PSendSysMessage("|cFFFF0000# |cfff4b25eУровень вашей гильдии:|r |cfffcedbb%u|r|cfff4b25e. Доступные награды:|r", level);

		if (level == 1)
			handler.PSendSysMessage("|cFFFF0000#|r |cfff4b25eНет доступных наград|r");
		else
		{
			QueryResult result1 = CharacterDatabase.PQuery("SELECT rate_ghost_ms, rate_xp, rate_honor FROM guild_level_reward WHERE level = %u", level);
			if (result1)
			{
				uint32 full_ghost_ms, full_xp, full_honor;

				Field *fields = result1->Fetch();
				float rate_ghost_ms = fields[0].GetFloat();
				float rate_xp = fields[1].GetFloat();
				float rate_honor = fields[2].GetFloat();

				full_ghost_ms = rate_ghost_ms * 100;
				full_xp = rate_xp * 100;
				full_honor = rate_honor * 100;

				handler.PSendSysMessage("|cFFFF0000# |cff6C8CD5Передвижение в форме духа:|r %u%%", full_ghost_ms);
				handler.PSendSysMessage("|cFFFF0000# |cff6C8CD5Получаемый опыт:|r %u%%", full_xp);
				handler.PSendSysMessage("|cFFFF0000# |cff6C8CD5Получаемые очки чести:|r %u%%", full_honor);
			}
		}	
	}

	player->CLOSE_GOSSIP_MENU();
}

void static Invested(Player* player, Creature* creature)
{
	player->PlayerTalkClass->ClearMenus();
	player->ADD_GOSSIP_ITEM_EXTENDED(10, "|TInterface/ICONS/Achievement_BG_kill_flag_carrierEOS:32:32:-18:0|tВложить очки опыта выборочно", GOSSIP_SENDER_MAIN, 1000, "Введите количество очков опыта для вложения", 0, true);
	player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Achievement_BG_kill_flag_carrierEOS:32:32:-18:0|tВложить все очки опыта", GOSSIP_SENDER_MAIN, 11);
	player->SEND_GOSSIP_MENU(1, creature->GetGUID());
}

void static Settings(Player* player, Creature* creature)
{
	player->PlayerTalkClass->ClearMenus();
	player->ADD_GOSSIP_ITEM(10, "Сменить цвет названия гильдии", GOSSIP_SENDER_MAIN, 2);
	player->SEND_GOSSIP_MENU(1, creature->GetGUID());
}

void static Top_Exp(Player* player, Creature* creature)
{
	player->PlayerTalkClass->ClearMenus();
	ChatHandler handler(player->GetSession());
	uint32 guild = player->GetGuildId();	
	uint32 step = 1;

	QueryResult result = CharacterDatabase.PQuery("SELECT name, exp_point FROM guild_level_invested WHERE exp_point > 0 AND guild = %u ORDER BY exp_point DESC LIMIT 15", guild);
	if (result)
	{
		player->ADD_GOSSIP_ITEM(4, "Топ вложивших:", GOSSIP_SENDER_MAIN, 0);
		do
		{
			Field* fields = result->Fetch();
			std::string name = fields[0].GetString();
			uint32 exp_point = fields[1].GetUInt32();

			std::stringstream buffer;
			buffer << step << ". |cff790C06" << name << "|r  вложил |cFF1E90FF" << exp_point << "|r очков опыта|r";
			player->ADD_GOSSIP_ITEM(4, buffer.str(), GOSSIP_SENDER_MAIN, 0);
			++step;

		} while (result->NextRow());
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());
	}
	if (!result)
	{
		player->CLOSE_GOSSIP_MENU();
		handler.PSendSysMessage("|cFFFF0000#|cff6C8CD5 Ещё никто не вкладывал |cFFFF0000Босс Монетки");
	}
}

class npc_guild_level : public CreatureScript
{
    public: npc_guild_level() : CreatureScript("npc_guild_level") {}

	bool OnGossipHello(Player* player, Creature* creature) 
	{
		player->PlayerTalkClass->ClearMenus();
		uint32 guild = player->GetGuildId();

		if (!guild) 
		{
			player->CLOSE_GOSSIP_MENU();
			return false;
		}
		
		QueryResult result	= CharacterDatabase.PQuery("SELECT level, xp FROM guild_level WHERE guild = %u", guild);
		uint32 level		= result->Fetch()->GetUInt16();
		uint32 max_level	= Unell_Script::Unell_max_guild_level();

		player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Spell_Magic_ManaGain:32:32:-18:0|tИнформация о моей гильдии", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Spell_Magic_ManaGain:32:32:-18:0|tИнформация о наградах", GOSSIP_SENDER_MAIN, 13);
		if (player->GetRank() == 0)
		player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Temp:32:32:-18:0|tНастройки гильдии", GOSSIP_SENDER_MAIN, 9);
		if (level < max_level)
			player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Achievement_BG_kill_flag_carrierEOS:32:32:-18:0|tПожертвование для гильдии", GOSSIP_SENDER_MAIN, 10);
		player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Temp:32:32:-18:0|tТоп вложивших в гильдию", GOSSIP_SENDER_MAIN, 12);
		player->ADD_GOSSIP_ITEM(10, "|TInterface/ICONS/Spell_ChargeNegative:32:32:-18:0|tВыход", GOSSIP_SENDER_MAIN, 100);
		player->SEND_GOSSIP_MENU(1, creature->GetGUID());

		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) 
	{
		switch (action) 
		{
			case 100: // Выход
				player->CLOSE_GOSSIP_MENU();
				break;
			case 1: // Информация о гильдии
				GuildInfo(player);
				break;				
			case 2: // Смена цвета гильдии
				ReplaceColorList(player, creature);
				break;
			case 3: // Красный цвет ги
				ReplaceColor(player, creature, 1);
				break;
			case 4: // Синий цвет ги
				ReplaceColor(player, creature, 2);
				break;
			case 5: // Чёрный цвет ги
				ReplaceColor(player, creature, 3);
				break;
			case 6: // Белый цвет ги
				ReplaceColor(player, creature, 4);
				break;
			case 7: // Зелёный цвет ги
				ReplaceColor(player, creature, 5);
				break;
			case 8: // Жёлтый цвет ги
				ReplaceColor(player, creature, 6);
				break;
			case 9: // Настройки
				Settings(player, creature);
				break;
			case 10: // Вкладка вклада опыта
				Invested(player, creature);
				break;
			case 11: // Вложить весь опыт
				Full_Invested(player, creature);
				break;
			case 12: // Топ вложивших
				Top_Exp(player, creature);
				break;
			case 13: // Информация о наградах
				GuildInfo_Reward(player);
				break;
		}

		return true;
	}

	bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, char const* code)
	{
		switch (action)
		{
			case 1000:
				Selection_Invested(player, creature, code);
				break;
		}
		return true;
	}
};

class guildMasterChat : public PlayerScript
{
public:
        guildMasterChat() : PlayerScript("guildMasterChat") {}
 
        void OnChat(Player* player, uint32 /*type*/, uint32 lang, std::string& msg, Guild* guild)
        {
			if (player->GetRank() == 0) msg = "|cFFFFD700" + msg + "|r";
        }		
};

class Unell_Guild_Reward : public PlayerScript
{
	public: Unell_Guild_Reward() : PlayerScript("Unell_Guild_Reward") { }

	void OnGiveHonorPoints(Player* player, float& points, float& bonusPoints, Unit*) override
	{
		uint32 guild = player->GetGuildId();
		
		if (!guild || points < 0.01f)
			return;
		
		QueryResult db_level = CharacterDatabase.PQuery("SELECT level FROM `guild_level` WHERE `guild` = '%u'", guild);
		if (db_level)
		{
			uint32 level = db_level->Fetch()->GetInt32();
			QueryResult db_reward = CharacterDatabase.PQuery("SELECT rate_honor FROM guild_level_reward WHERE `level` = '%u'", level);

			if (db_reward)
			{
				float rate = db_reward->Fetch()->GetFloat();

				if (rate > 0.01f)
					points *= rate;
			}
		}
	}	
};

void AddSC_Unell_Guild_System()
{
	new npc_guild_level();
	new guildMasterChat();
	new Unell_Guild_Reward();
}