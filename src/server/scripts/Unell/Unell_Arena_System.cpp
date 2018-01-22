/*
	* Unell Arena System
 */

#include "Unell_Script.h"

class npc_1v1arena : public CreatureScript
{
  public:
    npc_1v1arena() : CreatureScript("npc_1v1arena") {}

    bool JoinQueueArena(Player *player, Creature *me, bool isRated)
    {
        if (!player || !me)
            return false;

        if (sConfigMgr->GetIntDefault("Arena.1v1.MinLevel", 80) > player->getLevel())
            return false;

        uint64 guid = player->GetGUID();
        uint8 arenaslot = ArenaTeam::GetSlotByType(ARENA_TEAM_5v5);
        uint8 arenatype = ARENA_TYPE_5v5;
        uint32 arenaRating = 0;
        uint32 matchmakerRating = 0;

        // ignore if we already in BG or BG queue
        if (player->InBattleground())
            return false;

        //check existance
        Battleground *bg = sBattlegroundMgr->GetBattlegroundTemplate(BATTLEGROUND_AA);
        if (!bg)
        {
            sLog->outError("Battleground: template bg(all arenas) not found");
            return false;
        }

        if (DisableMgr::IsDisabledFor(DISABLE_TYPE_BATTLEGROUND, BATTLEGROUND_AA, NULL))
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_ARENA_DISABLED);
            return false;
        }

        BattlegroundTypeId bgTypeId = bg->GetBgTypeID();
        BattlegroundQueueTypeId bgQueueTypeId = BattlegroundMgr::BGQueueTypeId(bgTypeId, arenatype);
        PvPDifficultyEntry const *bracketEntry = GetBattlegroundBracketByLevel(bg->GetMapId(), player->getLevel());
        if (!bracketEntry)
            return false;

        GroupJoinBattlegroundResult err = ERR_GROUP_JOIN_BATTLEGROUND_FAIL;

        if (player->GetBattlegroundQueueIndex(bgQueueTypeId) < PLAYER_MAX_BATTLEGROUND_QUEUES)
            return false;

        if (!player->HasFreeBattlegroundQueueId())
            return false;

        uint32 ateamId = 0;

        if (isRated)
        {
            ateamId = player->GetArenaTeamId(arenaslot);
            ArenaTeam *at = sArenaTeamMgr->GetArenaTeamById(ateamId);
            if (!at)
            {
                player->GetSession()->SendNotInArenaTeamPacket(arenatype);
                return false;
            }

            arenaRating = at->GetRating();
            matchmakerRating = arenaRating;

            if (arenaRating <= 0)
                arenaRating = 1;
        }

        BattlegroundQueue &bgQueue = sBattlegroundMgr->GetBattlegroundQueue(bgQueueTypeId);
        bg->SetRated(isRated);

        GroupQueueInfo *ginfo = bgQueue.AddGroup(player, NULL, bracketEntry, isRated, false, arenaRating, matchmakerRating, ateamId);
        uint32 avgTime = bgQueue.GetAverageQueueWaitTime(ginfo);
        uint32 queueSlot = player->AddBattlegroundQueueId(bgQueueTypeId);

        WorldPacket data;

        TeamId teamId = (TEAM_ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE);
        sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, bg, queueSlot, STATUS_WAIT_QUEUE, 0, bg->GetStartTime(), bg->GetArenaType(), teamId);
        player->GetSession()->SendPacket(&data);

        sBattlegroundMgr->ScheduleArenaQueueUpdate(matchmakerRating, bgQueueTypeId, bracketEntry->GetBracketId());
        return true;
    }

    bool CreateArenateam(Player *player, Creature *me)
    {
        if (!player || !me)
            return false;

        uint8 slot = ArenaTeam::GetSlotByType(ARENA_TEAM_5v5);
        if (slot >= MAX_ARENA_SLOT)
            return false;

        // Check if player is already in an arena team
        if (player->GetArenaTeamId(slot))
        {
            player->GetSession()->SendArenaTeamCommandResult(ERR_ARENA_TEAM_CREATE_S, player->GetName(), "", ERR_ALREADY_IN_ARENA_TEAM);
            return false;
        }

        // Teamname = playername
        // if teamname exist, we have to choose another name (playername + number)
        int i = 1;
        std::stringstream teamName;
        teamName << player->GetName();
        do
        {
            if (sArenaTeamMgr->GetArenaTeamByName(teamName.str()) != NULL) // teamname exist, so choose another name
            {
                teamName.str(std::string());
                teamName << player->GetName() << (i++);
            }
            else
                break;
        } while (i < 100); // should never happen

        // Create arena team
        ArenaTeam *arenaTeam = new ArenaTeam();

        if (!arenaTeam->Create(player->GetGUID(), ARENA_TEAM_5v5, teamName.str(), 4283124816, 45, 4294242303, 5, 4294705149))
        {
            delete arenaTeam;
            return false;
        }

        // Register arena team
        sArenaTeamMgr->AddArenaTeam(arenaTeam);
        arenaTeam->AddMember(player->GetGUID());

        ChatHandler(player->GetSession()).SendSysMessage("Команда создана!");

        return true;
    }

    bool OnGossipHello(Player *player, Creature *me)
    {
        if (!player || !me)
            return true;

        if (!sConfigMgr->GetBoolDefault("Arena.1v1.Enable", false))
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Соло арена выключена!");
            return true;
        }

        if (player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_5v5))
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Выйти из очереди", GOSSIP_SENDER_MAIN, 3, "Вы уверены?", 0, false);
        else
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Встать в очередь (стычка)", GOSSIP_SENDER_MAIN, 20);

        if (player->GetArenaTeamId(ArenaTeam::GetSlotByType(ARENA_TEAM_5v5)) == 0)
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Создать команду", GOSSIP_SENDER_MAIN, 1, "Создать новую команду?", sConfigMgr->GetIntDefault("Arena.1v1.Costs", 400000), false);
        else
        {
            if (player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_5v5) == false)
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Встать в очередь (рейтинг)", GOSSIP_SENDER_MAIN, 2);
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Удалить команду", GOSSIP_SENDER_MAIN, 5, "Вы уверены?", 0, false);
            }

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Показать статистику", GOSSIP_SENDER_MAIN, 4);
        }

        player->SEND_GOSSIP_MENU(1, me->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *me, uint32 /*uiSender*/, uint32 uiAction)
    {
        if (!player || !me)
            return true;

        player->PlayerTalkClass->ClearMenus();

        switch (uiAction)
        {
        case 1:
        {
            if (sConfigMgr->GetIntDefault("Arena.1v1.MinLevel", 80) <= player->getLevel())
            {
                if (player->GetMoney() >= sConfigMgr->GetIntDefault("Arena.1v1.Costs", 400000) && CreateArenateam(player, me))
                    player->ModifyMoney(sConfigMgr->GetIntDefault("Arena.1v1.Costs", 400000) * -1);
            }
            else
            {
                ChatHandler(player->GetSession()).PSendSysMessage("Вам нужен уровень %u+ чтобы создать команду", sConfigMgr->GetIntDefault("Arena.1v1.MinLevel", 80));
                player->CLOSE_GOSSIP_MENU();
                return true;
            }
        }
        break;

        case 2: // Join Queue Arena (rated)
        {
            if (Arena1v1CheckTalents(player) && JoinQueueArena(player, me, true) == false)
                ChatHandler(player->GetSession()).SendSysMessage("Something went wrong while join queue.");

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        break;

        case 20: // Join Queue Arena (unrated)
        {
            if (Arena1v1CheckTalents(player) && JoinQueueArena(player, me, false) == false)
                ChatHandler(player->GetSession()).SendSysMessage("Something went wrong while join queue.");

            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        break;

        case 3: // Leave Queue
        {
            WorldPacket Data;
            Data << (uint8)0x1 << (uint8)0x0 << (uint32)BATTLEGROUND_AA << (uint16)0x0 << (uint8)0x0;
            player->GetSession()->HandleBattleFieldPortOpcode(Data);
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        break;

        case 4: // get statistics
        {
            ArenaTeam *at = sArenaTeamMgr->GetArenaTeamById(player->GetArenaTeamId(ArenaTeam::GetSlotByType(ARENA_TEAM_5v5)));
            if (at)
            {
                std::stringstream s;
                s << "Рейтинг: " << at->GetStats().Rating;
                s << "\nРанг: " << at->GetStats().Rank;
                s << "\nИгр в Сезоне: " << at->GetStats().SeasonGames;
                s << "\nВыиграно в Сезоне: " << at->GetStats().SeasonWins;
                s << "\nИгр за неделю: " << at->GetStats().WeekGames;
                s << "\nВыигрышей за неделю: " << at->GetStats().WeekWins;

                ChatHandler(player->GetSession()).PSendSysMessage("%s", s.str().c_str());
            }
        }
        break;

        case 5: // Disband arenateam
        {
            WorldPacket Data;
            Data << (uint32)player->GetArenaTeamId(ArenaTeam::GetSlotByType(ARENA_TEAM_5v5));
            player->GetSession()->HandleArenaTeamLeaveOpcode(Data);
            ChatHandler(player->GetSession()).SendSysMessage("Команда удалена!");
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
        break;
        }

        OnGossipHello(player, me);
        return true;
    }
};

void AddSC_Unell_Arena_System()
{
    new npc_1v1arena();
}