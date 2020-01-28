#include "ScriptMgr.h"
#include "ArenaTeamMgr.h"
#include "Common.h"
#include "DisableMgr.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "ArenaTeam.h"
#include "Language.h"
#include "Solo3v3.h"
#include "BattlegroundQueue.h"
#include "Group.h"

class CreatureScript_Solo3v3 : public CreatureScript
{
public:
    CreatureScript_Solo3v3() : CreatureScript("CreatureScript_Solo3v3")
    {
        for (int i = 0; i < MAX_TALENT_CAT; i++)
            cache3v3Queue[i] = 0;

        lastFetchQueueList = 0;
    }

    bool OnGossipHello(Player* player, Creature* me)
    {
        if(!player || !me)
            return true;

        fetchQueueList();
        std::stringstream infoQueue;
        infoQueue << "Line up at the Solo 3vs3 arena\n";
		infoQueue << "Players in line: " << (cache3v3Queue[MELEE] + cache3v3Queue[RANGE] + cache3v3Queue[HEALER]);
        infoQueue << "\n\n";
		infoQueue << "Melee: " << cache3v3Queue[MELEE] << "\n";
        infoQueue << "Range: " << cache3v3Queue[RANGE] << "\n";
		infoQueue << "Healer: " << cache3v3Queue[HEALER];

		std::stringstream infoQueue2;
        infoQueue2 << "Line up at the Solo 3vs3 arena\n\n";
		infoQueue2 << "Players in line: " << (cache3v3Queue[MELEE] + cache3v3Queue[RANGE] + cache3v3Queue[HEALER]);
        infoQueue2 << "\n\n";
		infoQueue2 << "Melee: " << cache3v3Queue[MELEE] << "\n";
        infoQueue2 << "Range: " << cache3v3Queue[RANGE] << "\n";
		infoQueue2 << "Healer: " << cache3v3Queue[HEALER];

        if (player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_5v5)
            || player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_3v3_SOLO))
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, infoQueue2.str().c_str(), GOSSIP_SENDER_MAIN, 3, "Are you sure you want to exit the Solo 3vs3 arena lineup?", 0, false);

        if (!player->GetArenaTeamId(ArenaTeam::GetSlotByType(ARENA_TEAM_5v5)))
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, "Create a Solo 3vs3 Arena Team", GOSSIP_SENDER_MAIN, 1, "", 0, false);
        else
        {
            if (player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_5v5) == false && player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_3v3_SOLO) == false)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, infoQueue.str().c_str(), GOSSIP_SENDER_MAIN, 2);
        }

        player->SEND_GOSSIP_MENU(10110, me->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* me, uint32 /*Sender*/, uint32 Actions)
    {
        if(!player || !me)
            return true;

        player->PlayerTalkClass->ClearMenus();

        switch (Actions)
        {
            case 1:
                CreateArenateam(player, me);
				break;
            case 2:
            {
                if (player->HasAura(26013))
                {
                    WorldPacket data;
                    sBattlegroundMgr->BuildGroupJoinedBattlegroundPacket(&data, ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS);
                    player->GetSession()->SendPacket(&data);
                }
                else if (ArenaCheckFullEquipAndTalents(player) && JoinQueueArena(player, me, true, ARENA_TYPE_3v3_SOLO) == false)
                    ChatHandler(player->GetSession()).SendSysMessage("Something went wrong when you tried to get in line. Are you already standing in a different lineup to the arena / bg?");

                player->CLOSE_GOSSIP_MENU();
                return true;
            }
            case 3: // Leave Queue
            {
                uint8 arenaType = ARENA_TYPE_5v5;
                if (player->InBattlegroundQueueForBattlegroundQueueType(BATTLEGROUND_QUEUE_3v3_SOLO))
                    arenaType = ARENA_TYPE_3v3_SOLO;

                WorldPacket Data;
                Data << arenaType << (uint8)0x0 << (uint32)BATTLEGROUND_AA << (uint16)0x0 << (uint8)0x0;
                player->GetSession()->HandleBattleFieldPortOpcode(Data);
                player->CLOSE_GOSSIP_MENU();
                return true;
            }
		}

        OnGossipHello(player, me);
        return true;
    }

private:
    int cache3v3Queue[MAX_TALENT_CAT];
    uint32 lastFetchQueueList;

    bool ArenaCheckFullEquipAndTalents(Player* player)
    {
        if (!player)
            return false;

        std::stringstream Message;

        if (player->GetFreeTalentPoints() > 0)
            Message << "You have currently " << player->GetFreeTalentPoints() << " free talent points. Please spend all your talent points before queueing arena.\n";

        Item* newItem = NULL;
        for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; ++slot)
        {
            if (slot == EQUIPMENT_SLOT_OFFHAND || slot == EQUIPMENT_SLOT_RANGED || slot == EQUIPMENT_SLOT_TABARD || slot == EQUIPMENT_SLOT_BODY)
                continue;

            newItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
            if (newItem == NULL)
            {
                Message << "Your character is not fully equipped.\n";
                break;
            }
        }

        if (Message.str().length() > 0)
        {
            ChatHandler(player->GetSession()).SendSysMessage(Message.str().c_str());
            return false;
        }
        return true;
    }

    bool JoinQueueArena(Player* player, Creature* me, bool isRated, uint8 arenatype)
    {
        if (!player || !me)
            return false;

        uint8 arenaslot = ArenaTeam::GetSlotByType(ARENA_TEAM_5v5);
        uint32 arenaRating = 0;
        uint32 matchmakerRating = 0;

        if (player->InBattleground() || player->InBattlegroundQueue())
            return false;

        Battleground* bg = sBattlegroundMgr->GetBattlegroundTemplate(BATTLEGROUND_AA);
        if (!bg)
            return false;

        if (DisableMgr::IsDisabledFor(DISABLE_TYPE_BATTLEGROUND, BATTLEGROUND_AA, NULL))
        {
            ChatHandler(player->GetSession()).PSendSysMessage(LANG_ARENA_DISABLED);
            return false;
        }

        BattlegroundTypeId bgTypeId = bg->GetBgTypeID();
        BattlegroundQueueTypeId bgQueueTypeId = BattlegroundMgr::BGQueueTypeId(bgTypeId, arenatype);
        PvPDifficultyEntry const* bracketEntry = GetBattlegroundBracketByLevel(bg->GetMapId(), player->getLevel());
        if (!bracketEntry)
            return false;

        if (player->GetBattlegroundQueueIndex(bgQueueTypeId) < PLAYER_MAX_BATTLEGROUND_QUEUES)
            return false;

        if (!player->HasFreeBattlegroundQueueId())
            return false;

        uint32 ateamId = 0;

        if (isRated)
        {
            ateamId = player->GetArenaTeamId(arenaslot);
            ArenaTeam* at = sArenaTeamMgr->GetArenaTeamById(ateamId);

            if (!at)
            {
                player->GetSession()->SendNotInArenaTeamPacket(arenatype);
                return false;
            }

            arenaRating = at->GetRating();
            matchmakerRating = at->GetAverageMMR();

            if (arenaRating <= 0)
                arenaRating = 1;
        }

		BattlegroundQueue &bgQueue = sBattlegroundMgr->GetBattlegroundQueue(bgQueueTypeId);
		bg->SetRated(isRated);

		GroupQueueInfo* ginfo = bgQueue.AddGroup(player, NULL, bracketEntry, isRated, false, arenaRating, matchmakerRating, ateamId);
		uint32 avgTime = bgQueue.GetAverageQueueWaitTime(ginfo);
		uint32 queueSlot = player->AddBattlegroundQueueId(bgQueueTypeId);

		WorldPacket data;

		sBattlegroundMgr->BuildBattlegroundStatusPacket(&data, bg, queueSlot, STATUS_WAIT_QUEUE, avgTime, ginfo->JoinTime, arenatype, player->GetTeamId());
		player->GetSession()->SendPacket(&data);
		sBattlegroundMgr->ScheduleArenaQueueUpdate(ateamId, bgQueueTypeId, bracketEntry->GetBracketId());
        return true;
    }

    bool CreateArenateam(Player* player, Creature* me)
    {
        if (!player || !me)
            return false;

        uint8 slot = ArenaTeam::GetSlotByType(ARENA_TEAM_5v5);
        if (slot >= MAX_ARENA_SLOT)
            return false;

        if (player->GetArenaTeamId(slot))
        {
            player->GetSession()->SendArenaTeamCommandResult(ERR_ARENA_TEAM_CREATE_S, player->GetName(), "", ERR_ALREADY_IN_ARENA_TEAM);
            return false;
        }

        int i = 1;
        std::stringstream teamName;
		teamName << "3vs3 Solo - " << player->GetName();
        do
        {
            if (sArenaTeamMgr->GetArenaTeamByName(teamName.str()) != NULL) // teamname exist, so choose another name
            {
                teamName.str(std::string());
                teamName << player->GetName() << i++;
            }
            else
                break;
        } while (i < 100);

        ArenaTeam* arenaTeam = new ArenaTeam();

        if (!arenaTeam->Create(player->GetGUID(), ARENA_TEAM_5v5, teamName.str(), 4278190080, 45, 4278190080, 5, 4278190080))
        {
            delete arenaTeam;
            return false;
        }

        sArenaTeamMgr->AddArenaTeam(arenaTeam);
        arenaTeam->AddMember(player->GetGUID());

        return true;
    }

    void fetchQueueList()
    {
        if (GetMSTimeDiffToNow(lastFetchQueueList) < 1000)
            return;

        lastFetchQueueList = getMSTime();

        BattlegroundQueue* queue = &sBattlegroundMgr->GetBattlegroundQueue(BATTLEGROUND_QUEUE_3v3_SOLO);

        for (int i = 0; i < MAX_TALENT_CAT; i++)
            cache3v3Queue[i] = 0;

        for (int i = BG_BRACKET_ID_FIRST; i <= BG_BRACKET_ID_LAST; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (BattlegroundQueue::GroupsQueueType::iterator itr = queue->m_QueuedGroups[i][j].begin(); itr != queue->m_QueuedGroups[i][j].end(); itr++)
				{
					if ((*itr)->IsInvitedToBGInstanceGUID)
						continue;

					std::map<uint64, PlayerQueueInfo*> *grpPlr = &(*itr)->Players;
					for (std::map<uint64, PlayerQueueInfo*>::iterator grpPlrItr = grpPlr->begin(); grpPlrItr != grpPlr->end(); grpPlrItr++)
					{
						Player* plr = sObjectAccessor->FindPlayer(grpPlrItr->first);
						if (!plr)
							continue;

						Solo3v3TalentCat plrCat = GetTalentCatForSolo3v3(plr);
						cache3v3Queue[plrCat]++;
					}
				}
			}
		}
    }
};


void AddSC_Solo3v3()
{
    new CreatureScript_Solo3v3();
}
