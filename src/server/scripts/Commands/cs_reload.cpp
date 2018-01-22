/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: http://github.com/azerothcore/azerothcore-wotlk/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

/* ScriptData
Name: reload_commandscript
%Complete: 100
Comment: All reload related commands
Category: commandscripts
EndScriptData */

#include "AchievementMgr.h"
#include "AuctionHouseMgr.h"
#include "BattlegroundMgr.h"
#include "Chat.h"
#include "CreatureTextMgr.h"
#include "DisableMgr.h"
#include "Language.h"
#include "LFGMgr.h"
#include "MapManager.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "SkillDiscovery.h"
#include "SkillExtraItems.h"
#include "SmartAI.h"
#include "SpellMgr.h"
#include "TicketMgr.h"
#include "WardenCheckMgr.h"
#include "WaypointManager.h"

class reload_commandscript : public CommandScript
{
public:
    reload_commandscript() : CommandScript("reload_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> reloadAllCommandTable =
        {
            { "achievement", SEC_ADMINISTRATOR,  true,  &HandleReloadAllAchievementCommand, "" },
            { "area",        SEC_ADMINISTRATOR,  true,  &HandleReloadAllAreaCommand,       "" },
            { "gossips",     SEC_ADMINISTRATOR,  true,  &HandleReloadAllGossipsCommand,    "" },
            { "item",        SEC_ADMINISTRATOR,  true,  &HandleReloadAllItemCommand,       "" },
            { "locales",     SEC_ADMINISTRATOR,  true,  &HandleReloadAllLocalesCommand,    "" },
            { "loot",        SEC_ADMINISTRATOR,  true,  &HandleReloadAllLootCommand,       "" },
            { "npc",         SEC_ADMINISTRATOR,  true,  &HandleReloadAllNpcCommand,        "" },
            { "quest",       SEC_ADMINISTRATOR,  true,  &HandleReloadAllQuestCommand,      "" },
            { "scripts",     SEC_ADMINISTRATOR,  true,  &HandleReloadAllScriptsCommand,    "" },
            { "spell",       SEC_ADMINISTRATOR,  true,  &HandleReloadAllSpellCommand,      "" },
            { "",            SEC_ADMINISTRATOR,  true,  &HandleReloadAllCommand,           "" }
        };
        static std::vector<ChatCommand> reloadCommandTable =
        {
            { "auctions",                     SEC_ADMINISTRATOR, true,  &HandleReloadAuctionsCommand,                   "" },
            { "access_requirement",           SEC_ADMINISTRATOR, true,  &HandleReloadAccessRequirementCommand,          "" },
            { "achievement_criteria_data",    SEC_ADMINISTRATOR, true,  &HandleReloadAchievementCriteriaDataCommand,    "" },
            { "achievement_reward",           SEC_ADMINISTRATOR, true,  &HandleReloadAchievementRewardCommand,          "" },
            { "all",                          SEC_ADMINISTRATOR, true,  nullptr,                                        "", reloadAllCommandTable },
            { "areatrigger_involvedrelation", SEC_ADMINISTRATOR, true,  &HandleReloadQuestAreaTriggersCommand,          "" },
            { "areatrigger_tavern",           SEC_ADMINISTRATOR, true,  &HandleReloadAreaTriggerTavernCommand,          "" },
            { "areatrigger_teleport",         SEC_ADMINISTRATOR, true,  &HandleReloadAreaTriggerTeleportCommand,        "" },
            { "autobroadcast",                SEC_ADMINISTRATOR, true,  &HandleReloadAutobroadcastCommand,              "" },
            { "broadcast_text",               SEC_ADMINISTRATOR, true,  &HandleReloadBroadcastTextCommand,              "" },
            { "battleground_template",        SEC_ADMINISTRATOR, true,  &HandleReloadBattlegroundTemplate,              "" },
            { "command",                      SEC_ADMINISTRATOR, true,  &HandleReloadCommandCommand,                    "" },
            { "conditions",                   SEC_ADMINISTRATOR, true,  &HandleReloadConditions,                        "" },
            { "config",                       SEC_ADMINISTRATOR, true,  &HandleReloadConfigCommand,                     "" },
            { "creature_text",                SEC_ADMINISTRATOR, true,  &HandleReloadCreatureText,                      "" },
            { "creature_questender",          SEC_ADMINISTRATOR, true,  &HandleReloadCreatureQuestEnderCommand,         "" },
            { "creature_linked_respawn",      SEC_GAMEMASTER,    true,  &HandleReloadLinkedRespawnCommand,              "" },
            { "creature_loot_template",       SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesCreatureCommand,      "" },
            { "creature_onkill_reputation",   SEC_ADMINISTRATOR, true,  &HandleReloadOnKillReputationCommand,           "" },
            { "creature_queststarter",        SEC_ADMINISTRATOR, true,  &HandleReloadCreatureQuestStarterCommand,       "" },
            { "creature_template",            SEC_ADMINISTRATOR, true,  &HandleReloadCreatureTemplateCommand,           "" },
            //{ "db_script_string",             SEC_ADMINISTRATOR, true,  &HandleReloadDbScriptStringCommand,            "" },
            { "disables",                     SEC_ADMINISTRATOR, true,  &HandleReloadDisablesCommand,                   "" },
            { "disenchant_loot_template",     SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesDisenchantCommand,    "" },
            { "event_scripts",                SEC_ADMINISTRATOR, true,  &HandleReloadEventScriptsCommand,               "" },
            { "fishing_loot_template",        SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesFishingCommand,       "" },
            { "game_graveyard_zone",          SEC_ADMINISTRATOR, true,  &HandleReloadGameGraveyardZoneCommand,          "" },
            { "game_tele",                    SEC_ADMINISTRATOR, true,  &HandleReloadGameTeleCommand,                   "" },
            { "gameobject_questender",        SEC_ADMINISTRATOR, true,  &HandleReloadGOQuestEnderCommand,               "" },
            { "gameobject_loot_template",     SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesGameobjectCommand,    "" },
            { "gameobject_queststarter",      SEC_ADMINISTRATOR, true,  &HandleReloadGOQuestStarterCommand,             "" },
            { "gm_tickets",                   SEC_ADMINISTRATOR, true,  &HandleReloadGMTicketsCommand,                  "" },
            { "gossip_menu",                  SEC_ADMINISTRATOR, true,  &HandleReloadGossipMenuCommand,                 "" },
            { "gossip_menu_option",           SEC_ADMINISTRATOR, true,  &HandleReloadGossipMenuOptionCommand,           "" },
            { "item_enchantment_template",    SEC_ADMINISTRATOR, true,  &HandleReloadItemEnchantementsCommand,          "" },
            { "item_loot_template",           SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesItemCommand,          "" },
            { "item_set_names",               SEC_ADMINISTRATOR, true,  &HandleReloadItemSetNamesCommand,               "" },
			{ "item_template",                SEC_ADMINISTRATOR, true,  &HandleReloadItemTemplateCommand,               "" },
            { "lfg_dungeon_rewards",          SEC_ADMINISTRATOR, true,  &HandleReloadLfgRewardsCommand,                 "" },
            { "locales_achievement_reward",   SEC_ADMINISTRATOR, true,  &HandleReloadLocalesAchievementRewardCommand,   "" },
            { "locales_creature",             SEC_ADMINISTRATOR, true,  &HandleReloadLocalesCreatureCommand,            "" },
            { "locales_creature_text",        SEC_ADMINISTRATOR, true,  &HandleReloadLocalesCreatureTextCommand,        "" },
            { "locales_gameobject",           SEC_ADMINISTRATOR, true,  &HandleReloadLocalesGameobjectCommand,          "" },
            { "locales_gossip_menu_option",   SEC_ADMINISTRATOR, true,  &HandleReloadLocalesGossipMenuOptionCommand,    "" },
            { "locales_item",                 SEC_ADMINISTRATOR, true,  &HandleReloadLocalesItemCommand,                "" },
            { "locales_item_set_name",        SEC_ADMINISTRATOR, true,  &HandleReloadLocalesItemSetNameCommand,         "" },
            { "locales_npc_text",             SEC_ADMINISTRATOR, true,  &HandleReloadLocalesNpcTextCommand,             "" },
            { "locales_page_text",            SEC_ADMINISTRATOR, true,  &HandleReloadLocalesPageTextCommand,            "" },
            { "locales_points_of_interest",   SEC_ADMINISTRATOR, true,  &HandleReloadLocalesPointsOfInterestCommand,    "" },
            { "locales_quest",                SEC_ADMINISTRATOR, true,  &HandleReloadLocalesQuestCommand,               "" },
            { "mail_level_reward",            SEC_ADMINISTRATOR, true,  &HandleReloadMailLevelRewardCommand,            "" },
            { "mail_loot_template",           SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesMailCommand,          "" },
            { "milling_loot_template",        SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesMillingCommand,       "" },
            { "npc_spellclick_spells",        SEC_ADMINISTRATOR, true,  &HandleReloadSpellClickSpellsCommand,           "" },
            { "npc_trainer",                  SEC_ADMINISTRATOR, true,  &HandleReloadNpcTrainerCommand,                 "" },
            { "npc_vendor",                   SEC_ADMINISTRATOR, true,  &HandleReloadNpcVendorCommand,                  "" },
            { "page_text",                    SEC_ADMINISTRATOR, true,  &HandleReloadPageTextsCommand,                  "" },
            { "pickpocketing_loot_template",  SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesPickpocketingCommand, "" },
            { "points_of_interest",           SEC_ADMINISTRATOR, true,  &HandleReloadPointsOfInterestCommand,           "" },
            { "prospecting_loot_template",    SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesProspectingCommand,   "" },
            { "quest_poi",                    SEC_ADMINISTRATOR, true,  &HandleReloadQuestPOICommand,                   "" },
            { "quest_template",               SEC_ADMINISTRATOR, true,  &HandleReloadQuestTemplateCommand,              "" },
            { "reference_loot_template",      SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesReferenceCommand,     "" },
            { "reserved_name",                SEC_ADMINISTRATOR, true,  &HandleReloadReservedNameCommand,               "" },
            { "reputation_reward_rate",       SEC_ADMINISTRATOR, true,  &HandleReloadReputationRewardRateCommand,       "" },
            { "reputation_spillover_template", SEC_ADMINISTRATOR, true,  &HandleReloadReputationRewardRateCommand,      "" },
            { "skill_discovery_template",     SEC_ADMINISTRATOR, true,  &HandleReloadSkillDiscoveryTemplateCommand,     "" },
            { "skill_extra_item_template",    SEC_ADMINISTRATOR, true,  &HandleReloadSkillExtraItemTemplateCommand,     "" },
            { "skill_fishing_base_level",     SEC_ADMINISTRATOR, true,  &HandleReloadSkillFishingBaseLevelCommand,      "" },
            { "skinning_loot_template",       SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesSkinningCommand,      "" },
            { "smart_scripts",                SEC_ADMINISTRATOR, true,  &HandleReloadSmartScripts,                      "" },
            { "spell_required",               SEC_ADMINISTRATOR, true,  &HandleReloadSpellRequiredCommand,              "" },
            { "spell_area",                   SEC_ADMINISTRATOR, true,  &HandleReloadSpellAreaCommand,                  "" },
            { "spell_bonus_data",             SEC_ADMINISTRATOR, true,  &HandleReloadSpellBonusesCommand,               "" },
            { "spell_group",                  SEC_ADMINISTRATOR, true,  &HandleReloadSpellGroupsCommand,                "" },
            { "spell_loot_template",          SEC_ADMINISTRATOR, true,  &HandleReloadLootTemplatesSpellCommand,         "" },
            { "spell_linked_spell",           SEC_ADMINISTRATOR, true,  &HandleReloadSpellLinkedSpellCommand,           "" },
            { "spell_pet_auras",              SEC_ADMINISTRATOR, true,  &HandleReloadSpellPetAurasCommand,              "" },
            { "spell_proc_event",             SEC_ADMINISTRATOR, true,  &HandleReloadSpellProcEventCommand,             "" },
            { "spell_proc",                   SEC_ADMINISTRATOR, true,  &HandleReloadSpellProcsCommand,                 "" },
            { "spell_scripts",                SEC_ADMINISTRATOR, true,  &HandleReloadSpellScriptsCommand,               "" },
            { "spell_target_position",        SEC_ADMINISTRATOR, true,  &HandleReloadSpellTargetPositionCommand,        "" },
            { "spell_threats",                SEC_ADMINISTRATOR, true,  &HandleReloadSpellThreatsCommand,               "" },
            { "spell_group_stack_rules",      SEC_ADMINISTRATOR, true,  &HandleReloadSpellGroupStackRulesCommand,       "" },
            { "trinity_string",               SEC_ADMINISTRATOR, true,  &HandleReloadTrinityStringCommand,              "" },
            { "warden_action",                SEC_ADMINISTRATOR, true,  &HandleReloadWardenactionCommand,               "" },
            { "waypoint_scripts",             SEC_ADMINISTRATOR, true,  &HandleReloadWpScriptsCommand,                  "" },
            { "waypoint_data",                SEC_ADMINISTRATOR, true,  &HandleReloadWpCommand,                         "" },
            { "vehicle_accessory",            SEC_ADMINISTRATOR, true,  &HandleReloadVehicleAccessoryCommand,           "" },
            { "vehicle_template_accessory",   SEC_ADMINISTRATOR, true,  &HandleReloadVehicleTemplateAccessoryCommand,   "" }
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "reload",         SEC_ADMINISTRATOR,  true,  nullptr,                                                     "", reloadCommandTable }
        };
        return commandTable;
    }

    //reload commands
    static bool HandleReloadGMTicketsCommand(ChatHandler* /*handler*/, const char* /*args*/)
    {
        sTicketMgr->LoadTickets();
        return true;
    }

    static bool HandleReloadAllCommand(ChatHandler* handler, const char* /*args*/)
    {
        HandleReloadSkillFishingBaseLevelCommand(handler, "");

        HandleReloadAllAchievementCommand(handler, "");
        HandleReloadAllAreaCommand(handler, "");
        HandleReloadAllLootCommand(handler, "");
        HandleReloadAllNpcCommand(handler, "");
        HandleReloadAllQuestCommand(handler, "");
        HandleReloadAllSpellCommand(handler, "");
        HandleReloadAllItemCommand(handler, "");
        HandleReloadAllGossipsCommand(handler, "");
        HandleReloadAllLocalesCommand(handler, "");

        HandleReloadAccessRequirementCommand(handler, "");
        HandleReloadMailLevelRewardCommand(handler, "");
        HandleReloadCommandCommand(handler, "");
        HandleReloadReservedNameCommand(handler, "");
        HandleReloadTrinityStringCommand(handler, "");
        HandleReloadGameTeleCommand(handler, "");

        HandleReloadVehicleAccessoryCommand(handler, "");
        HandleReloadVehicleTemplateAccessoryCommand(handler, "");

        HandleReloadAutobroadcastCommand(handler, "");
        HandleReloadBroadcastTextCommand(handler, "");
        HandleReloadBattlegroundTemplate(handler, "");
        return true;
    }

    static bool HandleReloadItemTemplateCommand(ChatHandler* handler, const char* /*args*/)
	{
		sLog->outString("Re-Loading item template...");
		sObjectMgr->LoadItemTemplates();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `item_template` |cFFFF0000перезагружена.|r");
        return true;
	}
	
	static bool HandleReloadBattlegroundTemplate(ChatHandler* handler, char const* /*args*/)
    {
        sLog->outString("Re-Loading Battleground Templates...");
        sBattlegroundMgr->CreateInitialBattlegrounds();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `battleground_template` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAllAchievementCommand(ChatHandler* handler, const char* /*args*/)
    {
        HandleReloadAchievementCriteriaDataCommand(handler, "");
        HandleReloadAchievementRewardCommand(handler, "");
        return true;
    }

    static bool HandleReloadAllAreaCommand(ChatHandler* handler, const char* /*args*/)
    {
        //HandleReloadQuestAreaTriggersCommand(handler, ""); -- reloaded in HandleReloadAllQuestCommand
        HandleReloadAreaTriggerTeleportCommand(handler, "");
        HandleReloadAreaTriggerTavernCommand(handler, "");
        HandleReloadGameGraveyardZoneCommand(handler, "");
        return true;
    }

    static bool HandleReloadAllLootCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables...");
        LoadLootTables();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблицы|r `*_loot_template` |cFFFF0000перезагружены.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadAllNpcCommand(ChatHandler* handler, const char* args)
    {
        if (*args != 'a')                                          // will be reloaded from all_gossips
        HandleReloadNpcTrainerCommand(handler, "a");
        HandleReloadNpcVendorCommand(handler, "a");
        HandleReloadPointsOfInterestCommand(handler, "a");
        HandleReloadSpellClickSpellsCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllQuestCommand(ChatHandler* handler, const char* /*args*/)
    {
        HandleReloadQuestAreaTriggersCommand(handler, "a");
        HandleReloadQuestPOICommand(handler, "a");
        HandleReloadQuestTemplateCommand(handler, "a");

        sLog->outString("Re-Loading Quests Relations...");
        sObjectMgr->LoadQuestStartersAndEnders();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблицы|r `*_queststarter` and `*_questender` |cFFFF0000перезагружены.|r");
        return true;
    }

    static bool HandleReloadAllScriptsCommand(ChatHandler* handler, const char* /*args*/)
    {
        if (sScriptMgr->IsScriptScheduled())
        {
            handler->PSendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        sLog->outString("Re-Loading Scripts...");
        HandleReloadEventScriptsCommand(handler, "a");
        HandleReloadSpellScriptsCommand(handler, "a");
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблицы|r `*_scripts` |cFFFF0000перезагружены.|r");
        HandleReloadDbScriptStringCommand(handler, "a");
        HandleReloadWpScriptsCommand(handler, "a");
        HandleReloadWpCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllSpellCommand(ChatHandler* handler, const char* /*args*/)
    {
        HandleReloadSkillDiscoveryTemplateCommand(handler, "a");
        HandleReloadSkillExtraItemTemplateCommand(handler, "a");
        HandleReloadSpellRequiredCommand(handler, "a");
        HandleReloadSpellAreaCommand(handler, "a");
        HandleReloadSpellGroupsCommand(handler, "a");
        HandleReloadSpellLinkedSpellCommand(handler, "a");
        HandleReloadSpellProcEventCommand(handler, "a");
        HandleReloadSpellProcsCommand(handler, "a");
        HandleReloadSpellBonusesCommand(handler, "a");
        HandleReloadSpellTargetPositionCommand(handler, "a");
        HandleReloadSpellThreatsCommand(handler, "a");
        HandleReloadSpellGroupStackRulesCommand(handler, "a");
        HandleReloadSpellPetAurasCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllGossipsCommand(ChatHandler* handler, const char* args)
    {
        HandleReloadGossipMenuCommand(handler, "a");
        HandleReloadGossipMenuOptionCommand(handler, "a");
        if (*args != 'a')                                          // already reload from all_scripts
        HandleReloadPointsOfInterestCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllItemCommand(ChatHandler* handler, const char* /*args*/)
    {
        HandleReloadPageTextsCommand(handler, "a");
        HandleReloadItemEnchantementsCommand(handler, "a");
        return true;
    }

    static bool HandleReloadAllLocalesCommand(ChatHandler* handler, const char* /*args*/)
    {
        HandleReloadLocalesAchievementRewardCommand(handler, "a");
        HandleReloadLocalesCreatureCommand(handler, "a");
        HandleReloadLocalesCreatureTextCommand(handler, "a");
        HandleReloadLocalesGameobjectCommand(handler, "a");
        HandleReloadLocalesGossipMenuOptionCommand(handler, "a");
        HandleReloadLocalesItemCommand(handler, "a");
        HandleReloadLocalesNpcTextCommand(handler, "a");
        HandleReloadLocalesPageTextCommand(handler, "a");
        HandleReloadLocalesPointsOfInterestCommand(handler, "a");
        HandleReloadLocalesQuestCommand(handler, "a");
        return true;
    }

    static bool HandleReloadConfigCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading config settings...");
        sWorld->LoadConfigSettings(true);
        sMapMgr->InitializeVisibilityDistanceInfo();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|r Конфиг сервера |cFFFF0000перезагружен.|r");
        return true;
    }

    static bool HandleReloadAccessRequirementCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Access Requirement definitions...");
        sObjectMgr->LoadAccessRequirements();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `access_requirement` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAchievementCriteriaDataCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Additional Achievement Criteria Data...");
        sAchievementMgr->LoadAchievementCriteriaData();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `achievement_criteria_data` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAchievementRewardCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Achievement Reward Data...");
        sAchievementMgr->LoadRewards();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `achievement_reward` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAreaTriggerTavernCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Tavern Area Triggers...");
        sObjectMgr->LoadTavernAreaTriggers();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `areatrigger_tavern` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAreaTriggerTeleportCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading AreaTrigger teleport definitions...");
        sObjectMgr->LoadAreaTriggerTeleports();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `areatrigger_teleport` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAutobroadcastCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Autobroadcasts...");
        sWorld->LoadAutobroadcasts();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `autobroadcast` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadBroadcastTextCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Broadcast texts...");
        sObjectMgr->LoadBroadcastTexts();
        sObjectMgr->LoadBroadcastTextLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `broadcast_text` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadCommandCommand(ChatHandler* handler, const char* /*args*/)
    {
        handler->SetLoadCommandTable(true);
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `command` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadOnKillReputationCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading creature award reputation definitions...");
        sObjectMgr->LoadReputationOnKill();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `creature_onkill_reputation` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadCreatureTemplateCommand(ChatHandler* handler, const char* args)
    {
		sLog->outString("Reloading creatue template...");
		sObjectMgr->LoadCreatureTemplates();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `creature_template` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadCreatureQuestStarterCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Loading Quests Relations... (`creature_queststarter`)");
        sObjectMgr->LoadCreatureQuestStarters();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `creature_queststarter` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLinkedRespawnCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Loading Linked Respawns... (`creature_linked_respawn`)");
        sObjectMgr->LoadLinkedRespawn();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `creature_linked_respawn` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadCreatureQuestEnderCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Loading Quests Relations... (`creature_questender`)");
        sObjectMgr->LoadCreatureQuestEnders();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `creature_questender` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadGossipMenuCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading `gossip_menu` Table!");
        sObjectMgr->LoadGossipMenu();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `gossip_menu` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadGossipMenuOptionCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading `gossip_menu_option` Table!");
        sObjectMgr->LoadGossipMenuItems();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `gossip_menu_option` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadGOQuestStarterCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Loading Quests Relations... (`gameobject_queststarter`)");
        sObjectMgr->LoadGameobjectQuestStarters();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `gameobject_queststarter` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadGOQuestEnderCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Loading Quests Relations... (`gameobject_questender`)");
        sObjectMgr->LoadGameobjectQuestEnders();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `gameobject_questender` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadQuestAreaTriggersCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Quest Area Triggers...");
        sObjectMgr->LoadQuestAreaTriggers();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `areatrigger_involvedrelation` (quest area triggers) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadQuestTemplateCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Quest Templates...");
        sObjectMgr->LoadQuests();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `quest_template` (quest definitions) |cFFFF0000перезагружена.|r");

        /// dependent also from `gameobject` but this table not reloaded anyway
        sLog->outString("Re-Loading GameObjects for quests...");
        sObjectMgr->LoadGameObjectForQuests();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Data GameObjects for quests |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLootTemplatesCreatureCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`creature_loot_template`)");
        LoadLootTemplates_Creature();
        LootTemplates_Creature.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `creature_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesDisenchantCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`disenchant_loot_template`)");
        LoadLootTemplates_Disenchant();
        LootTemplates_Disenchant.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `disenchant_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesFishingCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`fishing_loot_template`)");
        LoadLootTemplates_Fishing();
        LootTemplates_Fishing.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `fishing_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesGameobjectCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`gameobject_loot_template`)");
        LoadLootTemplates_Gameobject();
        LootTemplates_Gameobject.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `gameobject_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesItemCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`item_loot_template`)");
        LoadLootTemplates_Item();
        LootTemplates_Item.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `item_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesMillingCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`milling_loot_template`)");
        LoadLootTemplates_Milling();
        LootTemplates_Milling.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `milling_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesPickpocketingCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`pickpocketing_loot_template`)");
        LoadLootTemplates_Pickpocketing();
        LootTemplates_Pickpocketing.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `pickpocketing_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesProspectingCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`prospecting_loot_template`)");
        LoadLootTemplates_Prospecting();
        LootTemplates_Prospecting.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `prospecting_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesMailCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`mail_loot_template`)");
        LoadLootTemplates_Mail();
        LootTemplates_Mail.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `mail_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesReferenceCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`reference_loot_template`)");
        LoadLootTemplates_Reference();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `reference_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesSkinningCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`skinning_loot_template`)");
        LoadLootTemplates_Skinning();
        LootTemplates_Skinning.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `skinning_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadLootTemplatesSpellCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Loot Tables... (`spell_loot_template`)");
        LoadLootTemplates_Spell();
        LootTemplates_Spell.CheckLootRefs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_loot_template` |cFFFF0000перезагружена.|r");
        sConditionMgr->LoadConditions(true);
        return true;
    }

    static bool HandleReloadTrinityStringCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading trinity_string Table!");
        sObjectMgr->LoadTrinityStrings();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `trinity_string` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadWardenactionCommand(ChatHandler* handler, const char* /*args*/)
    {
        if (!sWorld->getBoolConfig(CONFIG_WARDEN_ENABLED))
        {
            handler->SendSysMessage("Warden system disabled by config - reloading warden_action skipped.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        sLog->outString("Re-Loading warden_action Table!");
        sWardenCheckMgr->LoadWardenOverrides();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `warden_action` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadNpcTrainerCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading `npc_trainer` Table!");
        sObjectMgr->LoadTrainerSpell();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `npc_trainer` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadNpcVendorCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading `npc_vendor` Table!");
        sObjectMgr->LoadVendors();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `npc_vendor` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadPointsOfInterestCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading `points_of_interest` Table!");
        sObjectMgr->LoadPointsOfInterest();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `points_of_interest` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadQuestPOICommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString( "Re-Loading Quest POI ..." );
        sObjectMgr->LoadQuestPOI();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `quest_poi` and `quest_poi_points` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellClickSpellsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading `npc_spellclick_spells` Table!");
        sObjectMgr->LoadNPCSpellClickSpells();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `npc_spellclick_spells` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadReservedNameCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Loading ReservedNames... (`reserved_name`)");
        sObjectMgr->LoadReservedPlayersNames();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `reserved_name` (player reserved names) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadReputationRewardRateCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString( "Re-Loading `reputation_reward_rate` Table!" );
        sObjectMgr->LoadReputationRewardRate();
        handler->SendGlobalSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `reputation_reward_rate` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadReputationSpilloverTemplateCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString( "Re-Loading `reputation_spillover_template` Table!" );
        sObjectMgr->LoadReputationSpilloverTemplate();
        handler->SendGlobalSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `reputation_spillover_template` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSkillDiscoveryTemplateCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Skill Discovery Table...");
        LoadSkillDiscoveryTable();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `skill_discovery_template` (recipes discovered at crafting) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSkillExtraItemTemplateCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Skill Extra Item Table...");
        LoadSkillExtraItemTable();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `skill_extra_item_template` (extra item creation when crafting) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSkillFishingBaseLevelCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Skill Fishing base level requirements...");
        sObjectMgr->LoadFishingBaseSkillLevel();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `skill_fishing_base_level` (fishing base level for zone/subzone) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellAreaCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading SpellArea Data...");
        sSpellMgr->LoadSpellAreas();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_area` (spell dependences from area/quest/auras state) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellRequiredCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Required Data... ");
        sSpellMgr->LoadSpellRequired();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_required` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellGroupsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Groups...");
        sSpellMgr->LoadSpellGroups();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_group` (spell groups) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellLinkedSpellCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Linked Spells...");
        sSpellMgr->LoadSpellLinked();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_linked_spell` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellProcEventCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Proc Event conditions...");
        sSpellMgr->LoadSpellProcEvents();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_proc_event` (spell proc trigger requirements) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellProcsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Proc conditions and data...");
        sSpellMgr->LoadSpellProcs();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_proc` (spell proc conditions and data) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellBonusesCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Bonus Data...");
        sSpellMgr->LoadSpellBonusess();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_bonus_data` (spell damage/healing coefficients) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellTargetPositionCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell target coordinates...");
        sSpellMgr->LoadSpellTargetPositions();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_target_position` (destination coordinates for spell targets) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellThreatsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Aggro Spells Definitions...");
        sSpellMgr->LoadSpellThreats();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_threat` (spell aggro definitions) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellGroupStackRulesCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell Group Stack Rules...");
        sSpellMgr->LoadSpellGroupStackRules();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_group_stack_rules` (spell stacking definitions) |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSpellPetAurasCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Spell pet auras...");
        sSpellMgr->LoadSpellPetAuras();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_pet_auras` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadPageTextsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Page Texts...");
        sObjectMgr->LoadPageTexts();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `page_texts` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadItemEnchantementsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Item Random Enchantments Table...");
        LoadRandomEnchantmentsTable();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `item_enchantment_template` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadItemSetNamesCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Item set names...");
        sObjectMgr->LoadItemSetNames();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `item_set_names` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadEventScriptsCommand(ChatHandler* handler, const char* args)
    {
        if (sScriptMgr->IsScriptScheduled())
        {
            handler->SendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (*args != 'a')
            sLog->outString("Re-Loading Scripts from `event_scripts`...");

        sObjectMgr->LoadEventScripts();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `event_scripts` |cFFFF0000перезагружена.|r");

        return true;
    }

    static bool HandleReloadWpScriptsCommand(ChatHandler* handler, const char* args)
    {
        if (sScriptMgr->IsScriptScheduled())
        {
            handler->SendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (*args != 'a')
            sLog->outString("Re-Loading Scripts from `waypoint_scripts`...");

        sObjectMgr->LoadWaypointScripts();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `waypoint_scripts` |cFFFF0000перезагружена.|r");

        return true;
    }

    static bool HandleReloadWpCommand(ChatHandler* handler, const char* args)
    {
        if (*args != 'a')
            sLog->outString("Re-Loading Waypoints data from 'waypoints_data'");

        sWaypointMgr->Load();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r 'waypoint_data' |cFFFF0000перезагружена.|r");

        return true;
    }

    static bool HandleReloadSpellScriptsCommand(ChatHandler* handler, const char* args)
    {
        if (sScriptMgr->IsScriptScheduled())
        {
            handler->SendSysMessage("DB scripts used currently, please attempt reload later.");
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (*args != 'a')
            sLog->outString("Re-Loading Scripts from `spell_scripts`...");

        sObjectMgr->LoadSpellScripts();

        if (*args != 'a')
            handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `spell_scripts` |cFFFF0000перезагружена.|r");

        return true;
    }

    static bool HandleReloadDbScriptStringCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Script strings from `db_script_string`...");
        sObjectMgr->LoadDbScriptStrings();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `db_script_string` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadGameGraveyardZoneCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Graveyard-zone links...");

        sObjectMgr->LoadGraveyardZones();

        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `game_graveyard_zone` |cFFFF0000перезагружена.|r");

        return true;
    }

    static bool HandleReloadGameTeleCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Game Tele coordinates...");

        sObjectMgr->LoadGameTele();

        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `game_tele` |cFFFF0000перезагружена.|r");

        return true;
    }

    static bool HandleReloadDisablesCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading disables table...");
        DisableMgr::LoadDisables();
        sLog->outString("Checking quest disables...");
        DisableMgr::CheckQuestDisables();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `disables` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesAchievementRewardCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Achievement Reward Data...");
        sAchievementMgr->LoadRewardLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_achievement_reward` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLfgRewardsCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading lfg dungeon rewards...");
        sLFGMgr->LoadRewards();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `lfg_dungeon_rewards` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesCreatureCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Creature ...");
        sObjectMgr->LoadCreatureLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_creature` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesCreatureTextCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Creature Texts...");
        sCreatureTextMgr->LoadCreatureTextLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_creature_text` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesGameobjectCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Gameobject ... ");
        sObjectMgr->LoadGameObjectLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_gameobject` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesGossipMenuOptionCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString( "Re-Loading Locales Gossip Menu Option ... ");
        sObjectMgr->LoadGossipMenuItemsLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_gossip_menu_option` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesItemCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Item ... ");
        sObjectMgr->LoadItemLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_item` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesItemSetNameCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Item set name... ");
        sObjectMgr->LoadItemSetNameLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_item_set_name` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesNpcTextCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales NPC Text ... ");
        sObjectMgr->LoadNpcTextLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_npc_text` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesPageTextCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Page Text ... ");
        sObjectMgr->LoadPageTextLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_page_text` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesPointsOfInterestCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Points Of Interest ... ");
        sObjectMgr->LoadPointOfInterestLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_points_of_interest` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadLocalesQuestCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Locales Quest ... ");
        sObjectMgr->LoadQuestLocales();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `locales_quest` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadMailLevelRewardCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Player level dependent mail rewards...");
        sObjectMgr->LoadMailLevelRewards();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000 Таблица|r `mail_level_reward` |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadAuctionsCommand(ChatHandler* handler, const char* /*args*/)
    {
        ///- Reload dynamic data tables from the database
        sLog->outString("Re-Loading Auctions...");
        sAuctionMgr->LoadAuctionItems();
        sAuctionMgr->LoadAuctions();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Auctions |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadConditions(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Conditions...");
        sConditionMgr->LoadConditions(true);
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Conditions |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadCreatureText(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Creature Texts...");
        sCreatureTextMgr->LoadCreatureTexts();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Creature Texts |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadSmartScripts(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Re-Loading Smart Scripts...");
        sSmartScriptMgr->LoadSmartAIFromDB();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Smart Scripts |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadVehicleAccessoryCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Reloading vehicle_accessory table...");
        sObjectMgr->LoadVehicleAccessories();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Vehicle accessories |cFFFF0000перезагружена.|r");
        return true;
    }

    static bool HandleReloadVehicleTemplateAccessoryCommand(ChatHandler* handler, const char* /*args*/)
    {
        sLog->outString("Reloading vehicle_template_accessory table...");
        sObjectMgr->LoadVehicleTemplateAccessories();
        handler->SendGlobalGMSysMessage("|cff6C8CD5#|cFFFF0000|r Vehicle template accessories |cFFFF0000перезагружена.|r");
        return true;
    }
};

void AddSC_reload_commandscript()
{
    new reload_commandscript();
}
