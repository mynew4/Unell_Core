#ifndef UNELL_SCRIPT_H
#define UNELL_SCRIPT_H

#include "AccountMgr.h"
#include "ArenaTeam.h"
#include "ArenaTeamMgr.h"
#include "BattlegroundMgr.h"
#include "BattlegroundMgr.h"
#include "Channel.h"
#include "Common.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "Define.h"
#include "DisableMgr.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "Item.h"
#include "Language.h"
#include "Log.h"
#include "Pet.h"
#include "Player.h"
#include "ScriptPCH.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "TicketMgr.h"
#include "Unell_Arena_System.h"
#include "Util.h"
#include "World.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include <string>

enum UnellStrings // Локализация
{
	// Уровни ГМ
	UNELL_LANG_GM_LEVEL_0 = 40000,
	UNELL_LANG_GM_LEVEL_1,
	UNELL_LANG_GM_LEVEL_2,
	UNELL_LANG_GM_LEVEL_3,
	UNELL_LANG_GM_LEVEL_4,
	UNELL_LANG_GM_LEVEL_5,
	UNELL_LANG_GM_LEVEL_6,

	// Анонсы входа / выхода
	UNELL_LANG_ANNOUNCE_GM_ENTER,
	UNELL_LANG_ANNOUNCE_GM_ENTER_PHONE,
	UNELL_LANG_ANNOUNCE_PLAYER_VIP_ENTER,
	UNELL_LANG_ANNOUNCE_PLAYER_VIP_ENTER_PHONE,

	// Анонсы выхода
	UNELL_LANG_ANNOUNCE_GM_LOGOUT,
	UNELL_LANG_ANNOUNCE_PLAYER_VIP_LOGOUT,
	
	// Анонс ГМ острова
	UNELL_LANG_ANNOUNCE_GM_ISLAND,

	// Суммон на ГМ Остров
	UNELL_LANG_NOT_SUMMONIG_GM_ISLAND,
	UNELL_LANG_NOT_SUMMONIG_GM_ISLAND_DEVEPOLER,
	UNELL_LANG_ANNOUNCE_GM_ISLAND_SUMMON,

};

namespace Unell_Script
{
	std::string Unell_accuser(uint32 accid);
	uint32 Unell_accid(std::string username);
	std::string Unell_InfoOS(uint32 accid);
	uint32 Unell_refid(uint32 accid);
	bool Unell_acctoken(uint32 accid);
	bool Unell_accref(uint32 accid);
	bool Unell_isgm(uint32 guid);
	bool Unell_Achieved(uint32 AchievedID);
	uint32 Unell_max_guild_level();
	uint32 Unell_Ticket_Open();
	const char * Unell_Item_Locale(Player* player, uint32 ItemID);
	const char * Unell_Creature_Locale(Player* player, uint32 Entry);
	std::string GetItemLink(Player* player, uint32 itemid);
	std::string GetSpellLink(uint32 spellid);
	uint32 Unell_Space_Count(Player* player);
	std::string UnellCharNameByGuid(uint64 guid);
};

#endif