#include "ScriptMgr.h"

class CreatureScript_CharacterTools : public CreatureScript
{
	public:
		CreatureScript_CharacterTools() : CreatureScript("CreatureScript_CharacterTools") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Change My Race (PvP Token 50x)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Change My Name (Donate Token 5x)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Change My Faction (PvP Token 100x)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Change My Appearance (PvP Token 50x)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);

		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

        switch (Actions)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                if (!player->HasItemCount(100002, 50))
                {
                    player->GetSession()->SendAreaTriggerMessage("|cff00ffffYou don't have enough PvP Token|r");
                    CloseGossipMenuFor(player);
                    return false;
                }

                player->GetSession()->SendAreaTriggerMessage("Please Logout For Race Change");
                player->DestroyItemCount(100002, 50, true);
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                if (!player->HasItemCount(100004, 5))
                {
                    player->GetSession()->SendAreaTriggerMessage("|cff00ffffYou don't have enough Donate Token|r");
                    CloseGossipMenuFor(player);
                    return false;
                }

                player->GetSession()->SendAreaTriggerMessage("Please Logout For Name Change");
                player->DestroyItemCount(100004, 5, true);
                player->SetAtLoginFlag(AT_LOGIN_RENAME);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                if (!player->HasItemCount(100002, 100))
                {
                    player->GetSession()->SendAreaTriggerMessage("|cff00ffffYou don't have enough PvP Token|r");
                    CloseGossipMenuFor(player);
                    return false;
                }

                player->GetSession()->SendAreaTriggerMessage("Please Logout For Faction Change");
                player->DestroyItemCount(100002, 100, true);
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                if (!player->HasItemCount(100002, 50))
                {
                    player->GetSession()->SendAreaTriggerMessage("|cff00ffffYou don't have enough PvP Token|r");
                    CloseGossipMenuFor(player);
                    return false;
                }

                player->GetSession()->SendAreaTriggerMessage("Please Logout For Character Customize");
                player->DestroyItemCount(100002, 50, true);
                player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
                CloseGossipMenuFor(player);
                break;
            default:
                CloseGossipMenuFor(player);
                break;
        }

		return true;
	}

};

void AddSC_CharacterTools()
{
	new CreatureScript_CharacterTools();
}
