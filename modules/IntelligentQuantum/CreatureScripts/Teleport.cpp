#include "ScriptMgr.h"

static const Position PlayerSpawnPoint[5] =
{
    {1082.826172f, -2574.552490f, 59.957962f, 0.459430f},
    {1108.761353f, -2516.412109f, 59.954971f, 5.195375f},
    {1146.359497f, -2508.554932f, 62.094009f, 3.879836f},
    {1150.805664f, -2576.504395f, 64.738426f, 1.920263f},
    {1175.773560f, -2521.281494f, 61.110966f, 3.432152f}
};

class CreatureScript_Teleport : public CreatureScript
{
	public:
		CreatureScript_Teleport() : CreatureScript("CreatureScript_Teleport") {}

	bool OnGossipHello(Player* player, Creature* creature)
	{
        if (player->IsInCombat() || player->duel || player->InArena() || player->InBattleground() || !player->IsAlive())
        {
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ffffYou cannot use teleport right now !|r");
            player->PlayerTalkClass->SendCloseGossip();
            return false;
        }

        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Shop Mall", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Duel Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
        // AddGossipItemFor(player, GOSSIP_ICON_TAXI, "PvP Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Work Center", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Transmog Center", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Cosmetic Room", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Training Dummy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Quest Zone", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Icecrown", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
        AddGossipItemFor(player, GOSSIP_ICON_TAXI, "City Teleport", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
        return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

        switch (Actions)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if(player->GetTeamId() == TEAM_ALLIANCE)
                {
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Stormwind", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Ironforge", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Darnassus", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "The Exodar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                }
                else
                {
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Orgrimmar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Thunder Bluff", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Undercity", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                    AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Silvermoon", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                }
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Dalaran", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Shattrath", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);

                player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->TeleportTo(0, -9129.269531f, 388.208740f, 91.057014f, 0.637305f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->TeleportTo(0, -5000.476074f, -859.561523f, 497.045746f, 5.405354f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->TeleportTo(1, 9954.119141f, 2167.963867f, 1327.462891f, 1.536971f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->TeleportTo(530, -4001.156982f, -11873.359375f, -0.527358f, 1.064644f);
                player->SetPhaseMask(1,1);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->TeleportTo(1, 1346.678955f, -4373.142090f, 26.181185f, 0.070212f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->TeleportTo(1, -1267.347534f, 221.531189f, 59.157173f, 4.593608f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                player->TeleportTo(0, 1887.412964f, 237.202225f, 57.703121f, 3.034173f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:
                player->TeleportTo(530, 9370.547852f, -7277.637207f, 14.240896f, 0.007574f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:
                player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:
                player->TeleportTo(530, -1721.781128f, 5382.058105f, 1.545847f, 2.754345f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:
                player->TeleportTo(469, -7595.870117f, -1053.469971f, 409.797485f, 3.763400f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:
                player->TeleportTo(0, 4164.259766f, -3895.590088f, 134.281006f, 5.195740f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 14:
                player->TeleportTo(469, -7561.358398f, -1051.956909f, 408.490662f, 0.642806f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 15:
                player->TeleportTo(469, -7582.596191f, -1021.794434f, 408.491211f, 0.591756f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 16:
                player->TeleportTo(469, -7475.237305f, -1028.082031f, 408.569275f, 2.177780f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 17:
                player->TeleportTo(469, -7615.787598f, -1024.995972f, 413.381531f, 2.178264f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 18:
            {
                int32 RespawnPos = urand(0, 5 - 1);
                player->TeleportTo(0, PlayerSpawnPoint[RespawnPos].GetPositionX(), PlayerSpawnPoint[RespawnPos].GetPositionY(), PlayerSpawnPoint[RespawnPos].GetPositionZ(), PlayerSpawnPoint[RespawnPos].GetOrientation());
                CloseGossipMenuFor(player);
            }
            break;
            case GOSSIP_ACTION_INFO_DEF + 19:
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Bloodmoon Isle (5 MAN)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                AddGossipItemFor(player, GOSSIP_ICON_TAXI, "Alcaz Island (Solo)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);

                player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 20:
                player->TeleportTo(571, 4538.409668f, -5479.918945f, 1.565197f, 5.403717f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 21:
                player->TeleportTo(1, -2704.870117f, -4668.560059f, 13.103700f, 4.674040f);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 22:
                player->TeleportTo(571, 5873.819824f, 2110.979980f, 636.010986f, 3.552300f);
                CloseGossipMenuFor(player);
                break;
            default:
                CloseGossipMenuFor(player);
                break;
        }

		return true;
	}
};

void AddSC_Teleport()
{
	new CreatureScript_Teleport();
}
