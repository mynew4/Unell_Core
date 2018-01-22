#include "Unell_Script.h"

namespace Unell_Script
{
	std::string Unell_accuser(uint32 accid) // accuser(accid);
	{
		QueryResult resultuser = LoginDatabase.PQuery("SELECT username FROM account WHERE id = %u", accid);
		if(resultuser)					
		{
			Field * field = resultuser->Fetch();								
			std::string username = field[0].GetString();	
			return username;
		}
		else
			return "Неизвестно";
	}
	
	uint32 Unell_accid(std::string username) // accuser(accid);
	{
		QueryResult resultid = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%u'", username.c_str());
		if (resultid)
		{
			Field * field = resultid->Fetch();
			uint32 acc_id = field[0].GetInt32();
			return acc_id;
		}
		else
			return 0;
	}
		
	std::string Unell_InfoOS(uint32 accid) // InfoOS(accid);
	{
		QueryResult resultos = LoginDatabase.PQuery("SELECT os FROM account WHERE id = %u", accid);
		if(resultos)					
		{
			Field * field = resultos->Fetch();								
			std::string os = field[0].GetString();	
			return os;
		}
		else
			return "Хрен знает что за ОС :D";
	}
	
	bool Unell_isgm(uint32 guid) // Unell_isgm(guid);
	{
		QueryResult resultacc = CharacterDatabase.PQuery("SELECT account FROM characters WHERE guid = %u", guid);
		if(resultacc)
		{
			Field * field = resultacc->Fetch();								
			uint32 accid = field[0].GetUInt32();
			
			QueryResult res = LoginDatabase.PQuery("SELECT gmlevel FROM account_access WHERE id = %u", accid);
			if(res)
			{
				Field * field = res->Fetch();								
				uint32 gmlevel = field[0].GetUInt32();
				if (gmlevel > 0)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	uint32 Unell_refid(uint32 accid) // refid_token(accid);
	{
		
		QueryResult res = LoginDatabase.PQuery("SELECT refereraccid FROM account_token WHERE id = %u", accid);
		if (res)
		{
			uint32 refid = res->Fetch()->GetUInt32();
			return refid;
		}
		else
			return 0;
		
	}

	bool Unell_acctoken(uint32 accid) // accuser(accid);
	{
		
		QueryResult resultuser = LoginDatabase.PQuery("SELECT id FROM account_token WHERE id = %u", accid);
		
		if(resultuser)					
		{
			return true;
		}
		else
			return false;
	}

	bool Unell_accref(uint32 accid) // accuser(accid);
	{
		
		QueryResult resultuser = LoginDatabase.PQuery("SELECT id FROM account_ref WHERE id = %u", accid);
		
		if(resultuser)					
		{
			return true;
		}
		else
			return false;
	}
	
	bool Unell_Achieved(uint32 AchievedID) // Unell_Achieved(AchievedID);
	{
		QueryResult Achieved = CharacterDatabase.PQuery("SELECT id FROM `prize_first` WHERE id = %u", AchievedID);
		
		if(Achieved)
			return true;
		else
			return false;
	}

	uint32 Unell_max_guild_level() // refid_token(accid);
	{
		uint32 maxlvl_guild;
		QueryResult maxlevel = CharacterDatabase.PQuery("SELECT max(level) FROM guild_xp_table");
		if (maxlevel)
		{
			maxlvl_guild = maxlevel->Fetch()->GetUInt32();
			return maxlvl_guild;
		}
		else
			return 0;
	}

	uint32 Unell_Ticket_Open() // Unell_Ticket_Open();
	{
		QueryResult ticket_open_res = CharacterDatabase.PQuery("SELECT COUNT(*) FROM `gm_ticket` WHERE `type` = '0'");
		if (ticket_open_res)
		{
			uint32 ticket_open = ticket_open_res->Fetch()->GetUInt32();
			return ticket_open;
		}
		else
			return 0;
	}

	const char * Unell_Item_Locale(Player* player, uint32 ItemID) // refid_token(accid);
	{
		ChatHandler handler(player->GetSession());
		ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(ItemID);
		ItemLocale const* itemLocale = sObjectMgr->GetItemLocale(ItemID);
		char const* name = NULL;
		if (itemLocale)
			name = itemLocale->Name[handler.GetSessionDbcLocale()].c_str();
		if ((!name || !*name) && itemTemplate)
			name = itemTemplate->Name1.c_str();
		if (!name)
			name = "Unknown item";
		
		return name;
	}

	const char * Unell_Creature_Locale(Player* player, uint32 Entry) // refid_token(accid);
	{
		ChatHandler handler(player->GetSession());
		CreatureTemplate const* CreatureTemplate = sObjectMgr->GetCreatureTemplate(Entry);
		CreatureLocale const* CreatureLocale = sObjectMgr->GetCreatureLocale(Entry);
		char const* crename = NULL;
		if (CreatureLocale)
			crename = CreatureLocale->Name[handler.GetSessionDbcLocale()].c_str();
		if ((!crename || !*crename) && CreatureTemplate)
			crename = CreatureTemplate->Name.c_str();
		if (!crename)
			crename = "Unknown creature";

		return crename;
	}

	std::string GetItemLink(Player* player, uint32 itemid)
	{
		ChatHandler handler(player->GetSession());
		ItemTemplate const* itemTemplate = sObjectMgr->GetItemTemplate(itemid);
		ItemLocale const* itemLocale = sObjectMgr->GetItemLocale(itemid);
		char const* name = NULL;
		if (itemLocale)
			name = itemLocale->Name[handler.GetSessionDbcLocale()].c_str();
		if ((!name || !*name) && itemTemplate)
			name = itemTemplate->Name1.c_str();
		if (!name)
			name = "Unknown item";

		std::ostringstream ss;
		std::string color = "cffffffff";

		switch (itemTemplate->Quality)
		{
			case 0:
				color = "cff9d9d9d";
				break;
			case 1:
				color = "cffffffff";
				break;
			case 2:
				color = "cff1eff00";
				break;
			case 3:
				color = "cff0070dd";
				break;
			case 4:
				color = "cffa335ee";
				break;
			case 5:
				color = "cffff8000";
				break;
			case 6:
			case 7:
				color = "cffe6cc80";
				break;
			default:
				break;
		}

		ss << "|" << color << "|Hitem:" << itemid << ":0:0:0:0:0:0:0:0|h[" << name << "]|h|r";

		return ss.str();
	}

	std::string GetSpellLink(uint32 spellid)
	{
		auto spell = sSpellStore.LookupEntry(spellid);
		if (!spell)
			return "SPELL NOT FOUND";

		std::ostringstream ss;

		ss << spell->Id << " - |cffffffff|Hspell:" << spell->Id << "|h[" << spell->SpellName << "]|h|r";

		return ss.str();
	}

	uint32 Unell_Space_Count(Player* player) // Unell_Space_Count(player);
	{
		uint32 itemId = 40265;
		uint32 count = 1000;
		uint32 noSpaceForCount = 0;

		// check space and find places
		ItemPosCountVec dest;
		InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
		if (msg != EQUIP_ERR_OK)                               // convert to possible store amount
			count -= noSpaceForCount;

		return count;
	}

	std::string UnellCharNameByGuid(uint64 guid) // UnellCharNameByGuid(guid);
	{
		std::string username;
		QueryResult resultname = CharacterDatabase.PQuery("SELECT name FROM `characters` WHERE `guid` = %u", guid);
		if (resultname)
		{
			username = resultname->Fetch()->GetString();
			return username;
		}
		else
			return "Неизвестно";
	}
}