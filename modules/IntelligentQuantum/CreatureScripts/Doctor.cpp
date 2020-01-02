#include "ScriptMgr.h"

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

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Ability_Warrior_SecondWind:25|t|r Max Skill", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Spell_Shadow_DeathScream:25|t|r Remove Sickness", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Spell_Nature_Sleep:25|t|r Remove Shaman Debuff", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Spell_holy_removecurse:25|t|r Remove Paladin Debuff", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Inv_misc_enggizmos_30:25|t|r Remove All Spell Coldown", GOSSIP_SENDER_MAIN, 5);

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
				player->RemoveAurasDueToSpell(15007);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 3:
				player->RemoveAurasDueToSpell(57723);
				player->RemoveAurasDueToSpell(57724);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 4:
				player->RemoveAurasDueToSpell(25771);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 5:
				player->RemoveArenaSpellCooldowns(true);
				player->SetHealth(player->GetMaxHealth());
				player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
				player->PlayerTalkClass->SendCloseGossip();
				break;
		}
		return true;
	}

};

void AddSC_Doctor()
{
	new CreatureScript_Doctor();
}
