#include "ScriptMgr.h"

class CreatureScript_Teleport : public CreatureScript
{
	public:
		CreatureScript_Teleport() : CreatureScript("CreatureScript_Teleport") {}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->IsInCombat() || player->duel || !player->IsAlive())
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ffffYou couldn't do this right now !|r");
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Shop Mall", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Work Center", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Transmog Center", GOSSIP_SENDER_MAIN, 9);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "DuelZone", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "PvPZone", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Icecrown", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Daily Zone", GOSSIP_SENDER_MAIN, 5);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Actions)
		{
			case 1:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(571, 8302.129883f, 3204.659912f, 631.161011f, 4.830314f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 2:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(530, -250.225281f, 1064.436890f, 54.310257f, 1.614673f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 3:
				player->AddAura(8611, player);
				player->TeleportTo(0, -13228.915039f, 226.867920f, 32.745441f, 1.122707f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 4:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(571, 5873.819824f, 2110.979980f, 636.010986f, 3.552300f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 5:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Stormwind", GOSSIP_SENDER_MAIN, 6);
            	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Orgrimmar", GOSSIP_SENDER_MAIN, 7);

				player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
				break;
			case 6:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(0, -9129.269531f, 388.208740f, 91.057014f, 0.637305f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 7:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(1, 1346.678955f, -4373.142090f, 26.181185f, 0.070212f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 8:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(571, 1146.480957f, -4888.828613f, 408.806915f, 0.301689f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 9:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(571, 8428.708008f, 2879.004883f, 606.259583f, 1.633352f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
            default:
                break;
		}
		return true;
	}
};

void AddSC_Teleport()
{
	new CreatureScript_Teleport();
}
