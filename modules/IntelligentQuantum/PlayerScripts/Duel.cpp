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

	void Powers(Player *player)
	{
		player->SetHealth(player->GetMaxHealth());

        switch (player->getPowerType())
        {
            case POWER_RAGE:
                DruidForm(player);
                player->SetPower(POWER_RAGE, 0);
                break;
            case POWER_ENERGY:
                DruidForm(player);
                player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));
                break;
            case POWER_RUNIC_POWER:
                player->SetPower(POWER_RUNIC_POWER, 0);
                break;
            case POWER_MANA:
                player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
                break;
            default:
                break;
        }
	}

	void RemoveCooldowns(Player * player)
	{
		switch (player->getClass())
		{
			case CLASS_HUNTER:
			case CLASS_WARLOCK:
            case CLASS_DEATH_KNIGHT:
                Powers(player);
				player->RemoveArenaSpellCooldowns(true);
				break;
			default:
				player->RemoveArenaSpellCooldowns();
                Powers(player);
				break;
		}
	}

	void OnDuelStart(Player *player1, Player *player2)
	{
        uint32 Auras[] = {15007, 57723, 57724, 25771};

        for (uint32 aura : Auras)
        {
            player1->RemoveAura(aura);
            player2->RemoveAura(aura);
        }

        RemoveCooldowns(player1);
        RemoveCooldowns(player2);
	}

    void OnDuelEnd(Player *Winner, Player *Loser, DuelCompleteType /*type*/)
	{
        Powers(Winner);
        Powers(Loser);
	}
};

void AddSC_Duel()
{
	new PlayerScript_Duel();
}
