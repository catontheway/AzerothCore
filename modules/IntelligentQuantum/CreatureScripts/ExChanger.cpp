#include "ScriptMgr.h"

class CreatureScript_ExChanger : public CreatureScript
{
public:
    CreatureScript_ExChanger() : CreatureScript("CreatureScript_ExChanger") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Change 100x PvP Token To 2K Honor", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Change 10K Honor To 100x PvP Token", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Change 1K Arena Points To 1x Donate Token", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Change 24x Played Time Token To 1x Donate Token", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Change 3x Played Time Token To 10x Trans Token", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Change 3x Played Time Token To 5x Cosmetic Token", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Other Ex-Changer", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Actions)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (Actions)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->GetSession()->SendListInventory(creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                if (player->HasItemCount(100002, 100))
                {
                    player->ModifyHonorPoints(+2000);
                    player->DestroyItemCount(100002, 100, true);
                    ChatHandler(player->GetSession()).PSendSysMessage("You Exchanged Succesfully");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You Don't Have Enough PvP Token");
                    CloseGossipMenuFor(player);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                if (player->GetHonorPoints() >= 10000)
                {
                    player->ModifyHonorPoints(-10000);
                    player->AddItem(100002, 100);
                    ChatHandler(player->GetSession()).PSendSysMessage("You Exchanged Succesfully");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You Don't Have Enough Honor");
                    CloseGossipMenuFor(player);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                if (player->GetArenaPoints() >= 1000)
                {
                    player->ModifyArenaPoints(-1000);
                    player->AddItem(100004, 1);
                    ChatHandler(player->GetSession()).PSendSysMessage("You Exchanged Succesfully");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You Don't Have Enough Arena");
                    CloseGossipMenuFor(player);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                if (player->HasItemCount(100006, 24))
                {
                    player->AddItem(100004, 1);
                    player->DestroyItemCount(100006, 24, true);
                    ChatHandler(player->GetSession()).PSendSysMessage("You Exchanged Succesfully");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You Don't Have Enough Played Time Token");
                    CloseGossipMenuFor(player);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                if (player->HasItemCount(100006, 3))
                {
                    player->AddItem(100001, 10);
                    player->DestroyItemCount(100006, 3, true);
                    ChatHandler(player->GetSession()).PSendSysMessage("You Exchanged Succesfully");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You Don't Have Enough Played Time Token");
                    CloseGossipMenuFor(player);
                }
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                if (player->HasItemCount(100006, 3))
                {
                    player->AddItem(100005, 5);
                    player->DestroyItemCount(100006, 3, true);
                    ChatHandler(player->GetSession()).PSendSysMessage("You Exchanged Succesfully");
                    CloseGossipMenuFor(player);
                }
                else
                {
                    ChatHandler(player->GetSession()).PSendSysMessage("You Don't Have Enough Played Time Token");
                    CloseGossipMenuFor(player);
                }
                break;
            default:
                CloseGossipMenuFor(player);
                break;
        }

        return true;
    }
};

void AddSC_ExChanger()
{
    new CreatureScript_ExChanger();
}
