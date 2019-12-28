#include "ScriptMgr.h"

class PlayerScript_Duel : public PlayerScript
{
	public:
		PlayerScript_Duel() : PlayerScript("PlayerScript_Duel") {}

	void DruidForm(Player * player)
	{
		if (player->getClass() == CLASS_DRUID)
			player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
	}

	void GetPowers(Player *player)
	{
		player->SetHealth(player->GetMaxHealth());

		if (player->getPowerType() == POWER_RAGE)
        {
            DruidForm(player);
            player->SetPower(POWER_RAGE, 0);
        }
		else if (player->getPowerType() == POWER_ENERGY)
		{
			DruidForm(player);
			player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));
		}
		else if (player->getPowerType() == POWER_RUNIC_POWER)
		{
			player->SetPower(POWER_RUNIC_POWER, 0);
		}
		else if (player->getPowerType() == POWER_MANA)
		{
			player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
		}
	}

	void SetPowers(Player * player)
	{
		switch (player->getClass())
		{
			case CLASS_HUNTER:
			case CLASS_WARLOCK:
				GetPowers(player);
				player->RemoveArenaSpellCooldowns(true);
				break;
			default:
				player->RemoveArenaSpellCooldowns();
				GetPowers(player);
				break;
		}
	}

	void OnDuelStart(Player *player1, Player *player2)
	{
        uint32 Auras[] =
        {
            498, 642, 10278, 11196, 25771, 41425, 57723, 57724,
            61987, 66233, 18499, 55694, 1719, 20230, 2687, 23920,
            2565, 871, 60503, 29842, 52437, 16491, 12292, 46916,
            50227, 65116, 58984, 59544, 33697, 26297, 54428, 1044,
            642, 1038, 61987, 31884, 20053, 57669, 59578, 48952,
            31821, 31842, 20216, 34027, 54216, 3045, 19263, 5384,
            34471, 6774, 26669, 11305, 31224, 14177, 63848, 13750,
            13877, 51713, 14278, 6346, 64844, 64904, 48111, 48068,
            586, 47930, 33206, 10060, 47788, 47858, 45529, 48792,
            49016, 49796, 49039, 51271, 50461, 49222, 2825, 30823,
            16166, 64701, 55166, 61295, 55277, 32182, 43010, 43012,
            45438, 12043, 57531, 12042, 12472, 11426, 18708, 47891,
            47241, 22812, 29166, 53312, 33357, 50213, 48505, 61336,
            58923, 17116
        };

        for (uint32 aura : Auras)
        {
            player1->RemoveAura(aura);
            player2->RemoveAura(aura);
        }

        SetPowers(player1);
        SetPowers(player2);
	}

	void OnDuelEnd(Player *Winner, Player *Loser, DuelCompleteType /*type*/)
	{
        SetPowers(Winner);
        SetPowers(Loser);
	}
};

void AddSC_Duel()
{
	new PlayerScript_Duel();
}
