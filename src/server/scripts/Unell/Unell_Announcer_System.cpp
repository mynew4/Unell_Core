#include "Unell_Script.h"

class Boss_Announcer : public PlayerScript
{
  public:
	Boss_Announcer() : PlayerScript("Boss_Announcer") {}

	void OnCreatureKill(Player *player, Creature *boss)
	{
		if (sConfigMgr->GetBoolDefault("Unell.Boss.Announcer", true))
		{
			if (boss->isWorldBoss() && !boss->GetInstanceId())
			{
				char msg[250];
				ChatHandler handler(player->GetSession());
				std::string NameLink = ChatHandler(player->GetSession()).GetNameLink(player);
				uint32 Entry = boss->GetEntry();
				CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
				CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
				char const *crename = NULL;
				if (CreatureLocale)
					crename = CreatureLocale->Name[handler.GetSessionDbcLocale()].c_str();
				if ((!crename || !*crename) && CreatureTemplate)
					crename = CreatureTemplate->Name.c_str();
				if (!crename)
					crename = "Unknown creature";

				snprintf(msg, 250, "|cFFFF0000[Босс Анонсер]: |cff6C8CD5Игрок |cff14ECCF%s |cff6C8CD5и его группа убили мирового босса |cff14ECCF%s|r", NameLink.c_str(), crename);
				sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			}
		}
	}

	void OnPlayerKilledByCreature(Creature *boss, Player *player)
	{
		if (sConfigMgr->GetBoolDefault("Unell.Boss.Announcer.Player", true))
		{
			if (boss->isWorldBoss() && !boss->GetInstanceId())
			{
				char msg[250];
				ChatHandler handler(player->GetSession());
				std::string NameLink = ChatHandler(player->GetSession()).GetNameLink(player);
				uint32 Entry = boss->GetEntry();
				CreatureTemplate const *CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
				CreatureLocale const *CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
				char const *crename = NULL;
				if (CreatureLocale)
					crename = CreatureLocale->Name[handler.GetSessionDbcLocale()].c_str();
				if ((!crename || !*crename) && CreatureTemplate)
					crename = CreatureTemplate->Name.c_str();
				if (!crename)
					crename = "Unknown creature";

				snprintf(msg, 250, "|cFFFF0000[Босс Анонсер]: |cff6C8CD5Мировой босс |cff14ECCF%s |cff6C8CD5убил игрока |cff14ECCF%s|r", crename, NameLink.c_str());
				sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			}
		}
	}
};

class gm_announce : public PlayerScript
{
  public:
	gm_announce() : PlayerScript("gm_announce") {}

	void OnLogin(Player *player)
	{
		ChatHandler handler(player->GetSession());
		std::string NameLink = ChatHandler(player->GetSession()).GetNameLink(player);
		uint32 accId = player->GetSession()->GetAccountId();
		std::string os = Unell_Script::Unell_InfoOS(accId);
		std::string gmlvl;

		if (sConfigMgr->GetBoolDefault("Unell.Announce.Login.Enable", false))
		{
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

			if (player->GetSession()->GetSecurity() >= 1 && sConfigMgr->GetBoolDefault("Unell.Announce.Login.GM", true))
			{
				if (os == "OSX")
				{
					if (!sConfigMgr->GetBoolDefault("Unell.Announce.Login.GM.OnlyGM", true))
						sWorld->SendWorldText(UNELL_LANG_ANNOUNCE_GM_ENTER_PHONE, gmlvl.c_str(), NameLink.c_str());
					else
						sWorld->SendGMText(UNELL_LANG_ANNOUNCE_GM_ENTER_PHONE, gmlvl.c_str(), NameLink.c_str());
				}
				else
				{
					if (!sConfigMgr->GetBoolDefault("Unell.Announce.Login.GM.OnlyGM", true))
						sWorld->SendWorldText(UNELL_LANG_ANNOUNCE_GM_ENTER, gmlvl.c_str(), NameLink.c_str());
					else
						sWorld->SendGMText(UNELL_LANG_ANNOUNCE_GM_ENTER, gmlvl.c_str(), NameLink.c_str());
				}
			}
			else if (sConfigMgr->GetBoolDefault("Unell.Announce.Login.Vip.Player", true) && player->GetSession()->GetSecurity() == 0)
			{
				if (player->GetSession()->IsPremium())
				{
					if (os == "OSX")
					{
						if (!sConfigMgr->GetBoolDefault("Unell.Announce.Login.GM.OnlyGM", true))
							sWorld->SendWorldText(UNELL_LANG_ANNOUNCE_PLAYER_VIP_ENTER_PHONE, NameLink.c_str());
						else
							sWorld->SendGMText(UNELL_LANG_ANNOUNCE_PLAYER_VIP_ENTER_PHONE, NameLink.c_str());
					}
					else
					{
						if (!sConfigMgr->GetBoolDefault("Unell.Announce.Login.GM.OnlyGM", true))
							sWorld->SendWorldText(UNELL_LANG_ANNOUNCE_PLAYER_VIP_ENTER, NameLink.c_str());
						else
							sWorld->SendGMText(UNELL_LANG_ANNOUNCE_PLAYER_VIP_ENTER, NameLink.c_str());
					}
				}
			}
			else
				return;
		}
	}

	void OnLogout(Player *player)
	{
		ChatHandler handler(player->GetSession());
		std::string NameLink = handler.GetNameLink(player);
		std::string gmlvl;

		if (sConfigMgr->GetBoolDefault("Unell.Announce.Logout.Enable", false))
		{
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

			if (player->GetSession()->GetSecurity() >= 1 && sConfigMgr->GetBoolDefault("Unell.Announce.Logout.GM", true))
			{
				if (!sConfigMgr->GetBoolDefault("Unell.Announce.Logout.GM.OnlyGM", true))
					sWorld->SendWorldText(UNELL_LANG_ANNOUNCE_GM_LOGOUT, gmlvl.c_str(), NameLink.c_str());
				else
					sWorld->SendGMText(UNELL_LANG_ANNOUNCE_GM_LOGOUT, gmlvl.c_str(), NameLink.c_str());
			}
			else if (sConfigMgr->GetBoolDefault("Unell.Announce.Logout.Vip.Player", true) && player->GetSession()->GetSecurity() == 0)
			{
				if (player->GetSession()->IsPremium())
				{
					if (!sConfigMgr->GetBoolDefault("Unell.Announce.Logout.GM.OnlyGM", true))
						sWorld->SendWorldText(UNELL_LANG_ANNOUNCE_PLAYER_VIP_LOGOUT, NameLink.c_str());
					else
						sWorld->SendGMText(UNELL_LANG_ANNOUNCE_PLAYER_VIP_LOGOUT, NameLink.c_str());
				}
			}
			else
				return;
		}
		
	}
};

class player_announce : public PlayerScript
{
  public:
	player_announce() : PlayerScript("player_announce") {}

	void OnLogin(Player *player)
	{
		char msg[250];
		std::string NameLink = ChatHandler(player->GetSession()).GetNameLink(player);
		uint32 playeronline = sWorld->GetPlayerCount();

		bool Penter = sConfigMgr->GetBoolDefault("Unell.Player.Annouce.Enter.Enable", true);
		uint32 MinOnline = sConfigMgr->GetIntDefault("Unell.Player.Annouce.Enter.MinOnline", 2);
		uint32 MaxOnline = sConfigMgr->GetIntDefault("Unell.Player.Annouce.Enter.MaxOnline", 30);
		bool Ongm = sConfigMgr->GetBoolDefault("Unell.Player.Annouce.Enter.OnliGM", true);

		switch (player->GetSession()->GetSecurity())
		{
		case SEC_PLAYER:
			if (!player->GetSession()->IsPremium() && Penter)
			{
				if (Ongm)
				{
					snprintf(msg, 250, "|cffff0000[Анонс входа]:|r |cff6C8CD5Игрок |cff14ECCF%s |cff6C8CD5входит в игровой мир", NameLink.c_str());
					sWorld->SendGMText(LANG_GM_BROADCAST, msg);

					if (playeronline >= MinOnline && playeronline <= MaxOnline)
					{
						snprintf(msg, 250, "|cffff0000# |cff00ff00Сейчас|r %u |cff00ff00игроков онлайн|r", playeronline);
						sWorld->SendGMText(LANG_GM_BROADCAST, msg);
					}
				}
				else
				{
					snprintf(msg, 250, "|cffff0000[Анонс входа]:|r |cff6C8CD5Игрок |cff14ECCF%s |cff6C8CD5входит в игровой мир", NameLink.c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);

					if (playeronline >= MinOnline && playeronline <= MaxOnline)
					{
						snprintf(msg, 250, "|cffff0000# |cff00ff00Сейчас|r %u |cff00ff00игроков онлайн|r", playeronline);
						sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					}
				}
			}
			break;
		default:
			break;
		}
	}
};

void AddSC_Unell_Announcer_System()
{
	new Boss_Announcer();
	new gm_announce();
	new player_announce();
}