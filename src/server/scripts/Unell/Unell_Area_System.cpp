#include "Unell_Script.h"

class Unell_Area : public PlayerScript
{
  public:
	Unell_Area() : PlayerScript("Unell_Area") {}

	void OnUpdateZone(Player *player, uint32 newZone, uint32 newArea) override
	{
		Battleground *bg = player->GetBattleground();

		if (bg && player->GetMap()->IsBattleground() && bg->GetStatus() == STATUS_WAIT_JOIN)
		{
			ChatHandler handler(player->GetSession());
			if (sConfigMgr->GetBoolDefault("Unell.BattleGround.Buffs.Enable", true))
			{
				handler.PSendSysMessage("|cffff0000# |cff14ECCFВы перешли на Поле Боя. Вам были выданы классовые баффы");
				player->CastSpell(player, 25898, true);
				player->CastSpell(player, 48470, true);
				player->CastSpell(player, 48162, true);
				player->CastSpell(player, 48074, true);
				player->CastSpell(player, 48170, true);
			}
		}

		if (bg && player->GetMap()->IsBattleArena() && bg->GetStatus() == STATUS_WAIT_JOIN)
		{
			ChatHandler handler(player->GetSession());
			// handler.PSendSysMessage("Вы в зоне Арены, которая вот вот начнётся!");
		}

		if (sConfigMgr->GetBoolDefault("Unell.Protection.Zone.Enable", true))
		{
			uint32 ZoneID = sConfigMgr->GetIntDefault("Unell.Protection.Zone.ZoneID", 268);
			uint32 guid = sObjectMgr->GetPlayerGUIDByName(player->GetName());

			if (player->GetZoneId() == ZoneID && !Unell_Script::Unell_isgm(guid))
			{
				ChatHandler handler(player->GetSession());
				player->AddAura(31797, player);
				handler.PSendSysMessage("|cffff0000# |cff14ECCFВы не являетесь представителем администрации нашего сервера, поэтому вам запрещено быть в данной зоне!");
			}
		}
	}
};

enum ForbiddenAreas
{
	AREA_GM_ISLAND = 876, // GM Island
};

class Unell_Area_GM_Island : public PlayerScript
{
  public:
	Unell_Area_GM_Island() : PlayerScript("Unell_Area_GM_Island") {}

	void OnUpdateZone(Player *pPlayer, uint32 newZone, uint32 newArea)
	{
		if (sConfigMgr->GetBoolDefault("Unell.Protection.GM.Island", true))
		{
			switch (pPlayer->GetAreaId())
			{
			case AREA_GM_ISLAND:
			{
				if (pPlayer->GetSession()->GetSecurity() >= 1)
					return;

				pPlayer->TeleportTo(0, -11395.64355f, 1326.727661f, 362.421051f, 2.286590f); // Хрен пойми куда
				pPlayer->AddAura(35182, pPlayer);

				std::string NameLink = ChatHandler(pPlayer->GetSession()).GetNameLink(pPlayer);
				sWorld->SendGMText(UNELL_LANG_ANNOUNCE_GM_ISLAND, NameLink.c_str());
			}
			break;
			}
		}
	}
};

void AddSC_Unell_Area_System()
{
	new Unell_Area();
	new Unell_Area_GM_Island();
}