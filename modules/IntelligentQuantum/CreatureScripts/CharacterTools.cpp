#include "ScriptMgr.h"

class CreatureScript_CharacterTools : public CreatureScript
{
	public:
		CreatureScript_CharacterTools() : CreatureScript("CreatureScript_CharacterTools") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Change My Race", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Change My Name", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Change My Faction", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Change My Appearance", GOSSIP_SENDER_MAIN, 4);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Actions)
		{
			case 1:
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 2:
				player->SetAtLoginFlag(AT_LOGIN_RENAME);
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 3:
				player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 4:
				player->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
				player->PlayerTalkClass->SendCloseGossip();
				break;
        }
		return true;
	}

};

void AddSC_CharacterTools()
{
	new CreatureScript_CharacterTools();
}
