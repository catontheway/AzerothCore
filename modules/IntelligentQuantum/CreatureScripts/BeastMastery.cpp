#include "ScriptMgr.h"
#include "Pet.h"

class CreatureScript_BeastMastery : public CreatureScript
{
	public:
		CreatureScript_BeastMastery() : CreatureScript("CreatureScript_BeastMastery") { }

	void CreatePet(Player * player, Creature * m_creature, uint32 entry)
	{
		if (player->getClass() != CLASS_HUNTER)
		{
			player->GetSession()->SendAreaTriggerMessage("|cff00ffffYou're Not A Hunter !|r");
			player->PlayerTalkClass->SendCloseGossip();
			return;
		}

		if (player->GetPet())
		{
			player->GetSession()->SendAreaTriggerMessage("|cff00ffffPlesae Abandon Your Pet First.|r");
			player->PlayerTalkClass->SendCloseGossip();
			return;
		}

		Creature *creatureTarget = m_creature->SummonCreature(entry, player->GetPositionX(), player->GetPositionY() + 2, player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 500);

		if (!creatureTarget)
			return;

		Pet* pet = player->CreateTamedPetFrom(creatureTarget, 0);

		if (!pet)
			return;

		creatureTarget->setDeathState(JUST_DIED);
		creatureTarget->RemoveCorpse();
		creatureTarget->SetHealth(0);

		pet->SetPower(POWER_HAPPINESS, 1048000);

		pet->SetUInt64Value(UNIT_FIELD_CREATEDBY, player->GetGUID());
		pet->SetUInt32Value(UNIT_FIELD_FACTIONTEMPLATE, player->getFaction());

		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel() - 1);
		pet->GetMap()->AddToMap(pet->ToCreature());

		pet->SetUInt32Value(UNIT_FIELD_LEVEL, player->getLevel());

		pet->GetCharmInfo()->SetPetNumber(sObjectMgr->GeneratePetNumber(), true);

		if (!pet->InitStatsForLevel(player->getLevel()))
			pet->UpdateAllStats();

		pet->UpdateAllStats();

		player->SetMinion(pet, true);

		pet->SavePetToDB(PET_SAVE_AS_CURRENT, true);
		pet->InitTalentForLevel();
		player->PetSpellInitialize();

		player->PlayerTalkClass->SendCloseGossip();
	}

	bool OnGossipHello(Player * player, Creature * m_creature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Normal Pets", GOSSIP_SENDER_MAIN, 1);

		if (player->CanTameExoticPets())
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_INTERACT_1, "Exotic Pets", GOSSIP_SENDER_MAIN, 2);

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, "Food Shop", GOSSIP_SENDER_MAIN, 3);
		player->SEND_GOSSIP_MENU(68, m_creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player * player, Creature * m_creature, uint32 /*Sender*/, uint32 Action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Action)
		{
			case 1:
                player->ADD_GOSSIP_ITEM(4, "Ravager", GOSSIP_SENDER_MAIN, 100);
                player->ADD_GOSSIP_ITEM(4, "Spider", GOSSIP_SENDER_MAIN, 101);
                player->ADD_GOSSIP_ITEM(4, "Wolf", GOSSIP_SENDER_MAIN, 102);
                player->ADD_GOSSIP_ITEM(4, "Scorpion", GOSSIP_SENDER_MAIN, 103);
                player->ADD_GOSSIP_ITEM(4, "Carrion Bird", GOSSIP_SENDER_MAIN, 104);
                player->ADD_GOSSIP_ITEM(4, "Hyena", GOSSIP_SENDER_MAIN, 105);
                player->ADD_GOSSIP_ITEM(4, "Gorilla", GOSSIP_SENDER_MAIN, 106);
                player->ADD_GOSSIP_ITEM(4, "Crocolisk", GOSSIP_SENDER_MAIN, 107);
                player->ADD_GOSSIP_ITEM(4, "Serpent", GOSSIP_SENDER_MAIN, 108);
                player->ADD_GOSSIP_ITEM(4, "Cat", GOSSIP_SENDER_MAIN, 109);
                player->ADD_GOSSIP_ITEM(4, "Crab", GOSSIP_SENDER_MAIN, 110);

				player->SEND_GOSSIP_MENU(68, m_creature->GetGUID());
				break;
			case 2:
                player->ADD_GOSSIP_ITEM(4, "Chimaera", GOSSIP_SENDER_MAIN, 200);
                player->ADD_GOSSIP_ITEM(4, "Core Hound", GOSSIP_SENDER_MAIN, 201);
                player->ADD_GOSSIP_ITEM(4, "Devilsaur", GOSSIP_SENDER_MAIN, 202);
                player->ADD_GOSSIP_ITEM(4, "Rhino", GOSSIP_SENDER_MAIN, 203);
                player->ADD_GOSSIP_ITEM(4, "Silithid", GOSSIP_SENDER_MAIN, 204);
                player->ADD_GOSSIP_ITEM(4, "Worm", GOSSIP_SENDER_MAIN, 205);
                player->ADD_GOSSIP_ITEM(4, "Spirit Beast (Bear)", GOSSIP_SENDER_MAIN, 206);
                player->ADD_GOSSIP_ITEM(4, "Spirit Beast (Tiger)", GOSSIP_SENDER_MAIN, 207);
                player->ADD_GOSSIP_ITEM(4, "Spirit Beast (Wolf)", GOSSIP_SENDER_MAIN, 208);
                player->ADD_GOSSIP_ITEM(4, "Spirit Beast (Leopard)", GOSSIP_SENDER_MAIN, 209);

				player->SEND_GOSSIP_MENU(68, m_creature->GetGUID());
				break;
			case 3:
				player->GetSession()->SendListInventory(m_creature->GetGUID());
				break;
			case 100:
				CreatePet(player, m_creature, 19349);
				break;
			case 101:
				CreatePet(player, m_creature, 930);
				break;
			case 102:
				CreatePet(player, m_creature, 213);
				break;
			case 103:
				CreatePet(player, m_creature, 5424);
				break;
			case 104:
				CreatePet(player, m_creature, 5429);
				break;
			case 105:
				CreatePet(player, m_creature, 5426);
				break;
			case 106:
				CreatePet(player, m_creature, 6513);
				break;
			case 107:
				CreatePet(player, m_creature, 28002);
				break;
			case 108:
				CreatePet(player, m_creature, 28011);
				break;
			case 109:
				CreatePet(player, m_creature, 28001);
				break;
			case 110:
				CreatePet(player, m_creature, 3108);
				break;
			case 200:
				CreatePet(player, m_creature, 8764);
				break;
			case 201:
				CreatePet(player, m_creature, 17447);
				break;
			case 202:
				CreatePet(player, m_creature, 6499);
				break;
			case 203:
				CreatePet(player, m_creature, 32361);
				break;
			case 204:
				CreatePet(player, m_creature, 15230);
				break;
			case 205:
				CreatePet(player, m_creature, 26359);
				break;
			case 206:
				CreatePet(player, m_creature, 38453);
				break;
			case 207:
				CreatePet(player, m_creature, 33776);
				break;
			case 208:
				CreatePet(player, m_creature, 35189);
				break;
			case 209:
				CreatePet(player, m_creature, 32517);
				break;
            default:
                break;
		}
		return true;
	}

};

void AddSC_BeastMastery()
{
	new CreatureScript_BeastMastery();
}
