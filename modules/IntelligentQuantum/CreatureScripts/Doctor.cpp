#include "ScriptMgr.h"
#include "Chat.h"
#include "Group.h"
#include "InstanceSaveMgr.h"
#include "InstanceScript.h"
#include "MapManager.h"
#include "Player.h"
#include "Language.h"

class CreatureScript_Doctor : public CreatureScript
{
	public:
		CreatureScript_Doctor() : CreatureScript("CreatureScript_Doctor") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->IsInCombat() || player->duel || !player->IsAlive())
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ffffYou couldn't do this right now !|r");
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}

        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Max Skill", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Give Me Gold", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Repair All Items", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Remove Sickness", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Remove Shaman Debuff", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Remove Paladin Debuff", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
        AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Remove All Spell Coldown", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);

		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

        switch (Actions)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->UpdateSkillsToMaxSkillsForLevel();
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->ModifyMoney(1 * 500000000);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->DurabilityRepairAll(false, 0.0f, true);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->RemoveAurasDueToSpell(15007);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->RemoveAurasDueToSpell(57723);
                player->RemoveAurasDueToSpell(57724);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->RemoveAurasDueToSpell(25771);
                CloseGossipMenuFor(player);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                player->RemoveArenaSpellCooldowns(true);
                player->SetHealth(player->GetMaxHealth());
                player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
                CloseGossipMenuFor(player);
                break;
            default:
                CloseGossipMenuFor(player);
                break;
        }

		return true;
	}

};

void AddSC_Doctor()
{
	new CreatureScript_Doctor();
}
