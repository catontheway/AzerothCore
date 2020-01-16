#include "ScriptMgr.h"

class CreatureScript_ExChanger : public CreatureScript
{
public:
    CreatureScript_ExChanger() : CreatureScript("CreatureScript_ExChanger") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        player->ADD_GOSSIP_ITEM(3, "Change 50x Bloody Token To 8K Honor", GOSSIP_SENDER_MAIN, 1);
        player->ADD_GOSSIP_ITEM(3, "Change 50x Bloody Token To 2x EoF", GOSSIP_SENDER_MAIN, 2);
        player->ADD_GOSSIP_ITEM(3, "Change 1x EoF To 25x Bloody Token", GOSSIP_SENDER_MAIN, 3);
        player->ADD_GOSSIP_ITEM(3, "Change 1x EoF To 2K Honor", GOSSIP_SENDER_MAIN, 4);
        player->ADD_GOSSIP_ITEM(3, "Other Ex-Changer", GOSSIP_SENDER_MAIN, 5);

        player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Actions)
    {
        player->PlayerTalkClass->ClearMenus();

        switch (Actions)
        {
            case 1:
                if (player->HasItemCount(100002, 50))
                {
                    player->ModifyHonorPoints(+8000);
                    player->DestroyItemCount(100002, 50, true);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();
                break;
            case 2:
                if (player->HasItemCount(100002, 50))
                {
                    player->AddItem(100002, 2);
                    player->DestroyItemCount(100002, 50, true);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();
                break;
            case 3:
                if (player->HasItemCount(49426, 1))
                {
                    player->AddItem(100002, 25);
                    player->DestroyItemCount(49426, 1, true);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();
                break;
            case 4:
                if (player->HasItemCount(49426, 1))
                {
                    player->ModifyHonorPoints(+2000);
                    player->DestroyItemCount(49426, 1, true);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                else
                    player->PlayerTalkClass->SendCloseGossip();
                break;
            case 5:
                player->GetSession()->SendListInventory(creature->GetGUID());
                break;
            default:
                break;
        }
        return true;
    }
};

void AddSC_ExChanger()
{
    new CreatureScript_ExChanger();
}
