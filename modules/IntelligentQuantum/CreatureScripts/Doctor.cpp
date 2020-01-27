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

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Max Skill", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Give Me Gold", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove Sickness", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove Shaman Debuff", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove Paladin Debuff", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove All Spell Coldown", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Remove All Instance Save (EOF) 5X", GOSSIP_SENDER_MAIN, 7);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Actions)
		{
			case 1:
				player->UpdateSkillsToMaxSkillsForLevel();
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 2:
				player->ModifyMoney(1 * 500000000);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 3:
				player->RemoveAurasDueToSpell(15007);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 4:
				player->RemoveAurasDueToSpell(57723);
				player->RemoveAurasDueToSpell(57724);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 5:
				player->RemoveAurasDueToSpell(25771);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 6:
				player->RemoveArenaSpellCooldowns(true);
				player->SetHealth(player->GetMaxHealth());
				player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				player->PlayerTalkClass->SendCloseGossip();
				break;
            case 7:
                if (!player->HasItemCount(49426, 5))
                {
                    player->GetSession()->SendAreaTriggerMessage("You Dont Have Enough Emblem Of Frost.|r");
                    player->PlayerTalkClass->SendCloseGossip();
                    return false;
                }
                else
                {
                    for (uint8 i = 0; i < MAX_DIFFICULTY; ++i)
                    {
                        BoundInstancesMap const& m_boundInstances = sInstanceSaveMgr->PlayerGetBoundInstances(player->GetGUIDLow(), Difficulty(i));

                        for (BoundInstancesMap::const_iterator itr = m_boundInstances.begin(); itr != m_boundInstances.end();)
                        {
                            sInstanceSaveMgr->PlayerUnbindInstance(player->GetGUIDLow(), itr->first, Difficulty(i), true, player);
                        }
                    }

                    player->DestroyItemCount(49426, 5, true);
                    player->PlayerTalkClass->SendCloseGossip();
                }
                break;
            default:
                break;
        }
		return true;
	}

};

void AddSC_Doctor()
{
	new CreatureScript_Doctor();
}
