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
        AddGossipItemFor(player, GOSSIP_ICON_DOT, "Normal Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (player->CanTameExoticPets())
            AddGossipItemFor(player, GOSSIP_ICON_DOT, "Exotic Pets", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        AddGossipItemFor(player, GOSSIP_ICON_VENDOR, "Food Shop", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature);
        return true;
	}

	bool OnGossipSelect(Player * player, Creature * m_creature, uint32 /*Sender*/, uint32 Action)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (Action)
		{
			case 1:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Ravager", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Spider", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Wolf", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Scorpion", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Carrion Bird", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Hyena", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Gorilla", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Crocolisk", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Serpent", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Cat", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Crab", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);

                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature);
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Chimaera", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Core Hound", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Devilsaur", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Rhino", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Silithid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Worm", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Spirit Beast (Bear)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Spirit Beast (Tiger)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Spirit Beast (Wolf)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                AddGossipItemFor(player, GOSSIP_ICON_BATTLE, "Spirit Beast (Leopard)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);

                SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, m_creature);
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->GetSession()->SendListInventory(m_creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                CreatePet(player, m_creature, 19349);
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                CreatePet(player, m_creature, 930);
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                CreatePet(player, m_creature, 213);
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                CreatePet(player, m_creature, 5424);
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                CreatePet(player, m_creature, 5429);
                break;
            case GOSSIP_ACTION_INFO_DEF + 9:
                CreatePet(player, m_creature, 5426);
                break;
            case GOSSIP_ACTION_INFO_DEF + 10:
                CreatePet(player, m_creature, 6513);
                break;
            case GOSSIP_ACTION_INFO_DEF + 11:
                CreatePet(player, m_creature, 28002);
                break;
            case GOSSIP_ACTION_INFO_DEF + 12:
                CreatePet(player, m_creature, 28011);
                break;
            case GOSSIP_ACTION_INFO_DEF + 13:
                CreatePet(player, m_creature, 28001);
                break;
            case GOSSIP_ACTION_INFO_DEF + 14:
                CreatePet(player, m_creature, 3108);
                break;
            case GOSSIP_ACTION_INFO_DEF + 15:
                CreatePet(player, m_creature, 8764);
                break;
            case GOSSIP_ACTION_INFO_DEF + 16:
                CreatePet(player, m_creature, 17447);
                break;
            case GOSSIP_ACTION_INFO_DEF + 17:
                CreatePet(player, m_creature, 6499);
                break;
            case GOSSIP_ACTION_INFO_DEF + 18:
                CreatePet(player, m_creature, 32361);
                break;
            case GOSSIP_ACTION_INFO_DEF + 19:
                CreatePet(player, m_creature, 15230);
                break;
            case GOSSIP_ACTION_INFO_DEF + 20:
                CreatePet(player, m_creature, 26359);
                break;
            case GOSSIP_ACTION_INFO_DEF + 21:
                CreatePet(player, m_creature, 38453);
                break;
            case GOSSIP_ACTION_INFO_DEF + 22:
                CreatePet(player, m_creature, 33776);
                break;
            case GOSSIP_ACTION_INFO_DEF + 23:
                CreatePet(player, m_creature, 35189);
                break;
            case GOSSIP_ACTION_INFO_DEF + 24:
                CreatePet(player, m_creature, 32517);
                break;
            default:
                CloseGossipMenuFor(player);
                break;
		}
		return true;
	}

};

void AddSC_BeastMastery()
{
	new CreatureScript_BeastMastery();
}
