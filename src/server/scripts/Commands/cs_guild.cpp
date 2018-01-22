/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: http://github.com/azerothcore/azerothcore-wotlk/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

/* ScriptData
Name: guild_commandscript
%Complete: 100
Comment: All guild related commands
Category: commandscripts
EndScriptData */

#include "Chat.h"
#include "Language.h"
#include "Guild.h"
#include "GuildMgr.h"
#include "ObjectAccessor.h"
#include "ScriptMgr.h"

class guild_commandscript : public CommandScript
{
public:
    guild_commandscript() : CommandScript("guild_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> guildCommandTable =
        {
            { "create",         SEC_GAMEMASTER,     true,  &HandleGuildCreateCommand,           "" },
            { "delete",         SEC_GAMEMASTER,     true,  &HandleGuildDeleteCommand,           "" },
            { "invite",         SEC_GAMEMASTER,     true,  &HandleGuildInviteCommand,           "" },
            { "uninvite",       SEC_GAMEMASTER,     true,  &HandleGuildUninviteCommand,         "" },
            { "rank",           SEC_GAMEMASTER,     true,  &HandleGuildRankCommand,             "" }
        };
        static std::vector<ChatCommand> commandTable =
        {
            { "guild",          SEC_GAMEMASTER,  true, nullptr,                                 "", guildCommandTable }
        };
        return commandTable;
    }

    /** \brief GM command level 3 - Create a guild.
     *
     * This command allows a GM (level 3) to create a guild.
     *
     * The "args" parameter contains the name of the guild leader
     * and then the name of the guild.
     *
     */
    static bool HandleGuildCreateCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // if not guild name only (in "") then player name
        Player* target;
        if (!handler->extractPlayerTarget(*args != '"' ? (char*)args : nullptr, &target))
            return false;

        char* tailStr = *args != '"' ? strtok(nullptr, "") : (char*)args;
        if (!tailStr)
            return false;

        char* guildStr = handler->extractQuotedArg(tailStr);
        if (!guildStr)
            return false;

        std::string guildName = guildStr;

        if (target->GetGuildId())
        {
            handler->SendSysMessage(LANG_PLAYER_IN_GUILD);
            return true;
        }

        Guild* guild = new Guild;
        if (!guild->Create(target, guildName))
        {
            delete guild;
            handler->SendSysMessage(LANG_GUILD_NOT_CREATED);
            handler->SetSentErrorMessage(true);
            return false;
        }

        sGuildMgr->AddGuild(guild);

        return true;
    }

    static bool HandleGuildDeleteCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char* guildStr = handler->extractQuotedArg((char*)args);
        if (!guildStr)
            return false;

        std::string guildName = guildStr;

        Guild* targetGuild = sGuildMgr->GetGuildByName(guildName);
        if (!targetGuild)
            return false;

        targetGuild->Disband();
        delete targetGuild;

        return true;
    }

    static bool HandleGuildInviteCommand(ChatHandler* handler, char const* args)
    {
		if (!*args)
		{
			handler->PSendSysMessage("|cffff0000# |cff00ff00Нужно ввести номер гильдии и указать имя персонажа (или выбрать его)");
			handler->SetSentErrorMessage(true);
			return false;
		}
		
		char* char_guild_id = strtok((char*)args, " ");
		if (!char_guild_id)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Не указан номер гильдии");
			handler->SetSentErrorMessage(true);
			return false;
		}

		uint64 targetGuid;
		Player* target = handler->getSelectedPlayer();

		if (target)
			targetGuid = target->GetGUID();
		else
		{
			char* player_name = strtok(NULL, " ");
			if (!player_name)
			{
				handler->PSendSysMessage("|cFFFF0000# |cff00ff00Не указано имя персонажа");
				handler->SetSentErrorMessage(true);
				return false;
			}

			std::string playername = player_name;
			targetGuid = sObjectMgr->GetPlayerGUIDByName(playername);
		}

		uint32 guildid = (uint32)atoi(char_guild_id);
		if (!guildid)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Непонятный номер гильдии:|r %u", guildid);
			handler->SetSentErrorMessage(true);
			return false;
		}

		Guild* targetGuild = sGuildMgr->GetGuildById(guildid);
		if (!targetGuild)
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Гильдии с номером|r %u |cff00ff00не найдено", guildid);
			handler->SetSentErrorMessage(true);
			return false;
		}

		if (!targetGuild->AddMember(targetGuid))
		{
			handler->PSendSysMessage("|cFFFF0000# |cff00ff00Скорее всего игрок уже в гильдии");
			handler->SetSentErrorMessage(true);
			return false;
		}

		return true;
		
		/*if (!*args)
            return false;

        // if not guild name only (in "") then player name
        uint64 targetGuid;
        if (!handler->extractPlayerTarget(*args != '"' ? (char*)args : nullptr, nullptr, &targetGuid))
            return false;

        char* tailStr = *args != '"' ? strtok(nullptr, "") : (char*)args;
        if (!tailStr)
            return false;

        char* guildStr = handler->extractQuotedArg(tailStr);
        if (!guildStr)
            return false;

        std::string guildName = guildStr;
        Guild* targetGuild = sGuildMgr->GetGuildByName(guildName);
        if (!targetGuild)
            return false;

        // player's guild membership checked in AddMember before add
        return targetGuild->AddMember(targetGuid);*/
    }

    static bool HandleGuildUninviteCommand(ChatHandler* handler, char const* args)
    {
        Player* target;
        uint64 targetGuid;
        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid))
            return false;

        uint32 guildId = target ? target->GetGuildId() : Player::GetGuildIdFromStorage(GUID_LOPART(targetGuid));
        if (!guildId)
            return false;

        Guild* targetGuild = sGuildMgr->GetGuildById(guildId);
        if (!targetGuild)
            return false;

        targetGuild->DeleteMember(targetGuid, false, true, true);
        return true;
    }

    static bool HandleGuildRankCommand(ChatHandler* handler, char const* args)
    {
        char* nameStr;
        char* rankStr;
        handler->extractOptFirstArg((char*)args, &nameStr, &rankStr);
        if (!rankStr)
            return false;

        Player* target;
        uint64 targetGuid;
        std::string target_name;
        if (!handler->extractPlayerTarget(nameStr, &target, &targetGuid, &target_name))
            return false;

        uint32 guildId = target ? target->GetGuildId() : Player::GetGuildIdFromStorage(GUID_LOPART(targetGuid));
        if (!guildId)
            return false;

        Guild* targetGuild = sGuildMgr->GetGuildById(guildId);
        if (!targetGuild)
            return false;

        uint8 newRank = uint8(atoi(rankStr));
        return targetGuild->ChangeMemberRank(targetGuid, newRank);
    }
};

void AddSC_guild_commandscript()
{
    new guild_commandscript();
}
