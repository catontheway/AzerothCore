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

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Temp:30|t|r .::Shop::.", GOSSIP_SENDER_MAIN, 12);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Achievement_bg_winwsg:30|t|r .::DuelZone::.", GOSSIP_SENDER_MAIN, 13);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Achievement_BG_AB_defendflags:30|t|r .::PvPZone::.", GOSSIP_SENDER_MAIN, 14);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|TInterface\\icons\\Achievement_Dungeon_Icecrown_Frostmourne:30|t|r .::Icecrown::.", GOSSIP_SENDER_MAIN, 15);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Ability_hunter_huntervswild:30|t|r .::City Teleport::.", GOSSIP_SENDER_MAIN, 1);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Actions)
		{
			case 12:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1202.095337f, 1398.909302f, 29.009785f, 3.171714f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 13:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(0, -5108.125977f, -1792.048340f, 497.835999f, 1.364920f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 14:
				player->AddAura(8611, player);
				player->TeleportTo(0, -13228.915039f, 226.867920f, 32.745441f, 1.122707f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 15:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(571, 5873.819824f, 2110.979980f, 636.010986f, 3.552300f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 1:
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportStormWind:25|t|r Stormwind", GOSSIP_SENDER_MAIN, 2);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportIronForge:25|t|r Ironforge", GOSSIP_SENDER_MAIN, 3);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportDarnassus:25|t|r Darnassus", GOSSIP_SENDER_MAIN, 4);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportExodar:25|t|r The Exodar", GOSSIP_SENDER_MAIN, 5);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportOrgrimmar:25|t|r Orgrimmar", GOSSIP_SENDER_MAIN, 6);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportThunderBluff:25|t|r Thunder Bluff", GOSSIP_SENDER_MAIN, 7);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportUnderCity:25|t|r Undercity", GOSSIP_SENDER_MAIN, 8);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportSilvermoon:25|t|r Silvermoon", GOSSIP_SENDER_MAIN, 9);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportDalaran:25|t|r Dalaran", GOSSIP_SENDER_MAIN, 10);
				player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "|cff00ff00|TInterface\\icons\\Spell_Arcane_TeleportShattrath:25|t|r Shattrath", GOSSIP_SENDER_MAIN, 11);

				player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
				break;
			case 2:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(0, -9129.269531f, 388.208740f, 91.057014f, 0.637305f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 3:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(0, -5000.476074f, -859.561523f, 497.045746f, 5.405354f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 4:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(1, 9954.119141f, 2167.963867f, 1327.462891f, 1.536971f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 5:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(530, -4001.156982f, -11873.359375f, -0.527358f, 1.064644f);
				player->SetPhaseMask(1, 1);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 6:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(1, 1346.678955f, -4373.142090f, 26.181185f, 0.070212f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 7:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(1, -1267.347534f, 221.531189f, 59.157173f, 4.593608f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 8:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(0, 1887.412964f, 237.202225f, 57.703121f, 3.034173f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 9:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(530, 9370.547852f, -7277.637207f, 14.240896f, 0.007574f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 10:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(571, 5804.149902f, 624.770996f, 647.767029f, 1.640000f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 11:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(530, -1721.781128f, 5382.058105f, 1.545847f, 2.754345f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
		}
		return true;
	}
};

class CreatureScript_Teleport_Mall : public CreatureScript
{
	public:
		CreatureScript_Teleport_Mall() : CreatureScript("CreatureScript_Teleport_Mall") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->IsInCombat() || player->duel || !player->IsAlive())
		{
			ChatHandler(player->GetSession()).PSendSysMessage("|cff00ffffYou couldn't do this right now !|r");
			player->PlayerTalkClass->SendCloseGossip();
			return false;
		}

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Training Area::.", GOSSIP_SENDER_MAIN, 1);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Work Center::.", GOSSIP_SENDER_MAIN, 2);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::TransMog Area::.", GOSSIP_SENDER_MAIN, 3);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Start Gear::.", GOSSIP_SENDER_MAIN, 4);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Quest::.", GOSSIP_SENDER_MAIN, 5);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Set One::.", GOSSIP_SENDER_MAIN, 6);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Set TWO::.", GOSSIP_SENDER_MAIN, 7);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Donate Shop::.", GOSSIP_SENDER_MAIN, 8);
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, ".::Dummy Trainer::.", GOSSIP_SENDER_MAIN, 9);

		player->PlayerTalkClass->SendGossipMenu(68, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*Sender*/, uint32 Actions)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Actions)
		{
			case 1:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1202.095337f, 1398.909302f, 29.009785f, 3.171714f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 2:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1166.410156f, 1341.182739f, 31.549500f, 3.108536f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 3:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1165.725464f, 1438.427246f, 31.548861f, 3.096108f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 4:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1134.714966f, 1399.274902f, 30.306320f, 3.114961f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 5:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1045.054932f, 1343.384033f, 29.146563f, 1.554565f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 6:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 986.846375f, 1343.289429f, 29.146698f, 1.574158f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 7:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 986.871399f, 1454.885498f, 29.146669f, 4.710279f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 8:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 1045.335938f, 1454.887573f, 29.146769f, 4.648983f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
			case 9:
				player->CastSpell(player, 35517, true);
				player->TeleportTo(189, 909.165955f, 1398.667236f, 18.023378f, 3.135518f);
				player->PlayerTalkClass->SendCloseGossip();
				break;
		}
		return true;
	}

};

void AddSC_Teleport()
{
	new CreatureScript_Teleport();
	new CreatureScript_Teleport_Mall();
}
